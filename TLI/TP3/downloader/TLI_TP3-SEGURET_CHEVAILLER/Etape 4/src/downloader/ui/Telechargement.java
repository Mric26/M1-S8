package downloader.ui;

import java.beans.PropertyChangeEvent;
import java.beans.PropertyChangeListener;
import javax.swing.JProgressBar;
import downloader.fc.Downloader;

class Telechargement implements Runnable {
   private Thread t;
   private String threadName;
   private String url;
   private JProgressBar barre;
   
   Telechargement( String name, String add, final JProgressBar b ){
       threadName = name;
       url = add;
       barre = b;
   }
   
   public void run() {
	   try {
			final Downloader downloader = new Downloader(url);
			System.out.format("Downloading %s:", downloader);
			
			//ajouter listener au downlader
			downloader.addPropertyChangeListener(new  PropertyChangeListener() {
				public void propertyChange(PropertyChangeEvent evt) {
					System.out.print(".");
					System.out.flush();
					barre.setValue( downloader.getProgress() );
				}
			});
			
			//String filename = downloader.download();
			//System.out.format("into %s\n", filename);
			
		}
		catch( Exception e ) {
			System.err.println("Download failed!");
		}
   }
   
   public void start () {
	   if (t == null) {
		   t = new Thread (this, threadName);
		   t.start ();
	   }
   }

} 
