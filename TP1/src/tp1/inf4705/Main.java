package tp1.inf4705;

import java.io.BufferedReader;
import java.io.Reader;

public class Main {
	public static void main(String args[]){
		
		//Lecture des parametres d'entrees
		String[] params = new String[args.length];
		for(int i = 0; i < args.length;i++){
			params[i] = args[i];
		}
		
		
		int i = 0;
		while(i < 30){
			// Case pour 1000 donnees
			String str = params[1]+"/testset_1000_"+i+".txt";
			//Lecture des fichiers textes
			/*BufferedReader br = new BufferedReader(new Reader(str));
			try{
				int[] array = new int[1000];
			}finally{
				br.close();
			}
			
			// Case pour 5000 donnees
			str = params[1]+"/testset_5000_"+i+".txt";
			//Lecture des fichiers textes
			br = new BufferedReader(new Reader(str));
			try{
				int[] array = new int[5000];
			}finally{
				br.close();
			}
			
			// Case pour 10000 donnees
			str = params[1]+"/testset_10000_"+i+".txt";
			//Lecture des fichiers textes
			br = new BufferedReader(new Reader(str));
			try{
				int[] array = new int[10000];
			}finally{
				br.close();
			}*/
			
			i++;
		}
		
		
		
		
		System.out.println("Hello world!");
	}
}
