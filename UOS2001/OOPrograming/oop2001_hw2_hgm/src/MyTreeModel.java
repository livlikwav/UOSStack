import javax.swing.event.TreeModelListener;
import javax.swing.tree.TreeModel;
import javax.swing.tree.TreePath;

public class MyTreeModel implements TreeModel{
	protected Class c;
	
	public MyTreeModel(Class c) {
		this.c = c;
	}
	
	@Override
	public Object getRoot() {
		return c;
	}

	@Override
	public Object getChild(Object parent, int index) {
		if(parent instanceof Class) {
			Class p = (Class) parent;
			return p.getMember(index);
		}else {//Member : Method or Field
			return null;
		}
	}

	@Override
	public int getChildCount(Object parent) {
		if(parent instanceof Class) {
			return ((Class)parent).size();
		}else {//Member : Method or Field
			return 0;
		}
	}

	@Override
	public boolean isLeaf(Object node) {
		if(node instanceof Class) {
			return false;
		}else {//Member : Method or Field
			return true;
		}
	}
	
	@Override
	public int getIndexOfChild(Object parent, Object child) {
		if(parent instanceof Class) {
			Class p = (Class) parent;
			if(child instanceof Method) {
				return p.getIndexOf((Method)child);
			}else{//child instanceof Field
				return p.getIndexOf((Field)child);
			}
		}else {//Member : Method or Field
			return -1;
		}
	}

	@Override
	public void valueForPathChanged(TreePath path, Object newValue) {
	}
	@Override
	public void addTreeModelListener(TreeModelListener l) {
	}
	@Override
	public void removeTreeModelListener(TreeModelListener l) {
	}
}
