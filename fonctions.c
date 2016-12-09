#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

// ** Fonctions appelées lors de la génération de génotypes aléatoires **

//Fonction écriture fichiers texte
void creer_fichier_genotypes(int genotype[], int tailleTableau, int individu)
{
	FILE* fichier_genotype = NULL;
	int i;
	

	fichier_genotype = fopen("genotypes_alea.txt", "a");
	
	if (fichier_genotype != NULL)
	{
		fprintf(fichier_genotype, "/ind %d ", individu);
		for (i = 0 ; i < tailleTableau ; i++)
		{
			fprintf(fichier_genotype, "%d", genotype[i]);
		}
		fprintf(fichier_genotype, "\n");
		fclose(fichier_genotype);
	}
}

void creer_fichier_haplotypes(int genotype[], int haplotype1[], int haplotype2[], int tailleTableau, int individu)
{
	FILE* fichier_haplotypes = NULL;
	int j,k,l;
	
	
	fichier_haplotypes = fopen("haplotypes_alea.txt", "a");
	
	if (fichier_haplotypes != NULL)
	{
		fprintf(fichier_haplotypes, "/ind %d geno ", individu);
		for(j = 0 ; j < tailleTableau ; j++)
		{
			fprintf(fichier_haplotypes, "%d", genotype[j]);
		}
		
		fprintf(fichier_haplotypes, "\n/ind %d real haplo1 ", individu);
		j = 0;
		for(k = 0 ; k < tailleTableau ; k++)
		{
			fprintf(fichier_haplotypes, "%d", haplotype1[k]);
		}
		
		fprintf(fichier_haplotypes, "\n/ind %d real haplo2 ", individu);
		l = 0;
		for(l = 0 ; l < tailleTableau ; l++)
		{
			fprintf(fichier_haplotypes, "%d", haplotype2[l]);
		}
		fprintf(fichier_haplotypes, "\n");
		fclose(fichier_haplotypes);
	}
}




//Fonction tirage aleatoire dans l'intervalle [a,b[
int rand_a_b(int a, int b)
{
	return rand()%(b-a) +a;
}


//Fonction affichage contenu de tableau
void affiche_tableau(int tableau[], int tailleTableau)
{
	int i;

	for (i = 0 ; i < tailleTableau ; i++)
	{
		printf("%d", tableau[i]);
	}

}


//Fonction génération aléatoire des positions d'un génome
void tirage_loci_aleatoire(int* genotype, int tailleGenotype)
{
	int position;
	int lociAleatoire=0;

	for (position = 0; position < tailleGenotype; position ++)
	{

	lociAleatoire = rand_a_b(0, 2) ; //Tirage aléatoire dans l'intervalle [0, 2[
    genotype[position] = lociAleatoire ;

	}
}

//Fonction génération aléatoire des positions d'un génome
void tirage_loci_ambigu(int* genotype, int tailleGenotype, int maxLociAmbigus)
{
	int i;
    int* pos_locus_ambigu = NULL;
	int* deja_fait = NULL;

	//afficherVect(locus, taille_locus);
	pos_locus_ambigu = malloc((maxLociAmbigus) * sizeof (int));
	deja_fait = malloc((tailleGenotype) * sizeof (int));

    for(i = 0; i < maxLociAmbigus; i++){
        do{
            pos_locus_ambigu[i] = rand_a_b(0, tailleGenotype) ;
        }while(deja_fait[pos_locus_ambigu[i]] == 1);

        deja_fait[pos_locus_ambigu[i]]  = 1;
        genotype[pos_locus_ambigu[i]] = 2;
        //afficherVect(locus, taille_locus);
    }
    //free(pos_locus_ambigu); //BUG à la compil
    //free(deja_fait);
}

void tirage_haplotypes(int* genotype, int* haplotype1, int* haplotype2, int tailleGenotype)
{
    int position;
    int lociAmbHap;

    for (position = 0; position < tailleGenotype; position ++)
    {
        lociAmbHap=0;

        haplotype1[position] = genotype[position];
        haplotype2[position] = genotype[position];

		if(genotype[position]==2){

            lociAmbHap = rand_a_b(0, 2) ;
            haplotype1[position] = lociAmbHap;
            if (lociAmbHap == 0) { haplotype2[position] = 1;
            }else//(lociAmbHap == 1)
            { haplotype2[position] = 0;}
		}
    }
}

void nouveaux_tirages_si_doublon(int* genotype1, int* genotype2, int* haplotype1, int* haplotype2, int tailleGenotype, int maxLociAmbigus){

    int similaire = 0;
    int i;

    //1ere verification de similarité entre genotype
    for(i = 0; i < tailleGenotype; i++){

        if (genotype1[i] == genotype2[i]) similaire++;
    }

    if(similaire == tailleGenotype){

        do{//nouveau tirage s'il sont similaires
            similaire = 0;

            tirage_loci_aleatoire(genotype2, tailleGenotype);
            tirage_loci_ambigu(genotype2, tailleGenotype, maxLociAmbigus);
            tirage_haplotypes(genotype2, haplotype1, haplotype2, tailleGenotype);

            for(i = 0; i < tailleGenotype; i++){

                if (genotype1[i] == genotype2[i]) similaire++;
            }

        }while(similaire == tailleGenotype); //on prévoit le cas d'un troisième (ou plus!) tirage similaire
      }
    //affiche_tableau(genotype1, tailleGenotype);
    //affiche_tableau(genotype2, tailleGenotype);
}


