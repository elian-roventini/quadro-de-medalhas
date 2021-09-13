/*
Integrantes
    Elián Roventini Andrade
    Gabriel Souza Recouso
    Vinícius Luiz Ventura Ribeiro
    Vinicius Matheus Martins

*/

/*
Implementação das operações realizadas sobre o TAD lista
*/

#include "lista.h"
#include "heapsort.c"

/*Inicializando variáveis globais. Fundamentais para o funcionamento do algoritmo*/

int pesos[LST_MAX];
int indice_peso[LST_MAX];
int gold = 5,
    silver = 3,
    bronze = 1,
    peso = 0;

/* função que inicializa a lista */
void lst_iniciar(lista * l) {
    l->n = 0;
}

/* função que insere um valor no final da lista ou atualiza esse valor na lista */
bool lst_inserir(lista * l, lst_info val) {
    int comparar;
    bool flag = false;
    if (l->n < LST_MAX) { //Verifica se estourou o limite da lista

        for (int i = 0; i < l->n; i++) { //Para cada item na lista, compara se já existe o nome do país,
                                        // caso exista, atualiza o valor das medalhas na lista
                                        // caso não, adicionado a struct val na lista com os devidos valores inseridos 
            comparar = lst_compara(l->itens[i], val);
            if (comparar == 0) { //Valor existente na lista
                flag = true;
                break;
            }
        }
        
        if (!flag) {
            l->itens[l->n++] = val; //Atribui a struct val na lista
        }else {
            //Atualiza as medalha
            int x;
            x = lst_procurar_ponteiro(l, val.pais); //Encontra a posição do país
            l->itens[x].ouro += val.ouro;
            l->itens[x].prata += val.prata;
            l->itens[x].bronze += val.bronze;
        }

        return true;
    }
    return false;
}

/* função de devolve a posição de um país na lista ou -1 */
int lst_procurar(lista l, const char * string) {
    for (int i = 0; i < l.n; i++) {
        if (strcmp(l.itens[i].pais, string) == 0) { //Se a string for igual ao país
            return i;
        }
    }
    return -1;
}
/* função de devolve a posição de um país na lista ou -1 com ponteiro para auxiliar a função lst_inserir */
int lst_procurar_ponteiro(lista * l, const char * string) {
    for (int i = 0; i < l->n; i++) {
        if (strcmp(l->itens[i].pais, string) == 0) { //Se a string for igual ao país
            return i;
        }
    }
    return -1;
}

/* compara 2 valores da lista, devolve 0 se forem iguais, < 0 se
* o 1o. for menor que o 2o., > 0 se o 1o. for maior que o 2o. */
int lst_compara(lst_info value, lst_info value2) {
    return strcmp(value.pais, value2.pais); //Foi utilizado a função strcmp para comparar os países
}

