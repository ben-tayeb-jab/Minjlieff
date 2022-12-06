#include <stdio.h>
#include <stdlib.h>

#define TAILLE 5
#define COLOR_RED "\x1B[31m"
#define COLOR_RESET "\x1B[0m"

typedef enum {
	      BLANC,
	      ROUGE
} joueur;


typedef enum {
	      VIDE,
	      CROIX,
	      DIAG,
	      POUSSEUR,
	      TIREUR,
} contenu;

typedef struct {
    int i;
    int j;
} position;

// deck :
// matrice [2][4].
// m[j][c]  (joueur + contenu)
typedef struct 
{
    contenu tuile[4*((TAILLE*TAILLE)/8)][4*((TAILLE*TAILLE)/8)];
    joueur couleur;
} deck ;

typedef struct {
    position pos;
    contenu t;
    int nbr;
    deck *deck;
} coup;


int est_dans_plateau(int i,int j){
    return i>=0 && i<TAILLE && j>=0 && j<TAILLE;
}

int est_couleur_blanche(contenu plateau[TAILLE][TAILLE],int i,int j){
	if (plateau[i][j]==CROIX || plateau[i][j]==POUSSEUR || plateau[i][j]==DIAG ||plateau[i][j]==TIREUR){
		return 1;
	}
	return 0;
}

int est_couleur_rouge(contenu plateau[TAILLE][TAILLE],int i,int j){
	if (plateau[i][j]==-CROIX || plateau[i][j]==-POUSSEUR || plateau[i][j]==-DIAG ||plateau[i][j]==-TIREUR){
		return 1;
	}
	return 0;
}

int est_coup_possible(position pos, coup *dernier_coup, contenu plateau[TAILLE][TAILLE]){
    if (dernier_coup == NULL) {
		return 1;
    }

    if(plateau[pos.i][pos.j] != VIDE) {
		return 0;
    }
    
    position dernier_pos = dernier_coup->pos;
    int last_pos_i = dernier_pos.i;
    int last_pos_j = dernier_pos.j;
	
    if (dernier_coup->t==DIAG || dernier_coup->t==-DIAG){
		if(last_pos_i - last_pos_j == pos.i-pos.j)
			return 1;

		last_pos_i= dernier_pos.i;
		last_pos_j= dernier_pos.j;	
		while(last_pos_j<TAILLE-1 && last_pos_i >0){
		    last_pos_i--;
		    last_pos_j++;
		    if (last_pos_i==pos.i&& last_pos_j==pos.j){
				printf("3\n");
				return 1;
		    }
		}

		last_pos_i= dernier_pos.i;
		last_pos_j= dernier_pos.j;
		while(last_pos_j>0 && last_pos_i < TAILLE-1){
		    last_pos_i++;
		    last_pos_j--;
		    if (last_pos_i==pos.i&& last_pos_j==pos.j){
				printf("4\n");
				return 1;
		    }
		}

		return 0;
    }

    if (dernier_coup->t==CROIX || dernier_coup->t==-CROIX){
		if (last_pos_i==pos.i || last_pos_j==pos.j){
			return 1;
		}
		return 0;
	    
    }

    if (dernier_coup->t==TIREUR || dernier_coup->t==-TIREUR){
	    for (int i = last_pos_i-1; i < last_pos_i+2; ++i){
		    for (int j = last_pos_j-1; j < last_pos_j+2 ; ++j){
			    if (est_dans_plateau(i,j)==1){
					
				    if (i==pos.i && j==pos.j && 
					(last_pos_i!=pos.i || last_pos_j!=pos.j)){
					    printf("T\n");

					    return 1;
					}
				}
			}
		}
	    return 0;

	}

    if(dernier_coup->t==POUSSEUR || dernier_coup->t==-POUSSEUR){
	    
		for (int i = 0; i < TAILLE; ++i){
			    
			for (int j = 0; j < TAILLE; ++j){
				if ((j<last_pos_j-1)||(j>last_pos_j+1)||
				    (i<last_pos_i-1)||(i>last_pos_i+1)){
					if (i==pos.i && j==pos.j){
						printf("P\n");
						return 1;
					}
				}
								
			}
						
						
		}
		return 0;
    }
		
    printf("coup Impossible \n");
    return 0;
}



