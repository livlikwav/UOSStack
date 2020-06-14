import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;
import java.io.FileInputStream;
import java.io.FileNotFoundException;
import java.io.IOException;
import java.util.StringTokenizer;

import javax.swing.JFileChooser;
import javax.swing.JOptionPane;
import javax.swing.event.TreeSelectionEvent;
import javax.swing.event.TreeSelectionListener;

public class MyParserController {//Controller
	MyParserView view;
	MyTreeModel model;

	protected Keyword keyword = new Keyword();
	
	public MyParserController(MyParserView view, MyTreeModel model) {
		this.view = view;
		this.model = model;
		
		view.menubar.open.addActionListener(new MyButtonListener(this, view));
		view.menubar.exit.addActionListener(new MyButtonListener(this, view));
	}
	
	public void parsingJava(FileInputStream file) {
		//GET FILE STREAM
		int b = 0;
		StringBuffer buffer = new StringBuffer();
		try {
			b = file.read();
			while(b != -1) {
				buffer.append((char)b);
				b = file.read();
			}
			//System.out.println(buffer);
		}catch(IOException e){
			System.out.println("Input Error");
		}
		
		//Parsing Java Code
		Class cl = new Class();
		Member mb = new Member();
		boolean firstToken = true;
		
		StringTokenizer outerSt = new StringTokenizer(buffer.toString(), "{|}");
		while(outerSt.hasMoreTokens()) {
			StringTokenizer innerSt = new StringTokenizer(outerSt.nextToken());
			while(innerSt.hasMoreTokens()) {
				String str = innerSt.nextToken();
				
				if(keyword.contains(str)) {
					if(str.equals("class")) {
						cl = new Class();
						cl.setName(innerSt.nextToken());
						continue;
					}
					if(firstToken) {
						firstToken = false;
						mb = new Member();
						mb.set(keyword.getVal(str), str);
					}else {
						mb.set(keyword.getVal(str), str);
					}
				}else {//not keyword
					if(str.contains("(")) {//method
						Method method = mb.toMethod();
						while(innerSt.hasMoreTokens()) {
							str = str + " " + innerSt.nextToken();
						}
						method.set("name", str);
						method.set("body", outerSt.nextToken());
						cl.setMember(method);
						firstToken = true;
					}else {//field
						Field field = mb.toField();
						field.set("name", str.substring(0, str.length() - 1));//delete ; in field name
						cl.setMember(field);
						firstToken = true;
					}
				}
			}
		}
		//Update metadata of field
		cl.updateMetadata();
		//DEBUG
		cl.printMems();
		//UpdateModel
		updateModel(cl);
		//UpdateView
		updateView(model);
	}
	public void updateModel(Class cl) {
		model = new MyTreeModel(cl);
	}
	
	public void updateView(MyTreeModel model) {
		view.update(model);
		view.splitpane.tree.addTreeSelectionListener(new MyTreeSelectionListener(view));
	}
}

class MyButtonListener implements ActionListener{
	private MyParserController controller;
	private MyParserView view;
	
	public MyButtonListener(MyParserController controller, MyParserView view) {
		this.controller = controller;
		this.view = view;
	}
	@Override
	public void actionPerformed(ActionEvent e) {
		String cmd = e.getActionCommand();
		switch(cmd) {
		case "Open":
			FileInputStream file;
			
			JFileChooser chooser = new JFileChooser();
			int r = chooser.showOpenDialog(view);
			if(r == JFileChooser.APPROVE_OPTION) {
				String name = chooser.getSelectedFile().getAbsolutePath();
				try {
					file = new FileInputStream(name);
					controller.parsingJava(file);
				} catch (FileNotFoundException e1) {
					e1.printStackTrace();
				}
			}
			break;
		case "Exit":
			int dialogButton = JOptionPane.showConfirmDialog(null, "종료하시겠습니까?", "프로그램 종료", JOptionPane.YES_NO_OPTION);
			
			if(dialogButton == JOptionPane.YES_OPTION) {
				System.exit(0);
			}else if((dialogButton == JOptionPane.NO_OPTION)||(dialogButton == JOptionPane.CLOSED_OPTION)) {
				return;
			}
			break;
		}
	}
}

class MyTreeSelectionListener implements TreeSelectionListener{
	private MyParserView view;
	
	public MyTreeSelectionListener(MyParserView view) {
		this.view = view;
	}

	@Override
	public void valueChanged(TreeSelectionEvent e) {
		Object o = e.getPath().getLastPathComponent();
		
		view.mycard.layout.show(view.mycard, o.toString());
		
		if(o instanceof Method) {
			view.splitpane.display.setText(((Method) o).getFields());
		}else {
			view.splitpane.display.setText("");
		}
		
	}
	
}