/*****************************************************************/
/*         Trabalho pratico 1 | PROG2 | MIEEC | 2020/21         */
/*****************************************************************/
/*                  NAO ALTERAR ESTE FICHEIRO                    */
/*****************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "plantas.h"

/* VERIFICACOES IMPLEMENTADAS */
int verifica_planta_nova(planta **p, const char *ID, const char *nome_cientifico, char **alcunhas, int n_alcunhas, int n_sementes)
{
    int er = 0;

    *p = planta_nova(ID, nome_cientifico, alcunhas, n_alcunhas, n_sementes);
    if (!(*p))
    {
        printf("...verifica_planta_nova: planta nova e' NULL (ERRO)\n");
        return 1;
    }
    else
        printf("...verifica_planta_nova: planta nova nao e' NULL (ok)\n");

    if (strcmp((*p)->ID, ID) != 0)
    {
        printf("...verifica_planta_nova: ID da nova planta (= %s) e' diferente do esperado (= %s) (ERRO)\n", (*p)->ID, ID);
        er++;
    }
    else
        printf("...verifica_planta_nova: ID coincide com o esperado (= %s) (ok)\n", ID);

    if (strcmp((*p)->nome_cientifico, nome_cientifico) != 0)
    {
        printf("...verifica_planta_nova: Nome cientifico da nova planta (= %s) e' diferente do esperado (= %s) (ERRO)\n", (*p)->nome_cientifico, nome_cientifico);
        er++;
    }
    else
        printf("...verifica_planta_nova: Nome cientifico coincide com o esperado (= %s) (ok)\n", nome_cientifico);

    if ((*p)->n_sementes != n_sementes)
    {
        printf("...verifica_planta_nova: Numero de sementes da nova planta (= %d) e' diferente do esperado (= %d) (ERRO)\n", (*p)->n_sementes, n_sementes);
        er++;
    }
    else
        printf("...verifica_planta_nova: Numero de sementes coincide com o esperado (= %d) (ok)\n", n_sementes);

    if ((*p)->n_alcunhas != n_alcunhas)
    {
        printf("...verifica_planta_nova: Numero de alcunhas da nova planta (= %d) e' diferente do esperado (= %d) (ERRO)\n", (*p)->n_alcunhas, n_alcunhas);
        er++;
        return er;
    }
    else
        printf("...verifica_planta_nova: Numero de alcunhas coincide com o esperado (= %d) (ok)\n", n_alcunhas);

    if (alcunhas == NULL)
    {
        if ((*p)->alcunhas != alcunhas)
        {

            printf("...verifica_planta_nova: O vetor alcunhas da nova planta e' diferente do esperado (= NULL) (ERRO)\n");
            er++;
        }
        else
            printf("...verifica_planta_nova: O vetor alcunhas da nova planta coincide com o esperado (= NULL) (ok)\n");
    }
    else
    {
        int flag = 0;
        for (int i = 0; i < n_alcunhas; i++)
        {
            if (strcmp(alcunhas[i], (*p)->alcunhas[i]))
            {
                printf("...verifica_planta_nova: O conteudo do vetor alcunhas na posicao %d (= %s) e' diferente do esperado (= %s) (ERRO)\n", i, (*p)->alcunhas[i], alcunhas[i]);
                er++;
                flag = 1;
            }
        }
        if (!flag)
            printf("...verifica_planta_nova: O conteudo do vetor alcunhas coincide com o esperado (ok)\n");
    }

    return er;
}
int verifica_colecao_nova(colecao **c, const char *tipo_ordem)
{
    int er = 0;

    *c = colecao_nova(tipo_ordem);
    if (!(*c))
    {
        printf("...verifica_colecao_nova: colecao nova e' NULL (ERRO)\n");
        return 1;
    }
    else
        printf("...verifica_colecao_nova: colecao nova nao e' NULL (ok)\n");

    if (strcmp((*c)->tipo_ordem, tipo_ordem))
    {
        printf("...verifica_colecao_nova: tipo_ordem da colecao nova (= %s) 'e diferente do esperado (= %s) (ERRO)\n", (*c)->tipo_ordem, tipo_ordem);
        er++;
    }
    else
        printf("...verifica_colecao_nova: tipo_ordem da colecao nova coincide com o esperado (= %s) (ok)\n", tipo_ordem);

    return er;
}

