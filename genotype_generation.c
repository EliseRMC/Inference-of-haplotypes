#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "fonctions.c"

int main()
{
	srand(time(NULL));
	
	int nbIndividus, tailleGenotype, maxLociAmbigus;
	
	//L'utilisateur choisi le nombre d'individu, la taille des génotypes et le maximum de loci ambigus souhaité
	printf("Entrez le nombre d'individus : "); scanf("%d", &nbIndividus);
	printf("Entrez la taille des génotypes : "); scanf("%d", &tailleGenotype);
	printf("Entrez le nombre maximum de loci ambigu d'un génotype : "); scanf("%d", &maxLociAmbigus);
	
	remove("genotypes_alea.txt");
	remove("haplotypes_alea.txt");
	//Appel de la fonction de génération aléatoire de génotypes et d'haplotypes
	generation_genotype_aleatoire(nbIndividus, tailleGenotype, maxLociAmbigus);
	printf("\n");
	
	return 0;
}



	
