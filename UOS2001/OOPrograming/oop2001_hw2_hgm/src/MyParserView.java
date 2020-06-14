import java.awt.GridLayout;

import javax.swing.JFrame;
import javax.swing.JMenuBar;
import javax.swing.JPanel;
import javax.swing.JScrollPane;
import javax.swing.JSplitPane;
import javax.swing.JTextArea;
import javax.swing.JTree;
import javax.swing.event.TreeSelectionEvent;
import javax.swing.event.TreeSelectionListener;

public class MyParserView extends JFrame{
	static final int WIDTH = 1024;
	static final int HEIGHT = 768;
	public MyMenuBar menubar;
	public MySplitPane splitpane;
	public MyCard mycard;
	
	public MyParserView() {
		setTitle("Class Viewer");
		setSize(WIDTH, HEIGHT);
		//set menubar
		menubar = new MyMenuBar();
		setJMenuBar(menubar);
		//set GridLayout(1, 2);
		setLayout(new GridLayout(1, 2));
		
		setVisible(true);
	}
	
	public void update(MyTreeModel model) {
		splitpane = new MySplitPane(model);
		add(splitpane);

		//make card layout of each tree node
		mycard = new MyCard(model);
		add(mycard);
		
		//refresh JFrame
		revalidate();
		
	}
	
}