int nb_coup_possibles(coup* dernier_coup,contenu plateau[TAILLE][TAILLE]){
	
    if (dernier_coup==NULL) {
		return 1;
    }

    position p = dernier_coup -> pos;
    int cpt=0;
    int pos_i = p.i;
    int pos_j = p.j;

    if (dernier_coup->t==DIAG || dernier_coup->t==-DIAG){


	    while(pos_j<TAILLE-1 && pos_i < TAILLE-1){
			pos_i++;
			pos_j++;
			if (plateau[pos_i][pos_j]==VIDE){
				cpt++;
			}
	    }

	    pos_i =p.i;
	    pos_j = p.j;
	    while(pos_j>0 && pos_i> 0){
			pos_i--;
			pos_j--;
			if (plateau[pos_i][pos_j]==VIDE){
				cpt++;

		    }
	    }

	    pos_i =p.i;
	    pos_j = p.j;
	    while(pos_j<TAILLE-1 && pos_i >0){
			pos_i--;
			pos_j++;
			if (plateau[pos_i][pos_j]==VIDE){
				cpt++;
		    }
	    }

	    pos_i =p.i;
	    pos_j = p.j;		
	    while(pos_j>0 && pos_i < TAILLE-1){
			pos_i++;
			pos_j--;
			if (plateau[pos_i][pos_j]==VIDE){
				cpt++;

		    }
	    }
	    return cpt;
	}
	if (dernier_coup->t==CROIX || dernier_coup->t==-CROIX){
	    for (int i = 0; i < TAILLE; ++i){
		    if (VIDE==plateau[i][pos_j] && (i!=pos_i)){
			    cpt++;
			}
				
		}
	    for (int j = 0; j < TAILLE; ++j){
		    if (VIDE==plateau[pos_i][j] && j!=pos_j){
			    cpt++;
			}
		}
	    return cpt;
		
	}
    if (dernier_coup->t==TIREUR || dernier_coup->t==-TIREUR){
	    for (int i = pos_i-1; i < pos_i+2; ++i){
		    for (int j = pos_j-1; j < pos_j+2 ; ++j){
			    if (est_dans_plateau(i,j)==1){
					
				    if (plateau[i][j]==VIDE && (i!=pos_i || j!=pos_j)){
					    cpt++;
					}
				}
			}
		}
	    return cpt;

	}
	if(dernier_coup->t==POUSSEUR || dernier_coup->t==-POUSSEUR){

		for (int i = 0; i < TAILLE; ++i){
					
			for (int j = 0; j < TAILLE; ++j){
				if ((j<pos_j-1)||(j>pos_j+1)||(i<pos_i-1)||(i>pos_i+1)){
					if (plateau[i][j]==VIDE){
						cpt++;
					}
				}
			}
					
		}
		return cpt;

    }
	
}


coup* jouer_coup(position pos, deck *d, contenu tuile,coup *dernier_coup,contenu plateau[TAILLE][TAILLE]){
    coup *c = malloc(sizeof(coup));
    c->pos = pos;
    c->deck=d;
    c->t=tuile;
	
    if (dernier_coup==NULL){
	    plateau[pos.i][pos.j]=tuile;
	}else{
		if (est_coup_possible(pos,dernier_coup,plateau)==1){
			plateau[pos.i][pos.j]=tuile;
		}else{
		    printf("coup Impossible\n");
		    return NULL;
		}
    }
    return c;
}


