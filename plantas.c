/*****************************************************************/
/*          Biblioteca plantas | PROG2 | MIEEC | 2020/21         */
/*****************************************************************/

#include "plantas.h"
#include <string.h>
#include <stdlib.h>
#include <stdio.h>

planta *planta_nova(const char *ID, const char *nome_cientifico, char **alcunhas, int n_alcunhas, int n_sementes){

	if( ID == NULL || sizeof(ID) > 10 || nome_cientifico == NULL || sizeof(nome_cientifico) > MAX_NAME|| n_alcunhas < 0 || n_sementes < 0) return NULL;

	planta* nova = (planta*) malloc(sizeof(planta));
	if(!nova) return NULL;

	strcpy( nova->ID , ID );
	strcpy( nova->nome_cientifico , nome_cientifico );
	nova->n_sementes = n_sementes;
	nova->n_alcunhas = n_alcunhas;

	if ( n_alcunhas > 0 ){

		nova->alcunhas = calloc( n_alcunhas, sizeof(char*));
		if(!nova->alcunhas) return NULL;
	
		for ( int  i = 0; i < n_alcunhas; i++){

			nova->alcunhas[i]= malloc(sizeof(char) * (strlen(alcunhas[i]) + 1 ));
            strcpy(nova->alcunhas[i], alcunhas[i]);

		}
	}
	else nova->alcunhas = NULL;

	return nova;
}

colecao *colecao_nova(const char *tipo_ordem){
	
	if(tipo_ordem == NULL) return NULL;

	colecao* nova = (colecao*)malloc(sizeof(colecao));
	if( nova == NULL ) return NULL;

	nova->tamanho = 0;
	strcpy( nova->tipo_ordem , tipo_ordem);
	nova->plantas = (planta**)malloc( sizeof(planta*));
	//nova->plantas = NULL;
	
	return nova;
}

int planta_insere(colecao *c, planta *p){
	if(c == NULL || p == NULL ) return -1;

	int alcunha_ja_existe;

	for (int i = 0; i < c->tamanho; i++){

		//caso exista planta com mesmo ID que p
		if ( strcmp( c->plantas[i]->ID , p->ID ) == 0 ) {

			//atualiza nº sementes
			c->plantas[i]->n_sementes = c->plantas[i]->n_sementes + p->n_sementes;

			//atualiza alcunhas
			for ( int k = 0; k < p->n_alcunhas ; k++){
				alcunha_ja_existe = 0;
				for (int m = 0; m < c->plantas[i]->n_alcunhas ; m++){

					if( strcmp( p->alcunhas[k] , c->plantas[i]->alcunhas[m] ) == 0) {
						alcunha_ja_existe = 1;
						break;
					}
				}

				if( !alcunha_ja_existe ){

					if( c->plantas[i]->n_alcunhas == 0 ) c->plantas[i]->alcunhas = (char**)malloc(sizeof(char*));

					else c->plantas[i]->alcunhas = (char**)realloc( c->plantas[i]->alcunhas , (c->plantas[i]->n_alcunhas + 1) * sizeof(char*) );
					
					c->plantas[i]->alcunhas[ c->plantas[i]->n_alcunhas ] = malloc(sizeof(char) * ( strlen(p->alcunhas[k])+1 ));
					memcpy(c->plantas[i]->alcunhas[ c->plantas[i]->n_alcunhas ], p->alcunhas[k],strlen(p->alcunhas[k])+1);
					c->plantas[i]->n_alcunhas++;
				}
			}
			return 1;
		}
	}

	//insere no fim do vetor plantas
	c->tamanho++;
	c->plantas = (planta**)realloc(c->plantas , c->tamanho * sizeof(planta*));
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
  	char buffer[300];
	char *search = "," , *line = NULL;
	char *ID , *ncient , *nsem ,*token1 , *token2;
	char **cmds;
	int count_alc = 0 , aux_ins; 
 	size_t len = 0;

	f = fopen(nome_ficheiro, "r");
	if (f == NULL) return NULL;
	
	colecao * c_imp = colecao_nova(tipo_ordem);
	planta * aux;
	
	while ( getline(&line, &len, f) != -1 ){
		
		strcpy(buffer , line);
		count_alc = 0;	
		aux = NULL;	
		
		ID = strtok( buffer, search);
		ncient = strtok( NULL, search);
		nsem = strtok( NULL, search);
		
		// contador numero de alcunhas da plantas
		while(1) { 
			token1 = strtok( NULL , search);
			if( token1 == NULL) break; 
			count_alc++; 
		}

		strcpy(buffer , line);
		
		//planta possui alcunhas
		if( count_alc > 0 ) {
			
			strtok( buffer, search); 
			strtok(NULL , search);
			strtok(NULL , search);

			cmds = (char**) malloc( count_alc * sizeof(char*));
			
			for (int k = 0; k < count_alc ; k++){
				
				token2 = strtok(NULL , search); //aponta para a primeira alcunha quando k = 0
				cmds[k]= (char *)malloc(sizeof(char) * ( strlen(token2) + 1 ) );
        		strcpy(cmds[k], token2);
				
			}
			aux = planta_nova(ID , ncient , cmds , count_alc , atoi(nsem) );  
		}
		
		//planta não possui alcunhas
		else { 
			ID = strtok( buffer, search);
			ncient = strtok( NULL, search);
			nsem = strtok( NULL, search);
			aux = planta_nova(ID , ncient , NULL , 0 , atoi(nsem) ); 
		}
		
		//insere planta aux em c_imp
		aux_ins = planta_insere( c_imp , aux );
		if ( aux_ins == -1 ) return NULL;
		else if ( aux_ins == 1 ) planta_apaga(aux);

		//liberta memória em cmds
		for(int k = 0; k < count_alc ; k++) free(cmds[k]);
		free(cmds);
		cmds = NULL;
	}
	
	colecao_reordena(c_imp , c_imp->tipo_ordem);
	fclose(f);
	free(line);
	return c_imp;
}

