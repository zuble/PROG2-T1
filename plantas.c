/*****************************************************************/
/*          Biblioteca plantas | PROG2 | MIEEC | 2020/21         */
/*****************************************************************/

#include "plantas.h"
#include <string.h>
#include <stdlib.h>
#include <stdio.h>

planta *planta_nova(const char *ID, const char *nome_cientifico, char **alcunhas, int n_alcunhas, int n_sementes){
	
	if( ID == NULL || nome_cientifico == NULL || alcunhas == NULL || n_alcunhas < 0 || n_sementes < 0) return NULL;

	planta* nova = (planta*) malloc(sizeof(planta));

	strncpy( nova->ID , ID , 10 );
	strncpy( nova->nome_cientifico , nome_cientifico , MAX_NAME);
	nova->alcunhas = alcunhas;
	nova->n_alcunhas = n_alcunhas;
	nova->n_sementes = n_sementes;

	return nova;
}

colecao *colecao_nova(const char *tipo_ordem){

	if(tipo_ordem == NULL) return NULL;

	colecao* nova = (colecao*)malloc(sizeof(colecao));
	if( nova == NULL ) return NULL;

	nova->tamanho = 0;
	strncpy( nova->tipo_ordem , tipo_ordem , 5 );
	nova->plantas = NULL;

	return nova;
}

int planta_insere(colecao *c, planta *p){
	
	if(c == NULL || p == NULL ) return -1;

	planta * aux;
	long int i ;
	int aux_alcunha = 0 ;

	printf("%ld" , c->tamanho);
	//************************************************************************************
	if (c->tamanho  != 0 ){
		puts("ola");
		for (i = 0; i < c->tamanho; i++){
			
			//existe planta com mesmo ID 
			if ( strcmp( c->plantas[i]->ID , p->ID ) == 0 ) {
				
				//atualiza nº sementes
				c->plantas[i]->n_sementes =+ p->n_sementes;
				int n_alcunha_c = c->plantas[i]->n_alcunhas;
				int n_alcunha_p = p->n_alcunhas;
				
				//atualiza alcunhas
				for ( int k = 0; k < p->n_alcunhas ; k++){
					for (int m = 0; m < n_alcunha_c; m++){
						if( strcmp( p->alcunhas[k] , c->plantas[i]->alcunhas[m] ) == 0){
							aux_alcunha = 1; //alcunha k já existe
						}
					}
					if( aux_alcunha == 0){
						c->plantas[i]->alcunhas[n_alcunha_c] = p->alcunhas[k];
					}
					aux_alcunha = 0;				
				}
			
				return 1;			
			}

			if ( strcmp(c->tipo_ordem , "nome") == 0 ) {
				puts("poal");			
			}

			if (  strcmp(c->tipo_ordem , "id") == 0 ) {
				puts("poal");			
			}

		}

	}

	else{
		puts("ola");
		
		//strncpy( c->plantas[0]->ID , p->ID , 10 );
		//strncpy( c->plantas[0]->nome_cientifico , p->nome_cientifico , MAX_NAME);
		//c->plantas[0]->alcunhas = p->alcunhas;
		//c->plantas[0]->n_alcunhas = p->n_alcunhas;
		//c->plantas[0]->n_sementes = p->n_sementes;
		
		c->plantas[0] = p ;
		return 0;
	}
//********************************************************************************************
	return -1;
}
int colecao_tamanho(colecao *c){
	if(c == NULL) return -1;


	return c->tamanho;
}

colecao *colecao_importa(const char *nome_ficheiro, const char *tipo_ordem){
	return NULL;
}

planta *planta_remove(colecao *c, const char *nomep){
	return NULL;
}

int planta_apaga(planta *p){
	if(p == NULL) return -1;

	free(p);
	return 0;
}

int colecao_apaga(colecao *c){
	if(c == NULL) return -1;

	if(c->tamanho > 0){
		for (int i = 0; i < c->tamanho; i++){
			planta_apaga(c->plantas[i]);
		}
	}

	free(c);
	return 0;
}

int *colecao_pesquisa_nome(colecao *c, const char *nomep, int *tam){

	int indi[100];
	int achou = 0, cont = 0;

	for ( int i = 0; k < c->tamanho ; i++){
		if( strcmp( nomep , c->plantas[i]->nome_cientifico ) == 0){
				achou = 1; //a plante tem o nomep
		}

		else for (int m = 0; m < n_alcunha_c; m++){
			if( strcmp( nomep , c->plantas[i]->alcunhas[m] ) == 0){
				achou = 1; //a plante tem o nomep
				m == n_alcunha_c;
			}
		}
	
		if (achou==1)
		{
			indi[cont] = c->plantas[i]->ID;
			achou = 0;
			cont++;
		}
	}

	*tam=cont;
	if (cont!=0)
		return indi;
	else
		return NULL;

	
}

int colecao_reordena(colecao *c, const char *tipo_ordem){
	return -1;
}