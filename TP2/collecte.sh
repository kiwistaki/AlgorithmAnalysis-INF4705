#!/usr/bin/env zsh

for algo in {"vorace","dynamique"}; do 
    # Pour chaque fichier de s�rie.
    for serie in {"10","14","18","22","26","30"}; do 
        # Pour chaque exemplaire dans une s�rie.
        for ex in $(ls $serie); do
			echo ${algo}_${serie}_${ex}
            # On receuille le temps d'ex�cution dans t.
            t=$(./tp.sh -a $algo -e ${serie}/${ex} -t -p)
			#p=$(timeout ./tp.sh -a $algo -e ${serie}/${ex} -p)

            # Si jamais on mesure un temps, on l'ins�re dans le bon fichier.
            if [ t != "" ]; then
                echo $t >> ./${algo}_${serie}.csv
            fi
        done
    done
done