planta *planta_remove(colecao *c, const char *nomep){
	
	if ( c == NULL || nomep == NULL ) return NULL;
	
	planta * aux = NULL;
	int k = 0 , i;

	for ( i = 0; i < c->tamanho ; i++){
		if( strcmp( c->plantas[i]->nome_cientifico , nomep ) == 0){
			aux = c->plantas[i];
			break;
		}
	}

	if (aux != NULL){
		while (i < c->tamanho-1){
			c->plantas[i] = c->plantas[i+1];
			i++;
		}
		c->tamanho --;
	}
	return aux;
}

int planta_apaga(planta *p){
	if(p == NULL) return -1;

	if( p->n_alcunhas > 0){
		for (int i = 0; i < p->n_alcunhas; i++){
			free(p->alcunhas[i]);
		}
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
	
	if ( c == NULL || nomep == NULL ) return NULL;
    
    int *indi = malloc ( sizeof(int) );    
    int achou = 0, cont = 0;
 
    for ( int i = 0; i < c->tamanho ; i++){
        
        if(strstr( c->plantas[i]->nome_cientifico , nomep) != NULL){
            achou = 1;
        }
        else {
            for (int m = 0; m < c->plantas[i]->n_alcunhas; m++){
                
				if(strstr( c->plantas[i]->alcunhas[m] , nomep) != NULL){
                    achou = 1;
                    break;
                }
            }
        }
        
        if (achou==1){
            cont++;
            indi = realloc(indi, sizeof(int)*cont);
            indi[cont-1] = i;
            achou = 0;
        }
    }
 
    *tam = cont;
    if( !cont ) return NULL;
    return indi;
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
				}
			}
		}
	}
	
	if( strcmp(c->tipo_ordem , tipo_ordem) != 0){
		strcpy(c->tipo_ordem , tipo_ordem);
	}
	if( ordem == 1 ) return 1;
	if( ordem == 0 ) return 0;	
}