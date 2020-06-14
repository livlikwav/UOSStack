import java.util.HashMap;

public class Keyword {
	private HashMap<String, String> keyword;
	
	public Keyword() {
		keyword = new HashMap<String, String>();
		keyword.put("private", "access");
		keyword.put("public", "access");
		keyword.put("int", "type");
		keyword.put("int[]", "type");
		keyword.put("boolean", "type");
		keyword.put("void", "type");
		keyword.put("class", "class");
	}
	
	public boolean contains(String key) {
		if(keyword.containsKey(key)) {
			return true;
		}else {
			return false;
		}
	}
	
	public String getVal(String key) {
		return keyword.get(key);
	}
}
