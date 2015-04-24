package grapher.ui;

import grapher.fc.Function;
import grapher.fc.FunctionFactory;

import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;

import javax.swing.DefaultListModel;
import javax.swing.JColorChooser;
import javax.swing.JList;
import javax.swing.JOptionPane;
import javax.swing.JTable;
import javax.swing.table.DefaultTableModel;

public class SupprimerFonctionListe implements ActionListener {
	DefaultListModel<Function> functions;
	JList<Function> list;
	Grapher grapher;
	JTable tableau;

	public SupprimerFonctionListe(DefaultListModel<Function> f, JList<Function> l, Grapher g, JTable t) {
		functions = f;
		list = l;
		grapher = g;
		tableau = t;
	}

	public void actionPerformed(ActionEvent e) {
		int[] selectedRow = tableau.getSelectedRows();
		
		for (int i = 0; i < selectedRow.length; i++) {
			functions.remove(i);
    		DefaultTableModel model = (DefaultTableModel) tableau.getModel();
    		model.removeRow(i);
		}
		grapher.repaint();
	}

}
