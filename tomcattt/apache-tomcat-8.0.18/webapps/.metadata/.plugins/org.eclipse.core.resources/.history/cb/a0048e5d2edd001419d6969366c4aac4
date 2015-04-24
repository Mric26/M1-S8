package utils;

import java.util.Properties;
import java.io.FileInputStream;
import java.io.InputStream;
import java.io.IOException;
import java.sql.Connection;
import java.util.Vector;
import java.awt.Frame;

import javax.swing.JOptionPane;

import jus.util.IO;
import accesBD.BDCategories;
import accesBD.BDConnexion;
import modele.Representation;
import modele.Utilisateur;
import modele.Categorie;
import exceptions.ExceptionUtilisateur;
import exceptions.ExceptionConnexion;
import exceptions.CategorieException;

/**
 * les operations de l'application
 * 
 * @author fauvet
 * 
 */
public class Utilitaires {

	public Utilitaires() {
	}

	/**
	 * Affiche les categories du theatre avec pour chacune son prix
	 * @param user :l'utilisateur identifie
	 * @throws ExceptionConnexion
	 * @throws IOException
	 */
	public static void AfficherCategories(Utilisateur user) throws IOException {
		Vector<Categorie> res = new Vector<Categorie>();
		try {
			IO.afficherln("===================");
			IO.afficherln("Listes des categories tarifaires");
			res = BDCategories.getCategorie(user);
			if (res.isEmpty()) {
				IO.afficherln(" Liste vide ");
			} else {
				for (int i = 0; i < res.size(); i++) {
					IO.afficherln(res.elementAt(i).getCategorie() + " (prix : "
							+ res.elementAt(i).getPrix() + ")");
				}
			}
			IO.afficherln("===================");
		} catch (CategorieException e) {
			IO.afficherln(" Erreur dans l'affichage des categories : "
					+ e.getMessage());
		} catch (ExceptionConnexion e) {
			IO.afficherln(" Erreur dans l'affichage des categories : "
					+ e.getMessage());
		}
	}

	/**
	 * effectue la connexion pour l'utilisateur
	 * 
	 * @return l'oid de l'objet utilisateur
	 * @throws ExceptionUtilisateur
	 */
	public static Utilisateur Identification() throws ExceptionConnexion,ExceptionUtilisateur, IOException {
		Utilisateur user = null;
		String login;
		String passwd;
		// lecture des parametres de connexion dans connection.conf
		Properties p = new Properties();
		InputStream is = null;
		is = new FileInputStream(utils.Constantes.Config);
		p.load(is);
		login = p.getProperty("user");
		passwd = p.getProperty("mdp");
		if (login == null || login.equals("MYUSERNAME")) {
			UserNamePasswordDialog login_dialog = new UserNamePasswordDialog(
					new Frame(""));
			login_dialog.setVisible(true);
			login = login_dialog.getUid();
			passwd = login_dialog.getPwd();
		}
		/* test de la connexion */
		Connection conn = BDConnexion.getConnexion(login, passwd);
		if (conn != null) {
			IO.afficherln("Connexion reussie...");
			BDConnexion.FermerTout(conn, null, null);
			user = new Utilisateur(login, passwd);
		} else {
			throw new ExceptionConnexion("Connexion impossible\n");
		}
		return user;
	}

	/**
	 * Ajoute une categorie
	 * @param user
	 */
	public static void AjouterCategories(Utilisateur user) {
		Vector<Categorie> res = new Vector<Categorie>();
		
		//recup
		JOptionPane j = new JOptionPane();
		String nomC = j.showInputDialog("Entrez le nom de la categorie :");
		float prix = Float.parseFloat( j.showInputDialog("Donner le prix : ") );
		
		try {
			IO.afficherln("===================");
			IO.afficherln("Ajout de :");
			IO.afficherln(nomC + " avec un prix de : " + prix);
			BDCategories.ajouterCategorie(user, nomC, prix);
			IO.afficherln("===================");
			IO.afficherln("Listes des categories après ajout :");
			res = BDCategories.getCategorie(user);
			if (res.isEmpty()) {
				IO.afficherln(" Liste vide ");
			} else {
				for (int i = 0; i < res.size(); i++) {
					IO.afficherln(res.elementAt(i).getCategorie() + " (prix : "
							+ res.elementAt(i).getPrix() + ")");
				}
			}
			IO.afficherln("===================");
		} catch (CategorieException e) {
			IO.afficherln(" Erreur dans l'affichage des categories : "
					+ e.getMessage());
		} catch (ExceptionConnexion e) {
			IO.afficherln(" Erreur dans l'affichage des categories : "
					+ e.getMessage());
		}
	}
	
