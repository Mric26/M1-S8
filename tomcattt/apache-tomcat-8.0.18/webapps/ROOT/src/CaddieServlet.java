import javax.servlet.*;
import javax.servlet.http.*;
import java.io.IOException;
import modele.*;

public class CaddieServlet extends HttpServlet {

    public void doGet(HttpServletRequest req, HttpServletResponse res) throws ServletException, IOException {
      ServletOutputStream out = res.getOutputStream(); 
      //HttpSession session = req.getSession();
      Caddie caddie;
      if( req.getSession().getAttribute("caddie") != null ){
    	  caddie = (Caddie) req.getSession().getAttribute("Caddie");
      }
      else{
    	  req.getSession().setAttribute("Caddie", new Caddie());
    	  caddie = (Caddie) req.getSession().getAttribute("Caddie");
      }

	  res.setContentType("text/html");

	  out.println("<HEAD><TITLE> Caddie </TITLE></HEAD>");
	  out.println("<BODY bgproperties=\"fixed\" background=\"/images/rideau.JPG\">");
	  out.println("<font color=\"#FFFFFF\"><h1> Contenu de votre Caddie </h1>");
	  
	  try {
//		Utilisateur user = Utilitaires.Identification();
		  Ticket t = new Ticket("Test", "28/03/2015", 10, 3, 5);
		caddie.ajouterTicket(t);

		if( (caddie!= null) && (caddie.getRepresentations().size()!=0) ){
			//AFFICHAGE
			out.println("<TABLE BORDER>");
          		out.println("<TR>");
          			out.println("<TH> Num </TH>");
          			out.println("<TH> Titre de la piece </TH>");
          			out.println("<TH> Date de la representation </TH>");
          			out.println("<TH> Zone </TH>");
          			out.println("<TH> Nombre de place reservées </TH>");
          		out.println("</TR>");
          		for( int i =0; i<caddie.getRepresentations().size(); i++){
            		out.println("<TR>");
        			out.println("<TD> "+ caddie.getRepresentations().elementAt(i).getNumS() + "</TD>");
        			out.println("<TD> "+ caddie.getRepresentations().elementAt(i).getNom() + "</TD>");
        			out.println("<TD>" + caddie.getRepresentations().elementAt(i).getDate() + "</TD>");
        			out.println("<TD>" + caddie.getRepresentations().elementAt(i).getZone() + "</TD>");
        			out.println("<TD>" + caddie.getRepresentations().elementAt(i).getNbPlaces() + "</TD>");
             	    out.println("</TR>");
    	 	}
          	out.println("</TABLE>");
          	out.println("<BR/>");
          	out.println("<P> Montant de votre caddie : " + caddie.getMontant() + " </P>");
		}
		else{
			out.println("<P> Votre Caddie est vide </P>");
		}
	 	 
      }catch (Exception e) {
			out.println("<p><i><font color=\"#FFFFFF\"> Erreur lors de l'affichage du programme - Contacter un administrateur </i></p>");
			out.println("<p><i><font color=\"#FFFFFF\">" +  e + " </i></p>");
	  }

	  out.println("<hr><p><font color=\"#FFFFFF\"><a href=\"/index.html\">Accueil</a></p>");
	  out.println("</BODY>");
	  out.close();
    }

    public void doPost(HttpServletRequest req, HttpServletResponse res) throws ServletException, IOException {
	  doGet(req, res);
    }

    public String getServletInfo() {
        return "Retourne le programme du theatre";
    }

}
