/*****************************************************************/
/*          Biblioteca plantas | PROG2 | MIEEC | 2020/21         */
/*****************************************************************/

#ifndef PLANTAS_H
#define MAX_NAME 200
/*
* registo para armazenar elementos do vetor dinamico
* este registo contem duas strings (ID e nome_cientifico), dois inteiros (n_alcunhas e n_sementes) e um vetor de apontadores para char (alcunhas)
*/
typedef struct
{
  /** identificacao unica no catalogo **/
  char ID[10];

  /** designacao cientifica */
  char nome_cientifico[MAX_NAME];

  /** lista de nomes locais correntes dados a especie **/
  char **alcunhas;

  /** numero total de alcunhas da planta **/
  int n_alcunhas;

  /** numero de sementes guardadas no cofre **/
  int n_sementes;

} planta;

/*
* colecao contem um vetor de apontadores do tipo planta, o tamanho desse vetor e o tipo de ordenacao da colecao
*/
typedef struct
{
  /** apontador para o array de plantas armazenadas (vetor de apontadores do tipo planta) **/
  planta **plantas;

  /** tamanho do vetor de plantas **/
  long tamanho;

  /** indicacao do campo para ordenacao crescente do vetor: ‘nome’ - para nome_cientifico; ‘id’ - para campo de identificacao unica **/
  char tipo_ordem[5];

} colecao;

/*
*  cria uma nova planta com os valores dos parametros
*  parametro: ID - string de 10 carateres contendo o identificador unico da planta
*  parametro: nome_cientifico - string de MAX_NAME carateres contendo o nome cientifico da planta
*  parametro: alcunhas - vetor (de strings) contendo as possiveis alcunhas da planta; pode ser NULL caso nao existam alcunhas para a planta
*  parametro: n_alcunhas - inteiro contendo o tamanho (numero de alcunhas) do vetor alcunhas
*  parametro: n_sementes - inteiro contendo o numero de sementes da planta a guardar na colecao
*  retorno: retorna o apontador para a planta criada ou NULL se ocorrer algum erro ou se algum dos parametros nao estiver dentro da gama de valores valida
*/
planta *planta_nova(const char *ID, const char *nome_cientifico, char **alcunhas, int n_alcunhas, int n_sementes);

/*
*  cria uma nova colecao vazia
*  parametro: tipo_ordem - string contendo o tipo de ordenacao da nova colecao; ‘nome’ - para nome_cientifico ou ‘id’ - para campo de identificacao unica
*  retorno: apontador para a colecao ou NULL se ocorreu algum erro
*/
colecao *colecao_nova(const char *tipo_ordem);

/*
*  insere uma planta na colecao, na posicao correta de acordo com o tipo_ordem
*  parametro: c - apontador para a colecao
*  parametro: p - planta a inserir
*  retorno: 0 se a planta nao existia e foi inserida com sucesso, 1 se a planta ja existia e apenas foi atualizada e -1 se ocorrer um erro
*  observacoes: caso a planta ja exista (tenha o mesmo ID) deve atualizar o numero de sementes e acrescentar as novas alcunhas (garantindo que nao ha alcunhas repetidas)
*/
int planta_insere(colecao *c, planta *p);

/*
*  indica o numero de plantas na colecao
*  parametro: c - apontador para a colecao
*  retorno: numero de plantas da colecao ou -1 em caso de erro
*/
int colecao_tamanho(colecao *c);

/*
*  cria uma colecao, le o conteudo do ficheiro de texto de nome nome_ficheiro e importa-o para a colecao criada
*  parametro: nome_ficheiro - nome do ficheiro de texto contendo a colecao a importar
*  parametro: tipo_ordem - tipo de ordenacao da nova colecao; ‘nome’ - para nome_cientifico ou ‘id’ - para campo de identificacao unica
*  retorno: apontador para a colecao criada. Em caso de erro retorna NULL. 
*  observacao: A colecao deve ser ordenada de acordo com tipo_ordem.
               O conteudo do ficheiro esta no formato: ID,nome_cientifico,numero de sementes,alcunha0,alcunha1,...,alcunhaN ou ID,nome_cientifico,numero de sementes caso nao existam alcunhas.
*/
colecao *colecao_importa(const char *nome_ficheiro, const char *tipo_ordem);

/*
*  remove da colecao a planta com nome cientifico dado por nomep e corrige a colecao no elemento retirado
*  parametro: c - apontador para a colecao
*  parametro: nomep - nome cientifico da planta a remover
*  retorno: apontador para a planta removida da colecao ou NULL se ocorrer um erro (ou a planta nao existir na colecao)
*/
planta *planta_remove(colecao *c, const char *nomep);

/*
*  elimina uma planta, libertando toda a memoria por ela ocupada
*  parametro: p - apontador para a planta
*  retorno: 0 se remocao ocorrer com sucesso e -1 em caso de erro
*/
int planta_apaga(planta *p);

/*
*  elimina uma colecao, libertando toda a memoria por ela ocupada
*  parametro: c - apontador para a colecao 
*  retorno: 0 se bem sucedida e -1 em caso de insucesso
*/
int colecao_apaga(colecao *c);

/*
*  pesquisa todas as plantas que contenham a totalidade de nomep no nome cientifico ou nas alcunhas e retorna um vetor com as posicoes dessas plantas na colecao
*  parametro: c - apontador para a colecao 
*  parametro: nomep - nome a procurar
*  parametro: tam - apontador para o tamanho do vetor retornado/numero total de plantas encontradas
*  retorno: vetor de indices/posicoes das plantas encontradas. O tamanho deste vetor e retornado por referencia no parametro tam.
*/
int *colecao_pesquisa_nome(colecao *c, const char *nomep, int *tam);

/*
*  reordena a colecao de acordo com o tipo_ordem; ‘nome’ - ordena alfabeticamente por nome_cientifico; ‘id’ - ordena alfabeticamente pelo campo de identificacao unica
*  parametro: c - apontador para a colecao 
*  parametro: tipo_ordem - tipo de ordenacao a ser executada
*  retorno: 1 se for necessario reordenar e a reordenacao ocorrer com sucesso, 0 se nao for necessario reordenar e -1 em caso de erro
*  observacao: atualiza o campo tipo_ordem da colecao para o novo tipo_ordem
*/
int colecao_reordena(colecao *c, const char *tipo_ordem);

#define PLANTAS_H
#endif