contenu convert_int_to_tuile(int i,deck *d){

    if (d->couleur==BLANC){
	    switch(i){
		    case 1 :return CROIX ; break;
		    case 2 :return DIAG ; break;
		    case 3 :return POUSSEUR ; break;
		    case 4 :return TIREUR ; break;
		    default : printf("Mauvaise entrée Recommencer\n"); return VIDE; break;
	    }
	}else{
		switch(i){
			case 1 :return -CROIX ; break;
			case 2 :return -DIAG ; break;
			case 3 :return -POUSSEUR ; break;
			case 4 :return -TIREUR ; break;
			default : printf("Mauvaise entrée Recommencer\n"); return VIDE; break;
		}
    }
}

int check_tuile_dispo(contenu tuile,deck *d){
    if (tuile==CROIX || tuile == -CROIX){
	    for (int j = 0; j < ((TAILLE*TAILLE)/8); ++j){
		    if (d->tuile[0][j]!=VIDE){
			    return 1;
			}
		}
	}
    if (tuile==DIAG || tuile == -DIAG){
	    for (int j = 0; j < ((TAILLE*TAILLE)/8); ++j){
		    if (d->tuile[1][j]!=VIDE){
			    return 1;
			}
		}
	}
    if (tuile==POUSSEUR || tuile == -POUSSEUR){
	    for (int j = 0; j < ((TAILLE*TAILLE)/8); ++j){
		    if (d->tuile[2][j]!=VIDE){
			    return 1;
			}
		}
	}
    if (tuile==TIREUR || tuile == -TIREUR){
	    for (int j = 0; j < ((TAILLE*TAILLE)/8); ++j){
		    if (d->tuile[3][j]!=VIDE){
			    return 1;
			}
		}
	}
    return 0;
}

// rouge -xxx
int calcule_rouge(contenu plateau[TAILLE][TAILLE]) {
	int score = 0;
	int cpt=0;
	// score en ligne
	for (int i = 0; i < TAILLE; i++) {
		for (int j = 2; j <TAILLE; j++) {
			if ( est_couleur_rouge(plateau,i,j) && est_couleur_rouge(plateau,i,j-1) && est_couleur_rouge(plateau,i,j-2) ) {
				cpt++;
			} 
		}
	}

	// score en colonne
	for (int j = 0; j < TAILLE; j++) {
		for (int i = 2; i <TAILLE; i++) {
			
			if ( est_couleur_rouge(plateau,i,j) && est_couleur_rouge(plateau,i-1,j) && est_couleur_rouge(plateau,i-2,j) ) {
				cpt++;
			} 
			 
		}
	}



	// score diago haut gauche
	for (int i = 2; i < TAILLE; i++) {
		for (int j = 2; j < TAILLE; j++) {
			if ( est_couleur_rouge(plateau,i,j) && est_couleur_rouge(plateau,i-1,j-1) && est_couleur_rouge(plateau,i-2,j-2) ) {
				cpt++;
			} 
		}
	}

	// score diago haut droite
	for (int i = 2; i<TAILLE ; i++) {
		for (int j = 0; j <TAILLE-2; j++) {
			if ( est_couleur_rouge(plateau,i,j) && est_couleur_rouge(plateau,i-1,j+1) && est_couleur_rouge(plateau,i-2,j+2) ) {
				cpt++;
			} 
		}
	}

	score = cpt;

	return score;
}

