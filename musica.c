/*****************************************************************/
/*Biblioteca musica | PROG2 | MIEEC | 2019/20     */
/*****************************************************************/

#include "musica.h"
#include <string.h>
#include <stdlib.h>
#include <stdio.h>

instante *instante_novo(int duracao, char *notas, int bateria[], char *instrumentoExtra)
{
    /* cria instante */
    instante *novo = (instante *)malloc(sizeof(instante));
    novo->notasGuitarra[0]=0;
    novo->notasGuitarra[1]=0;
    novo->notasPiano[0]=0;
    novo->notasPiano[1]=0;
    if (duracao > 0 && duracao < 17) /* verifica se a duração está entre os valores previstos */
    {
        novo->duracao = duracao;
    }
    for (int i = 0; i < strlen(notas); i++)
    {
        if (notas[i] == '2')
        {
            novo->notasGuitarra[0] = notas[i - 1];
        }
        else if (notas[i] == '3')
        {
            novo->notasGuitarra[1] = notas[i - 1];
        }
        else if (notas[i] == '4')
        {
            novo->notasPiano[0] = notas[i - 1];
        }
        else if (notas[i] == '5')
        {
            novo->notasPiano[1] = notas[i - 1];
        }
    } /*se as notas nao foram copiadas, pois os numeros nao estavam presentes */
    if (novo->notasGuitarra[0] == ' ')
    {
        novo->notasGuitarra[0] = '-';
    }
    if (novo->notasGuitarra[1] == ' ')
    {
        novo->notasGuitarra[1] = '-';
    }
    if (novo->notasPiano[0] == ' ')
    {
        novo->notasPiano[0] = '-';
    }
    if (novo->notasPiano[1] == ' ')
    {
        novo->notasPiano[1] = '-';
    }

    for (int i = 0; i < 8; i++)
    {
        if (bateria[i] == 0 || bateria[i] == 1) /* verifica se os numeros de bateria sao 0 e 1 */
        {
            novo->bateria[i] = bateria[i];
        }
        else
            return NULL;
    }
    
    if (instrumentoExtra == NULL)
    {

        novo->instrumentoExtra = NULL;
    }
    else
    {   
         novo->instrumentoExtra = (char *)malloc((strlen(instrumentoExtra)+1 ) * sizeof(char));
        strcpy(novo->instrumentoExtra, instrumentoExtra);
    }
    return novo;
}

musica *musica_nova()
{
    /* cria música */
    musica *msc = (musica *)malloc(sizeof(musica));
    if (msc == NULL)
        return NULL;
        msc->cursor=NULL;
        msc->inicio=NULL;

    return msc;
}

int instante_insere(musica *m, instante *t, int pos)
{
    instante *aux, *elemento;
    if(m==NULL || t==NULL ){
        return -1;
    }
    
    if (m->inicio == NULL) /* se nao ha instantes em musica */
    {
        m->inicio = t;
        m->inicio->proximo = m->inicio;
    }
    else if (pos == -1) /*insere instante no final da musica  */
    {
        elemento = m->inicio->proximo;
        while (elemento->proximo != m->inicio)
        {
            elemento = elemento->proximo;
        }
        elemento->proximo = t;
        t->proximo = m->inicio;
    }
    else
    {
        elemento = m->inicio;
        for (int i = 0; i < pos - 2; i++) /*insere instante em pos  */
        {
            elemento = elemento->proximo;
        }
        aux = elemento->proximo;
        elemento->proximo = t;
        t->proximo = aux;
    }
    
    return 0;
}

int musica_tamanho(musica *m)
{
     instante *aux;
    int cont = 1;/*cont=1 pois o ciclo while nao conta o instante aux=m->inicio */
    if (m == NULL)
    {
        return -1;
    }
    aux = m->inicio;
    while (aux->proximo != m->inicio) /* aux vai percorrer todos os elementos e contá-los */
    {
        aux = aux->proximo;
        cont++;
    }
    
    return cont; 

}