	public static void RetirerCategories(Utilisateur user) {
		Vector<Categorie> res = new Vector<Categorie>();
		
		//recup
		JOptionPane j = new JOptionPane();
		String nomC = j.showInputDialog("Entrez le nom de la categorie :");
		
		try {
			IO.afficherln("===================");
			IO.afficherln("Retrait de :");
			IO.afficherln(nomC );
			BDCategories.enleverCategorie(user, nomC);
			IO.afficherln("===================");
			IO.afficherln("Listes des categories après retrait :");
			res = BDCategories.getCategorie(user);
			if (res.isEmpty()) {
				IO.afficherln(" Liste vide ");
			} else {
				for (int i = 0; i < res.size(); i++) {
					IO.afficherln(res.elementAt(i).getCategorie() + " (prix : "
							+ res.elementAt(i).getPrix() + ")");
				}
			}
			IO.afficherln("===================");
		} catch (CategorieException e) {
			IO.afficherln(" Erreur dans l'affichage des categories : "
					+ e.getMessage());
		} catch (ExceptionConnexion e) {
			IO.afficherln(" Erreur dans l'affichage des categories : "
					+ e.getMessage());
		}		
	}

	public static void ModifierNomCategories(Utilisateur user) {
		Vector<Categorie> res = new Vector<Categorie>();
		
		//recup
		JOptionPane j = new JOptionPane();
		String nomC = j.showInputDialog("Entrez l'ancien nom de la categorie :");
		String nomC2 = j.showInputDialog("Entrez le nouveau nom de la categorie :");
		
		try {
			IO.afficherln("===================");
			IO.afficherln("Modification de :");
			IO.afficherln(nomC + " en : " + nomC2);
			BDCategories.modifierNomCategorie(user, nomC, nomC2);
			IO.afficherln("===================");
			IO.afficherln("Listes des categories après modification :");
			res = BDCategories.getCategorie(user);
			if (res.isEmpty()) {
				IO.afficherln(" Liste vide ");
			} else {
				for (int i = 0; i < res.size(); i++) {
					IO.afficherln(res.elementAt(i).getCategorie() + " (prix : "
							+ res.elementAt(i).getPrix() + ")");
				}
			}
			IO.afficherln("===================");
		} catch (CategorieException e) {
			IO.afficherln(" Erreur dans l'affichage des categories : "
					+ e.getMessage());
		} catch (ExceptionConnexion e) {
			IO.afficherln(" Erreur dans l'affichage des categories : "
					+ e.getMessage());
		}	
	}

	public static void ModifierPrixCategories(Utilisateur user) {
		Vector<Categorie> res = new Vector<Categorie>();
		
		//recup
		JOptionPane j = new JOptionPane();
		String nomC = j.showInputDialog("Entrez le nom de la categorie :");
		double prix = Double.parseDouble( j.showInputDialog("Entrez le nouveau prix de la categorie :") );
		
		try {
			IO.afficherln("===================");
			IO.afficherln("Modification de :");
			IO.afficherln(nomC + " avec pour nouveau prix : " + prix);
			BDCategories.modifierPrixCategorie(user, nomC, prix);
			IO.afficherln("===================");
			IO.afficherln("Listes des categories après modification :");
			res = BDCategories.getCategorie(user);
			if (res.isEmpty()) {
				IO.afficherln(" Liste vide ");
			} else {
				for (int i = 0; i < res.size(); i++) {
					IO.afficherln(res.elementAt(i).getCategorie() + " (prix : "
							+ res.elementAt(i).getPrix() + ")");
				}
			}
			IO.afficherln("===================");
		} catch (CategorieException e) {
			IO.afficherln(" Erreur dans l'affichage des categories : "
					+ e.getMessage());
		} catch (ExceptionConnexion e) {
			IO.afficherln(" Erreur dans l'affichage des categories : "
					+ e.getMessage());
		}	
	}

