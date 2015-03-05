

public class inter{
	
	private double tab[20]; //table de noeuds
	
	double inter::omega(int i, int k, double t){
		if(tab[i] < tab[i+k]){
			return ((t - tab[i])/(tab[i+k] + tab[i]));
		}else{
			return 0;
		}
	}
	
	double inter::aine(int i, int k, double t){
		if(k == 0){
			if(t >= tab[i] && t =< tab[i+1]){
				return 1;
			}else{
				return 0;
			}
		}else{
			return (omega(i, k, t)*aine(i, k-1, t) + (1 - omega(i+1, k, t))*aine(i+1, k-1, t));
		}
	}

	
	
}
