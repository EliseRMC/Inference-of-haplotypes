#include "structures.h"

// ** Fonctions appelées lors de la génération de génotypes aléatoires **

//Fonction tirage aleatoire dans l'intervalle [a,b[
int rand_a_b(int a, int b)
{
	return rand()%(b-a) +a;
}

//Fonction génération de loci aléatoire avec positions ambigues
void tirage_avec_ambiguite(int* genotype, int* haplotype1, int* haplotype2, int position, int nbLociAmbigus)
{
	int lociAleatoire, lociAmbHap=0;
	
	lociAleatoire = rand_a_b(0,3);
	
	if (lociAleatoire == 1 || lociAleatoire == 0)
	{
		genotype[position] = lociAleatoire;
		haplotype1[position] = lociAleatoire;
		haplotype2[position] = lociAleatoire;
	}			
	else if (lociAleatoire == 2)//Si un loci ambigu dans la séquence, sélection aléatoire du 0 ou du 1 pour les haplotypes générés
	{ 
		genotype[position] = lociAleatoire;
		lociAmbHap = rand_a_b(0, 2) ; 
		haplotype1[position] = lociAmbHap;
		if (lociAmbHap == 0) 
		{
			haplotype2[position] = 1;
		}else if (lociAmbHap == 1)
		{
			haplotype2[position] = 0;
		}
		nbLociAmbigus ++ ;
	} 
}

//Fonction génération de loci aléatoire sans positions ambigues
void tirage_sans_ambiguite(int* genotype, int* haplotype1, int* haplotype2, int position)
{
	int lociAleatoire=0;
	lociAleatoire = rand_a_b(0, 2) ; //Tirage aléatoire dans l'intervalle [0, 2[
	if (lociAleatoire == 1 || lociAleatoire == 0)
	{
		genotype[position] = lociAleatoire ;
		haplotype1[position] = lociAleatoire;
		haplotype2 [position] = lociAleatoire;
	}
}

//Fonction génération aléatoire des positions d'un génome
void tirage_loci_aleatoire(int* genotype, int* haplotype1, int* haplotype2, int tailleGenotype, int maxLociAmbigus)
{
	int nbLociAmbigus=0;
	int position = 1;
	
	for (position = 0; position < tailleGenotype; position ++)
	{
		if (nbLociAmbigus < maxLociAmbigus)
		{
			tirage_avec_ambiguite(genotype, haplotype1, haplotype2, position, nbLociAmbigus);
		}
		else if (nbLociAmbigus >= maxLociAmbigus)
		{
			tirage_sans_ambiguite(genotype, haplotype1, haplotype2, position);
		}
	}
}

