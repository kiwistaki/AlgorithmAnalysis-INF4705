package tp2.inf4705;
import java.util.*;

public final class Greedy {
	
	private Greedy(){};
	
	public static int calculerNombreExtension(LinkedList<Integer> V, ArrayList<Pair<Integer,Integer>> A ){
		double S = V.size();
		double H = 0;
		LinkedList<LinkedList<Integer>> G = decomposition(V,A);
		
		for(LinkedList<Integer> el : G){
			double ci = el.size();
			H += (-ci/S)*(Math.log(ci/S)/Math.log(2));
		}
		H = H * 0.5* S;
		
		int res = (int)Math.floor(Math.pow(2, H));
		return res;
	}

	public static LinkedList<LinkedList<Integer>> decomposition(LinkedList<Integer> V, ArrayList<Pair<Integer,Integer>> A ){
		
		int size = findMax(V);
		LinkedList<LinkedList<Integer>> L = new LinkedList<LinkedList<Integer>>();
		LinkedList<Integer> c = longestChain(V, A, size);
		ArrayList<Pair<Integer,Integer>> Atmp = new ArrayList<Pair<Integer,Integer>>();
		
		
		while(c.size() > 0){
			
			//Initialisation de Atmp = A
			for(Pair<Integer,Integer> el : A){
				Atmp.add(new Pair<Integer,Integer>(el.getFirst(), el.getSecond()));
			}
			
			for(Integer vertex : c){
				
				if(V.contains(vertex)){
					//V.add(V.indexOf(vertex),null);
					V.remove(vertex);
				}
				
				for(Pair<Integer,Integer> arc : Atmp){
					if(arc.getFirst() == vertex || arc.getSecond() == vertex){						
						A.remove(arc);
					}
				}
			}
			L.push(c);
			c = longestChain(V,A,size);
		}
		
		for(Integer v : V)
		{
			LinkedList<Integer> sommets = new LinkedList<Integer>();
			sommets.push(v);
			L.push(sommets);
		}
		
		return L;
	}
	
	public static LinkedList<Integer> longestChain(LinkedList<Integer> V, ArrayList<Pair<Integer,Integer>> A, int size){
		
		LinkedList<Integer> c = new LinkedList<Integer>();
		int[] pred = new int[size+1];
		
		for(Integer item : V){
			pred[item] = -1;			
		}
			
		Deque<Integer> Q = new LinkedList<Integer>();
		Q = initializeQ(V, A);
		
		Integer last = -1;
		while(Q.size() > 0){
			
			last = Q.removeFirst();
			
			for(Pair<Integer,Integer> element: A){
				if(element.getFirst() == last){
					pred[element.getSecond()] = element.getFirst();
					if(Q.contains(element.getSecond())){
						Q.remove(element.getSecond());
						Q.addLast(element.getSecond());					
					}else{
						Q.addLast(element.getSecond());
					}
				}
			}			
		}		
		while(last != -1){
			c.push(last);
			last = pred[last];
		}
		return c;
	}

	public static LinkedList<Integer> initializeQ(LinkedList<Integer> VCopy, ArrayList<Pair<Integer,Integer>> A)	{
		
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
	
	public static int findMax(LinkedList<Integer> V){
		int max = -1;
		for(Integer e : V){
			if(e>max)
				max = e;
		}
		return max;
	}
	
}
