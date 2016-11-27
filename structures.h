
// ** Définitions Génération génotypes aléatoires **

//Fonctions
int rand_a_b(int a, int b);
void affiche_tableau(int tableau[], int tailleTableau);

void tirage_avec_ambiguite(int* genotype, int* haplotype1, int* haplotype2, int position, int nbLociAmbigus);
void tirage_sans_ambiguite(int* genotype, int* haplotype1, int* haplotype2, int position);
void tirage_loci_aleatoire(int* genotype, int* haplotype1, int* haplotype2, int tailleGenotype, int maxLociAmbigus);
void generation_genotype_aleatoire(int nbIndividus, int tailleGenotype, int maxLociAleatoire);


// ** Definitions Inference haplotypes **

//Alias
/*typedef struct TCell* TPtr;
typedef struct TCell TCell;

//Fonctions
void afficherErreur(char typeErreur);
TPtr *creationElem(int val);
void afficherListe(TPtr *adr_liste);
void insDebut(TPtr *adr_liste, int val, char bool_affiche);
void insPos(TPtr *adr_liste, int val, int pos, char bool_affiche);
void supprDebut(TPtr *adr_liste, char bool_affiche);
void supprPos(TPtr *adr_liste, int k, char bool_affiche);
void accesVal(TPtr *adr_liste, int val, TPtr *adr_ptrCell);
void insertListeTriee(TPtr *adr_liste, int val, char bool_affiche);
void lireFichier(char nomDuFichier[], char modeOuverture[]);*/
