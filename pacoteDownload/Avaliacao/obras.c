#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include "obras.h"

void imprimirCabecalho(){
    puts("***********************************************************************");
    puts("*                                                                     *");
    puts("*                      MUSEU MULTITEM�TICO                            *");
    puts("*                                                                     *");
    puts("*                                                          ADS - UNIP *");
    puts("***********************************************************************");
}

void limparBuffer(){
    fflush(stdin);
}

void limparTela(){
    char ent;
    puts("\nPressione ENTER para continuar...");
    limparBuffer();
    getchar();
    system("cls");
}

void lerArquivo(struct Obra *obras, int *contador) {
    FILE *arquivo = fopen("registro_obras.csv", "r");
    if (arquivo == NULL) {
        printf("Erro ao abrir o arquivo CSV.\n");
        return;
    }


    while (*contador < MAX_OBRAS) {
        char area[2];
        char titulo[MAX_TITULO];
        char descricao[MAX_DESCRICAO];

        if (fscanf(arquivo, "�rea: %1s\n", area) != 1 ||
            fscanf(arquivo, "T�tulo: %99[^\n]\n", titulo) != 1 ||
            fscanf(arquivo, "Descri��o: %499[^\n]\n", descricao) != 1) {
            break;
        }

        struct Obra novaObra;
        novaObra.area = area[0] - 'A';
        strcpy(novaObra.titulo, titulo);
        strcpy(novaObra.descricao, descricao);

        obras[(*contador)++] = novaObra;
    }

    fclose(arquivo);
}

void exibirObrasPorArea(const struct Obra *obras, int contador) {
    printf("Qual �rea voc� deseja selecionar (A, B, C, D)? ");
    char area;
    scanf(" %c", &area);
    area = toupper(area);

    int obrasEncontradas = 0;

    printf("\nObras na �rea %c:\n", area);
    for (int i = 0; i < contador; i++) {
        if (obras[i].area == area - 'A') {
            obrasEncontradas = 1;
            printf("Obra %d\n", i + 1);
            printf("T�tulo: %s\n", obras[i].titulo);
            printf("Descri��o: %s\n\n", obras[i].descricao);
        }
    }

    if (!obrasEncontradas) {
        printf("Nenhuma obra registrada! Escolha outra �REA:\n");
        exibirObrasPorArea(obras, contador);
        return;
    }

    int numObra;
    do {
        printf("Qual obra ser� exibida (insira o n�mero da Obra)? ");
        if (scanf("%d", &numObra) != 1 || numObra < 1 || numObra > contador || obras[numObra - 1].area != area - 'A') {
            printf("N�mero da Obra inv�lido. Tente novamente.\n");
            while (getchar() != '\n'); // Limpa o buffer de entrada
        } else {
            numObra--; // Ajuste para converter o n�mero da Obra para o �ndice
        }
    } while (numObra < 0 || numObra >= contador || obras[numObra].area != area - 'A');

    limparTela();
    imprimirCabecalho();
    printf("\nT�tulo: %s\n", obras[numObra].titulo);
    printf("Descri��o: %s\n\n", obras[numObra].descricao);

}


void avaliarObra(int numObra, const struct Obra obra) {
    FILE *arquivo;
    char nome_arquivo[] = "Avaliacao da Obra.csv";
    int quest1, quest2, quest3, quest4, interesse;
    float media;
    arquivo = fopen(nome_arquivo, "a");

    if (arquivo == NULL) {
        printf("Erro ao abrir o arquivo.\n");
        return;
    }

    printf("Museu Multitematico\n\n");
    printf("Sua opini�o � muito importante. Gostaria de avaliar a obra?\n 1 - Sim\n 2 - N�o\n");

    if (scanf("%d", &interesse) != 1 || (interesse != 1 && interesse != 2)) {
        printf("Entrada inv�lida. Por favor, selecione 1 para 'Sim' ou 2 para 'N�o.\n");
        fclose(arquivo);
        return;
    }

    if (interesse == 1) {
        printf("As informa��es coletadas s�o confidenciais e se destinam exclusivamente � pesquisa no �mbito do Museu Multitem�tico.\n\n");
        printf("As perguntas seguintes s�o respondidas em uma escala de 1 a 5, onde 1 significa 'Nenhum grau de import�ncia' e 5 significa 'Muito'.\n\n");

        do {
            printf("1. Qual o n�vel de impacto que essa obra teve sobre voc� (de 1 a 5)?\n");
        } while (scanf("%d", &quest1) != 1 || quest1 < 1 || quest1 > 5);

        do {
            printf("2. Como voc� considera o n�vel de import�ncia dessa obra para a sociedade atual (de 1 a 5)?\n");
        } while (scanf("%d", &quest2) != 1 || quest2 < 1 || quest2 > 5);

        do {
            printf("3. Qual a probabilidade de voc� indicar esta obra para um amigo(a) (de 1 a 5)?\n");
        } while (scanf("%d", &quest3) != 1 || quest3 < 1 || quest3 > 5);

        do {
            printf("4. Qual � o seu n�vel de satisfa��o com o tema da exposi��o (de 1 a 5)?\n");
        } while (scanf("%d", &quest4) != 1 || quest4 < 1 || quest4 > 5);

        media = (quest1 + quest2 + quest3 + quest4) / 4.0;
        printf("O Museu Multitematico agradece pela sua opini�o.\n");

        // Grava a avalia��o no arquivo, juntamente com o n�mero da Obra
        fprintf(arquivo, "N�mero da Obra: %d | Pergunta 1: %d | Pergunta 2: %d | Pergunta 3: %d | Pergunta 4: %d | M�dia: %.2f\n", numObra + 1, quest1, quest2, quest3, quest4, media); // Mudan�a aqui
    } else {
        printf("O Museu Multitematico agradece pela sua presen�a!\n");
    }

    fclose(arquivo);
}

void exibirObra(const struct Obra *obra) {
    printf("\nT�tulo: %s\n", obra->titulo);
    printf("Descri��o: %s\n\n", obra->descricao);
}
