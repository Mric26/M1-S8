package modele;

import java.util.Date;

public class Ticket {
	private int noSerie; 
	private int numS;  
	private Date dateRep; 
	private int noPlace; 
	private int noRang;
	private Date dateEmission; 
	private int noDossier; 
	
	public Ticket (int ns, int n, Date dr, int np, int nr, Date de, int nd) {
		this.setNoSerie(ns);
		this.setNumS(numS);
		this.setDateRep(dr);
		this.setNoPlace(np);
		this.setNoRang(nr);
		this.setDateEmission(de);
		this.setNoDossier(nd);
	}

	public int getNumS() {
		return numS;
	}

	public void setNumS(int numS) {
		this.numS = numS;
	}

	public int getNoSerie() {
		return noSerie;
	}

	public void setNoSerie(int noSerie) {
		this.noSerie = noSerie;
	}

	public Date getDateRep() {
		return dateRep;
	}

	public void setDateRep(Date dateRep) {
		this.dateRep = dateRep;
	}

	public int getNoRang() {
		return noRang;
	}

	public void setNoRang(int noRang) {
		this.noRang = noRang;
	}

	public int getNoPlace() {
		return noPlace;
	}

	public void setNoPlace(int noPlace) {
		this.noPlace = noPlace;
	}

	public Date getDateEmission() {
		return dateEmission;
	}

	public void setDateEmission(Date dateEmission) {
		this.dateEmission = dateEmission;
	}

	public int getNoDossier() {
		return noDossier;
	}

	public void setNoDossier(int noDossier) {
		this.noDossier = noDossier;
	}
	
}
