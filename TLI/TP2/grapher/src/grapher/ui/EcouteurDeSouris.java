package grapher.ui;

import javax.swing.event.MouseInputAdapter;

import java.awt.Color;
import java.awt.Cursor;
import java.awt.Dimension;
import java.awt.Font;
import java.awt.FontMetrics;
import java.awt.Graphics;
import java.awt.Image;
import java.awt.Point;
import java.awt.Rectangle;
import java.awt.Shape;
import java.awt.event.MouseEvent;
import java.awt.event.MouseWheelEvent;
import java.awt.event.MouseWheelListener;
import java.awt.image.ImageObserver;
import java.text.AttributedCharacterIterator;

class EcouteurDeSouris extends MouseInputAdapter implements MouseWheelListener {
	public Grapher graph;
	int etat;
	int posx;
	int posy;
	boolean zoom= false;

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
    		zoom= true;
    	}
    	else{
    		System.out.println("Autre !!!");
    	}
    	
    }
    
    public void mouseClicked(MouseEvent e) {
    }
    
    public void mouseReleased(MouseEvent e) {
    	if(etat == 1){ //zoom de 5%
    		Dimension d= graph.getPreferredSize();
    		int x, y;
    		x= (int)((d.width -d.width*0.05)/2);
    		y= (int)((d.height -d.height*0.05)/2);
    		Point p1 = new Point(e.getX() -x,e.getY() -y);
    		Point p2 = new Point(e.getX() +x,e.getY() +y);
    		graph.zoom(p1, p2);
    	}else if(etat == 3){
    		if (zoom){ //zoom selon une région rectangulaire
    			Point p1 = new Point(posx,posy);
        		Point p2 = new Point(e.getX(),e.getY());
        		graph.zoom(p1, p2);
        		zoom = false;
    		}else{ //dézoom de 5%
    			Dimension d= graph.getPreferredSize();
        		int x, y;
        		x= (int)((d.width +d.width*0.05)/2);
        		y= (int)((d.height +d.height*0.05)/2);
        		Point p1 = new Point(e.getX() -x,e.getY() -y);
        		Point p2 = new Point(e.getX() +x,e.getY() +y);
        		graph.zoom(p1, p2);
    		}
    		
    	}
    	graph.setCursor(new Cursor(Cursor.DEFAULT_CURSOR));
    }
    
    public void mouseWheelMoved(MouseWheelEvent e){
    	Point p1 = new Point(e.getX(), e.getY());
		graph.zoom(p1, e.getUnitsToScroll());
    }
    
}