int verifica_planta_insere(colecao **c)
{
    int er = 0, erro;
    char *alcunhas_p1[] = {"field eryngo", "rattlesnakemaster"};
    char *alcunhas_p2[] = {"rose"};

    planta *p1 = planta_nova("UOIEA", "Eryngium", alcunhas_p1, 1, 1);
    planta *p2 = planta_nova("ABC", "Rosae", alcunhas_p2, 1, 3);
    planta *p3 = planta_nova("AEIOU", "Lirium", NULL, 0, 10);
    planta *p4 = planta_nova("UOIEA", "Eryngium", alcunhas_p1, 2, 8);

    erro = planta_insere(*c, p1);

    if (erro == -1)
    {
        printf("...verifica_planta_insere: nao conseguiu inserir (ERRO)\n");
        planta_apaga(p1);
        return 1;
    }
    else if (erro == 1)
        planta_apaga(p1);

    erro = planta_insere(*c, p2);
    if (erro != 0)
        planta_apaga(p2);

    erro = planta_insere(*c, p3);
    if (erro != 0)
        planta_apaga(p3);

    erro = planta_insere(*c, p4);
    if (erro != 0)
        planta_apaga(p4);

    if (strcmp((*c)->plantas[0]->ID, "UOIEA") != 0 || strcmp((*c)->plantas[1]->ID, "AEIOU") != 0)
    {
        printf("...verifica_planta_insere: nao inseriu correctamente a 1ª e 3ª plantas, nao estao na posicao correta (ERRO)\n");
        er++;
        return er;
    }
    else
        printf("...verifica_planta_insere: inseriu a 1ª e 3ª plantas nas posicoes corretas (ok)\n");

    if ((*c)->plantas[0]->n_sementes != 9)
    {
        printf("...verifica_planta_insere: n_sementes da 1ª planta (= %d) 'e diferente do esperado (= 9) (ERRO)\n", (*c)->plantas[0]->n_sementes);
        er++;
    }
    else
        printf("...verifica_planta_insere: n_sementes da 1ª planta coincide com o esperado (= 9) (ok)\n");

    if ((*c)->plantas[0]->n_alcunhas != 2)
    {
        printf("...verifica_planta_insere: n_alcunhas da 1ª planta (= %d) 'e diferente do esperado (= 2) (ERRO)\n", (*c)->plantas[0]->n_alcunhas);
        er++;
    }
    else
        printf("...verifica_planta_insere: n_alcunhas da 1ª planta coincide com o esperado (= 2) (ok)\n");

    return er;
}
int verifica_colecao_tamanho(colecao *c)
{
    int tam = colecao_tamanho(c);
    if (tam != 3)
    {
        printf("...verifica_colecao_tamanho: tamanho da colecao (= %d) e' diferente do esperado (= 3) (ERRO)\n", tam);
        return 1;
    }
    printf("...verifica_colecao_tamanho: tamanho da colecao coincide com o esperado (= %d) (ok)\n", tam);
    return 0;
}
int verifica_colecao_importa(colecao **c, const char *ficheiro)
{
    int er = 0;
    printf("Importando colecao...\n");

    *c = colecao_importa(ficheiro, "id");

    if (*c == NULL)
    {
        printf("...verifica_colecao_importa: falhou importacao da colecao (ERRO)\n");
        return 1;
    }
    else
    {
        int tam = colecao_tamanho(*c);
        if (tam != 500)
        {
            printf("...verifica_colecao_importa: tamanho da colecao (= %d) e' diferente do esperado (= 500) (ERRO)\n", tam);
            er++;
        }
        else
            printf("...verifica_colecao_importa: tamanho da colecao coincide com o esperado (= 500) (ok)\n");
    }
    if (strcmp((*c)->plantas[0]->ID, "ACAL3") != 0 || strcmp((*c)->plantas[(*c)->tamanho - 1]->ID, "YUSM") != 0)
    {
        printf("...verifica_colecao_importa: IDs da 1ª (= %s) e 'ultima (= %s) posicoes da colecao diferem do esperado (ACAL3 e YUSM) (ERRO)\n", (*c)->plantas[0]->ID, (*c)->plantas[(*c)->tamanho - 1]->ID);
        er++;
    }
    else
        printf("...verifica_colecao_importa: IDs da 1ª e 'ultima posicoes da colecao coincidem com o esperado (ACAL3 e YUSM) (ok)\n");

    return er;
}
int verifica_planta_remove(colecao *c)
{
    int er = 0;

    planta *p;
    p = planta_remove(c, "inexistente");
    if (p)
    {
        printf("...verifica_planta_remove (teste de planta inexistente): removeu uma planta inexistente (ERRO)\n");
        er++;
    }
    else
        printf("...verifica_planta_remove (teste de planta inexistente): nao removeu nenhuma planta (ok)\n");
    planta_apaga(p);

    p = planta_remove(c, "Acnida alabamensis Standl.");
    if (!p)
    {
        printf("...verifica_planta_remove (teste de planta valida): nao removeu (ERRO)\n");
        er++;
    }
    else if (strcmp(p->ID, "ACAL3") != 0)
    {
        printf("...verifica_planta_remove (teste de planta valida): removeu uma planta errada (ERRO)\n");
        er++;
    }
    else
    {
        printf("...verifica_planta_remove (teste de planta valida): removeu com sucesso (ok)\n");
    }
    planta_apaga(p);
    return er;
}
int verifica_planta_apaga(planta **p)
{
    int erro;

    erro = planta_apaga(*p);
    if (erro == -1)
    {
        printf("...verifica_planta_apaga: deu erro ao apagar planta (ERRO)\n");
        return 1;
    }
    else
        printf("...verifica_planta_apaga: apagou com sucesso (ok)\n");
    return 0;
}

