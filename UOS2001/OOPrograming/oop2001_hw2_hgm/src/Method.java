import java.util.ArrayList;
import java.util.HashSet;
import java.util.Iterator;
import java.util.Scanner;
import java.util.StringTokenizer;

public class Method extends Member{
	String body;
	HashSet<String> fields = new HashSet<String>();
	ArrayList<String> params = new ArrayList<String>();
	
	public Method(Member member) {
		this.name = member.name;
		this.access = member.access;
		this.type = member.type;
	}
	
	@Override
	public void set(String keywordType, String val) {
		super.set(keywordType, val);
		if(keywordType.equals("body")) {
			//update body
			StringBuilder sb = new StringBuilder();
			Scanner sc = new Scanner(val);

			//check indentation
			boolean first = true;
			int startidx = 0;
			
			sc.nextLine(); //delete one \n
			while(sc.hasNext()) {
				String line = sc.nextLine();
				if(first) {
					for (int i = 0; i < line.length(); i++) {
						if(!Character.isWhitespace(line.charAt(i))) {
							startidx = i;
							first = false;
							break;
						}
					}
				}
				//delete front indentation
				sb.append(line.substring(startidx));
				sb.append("\n");
			}
			//save body string
			this.body = sb.toString();
			sc.close();
		}
		//update name
		if(keywordType.equals("name")) {
			StringTokenizer st = new StringTokenizer(name, "(|)|,| ");
			StringBuilder sb = new StringBuilder();
			
			sb.append(st.nextToken()); //ex : MyStack
			sb.append("()");
			name = sb.toString();
			
			//update params
			int tokennum;
			while((tokennum = st.countTokens()) > 0) {
				String paramtype = st.nextToken();
				params.add(paramtype); //param type
				st.nextToken(); //param name
			}
		}
	}
	
	@Override
	public void printInfo() {
		super.printInfo();
		System.out.println("body :\n" + body);
		System.out.println("fields : " + fields.toString());
	}
	
	public String getBody() {
		return body;
	}
	
	public void parsingBody(Class cl) {
		StringTokenizer st = new StringTokenizer(body, "(|)|{|}|;|+|-|=|[|]| ");
		while(st.hasMoreTokens()) {
			String s = st.nextToken().trim();
			
			//DEBUG
//			System.out.println(s + "/");
			
			if(cl.checkField(s)) {
				//add Method's field metadata
				fields.add(s);
				
				//add that Field's method metadata
				cl.getField(s).setMethods(this);
			}
		}
	}
	
	@Override
	public String toString() {
		// ex : MyStack(int)
		StringBuilder sb = new StringBuilder(name.substring(0, name.length()-2));
		sb.append("(");
		for (int i = 0; i < params.size(); i++) {
			sb.append(params.get(i));
			if(i == params.size() - 1) {
				continue;
			}
			sb.append(", ");
		}
		sb.append(")");
		return sb.toString();
	}
	
	public String getFields() {
		StringBuilder sb = new StringBuilder();
		Iterator<String> iter = fields.iterator();
		while(iter.hasNext()){
			sb.append(iter.next());
			sb.append("\n");
		}
		return sb.toString();
	}
}