//Fonction génération aléatoire d'un génotypes pour chacun des individus
void generation_genotype_aleatoire(int nbIndividus, int tailleGenotype, int maxLociAmbigus)
{
	//Initialisation des tableaux de génotype et d'haplotypes
	int** liste_geno = NULL;
	int** liste_haplo1 = NULL;
	int** liste_haplo2 = NULL;

	//Allocations de mémoire
	liste_geno = (int**)malloc((nbIndividus) * sizeof (int*));
	liste_haplo1 = (int**)malloc((nbIndividus) * sizeof (int*));
	liste_haplo2 = (int**)malloc((nbIndividus) * sizeof (int*));

	//Initialisation compteur du nombre d'individus
	int individu, individu2;

	//Boucle de génération aléatoire de génotype et d'haplotypes pour chacun des individus
	for (individu = 0; individu < nbIndividus; individu ++)
	{

        liste_geno[individu] = (int*)malloc(tailleGenotype * sizeof(int));
        liste_haplo1[individu] = (int*)malloc(tailleGenotype * sizeof(int));
        liste_haplo2[individu] = (int*)malloc(tailleGenotype * sizeof(int));

	    tirage_loci_aleatoire(liste_geno[individu], tailleGenotype);
        tirage_loci_ambigu(liste_geno[individu], tailleGenotype, maxLociAmbigus);
        tirage_haplotypes(liste_geno[individu], liste_haplo1[individu], liste_haplo2[individu], tailleGenotype);


		//Affichages du génotype et des haplotypes générés pour chaque individu
		printf("\n\n===Individu %d ===", individu+1);
		printf("\nGenotype    : ");
		affiche_tableau(liste_geno[individu], tailleGenotype);
		printf("\nHaplotype 1 : ");
		affiche_tableau(liste_haplo1[individu], tailleGenotype);
		printf("\nHaplotype 2 : ");
		affiche_tableau(liste_haplo2[individu], tailleGenotype);
		
		creer_fichier_genotypes(liste_geno[individu], tailleGenotype, individu);
		creer_fichier_haplotypes(liste_geno[individu], liste_haplo1[individu], liste_haplo2[individu], tailleGenotype, individu);
	}
/*
	for (individu = 0; individu < nbIndividus; individu ++){
        for(individu2 = 0; individu2 < nbIndividus; individu2++){
        //possibilite d optimiser pour eviter de comparer liste_geno[i] avec lui meme
        nouveaux_tirages_si_doublon(liste_geno[individu], liste_geno[individu2], liste_haplo1[individu2], liste_haplo1[individu2],tailleGenotype, maxLociAmbigus);
        //complexite de type taille_locus^3 (3eme boucle for dans la fct)
        //possibilite d optimiser en evitant une comparaison 2 a 2 mais plutot de type "diviser pour regner" ?
	    }
	}*/

	//libération de mémoire alloué dynamiquement
	for (individu = 1; individu <= nbIndividus; individu ++){
           free(liste_geno[individu]);
           free(liste_haplo1[individu]);
           free(liste_haplo2[individu]);
	}
	free(liste_geno);
	free(liste_haplo1);
	free(liste_haplo2);
}



// Fonctions Inférences haplotypes

void lire_genotype(char* ligne, char* genotype, int tailleGenotype)
{
	int pos_ligne, position=0;
	if (ligne[6] == ' ')
	{
		printf("%s", ligne);
		
		pos_ligne=7;
		position=0;
		for(position = 0 ; position < tailleGenotype ; position ++)
		{
			genotype[position] = ligne[pos_ligne];
			pos_ligne++;
		}
		printf("Genotype : %s\n", genotype);
	}else{
		printf("%s", ligne);
		pos_ligne=8; 
		position=0;
		for(position = 0 ; position < tailleGenotype ; position ++)
		{
			genotype[position] = ligne[pos_ligne];
			pos_ligne++;
		}
		printf("Genotype : %s\n", genotype);
	}
	
}



void lire_fichier_genotypes(int nbIndividus, int tailleGenotype)
{
	FILE* fichierGenotypes = NULL;
	char* ligne = NULL;
	//char* genotype = NULL;
	char** listeGenotypes = NULL;
	int tailleLigne, individu = 0;
	
	tailleLigne=40;

	ligne = (char*)malloc((tailleLigne) * sizeof (char*));
	//genotype = (char*)malloc((tailleGenotype) * sizeof (char*));
	listeGenotypes = (char**)malloc((nbIndividus) * sizeof (char**));

	fichierGenotypes = fopen("genotypes_alea.txt", "r");
	
	if (fichierGenotypes != NULL)
	{
	
		while (fgets(ligne, tailleLigne, fichierGenotypes) != NULL)
		{
			listeGenotypes[individu] = (char*)malloc((tailleGenotype) * sizeof (char*));
			lire_genotype(ligne, listeGenotypes[individu], tailleGenotype);
			individu++;
		}

        fclose(fichierGenotypes);
		
	}
	individu=0;
	for (individu = 0; individu < nbIndividus; individu ++){
           free(listeGenotypes[individu]);
	}
	free(listeGenotypes);
	free(ligne);
}
	
