package modele;

import java.util.Date;

public class Ticket {
	private int noSerie; 
	private int numS;
	private int numZ;
	private String dateRep; 
	private int noPlace; 
	private int noRang;
//	private int noDossier; 
	
	public Ticket (int ns, int n, String dr, int np, int nr, int nz) {
		this.setNoSerie(ns);
		this.setNumS(n);
		this.setDateRep(dr);
		this.setNoPlace(np);
		this.setNoRang(nr);
//		this.setDateEmission(de);
		this.setNumZ(nz);
//		this.setNoDossier(nd);
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

	public String getDateRep() {
		return dateRep;
	}

	public void setDateRep(String dateRep) {
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

//	public Date getDateEmission() {
//		return dateEmission;
//	}
//
//	public void setDateEmission(Date dateEmission) {
//		this.dateEmission = dateEmission;
//	}

	public int getNumZ() {
		return numZ;
	}

	public void setNumZ(int numZ) {
		this.numZ = numZ;
	}

//	public int getNoDossier() {
//		return noDossier;
//	}
//
//	public void setNoDossier(int noDossier) {
//		this.noDossier = noDossier;
//	}
	
}
