package grapher.ui;

import javax.swing.event.MouseInputAdapter;

import java.awt.Cursor;
import java.awt.Point;
import java.awt.event.MouseEvent;
import java.awt.event.MouseWheelEvent;
import java.awt.event.MouseWheelListener;

class EcouteurDeSouris extends MouseInputAdapter implements MouseWheelListener {
	public Grapher graph;
	int etat;
	int posx;
	int posy;

    EcouteurDeSouris(Grapher g) {
    	graph = g;
    	etat = 0;
    }

    public void mousePressed(MouseEvent e) {
    	posx = e.getX();
		posy= e.getY();
    	//clic gauche
    	if(e.getButton() == MouseEvent.BUTTON1 ){
    		graph.setCursor(new Cursor(Cursor.MOVE_CURSOR));
    		etat = 1;
    	}
    	//clic molette
    	else if ( e.getButton() == MouseEvent.BUTTON2 ){
    		etat = 2;
    	}
    	//clic droit
    	else if ( e.getButton() == MouseEvent.BUTTON3 ){
    		graph.setCursor(new Cursor(Cursor.CROSSHAIR_CURSOR));
    		etat = 3;
    	}
    	else{
    		System.out.println("Mais quel est ce bouton !!!!");
    	}
    }
    
    public void mouseDragged(MouseEvent e) {
    	if( etat == 1 ){
    		graph.translate( e.getX() - posx, e.getY() - posy );
    		posx = e.getX();
    		posy = e.getY();
    	}
    	else if ( etat == 2){
    		Point p1 = new Point(posx,posy);
    		graph.zoom(p1, e.getY()-posy );
    	}
    	else if ( etat == 3){
    	}
    	else{
    		System.out.println("Autre !!!");
    	}
    	
    }
    
    public void mouseClicked(MouseEvent e) {
    }
    
    public void mouseReleased(MouseEvent e) {
    	if(etat == 3){
    		Point p1 = new Point(posx,posy);
    		Point p2 = new Point(e.getX(),e.getY());
    		graph.zoom(p1, p2);
    	}
    	graph.setCursor(new Cursor(Cursor.DEFAULT_CURSOR));
    }
    
    public void mouseWheelMoved(MouseWheelEvent e){
    	Point p1 = new Point(e.getX(), e.getY());
		graph.zoom(p1, e.getUnitsToScroll());
    }
    
}
