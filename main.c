#include <stdio.h>
#include <stdlib.h>

int qtdCharsFile(FILE **pont_arq);
int readFile(FILE **pont_arq, char *fileName);
void inputChars(FILE *pont_arq, char *arrayChar, int arrayIndex);
void printArray(char *array, int n);
void swap(char *a, char *b);
void createMaxHeap(char *array, int size, int indexNode);
void HeapSort(char *array, int size);
void inputZeros(int *array);
void setNumbersChars(int *array, char *arrayChars, int numberChars);

int main(void){

    FILE *pont_arq;
    char *arrayChar;
    int numberChars;
    int arrayIndex = 0;
    char *fileName = "arquivo.txt";
    int *counterChars;

    if( readFile(&pont_arq, fileName) == 1 ) {
        numberChars = qtdCharsFile(&pont_arq);
        arrayChar = malloc(numberChars * sizeof (char));
        inputChars(pont_arq, arrayChar, arrayIndex);

        fclose(pont_arq);

        printf("Array não ordenado: ");
        printArray(arrayChar, numberChars);
        HeapSort(arrayChar, numberChars);
        printf("\nArray ordenado: ");
        printArray(arrayChar, numberChars);

        //Preenchendo array de counterChars com zeros
        counterChars = malloc(26 * sizeof (int));
        inputZeros(counterChars);
        setNumbersChars(counterChars, arrayChar, numberChars);
        printf("\n");
        for (int i = 0; i < 26; i++){
            printf("%d ", counterChars[i]);
        }

        free(counterChars);
        free(arrayChar); // Liberando a memória alocada dinamicamente
    }
    printf("\nFim do programa...");
    return 0;
}

int qtdCharsFile(FILE **pont_arq){
    int counter = 0;
    char c;
    while ((c = fgetc(*pont_arq)) != EOF){
        counter++;
    }
    printf("%d\n", counter);
    rewind(*pont_arq);
    return counter;
}

int readFile(FILE **pont_arq, char *fileName){

    *pont_arq = fopen(fileName, "r");
    if( *pont_arq == NULL){
        printf("Erro ao tentar abrir o arquivo!");
        return 0;
    }
    return 1;
}

void inputChars(FILE *pont_arq, char *arrayChar, int arrayIndex){
    char c;
    do {
        c = fgetc(pont_arq);
        arrayChar[arrayIndex] = c;
        arrayIndex++;
    } while (c != EOF); //EOF simboliza o final do arquivo
}

void printArray(char *array, int n){
    for (int i = 0; i < n; i++){
        printf("%c ", array[i]);
    }
}

void swap(char *a, char *b) { // Função que realiza a troca entre o elemento do nó pai e o elemento do nó filho
    char aux;
    aux = *a;
    *a = *b;
    *b = aux;
}

void createMaxHeap(char *array, int size, int indexNode) {
    int biggest = indexNode;
    int left = 2 * indexNode + 1;
    int right = 2 * indexNode + 2;

    if (left < size && (array[left] > array[biggest])) { // Caso o elemento da esquerda é maior que o nó pai
        biggest = left; // Atribui o valor do elemento da esquerda ao nó pai
    }

    if (right < size && (array[right] > array[biggest])) { // Caso o elemento da direita é maior que o nó pai
        biggest = right; // Atribui o valor do elemento da direita ao nó pai
    }

    if (biggest != indexNode) { // Se ocorreu alguma atribuição ao nó pai
        swap(&array[indexNode], &array[biggest]); // Realiza a troca entre o elemento filho e o seu pai
        createMaxHeap(array, size, biggest);
    }
}

void HeapSort(char *array, int size) {

    for (int i = (size / 2) - 1; i >= 0; i--) { // Loop para criar a Máx-Heap
        createMaxHeap(array, size, i);
    }

    for (int j = size - 1; j >= 0; j--) {

        swap(&array[0], &array[j]); // Faz a troca entre o primeiro e o último elemento
        createMaxHeap(array, j, 0); // Construir novamente o max-heap com o último elemento na raiz da heap
    }
}

void inputZeros(int *array){
    for(int i = 0; i < 26; i++){
        array[i] = 0;
    }
}

void setNumbersChars(int *array, char *arrayChars, int numberChars){
    char chars[] = {'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h',
                    'i', 'j', 'k', 'l', 'm', 'n', 'o',
                    'p', 'q', 'r', 's', 't', 'u', 'v',
                    'w', 'x', 'y', 'z'};
    int i, j;

    for(i = 0; i < 26; i++){
        for(j = 0; j < numberChars; j++){
            if(arrayChars[j] == chars[i]){
                array[i] += 1;
            }
        }
    }
}

