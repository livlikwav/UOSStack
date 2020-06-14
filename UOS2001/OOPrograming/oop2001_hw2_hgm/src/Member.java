
public class Member{
	protected String name;
	protected String access;
	protected String type;
	
	public void set(String keywordType, String val) {
		if(keywordType.equals("type")) {
			this.type = val;
		}else if(keywordType.equals("name")) {
			this.name = val;
		}else if(keywordType.equals("access")) {
			this.access = val;
		}
	}

	@Override
	public String toString() {
		return name;
	}
	
	public void printInfo() {
		System.out.println("====================");
		System.out.println("name : " + name);
		System.out.println("access : " + access);
		System.out.println("type : " + type);
	}
	
	public Field toField() {
		return (new Field(this));
	}
	
	public Method toMethod() {
		return (new Method(this));
	}
	
	public String getName() {
		return name;
	}
	
	public String getAccess() {
		return access;
	}
	
	public String getType() {
		return type;
	}
}
