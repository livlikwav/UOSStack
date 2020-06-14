import java.awt.CardLayout;

import javax.swing.JButton;
import javax.swing.JPanel;

public class MyCard extends JPanel{
	CardLayout layout;
	
	public MyCard(MyTreeModel model) {
		layout = new CardLayout();
		setLayout(layout);
		
		Class cl = (Class)model.getRoot();
		
//		for (int i = 0; i < 10; i++) {
//			add(new JButton("현재 카드의 번호는" + i + "입니다"), "Center");
//		}
	}
}
