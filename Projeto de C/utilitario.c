#include "utilitario.h"
#include <stdio.h>
#include <string.h>

void limparBufferEntrada() {
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}

void lerString(char *string, int tamanho) {
    limparBufferEntrada();
    fgets(string, tamanho, stdin);
    // Remover o caractere de nova linha do final da string, se presente
    int length = strlen(string);
    if (length > 0 && string[length - 1] == '\n') {
        string[length - 1] = '\0';
    }
}

float lerFloatPositivo() {
    float valor;
    while (1) {
        scanf("%f", &valor);
        if (valor >= 0) {
            limparBufferEntrada();
            return valor;
        }
        limparBufferEntrada();
        printf("Entrada invalida. Por favor, digite um valor positivo: ");
    }
}

int lerInteiroPositivo() {
    int valor;
    while (1) {
        scanf("%d", &valor);
        if (valor >= 0) {
            limparBufferEntrada();
            return valor;
        }
        limparBufferEntrada();
        printf("Entrada invalida. Por favor, digite um valor inteiro positivo: ");
    }
}
