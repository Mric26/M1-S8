package accesBD;

import java.sql.Connection;
import java.sql.PreparedStatement;
import java.sql.ResultSet;
import java.sql.SQLException;
import java.sql.Statement;
import java.util.Vector;

import com.sun.org.apache.xerces.internal.impl.dv.dtd.NMTOKENDatatypeValidator;

import exceptions.CategorieException;
import exceptions.ExceptionConnexion;
import modele.Categorie;
import modele.Utilisateur;

public class BDCategories {

	public BDCategories () {
		
	}
	/**
	 * retourne la liste des catégories définies dans la bd
	 * @param Utilisateur
	 * @return Vector<Categorie>
	 * @throws CategorieException
	 * @throws ExceptionConnexion
	 */
	public static Vector<Categorie> getCategorie (Utilisateur user)
	throws CategorieException, ExceptionConnexion {
		Vector<Categorie> res = new Vector<Categorie>();
		String requete ;
		Statement stmt ;
		ResultSet rs ;
		Connection conn = BDConnexion.getConnexion(user.getLogin(), user.getmdp());
		
		requete = "select nomc, prix from LesCategories order by nomc";
		try {
			stmt = conn.createStatement();
			rs = stmt.executeQuery(requete);
			while (rs.next()) {
				res.addElement(new Categorie (rs.getString(1), rs.getFloat(2)));
			}
		} catch (SQLException e) {
			throw new CategorieException (" Problème dans l'interrogation des catégories.."
					+ "Code Oracle " + e.getErrorCode()
					+ "Message " + e.getMessage());
		}
		BDConnexion.FermerTout(conn, stmt, rs);
		return res;
	}
	
	public void ajouterCategorie(Utilisateur user, String nomCat,float prix) throws CategorieException, ExceptionConnexion {
		String requete ;
		PreparedStatement preparedStatement;
		
		Connection conn = BDConnexion.getConnexion(user.getLogin(), user.getmdp());
		
		requete = "INSERT INTO LesCategories(nomC, prix) VALUES(?,?)";
		try {
			preparedStatement = conn.prepareStatement(requete);
			preparedStatement.setString(0, nomCat);
			preparedStatement.setFloat(1, prix);
			preparedStatement.executeUpdate();
		} catch (SQLException e) {
			// TODO Auto-generated catch block
			e.printStackTrace();
		}
		try {
			conn.close();
		} catch (SQLException e) {
			// TODO Auto-generated catch block
			e.printStackTrace();
		}
	}
	
	public void modifierPrixCategorie(Utilisateur user, String nomCat,float prix) throws CategorieException, ExceptionConnexion {
		String requete ;
		PreparedStatement preparedStatement;
		
		Connection conn = BDConnexion.getConnexion(user.getLogin(), user.getmdp());
		
		requete = "UPDATE LesCategories set prix = ? where nomC = ?";
		try {
			preparedStatement = conn.prepareStatement(requete);
			preparedStatement.setString(1, nomCat);
			preparedStatement.setFloat(0, prix);
			preparedStatement.executeUpdate();
		} catch (SQLException e) {
			// TODO Auto-generated catch block
			e.printStackTrace();
		}
		try {
			conn.close();
		} catch (SQLException e) {
			// TODO Auto-generated catch block
			e.printStackTrace();
		}
	}
	
	public void modifierNomCategorie(Utilisateur user, String ancienNom,String nouvNom) throws CategorieException, ExceptionConnexion {
		String requete ;
		PreparedStatement preparedStatement;
		
		Connection conn = BDConnexion.getConnexion(user.getLogin(), user.getmdp());
		
		requete = "UPDATE LesCategories set nomC = ? where nomC = ?";
		try {
			preparedStatement = conn.prepareStatement(requete);
			preparedStatement.setString(0, ancienNom);
			preparedStatement.setString(1, nouvNom);
			preparedStatement.executeUpdate();
		} catch (SQLException e) {
			// TODO Auto-generated catch block
			e.printStackTrace();
		}
		try {
			conn.close();
		} catch (SQLException e) {
			// TODO Auto-generated catch block
			e.printStackTrace();
		}
	}
	
	public ResultSet interrogerBase(Utilisateur user, String listArgs, String nomCat, String conditions) throws CategorieException, ExceptionConnexion {
		Vector<Categorie> res = new Vector<Categorie>();
		String requete ;
		Statement stmt ;
		ResultSet rs ;
		Connection conn = BDConnexion.getConnexion(user.getLogin(), user.getmdp());
		
		requete = "SELECT " + listArgs + " from "+ nomCat + " where " + conditions;
		try {
			stmt = conn.createStatement();
			rs = stmt.executeQuery(requete);
		} catch (SQLException e) {
			throw new CategorieException (" Problème dans l'interrogation des catégories.."
					+ "Code Oracle " + e.getErrorCode()
					+ "Message " + e.getMessage());
		}
		BDConnexion.FermerTout(conn, stmt, rs);
		return rs;
	}
	
	public int nbPlacesDispo(Utilisateur user, int numS, String dateRep) throws CategorieException, ExceptionConnexion {
		
		int nbPlaces = 0;
		String requete ;
		Statement stmt ;
		ResultSet rs ;
		Connection conn = BDConnexion.getConnexion(user.getLogin(), user.getmdp());
		
		requete = "select count(*) from LesPlaces where numS ="+numS+" and dateRep="+dateRep;
		try {
			stmt = conn.createStatement();
			rs = stmt.executeQuery(requete);
			int nbPlacesTotal = rs.getInt(1);
			
			requete = "select count(*) from LesTickets where numS ="+numS+" and dateRep="+dateRep;
			stmt = conn.createStatement();
			rs = stmt.executeQuery(requete);
			nbPlaces = nbPlacesTotal - rs.getInt(1);		
		} catch (SQLException e) {
			throw new CategorieException (" Problème dans l'interrogation des catégories.."
					+ "Code Oracle " + e.getErrorCode()
					+ "Message " + e.getMessage());
		}
		
		BDConnexion.FermerTout(conn, stmt, rs);
		return nbPlaces;
	}

	public void reseverTicket(Utilisateur user, int numS, String dateRep, int noPlace, int noRang, int noDossier){
		
		String requete ;
		PreparedStatement preparedStatement;
		
		Connection conn;
		try {
			conn = BDConnexion.getConnexion(user.getLogin(), user.getmdp());
			
			if (nbPlacesDispo(user, numS, dateRep) > 70) {

			requete = "INSERT INTO LesTickets(numS ,dateRep,noPlace,noRang,dateEmission,noDossier)  VALUES(?,?,?,?,?,?)";
			try {
				preparedStatement = conn.prepareStatement(requete);
				preparedStatement.setInt(0, numS);
				preparedStatement.setString(1, dateRep);
				preparedStatement.setInt(2, noPlace);
				preparedStatement.executeUpdate();
				//TODO : finir ici
			} catch (SQLException e) {
				// TODO Auto-generated catch block
				e.printStackTrace();
			}
			try {
				conn.close();
			} catch (SQLException e) {
				// TODO Auto-generated catch block
				e.printStackTrace();
			}
		}	
		} catch (ExceptionConnexion e1) {
			// TODO Auto-generated catch block
			e1.printStackTrace();
		} catch (CategorieException e) {
			// TODO Auto-generated catch block
			e.printStackTrace();
		}
		
			
	}
	
}


