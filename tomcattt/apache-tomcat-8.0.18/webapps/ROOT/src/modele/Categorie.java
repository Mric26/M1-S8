package modele;

public class Categorie {

	private String categorie;
	private double prix;
	
	public Categorie (String c, double p) {
		this.categorie = c;
		this.prix = p;
	}

	public String getCategorie () {
		return this.categorie;
	}
	
	public double getPrix () {
		return this.prix;
	}
	
	public void setCategorie (String c) {
		this.categorie = c;
	}
	
	public void setPrix (double p) {
		this.prix = p;
	}
}
