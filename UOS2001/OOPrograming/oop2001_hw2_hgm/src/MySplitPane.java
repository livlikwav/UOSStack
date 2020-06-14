import java.awt.Font;

import javax.swing.BorderFactory;
import javax.swing.JScrollPane;
import javax.swing.JSplitPane;
import javax.swing.JTextArea;
import javax.swing.JTree;

public class MySplitPane extends JSplitPane{
	public JTree tree;
	public JTextArea display;
	
	public MySplitPane(MyTreeModel treemodel) {
		super(VERTICAL_SPLIT);
		
		tree = new JTree(treemodel);
		tree.setFont(new Font("Verdana", Font.PLAIN, 20));
		
		display = new JTextArea(5, 20);
		display.setFont(new Font("Verdana", Font.PLAIN, 20));
		display.setBorder(BorderFactory.createTitledBorder("Use"));
		
		add(new JScrollPane(tree));
		add(new JScrollPane(display));
	}
}
