package downloader.ui;

import java.awt.BorderLayout;
import java.awt.Dimension;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;
import java.beans.PropertyChangeEvent;
import java.beans.PropertyChangeListener;

import javax.swing.BoxLayout;
import javax.swing.JButton;
import javax.swing.JFrame;
import javax.swing.JLabel;
import javax.swing.JPanel;
import javax.swing.JProgressBar;
import javax.swing.JScrollPane;
import javax.swing.JTextField;
import javax.swing.SwingUtilities;

import downloader.fc.Downloader;

public class Main extends JFrame {
	private JPanel zoneBarres;
	
	Main(String title) {
		//fenetre principale
		super(title);
		this.setDefaultCloseOperation(EXIT_ON_CLOSE);
		this.setMinimumSize(new Dimension(800, 400));
		this.setLayout( new BorderLayout() );

		//zone des barres
		zoneBarres = new JPanel();
		zoneBarres.setLayout( new StackLayout() );

		//zone add (en bas)
		JPanel ajouterTelechargement = new JPanel();
		ajouterTelechargement.setLayout( new BorderLayout() );
		final JTextField recherche = new JTextField("");
		ajouterTelechargement.add(recherche, BorderLayout.CENTER);
		JButton add = new JButton("ADD"); 
		ajouterTelechargement.add( add, BorderLayout.EAST);
		add.addActionListener(new ActionListener() {
			public void actionPerformed(ActionEvent e) {
				ajouterDownload( recherche.getText() );
			}
		});

		//ajout élément + visible
		this.add(zoneBarres, BorderLayout.CENTER);
		this.add(ajouterTelechargement, BorderLayout.SOUTH);
		pack();
		this.setVisible(true);
	}

	public void ajouterDownload( String url ){
		//ajout details tel
		final JPanel itemTelechargement = new JPanel();
		itemTelechargement.setLayout( new BorderLayout() );
			//url + barra
			JPanel detailBarres = new JPanel();
			detailBarres.setLayout( new StackLayout() );
			JLabel txt = new JLabel(url);
			detailBarres.add(txt);
			final JProgressBar b = new JProgressBar();
			b.setStringPainted(true);
			detailBarres.add(b);
			itemTelechargement.add(detailBarres, BorderLayout.CENTER);
			//boutons
			JPanel ZoneBoutonDroite= new JPanel();
			BoxLayout boxLayoutZBD = new BoxLayout(ZoneBoutonDroite, BoxLayout.X_AXIS);
			ZoneBoutonDroite.setLayout(boxLayoutZBD);
				final JButton play = new JButton("Pause"); 
				ZoneBoutonDroite.add( play, BorderLayout.EAST);
				JButton delete = new JButton("Delete"); 
				ZoneBoutonDroite.add( delete, BorderLayout.EAST);
			itemTelechargement.add(ZoneBoutonDroite, BorderLayout.EAST);
			zoneBarres.add(itemTelechargement);
		this.revalidate();

		try {
			final Downloader downloader = new Downloader(url);
			
			//add listener des boutons
			play.addActionListener(new ActionListener() {
				public void actionPerformed(ActionEvent e) {
					if( downloader.getEtat() ){
						downloader.Pause();
						play.setText("Play");
					}
					else{
						downloader.Play();
						play.setText("Pause");
					}
				}
			});
			
			delete.addActionListener( new ActionListener() {
				public void actionPerformed(ActionEvent e) {
					downloader.cancel(true);
					zoneBarres.remove(itemTelechargement);
					revalidate();
				}
			});

			System.out.format("Downloading %s:", downloader);

			//ajouter listener au downlader
			downloader.addPropertyChangeListener(new  PropertyChangeListener() {
				public void propertyChange(PropertyChangeEvent evt) {
					System.out.print(".");
					System.out.flush();
					b.setValue( downloader.getProgress() );
				}
			});
			downloader.execute();
			System.out.format("Download complete");
		}
		catch( Exception e ) {
			System.err.println("Download failed!");
		}
	}
	
	public static void main(final String[] argv) {
		Main yolo = new Main("Downlader - TP4 TLI"); 
		for(String url: argv) {
			yolo.ajouterDownload(url);
		}
	}
	
}
 
