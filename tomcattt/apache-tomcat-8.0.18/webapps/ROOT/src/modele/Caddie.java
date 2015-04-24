package modele;

import java.io.IOException;
import java.sql.Connection;
import java.sql.PreparedStatement;
import java.sql.ResultSet;
import java.sql.SQLException;
import java.text.ParseException;
import java.text.SimpleDateFormat;
import java.util.Date;
import java.util.Vector;

import javax.servlet.ServletOutputStream;

import accesBD.BDCategories;
import accesBD.BDConnexion;
import exceptions.CategorieException;
import exceptions.ExceptionConnexion;

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
//		montant += 5;
		return true;
	}
	
	public boolean retirerTicket( Ticket t ){
		representations.remove(t);
//		montant -= 5;
		return true;
	}
	
	private void clean(){
		representations.clear();
		montant = 0;
		
	}
	
	public boolean confirmerCommande(Utilisateur user, ServletOutputStream out) throws CategorieException, ExceptionConnexion, IOException {
		String requete ;
		PreparedStatement preparedStatement;
		ResultSet rs;
		java.sql.Date sqlDate;
		int numD = -1;
		
		Connection conn = BDConnexion.getConnexion(user.getLogin(), user.getmdp());
		
		//requete
		for (int i = 0; i <representations.size(); i++) {
			
			if (BDCategories.nbPlacesDispoDansZone(user, representations.elementAt(i).getNumS(), representations.elementAt(i).getDateRep(), representations.elementAt(i).getNumZ()) > 0) {
				//Réserver ticket
				
				//Générer numDossier
				try {
				requete = "select max(noDossier) from LesDossiers";
				preparedStatement = conn.prepareStatement(requete);
				rs = preparedStatement.executeQuery();
				rs.next();
				numD = rs.getInt(1) + 1;
				preparedStatement.close();
				out.println("numD =" +numD);
				//Ajouter dossier à la BDD
				try {
					requete = "insert into LesDossiers(noDossier,montant) values(?,?)";
					preparedStatement = conn.prepareStatement(requete);
					preparedStatement.setInt(1, numD);
					preparedStatement.setDouble(2,montant);
					preparedStatement.executeUpdate();
					preparedStatement.close();
				} catch (SQLException e) {
					// TODO Auto-generated catch block
					e.printStackTrace();
				}
				
				
				//Ajouter ticket
				Ticket t = BDCategories.getTicket(user, representations.elementAt(i).getNumS(), representations.elementAt(i).getDateRep(), representations.elementAt(i).getNumZ());
				out.println("nOSerie = " +t.getNoSerie());
				requete = "INSERT INTO LesTickets VALUES(?,?,?,?,?,?,?)";
				preparedStatement = conn.prepareStatement(requete);
				preparedStatement.setInt(1, t.getNoSerie());
				preparedStatement.setInt(2, t.getNumS());
				Date d = new SimpleDateFormat("yyyy-MM-dd").parse(t.getDateRep());
				sqlDate = new java.sql.Date(d.getTime());
//					sqlDate = new java.sql.Date(representations.elementAt(i).getDateRep().getTime());
				preparedStatement.setDate(3, sqlDate);
				preparedStatement.setInt(4, t.getNoPlace());
				preparedStatement.setInt(5, t.getNoRang());
				Date now = new Date();
				sqlDate = new java.sql.Date(now.getTime());
				preparedStatement.setDate(6, sqlDate);
				preparedStatement.setInt(7, numD);
				//TODO: générer numDossier
				preparedStatement.executeUpdate();
				preparedStatement.close();
					
				//Incrémenter montant
					montant = montant + BDCategories.getPrix(user, t.getNumZ());
				} catch (SQLException e) {
					System.err.println("Erreur lors du lancement de la requete " + i + " sur " + representations.size());
					e.printStackTrace();
					return false;
				} catch (ParseException e) {
					// TODO Auto-generated catch block
					e.printStackTrace();
				}
				
				
				
			}
			
			
			
		}
		
		clean();
		//Deconnexion
		try {
			conn.close();
			return true;
		} catch (SQLException e) {
			System.err.println("Erreur lors de la fermeture de la connexion");
			e.printStackTrace();
			return false;
		}
	}
	
}
