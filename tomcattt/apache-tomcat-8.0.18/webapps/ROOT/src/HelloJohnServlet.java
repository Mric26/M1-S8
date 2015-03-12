import java.io.*;
import javax.servlet.*;
import javax.servlet.http.*;

/**
 * A simple Hello World Servlet.
 *
 */

public class HelloJohnServlet extends HttpServlet {

    public void doGet(HttpServletRequest request, HttpServletResponse response)
    throws IOException, ServletException
    {
        response.setContentType("text/html");
        PrintWriter out = response.getWriter();
        out.println("<html>");
        out.println("<head>");
        out.println("<title>Hello World!</title>");
        out.println("</head>");
        out.println("<body>");
        out.println("<h1>Bonjour mon cher John, ou devrais-je dire Malkovitch !!!</h1>");
        out.println("</body>");
        out.println("</html>");
    }
}
