package tp2.inf4705;

public class Pair <A,B> {
	private final A first;
	private final B second;
	
	public Pair(A left, B right){
		this.first = left;
		this.second = right;
	}
	
	public A getFirst(){ return first; }
	
	public B getSecond(){ return second; }
	
	@Override
	public int hashCode(){ return first.hashCode() ^ second.hashCode() ;}
	
	@Override
	public boolean equals(Object o){
		if (!(o instanceof Pair)) return false;
	    Pair<A,B> pairo = (Pair<A, B>) o;
	    return this.first.equals(pairo.getFirst()) &&
	           this.second.equals(pairo.getSecond());
	}
}
