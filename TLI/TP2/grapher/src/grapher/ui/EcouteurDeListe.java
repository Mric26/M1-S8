package grapher.ui;

import grapher.fc.Function;

import javax.swing.JList;
import javax.swing.event.ListSelectionEvent;
import javax.swing.event.ListSelectionListener;

public class EcouteurDeListe implements ListSelectionListener {
	
	public JList<Function> list;
	public Grapher grapher;
	
	public EcouteurDeListe( JList<Function> l, Grapher g ){
		list = l;
		grapher = g;
	}
	
	public void valueChanged(ListSelectionEvent e) {
		if (e.getValueIsAdjusting() == false) {
			//Selection
	        if (list.getSelectedIndex() != -1) {
	        	int[] tab = list.getSelectedIndices();
	        	grapher.tabSelected = new int[ tab.length ];
	        	for (int i = 0; i < tab.length; i++) {
	        		grapher.tabSelected[i] = tab[i];
				}
	        	grapher.repaint();
	        }
	    }
	}

}