#include <stdio.h>
#include <string.h>
#include <locale.h>
#include <stdlib.h>
#include "obras.h"


int main() {
        setlocale(LC_ALL, "Portuguese");

        struct Obra obras[MAX_OBRAS];
        int contador = 0;
        int numObra;

        lerArquivo(obras, &contador);
        exibirObrasPorArea(obras, contador);
        while(1){
            limparTela();
            avaliarObra(numObra, obras[numObra]);
            limparTela();
            imprimirCabecalho();
            exibirObra(obras);
        }
        return 0;
}
