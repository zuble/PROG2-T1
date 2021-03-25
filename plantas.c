/*****************************************************************/
/*          Biblioteca plantas | PROG2 | MIEEC | 2020/21         */
/*****************************************************************/

#include "plantas.h"
#include <string.h>
#include <stdlib.h>
#include <stdio.h>

void imprime(colecao * c){
	for (int i = 0; i < c->tamanho; i++){
		printf("plantas [%d] ~~ nome : %s | id : %s | nºalcunhas : %d | nºsementes : %d \n" , i , c->plantas[i]->nome_cientifico , c->plantas[i]->ID , c->plantas[i]->n_alcunhas , c->plantas[i]->n_sementes);
	}
	puts("");
	/*
	puts("alcunhas");
	for( int k = 0 ; k < c->tamanho ; k++){
		printf("%s : " , c->plantas[k]->nome_cientifico);
		for (int i = 0; i < c->plantas[k]->n_alcunhas; i++){
			printf("%s |", c->plantas[k]->alcunhas[i]);
		}
		puts("");
	}
	puts("");
	*/
}

planta *planta_nova(const char *ID, const char *nome_cientifico, char **alcunhas, int n_alcunhas, int n_sementes){

	if( ID == NULL || sizeof(ID) > 10 || nome_cientifico == NULL || sizeof(nome_cientifico) > MAX_NAME|| n_alcunhas < 0 || n_sementes < 0) return NULL;

	planta* nova = (planta*) malloc(sizeof(planta));
	if(!nova) return NULL;

	strncpy( nova->ID , ID , 10 );
	strncpy( nova->nome_cientifico , nome_cientifico , MAX_NAME);
	nova->n_sementes = n_sementes;
	nova->n_alcunhas = n_alcunhas;

	if ( n_alcunhas > 0 ){
	
		nova->alcunhas = (char**) calloc( n_alcunhas, sizeof(char*));
		if(!nova->alcunhas) return NULL;

		for ( int  i = 0; i < n_alcunhas; i++){

			nova->alcunhas[i]= (char *)malloc(sizeof(char) * strlen(alcunhas[i]) + 1 );
            strcpy(nova->alcunhas[i], alcunhas[i]);

		}
	}

	return nova;
}

colecao *colecao_nova(const char *tipo_ordem){
	
	if(tipo_ordem == NULL) return NULL;

	colecao* nova = (colecao*)malloc(sizeof(colecao));
	if( nova == NULL ) return NULL;

	nova->tamanho = 0;
	strncpy( nova->tipo_ordem , tipo_ordem , 5 );
	nova->plantas = (planta**) malloc( sizeof(planta*));
	//nova->plantas = NULL;
	
	return nova;
}

int planta_insere(colecao *c, planta *p){
	if(p == NULL ) return -1;

	planta * aux1 , * aux2;
	int aux_alcunha = 0;

	for (int i = 0; i < c->tamanho; i++){

		//caso exista planta com mesmo ID que p
		if ( strcmp( c->plantas[i]->ID , p->ID ) == 0 ) {

			//atualiza nº sementes
			c->plantas[i]->n_sementes = c->plantas[i]->n_sementes + p->n_sementes;

			//atualiza alcunhas
			for ( int k = 0; k < p->n_alcunhas ; k++){
				
				for (int m = 0; m < c->plantas[i]->n_alcunhas ; m++){

					if( strcmp( p->alcunhas[k] , c->plantas[i]->alcunhas[m] ) != 0) {
						/*
						c->plantas[i]->n_alcunhas = c->plantas[i]->n_alcunhas + 1;
						c->plantas[i]->alcunhas = (char**) realloc( c->plantas[i]->alcunhas , c->plantas[i]->n_alcunhas * sizeof(char*) );
						c->plantas[i]->alcunhas[ c->plantas[i]->n_alcunhas - 1 ] = (char *)malloc(sizeof(char) * strlen(p->alcunhas[k]+1));
						c->plantas[i]->alcunhas[ c->plantas[i]->n_alcunhas - 1 ] = p->alcunhas[k];*/

					}
				}
			}
			return 1;
		}
	}

	//insere no fim do vetor plantas
	c->tamanho++;
	c->plantas = (planta**)realloc(c->plantas , c->tamanho * sizeof(planta));
	c->plantas[c->tamanho-1] = p;
	//reordena
	colecao_reordena(c, c->tipo_ordem);

	return 0;
}

int colecao_tamanho(colecao *c){
	if(c == NULL) return -1;

	return c->tamanho;
}