	public static void ModifierNomPrixCategories(Utilisateur user) {
		ModifierNomCategories(user);
		ModifierPrixCategories(user);
	}

	public static void ExecuterRequete(Utilisateur user) {
		Vector<String> res = new Vector<String>();
		
		//recup
		JOptionPane j = new JOptionPane();
		String listArgs = j.showInputDialog("Entrez les elements à afficher");
		String nomCat = j.showInputDialog("Entrez le nom de la categorie");
		String conditions = j.showInputDialog("Entrez les conditions");
		
		try {
			IO.afficherln("===================");
			IO.afficherln("Affichage de :");
			IO.afficherln("Select " + listArgs + " from " + nomCat + " where " + conditions);
			res = BDCategories.interrogerBase(user, listArgs, nomCat, conditions);
			if (res.isEmpty()) {
				IO.afficherln(" Liste vide ");
			} else {
				for (int i = 0; i < res.size(); i++) {
					IO.afficherln( res.elementAt(i) );
				}
			}
			IO.afficherln("===================");
		} catch (CategorieException e) {
			IO.afficherln(" Erreur dans l'affichage des categories : "
					+ e.getMessage());
		} catch (ExceptionConnexion e) {
			IO.afficherln(" Erreur dans l'affichage des categories : "
					+ e.getMessage());
		}

	}

	public static void AfficherRepresentation(Utilisateur user) {
		Vector<Representation> res = new Vector<Representation>();
		try {
			IO.afficherln("===================");
			IO.afficherln("Listes des representation");
			res = BDCategories.getRepresentation(user);
			if (res.isEmpty()) {
				IO.afficherln(" Liste vide ");
			} else {
				for (int i = 0; i < res.size(); i++) {
					IO.afficherln(res.elementAt(i).getNom() + " (date : " + res.elementAt(i).getDate() + ")");
				}
			}
			IO.afficherln("===================");
		} catch (CategorieException e) {
			IO.afficherln(" Erreur dans l'affichage des categories : " + e.getMessage());
		} catch (ExceptionConnexion e) {
			IO.afficherln(" Erreur dans l'affichage des categories : " + e.getMessage());
		}
	}

	public static void AjouterRepresentation(Utilisateur user) {
		Vector<Representation> res = new Vector<Representation>();
		
		//recup
		JOptionPane j = new JOptionPane();
		int numS = Integer.parseInt( j.showInputDialog("Entrez le n de la representation :") );
		String dateRep = j.showInputDialog("Donner la date de representation : ");
		
		try {
			IO.afficherln("===================");
			IO.afficherln("Ajout de :");
			IO.afficherln(numS + " pour la date : " + dateRep);
			BDCategories.ajouterRepresentations(user, numS, dateRep);
			IO.afficherln("===================");
			IO.afficherln("Listes des representations");
			res = BDCategories.getRepresentation(user);
			if (res.isEmpty()) {
				IO.afficherln(" Liste vide ");
			} else {
				for (int i = 0; i < res.size(); i++) {
					IO.afficherln(res.elementAt(i).getNom() + " (date : " + res.elementAt(i).getDate() + ")");
				}
			}
			IO.afficherln("===================");
		} catch (CategorieException e) {
			IO.afficherln(" Erreur dans l'affichage des representations : "
					+ e.getMessage());
		} catch (ExceptionConnexion e) {
			IO.afficherln(" Erreur dans l'affichage des representations : "
					+ e.getMessage());
		}
	}

}