//Fonction génération aléatoire d'un génotypes pour chacun des individus	
void generation_genotype_aleatoire(int nbIndividus, int tailleGenotype, int maxLociAmbigus)
{
	//Initialisation des tableaux de génotype et d'haplotypes
	int* genotype = NULL;
	int* haplotype1 = NULL;
	int* haplotype2 = NULL;
	
	//Allocations de mémoire
	genotype = malloc(tailleGenotype * sizeof(int));
	haplotype1 = malloc(tailleGenotype * sizeof(int));
	haplotype2 = malloc(tailleGenotype * sizeof(int));
	
	//Initialisation compteur du nombre d'individus
	int individu=1;
	
	//Boucle de génération aléatoire de génotype et d'haplotypes pour chacun des individus
	for (individu = 1; individu <= nbIndividus; individu ++)
	{
		tirage_loci_aleatoire(genotype, haplotype1, haplotype2, tailleGenotype, maxLociAmbigus);
		
		//Affichages du génotype et des haplotypes générés pour chaque individu
		printf("\n\nGenotype Individu %d : ", individu);
		affiche_tableau(genotype, tailleGenotype);
		printf("\nHaplotype 1  : ");
		affiche_tableau(haplotype1, tailleGenotype);
		printf("\nHaplotype 2 : ");
		affiche_tableau(haplotype2, tailleGenotype);
	}
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










// ** Fonctions appelées lors de l'exécution de l'algorithme d'inférence d'haplotypes **

//Alias

/*struct TypeChaine80{
    char chaineCaratere[80];
};

////////////////////////////////////////////////

typedef struct TCell{
    int info;
    TPtr suiv;
};


////////////////////////////////////////////////

void afficherErreur(char typeErreur){
    printf("Erreur: ");
    switch(typeErreur){
        case 'L':
            printf("liste vide.\n");
            break;
        case 'P':
            printf("position erronee.\n");
            break;
        case 'V':
            printf("valeur inexistante.\n");
        break;
        case 'F':
            printf("ouverture du fichier impossible.\n");
        break;
    }
}

////////////////////////////////////////////////

TPtr *creationElem(int val){
    TPtr cell = (TCell*) malloc(sizeof(TCell));
    cell -> info = val;

    //verification de reussite
    if(cell == NULL){
    exit(1);
    }

    return cell;
}

////////////////////////////////////////////////

void afficherListe(TPtr *adr_liste){

    //verification d'existence de liste
    if (adr_liste == NULL)
    {
        afficherErreur('L');
        return;
    }

    TPtr p = *adr_liste;

    //afficher chaque cellule
    while (p != NULL)
    {
        printf("%d -> ", p->info);
        p = p -> suiv;
    }
    printf("NULL\n"); //marquer la fin de liste
}

////////////////////////////////////////////////

void insDebut(TPtr *adr_liste, int val, char bool_affiche){

    //verification d'existence de liste
    if (adr_liste == NULL)
    {
        afficherErreur('L');
        return;
    }

    // creation du nouvel element
    TPtr p_nouv;
    p_nouv=creationElem(val);
    // insertion de l'element au debut de la liste
    p_nouv -> suiv = *adr_liste;
    *adr_liste = p_nouv;

    if (bool_affiche=='T') afficherListe(adr_liste);
}

////////////////////////////////////////////////

void insPos(TPtr *adr_liste, int val, int k, char bool_affiche){

    //verification d'existence de liste
    if (adr_liste == NULL)
    {
        afficherErreur('L');
        return;
    }

    //variables
    TPtr prec = NULL, p = *adr_liste;
    int i = 1;

    //placement a la bonne position
    while(p != NULL && i < k){
        prec = p;
        p = p -> suiv;
        i++;
    }
    if(k==1){ //insertion en debut de liste (cas de liste vide [p == NULL] ET de liste preexistante)
        insDebut(adr_liste, val, bool_affiche);
        return;
        }//sinon k>1
    if (p == NULL && k!= i){//k > i (k>longueur de la liste)
            afficherErreur('P');
            return;
    }//sinon insertion en milieu de liste OU en fin de liste (p == NULL);
    insDebut(&prec -> suiv, val, bool_affiche);
}

////////////////////////////////////////////////

void supprDebut(TPtr *adr_liste, char bool_affiche){

    //verification d'existence de liste
    if (adr_liste == NULL)
    {
        afficherErreur('L');
        return;
    }

    //raccordements
    TPtr p = *adr_liste;
    *adr_liste = p -> suiv;

    free(p); //supression

    if (bool_affiche=='T') afficherListe(adr_liste);
}

////////////////////////////////////////////////

void supprPos(TPtr *adr_liste, int k, char bool_affiche){

    //verification d'existence de liste
    if (adr_liste == NULL)
    {
        afficherErreur('L');
        return;
    }

    //variables
    TPtr prec = NULL, p = *adr_liste;
    int i = 1;

    //placement a la bonne position
    while(p != NULL && i < k){
        prec = p;
        p = p -> suiv;
        i++;
    }
    if(k==1){ //insertion en debut de liste (cas de liste vide ET de liste preexistante)
        supprDebut(adr_liste, bool_affiche);
        return;
        }//sinon k>1
    if (p == NULL && k!= i){//k > i (k>longueur de la liste)
            afficherErreur('P');
            return;
    }//sinon insertion en milieu de liste OU en fin de liste (p == NULL);
    supprDebut(&prec -> suiv, bool_affiche);
}

////////////////////////////////////////////////

void accesVal(TPtr *adr_liste, int val, TPtr *adr_ptrCell){

    //variables
    TPtr p = *adr_liste;

    while(p != NULL){
        if(p -> info == val){//cas du match
        printf("%d\n", p->info);
        adr_ptrCell = p; return;
        }
        p = p -> suiv; //sinon incrementation
    }afficherErreur('V');
    *adr_ptrCell = NULL; // si on ne trouve pas
}

////////////////////////////////////////////////

void insertListeTriee(TPtr *adr_liste, int val, char bool_affiche){

    //verification d'existence de liste
    if (adr_liste == NULL)
    {
        afficherErreur('L');
        return;
    }

    //variables
    TPtr p = *adr_liste; TPtr prec = NULL;

    //placement a la bonne position
    while(p != NULL && val > p-> info){
        prec = p;
        p = p -> suiv;
    }//si liste vide, insertion en tete
    if (prec == NULL){
        insDebut(adr_liste, val, bool_affiche);
        return;
    }//sinon insertion au milieu OU en fin de liste
    insDebut(&prec -> suiv, val, bool_affiche);
}

////////////////////////////////////////////////

void lireFichier(char nomDuFichier[], char modeOuverture[]){

    FILE* fichier = NULL;
    fichier = fopen(nomDuFichier, modeOuverture);

    if (fichier == NULL)
    {
        afficherErreur('F');;
    }//sinon
    char chaine[50] = "";

    while (fgets(chaine, 50, fichier) != NULL)
    {
        printf("%s", chaine);
    }

        fclose(fichier);
}

////////////////////////////////////////////////

int longueurVecteur(int v[]){
    int i;
    for (i=0; i+)
}
int triRapide(int v[], int g, int d){

    //variables locales
    int ind_pivot;

    //affectation
    g = v[i];
    d =

    if(g < d){//sinon vecteur vide
        ind_pivot=partitionner(v, g, d);
        triRapide(v, g, ind_pivot - 1);
        triRapide(v, ind_pivot + 1, d);
    }
    return v[];
}

int partitionner(int v[], int g, int d){

    //variables locales
    int pivot, i, j;

    //affectation
    pivot=v[g];
    i=g+1;
    j=d;

    while(i <= j){
        if(v[i] <= pivot){
            i++;
        }//sinon
        while(v[j] > pivot){
            j--;
        }
        if(i < j){
        echanger(v,i,j);
        i++; j--;
    }
    echanger(v,g,j);
    return j;
}*/

