typedef struct TCellGen TCellGen;
typedef struct TCell2Gen TCell2Gen;
typedef struct TCellHap1 TCellHap1;
typedef struct TCell2Hap1 TCell2Hap1;
typedef struct TCellHap2 TCellHap2;
typedef struct TCell2Hap2 TCell2Hap2;


struct TCellGen{//élément de la liste chainée principale de génotype
    char info_geno[10]; //type vecteur de loci du genotype
    //int freq_genome;
    TCell2Gen* adr_liste2_haplo; //type pointeur sur l'adresse de la sous-liste chainée des couple d'haplotypes associés au genotype
    TCellGen* suiv_gen; //type pointeur sur un élément de la liste chainée principale  des génotypes
};

//pointeur de la liste fixé sur adr_liste2_haplo
struct TCell2Gen{//élément de la sous-liste chainée des couples d'haplotypes associés au génotype
    TCellHap1* adr_liste_haplo1; //type pointeur sur l'adresse d'un élément de la liste chainée principale des haplotypes (1)
    TCellHap2* adr_liste_haplo2; //type pointeur sur l'adresse d'un élément de la liste chainée principale des haplotypes (2)
    TCell2Gen* suiv_gen2; //type pointeur sur un élément de la sous-liste chainée des haplotypes associés au génotype
};

struct TCellHap1{//élément de la liste chainée principale des haplotypes1
    int info_haplo1[10]; //type vecteur de loci de l'haplotype (1)
    int freq_haplo1; //fréquence de l'haplotype 1
    TCell2Hap1* adr_liste2_haplo1; //type pointeur sur l'adresse de la sous-liste chainée des couples des génotypes/haplotypes2 associés à l'haplotype 1
    TCellHap1* suiv_haplo1; //type pointeur sur un élément de la liste chainée principale  des haplotypes 1
};

//pointeur de la liste fixé sur adr_liste2_haplo1
struct TCell2Hap1{//élément de la sous-liste chainée des couples des génotypes/haplotypes2 associés à l'haplotype 1
    TCellHap2* adr_liste_haplo2; //type pointeur sur l'adresse  d'un élément de la liste chainée principale des haplotypes (2)
    TCellGen* adr_liste_geno; //type pointeur sur l'adresse  d'un élément de la liste chainée principale des génotypes
    TCell2Hap2* suiv_haplo12; //type pointeur sur un élément de la sous-liste chainée des couples des génotypes/haplotypes2 associés à l'haplotype 1
};

struct TCellHap2{//élément de la liste chainée principale des haplotypes2
    int info_haplo2[10]; //type vecteur de loci de l'haplotype (2)
    int freq_haplo2; //fréquence de l'haplotype 2
    TCell2Hap2* adr_liste2_haplo2; //type pointeur sur l'adresse de la sous-liste chainée des couples des génotypes/haplotypes1 associés à l'haplotype 1
    TCellHap2* suiv_haplo2; //type pointeur sur un élément de la liste chainée principale des haplotypes 2
};

//pointeur de la liste fixé sur adr_liste2_haplo2
struct TCell2Hap2{//élément de la sous-liste chainée des couples des génotypes/haplotypes1 associés à l'haplotype 2
    TCellHap1* adr_liste_haplo1; //type pointeur sur l'adresse  d'un élément de la liste chainée principale des haplotypes (1)
    TCellGen* adr_liste_geno; //type pointeur sur l'adresse  d'un élément de la liste chainée principale des génotypes
    TCell2Hap2* suiv_haplo22; //type pointeur sur un élément de la sous-liste chainée des couples des génotypes/haplotypes1 associés à l'haplotype 2
};
