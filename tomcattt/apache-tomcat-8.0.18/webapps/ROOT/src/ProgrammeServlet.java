
/*
 * @(#)ProgrammeServlet.java	1.0 2007/10/31
 * 
 * Copyright (c) 2007 Sara Bouchenak.
 */
import javax.servlet.*;
import javax.servlet.http.*;

import utils.Utilitaires;

import java.io.IOException;
import java.text.ParseException;
import java.text.SimpleDateFormat;
import java.util.Date;
import java.util.Vector;

import accesBD.*;
import exceptions.*;
import modele.*;

/**
 * Proramme Servlet.
 *
 * This servlet dynamically returns the theater program.
 *
 * @author <a href="mailto:Sara.Bouchenak@imag.fr">Sara Bouchenak</a>
 * @version 1.0, 31/10/2007
 */

public class ProgrammeServlet extends HttpServlet {

   /**
    * HTTP GET request entry point.
    *
    * @param req	an HttpServletRequest object that contains the request 
    *			the client has made of the servlet
    * @param res	an HttpServletResponse object that contains the response 
    *			the servlet sends to the client
    *
    * @throws ServletException   if the request for the GET could not be handled
    * @throws IOException	   if an input or output error is detected 
    *					   when the servlet handles the GET request
    */
    public void doGet(HttpServletRequest req, HttpServletResponse res)
	throws ServletException, IOException
    {
        ServletOutputStream out = res.getOutputStream();   

	  res.setContentType("text/html");

	  out.println("<HEAD><TITLE> Programme de la saison </TITLE></HEAD>");
	  out.println("<BODY bgproperties=\"fixed\" background=\"/images/rideau.JPG\">");
	  out.println("<font color=\"#FFFFFF\"><h1> Programme de la saison </h1>");

	  // Recuperation de la liste de tous les spectacles de la saison.
	  // Puis construction dynamique d'une page web decrivant ces spectacles.
	  //recuperation
	  String numSstring = req.getParameter("numS") ;
	  String dateRep= req.getParameter("dateRep") ;
	  int numS = 0;
	  if (numSstring != null) {
		  numS = Integer.parseInt(req.getParameter("numS"));		
	}
	  
	  if (numSstring == null || dateRep == null || numSstring.isEmpty() || dateRep.isEmpty()) {
		try {
		Utilisateur user = Utilitaires.Identification();
	  	Vector<Representation> res2 = new Vector<Representation>();

 	  	res2 = BDCategories.getRepresentation(user);
 	  	
 		//AFFICHAGE
	  	out.println("<TABLE BORDER>");
          	out.println("<CAPTION> Programme du Theatre </CAPTION>");
          	out.println("<TR>");
          		out.println("<TH>Num</TH>");
         	    out.println("<TH>Titre de la piece</TH>");
         	    out.println("<TH>date de representation</TH>");
         	 out.println("</TR>");
	 	 for( int i =0; i<res2.size(); i++){
          		out.println("<TR>");
          			out.println("<TD> "+ res2.elementAt(i).getNumS() + "</TD>");
          			out.println("<TD> "+ res2.elementAt(i).getNom() + "</TD>");
          			out.println("<TD>" + res2.elementAt(i).getDate() + "</TD>");
           	    out.println("</TR>");
	 	 }
          	out.println("</TABLE>");
          	out.println("<h3> Consulter la liste des places disponibles d'une représentation </h3>");
          	//Formulaire
          	out.print("<form action=\"");
        	out.print("ProgrammeServlet\" ");
        	out.println("method=POST>");
        	out.println("Num&eacute;ro de spectacle :");
        	out.println("<input type=text size=20 name=numS>");
        	out.println("<br>");
        	out.println("Date du spectacle (format : yyyy-MM-dd) :");
        	out.println("<input type=text size=20 name=dateRep>");
        	out.println("<br>");
        	out.println("<input type=submit>");
        	out.println("</form>");
          	
          	
	  } catch (CategorieException e) {
		out.println("<p><i><font color=\"#FFFFFF\"> Erreur lors de l'affichage du programme - Contacter un administrateur </i></p>");
		out.println("<p><i><font color=\"#FFFFFF\">" +  e + " </i></p>");
	  } catch (ExceptionConnexion e) {
		  out.println("<p><i><font color=\"#FFFFFF\"> Erreur lors de l'affichage du programme - Contacter un administrateur </i></p>");
		  out.println("<p><i><font color=\"#FFFFFF\">" +  e + " </i></p>");
	  } catch (ExceptionUtilisateur e) {
		out.println("<p><i><font color=\"#FFFFFF\"> Erreur lors de l'affichage du programme - Contacter un administrateur </i></p>");
		out.println("<p><i><font color=\"#FFFFFF\">" +  e + " </i></p>");
	  } catch (Exception e) {
			out.println("<p><i><font color=\"#FFFFFF\"> Erreur lors de l'affichage du programme - Contacter un administrateur </i></p>");
			out.println("<p><i><font color=\"#FFFFFF\">" +  e + " </i></p>");
		  }
	} else{
		try {
			
			Utilisateur user = Utilitaires.Identification();
		  	Vector<Place> res2 = new Vector<Place>();
	 	  	res2 = BDCategories.getPlacePourRep(user, numS, dateRep);

	 	  	
	 		//AFFICHAGE
		  	out.println("<TABLE BORDER>");
	          	out.println("<CAPTION> Liste des places disponibles pour le spectacle n° " + numS + " à la date "+ dateRep +" </CAPTION>");
	          	out.println("<TR>");
	         	    out.println("<TH>Numéro Place</TH>");
	         	    out.println("<TH>Numéro Rang</TH>");
	         	 out.println("</TR>");
		 	 for( int i =0; i<res2.size(); i++){
	          		out.println("<TR>");
	          				//(dd/MM/yyyy HH:mm:ss)
	                	  out.println("<TD> "+ res2.elementAt(i).getNoPlace() + "</TD>");
	            	      out.println("<TD>" + res2.elementAt(i).getNoRang() + "</TD>");
	           	    out.println("</TR>");
		 	 }
	          	out.println("</TABLE>");
		  } catch (ExceptionConnexion e) {
			  out.println("<p><i><font color=\"#FFFFFF\"> ExceptionConnexion lors de l'affichage du programme - Contacter un administrateur </i></p>");
		} catch (ExceptionUtilisateur e) {
			out.println("<p><i><font color=\"#FFFFFF\"> ExceptionUtilisateur lors de l'affichage du programme - Contacter un administrateur </i></p>");
		} catch (CategorieException e) {
			out.println("<p><i><font color=\"#FFFFFF\"> CategorieException lors de l'affichage du programme - Contacter un administrateur </i></p>");
		} catch (ParseException e) {
			// TODO Auto-generated catch block
			e.printStackTrace();
		}
		
	}

	  out.println("<hr><p><font color=\"#FFFFFF\"><a href=\"/index.html\">Accueil</a></p>");
	  out.println("<p><font color=\"#FFFFFF\"><a href=\"CaddieServlet\">Caddie</a></p>");
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
        return "Retourne le programme du theatre";
    }

}
