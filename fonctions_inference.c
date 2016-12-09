#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "structures_inference.h"

/////////////////////////////////////// Fonctions geno_chaines\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\


TCell2Gen* creation_cell_geno2(TCellGen* tete_liste_geno){

    //Variables
    TCell2Gen* cell = tete_liste_geno -> adr_liste2_haplo;
    cell = (TCell2Gen*) malloc(sizeof(TCell2Gen)); //Besoin d`une allocation dynamique ?????????????????????????????????

    //Verification de réussite de l'allocation mémoire
    if(cell == NULL) exit(1); //sinon la mémoire est saturée et on doit quitter le programme

    //Attribution
    cell -> adr_liste_haplo1 = NULL;
    cell -> adr_liste_haplo2 = NULL;
    cell -> suiv_gen2 = NULL;

    return cell;
}

void creation_cell_geno(TCellGen* adr_tete, char* genotype){

    //Variables
    TCellGen* cell = NULL;
    cell = (TCellGen*) malloc(sizeof(TCellGen)); //allocation dynamique d'une nouvelle cellule

    //Verification de réussite de l'allocation mémoire
    if(cell == NULL) exit(1); //sinon la mémoire est saturée et on doit quitter le programme

    //Attribution
    *(cell -> info_geno) = *genotype; //appel: entree = liste_geno[individu]
    //cell -> freq_genome = val;
    cell -> adr_liste2_haplo = creation_cell_geno2(cell);
    cell -> suiv_gen = NULL;

    adr_tete = cell; // liaison avec l'adr_tete de liste

}

void creation_cell_haplo1(TCellHap1* adr_tete, int haplotype1[10]){

    //Variables
    TCellHap1* cell = NULL;
    cell = (TCellHap1*) malloc(sizeof(TCellHap1)); //allocation dynamique d'une nouvelle cellule

    //Verification de réussite de l'allocation mémoire
    if(cell == NULL) exit(1); //sinon la mémoire est saturée et on doit quitter le programme

    //Attribution
    *(cell -> info_haplo1) = *haplotype1; //appel: entree = liste_geno[individu]
    cell -> freq_haplo1 = 0;
    cell -> adr_liste2_haplo1 = NULL; //A FAIRE
    cell -> suiv_haplo1 = NULL;

    adr_tete = cell; // liaison avec l'adr_tete de liste
}

TCell2Hap1* creation_cell_haplo12(TCellHap1* tete_liste_haplo1){

    //Variables
    TCell2Hap1* cell = NULL;
    cell = tete_liste_haplo1-> adr_liste2_haplo1;
    cell = (TCell2Hap1*) malloc(sizeof(TCell2Hap1)); //allocation dynamique d'une nouvelle cellule

    //Verification de réussite de l'allocation mémoire
    if(cell == NULL) exit(1); //sinon la mémoire est saturée et on doit quitter le programme

    //Attribution
    cell -> adr_liste_haplo2 = NULL;
    cell -> adr_liste_geno = NULL;
    cell -> suiv_haplo12 = NULL;

    return cell;
}

void creation_cell_haplo2(TCellHap2* adr_tete, int haplotype2[10]){

    //Variables
    TCellHap2* cell = NULL;
    cell = (TCellHap2*) malloc(sizeof(TCellHap2)); //allocation dynamique d'une nouvelle cellule

    //Verification de réussite de l'allocation mémoire
    if(cell == NULL) exit(1); //sinon la mémoire est saturée et on doit quitter le programme

    //Attribution
    *(cell -> info_haplo2) = *haplotype2; //appel: entree = liste_geno[individu]
    cell -> freq_haplo2 = 0;
    cell -> adr_liste2_haplo2 = NULL; //A FAIRE
    cell -> suiv_haplo2 = NULL;

    adr_tete = cell; // liaison avec l'adr_tete de liste
}

TCell2Hap2* creation_cell_haplo22(TCellHap2* tete_liste_haplo2){

    //Variables
    TCell2Hap2* cell = NULL;
    cell = tete_liste_haplo2-> adr_liste2_haplo2;
    cell = (TCell2Hap2*) malloc(sizeof(TCell2Hap2)); //allocation dynamique d'une nouvelle cellule

    //Verification de réussite de l'allocation mémoire
    if(cell == NULL) exit(1); //sinon la mémoire est saturée et on doit quitter le programme

    //Attribution
    cell -> adr_liste_haplo1 = NULL;
    cell -> adr_liste_geno = NULL;
    cell -> suiv_haplo22 = NULL;

    return cell;
}

