#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "fonctions.c"

int main()
{
	
	int nbIndividus, tailleGenotype;
	
	//L'utilisateur choisi le nombre d'individu, la taille des génotypes et le maximum de loci ambigus souhaité
	printf("Entrez le nombre d'individus listés dans le fichier : "); scanf("%d", &nbIndividus);
	printf("Entrez la taille des génotypes listés dans le fichier : "); scanf("%d", &tailleGenotype);
	
	//Appel de la fonction de génération aléatoire de génotypes et d'haplotypes
	lire_fichier_genotypes(nbIndividus, tailleGenotype);
	printf("\n");
	
	return 0;
}



	