int calcule_blanc(contenu plateau[TAILLE][TAILLE]) {
	int score = 0;
	int cpt=0;
	// score en ligne
	for (int i = 0; i < TAILLE; i++) {
		for (int j = 2; j <TAILLE; j++) {
			if ( est_couleur_blanche(plateau,i,j) && est_couleur_blanche(plateau,i,j-1) && est_couleur_blanche(plateau,i,j-2) ) {
				cpt++;
			} 
		}
	}

	// score en colonne
	for (int j = 0; j < TAILLE; j++) {
		for (int i = 2; i <TAILLE; i++) {
			
			if ( est_couleur_blanche(plateau,i,j) && est_couleur_blanche(plateau,i-1,j) && est_couleur_blanche(plateau,i-2,j) ) {
				cpt++;
			} 
			 
		}
	}



	// score diago haut gauche
	for (int i = 2; i < TAILLE; i++) {
		for (int j = 2; j < TAILLE; j++) {
			if ( est_couleur_blanche(plateau,i,j) && est_couleur_blanche(plateau,i-1,j-1) && est_couleur_blanche(plateau,i-2,j-2) ) {
				cpt++;
			} 
		}
	}

	// score diago haut droite
	for (int i = 2; i<TAILLE ; i++) {
		for (int j = 0; j <TAILLE-2; j++) {
			if ( est_couleur_blanche(plateau,i,j) && est_couleur_blanche(plateau,i-1,j+1) && est_couleur_blanche(plateau,i-2,j+2) ) {
				cpt++;
			} 
		}
	}

	score = cpt;

	return score;
}

void resultat(contenu plateau[TAILLE][TAILLE]) {
    int sb, sr;
    sr = calcule_rouge(plateau);
    sb = calcule_blanc(plateau);
    if (sr < sb) {
	printf("victoire du joueur BLANC\n Blanc = %d points\n \x1B[31m Rouge \x1B[0m = %d points",sb, sr);
    } else if (sr > sb) {
	printf("victoire du joueur \x1B[31m ROUGE \x1B[0m \n Blanc = %d points\n \x1B[31m Rouge \x1B[0m = %d points",sb, sr);
    } else {
	printf("Egalité \n Blanc = %d points\n \x1B[31m Rouge \x1B[0m = %d points",sb, sr);
    }
    printf("\n");
}

deck* initialiser_deck(joueur couleur){
    deck c= {{CROIX,DIAG,POUSSEUR,TIREUR}};

    deck *d = malloc(sizeof(deck));
    d->couleur=couleur;

    for (int i = 0; i < 4; ++i){
	    for (int j = 0; j < ((TAILLE*TAILLE)/8); ++j){
		    if (couleur==BLANC){
			    d->tuile[i][j]=c.tuile[0][i];
			}else{
				d->tuile[i][j]=-(c.tuile[0][i]);
		    }
		}
	}
    return d;
}

void maj_deck(contenu tuile,deck *d){
    if (tuile==CROIX || tuile == -CROIX){
	    for (int j = 0; j < ((TAILLE*TAILLE)/8); ++j){
		    if (d->tuile[0][j]!=0){
			    d->tuile[0][j]=0;
			    return ;
			}
		}
	}
    if (tuile==DIAG || tuile == -DIAG){
	    for (int j = 0; j < ((TAILLE*TAILLE)/8); ++j){
		    if (d->tuile[1][j]!=0){
			    d->tuile[1][j]=0;
			    return;
			}
		}
	}
    if (tuile==POUSSEUR || tuile == -POUSSEUR){
	    for (int j = 0; j < ((TAILLE*TAILLE)/8); ++j){
		    if (d->tuile[2][j]!=0){
			    d->tuile[2][j]=0;
			    return;
			}
		}
	}
    if (tuile==TIREUR || tuile == -TIREUR){
	    for (int j = 0; j < ((TAILLE*TAILLE)/8); ++j){
		    if (d->tuile[3][j]!=0){
			    d->tuile[3][j]=0;
			    return;
			}
		}
	}
}

// PLUS BAS, au niveau de l'interface
void afficherDeck(deck *d){
    printf("Joueur %d Cartes disponibles : '0' -> vide \n",d->couleur+1);
    for (int i = 0; i < 4; ++i)
	{
	    switch(i){
	    case 0 : printf("1/ CROIX :     "); break;
	    case 1 : printf("2/ DIAG :      "); break;
	    case 2 : printf("3/ POUSSEUR :  "); break;
	    case 3 : printf("4/ TIREUR :    "); break;

	    }
	    int cpt=0;
	    for (int j = 0; j < ((TAILLE*TAILLE)/8); ++j)
		{
		    if (d->tuile[i][j]!=VIDE)
			{
			    cpt++;
			}
		}
	    printf("%d ",cpt);
	    printf("\n");
	}
}

