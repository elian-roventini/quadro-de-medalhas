/*
Integrantes
    Elián Roventini Andrade
    Gabriel Souza Recouso
    Vinícius Luiz Ventura Ribeiro
    Vinicius Matheus Martins

*/

#include "lista.h"
#define MAX_MODALIDADE 1000 //Definição do limite máximo de modalidades que um arquivo pode ter (1000 modalidades)

int main() {

    //Definindo as variáveis do algoritmo
    FILE *arq; 
    char str[51];
    char *result;
    int i = 0; //Usado para saber tanto a posição do país para levar a próxima modalidade quanto para saber a medalha 
    bool modalidade = true;
    int numModalidade = 0;


    lista l; //A Lista
    lst_info val; //variável utilizada por algumas operações

    lst_iniciar(&l); //Inicia a lista

    arq = fopen("teste.txt", "r"); //Abre o arquivo para leitura

    while (!feof(arq) && (numModalidade <= MAX_MODALIDADE)) {
        //Enquanto o arquivo NÃO for EOF E o número de modalidade for menor ou igual ao máximo de modalidades, continua o laço

        if (!modalidade) { //Se não for modalidade
            result = fgets(str, 31, arq); //Guarda na variável result o valor da linha atual do arquivo | Lê até 30 caracteres (país)
            for (int i = 0, posicao = 0; i < strlen(result); i++, posicao++) { //utilizado para retirar o '\n' da string
                if (result[posicao] == '\n') posicao++; //Se achar o \n, adiciona mais um a variável posição
                result[i] = result[posicao]; //Atribue na posição i do vetor a sua nova posição 
            }
            
            strcpy(val.pais, result); //copia para a struct o resultado para o nome do país 
            i++; //Acrescenta mais um a contagem

            /*Inicializa/Reinicia os valores do ouro, prata e bronze da struct atual*/
            val.ouro = 0;
            val.prata = 0;
            val.bronze = 0;

            switch (i) { //Entra em um switch para determinar pela contagem se é medalha de ouro, prata ou bronze 
                case 1:
                    val.ouro += 1;
                    break;

                case 2:
                    val.prata += 1;
                    break;

                case 3:
                    val.bronze += 1;
                    break;
                
                default:
                    break;
            }

            lst_inserir(&l, val); //Insere os valores na lista

            if (i == 3) { //Caso for o último país dessa modalidade
                modalidade = true; //Modalidade fica verdadeiro, pois será o próximo
                i = 0; //Reinicia a posição do país como zero
            }
        }else { //Se for modalidade
            result = fgets(str, 51, arq);  //Lê até 50 caracteres (modalidade) e atribue na variável result
            modalidade = false; //Atribue modalidade como falso, pois o próximo será país
            numModalidade++;  //Adiciona mais 1 na contagem de número de modalidade         
        }
    }
    
    lst_ordenar(&l); //Ordena a lista (utilizando heapsort e já ordenando alfabeticamente os valores com pesos iguais)

    lst_imprimir(l); //Imprime o Quadro de Medalhas

    fclose(arq); //Fecha o arquivo

    return 0;
}

