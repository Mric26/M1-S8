import javax.servlet.*;
import javax.servlet.http.*;

import exceptions.CategorieException;
import exceptions.ExceptionConnexion;
import exceptions.ExceptionUtilisateur;
import modele.Caddie;
import modele.Representation;
import modele.Ticket;
import modele.Utilisateur;
import utils.Utilitaires;
import accesBD.BDCategories;

import java.io.IOException;
import java.text.ParseException;
import java.text.SimpleDateFormat;
import java.util.Date;
import java.util.Vector;

public class ReservationServlet extends HttpServlet {
	//avec zone donnée, pour une représentation donnée par son numéro et le numéro du spectacle associé

    public void doGet(HttpServletRequest req, HttpServletResponse res)
	throws ServletException, IOException
    {
	  String dateRep,numSString,zoneString;
	  int numS =0;
	  int zone = 0;
          ServletOutputStream out = res.getOutputStream();   

          Caddie caddie;
          if( req.getSession().getAttribute("Caddie") != null ){
        	  caddie = (Caddie) req.getSession().getAttribute("Caddie");
        	  //out.println("session existante");
          }
          else{
        	  req.getSession().setAttribute("Caddie", new Caddie());
        	  caddie = (Caddie) req.getSession().getAttribute("Caddie");
        	  //out.println("pas session");
          }
	  res.setContentType("text/html");

	  out.println("<HEAD><TITLE> Reservation </TITLE></HEAD>");
	  out.println("<BODY bgproperties=\"fixed\" background=\"/images/rideau.JPG\">");
	  out.println("<font color=\"#FFFFFF\"><h1> Reserver une place </h1>");
	  
	  numSString = req.getParameter("numS");
	  if (numSString != null) {
		  numS		= Integer.parseInt( numSString );	
	  }
	  dateRep		= req.getParameter("dateRep");
	  zoneString = req.getParameter("zone");
	  if (zoneString != null) {
		  zone	= Integer.parseInt( zoneString );		
	  }
	  if (zoneString == null || dateRep == null || numSString == null) {
		  Utilisateur user = null;
		  Vector<Representation> res2 = new Vector<Representation>();
		try {
			user = Utilitaires.Identification();
	 	  	res2 = BDCategories.getRepresentation(user);
		} catch (ExceptionConnexion | ExceptionUtilisateur e) {
			e.printStackTrace();
		} catch (CategorieException e) {
			e.printStackTrace();
		}
		out.println("<TABLE BORDER>");
		out.println("<CAPTION> Programme du Theatre </CAPTION>");
		out.println("<TR>");
		out.println("<TH>Num</TH>");
   	    out.println("<TH>Titre de la piece</TH>");
   	    out.println("<TH>date de representation</TH>");
   	    int nbZone = 0;
		try {
			nbZone = BDCategories.nbZone(user);
		} catch (CategorieException | ExceptionConnexion e) {
			e.printStackTrace();
		}
   	    for (int i = 1; i < nbZone+1; i++) {
   	    	out.println("<TH>Place dispo zone " + i + " </TH>");
		}
   	    out.println("</TR>");
	 	for( int i =0; i<res2.size(); i++){
        		out.println("<TR>");
    			out.println("<TD> "+ res2.elementAt(i).getNumS() + "</TD>");
    			out.println("<TD> "+ res2.elementAt(i).getNom() + "</TD>");
    			out.println("<TD>" + res2.elementAt(i).getDate() + "</TD>");
    			for (int j = 1; j < nbZone+1; j++) {
    				int place = 0;
					try {;
						String dateStirng = res2.elementAt(i).getDate();
						String[] dateSplit = dateStirng.split(" ");
//						out.println("dateSPlit = "+dateSplit[0]);
						place = BDCategories.nbPlacesDispoDansZone(user, res2.elementAt(i).getNumS(), dateSplit[0], j);
					} catch (CategorieException | ExceptionConnexion e) {
					}
    	   	    	out.println("<TD>" + place + "</TD>");
    			}
         	    out.println("</TR>");
	 	}
        out.println("</TABLE>");
		   
            	out.println("<font color=\"#FFFFFF\">Veuillez saisir les informations relatives &agrave; la nouvelle repr&eacute;sentation :");
            	out.println("<P>");
            	out.print("<form action=\"");
            	out.print("ReservationServlet\" ");
            	out.println("method=POST>");
            	out.println("Num&eacute;ro de spectacle :");
            	out.println("<input type=text size=20 name=numS>");
            	out.println("<br>");
            	out.println("Date de la repr&eacute;sentation :");
            	out.println("<input type=text size=20 name=dateRep>");
            	out.println("<br>");
            	out.println("Numéro de zone :");
            	out.println("<input type=text size=20 name=zone>");
            	out.println("<br>");
//            	out.println("Zone :");
//            	out.println("<input type=text size=20 name=zone>");
//            	out.println("<br>");
            	out.println("<input type=submit>");
            	out.println("</form>");
	  } else {
	  	// TO DO
		//  ajouter un ticket au caddie
		  	out.println("<p> numS = " + numS + "</p>");
			String[] dateSplit = dateRep.split(" ");
			out.println("<p> dateRep = " + dateSplit[0] + "</p>");
			out.println("<p> nuMZ = " + zone + "</p>");
			Ticket t = new Ticket(0, numS, dateSplit[0], 0, 0, zone);
			caddie.ajouterTicket(t);
			out.println("<p> " + caddie.getNoCaddie() + "</p>");
		
		//END TO DO */
	  }

		  
	  out.println("<hr><p><font color=\"#FFFFFF\"><a href=\"/admin/admin.html\">Page d'administration</a></p>");
	  out.println("<hr><p><font color=\"#FFFFFF\"><a href=\"/index.html\">Page d'accueil</a></p>");
	  out.println("</BODY>");
	  out.close();

    }

   /**
    * HTTP POST request entry point.
    *
    * @param req	an HttpServletRequest object that contains the request 
    *			the client has made of the servlet
    * @param res	an HttpServletResponse object that contains the response 
    *			the servlet sends to the client
    *
    * @throws ServletException   if the request for the POST could not be handled
    * @throws IOException	   if an input or output error is detected 
    *					   when the servlet handles the POST request
    */
    public void doPost(HttpServletRequest req, HttpServletResponse res)
	throws ServletException, IOException
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
