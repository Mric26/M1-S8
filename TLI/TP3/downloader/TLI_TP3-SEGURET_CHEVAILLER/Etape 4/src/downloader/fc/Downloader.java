package downloader.fc;

import java.net.URL;
import java.net.URLConnection;
import java.net.MalformedURLException;
import java.util.concurrent.locks.ReentrantLock;
import java.io.File;
import java.io.BufferedInputStream;
import java.io.FileOutputStream;
import java.io.IOException;

import javax.swing.SwingWorker;

public class Downloader extends SwingWorker<String, Void> {
	public static final int CHUNK_SIZE = 1024;
	private final ReentrantLock lock;
	private boolean etat; 												//un enum est ici inutile etant donné qu'il n'y a que deux états. true = play & false = pause
	
	URL url;
	int content_length;
	BufferedInputStream in;
	
	String filename;
	File temp;
	FileOutputStream out;
	
	public Downloader(String uri) {
		try {
			url = new URL(uri);
			lock = new ReentrantLock();
			setEtat(true);
			
			URLConnection connection = url.openConnection();
			content_length = connection.getContentLength();
			
			in = new BufferedInputStream(connection.getInputStream());
			
			String[] path = url.getFile().split("/");
			filename = path[path.length-1];
			temp = File.createTempFile(filename, ".part");
			out = new FileOutputStream(temp);
		}
		catch(MalformedURLException e) { throw new RuntimeException(e); }
		catch(IOException e) { throw new RuntimeException(e); }
	}
	
	public String toString() {
		return url.toString();
	}

	public String doInBackground() throws InterruptedException {
		byte buffer[] = new byte[CHUNK_SIZE];
		int size = 0;
		int count = 0;
		
		setEtat(true);
		
		while( count >= 0 ) {
			//pose du lock
			lock.lock();
			//relechargement
			try{
				out.write(buffer, 0, count);
			}
			catch(IOException e) { continue; }
			
			size += count;
			setProgress(100*size/content_length);
			
			try{
				count = in.read(buffer, 0, CHUNK_SIZE);
			}
			catch(IOException e) { continue; }
			//relache le lock
			lock.unlock();
			//dodo
			Thread.sleep(1000);
		}
		
		if(size < content_length) {
			temp.delete();
			throw new InterruptedException();
		}
		
		temp.renameTo(new File(filename));
		return filename;
	}
	
	public void Play(){
		lock.unlock();
		setEtat(true);
	}
	
	public void Pause(){
		lock.lock();
		setEtat(false);
	}

	public boolean getEtat() {
		return etat;
	}

	public void setEtat(boolean etat) {
		this.etat = etat;
	}
	
}
