package grapher.ui;

import grapher.fc.Function;
import grapher.fc.FunctionFactory;

import java.util.Vector;

import javax.swing.DefaultListModel;
import javax.swing.JFrame;
import javax.swing.JList;
import javax.swing.JSplitPane;
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
	    JList<Function> list = new JList<Function>(functions);
	    EcouteurDeListe ecdl = new EcouteurDeListe();
	    list.addListSelectionListener(ecdl);
	    
	    //split
	    JSplitPane jp = new JSplitPane(JSplitPane.HORIZONTAL_SPLIT);
		jp.setOneTouchExpandable(true);
		jp.setDividerLocation(100);
	    
		//Ajouts
		jp.add(list);
		jp.add(grapher);
		add(jp);
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
