package tp1.inf4705;

import java.util.List;

public class CountingSort 
{

	private CountingSort()
	{
		
	}
	
	private static final CountingSort instance = new CountingSort();

	
	public static CountingSort getInstance()
	{
		return instance;
	}

	// Code inspire de http://rosettacode.org/wiki/Sorting_algorithms/Counting_sort#Java
	public List<Long> sort(List<Long> array){
		Long[] minMax = getMinMaxValues(array);
		Long min = minMax[0];
		Long max = minMax[1];
		
		long interval = max - min + 1;
		// Si impossible a traiter
		if (interval > Integer.MAX_VALUE)
			return QuickSort.getInstance().insertionSort(array, array.size());
		
		
		long[] count = new long[(int)(max-min+1)];
		
		for(long i : array){
			count[(int)(i-min)]++;
		}
		int z= 0;
		for(long i= min;i <= max;i++){
			while(count[(int)(i - min)] > 0){
				array.set(z,i);
				z++;
				count[(int)(i - min)]--;
			}
		}
		return array;
	}
	
	private Long[] getMinMaxValues(List<Long> array){
		Long[] minMax = new Long[2];
		Long min = array.get(0);
		Long max = array.get(0);
		for(int i  = 1; i < array.size(); i++){
			if(array.get(i)> max)
				max = array.get(i);
			if(array.get(i) < min)
				min = array.get(i);
		}
		minMax[0] = min;
		minMax[1] = max;
		return minMax;
	}
	
}