/* função que ordena a lista por Heapsort */
void lst_ordenar(lista * l) {
    lst_peso(l, pesos); //Aqui cria-se um vetor com os pesos de cada país, para sabermos a ordem correta e realizar o
                        //heapSort de maximização da melhor forma possível

    int tamanho = sizeof(pesos)/sizeof(pesos[0]); //Cria o tamanho do vetor
    heapSort(pesos, tamanho); //Realiza o heapSort 


    int i, j; //Variáveis para loop
    /*Variáveis auxiliares para atribuir valores da lista (para a troca dos valores)*/
    int aux, aux2, aux3;
    char strAux[31];

    /*Algoritmo para Ordenar os valores e países dentro da lista*/
    for (i = 0; i < l->n; i++) { //Passa por cada peso dentro do array pesos (usado também para passar pela lista)
        for (j = 0; j < l->n; j++) { //Passa por cada item dentro da lista
            if (pesos[i] == ((l->itens[j].ouro * gold) + (l->itens[j].prata * silver) + (l->itens[j].bronze * bronze)) 
                && indice_peso[j] != -1) { //Verifica se a soma dos pesos de cada medalha é igual ao peso dentro do vetor
                                            //e o vetor de indice_peso é diferente de -1 (para termos certeza que não
                                            //passará novamente por algum valor [ocorre problemas quando temos pesos iguais dentro do array])
                
                indice_peso[j] = -1; //Atribui -1 no vetor indice_peso para não passar novamente por esse índice

                /*Atribui nas variáveis auxiliares os valores dos itens da lista atual*/
                strcpy(strAux, l->itens[i].pais);
                aux = l->itens[i].ouro;
                aux2 = l->itens[i].prata;
                aux3 = l->itens[i].bronze;
                
                /*Atribui nos valores da lista atual, os valores dos itens da lista j*/
                strcpy(l->itens[i].pais, l->itens[j].pais);
                l->itens[i].ouro = l->itens[j].ouro;
                l->itens[i].prata = l->itens[j].prata;
                l->itens[i].bronze = l->itens[j].bronze;

                /*Atribui nos valores da lista j, os valores dos itens atribuídos nas variáveis auxiliar*/
                strcpy(l->itens[j].pais, strAux);
                l->itens[j].ouro = aux; 
                l->itens[j].prata = aux2;
                l->itens[j].bronze = aux3;

                break;
            }
        }        
    }

    /*Algoritmo utilizado após a ordenação, ordenando alfabeticamente os países através dos valores com pesos iguais */
    for (i = 0; i < l->n; i++) { //Novamente passando pelo vetor pesos e lista i
        for (j = 0; j < l->n; j++) { //Utilizado para passar por cada vetor peso j
            if (pesos[i] == pesos[j] && i != j) { //Verifica se o array peso i é igual ao array peso j (passando por todo o vetor para cada número)
                                                  //E verifica se i é diferente de j
                                                  //Caso verdadeiro, significa que o peso do país X é igual ao peso do país Y (provavelmente os N países seguintes)

                int comparar = lst_compara(l->itens[i], l->itens[j]); //Compara através da função lst_compara os valores para ver
                                                                     //se são maiores ou menores relativo a ordem alfabética

                if (comparar < 0) { //Se o primeiro país for menor que o segundo, entra no if

                    /*Atribui nas variáveis auxiliares os valores dos itens da lista atual*/
                    strcpy(strAux, l->itens[i].pais);
                    aux = l->itens[i].ouro;
                    aux2 = l->itens[i].prata;
                    aux3 = l->itens[i].bronze;

                    /*Atribui nos valores da lista atual, os valores dos itens da lista j*/
                    strcpy(l->itens[i].pais, l->itens[j].pais);
                    l->itens[i].ouro = l->itens[j].ouro;
                    l->itens[i].prata = l->itens[j].prata;
                    l->itens[i].bronze = l->itens[j].bronze;

                    /*Atribui nos valores da lista j, os valores dos itens atribuídos nas variáveis auxiliar*/
                    strcpy(l->itens[j].pais, strAux);
                    l->itens[j].ouro = aux; 
                    l->itens[j].prata = aux2;
                    l->itens[j].bronze = aux3;
                }else { //Caso não, dá break
                    break;
                }   
            }
        }
    }
}

/*Função utilizada para criar os pesos de cada país relativa a suas medalhas*/
void lst_peso(lista * l, int pesos[]) {
    
    for (int i = 0; i < l->n; i++){
        peso = (l->itens[i].ouro * gold) + (l->itens[i].prata * silver) + (l->itens[i].bronze * bronze); //Soma de todos os pesos com as medalhs
        pesos[i] = peso; //Atribuindo o peso no array pesos
        indice_peso[i] = peso; //Atribuindo o peso em uma variável "auxiliar" chamada indice_peso
    }
    
}

/* função que imprime o quadro de medalhas */
void lst_imprimir(lista l) {
    printf("Quadro de Medalhas\n");

    for (int i = 0; i < l.n; i++) {
        printf("%s %d %d %d\n", l.itens[i].pais, l.itens[i].ouro, l.itens[i].prata, l.itens[i].bronze);
    }
}