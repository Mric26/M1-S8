package grapher.ui;

import javax.swing.JTable;

public class JTablePerso extends JTable {
	
	public JTablePerso(Object[][] rowData, Object[] columnNames){ 
		super(rowData, columnNames);
	}
	
	public boolean isCellEditable(int row, int column){  
        return false;  
    }

}
