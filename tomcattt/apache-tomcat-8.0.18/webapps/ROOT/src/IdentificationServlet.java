

import javax.servlet.*;
import javax.servlet.http.*;

import modele.Utilisateur;
import utils.Utilitaires;
import accesBD.BDCategories;

import java.io.BufferedReader;
import java.io.File;
import java.io.FileReader;
import java.io.IOException;

public class IdentificationServlet extends HttpServlet {

	public void doGet(HttpServletRequest req, HttpServletResponse res) throws ServletException, IOException
	{
	  String name, pswd, result;
	  ServletOutputStream out = res.getOutputStream();   
	
	  res.setContentType("text/html");
	
	  out.println("<HEAD><TITLE> Identification </TITLE></HEAD>");
	  out.println("<BODY bgproperties=\"fixed\" background=\"/images/rideau.JPG\">");
	  out.println("<font color=\"#FFFFFF\"><h1> identifaction pour acces &agrave la page d'administration </h1>");
	
	  name		= req.getParameter("name");
	  pswd		= req.getParameter("pswd");
	  if (name == null || pswd == null ) {
	        	out.println("<font color=\"#FFFFFF\">Veuillez saisir votre login et mot de passe administrateur :");
	        	out.println("<P>");
	        	out.print("<form action=\"");
	        	out.print("IdentificationServlet\" ");
	        	out.println("method=POST>");
	        	out.println("nom administateur :");
	        	out.println("<input type=text size=20 name=name>");
	        	out.println("<br>");
	        	out.println("mot de passe :");
	        	out.println("<input type=password size=20 name=pswd>");
	        	out.println("<input type=submit>");
	        	out.println("</form>");
	  } else {
		try {
			Utilisateur user = Utilitaires.Identification();
			result= BDCategories.identification(user, name, pswd);
			String adm= "admin";
			if(result.equals(adm)){ //on affiche la page admin.html
				//out.println("<hr><p><font color=\"#FFFFFF\"><a href=\"/admin/admin.html\">Page d'administration</a></p>");
				
				out.println("<!doctype html public \"-//w3c//dtd html 4.0 transitional//en\">");
						out.println("<html>");
						out.println("<head>");
						out.println("<meta http-equiv=\"Content-Type\text/html; charset=iso-8859-1\">");
						out.println("<meta name=\"GENERATOR\" content=\"Microsoft FrontPage 5.0\">");
						out.println("<meta name=\"Author\" content=\"Sara Bouchenak\">");
						out.println("<title>Petit Théatre de l'Informatique</title>");
								out.println("</head>");
								out.println("<body bgcolor=\"#FFFFFF\">");
								out.println("<table border=\"1\" cellpadding=\"0\" cellspacing=\"0\" style=\"border-collapse: collapse\" bordercolor=\"#FFFFFF\" width=\"100%\" id=\"AutoNumber1\" height=\"1\">");
								out.println( "<tr>");
								out.println("<td width=\"25%\" align=\"left\" valign=\"top\" height=\"1\">");
								out.println("<font face=\"Monotype Corsiva\">");
								out.println(" <img border=\"0\" src=\"/images/rideau-gauche.jpg\" width=\"151\" height=\"504\"></font></td>");
								out.println("<td width=\"50%\" align=\"center\" valign=\"top\" height=\"65\">");
								out.println("<font face=\"Monotype Corsiva\">");
								out.println("<img border=\"0\" src=\"/images/theatre.jpg\" width=\"143\" height=\"129\"></font><p>");
								out.println("<font face=\"Monotype Corsiva\" size=\"5\">Petit Théatre de l'Informatique</font></p>");
										out.println("<p align=\"left\">&nbsp;</p>");
										out.println("<p align=\"left\"><font face=\"Monotype Corsiva\" style=\"font-size: 16pt\">");
										out.println("Administration du Petit Théatre de l'Informatique - <br>");
												out.println("Accès restreint.</font></p>");
												out.println( "<ul type=\"square\">");
												out.println( "<li>");
												out.println( "<p align=\"left\"><font face=\"Monotype Corsiva\" style=\"font-size: 16pt\">");
												out.println("<a href=\"/servlet/NouvelleRepresentationServlet\">Nouvelle représentation</a><br>");
												out.println("&nbsp;</font></li>");
												out.println( "</ul>");
												out.println( "<p align=\"left\"><ul type=\"square\">");
												out.println( "<li>");
												out.println( "<p align=\"left\"><font face=\"Monotype Corsiva\" style=\"font-size: 16pt\">");
												out.println( "<a href=\"/index.html\">Accueil</a></font></li>");
												out.println( "</ul>");
												out.println("</td>");
												out.println( "<td width=\"25%\" align=\"right\" valign=\"top\" height=\"1\">");
												out.println("<font face=\"Monotype Corsiva\">");
												out.println( "<img border=\"0\" src=\"/images/rideau-droit.jpg\" width=\"153\" height=\"504\"></font></td>");
												out.println( "</tr>");
												out.println("</table>");

												out.println("</body>");
												out.println("</html>");
			
			}else{
				out.println("<p><i><font color=\"#FFFFFF\">login et mot de passe incorrects, reessayer</i></p>");
				out.println("<hr><p><font color=\"#FFFFFF\"><a href=\"/admin\">page d'identification</a></p>");
			}
			
		} catch (Exception e) {
			out.println("<p><i><font color=\"#FFFFFF\">login et mot de passe incorrects, reessayer</i></p>");
			out.println("<p><i><font color=\"#FFFFFF\">" +  e + " </i></p>");
		}
		//END TO DO
	  }
	
	  out.println("<hr><p><font color=\"#FFFFFF\"><a href=\"/index.html\">Page d'accueil</a></p>");
	  out.println("</BODY>");
	  out.close();
	
	}
	
	public void doPost(HttpServletRequest req, HttpServletResponse res)	throws ServletException, IOException
	{
	  doGet(req, res);
	}
	
	
	   /**
	* Returns information about this servlet.
	*
	* @return String information about this servlet
	*/
	
	public String getServletInfo() {
	    return "Ajoute une representation a une date donnee pour un spectacle existant";
	}
}
