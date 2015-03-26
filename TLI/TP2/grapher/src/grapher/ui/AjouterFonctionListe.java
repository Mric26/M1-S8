package grapher.ui;

import grapher.fc.Function;
import grapher.fc.FunctionFactory;

import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;

import javax.swing.DefaultListModel;
import javax.swing.JDialog;
import javax.swing.JList;
import javax.swing.JOptionPane;

public class AjouterFonctionListe implements ActionListener {
	DefaultListModel<Function> functions;
	Grapher grapher;

	public AjouterFonctionListe(DefaultListModel<Function> f, Grapher g) {
		functions = f;
		grapher = g;
	}

	public void actionPerformed(ActionEvent e) {
		JOptionPane j = new JOptionPane();
		String nom = j.showInputDialog("Entrez le nom de la Fonction :");
		functions.add(functions.size(), FunctionFactory.createFunction(nom));
		grapher.repaint();
	}

}
