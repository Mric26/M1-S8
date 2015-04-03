package modele;

public class Representation {
	private String nom;
	private String date;
	
	public Representation (String n, String d) {
		this.nom = n;
		this.date = d;
	}

	public String getNom () {
		return this.nom;
	}
	
	public String getDate () {
		return this.date;
	}
	
	public void setNom (String c) {
		this.nom = c;
	}
	
	public void setDate (String d) {
		this.date = d;
	}
}