colecao *colecao_importa(const char *nome_ficheiro, const char *tipo_ordem){
	
	if( nome_ficheiro == NULL || tipo_ordem == NULL ) return NULL;
	
	FILE * f;
  	char buffer[500];
	char *search = "," , *line;
	char *ID , *ncient , *nsem ,*token;
	int i = 0 ; 
 	size_t len = 0;
  	ssize_t read;

	f = fopen(nome_ficheiro, "r");
	if (f == NULL) return NULL;
	
	colecao * c_imp = colecao_nova(tipo_ordem);
	planta * aux;
	
	while ((read = getline(&line, &len, f)) != -1 ){
		
		strcpy(buffer , line);
		i = 0;
		char **cmds = (char **) calloc(0, sizeof(char*) );
		ID = strtok( buffer, search);
		
		ncient = strtok( NULL, search);
		
		nsem = strtok( NULL, search);
		
		token = strtok( NULL , search);
		
		if( !token ) {
			
			while(token != NULL){
				//cmds[i] = token ;
				i++;
				//token = strtok( NULL , search);
			}
			//token = strtok( buffer, search);

			//for (int j = 0; j < 3; j++){
			//	token = strtok(NULL , search);
			//}
			
			aux = planta_nova(ID , ncient , NULL, i , atoi(nsem) );
		}
		else { 
			aux = planta_nova(ID , ncient , NULL , i , atoi(nsem) );	
		} 
		planta_insere( c_imp , aux );
		//free(cmds);
		
	}
	
	//imprime(c_imp);
	colecao_reordena(c_imp , c_imp->tipo_ordem);
	fclose(f);
	return c_imp;
	
	//return NULL;
}

planta *planta_remove(colecao *c, const char *nomep){

	return NULL;
}

int planta_apaga(planta *p){
	if(p == NULL) return -1;

	for (int i = 0; i < p->n_alcunhas; i++){
        free(p->alcunhas[i]);
    }

    free(p->alcunhas);
    free(p);
	p = NULL;

    return 0;
}

int colecao_apaga(colecao *c){
	if(c == NULL) return -1;

	if(c->tamanho > 0){
		for (int i = 0; i < c->tamanho; i++){
			planta_apaga(c->plantas[i]);
		}
	}
	free(c->plantas);
	free(c);
	c = NULL;

	return 0;
}

int *colecao_pesquisa_nome(colecao *c, const char *nomep, int *tam){
	/*
	int *indi = calloc(0, sizeof(int));    //TROCAR O 100
    int achou = 0, cont = 0;

    for ( int i = 0; i < c->tamanho ; i++){
        if( strstr( c->plantas[i]->nome_cientifico , nomep) != NULL){
                achou = 1; //a planta tem o nomep
        }

        else for (int m = 0; m < c->plantas[i]->n_alcunhas; m++){
            if( strstr( c->plantas[i]->alcunhas[m] , nomep ) != NULL ){
                achou = 1; //a planta tem o nomep
                m = c->plantas[i]->n_alcunhas;
            }
        }

        if (achou==1){
            indi = (int*)realloc(indi, cont+1);
            indi[cont] = i;
            achou = 0;
            cont++;
        }
	}
	*tam = cont;
	if( !cont ) return NULL;
	*/
	return 	NULL;
}

int colecao_reordena(colecao *c, const char *tipo_ordem){
	
	if( c == NULL || tipo_ordem == NULL ) return -1;
	if( c->tamanho == 0) return 0;
	planta * aux;
	int ordem = 0;

	if( strcmp( "nome" , tipo_ordem ) == 0 ){
		
		for (int i = 0; i < c->tamanho; i++){
			for (int k = i + 1; k < c->tamanho; k++){

				if ( strcmp(c->plantas[i]->nome_cientifico , c->plantas[k]->nome_cientifico ) > 0) {
					ordem = 1;
					aux = c->plantas[i];
					c->plantas[i] = c->plantas[k];
					c->plantas[k] = aux;
					//imprime(c);
				}

			}

		}
		
	}

	if( strcmp( "id" , tipo_ordem ) == 0 ){

		for (int i = 0; i < c->tamanho; i++){
			for (int k = i + 1; k < c->tamanho; k++){

				if ( strcmp(c->plantas[i]->ID , c->plantas[k]->ID ) > 0) {
					ordem = 1;
					aux = c->plantas[i];
					c->plantas[i] = c->plantas[k];
					c->plantas[k] = aux;
					//imprime(c);
				}

			}

		}
		
	}
	
	strcpy(c->tipo_ordem , tipo_ordem);
	if( ordem == 1 ) return 1;
	if( ordem == 0 ) return 0;
	
}
