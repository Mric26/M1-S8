import javax.servlet.*;
import javax.servlet.http.*;

import exceptions.CategorieException;
import exceptions.ExceptionConnexion;
import exceptions.ExceptionUtilisateur;
import utils.Utilitaires;

import java.io.IOException;

import modele.*;

public class CaddieValideServlet extends HttpServlet {

    public void doGet(HttpServletRequest req, HttpServletResponse res) throws ServletException, IOException {
    	
      ServletOutputStream out = res.getOutputStream(); 
      Utilisateur user = null;
	try {
		user = Utilitaires.Identification();
	} catch (ExceptionConnexion e1) {
		// TODO Auto-generated catch block
		e1.printStackTrace();
	} catch (ExceptionUtilisateur e1) {
		// TODO Auto-generated catch block
		e1.printStackTrace();
	}
      Caddie caddie;
      
      if( req.getSession().getAttribute("Caddie") != null ){
    	  caddie = (Caddie) req.getSession().getAttribute("Caddie");
      }
      else{
    	  req.getSession().setAttribute("Caddie", new Caddie());
    	  caddie = (Caddie) req.getSession().getAttribute("Caddie");
      }

      try {
		caddie.confirmerCommande(user,out);
      } catch (CategorieException | ExceptionConnexion e) {
    	  out.println("<p><i><font color=\"#FFFFFF\"> Erreur lors de la confirmation de la commande - Contacter un administrateur </i></p>");
  		  out.println("<p><i><font color=\"#FFFFFF\">" +  e + " </i></p>");
      }
      
	  res.setContentType("text/html");
	  out.println("<HEAD><TITLE> Caddie </TITLE></HEAD>");
	  out.println("<BODY bgproperties=\"fixed\" background=\"/images/rideau.JPG\">");
	  out.println("<font color=\"#FFFFFF\"><h1> Caddie Validé </h1>");

	  out.println("<P> Caddie validé </P>");
	  out.println("<P> Merci de votre achat. </P>");

	  out.println("<hr><p><font color=\"#FFFFFF\"><a href=\"/index.html\">Accueil</a></p>");
	  out.println("<p><font color=\"#FFFFFF\"><a href=\"CaddieServlet\">Caddie</a></p>");
	  out.println("</BODY>");
	  out.close();
    }

    public void doPost(HttpServletRequest req, HttpServletResponse res) throws ServletException, IOException {
	  doGet(req, res);
    }

    public String getServletInfo() {
        return "Le contenu du Caddie";
    }

}
