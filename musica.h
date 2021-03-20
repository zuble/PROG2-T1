/*****************************************************************/
/*  Biblioteca musica  | PROG2 | MIEEC | 2019/20  */
/*****************************************************************/


#ifndef MUSICA_H

/**
* registo para armazenar elementos da lista ligada circular
* este registo contem uma string e um apontador para o proximo elemento da lista
*/
typedef struct _instante
{
  
    /** extensão de tempo em que as notas deste “instante” tocam: valores de 1-16*/
    int duracao;

    /** notas a tocar na guitarra simultaneamente: letras de A-G se não houver nota fica um '-' exemplos 'CB', '-G', 'A-', '--' */
    char notasGuitarra[2];

    /** notas a tocar no piano simultaneamente: letras de A-G se não houver nota fica um '-' exemplos 'CB', '-G', 'A-', '--' */
    char notasPiano[2];

    /** indicação individual de cada instrumento da bateria sobre se toca ou não: exemplo {1, 0, 1, 1, 0, 1, 0, 1}  */
    int bateria[8];

    /** ficheiro de som extra a tocar neste “instante” */
    char *instrumentoExtra;

    /** apontador para o próximo elemento instante */
    struct _instante *proximo;
} instante;


/**
 * musica contem apenas dois apontadores para elementos instante
 */
typedef struct
{
  /** apontador para o primeiro instante de todos armazenados */
  instante* inicio;
 
  /** apontador para o instante atualmente em reprodução ou para uso genérico se não a tocar */
  instante* cursor;
} musica;


#define LISTA_INICIO 0
#define LISTA_FIM 1

/**
 *  cria um novo instante com os valores dos parametros
 *  parametros: duracao - valor inteiro de 1 a 16
 *  parametros: notas - string que pode ser NULL se não houve notas ou "C2A3D4B5" se houve todas as notas ou as notas que houverem por exemplo "C3A5"
 *  parametros: bateria - 8 inteiros com valores de 0 ou 1, que reflete a indicação individual de cada instrumento da bateria sobre se toca ou não: exemplo {1, 0, 1, 0, 1, 1, 0, 0}
 *  parametros: instrumentoExtra - string com o nome do ficheiro de som extra se não houver ficheiro está NULL
 *  retorno: retorna o apontador para o instante criado ou NULL se não tiver sucesso ou se alguns dos parametros não tiverem dentro dos valores possiveis
 */
instante* instante_novo(int duracao, char *notas, int bateria[],  char *instrumentoExtra);


/**
 *  cria uma nova musica vazia
 *  retorno: apontador para a musica ou NULL se a musica não foi criada retorna NULL
 */

musica* musica_nova();

/**
 *  insere um instante na posicao especificada
 *  parametro: m apontador para a musica
 *  parametro: t instante a inserir
 *  parametro: pos  posicao na musica que se pretende inserir o novo instante,
 *             se pos=-1 insere no fim da lista
 *  retorno: 0 se for com sucesso e -1 se ocorrer um erro e a musica ou o instante forem NULL
 *  observacoes: a primeira posicao da musica e´ pos=0 e o pos nao pode ultrapasar o numero de instantes que a musica contem
 */
int  instante_insere(musica *m, instante *t, int pos );

/**
 *  indica o numero de instantes na musica
 *  parametro: m apontador para a musica
 *  retorno: numero de instantes da musica ou -1 se musica = NULL ou ocorra um erro
 */
int musica_tamanho(musica *m);

/**
 *  pesquisa uma nota especifica da Guitarra ou Piano
 *  parametro: m apontador para a musica
 *  parametro: nota (A-G)
 *  parametro: instrumento 0=guitarra 1=piano
 *  retorno: apontador para o primeiro instante que tenha a nota naquele instrumento ou NULL se ocorrer um erro
 */
instante * musica_pesquisa_nota(musica * m, char nota, int instrumento);

