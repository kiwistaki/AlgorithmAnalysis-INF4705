package tp2.inf4705;

import java.util.ArrayList;
import java.util.LinkedList;

public final class Backtracking {

	private Backtracking(){};
	
	public static int getLinearExtension(LinkedList<Integer> V, ArrayList<Pair<Integer,Integer>> A ){
		int linearExtension = 0;
		linearExtension = calculateLinearExtension(V,A);
		return linearExtension;
	};
	
	public static int calculateLinearExtension(LinkedList<Integer> V, ArrayList<Pair<Integer,Integer>> A ){
		int linExt = 0;
		LinkedList<Integer> summitVertices = new LinkedList<Integer>();
		summitVertices = getSummitVertices(V,A);
		
		//Copy of arcs list
		ArrayList<Pair<Integer,Integer>> Acopy = new ArrayList<Pair<Integer,Integer>>();
		for(Pair<Integer,Integer> e : A){
			Acopy.add(new Pair<Integer,Integer>(e.getFirst(), e.getSecond()));
		}
		
		if(V.size() > 0){
			for(Integer o : summitVertices){
				//Retrait de V et A 
				V.remove(o);
				//System.out.println(o);
				LinkedList<Pair<Integer,Integer>> temp = new LinkedList<Pair<Integer,Integer>>(); 
				for(Pair<Integer,Integer> e : Acopy){
					if(e.getFirst() == o || e.getSecond() == o){
						A.remove(e);
						temp.add(e);
					}
				}
				
				linExt += calculateLinearExtension(V,A);
				
				//rajout dans V et A
				V.add(o);
				for(Pair<Integer,Integer> e : temp){
					A.add(e);
				}			
			}
		}else{
			linExt += 1;
		}
		return linExt;
	}
	
	private static LinkedList<Integer> getSummitVertices(LinkedList<Integer> V, ArrayList<Pair<Integer,Integer>> A){
		LinkedList<Integer> res = new LinkedList<Integer>();
		for(int i = 0; i < V.size(); i++)
			res.add(V.get(i));
		
		for(Pair<Integer,Integer> element : A){
			if(res.contains(element.getSecond())){
				res.remove(element.getSecond());
			}
			
		}
	
		return res;
	}
}
