package modele;

public class Place {
	
	private int noRang;
	private int noPlace;
	
	public Place(int p, int r){
		setNoRang(r);
		setNoPlace(p);
	}

	public int getNoRang() {
		return noRang;
	}

	public void setNoRang(int noRang) {
		this.noRang = noRang;
	}

	public int getNoPlace() {
		return noPlace;
	}

	public void setNoPlace(int noPlace) {
		this.noPlace = noPlace;
	}
	

}
