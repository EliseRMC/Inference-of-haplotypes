
// ** Définitions Génération génotypes aléatoires **

//Fonctions
int rand_a_b(int a, int b);
void affiche_tableau(int tableau[], int tailleTableau);

void tirage_avec_ambiguite(int* genotype, int* haplotype1, int* haplotype2, int position, int nbLociAmbigus);
void tirage_sans_ambiguite(int* genotype, int* haplotype1, int* haplotype2, int position);
void tirage_loci_aleatoire(int* genotype, int tailleGenotype);
void generation_genotype_aleatoire(int nbIndividus, int tailleGenotype, int maxLociAmbigus);
void creer_fichier_genotypes(int genotype[], int tailleTableau, int individu);
void creer_fichier_haplotypes(int genotype[], int haplotype1[], int haplotype2[], int tailleTableau, int individu);
void tirage_loci_ambigu(int* genotype, int tailleGenotype, int maxLociAmbigus);
void tirage_haplotypes(int* genotype, int* haplotype1, int* haplotype2, int tailleGenotype);
void nouveaux_tirages_si_doublon(int* genotype1, int* genotype2, int* haplotype1, int* haplotype2, int tailleGenotype, int maxLociAmbigus)


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
