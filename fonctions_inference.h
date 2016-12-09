//Fonctions algorithme_EM

void lire_genotype(char* ligne, char* genotype, int tailleGenotype);
void lire_fichier_genotypes(int nbIndividus, int tailleGenotype);



void creation_cell_geno(TCellGen* adr_tete, int genotype[10]);
void creation_cell_haplo1(TCellHap1* adr_tete, int haplotype1[10]);
void creation_cell_haplo2(TCellHap2* adr_tete, int haplotype2[10]);
TCell2Gen* creation_cell_geno2(TCellGen* tete_liste_geno);
TCell2Hap1* creation_cell_haplo12(TCellHap1* tete_liste_haplo1);
TCell2Hap2* creation_cell_haplo22(TCellHap2* tete_liste_haplo2);


