package grapher.ui;

import java.awt.Color;

import javax.swing.JTable;
import javax.swing.event.TableModelEvent;
import javax.swing.event.TableModelListener;

public class EcouteurDeJtable implements TableModelListener {
	
	public JTable table;
	public Grapher grapher;
	
	public EcouteurDeJtable( JTable t, Grapher g ){
		table = t;
		grapher = g;
	}

	public void tableChanged(TableModelEvent e) {
        int[] selectedRow = table.getSelectedRows();
        int[] selectedColumns = table.getSelectedColumns();

        if( (selectedRow.length == 1) && (selectedColumns[0] == 1) ){
        	//changement de couleur
        	int nbElem = table.getRowCount();
        	grapher.tabColor = new Color[nbElem];
        	for (int i = 0; i < nbElem; i++) {
				grapher.tabColor[i] = (Color) table.getValueAt(i, 1);
			}
        }
        else {
        	//mise en gras
        	for (int i = 0; i < selectedRow.length; i++) {
                for (int j = 0; j < selectedColumns.length; j++) {
                	grapher.tabSelected = new int[ selectedRow.length ];
    	        	for (int k = 0; k < selectedRow.length; k++) {
    	        		grapher.tabSelected[k] = selectedRow[k];
    				}
                }
        	}
        }
        grapher.repaint();
	}
	
}
