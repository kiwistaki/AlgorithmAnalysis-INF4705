package tp2.inf4705;

public class Dynamique {

	private static final Dynamique instance = new Dynamique();
	
	private Dynamique(){};
	
	public static Dynamique getInstance(){return instance;}
}
