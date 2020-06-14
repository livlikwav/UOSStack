import java.awt.CardLayout;
import java.awt.Dimension;
import java.awt.Font;

import javax.swing.JPanel;
import javax.swing.JScrollPane;
import javax.swing.JTable;
import javax.swing.JTextArea;

public class MyCard extends JPanel{
	CardLayout layout;
	
	public MyCard(MyTreeModel model) {
		layout = new CardLayout();
		setLayout(layout);
		
		Class cl = (Class)model.getRoot();
		
		//make class card layout
		add(new JScrollPane(new JTable(new MyTableModel(cl))), cl.toString());
		
		//member
		int membernum = cl.size();
		for (int i = 0; i < membernum; i++) {
			Member mem = cl.getMember(i);
			if(mem instanceof Field) {
				add(new JScrollPane(new JTable(new MyTableModel((Field)mem))), mem.toString());
			}else if(mem instanceof Method) {
				JTextArea textarea = new JTextArea(((Method) mem).getBody());
				textarea.setFont(new Font("Verdana", Font.PLAIN, 15));
				add(textarea, mem.toString());
			}
		}
		
	}
}
