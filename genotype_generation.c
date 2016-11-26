#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "fonctions.c"

int main()
{
	srand(time(NULL));
	
	int nbIndividus, tailleGenotype, maxLociAmbigus;
	printf("Entrez le nombre d'individus : "); scanf("%d", &nbIndividus);
	printf("Entrez la taille des génotypes : "); scanf("%d", &tailleGenotype);
	printf("Entrez le nombre maximum de loci ambigu d'un génotype : "); scanf("%d", &maxLociAmbigus);
	
	//nbIndividus = 12; tailleGenotype = 10; nbLociAmbigus = 3;
	
	generation_genotype_aleatoire(nbIndividus, tailleGenotype, maxLociAmbigus);
}



	
