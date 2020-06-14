
public class MyParser {

	public static void main(String[] args) {
		MyParserView view = new MyParserView();
		MyTreeModel model = new MyTreeModel(new Class());
		MyParserController controller = new MyParserController(view, model);
	}
}
