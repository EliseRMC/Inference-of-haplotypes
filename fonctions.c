#include "structures.h"

// ** Fonctions appelées lors de la génération de génotypes aléatoires **

//Fonction tirage aleatoire dans l'intervalle [a,b[
int rand_a_b(int a, int b)
{
	printf("rand\n");
	return rand()%(b-a) +a;
}

int tableau[10]

//Fonction génération de génotype aléatoires
void  generation_genotype_aleatoire(int nbIndividus, int tailleGenotype, int maxLociAmbigus)
{
	printf("fonction ok\n");
	printf("nombre d'individus = %d\n", nbIndividus);
	printf("taille génotype = %d\n", tailleGenotype);
	printf("nombre max de loci ambigus = %d\n",  maxLociAmbigus);
	int genotype[tailleGenotype],haplotype1[tailleGenotype], haplotype2[tailleGenotype];
	int lociAleatoire, lociAmbHap, individu, position, nbLociAmbigus=0;
	while(individu < nbIndividus) //Tant que le nombre d'individu est inférieur à 12
	{ 
	printf("boucle individu\n");
		while(position < tailleGenotype) //Tant que les 10 positions du genome n'ont pas été générés
		{
		printf("boucle genotype\n");
			if (nbLociAmbigus < maxLociAmbigus) //Si le nombre de loci ambigu dans la séquence est inférieur à 3
			{ 
				lociAleatoire = rand_a_b(0,3) ; //Tirage aléatoire dans l'intervalle [0,3[
				printf("ok\n");
				printf("loci Aleatoire : %d\n", lociAleatoire);
				if (lociAleatoire == 1 || lociAleatoire == 0)
				{
					genotype[tailleGenotype] = lociAleatoire;
					haplotype1[tailleGenotype] = lociAleatoire;
					haplotype2[tailleGenotype] = lociAleatoire;
					printf("loci alea < 3\n");
				}			
				else if (lociAleatoire == 2)//Si un loci ambigu dans la séquence, sélection aléatoire du 0 ou du 1 pour les haplotypes générés
				{ 
					genotype[tailleGenotype] = lociAleatoire;
					lociAmbHap = rand_a_b(0, 2) ; 
					haplotype1[tailleGenotype] = lociAmbHap;
					printf("loci ambigu trouvé");
					if (lociAmbHap == 0) 
					{
						haplotype2[tailleGenotype] = 1;
					}else if (lociAmbHap == 1)
					{
						haplotype2[tailleGenotype] = 0;
					}
					nbLociAmbigus++ ;
				}
			}
			if (nbLociAmbigus >= maxLociAmbigus) // Si le nombre de 2 dans la séquence est supérieur à 3
			{ 
				lociAleatoire = rand_a_b(0, 2) ; //Tirage aléatoire dans l'intervalle [0, 2[
				if (lociAleatoire == 1 || lociAleatoire == 0)
				{
					genotype[tailleGenotype] = lociAleatoire ;
					haplotype1[tailleGenotype] = lociAleatoire;
					haplotype2 [tailleGenotype] = lociAleatoire;
					printf("nb loci ambigu max");
				}
			}
		position++;
		}
	affiche_tableau(genotype[position], tailleGenotype);
	individu++;
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

