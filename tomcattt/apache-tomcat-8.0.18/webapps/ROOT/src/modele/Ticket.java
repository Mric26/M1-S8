package modele;

public class Ticket {
	private String nom;
	private String date;
	private int numS;
	private int Zone;
	private int NbPlaces;
	
	public Ticket (String n, String d, int id, int z, int p) {
		this.setNom(n);
		this.setDate(d);
		this.setNumS(id);
		this.setZone(z);
		this.setNbPlaces(p);
	}

	public String getNom() {
		return nom;
	}

	public void setNom(String nom) {
		this.nom = nom;
	}

	public String getDate() {
		return date;
	}

	public void setDate(String date) {
		this.date = date;
	}

	public int getNumS() {
		return numS;
	}

	public void setNumS(int numS) {
		this.numS = numS;
	}

	public int getZone() {
		return Zone;
	}

	public void setZone(int zone) {
		Zone = zone;
	}

	public int getNbPlaces() {
		return NbPlaces;
	}

	public void setNbPlaces(int nbPlaces) {
		NbPlaces = nbPlaces;
	}
	
}