void initialiser_plateau(contenu plateau[TAILLE][TAILLE]){
    for (int i = 0; i < TAILLE; ++i){
	    for (int j = 0; j < TAILLE; ++j){
		    plateau[i][j]=VIDE;
		}
	}
}

void afficherPlateau(contenu plateau[TAILLE][TAILLE]){
    printf("\n");
    printf(" Plateau N = %d ",TAILLE);

    printf("\n    ");

    for (int i = 0; i < TAILLE; ++i){
	    printf("%d   ",i);
	}

    for (int i = 0; i < TAILLE; ++i){
	    printf("\n");
	    printf("---------------------\n");
	    printf("%d : ",i );
	    for (int j = 0; j < TAILLE; ++j){
		    if (plateau[i][j]==VIDE){
			    printf(".   ");
			}
		    if (plateau[i][j]==DIAG){
			    printf("D   ");
			}
		    if (plateau[i][j]==-DIAG){
			    printf ("\x1B[31m");
			    printf("D   ");
			    printf ("\x1B[0m");			
			}
		    if (plateau[i][j]==CROIX){
			    printf("C   ");
			}
		    if (plateau[i][j]==-CROIX){
			    printf ("\x1B[31m");
			    printf("C   ");
			    printf ("\x1B[0m");				
			}
		    if (plateau[i][j]==POUSSEUR){
			    printf("P   ");
			}
		    if (plateau[i][j]==-POUSSEUR){
			    printf ("\x1B[31m");
			    printf("P   ");
			    printf ("\x1B[0m");				
			}
		    if (plateau[i][j]==TIREUR){
			    printf("T   ");
			}
		    if (plateau[i][j]==-TIREUR){
			    printf ("\x1B[31m");
			    printf("T   ");
			    printf ("\x1B[0m");				
			}

		}
	}
    printf("\n");
    printf("\n");

}

void jouer_1v1(contenu plateau[TAILLE][TAILLE]){

    int i;
    int j;
    int nb_coup_possible;
    int t;
    contenu tuile;

    coup *dernier_coup=NULL;
    coup *avant_dernier_coup;
    position pos;

    deck *noir = initialiser_deck(ROUGE);
    deck *blanc = initialiser_deck(BLANC);

    deck *tmp = blanc;
    do {

	afficherPlateau(plateau);
	printf ("Au tour du joueur %d :\n",tmp->couleur+1);
	printf("Veuiller saisir la ligne i :\n");
	scanf(" %d",&i);
	printf("Veuiller saisir la colonne j :\n");
	scanf(" %d",&j);
	printf("\n");
	pos.i=i;
	pos.j=j;

	if (est_coup_possible(pos,dernier_coup,plateau)==1){
		/* code */
		
		afficherDeck(tmp);
		printf("Quelle tuile voulez-vous jouer ?\n");
		scanf(" %d",&t);
		tuile = convert_int_to_tuile(t,tmp);
		if (tuile!=VIDE){
				
			if (check_tuile_dispo(tuile,tmp)==1){
				maj_deck(tuile,tmp);
				avant_dernier_coup=dernier_coup;
				dernier_coup = jouer_coup(pos,tmp,tuile,dernier_coup,plateau);
				if (dernier_coup!=NULL){
					if (tmp==blanc){
						tmp=noir;
					}else{
					    tmp=blanc;
					}
				}else{
				    dernier_coup=avant_dernier_coup;
				}
			}else{
			    printf("tuile PLUS dispo dans le deck ! RECOMMENCEZ \n");
			}
		}
	}else{
	    printf ("\x1B[31m");
	    printf("ERREUR les positions entrés sont incorrects !!! Recommencez \n\n");
	    printf ("\x1B[0m");	
	}

	nb_coup_possible=nb_coup_possibles(dernier_coup,plateau);
	printf("NB de coups possibles : %d\n",nb_coup_possible);

    }while(nb_coup_possible!=0);

    afficherPlateau(plateau);
    resultat(plateau);

}

