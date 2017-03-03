package tp1.inf4705;

import java.util.LinkedList;
import java.util.List;
import java.util.Random;

public class QuickSort {

	private QuickSort(){	
	}
	
	private static final QuickSort instance = new QuickSort();

	
	public static QuickSort getInstance(){
		return instance;
	}
	
	//Code inspire de http://rosettacode.org/wiki/Sorting_algorithms/Quicksort#Java
	public  <E extends Comparable<? super E>> List<E> quickSort(List<E> arr, boolean pivotFirst, boolean seuil) {
		if (!arr.isEmpty()) {
			Random rand = new Random();
        	int randomPivot = rand.nextInt(arr.size());
        	
        	E pivot;
        	int seuilValue = 32;
			
        	//Le pivot choisi sera le premier de la liste ou bien un au hasard, selon l'algorithme appelé
        	if(pivotFirst){
        		pivot = arr.get(0); 
        	}else{
        		pivot = arr.get(randomPivot);
        	}
        	
        	if(seuil && (arr.size() <= seuilValue)){
        		insertionSort(arr, arr.size());
        	}else{
		 
			    List<E> less = new LinkedList<E>();
			    List<E> pivotList = new LinkedList<E>();
			    List<E> more = new LinkedList<E>();
			 
			    // Partition
			    for (E i: arr) {
			        if (i.compareTo(pivot) < 0)
			            less.add(i);
			        else if (i.compareTo(pivot) > 0)
			            more.add(i);
			        else
			            pivotList.add(i);
			    }
			 
			    // Recursively sort sublists
			    less = quickSort(less,pivotFirst,seuil);
			    more = quickSort(more,pivotFirst,seuil);
			 
			    // Concatenate results
			    less.addAll(pivotList);
			    less.addAll(more);
			    return less;
          }
		}
		return arr;
		 
	}

	public <E extends Comparable<? super E>> List<E> insertionSort(List<E> arr, int length) {
		
	    for (int j = 1; j < length; j++){ 
	        E key = arr.get(j); 
	        int i = j-1; 
	        while ( (i > -1) && ( arr.get(i).compareTo(key) > 0 ) ) { 	            	 
	        	arr.set(i+1, arr.get(i));
	        	i--; 
	        } 
	        arr.set(i+1, key); 
	    }
	    return arr;
    }
}
