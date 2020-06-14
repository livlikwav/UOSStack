import javax.swing.JMenu;
import javax.swing.JMenuBar;
import javax.swing.JMenuItem;

public class MyMenuBar extends JMenuBar{
	public JMenu menu;
	public JMenuItem open;
	public JMenuItem exit;
	
	public MyMenuBar() {
		menu = new JMenu("File");
		open = new JMenuItem("Open");
		exit = new JMenuItem("Exit");
		
		menu.add(open);
		menu.add(exit);
		add(menu);
	}
}