int verifica_colecao_pesquisa_nome(colecao *c)
{
    int er = 0;
    int *idxs, tam;
    idxs = colecao_pesquisa_nome(c, "Rosae", &tam);

    if (idxs)
    {
        printf("...verifica_colecao_pesquisa_nome (teste de um nome que nao existe): vetor nao 'e NULL (ERRO)\n");
        er++;
    }
    else
        printf("...verifica_colecao_pesquisa_nome (teste de um nome que nao existe): retornou NULL (ok)\n");

    idxs = colecao_pesquisa_nome(c, "sneezeweed", &tam);
    if (idxs == NULL)
    {
        printf("...verifica_colecao_pesquisa_nome (teste de um nome que existe): nome nao foi encontrado (ERRO)\n");
        er++;
    }
    else if (tam != 2)
    {
        printf("...verifica_colecao_pesquisa_nome (teste de um nome que existe): numero de indices encontrados (= %d) nao coincide com o esperado (= 2) (ERRO)\n", tam);
        er++;
    }
    else
        printf("...verifica_colecao_pesquisa_nome (teste de um nome que existe): numero de indices encontrados coincide com o esperado (= 2) (ok)\n");

    if (idxs != NULL)
    {
        free(idxs);
    }
    return er;
}
int verifica_colecao_reordena(colecao **c)
{
    int erro;
    erro = colecao_reordena(*c, "nome");
    if (erro == -1)
    {
        printf("...verifica_colecao_reordena: deu erro ao reordenar a colecao (ERRO)\n");
        return 1;
    }
    if (strcmp((*c)->plantas[0]->ID, "ACSP5") != 0 || strcmp((*c)->plantas[(*c)->tamanho - 1]->ID, "YUSM") != 0)
    {
        printf("...verifica_colecao_reordena: 1ª (= %s) e 'ultima (= %s) plantas sao diferentes do esperado (= ACSP5 e YUSM) (ERRO)\n", (*c)->plantas[0]->ID, (*c)->plantas[(*c)->tamanho - 1]->ID);
        return 1;
    }
    else
    {
        printf("...verifica_colecao_reordena: 1ª e 'ultima plantas coincidem com o esperado (= ACSP5 e YUSM) (ok)\n");
    }
    return 0;
}
int main()
{
    int errorCount = 0, error;

    char nome[] = "Sagittaria lancifolia L. ssp. media (Micheli) Bogin";
    char *alcunhas[] = {"bulltongue arrowhead", "delta arrowhead"};
    int sementes = 60;
    char ID[10] = "SALAM2";
    char ficheiro[] = "db_small.txt";
    planta *p;
    colecao *c, *c1;

    printf("INICIO DOS TESTES\n\n");

    error = verifica_planta_nova(&p, ID, nome, alcunhas, 2, sementes);

    if (error)
    {
        printf("ERRO: %d erros encontrados em verifica_planta_nova\n\n", error);
        errorCount += error;
    }
    else
    {
        printf("OK: verifica_planta_nova passou\n\n");
    }

    error = verifica_colecao_nova(&c, "nome");
    if (error)
    {
        printf("ERRO: %d erros encontrados em verifica_colecao_nova\n\n", error);
        errorCount += error;
    }
    else
    {
        printf("OK: verifica_colecao_nova passou\n\n");
    }

    error = verifica_planta_insere(&c);
    if (error)
    {
        printf("ERRO: %d erros encontrados em verifica_planta_insere\n\n", error);
        errorCount += error;
    }
    else
    {
        printf("OK: verifica_planta_insere passou\n\n");
    }

    error = verifica_colecao_tamanho(c);
    if (error)
    {
        printf("ERRO: %d erros encontrados em verifica_colecao_tamanho\n\n", error);
        errorCount += error;
    }
    else
    {
        printf("OK: verifica_colecao_tamanho passou\n\n");
    }

    error = verifica_colecao_importa(&c1, ficheiro);
    if (error)
    {
        printf("ERRO: %d erros encontrados em verifica_colecao_importa\n\n", error);
        errorCount += error;
    }
    else
    {
        printf("OK: verifica_colecao_importa passou\n\n");
    }

    error = verifica_planta_remove(c1);
    if (error)
    {
        printf("ERRO: %d erros encontrados em verifica_planta_remove\n\n", error);
        errorCount += error;
    }
    else
    {
        printf("OK: verifica_planta_remove passou\n\n");
    }

    error = verifica_planta_apaga(&p);
    if (error)
    {
        printf("ERRO: %d erros encontrados em verifica_planta_apaga\n\n", error);
        errorCount += error;
    }
    else
    {
        printf("OK: verifica_planta_apaga passou\n\n");
    }

    error = verifica_colecao_pesquisa_nome(c1);
    if (error)
    {
        printf("ERRO: %d erros encontrados em verifica_colecao_pesquisa_nome\n\n", error);
        errorCount += error;
    }
    else
    {
        printf("OK: verifica_colecao_pesquisa_nome passou\n\n");
    }

    error = verifica_colecao_reordena(&c1);
    if (error)
    {
        printf("ERRO: %d erros encontrados em verifica_colecao_reordena\n\n", error);
        errorCount += error;
    }
    else
    {
        printf("OK: verifica_colecao_reordena passou\n\n");
    }

    colecao_apaga(c);
    colecao_apaga(c1);

    if (errorCount == 0)
        printf("FIM DOS TESTES: Todos os testes passaram\n");
    else
        printf("FIM DOS TESTES: Foram encontrados %d ERROS no total\n", errorCount);

    return 0;
}
