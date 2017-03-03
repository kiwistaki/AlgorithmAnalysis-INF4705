package tp1.inf4705;

import java.io.BufferedReader;
import java.io.FileReader;
import java.io.IOException;
import java.util.ArrayList;
import java.util.Date;
import java.util.List;

public class Main {
	public static void main(String args[]) throws IOException{
		
		String algo = "";
		String path = "";
		boolean trieCroissant = false;
		boolean afficheTemps = false;
		long startTime = 0;
		long endTime = 0;
		long total = 0;
		
		//Lecture des parametres d'entrees
		for(int i=0; i < args.length; i++ ){
			switch(args[i]){
			case "-a":
				algo = args[i+1];
				break;
			case "-e":
				path = args[i+1];
				break;
			case "-p":
				trieCroissant = true;
				break;
			case "-t":
				afficheTemps= true;
				break;
			default:
				break;	
			}
		}
		
		// Lecture du fichier txt
		ArrayList<Long> donnees = new ArrayList<Long>();
		BufferedReader br = new BufferedReader(new FileReader(path));
		try {
			String line = br.readLine();
		    while (line != null) {
		    	donnees.add(Long.parseLong(line));
		        line = br.readLine();
		    }
		} finally {
		    br.close();
		}
		
		List<Long> donneeTrie= new ArrayList<Long>();
		CountingSort cs;
		QuickSort qs;
		
		switch(algo){
			case "counting":
				startTime = (new Date()).getTime();
				cs = CountingSort.getInstance();
				donneeTrie = cs.sort(donnees);
				endTime = (new Date()).getTime();
				total = endTime - startTime;
				break;
			case "quick":
				startTime = (new Date()).getTime();
				qs = QuickSort.getInstance();
				donneeTrie = qs.quickSort(donnees, true,false);
				endTime = (new Date()).getTime();
				total = endTime - startTime;
				break;
			case "quickRandom":
				total = 0;
				qs = QuickSort.getInstance();
				for(int i = 0; i < 10; i++){
					startTime = (new Date()).getTime();
					donneeTrie = qs.quickSort(donnees, false,false);
					endTime = (new Date()).getTime();
					total += (endTime - startTime);
				}
				total = total / 10;
				break;
			case "quickSeuil":
				startTime = (new Date()).getTime();
				qs = QuickSort.getInstance();
				donneeTrie = qs.quickSort(donnees, true,true);
				endTime = (new Date()).getTime();
				total = endTime - startTime;
				break;
			case "quickRandomSeuil":
				total = 0;
				qs = QuickSort.getInstance();
				for(int i = 0; i < 10; i++){
					startTime = (new Date()).getTime();
					donneeTrie = qs.quickSort(donnees, false,true);
					endTime = (new Date()).getTime();
					total += (endTime - startTime);
				}
				total = total / 10;
				break;
			default:
				break;
		}
		
		
		if(trieCroissant){
			for(int i = 0; i< donneeTrie.size();i++){
				System.out.println(donneeTrie.get(i).toString());
			}
		}
		
		if(afficheTemps){
			//affiche temps du timer
			System.out.println(total);
		}
	}
}
