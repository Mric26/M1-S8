package grapher.ui;

import grapher.fc.Function;
import grapher.fc.FunctionFactory;

import java.awt.BorderLayout;
import java.awt.Color;
import java.awt.MenuBar;
import java.awt.event.KeyEvent;

import javax.swing.DefaultListModel;
import javax.swing.JButton;
import javax.swing.JColorChooser;
import javax.swing.JFrame;
import javax.swing.JList;
import javax.swing.JMenu;
import javax.swing.JMenuBar;
import javax.swing.JMenuItem;
import javax.swing.JPanel;
import javax.swing.JSplitPane;
import javax.swing.JTable;
import javax.swing.JToolBar;
import javax.swing.SwingUtilities;


@SuppressWarnings("serial")
public class Main extends JFrame {
	private DefaultListModel<Function> functions;

	Main(String title, String[] expressions) {
		super(title);
		setDefaultCloseOperation(EXIT_ON_CLOSE);
		
		//liste des fonctions
		functions = new DefaultListModel<Function>();
		for(String expression : expressions) {
			functions.add(functions.size(), FunctionFactory.createFunction(expression) );
		}
		
		//grapher
		Grapher grapher = new Grapher( functions );		
		
		//liste
	    JList<Function> list = new JList<Function>( functions );
	    EcouteurDeListe ecdl = new EcouteurDeListe( list, grapher );
	    list.addListSelectionListener(ecdl);
	    
	    //table
//	    Function[][] donnees = new Function[1][functions.size()];
//	    for (int i = 0; i < functions.size(); i++) {
//			donnees[i][0] = functions.elementAt(i);
//		}
//	    JColorChooser[][] couleur = new JColorChooser[1][functions.size()];
//	    for (int i = 0; i < functions.size(); i++) {
//	    	couleur[i][0] = new JColorChooser();
//		}
//        String[] entetes = {"Fonctions", "Couleur"};
//        JTable tableau = new JTable(donnees, couleur);
	    
	    //toolbar ajout/supp
	    JButton b1 = new JButton("+");
	    b1.addActionListener( new AjouterFonctionListe(functions, grapher) );
	    JButton b2 = new JButton("-");
	    b2.addActionListener( new SupprimerFonctionListe(functions, list, grapher) );
	    JToolBar barre = new JToolBar();
	    barre.add( b1 );
	    barre.add( b2 );
	    barre.setFloatable(false);
	    
	    //panel
	    JPanel panel = new JPanel();
	    panel.setLayout( new BorderLayout() );
	    panel.add( list );
	    panel.add( barre, BorderLayout.SOUTH );
	    
	    //split
	    JSplitPane jp = new JSplitPane(JSplitPane.HORIZONTAL_SPLIT);
		jp.setOneTouchExpandable(true);
		jp.setDividerLocation(100);
		
		//barre de menu
		JMenuBar menuBar = new JMenuBar();
		JMenu menu = new JMenu("Expression");
		menuBar.add(menu);
		JMenuItem menuItemAdd = new JMenuItem("Add");
		menuItemAdd.addActionListener( new AjouterFonctionListe(functions, grapher) );
		JMenuItem menuItemRemove = new JMenuItem("Remove");
		menuItemRemove.addActionListener( new SupprimerFonctionListe(functions, list, grapher) );
		menu.add(menuItemAdd);
		menu.add(menuItemRemove);
	    
		//Ajouts
		jp.add(panel);
		jp.add(grapher);
		add(jp);
		this.setJMenuBar(menuBar);
		pack();
	}

	public static void main(String[] argv) {
		final String[] expressions = argv;
		SwingUtilities.invokeLater(new Runnable() {
			public void run() { 
				new Main("grapher", expressions).setVisible(true); 
			}
		});
	}

}
