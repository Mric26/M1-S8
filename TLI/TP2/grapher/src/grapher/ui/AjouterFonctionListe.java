package grapher.ui;

import grapher.fc.Function;
import grapher.fc.FunctionFactory;

import java.awt.Color;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;

import javax.swing.DefaultListModel;
import javax.swing.JButton;
import javax.swing.JColorChooser;
import javax.swing.JDialog;
import javax.swing.JList;
import javax.swing.JOptionPane;
import javax.swing.JTable;
import javax.swing.table.DefaultTableModel;

public class AjouterFonctionListe implements ActionListener {
	DefaultListModel<Function> functions;
	Grapher grapher;
	JTable tableau;

	public AjouterFonctionListe(DefaultListModel<Function> f, Grapher g, JTable t) {
		functions = f;
		grapher = g;
		tableau = t;
	}

	public void actionPerformed(ActionEvent e) {
		JOptionPane j = new JOptionPane();
		String nom = j.showInputDialog("Entrez le nom de la Fonction :");
		Function f = FunctionFactory.createFunction(nom);
		//ajout list
		functions.add(functions.size(), f);
		//ajout dans jtable
		DefaultTableModel model = (DefaultTableModel) tableau.getModel();
		JButton b = new JButton();
	    b.setBackground(Color.ORANGE);
		model.addRow(new Object[]{f, b});
		//repaint
		grapher.repaint();
	}

}
