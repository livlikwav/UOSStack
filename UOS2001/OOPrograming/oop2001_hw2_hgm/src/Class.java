import java.util.ArrayList;
import java.util.HashMap;
import java.util.HashSet;

public class Class{
	private String name;
	private ArrayList<Member> members = new ArrayList<Member>();
	private HashMap<String, Field> fields = new HashMap<String, Field>();
	
	public Member getMember(int index) {
		return members.get(index);
	}
	
	public Field getField(String fieldname) {
		return fields.get(fieldname);
	}
	
	public boolean checkField(String fieldname) {
		if(fields.containsKey(fieldname)) {
			return true;
		}else {
			return false;
		}
	}
	
	public int size() {
		return members.size();
	}
	
	public int getIndexOf(Member member) {
		for (int i = 0; i < members.size(); i++) {
			if(members.get(i).equals(member)) {
				return i;
			}
		}
		return -1;
	}

	public void setMember(Field field) {
		members.add(field);
		fields.put(field.getName(), field);
	}
	
	public void setMember(Method method) {
		members.add(method);
	}
	
	public void setName(String name) {
		this.name = name;
	}
	
	@Override
	public String toString() {
		return name;
	}
	
	//DEBUG
	public void printMems() {
		for (int i = 0; i < members.size(); i++) {
			members.get(i).printInfo();
		}
	}
	
	public void updateMetadata() {
		//sort members from method to field
		ArrayList<Member> sorted = new ArrayList<Member>();
		//Method First
		for (int i = 0; i < members.size(); i++) {
			Member mem = members.get(i);
			if(mem instanceof Method) {
				sorted.add(mem);
			}
		}
		//Field Next
		for (int i = 0; i < members.size(); i++) {
			Member mem = members.get(i);
			if(mem instanceof Field) {
				sorted.add(mem);
			}
		}
		//update members
		members = sorted;
		
		//update metadata of each member
		for (int i = 0; i < members.size(); i++) {
			Member mem = members.get(i);
			if(mem instanceof Method) {
				//DEBUG
				//System.out.println("Method : " + mem.toString());
				
				((Method)mem).parsingBody(this);
			}
		}
		
	}
}
