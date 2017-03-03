package tp2.inf4705;

import java.io.BufferedReader;
import java.io.FileReader;
import java.io.IOException;
import java.util.ArrayList;
import java.util.Date;
import java.util.LinkedList;

public class Main {
	public static void main(String args[]) throws IOException{
		
		String algo = "";
		String path = "";
		boolean print = false;
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
				print = true;
				break;
			case "-t":
				afficheTemps= true;
				break;
			default:
				break;	
			}
		}
		
		// Lecture du fichier 
		BufferedReader br = new BufferedReader(new FileReader(path));
		ArrayList<Pair<Integer,Integer>> arcs = new ArrayList<Pair<Integer,Integer>>();	
		LinkedList<Integer> vertices = new LinkedList<Integer>();
		try {
			String line = br.readLine();
			//skip first line since useless
			line = br.readLine();
		    while (line != null) {
		    	String[] tokens = line.split(" ");
		    	if(!vertices.contains(Integer.parseInt(tokens[0])))
		    		vertices.add(Integer.parseInt(tokens[0]));
		    	if(!vertices.contains(Integer.parseInt(tokens[1])))
		    		vertices.add(Integer.parseInt(tokens[1]));
		    	arcs.add(new Pair<Integer,Integer>(Integer.parseInt(tokens[0]), Integer.parseInt(tokens[1])));
		        line = br.readLine();
		    }
		} finally {
		    br.close();
		}
		
		LinkedList<Integer> res = new LinkedList<Integer>();
		switch(algo){
		case "vorace":
			startTime = (new Date()).getTime();
			Vorace vor = Vorace.getInstance();
			res = vor.longestChain(vertices, arcs);
			endTime = (new Date()).getTime();
			total = endTime - startTime;
			break;
		case "dynamique":
			startTime = (new Date()).getTime();
			Dynamique dym = Dynamique.getInstance();
			endTime = (new Date()).getTime();
			total = endTime - startTime;
			break;
		case "retourArriere":
			startTime = (new Date()).getTime();
			RetourArriere ra = RetourArriere.getInstance();
			endTime = (new Date()).getTime();
			total = endTime - startTime;
			break;
		default:
			break;
		}
		
		if(print){
			for(Integer el : res)
				System.out.println(el.toString());
		}
		
		if(afficheTemps){
			//affiche temps du timer
			System.out.println(total);
		}
	}
}
