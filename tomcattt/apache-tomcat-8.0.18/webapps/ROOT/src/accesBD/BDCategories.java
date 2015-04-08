package accesBD;

import java.sql.Connection;
import java.sql.PreparedStatement;
import java.sql.ResultSet;
import java.sql.SQLException;
import java.sql.Statement;
import java.text.ParseException;
import java.text.SimpleDateFormat;
import java.util.Date;
import java.util.Vector;

import exceptions.CategorieException;
import exceptions.ExceptionConnexion;
import modele.Categorie;
import modele.Place;
import modele.Representation;
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
				res.addElement(new Categorie (rs.getString(1), rs.getDouble(2)));
			}
		} catch (SQLException e) {
			throw new CategorieException (" Problème dans l'interrogation des catégories.."
					+ "Code Oracle " + e.getErrorCode()
					+ "Message " + e.getMessage());
		}
		BDConnexion.FermerTout(conn, stmt, rs);
		return res;
	}
	
	/**
	 * retourne la liste des catégories définies dans la bd
	 * @param Utilisateur
	 * @return Vector<Categorie>
	 * @throws CategorieException
	 * @throws ExceptionConnexion
	 */
	public static Vector<Representation> getRepresentation (Utilisateur user) throws CategorieException, ExceptionConnexion {
		Vector<Representation> res = new Vector<Representation>();
		String requete ;
		Statement stmt ;
		ResultSet rs ;
		Connection conn = BDConnexion.getConnexion(user.getLogin(), user.getmdp());
		
		requete = "select nomS, dateRep, numS from LesRepresentations NATURAL JOIN LesSpectacles";
		try {
			stmt = conn.createStatement();
			rs = stmt.executeQuery(requete);
			while (rs.next()) {
				res.addElement(new Representation (rs.getString(1), rs.getString(2), rs.getInt(3)));
			}
		} catch (SQLException e) {
			throw new CategorieException (" Problème dans l'interrogation des catégories.."
					+ "Code Oracle " + e.getErrorCode()
					+ "Message " + e.getMessage());
		}
		BDConnexion.FermerTout(conn, stmt, rs);
		return res;
	}
	
	/**
	 * Permet d'ajouter une catégorie
	 * @param user
	 * @param nomCat
	 * @param prix
	 * @throws CategorieException
	 * @throws ExceptionConnexion
	 */
	public static void ajouterCategorie(Utilisateur user, String nomCat,double prix) throws CategorieException, ExceptionConnexion {
		String requete ;
		PreparedStatement preparedStatement;
		
		Connection conn = BDConnexion.getConnexion(user.getLogin(), user.getmdp());
		
		requete = "INSERT INTO LesCategories(nomC, prix) VALUES(?,?)";
		try {
			preparedStatement = conn.prepareStatement(requete);
			preparedStatement.setString(1, nomCat);
			preparedStatement.setDouble(2, prix);
			preparedStatement.executeUpdate();
		} catch (SQLException e) {
			System.err.println("Erreur lors du lancement de la requete");
			e.printStackTrace();
		}
		try {
			conn.close();
		} catch (SQLException e) {
			System.err.println("Erreur lors de la fermeture de la connexion");
			e.printStackTrace();
		}
	}
	
	/**
	 * Permet d'ajouter une representation
	 * @param user
	 * @param nomCat
	 * @param prix
	 * @throws CategorieException
	 * @throws ExceptionConnexion
	 */
	public static void ajouterRepresentations(Utilisateur user, int numS,  String dateRep) throws CategorieException, ExceptionConnexion {
		String requete ;
		PreparedStatement preparedStatement;
		
		Connection conn = BDConnexion.getConnexion(user.getLogin(), user.getmdp());
		
		requete = "INSERT INTO LesRepresentations(numS, dateRep) VALUES(?,?)";
		try {
			preparedStatement = conn.prepareStatement(requete);
			preparedStatement.setInt(1, numS);
			Date d = new SimpleDateFormat("dd/MM/yyyy").parse(dateRep);
			java.sql.Date sqlDate = new java.sql.Date(d.getTime());
			preparedStatement.setDate(2, sqlDate);
			preparedStatement.executeUpdate();
		} catch (SQLException | ParseException e) {
			System.err.println("Erreur lors du lancement de la requete");
			e.printStackTrace();
		}
		try {
			conn.close();
		} catch (SQLException e) {
			System.err.println("Erreur lors de la fermeture de la connexion");
			e.printStackTrace();
		}
	}
	
	/**
	 * Permet de retirer une catégorie
	 * @param user
	 * @param nomCat
	 * @param prix
	 * @throws CategorieException
	 * @throws ExceptionConnexion
	 */
	public static void enleverCategorie(Utilisateur user, String nomCat) throws CategorieException, ExceptionConnexion {
		String requete ;
		PreparedStatement preparedStatement;
		
		Connection conn = BDConnexion.getConnexion(user.getLogin(), user.getmdp());
		
		requete = "DELETE FROM LesCategories where nomC = ?";
		try {
			preparedStatement = conn.prepareStatement(requete);
			preparedStatement.setString(1, nomCat);
			preparedStatement.executeUpdate();
		} catch (SQLException e) {
			System.err.println("Erreur lors du lancement de la requete");
			e.printStackTrace();
		}
		try {
			conn.close();
		} catch (SQLException e) {
			System.err.println("Erreur lors de la fermeture de la connexion");
			e.printStackTrace();
		}
	}
	
	/**
	 * Permet de modifier le prix d'une catégorie
	 * @param user
	 * @param nomCat
	 * @param prix
	 * @throws CategorieException
	 * @throws ExceptionConnexion
	 */
	public static void modifierPrixCategorie(Utilisateur user, String nomCat,double prix) throws CategorieException, ExceptionConnexion {
		String requete ;
		PreparedStatement preparedStatement;
		
		Connection conn = BDConnexion.getConnexion(user.getLogin(), user.getmdp());
		
		requete = "UPDATE LesCategories set prix = ? where nomC = ?";
		try {
			preparedStatement = conn.prepareStatement(requete);
			preparedStatement.setString(2, nomCat);
			preparedStatement.setDouble(1, prix);
			preparedStatement.executeUpdate();
		} catch (SQLException e) {
			System.err.println("Erreur lors du lancement de la requete");
			e.printStackTrace();
		}
		try {
			conn.close();
		} catch (SQLException e) {
			System.err.println("Erreur lors de la fermeture de la connexion");
			e.printStackTrace();
		}
	}
	
	/**
	 * Permet de modifier le nom d'une catégorie
	 * @param user
	 * @param ancienNom
	 * @param nouvNom
	 * @throws CategorieException
	 * @throws ExceptionConnexion
	 */
	public static void modifierNomCategorie(Utilisateur user, String ancienNom,String nouvNom) throws CategorieException, ExceptionConnexion {
		// TODO
//		String requete ;
//		PreparedStatement preparedStatement;
//		Statement stmt ;
//		ResultSet rs ;
		
//		Connection conn = BDConnexion.getConnexion(user.getLogin(), user.getmdp());
	
		//1ere requete : creer nouvelle catgeorie avec le nouveau nom et l'ancien prix
//		int prix = 0;
//		requete = "select prix from LesCategories where nomC = " + ancienNom;
//		try {
//			stmt = conn.createStatement();
//			rs = stmt.executeQuery(requete);
//			prix = rs.getInt(1);
//		} catch (SQLException e) {
//			System.err.println("Erreur lors de la recuperation du prix");
//			e.printStackTrace();
//		}
//		
//		ajouterCategorie(user, nouvNom, prix);
		
		//2eme requete : modifier les zones afin de mettre en relation avec la nouvelle categorie
//		requete = "update LesZones set nomC = ? where nomC = ?";
//		try {
//			preparedStatement = conn.prepareStatement(requete);
//			preparedStatement.setString(1, nouvNom);
//			preparedStatement.setString(2, ancienNom);
//			rs = preparedStatement.executeQuery(requete);
//		} catch (SQLException e) {
//			System.err.println("Erreur lors de la modification des zones");
//			e.printStackTrace();
//		}
		
		//3eme requete : supprimer l'ancienne categorie
//		enleverCategorie(user, ancienNom);
//		
//		try {
//			conn.close();
//		} catch (SQLException e) {
//			System.err.println("Erreur lors de la fermeture de la connexion");
//			e.printStackTrace();
//		}
		
	}
	
	/**
	 * Fonction généraliste permettant d'interroger la base
	 * @param user
	 * @param listArgs
	 * @param nomCat 
	 * @param conditions
	 * @return
	 * @throws CategorieException
	 * @throws ExceptionConnexion
	 */
	public static Vector<String> interrogerBase(Utilisateur user, String listArgs, String nomCat, String conditions) throws CategorieException, ExceptionConnexion {
		// TODO
		Vector<String> res = new Vector<String>();
		String requete ;
		Statement stmt ;
		ResultSet rs ;
		Connection conn = BDConnexion.getConnexion(user.getLogin(), user.getmdp());
		
		requete = "SELECT " + listArgs + " from "+ nomCat + " where " + conditions;
		try {
			stmt = conn.createStatement();
			rs = stmt.executeQuery(requete);
			int colone = rs.getRow();
			while (rs.next()) {
				String elem = "";
				for (int i = 0; i < colone; i++) {
					elem = elem + rs.getString(i);
				}
				res.addElement( elem );
			}
		} catch (SQLException e) {
			throw new CategorieException (" Problème lors de l'execution de la requete"
					+ "Code Oracle " + e.getErrorCode()
					+ "Message " + e.getMessage());
		}
		BDConnexion.FermerTout(conn, stmt, rs);
		return res;
	}
	
	/**
	 * Renvoie le nombre de place disponibles pour une représentaiton donnée
	 * @param user
	 * @param numS : Numéro du spectacle
	 * @param dateRep : Date de représentation du spectacle
	 * @return : nombre de places (int)
	 * @throws CategorieException
	 * @throws ExceptionConnexion
	 */
	public static int nbPlacesDispo(Utilisateur user, int numS, String dateRep) throws CategorieException, ExceptionConnexion {
		
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
			BDConnexion.FermerTout(conn, stmt, rs);
		} catch (SQLException e) {
			System.err.println("Erreur lors de l'intérrogation de la base");
			e.printStackTrace();
		}
		
		return nbPlaces;
	}

	/**
	 * Permet de réserver un ticket
	 * @param user
	 * @param numS
	 * @param dateRep
	 * @param noPlace
	 * @param noRang
	 * @param noDossier
	 */
	public static void reseverTicket(Utilisateur user, int numS, String dateRep, int noPlace, int noRang, int noDossier){
		String requete ;
		PreparedStatement preparedStatement;
		
		Connection conn;
		try {
			conn = BDConnexion.getConnexion(user.getLogin(), user.getmdp());
			
			if (nbPlacesDispo(user, numS, dateRep) > 70) {
				requete = "INSERT INTO LesTickets(numS ,dateRep,noPlace,noRang,dateEmission,noDossier)  VALUES(?,?,?,?,?,?)";
				try {
					preparedStatement = conn.prepareStatement(requete);
					preparedStatement.setInt(1, numS);
					Date d = new SimpleDateFormat("dd/MM/yyyy").parse(dateRep);
					java.sql.Date sqlDate = new java.sql.Date(d.getTime());
					preparedStatement.setDate(2, sqlDate);
					preparedStatement.setInt(3, noPlace);
					preparedStatement.setInt(4, noRang);
					Date d2 = new SimpleDateFormat("dd/MM/yyyy").parse(new Date().toString());
					java.sql.Date sqlDate2 = new java.sql.Date(d2.getTime());
					preparedStatement.setDate(5, sqlDate2); 
					preparedStatement.setInt(6, noDossier);
					preparedStatement.executeUpdate();
					conn.close();
				} catch (SQLException e) {
					e.printStackTrace();
				} catch (ParseException e) {
					e.printStackTrace();
				}
			}	
		} catch (CategorieException e) {
			System.err.println("Erreur lors du lancement de la requête");
			e.printStackTrace();
		} catch (ExceptionConnexion e1) {
			System.err.println("Erreur lors de la connection");
			e1.printStackTrace();
		}
	}
	
	/**
	 * Renvoie le nombre de place disponibles pour une représentaiton donnée dans une zone donnée
	 * @param user
	 * @param numS : Numéro du spectacle
	 * @param dateRep : Date de représentation du spectacle
	 * @param numZ : numéro de la zone donnée
	 * @return : nombre de places (int)
	 * @throws CategorieException
	 * @throws ExceptionConnexion
	 */
	public static int nbPlacesDispoDansZone(Utilisateur user, int numS, String dateRep, int numZ) throws CategorieException, ExceptionConnexion {
		int nbPlaces = 0;
		String requete ;
		Statement stmt ;
		ResultSet rs ;
		
		try {
			Connection conn = BDConnexion.getConnexion(user.getLogin(), user.getmdp());
			
			requete = "select count(*) from LesPlaces NATURAL JOIN LesZones where numS ="+numS+" and dateRep=" + dateRep + " and numZ=" + numZ;
			
			stmt = conn.createStatement();
			rs = stmt.executeQuery(requete);
			int nbPlacesTotal = rs.getInt(1);
			
			requete = "select count(*) from LesTickets NATURAL JOIN LesZones where numS ="+numS+" and dateRep=" + dateRep + " and numZ=" + numZ;
			stmt = conn.createStatement();
			rs = stmt.executeQuery(requete);
			nbPlaces = nbPlacesTotal - rs.getInt(1);	
			
			BDConnexion.FermerTout(conn, stmt, rs);
		} catch (SQLException e) {
			throw new CategorieException (" Problème dans l'interrogation des catégories.."
					+ "Code Oracle " + e.getErrorCode()
					+ "Message " + e.getMessage());
		}
		
		
		return nbPlaces;
	}
	
	/**
	 * Permet de réserver plusieurs tickets dans une zone
	 * @param user
	 * @param numS
	 * @param dateRep
	 * @param numZ : numéro de la zone
	 * @param nbPlaces : nombre de place à réserver
	 */
	public static void reserverTickets(Utilisateur user, int numS, String dateRep, int numZ, int nbPlaces ){
		try {
			if (nbPlacesDispo(user, numS, dateRep) >= 70+nbPlaces) {
				if (nbPlacesDispoDansZone(user, numS, dateRep, numZ) >= nbPlaces) {
					//Création du numéro de dossier
					String requete ;
					Statement stmt ;
					ResultSet rs ;
					Connection conn = BDConnexion.getConnexion(user.getLogin(), user.getmdp());
					
					requete = "select max(noDossier) from LesTickets";
					
					stmt = conn.createStatement();
					rs = stmt.executeQuery(requete);
					int noDossier = rs.getInt(1) + 1;

					requete = "(select noPlace, noRang from LesPlaces where numZ =" + numZ + 
							") minus (select noPlace, noRang from LesTickets NATURAL JOIN LesPlaces where numZ=" + numZ+" and numS=" + numS + "and dateRep=" + dateRep + ")";
					stmt = conn.createStatement();
					rs = stmt.executeQuery(requete);		
					
					for (int i = 0; i < nbPlaces; i++) {
						int noPlace = rs.getInt(1);
						int noRang = rs.getInt(2);
						reseverTicket(user, numS, dateRep, noPlace, noRang, noDossier);
						rs.next();	
					}
					BDConnexion.FermerTout(conn, stmt, rs);
				}
			}
		} catch (CategorieException | ExceptionConnexion e) {
			System.err.println("Erreur lors de la connection");
			e.printStackTrace();
		} catch (SQLException e) {
			System.err.println("Erreur lors du lancement de la requête");
			e.printStackTrace();
		}
	}
	
	public static void ajouterSpectacle (Utilisateur user, int numS, String nomS) {
		String requete ;
		PreparedStatement preparedStatement;
		
		try {
			Connection conn = BDConnexion.getConnexion(user.getLogin(), user.getmdp());
			
			requete = "INSERT INTO LesSpectacles(numS, nomS) VALUES(?,?)";
			
			preparedStatement = conn.prepareStatement(requete);
			preparedStatement.setInt(0, numS);
			preparedStatement.setString(1, nomS);
			preparedStatement.executeUpdate();
			
			conn.close();
			
		} catch (SQLException e) {
			System.err.println("Erreur lors du lancement de la requete");
			e.printStackTrace();
		} catch (ExceptionConnexion e) {
			System.err.println("Erreur lors de la connection");
			e.printStackTrace();
		}
	}
	
	
	public static void ajouterRepresentation(Utilisateur user, int numS, String dateRep){
		String requete ;
		PreparedStatement preparedStatement;
		Statement stmt ;
		ResultSet rs ;
		
		try {
			Connection conn = BDConnexion.getConnexion(user.getLogin(), user.getmdp());
			
			requete = "INSERT INTO LesRepresentations(numS, dateRep) VALUES(?,?)";
			
			preparedStatement = conn.prepareStatement(requete);
			preparedStatement.setInt(0, numS);
			preparedStatement.setString(1, dateRep);
			preparedStatement.executeUpdate();
			
			requete = "select numZ from LesZones where categorie = 'orchestre' ";
			stmt = conn.createStatement();
			rs = stmt.executeQuery(requete);
			
			int numZ = rs.getInt(1);
			reserverTickets(user, numS, dateRep, numZ, 10);
			
			conn.close();
			
		} catch (SQLException e) {
			System.err.println("Erreur lors du lancement de la requete");
			e.printStackTrace();
		} catch (ExceptionConnexion e) {
			System.err.println("Erreur lors de la connection");
			e.printStackTrace();
		}
	}
	public static Vector<Representation> getRepresentationDUnSpectacle(Utilisateur user, int numS) {
		Vector<Representation> res = new Vector<Representation>();
		String requete ;
		Statement stmt ;
		ResultSet rs ;
		Connection conn;
		try {
			conn = BDConnexion.getConnexion(user.getLogin(), user.getmdp());
			requete = "select nomS, dateRep, numS from LesRepresentations NATURAL JOIN LesSpectacles where numS = "+numS;

			stmt = conn.createStatement();
			rs = stmt.executeQuery(requete);
			while (rs.next()) {
				res.addElement(new Representation (rs.getString(1), rs.getString(2), rs.getInt(3)));
			}
			BDConnexion.FermerTout(conn, stmt, rs);
		} catch (SQLException e) {
			try {
				throw new CategorieException (" Problème dans l'interrogation des catégories.."
						+ "Code Oracle " + e.getErrorCode()
						+ "Message " + e.getMessage());
			} catch (CategorieException e1) {
				// TODO Auto-generated catch block
				e1.printStackTrace();
			}
		} catch (ExceptionConnexion e) {
			// TODO Auto-generated catch block
			e.printStackTrace();
		}
		return res;
	}
	
	public static Vector<Place> getPlacePourRep (Utilisateur user, int numS, String dateRep) throws CategorieException, ExceptionConnexion, ParseException {
		Vector<Place> res = new Vector<Place>();
		String requete ;
//		Statement stmt ;
		ResultSet rs ;PreparedStatement preparedStatement;
		Connection conn = BDConnexion.getConnexion(user.getLogin(), user.getmdp());
		
		
		
		requete = "(select noPlace, noRang from LesPlaces ) minus (select noPlace, noRang from LesTickets where numS = ? and dateRep = ?)";
		try {
			preparedStatement = conn.prepareStatement(requete);
			preparedStatement.setInt(1, numS);
			Date d = new SimpleDateFormat("yyyy-MM-dd").parse(dateRep);
			java.sql.Date sqlDate = new java.sql.Date(d.getTime());
//			dateRep = sqlDate.toString();
			preparedStatement.setDate(2, sqlDate);
			rs =  preparedStatement.executeQuery();
			while (rs.next()) {
				res.addElement(new Place (rs.getInt(1), rs.getInt(2)));
			}
		} catch (SQLException e) {
			e.printStackTrace();
		}catch (Exception e) {
			e.printStackTrace();
		}
		return res;
	}
	
	public static int nbZone(Utilisateur user) throws CategorieException, ExceptionConnexion {
		String requete ;
		Statement stmt ;
		ResultSet rs ;
		
		try {
			Connection conn = BDConnexion.getConnexion(user.getLogin(), user.getmdp());
			
			requete = "select count(*) from LesZones";
			
			stmt = conn.createStatement();
			rs = stmt.executeQuery(requete);
			rs.next();
			BDConnexion.FermerTout(conn, stmt, rs);
			
			return rs.getInt(1);
				
		} catch (SQLException e) {
			throw new CategorieException (" Problème dans l'interrogation des catégories.."
					+ "Code Oracle " + e.getErrorCode()
					+ "Message " + e.getMessage());
		}
	}
	
}


