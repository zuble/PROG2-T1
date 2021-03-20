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
	//printf("\n\n%s\n\n" , tipo_ordem);
	strncpy( nova->tipo_ordem , tipo_ordem , 5 );
	//printf("\n\n%s\n\n" , nova->tipo_ordem);
	return nova;
}

int planta_insere(colecao *c, planta *p)
{
	return -1;
}
int colecao_tamanho(colecao *c)
{
	return -1;
}

colecao *colecao_importa(const char *nome_ficheiro, const char *tipo_ordem)
{
	return NULL;
}
planta *planta_remove(colecao *c, const char *nomep)
{
	return NULL;
}

int planta_apaga(planta *p)
{
	return -1;
}
int colecao_apaga(colecao *c)
{
	return -1;
}
int *colecao_pesquisa_nome(colecao *c, const char *nomep, int *tam)
{
	return NULL;
}
int colecao_reordena(colecao *c, const char *tipo_ordem)
{
	return -1;
}
