import java.util.ArrayList;
import java.util.HashSet;
import java.util.StringTokenizer;

public class Field extends Member {
	HashSet<Method> methods = new HashSet<Method>();
	
	public Field(Member member) {
		this.name = member.name;
		this.access = member.access;
		this.type = member.type;
	}
	
	@Override
	public void set(String keywordType, String val) {
		super.set(keywordType, val);
	}
	
	@Override
	public String toString() {
		StringBuilder sb = new StringBuilder();
		sb.append(name);
		//if field type is array
		if(type.contains("[") && type.contains("]")) {
			sb.append("[]");
		}
		sb.append(" : ");
		//if field type is array
		if(type.contains("[") && type.contains("]")) {
			sb.append(type.substring(0, type.length()-2));
		}else {
			sb.append(type);
		}
		
		return sb.toString();
	}
	
	public void setMethods(Method method) {
		methods.add(method);
	}
	
	@Override
	public void printInfo() {
		super.printInfo();
		System.out.println("methods : " + methods.toString());
	}
}