/*------------------------------------------------------------------*/

//Fonction affichage contenu de tableau
void affiche_tableau(int tableau[], int tailleTableau)
{
	int i;

	for (i = 0 ; i < tailleTableau ; i++){
		printf("%d", tableau[i]);
	}

}

//Fonction génération aléatoire des positions d'un génome
void tirage_loci_aleatoire(int* genotype, int tailleGenotype, int MAX)
{
	int position;
	int lociAleatoire=0;

	for (position = 0; position < tailleGenotype; position ++)
	{

	lociAleatoire = rand()%(MAX+1); //Tirage aléatoire dans l'intervalle [0, MAX]
    genotype[position] = lociAleatoire ;

	}
}

void affiche_liste_geno(TCellGen* adr_tete){

    /*if (adr_tete == NULL){ //si la précondition n'est pas vérifiée, renvoie une erreur
        affiche_erreur('L'); return;
    }*/

    //Variables
    TCellGen* p; //création de notre espion que l'on va faire courir le long de la liste
    p = adr_tete; //initialisation sur l'adresse du premier element de la liste
    
    printf("\n\nAffichage du contenu de la liste : \n\n");
    
	if (p == NULL)
	{
		printf("contenu manquant\n");
	}else{
		printf("contenu OK\n");
	}
    while (p != NULL){ //tant que l'on n'est pas au bout de la liste
        printf("%s ->", p->info_geno); //affichage de l'information de la cellule
        p = p -> suiv_gen; //on avance à la cellule suivante
    }
    printf("NULL\n"); //on marque la fin de liste
}

/////////////////////////////////////// Fonctions lecture\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\

//La fonction lire_genotype retourne un tableau contenant des caractères
char* lire_genotype(char* ligne, char* genotype, int tailleGenotype)
{
	int pos_ligne, position=0;
	

	
	//Conditions de lecture d'une ligne du fichier texte en prenant en compte la différence de nombre de caractères
	if (ligne[6] == ' ')
	{
		printf("%s", ligne);
		
		pos_ligne=7;
		position=0;
		for(position = 0 ; position < tailleGenotype ; position ++) //remplissage du tableau genotype position par position
		{
			genotype[position] = ligne[pos_ligne];
			pos_ligne++;
		}
		printf("Genotype : %s\n", genotype); // affichage du contenu du tableau après remplissage
	}else{
		printf("%s", ligne);
		pos_ligne=8; 
		position=0;
		for(position = 0 ; position < tailleGenotype ; position ++) //remplissage du tableau genotype position par position
		{
			genotype[position] = ligne[pos_ligne];
			pos_ligne++;
		}
		printf("Genotype : %s\n", genotype); // affichage du contenu du tableau après remplissage	
	}
	return genotype; //la fonction retourne le tableau de genotypes une fois complété
}


void lire_fichier_genotypes(int nbIndividus, int tailleGenotype)
{
	FILE* fichierGenotypes = NULL;
	char* ligne = NULL;
	char* genotype = NULL;
	int tailleLigne, individu = 0;
	TCellGen* liste_geno=NULL;
	
	tailleLigne=40;

	//Allocation
	ligne = (char*)malloc((tailleLigne) * sizeof (char*));
	genotype = (char*)malloc((tailleGenotype) * sizeof (char*));
	//listeGenotypes = (char**)malloc((nbIndividus) * sizeof (char**));

	fichierGenotypes = fopen("genotypes_alea.txt", "r");
	
	if (fichierGenotypes != NULL)
	{
		printf("\n\nAffichage des lignes lues et des génotypes récupérés : \n\n");
		while (fgets(ligne, tailleLigne, fichierGenotypes) != NULL)
		{
			lire_genotype(ligne, genotype, tailleGenotype);
			creation_cell_geno(liste_geno, genotype); // Le tableau de genotype généré à chaque itération est directement récupéré comme paramètre de la fonction creation_cell_geno
			
			
			//individu++;
		}

        fclose(fichierGenotypes);
		
	}
	affiche_liste_geno(liste_geno); //Affichage de la liste_geno une fois remplie
	
	
	/*individu=0;
	for (individu = 0; individu < nbIndividus; individu ++){
           free(listeGenotypes[individu]);
	}
	free(listeGenotypes);*/
	//return listeGenotypes;
	free(ligne);
}


