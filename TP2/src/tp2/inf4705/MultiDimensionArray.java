package tp2.inf4705;

public class MultiDimensionArray {
	int array[];
	int firstDim;
	int secondDim;
	
	public MultiDimensionArray(int numVertex, int numLongChain){
		array = new int[numLongChain*numVertex];
		firstDim = numLongChain;
		secondDim = numVertex;
		for(int i = 0; i < firstDim*secondDim; i++){
			setValueAtIndex(i,0);
		}
	}
	
	public int getValueAtIndex(int i){
		return array[i];
	}
	
	public int getMultIndex(int chain, int vertex){
		return firstDim*chain + vertex;
	}
	
	public void setValueAtIndex(int i, int value){
		array[i] = value;
	}
}
