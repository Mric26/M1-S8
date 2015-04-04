package modele;

public class Categorie {

	private String categorie;
	private double prix;
	private int id;
	
	public Categorie (int id, String c, double p) {
		this.categorie = c;
		this.prix = p;
		this.id = id;
	}

	public String getCategorie () {
		return this.categorie;
	}
	
	public double getPrix () {
		return this.prix;
	}
	
	public int getId () {
		return id;
	}
	
	public void setCategorie (String c) {
		this.categorie = c;
	}
	
	public void setPrix (double p) {
		this.prix = p;
	}
	
	public void setId (int id) {
		this.id = id;
	}
}
