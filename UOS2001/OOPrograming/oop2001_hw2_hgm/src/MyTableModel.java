import javax.swing.event.TableModelListener;
import javax.swing.table.TableModel;

public class MyTableModel implements TableModel{
	private String[] columnName;
	private Object[][] data;
	
	public MyTableModel(Class cl) {
		int columnnum = 3;
		
		columnName = new String[columnnum];
		columnName[0] = "Name";
		columnName[1] = "Type";
		columnName[2] = "Access";
		
		int membernum = cl.size();
		data = new Object[membernum][columnnum];
		
		for (int i = 0; i < membernum; i++) {
			data[i][0] = cl.getMember(i).getName();
			data[i][1] = cl.getMember(i).getType();
			data[i][2] = cl.getMember(i).getAccess();
		}
	}
	
	public MyTableModel(Field field) {
		int columnnum = 2;
		
		columnName = new String[columnnum];
		columnName[0] = "Name";
		columnName[1] = "Methods";
		
		int rownum = 1;
		data = new Object[rownum][columnnum];

		for (int i = 0; i < rownum; i++) {
			data[i][0] = field.getName();
			data[i][1] = field.getMethods();
		}
	}

	@Override
	public int getRowCount() {
		return data.length;
	}

	@Override
	public int getColumnCount() {
		return columnName.length;
	}

	@Override
	public String getColumnName(int columnIndex) {
		return columnName[columnIndex];
	}

	@Override
	public java.lang.Class<?> getColumnClass(int columnIndex) {
		Object value = getValueAt(0, columnIndex);
		return getValueAt(0, columnIndex).getClass();
	}

	@Override
	public boolean isCellEditable(int rowIndex, int columnIndex) {
		return false;
	}

	@Override
	public Object getValueAt(int rowIndex, int columnIndex) {
		return data[rowIndex][columnIndex];
	}

	@Override
	public void setValueAt(Object aValue, int rowIndex, int columnIndex) {
		data[rowIndex][columnIndex] = aValue;
	}

	@Override
	public void addTableModelListener(TableModelListener l) {
	}

	@Override
	public void removeTableModelListener(TableModelListener l) {
	}

}
