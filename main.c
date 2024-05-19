#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <math.h>

int qtdCharsFile(FILE **pont_arq);
int readFile(FILE **pont_arq, char *fileName);
void inputChars(FILE *pont_arq, char *arrayChar, int arrayIndex);
void printArray(char *array, int n);
void swap(char *a, char *b);
void createMaxHeap(char *array, int size, int indexNode);
void HeapSort(char *array, int size);
void inputZeros(int *array);
void setNumbersChars(int *array, char *arrayChars, int numberChars);
void setLanguage(int *array, int numberChars);


int main(void){

    FILE *pont_arq;
    char *arrayChar;
    int numberChars;
    int arrayIndex = 0;
    char *fileName = "arquivo.txt";
    int *counterChars;

    if( readFile(&pont_arq, fileName) == 1 ) {
        numberChars = qtdCharsFile(&pont_arq);
        arrayChar = malloc((numberChars + 1) * sizeof(char)); // Adiciona 1 para o caractere nulo
        inputChars(pont_arq, arrayChar, arrayIndex);

        fclose(pont_arq);

        HeapSort(arrayChar, numberChars);
        counterChars = malloc(26 * sizeof(int));
        inputZeros(counterChars);
        setNumbersChars(counterChars, arrayChar, numberChars);

        setLanguage(counterChars, numberChars);
        free(counterChars); // Lberando memória alocada dinamicamente
        free(arrayChar); // Liberando a memória alocada dinamicamente
    }
    printf("\nFim do programa...");
    return 0;
}

int qtdCharsFile(FILE **pont_arq){
    int counter = 0;
    char c;
    while ((c = fgetc(*pont_arq)) != EOF){
        if (isalpha(c)) {
            counter++;
        }
    }
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
    while ((c = fgetc(pont_arq)) != EOF) {
        if (isalpha(c)) {
            arrayChar[arrayIndex++] = tolower(c);
        }
    }
    arrayChar[arrayIndex] = '\0'; // Termina a string com um caractere nulo
}

void printArray(char *array, int n){
    for (int i = 0; i < n; i++){
        printf("%c ", array[i]);
    }
}

void swap(char *a, char *b) {
    char aux = *a;
    *a = *b;
    *b = aux;
}

void createMaxHeap(char *array, int size, int indexNode) {
    int biggest = indexNode;
    int left = 2 * indexNode + 1;
    int right = 2 * indexNode + 2;

    if (left < size && array[left] > array[biggest]) {
        biggest = left;
    }

    if (right < size && array[right] > array[biggest]) {
        biggest = right;
    }

    if (biggest != indexNode) {
        swap(&array[indexNode], &array[biggest]);
        createMaxHeap(array, size, biggest);
    }
}

void HeapSort(char *array, int size) {
    for (int i = size / 2 - 1; i >= 0; i--) {
        createMaxHeap(array, size, i);
    }

    for (int j = size - 1; j >= 0; j--) {
        swap(&array[0], &array[j]);
        createMaxHeap(array, j, 0);
    }
}

void inputZeros(int *array){
    for(int i = 0; i < 26; i++){
        array[i] = 0;
    }
}

void setNumbersChars(int *array, char *arrayChars, int numberChars){
    for (int i = 0; i < numberChars; i++){
        if (isalpha(arrayChars[i])) {
            array[arrayChars[i] - 'a']++;
        }
    }
}

void setLanguage(int *array, int numberChars){

    float percentualCharPortuguese[] = {0.1463, 0.0104, 0.0388, 0.0499, 0.1257, 0.0102, 0.0130, 0.0128, 0.0618, 0.0040, 0.0002, 0.0278, 0.0478, 0.0505, 0.1073, 0.0252, 0.0120, 0.0653, 0.0781, 0.0434, 0.0463, 0.0167, 0.0001, 0.0021, 0.0001, 0.0047};

    float percentualCharEnglish[] = {0.0816, 0.0149, 0.0278, 0.0425, 0.1270, 0.0222, 0.0201, 0.0609, 0.0696, 0.0015, 0.0077, 0.0402, 0.0240, 0.0674, 0.0750, 0.0192, 0.0009, 0.0598, 0.0632, 0.0905, 0.0275, 0.0097, 0.0236, 0.0015, 0.0197, 0.0007};

    float total_diff_ptg = 0;
    float total_diff_eng = 0;
    int i;

    for (i = 0; i < 26; i++){
        float result = (float) array[i] / (float) numberChars;
        total_diff_ptg += fabs(percentualCharPortuguese[i] - result);
        total_diff_eng += fabs(percentualCharEnglish[i] - result);
    }

    if(total_diff_ptg < total_diff_eng){
        printf("\nO texto está escrito em Português");
    } else {
        printf("\nO texto está escrito em Inglês");
    }

    printf("\nDiferença total para Português: %f", total_diff_ptg);
    printf("\nDiferença total para Inglês: %f", total_diff_eng);
}
