package tp2.inf4705;

public class RetourArriere {
	
	private static final RetourArriere instance = new RetourArriere();
	
	private RetourArriere(){};
	
	public static RetourArriere getInstance(){return instance;}
}