/**
 *  remove o instante da posicao especificada
 *  parametro: m apontador para a musica
 *  parametro: pos posicão na musica do instante que se pretende remover
 *  retorno: apontador para instante removido da musica ou NULL se ocorrer um erro ou musica=NULL
 *  observacoes: o pos nao pode ultrapasar o numero de instantes que a musica contem
 */
instante* instante_remove(musica * m, int pos);

/**
 *  elimina um instante, libertando toda a memoria ocupada
 *  parametro: t apontador para a instante
 *  retorno: 0 se for com sucesso e -1 em caso t = NULL ou insucesso 
 */
int instante_apaga(instante * t);

/**
 *  elimina uma musica, libertando toda a memoria ocupada
 *  parametro: m apontador para musica 
 *  retorno: 0 se for com sucesso e -1 em caso m = NULL ou insucesso 
 */
int musica_apaga(musica *m);

/** 
 * lê o conteúdo do ficheiro de texto de nome nomef para o registo musica.
 * parametro: nomef nome do ficheiro
 * retorno: apontador para a musica criada. Em caso de erro retorna NULL. 
 * observacao: O conteúdo do ficheiro está no formato: 
 *              Duração do instante, 8 valores binários (0-1) correspondentes à ativação de cada instrumento da bateria ( Surdo, Timbalão1, Timbalão2, Prato1, Prato2, Címbalo, Tarola, Bombo). 
 *              Seguem-se potencialmente as notas dos instrumentos pela ordem guitarLow, guitarHigh, pianoLow, pianoHigh e por fim o eventual nome do ficheiro extra a tocar nesse instante. 
 *              Os instrumentos guitarra e piano apresentam as notas como uma string de 2 caracteres, com a nota (A-G) e a oitava (2-3 guitarra, 4-5 piano).
 */
musica *musica_importa(const char *nomef);

/**
 * Avança o cursor de reprodução para o instante duracao tempos à frente face ao cursor atual. 
 * parametro: m apontador para a musica
 * parametro: duracao numero de tempos a avançar
 * retorno: 0 se bem sucedido ou -1 caso contrário
 * erros: m inválido, duracao negativa
 * observacao: se ficar a meio de um instante o cursor deverá apontar para o instante seguinte
 *             caso a duracao a avançar seja superior à duração total da música, o cursor deve "dar a volta" e reiniciar
 */
int musica_toca(musica *m, int duracao);

/**
 * Altera o conteúdo da musica consoante as operações guardadas no ficheiro apontado pelo argumento "ficheiro".
 * Use o ficheiro variante_B.txt para testar a sua implementação. 
 * parametro: m apontador para a musica
 * parametro: ficheiro nome do ficheiro que contem as correções a serem feitas
 * retorno: número de operações bem sucedidas e -1 em caso de erro
 * erros: m, notas, instrumentos e posições inválidas 
 *        (os instantes não podem ser negativos nem exceder o tamanho da musica)
 * observacao: O conteúdo do ficheiro variante_B.txt segue o seguinte formato:
 *  [tipo de modificação] - valores de 1 a 4
 * 
 *  Caso seja 1:
 *      1 [1º instante a ser removido] [último instante a ser removido]
 *      Exemplo:
 *          1 4 7
 *          - Significa remover os instantes de 4 a 7 (inclusive).
 * 
 *  Caso seja 2:
 *      2 [guitarra ou piano] [nota a alterar] [nova nota]
 *      Exemplo:
 *          2 0 A C
 *          - Altera na guitarra todos os instantes que têm a nota A para C.
 * 
 *  Caso seja 3:
 *      3 [qual o instrumento da bateria de 0-7] [0 para silenciar, 1 para tocar] [posição inicial] [posição final]
 *      Exemplo:
 *          3 1 1 5 7
 *          - Altera o instrumento 1 para o estado "tocar" da posição 5 a 7 (inclusive).
 * 
 *  Caso seja 4:
 *      4 [nova duração] [posição inicial] [posição final]
 *      Exemplo:
 *          4 3 7 10
 *          - Altera todos os instantes de 7 a 10 (inclusive) para a duração 3.
 * 
 */
int musica_corrige(musica *m, char *ficheiro);


#define MUSICA_H
#endif
