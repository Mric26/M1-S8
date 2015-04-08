package application;

import java.sql.Connection;
import java.util.Vector;

import utils.Constantes;
import utils.Utilitaires;

import jus.util.IO;
import modele.Utilisateur;
import modele.Categorie;
 
import exceptions.ExceptionTheatre;

/**
 * Point d'entree de l'application
 * @author fauvet
 *
 */
public class Theatre {

	/**
	 * Construit le menu
	 * @return liste des entrees du menu
	 */
	private static Vector<String>  Menu () {
		Vector<String> choix = new Vector<String> ();
		choix.add("Quitter");
		choix.add("Consulter les categories tarifaires ");
		choix.add("Ajouter une categorie tarifaire ");
		choix.add("Retirer une categorie tarifaire ");
		choix.add("Modifier le nom d'une categorie tarifaire ");
		choix.add("Modifier le prix d'une categorie tarifaire ");
		choix.add("Modifier le nom et le prix d'une categorie tarifaire ");
		choix.add("Executer une requete");
		choix.add("Consulter les representations ");
		choix.add("Ajouter une representation ");
		return choix;
	}

	/**
	 * Gestion du choix de la fonction (depend du role de l'utilisateur)
	 * @param args
	 */
	public static void main(String[] args) {
		IO.setIn(); IO.setOut();
		int choix = 0;
		try {
			Utilisateur user = Utilitaires.Identification();
			if (user != null) {
				do {
					IO.afficher (Constantes.Menu) ;
					choix = IO.lireFromListe(Menu(), Constantes.Invite);
					if (choix == 0) {
						IO.afficherln("au revoir...");
					} else if (choix == 1) {
						Utilitaires.AfficherCategories(user);
					} else if (choix == 2) {
						Utilitaires.AjouterCategories(user);
					} else if (choix == 3) {
						Utilitaires.RetirerCategories(user);	
					} else if (choix == 4) {
						Utilitaires.ModifierNomCategories(user);
					}else if (choix == 5) {
						Utilitaires.ModifierPrixCategories(user);
					}else if (choix == 6) {
						Utilitaires.ModifierNomPrixCategories(user);
					}else if (choix == 7) {
						Utilitaires.ExecuterRequete(user);
					}else if (choix == 8) {
						Utilitaires.AfficherRepresentation(user);
					}else if (choix == 9) {
						Utilitaires.AjouterRepresentation(user);
					}

				} while (choix != 0);
			}
		} catch (Exception e) {
			IO.afficherln("===========");
			IO.afficherln("Au revoir... " + e.getMessage());
		}
	}
}
