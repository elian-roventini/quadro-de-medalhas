/*
Integrantes
    Elián Roventini Andrade
    Gabriel Souza Recouso
    Vinícius Luiz Ventura Ribeiro
    Vinicius Matheus Martins

*/

/* lista.h
* Definição do TAD lista e protótipos de suas operações. */
#ifndef _LISTA_H
    #define _LISTA_H
    #include <stdio.h>
    #include <stdbool.h>
    #include <string.h>
    #define LST_MAX 300
    typedef struct {
        char pais[31];
        int ouro;
        int prata;
        int bronze;
    } lst_info;
    typedef struct {
        lst_info itens[LST_MAX];
        int n;
    } lista;

    /* função que inicializa a lista */
    void lst_iniciar(lista *);

    /* função que insere um valor no final da lista ou atualiza esse valor na lista */
    bool lst_inserir(lista *, lst_info);

    /* função de devolve a posição de um país na lista ou -1 */
    int lst_procurar(lista, const char *);

    /* função de devolve a posição de um país na lista ou -1 com ponteiro para auxiliar a função lst_inserir */
    int lst_procurar_ponteiro(lista *, const char *);

    /* compara 2 valores da lista, devolve 0 se forem iguais, < 0 se
    * o 1o. for menor que o 2o., > 0 se o 1o. for maior que o 2o. */
    int lst_compara(lst_info, lst_info);

    /* função que ordena a lista por Heapsort */
    void lst_ordenar(lista *);

    /*Função utilizada para criar os pesos de cada país relativa a suas medalhas*/
    void lst_peso(lista *, int []);

    /* função que imprime o quadro de medalhas */
    void lst_imprimir(lista);
    
#endif // _LISTA_H