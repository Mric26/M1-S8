package modele;

public class Users {
	private String name;
	private String pswd;
	private String role;
	
	public Users(String n,String p,String r){
		name= n;
		pswd= p;
		role= r;
	}
	
	public String getName() {
		return name;
	}
	public void setName(String name) {
		this.name = name;
	}
	public String getPswd() {
		return pswd;
	}
	public void setPswd(String pswd) {
		this.pswd = pswd;
	}
	public String getRole() {
		return role;
	}
	public void setRole(String role) {
		this.role = role;
	}
	

}
