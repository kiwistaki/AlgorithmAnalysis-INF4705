package tp2.inf4705;
import java.util.*;

public class Vorace {
	
	private static final Vorace instance = new Vorace();
	
	private Vorace(){};
	
	public static Vorace getInstance(){return instance;}

	public void decomposition(LinkedList<Integer> V, ArrayList<Pair<Integer,Integer>> A ){
		
		LinkedList<LinkedList<Integer>> L = new LinkedList<LinkedList<Integer>>();
		LinkedList<Integer> c = longestChain(V, A);
		
		while(c.size() > 0){
			
			for(Integer vertex : c){
				
				if(V.contains(vertex)){
					V.remove(vertex);
				}
				
				for(Pair<Integer,Integer> arc : A){
					if(arc.getFirst() == vertex || arc.getSecond() == vertex){
						
						A.remove(arc);
					}
				}
			}
			L.push(c);
			c = longestChain(V,A);
		}
/*	WEIRD, a re-checker.	
 * for(Integer v : V)
		{
			LinkedList<Integer> sommets = new LinkedList<Integer>();
			sommets.push(v);
			L.push(sommets);
		} */
	}
	
	public LinkedList<Integer> longestChain(LinkedList<Integer> V, ArrayList<Pair<Integer,Integer>> A){
		
		LinkedList<Integer> c = new LinkedList<Integer>();
		int[] pred = new int[V.size()];
		
		for(Integer item : V){
			pred[item] = -1;			
		}
			
		Deque<Integer> Q = new LinkedList<Integer>();
		Q = initializeQ(V, A);
		
		Integer last = -1;
		while(Q.size() > 0){
			
			last = Q.removeFirst();
			
			for(Pair<Integer,Integer> element: A){
				pred[element.getSecond()] = element.getFirst();
				if(Q.contains(element.getSecond())){
					Q.remove(element.getSecond());
					Q.addLast(element.getSecond());					
				}else{
					Q.addLast(element.getSecond());
				}
			}			
		}		
		while(last != 1){
			c.push(last);
			last = pred[last];
		}
		return c;
	}

	public LinkedList<Integer> initializeQ(LinkedList<Integer> VCopy, ArrayList<Pair<Integer,Integer>> A)	{
		
		LinkedList<Integer> res = new LinkedList<Integer>();
		for(int i = 0; i < VCopy.size(); i++)
			res.add(VCopy.get(i));
		
		for(Pair<Integer,Integer> element : A){
			if(res.contains(element.getSecond())){
				res.remove(element.getSecond());
			}
			
		}
	
		return res;
	}
	
}
