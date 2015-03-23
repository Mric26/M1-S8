package grapher.ui;

import grapher.fc.Function;
import grapher.fc.FunctionFactory;

import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;

import javax.swing.DefaultListModel;
import javax.swing.JList;
import javax.swing.JOptionPane;

public class SupprimerFonctionListe implements ActionListener {
	DefaultListModel<Function> functions;
	JList<Function> list;
	Grapher grapher;

	public SupprimerFonctionListe(DefaultListModel<Function> f, JList<Function> l, Grapher g) {
		functions = f;
		list = l;
		grapher = g;
	}

	public void actionPerformed(ActionEvent e) {
        if (list.getSelectedIndex() != -1) {
        	int[] tab = list.getSelectedIndices();
        	if( tab.length > 0 ){
        		for (int i = tab.length-1; i >= 0 ; i--) {
            		functions.remove(tab[i]);
    			}
            	grapher.repaint();
        	}
        }
	}

}
