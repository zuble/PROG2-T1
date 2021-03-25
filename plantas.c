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
	nova->alcunhas = (char**) calloc( n_alcunhas, sizeof(char*));
	if(!nova->alcunhas) return NULL;

	if ( n_alcunhas > 0 ){

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

//erro na inserçao duma alcunha que nao exista na coleçao
int planta_insere(colecao *c, planta *p){
	if(p == NULL ) return -1;

	planta * aux1 , * aux2;
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
					}
				}

				if( !alcunha_ja_existe ){
					puts("!alcunha_ja_existe");
					c->plantas[i]->n_alcunhas = c->plantas[i]->n_alcunhas + 1;
					c->plantas[i]->alcunhas = (char**) realloc( c->plantas[i]->alcunhas , c->plantas[i]->n_alcunhas * sizeof(char*) );
					c->plantas[i]->alcunhas[ c->plantas[i]->n_alcunhas - 1 ] = malloc(sizeof(char) * strlen(p->alcunhas[k])+1);
					//c->plantas[i]->alcunhas[ c->plantas[i]->n_alcunhas - 1 ] = p->alcunhas[k];
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

//verificar se existe erro na alocacao de memoria das alcunhas para char**
colecao *colecao_importa(const char *nome_ficheiro, const char *tipo_ordem){
	
	if( nome_ficheiro == NULL || tipo_ordem == NULL ) return NULL;
	
	FILE * f;
  	char buffer[500];
	char *search = "," , *line;
	char *ID , *ncient , *nsem ,*token1 , *token2;
	char **cmds = (char**) calloc(0, sizeof(char*) );
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
		//cmds = (char**) calloc(0, sizeof(char*) );
		
		ID = strtok( buffer, search);
		
		ncient = strtok( NULL, search);
		
		nsem = strtok( NULL, search);
		
		token1 = strtok( NULL , search); // token = 1º alcunha , caso tenha 
		
		if( !token1 ) {
			
			// contador para numero de alcunhas
			while(token1 != NULL) i++;
			
			token2 = strtok( buffer, search); // token2 aponta para ID

			for (int j = 0; j < 2; j++){
				token2 = strtok(NULL , search);
			}

			for (int k = 0; k < i ; k++){
				token2 = strtok(NULL , search);
				cmds[k] = realloc(cmds[k], strlen(token2) + 1);
        		strcpy(cmds[k], token2);
			}
			
			aux = planta_nova(ID , ncient , cmds, i , atoi(nsem) );
		}
		
		//nao existe alcunhas
		else aux = planta_nova(ID , ncient , NULL , 0 , atoi(nsem) );  
		
		planta_insere( c_imp , aux );
		//free(cmds);
		
	}
	
	//imprime(c_imp);
	colecao_reordena(c_imp , c_imp->tipo_ordem);
	fclose(f);
	return c_imp;
	
	//return NULL;
}

//retirar planta i , reajustar as plantas seguintes na colecao / realocar a colecao para -1
planta *planta_remove(colecao *c, const char *nomep){
	
	if ( c == NULL || nomep == NULL ) return NULL;
	/*
	planta * aux = NULL;	

	for ( int i = 0; i < c->tamanho ; i++){
		if( strcmp( c->plantas[i]->nome_cientifico , nomep ) == 0){
			puts("ola");
			aux = c->plantas[i];
		}
	}
	
	return aux;
	*/
	//******************************************
	planta * aux = NULL;	
	int k;

	for ( int i = 0; i < c->tamanho ; i++){
		if( strcmp( c->plantas[i]->nome_cientifico , nomep ) == 0){
			aux = c->plantas[i];
			k = i;
			break;
		}
	}

	if (aux != NULL)
	{
		while (k < c->tamanho)
		{
			c->plantas[k] = c->plantas[k+1];
			k++;
		}
		return aux;
	}
	else

	//******************************************
	//return aux;

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

//erro na condicao de encontrar a substring nomep no nome cientifico ou numa das alcunhas da planta i
int *colecao_pesquisa_nome(colecao *c, const char *nomep, int *tam){
	//printf("nomep : %s\n" , nomep);
	
	if ( c == NULL || nomep == NULL ) return NULL;
	
	int *indi = malloc ( sizeof(int) );    
	int achou = 0, cont = 0;

	for ( int i = 0; i < c->tamanho ; i++){
		//printf("c[%d]->nome_cientifico : %s\n" , i, c->plantas[i]->nome_cientifico );
		for (int m = 0; m < c->plantas[i]->n_alcunhas; m++){
            //printf("c[%d]->alcunhas[%d] : %s\n" , i,m, c->plantas[i]->alcunhas[m] );
			if( strstr( c->plantas[i]->alcunhas[m] , nomep ) != NULL || strstr( c->plantas[i]->nome_cientifico , nomep) != NULL ){
                achou = 1; 
            }
			if ( achou ) break;
        }
		
        if (achou==1){
			cont++;
            indi = realloc(indi, sizeof(int)*cont);
            indi[cont] = i;
			printf("%d" , indi[cont]);
			achou = 0;
        }
	}

	*tam = cont;
	if( !cont ) return NULL;
	
	return indi;
	//return NULL;
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
