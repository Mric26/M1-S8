package modele;

public class Representation {
	private String nom;
	private String date;
	private int numS;
	
	public Representation (String n, String d, int id) {
		this.nom = n;
		this.date = d;
		this.setNumS(id);
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

	public int getNumS() {
		return numS;
	}

	public void setNumS(int numS) {
		this.numS = numS;
	}
}
