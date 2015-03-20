import java.io.*;
import java.util.*;
import java.lang.*;
import javax.servlet.*;
import javax.servlet.http.*;
import java.text.*;

/**
 * A simple Servlet that requests parameters.
 *
 */

public class HappyBirthdayServlet extends HttpServlet {

    public void doGet(HttpServletRequest request, HttpServletResponse response)
    throws IOException, ServletException
    {
	String year, month, day;

        response.setContentType("text/html");
        PrintWriter out = response.getWriter();
        out.println("<html>");
        out.println("<head>");
        out.println("<title>Happy Birthday !</title>");
        out.println("</head>");
        out.println("<body>");
	year = request.getParameter("year");
	month= request.getParameter("month");
	day= request.getParameter("day");
        if (year != null && month != null && day!=null) {
			try {
			
            SimpleDateFormat dateFormat= new SimpleDateFormat("yyyy/MM/dd");
			Date date = new Date();
			date = dateFormat.parse(year+"/"+month+"/"+day);
			out.println("<p>Jour de naissance : "+date+".</p>");
			}catch (ParseException e) {
				e.printStackTrace();
			}
			

        } else {
           out.println("Firstname and lastname parameters not specified, Please enter some.");
            out.println("<P>");
            out.print("<form action=\"");
            out.print("birthday\" ");
            out.println("method=POST>");
            out.println("year:");
            out.println("<input type=text size=20 name=year>");
            out.println("<br>");
            out.println("month:");
            out.println("<input type=text size=20 name=month>");
            out.println("<br>");
            out.println("day:");
            out.println("<input type=text size=20 name=day>");
            out.println("<br>");
            out.println("<input type=submit>");
            out.println("</form>"); 
        }
	out.println("<a href=\"index.html\">");
	out.println("retour vers l'index");
	out.println("</a>");
        out.println("</body>");
        out.println("</html>");
    }

    public void doPost(HttpServletRequest request, HttpServletResponse response)
    throws IOException, ServletException
    {
        doGet(request, response);
    }
}
