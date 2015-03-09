package grapher.ui;

import static java.lang.Math.max;
import static java.lang.Math.min;

import javax.swing.event.MouseInputAdapter;

import java.awt.Cursor;
import java.awt.Graphics2D;
import java.awt.Point;
import java.awt.Rectangle;
import java.awt.event.MouseEvent;
import java.awt.event.MouseWheelEvent;
import java.awt.event.MouseWheelListener;

class EcouteurDeSouris extends MouseInputAdapter implements MouseWheelListener {
	public Grapher graph;
	Etat etat;
	int posx;
	int posy;
	boolean rectangle;
	int pos2x;
	int pos2y;
	
	enum Etat {
		init,
		clicGaucheP,
		clicGaucheZoom5,
		clicGaucheDrag,
		molette,
		clicDroitP,
		clicDroitZoom5,
		clicDroitZoomZone
	};

    EcouteurDeSouris(Grapher g) {
    	graph = g;
    	etat = Etat.init;
    	rectangle = false;
    }

    public void mousePressed(MouseEvent e) {
    	posx = e.getX();
		posy= e.getY();
    	//clic gauche
    	if(e.getButton() == MouseEvent.BUTTON1 ){
    		graph.setCursor(new Cursor(Cursor.MOVE_CURSOR));
    		etat = Etat.clicGaucheP;
    	}
    	//clic molette
    	else if ( e.getButton() == MouseEvent.BUTTON2 ){
    		etat = Etat.molette;
    	}
    	//clic droit
    	else if ( e.getButton() == MouseEvent.BUTTON3 ){
    		etat = Etat.clicDroitP;
    	}
    	else{
    		System.out.println("Mais quel est ce bouton !!!!");
    	}
    }
    
    public void mouseDragged(MouseEvent e) {
    	switch (etat) {
		case clicGaucheP:
			etat = Etat.clicGaucheDrag;
			graph.translate( e.getX() - posx, e.getY() - posy );
    		posx = e.getX();
    		posy = e.getY();
			break;
		case clicGaucheDrag:
			etat = Etat.clicGaucheDrag;
			graph.translate( e.getX() - posx, e.getY() - posy );
    		posx = e.getX();
    		posy = e.getY();
			break;
		case clicDroitP :
			etat = Etat.clicDroitZoomZone;
			rectangle = true;
			graph.setCursor(new Cursor(Cursor.CROSSHAIR_CURSOR));
			break;
		case clicDroitZoomZone :
			pos2x = e.getX();
			pos2y = e.getY();
			graph.repaint();
			break;
		default:
			break;
		}	
    }
    
    public void paint(Graphics2D g){
    	if( rectangle ){
    		int rectx = min(posx, pos2x);
    		int recty = min(posy, pos2y);
    		int rect2x = max(posx, pos2x);
    		int rect2y = max(posy, pos2y);
    		int width = rect2x - rectx;
    		int height = rect2y - recty;
			g.drawRect(rectx, recty, width, height);
		}
    }
    
    public void mouseReleased(MouseEvent e) {
    	Point p1;
    	Point p2;
    	switch (etat) {
		case clicGaucheP :
			etat = Etat.clicGaucheZoom5;
			p1 = new Point(e.getX(), e.getY());
			graph.zoom(p1, 5);
			break;
		case molette :
			break;
		case clicDroitP:
			etat = Etat.clicDroitZoom5;
			p1 = new Point(e.getX(), e.getY());
			graph.zoom(p1, -5);
			break;
		case clicDroitZoomZone :
			rectangle = false;
			p1 = new Point(posx,posy);
    		p2 = new Point(e.getX(),e.getY());
    		graph.zoom(p1, p2);
			break;
		default:
			break;
		}
    	graph.setCursor(new Cursor(Cursor.DEFAULT_CURSOR));
    }
    
    public void mouseWheelMoved(MouseWheelEvent e){
    	Point p1 = new Point(e.getX(), e.getY());
		graph.zoom(p1, -e.getUnitsToScroll());
    }
    
}
