import javax.servlet.*;
import javax.servlet.http.*;

import java.io.IOException;
import java.sql.Date;

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
		Date d1 = new Date(115, 04, 8);	
		Date d2 = new Date(115, 03, 28);
		Ticket t = new Ticket(1, 1, d1, 1, 1, d2, 1);
		caddie.ajouterTicket(t);

		if( (caddie!= null) && (caddie.getRepresentations().size()!=0) ){
			//AFFICHAGE
			out.println("<TABLE BORDER>");
          		out.println("<TR>");
          			out.println("<TH> NoSerie </TH>");
          			out.println("<TH> NumS </TH>");
          			out.println("<TH> DateRep </TH>");
          			out.println("<TH> NoPlace </TH>");
          			out.println("<TH> NoPRang </TH>");
          			out.println("<TH> DateEmission </TH>");
          			out.println("<TH> NoDossier </TH>");
          		out.println("</TR>");
          		for( int i =0; i<caddie.getRepresentations().size(); i++){
            		out.println("<TR>");
        			out.println("<TD> "+ caddie.getRepresentations().elementAt(i).getNoSerie() + "</TD>");
        			out.println("<TD> "+ caddie.getRepresentations().elementAt(i).getNumS() + "</TD>");
        			out.println("<TD> "+ caddie.getRepresentations().elementAt(i).getDateRep() + "</TD>");
        			out.println("<TD> "+ caddie.getRepresentations().elementAt(i).getNoPlace() + "</TD>");
        			out.println("<TD> "+ caddie.getRepresentations().elementAt(i).getNoRang() + "</TD>");
        			out.println("<TD> "+ caddie.getRepresentations().elementAt(i).getDateEmission() + "</TD>");
        			out.println("<TD> "+ caddie.getRepresentations().elementAt(i).getNoDossier() + "</TD>");
             	    out.println("</TR>");
    	 	}
          	out.println("</TABLE>");
          	out.println("<BR/>");
          	out.println("<P> Montant de votre caddie : " + caddie.getMontant() + " </P>");
            //Validation
          	out.println(" <a href=CaddieValideServlet target=_self> <input type=button value=Valider> </a> ");
		}
		else{
			out.println("<P> Votre Caddie est vide </P>");
		}
	 	 
      }catch (Exception e) {
			out.println("<p><i><font color=\"#FFFFFF\"> Erreur lors de l'affichage du programme - Contacter un administrateur </i></p>");
			out.println("<p><i><font color=\"#FFFFFF\">" +  e + " </i></p>");
	  }

	  out.println("<hr><p><font color=\"#FFFFFF\"><a href=\"/index.html\">Accueil</a></p>");
	  out.println("<p><font color=\"#FFFFFF\"><a href=\"CaddieServlet\">Caddie</a></p>");
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