instante *musica_pesquisa_nota(musica *m, char nota, int instrumento)
{
    instante *elemento;
 
    
    if (nota > 64 && nota < 72) /*verifica se nota  está entre A-G */
    {
        if (instrumento == 0)
        {
            elemento= m->inicio;
            while (elemento->proximo != m->inicio)/*percorre todos os instantes a procura da nota, quando a encontrar retorna o instante */
            {
                for (int i = 0; i < 2; i++)
                {
                    if (elemento->notasGuitarra[i] == nota)
                    {
                        return elemento;
                    }
                }
                elemento = elemento->proximo;
            }
        }
        if (instrumento == 1)
        {
            elemento = m->inicio;
            while (elemento->proximo != m->inicio)/*percorre todos os instantes a procura da nota, quando a encontrar retorna o instante */
            {
                for (int i = 0; i < 2; i++)
                {
                    if (elemento->notasPiano[i] == nota)
                    {
                        return elemento;
                    }
                }
                elemento = elemento->proximo;
            }
        }
    }
    
    return NULL;
}

instante *instante_remove(musica *m, int pos)
{
    instante *aux, *aux0, *aux1;
    instante *elemento;
    if (m == NULL || pos > musica_tamanho(m))
        return NULL;
    if (pos == 0)/*retira o 1º instante da musica (pos==0)*/
    {
        elemento = m->inicio;
        while (elemento->proximo != m->inicio)
        {
            elemento = elemento->proximo;
        }
        aux0 = m->inicio;
        m->inicio = m->inicio->proximo;
        elemento->proximo = m->inicio;
        return aux0;
    }
    else /*retira o instante da posicao pos da musica */
    {
        elemento = m->inicio;
        for (int i = 0; i < pos - 1; i++)/*vai buscar o endereço do instante a seguir ao que vamos remover */
        {
            elemento = elemento->proximo;
        }
        aux = elemento->proximo;
        elemento = m->inicio;
        for (int i = 0; i < pos - 2; i++)/*vai até ao elemento anterior ao que é para remover para alterar o proximo endereço */
        {
            elemento = elemento->proximo;
        }
        aux1 = elemento->proximo;
        elemento->proximo = aux;
        
        return aux1;
    }
}

int instante_apaga(instante *t)
{  
    if (t == NULL)
        return -1;
    if(t->instrumentoExtra!=NULL)
    free(t->instrumentoExtra);
    
    free(t);/*liberta o espaço alocado para t */
    return 0;
   
}

int musica_apaga(musica *m)
{
    instante *aux;
    instante *elemento;
    if (m == NULL)
        return -1;
    elemento = m->inicio;
    while (elemento->proximo != m->inicio)/*liberta cada instante de musica */
    {
        aux = elemento->proximo;
        instante_apaga(elemento);
        elemento = aux;
    }
    instante_apaga(elemento);/*liberta o ultimo instante de musica que nao é libertado no ciclo while */
    
    free(m);
    return 0; 
}

musica *musica_importa(const char *nomef)
{
    FILE *f = fopen(nomef, "r");
    if (f == NULL)
        return NULL;

    musica *m = musica_nova();
    if (m == NULL)
    {
        fclose(f);
        return NULL;
    }

    int duracao = 0, i, j;
    char str_aux[100] = {};
    int bateria[8] = {0};
    char notas[9] = {0};
    char instrumentoExtra[100] = {0};

    instante *aux;

    while (fscanf(f, "%d", &duracao) != EOF)
    {
        fgets(str_aux, 100 * sizeof(char), f);
        str_aux[strlen(str_aux) - 1] = '\0';

        /* lê os 8 carateres correspondentes à bateria */
        i = 0;
        j = 1;
        while (i < 8)
        {

            bateria[i] = atoi(str_aux + j);
            i++;
            j += 2;
        }

        /* lê o resto da linha do ficheiro */
        if (strlen(str_aux + 17) > 1)
        {
            j = 0;
            for (i = 17; i < strlen(str_aux + 17) + 18; i++)
            {
                if (str_aux[i] == ' ')
                    continue;
                else if (str_aux[i] == '"')
                {
                    strcpy(instrumentoExtra, str_aux + i + 1);
                    instrumentoExtra[strlen(instrumentoExtra) - 1] = '\0';
                    break;
                }
                else if (j < 8)
                {
                    notas[j++] = str_aux[i];
                }
            }
        }

        /* cria novo instante (caso não exista instrumentoExtra coloca NULL */
        if (strlen(instrumentoExtra) <= 1)
        {
            aux = instante_novo(duracao, notas, bateria, NULL);
        }
        else
        {
            aux = instante_novo(duracao, notas, bateria, instrumentoExtra);
        }

        if (aux == NULL)
        {
            musica_apaga(m);
            fclose(f);
            return NULL;
        }
        /* insere instante na lista */
        if (instante_insere(m, aux, -1) == -1)
        {
            musica_apaga(m);
            fclose(f);
            return NULL;
        }
        /* reinicia instrumentoExtra e notas */
        memset(instrumentoExtra, '\0', 100);
        memset(notas, '\0', 9);
    }
    fclose(f);
    return m;
}

