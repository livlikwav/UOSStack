import javax.swing.JScrollPane;
import javax.swing.JSplitPane;
import javax.swing.JTextArea;
import javax.swing.JTree;
import javax.swing.event.TreeSelectionEvent;
import javax.swing.event.TreeSelectionListener;

public class MySplitPane extends JSplitPane{
	public JTree tree;
	public JTextArea display;
	
	public MySplitPane(MyTreeModel treemodel) {
		super(VERTICAL_SPLIT);
		
		tree = new JTree(treemodel);
//		tree.addTreeSelectionListener(new TreeSelectionListener() {
//			public void valueChanged(TreeSelectionEvent e) {
//				Object o = e.getPath().getLastPathComponent();
//				if(o instanceof Class) {
//					//TODO
//				}else if(o instanceof Method) {
//					//TODO
//				}else if(o instanceof Field) {
//					//TODO
//				}
//			}
//		});
		
		display = new JTextArea(5, 20);
		add(new JScrollPane(tree));
		add(new JScrollPane(display));
	}
}
