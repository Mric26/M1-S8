package grapher.ui;

import javax.swing.JFrame;
import javax.swing.JSplitPane;
import javax.swing.SwingUtilities;


public class Main extends JFrame {
	Main(String title, String[] expressions) {
		super(title);
		setDefaultCloseOperation(EXIT_ON_CLOSE);
		
		Grapher grapher = new Grapher();		
		for(String expression : expressions) {
			grapher.add(expression);
		}
		
		Grapher grapher2 = new Grapher();		
		for(String expression : expressions) {
			grapher2.add(expression);
		}
		
		JSplitPane jp = new JSplitPane(JSplitPane.HORIZONTAL_SPLIT);
		jp.setOneTouchExpandable(true);
		jp.setDividerLocation(400);

		jp.add(grapher);
		jp.add(grapher2);
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