int musica_toca(musica *m, int duracao)
{
    int soma = 0;
    if (m == NULL)
        return -1;
    if (m->cursor == NULL)
    {
        m->cursor = m->inicio;
    }
    while (soma < duracao)/*verifica se a soma que corresponde a soma das durações dos instantes tocados nao ultrapassa o parametro duração */
    {
        soma = soma + m->cursor->duracao;
        m->cursor = m->cursor->proximo;
    }
    return 0;
}
int musica_corrige(musica *m, char *ficheiro)
{
      instante *elemento;
      
    int alteracao=0, cont = 0;
    FILE *f;
    f = fopen(ficheiro, "r");
    while (fscanf(f, "%d", &alteracao) != EOF)
    {
        if (alteracao == 1)
        {
            int n1=0, n2=0;
            fscanf(f, "%d %d", &n1, &n2);
            if (n1 >= 0 && n2 >= n1 && n2 <= musica_tamanho(m))/*verifica se os dados nao apresentam valores inválidos */
            {
                for (int i = n1; i <= n2; i++)
                {
                    instante_remove(m, i);
                }
                cont++;
            }
        }
        else if (alteracao == 2)
        {
            int instrumento=0;
            char notaaalterar='\0', novanota='\0';
            fscanf(f, "%d %c %c", &instrumento, &notaaalterar, &novanota);
            if (notaaalterar > 64 && notaaalterar < 72 && novanota > 64 && novanota < 72)/*verifica se os dados nao apresentam valores inválidos */
            {
                elemento = m->inicio;
                while (elemento->proximo != m->inicio)
                {
                    if (instrumento == 0)
                    {
                        for (int i = 0; i < 2; i++)
                        {
                            if (elemento->notasGuitarra[i] == notaaalterar)
                            {
                                elemento->notasGuitarra[i] = novanota;
                            }
                        }
                    }
                    else if (instrumento == 1)
                    {
                        for (int i = 0; i < 2; i++)
                        {
                            if (elemento->notasPiano[i] == notaaalterar)
                            {
                                elemento->notasPiano[i] = novanota;
                            }
                        }
                    }
                    elemento = elemento->proximo;
                }
                cont++;
            }
        }
        else if (alteracao == 3)
        {
            int instrumento1=0, toca=0, pi=0, pf=0;
            fscanf(f, "%d %d %d %d", &instrumento1, &toca, &pi, &pf);
            if (instrumento1 >= 0 && instrumento1 < 8 && toca >= 0 && toca < 2 && pi >= 0 && pf >= pi)/*verifica se os dados nao apresentam valores inválidos */
            {
                elemento = m->inicio;
                for (int i = 0; i < pi - 1; i++)/*vai até ao instante da posição pinicial */
                {
                    elemento = elemento->proximo;
                }
                for (int i = pi; i < pf + 1; i++)/*altera o valor da bateria dos instantes entre as posições pinicial e pfinal */
                {
                    elemento->bateria[instrumento1] = toca;
                    elemento = elemento->proximo;
                }
                cont++;
            }
        }
        else if (alteracao == 4)
        {
            int duracao=0, pinicial=0, pfinal=0;
            fscanf(f, "%d %d %d", &duracao, &pinicial, &pfinal);
            if (duracao >= 1 && duracao <= 16 && pinicial >= 0 && pfinal >= pinicial)/*verifica se os dados nao apresentam valores inválidos */
            {
                for (int i = 0; i < pinicial - 1; i++)/*vai até ao instante da posição pinicial */
                {
                    elemento = elemento->proximo;
                }
                for (int i = pinicial; i < pfinal + 1; i++)/*altera a duração dos instantes entre as posições pinicial e pfinal */
                {
                    elemento->duracao = duracao;
                    elemento = elemento->proximo;
                }
                cont++;
            }
        }
    }
    fclose(f);
    
    return cont;  /*retorna o total de erros corrigidos */ 
     
    
}
