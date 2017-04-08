package tp2.inf4705;

import java.util.ArrayList;
import java.util.LinkedList;

public final class Dynamic {

	private Dynamic(){};
	
	public static int calculateLinearExtension(LinkedList<Integer> V, ArrayList<Pair<Integer,Integer>> A, int[][] matAdj){

		LinkedList<LinkedList<Integer>> graph = new LinkedList<LinkedList<Integer>>();
		int[][] fermeture = fermetureTransitiveFloyd(matAdj);
		
		int Vsize = V.size();
		
		graph = Greedy.decomposition(V, A);
		

		
		//int[][] array = new int[graph.size()][V.size()];
		MultiDimensionArray multArray = new MultiDimensionArray(graph.size(), Vsize);
		
		multArray.setValueAtIndex(0, 1);
								
		for(int i=0; i < Vsize * graph.size(); i++)				
			{
				if(i % Vsize == 0)
				{
					multArray.setValueAtIndex(i, 1);
				}else if(i < Vsize)
				{
					multArray.setValueAtIndex(i, 1);
				}
									
			}
		
		int delta = 0;
				
		
		//Version 3.0 avec le multiDimensionalArray
		
			for(int x = 1; x < graph.size(); x++)
			{
				for(int y = 1; y < Vsize; y++ )
				{
					int totalNeighborValue = 0;
					int presentSommet = multArray.getMultIndex(x, y);
					int parentVertexIndex = multArray.getMultIndex(x, y-1);
					int parentVertexValue = multArray.getValueAtIndex(parentVertexIndex);
					int vertexXY = 0;
					
					LinkedList<Integer> chain = graph.get(x);
					
					
					if(y < chain.size())
					{
						vertexXY = graph.get(x).get(y);
					}else
					{
						vertexXY = graph.get(x).getLast();
					}
									
					for(int s = 0; s < graph.size(); s++)
					{
						if (x != s)
						{					
							int	vertexSY = graph.get(s).getLast();

							int autreSommet = multArray.getMultIndex(s, y);																										
							delta = fermeture[vertexSY][vertexXY];
																				
							//Sinon on calcule
							if (delta == 0){
							
								int autreSommetValue = multArray.getValueAtIndex(autreSommet);
								totalNeighborValue += autreSommetValue;
																			
							}
						}									
					}
					multArray.setValueAtIndex(presentSommet, multArray.getValueAtIndex(presentSommet) +  totalNeighborValue + parentVertexValue);
	
				}						
				
				
			}
			int finalValue = multArray.getValueAtIndex((graph.size() * Vsize) - 1);
			return finalValue;
	}
	
	
	
	 static int[][] fermetureTransitiveFloyd(int[][]  A){
		
		 //A[0].length?
		 for(int k=0; k < A.length; k++)
		 {
			 for(int j=0; j < A.length; j++)
			 {
				 for(int i=0; i < A.length; i++)
				 {
					 A[i][j] = Math.max(A[i][j], A[i][k] * A[k][j]);
				 }
			 }
		 }
		 
		 return A;
	}
	
	
};