void jouer_solo(contenu plateau[TAILLE][TAILLE]){

    int i;
    int j;
    int nb_coup_possible;
    int t;
    contenu tuile;

    coup *dernier_coup=NULL;
    coup *avant_dernier_coup;
    position pos;

    deck *noir = initialiser_deck(ROUGE);
    deck *blanc = initialiser_deck(BLANC);

    deck *tmp = blanc;
    do {

    if(tmp==blanc){

    
		afficherPlateau(plateau);
		printf ("Au tour du joueur %d :\n",tmp->couleur+1);
		printf("Veuiller saisir la ligne i :\n");
		scanf(" %d",&i);
		printf("Veuiller saisir la colonne j :\n");
		scanf(" %d",&j);
		printf("\n");
		pos.i=i;
		pos.j=j;

		if (est_coup_possible(pos,dernier_coup,plateau)==1){
			/* code */
			
			afficherDeck(tmp);
			printf("Quelle tuile voulez-vous jouer ?\n");
			scanf(" %d",&t);
			tuile = convert_int_to_tuile(t,tmp);
			if (tuile!=VIDE){
					
				if (check_tuile_dispo(tuile,tmp)==1){
					maj_deck(tuile,tmp);
					avant_dernier_coup=dernier_coup;
					dernier_coup = jouer_coup(pos,tmp,tuile,dernier_coup,plateau);
					if (dernier_coup!=NULL){
						if (tmp==blanc){
							tmp=noir;
						}else{
						    tmp=blanc;
						}
					}else{
					    dernier_coup=avant_dernier_coup;
					}
				}else{
				    printf("tuile PLUS dispo dans le deck ! RECOMMENCEZ \n");
				}
			}
		}else{
		    printf ("\x1B[31m");
		    printf("ERREUR les positions entrés sont incorrects !!! Recommencez \n\n");
		    printf ("\x1B[0m");	
		}

		nb_coup_possible=nb_coup_possibles(dernier_coup,plateau);
		printf("NB de coups possibles : %d\n",nb_coup_possible);
	
	}else{
		afficherPlateau(plateau);
		for(int k=0;k<TAILLE;k++){
			for(int l=0;l<TAILLE;l++){
				pos.i=k;
				pos.j=l;
				if (est_coup_possible(pos,dernier_coup,plateau)==1){			
					afficherDeck(tmp);
					t = rand()%4+1;
					tuile = convert_int_to_tuile(t,tmp);
					if (tuile!=VIDE){
							
						if (check_tuile_dispo(tuile,tmp)==1){
							maj_deck(tuile,tmp);
							avant_dernier_coup=dernier_coup;
							dernier_coup = jouer_coup(pos,tmp,tuile,dernier_coup,plateau);
							if (dernier_coup!=NULL){
								if (tmp==blanc){
									tmp=noir;
								}else{
								    tmp=blanc;
								}
							}else{
							    dernier_coup=avant_dernier_coup;
							}
							k=TAILLE;
							l=TAILLE;
						}else{
						    printf("tuile PLUS dispo dans le deck ! RECOMMENCEZ \n");
						}
					}
				}
			}
		}

		nb_coup_possible=nb_coup_possibles(dernier_coup,plateau);
		printf("NB de coups possibles : %d\n",nb_coup_possible);
	}


	}while(nb_coup_possible!=0);

	afficherPlateau(plateau);
	resultat(plateau);

}


int main(int argc, char const *argv[]){
    contenu plateau[TAILLE][TAILLE];
    initialiser_plateau(plateau);
    int a;
    printf("Quel mode voulez vous jouer ?\n1-> VS Ordinateur\n2--> 1v1 \n");
    scanf(" %d",&a);

    if (a==1){
    	jouer_solo(plateau);
	}else{
		jouer_1v1(plateau);
    }

    return 0;
}
