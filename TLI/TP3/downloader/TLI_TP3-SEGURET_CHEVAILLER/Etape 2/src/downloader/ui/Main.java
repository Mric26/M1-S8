package downloader.ui;

import java.awt.BorderLayout;
import java.awt.Dimension;

import javax.swing.JButton;
import javax.swing.JFrame;
import javax.swing.JPanel;
import javax.swing.JProgressBar;
import javax.swing.JTextField;

import downloader.fc.Downloader;

public class Main extends JFrame {
	
	public static void main(String argv[]) {
		
		//fenetre principale
		JFrame fenetre = new JFrame("Downloader");
		fenetre.setDefaultCloseOperation(EXIT_ON_CLOSE);
		fenetre.setMinimumSize(new Dimension(800, 400));
		fenetre.setLayout( new BorderLayout() );

		//zone des barres
		JPanel zoneBarres = new JPanel();
		zoneBarres.setLayout( new StackLayout() );

		int i = 0;
		for(String url: argv) {
			final JProgressBar b = new JProgressBar();
			b.setStringPainted(true);
			zoneBarres.add(b);
			
			String name = "Téléchargement" + i;
			Telechargement t = new Telechargement(name, url, b);
			t.start();
			i++;
		}
		
		//zone add (en bas)
		JPanel ajouterTelechargement = new JPanel();
		ajouterTelechargement.setLayout( new BorderLayout() );
		JTextField recherche = new JTextField("");
		ajouterTelechargement.add(recherche, BorderLayout.CENTER);
		ajouterTelechargement.add( new JButton("ADD"), BorderLayout.EAST);
		
		//ajout élément + visible
		fenetre.add(zoneBarres, BorderLayout.CENTER);
		fenetre.add(ajouterTelechargement, BorderLayout.SOUTH);
		fenetre.setVisible(true);
	}
	
}
 
