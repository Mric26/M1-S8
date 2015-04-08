package modele;

import java.util.Vector;

public class Caddie {

	private int noCaddie;
	private double montant;
	private Vector<Ticket> representations = new Vector<Ticket>();
	
	public Caddie(){
		setNoCaddie((int) (Math.random()*9999));
		setRepresentations(new Vector<Ticket>());
		setMontant(0);
	}

	public int getNoCaddie() {
		return noCaddie;
	}

	public void setNoCaddie(int noCaddie) {
		this.noCaddie = noCaddie;
	}

	public double getMontant() {
		return montant;
	}

	public void setMontant(double montant) {
		this.montant = montant;
	}

	public Vector<Ticket> getRepresentations() {
		return representations;
	}

	public void setRepresentations(Vector<Ticket> representations) {
		this.representations = representations;
	}
	
	public boolean ajouterTicket( Ticket t ){
		representations.add(t);
		montant += 5;
		return true;
	}
	
	public boolean retirerTicket( Ticket t ){
		representations.remove(t);
		montant -= 5;
		return true;
	}
	
}
