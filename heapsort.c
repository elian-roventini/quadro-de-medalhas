/*
Integrantes
    Elián Roventini Andrade
    Gabriel Souza Recouso
    Vinícius Luiz Ventura Ribeiro
    Vinicius Matheus Martins

*/

/*Implementação do Algoritmo HeapSort de maximização*/
#include <stdio.h>
#include <stdlib.h>

//Criando a struck sendo o tamanho = array
struct MaxHeap
{
    int tamanho;
    int * array;
};

// Função para trocar os valores
void swap(int * a, int * b) {
     int t = *a; *a = *b;  *b = t; 
}

//A função main para o heapify um Max heap
// Essa função assum que todos os valores abaixo da raiz(pai) ja estao heapify
void maxHeapify(struct MaxHeap * maxHeap, int idx) {
    int maior = idx;  // Começa o maior valor como raiz
    int esquerda = (idx << 1) + 1;  // esquerda = 2*idx + 1
    int direita = (idx + 1) << 1; // direita = 2*idx + 2

    // Confere se o filho esquerdo da raiz existe e é maior que a raiz
    if (esquerda < maxHeap->tamanho && maxHeap->array[esquerda] < maxHeap->array[maior]) 
        maior = esquerda;

    // Confere se o filho direito da raiz existe e é maior que o maior existente
    if (direita < maxHeap->tamanho && maxHeap->array[direita] < maxHeap->array[maior]) 
        maior = direita;

    // Muda a raiz se for necessario
    if (maior != idx) {
        swap(&maxHeap->array[maior], &maxHeap->array[idx]);
        maxHeapify(maxHeap, maior);
    }
}

// Função cridada para criar um max heap para o tamanho
struct MaxHeap* createAndBuildHeap(int *array, int tamanho) {
    int i;
    struct MaxHeap* maxHeap = (struct MaxHeap*) malloc(sizeof(struct MaxHeap));
    maxHeap->tamanho = tamanho; // Tamanho do heap é lido
    maxHeap->array = array; // Le o primeiro valor do array

    //Começa com o valor mais exteremo a direita e faz o heapify para todos os valores 
    // Os ordenando de baixo para cima
    for (i = (maxHeap->tamanho - 2) / 2; i >= 0; --i)
        maxHeapify(maxHeap, i);
    return maxHeap;
}

// Função usda para ordenar o array
void heapSort(int* array, int tamanho) {
    // Cria o heap para os dados inseridos
    struct MaxHeap* maxHeap = createAndBuildHeap(array, tamanho);

    // Fica em looping ate o tamanho do heap for maior que 1
    // O ultimo valor do heap vai ser o maior
    while (maxHeap->tamanho > 1) {
     
        // O maior valor do heap fica como raiz e é trocado com o ultimo valor do heap reduzindo o tamanho o heap em 1
        swap(&maxHeap->array[0], &maxHeap->array[maxHeap->tamanho - 1]);
        --maxHeap->tamanho;  //Reduz o tamanho do heap

        // heapify é a raiz
        maxHeapify(maxHeap, 0);
    }
}
