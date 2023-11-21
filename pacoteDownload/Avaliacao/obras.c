#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include "obras.h"

void imprimirCabecalho(){
    puts("***********************************************************************");
    puts("*                                                                     *");
    puts("*                      MUSEU MULTITEMÁTICO                            *");
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

        if (fscanf(arquivo, "Área: %1s\n", area) != 1 ||
            fscanf(arquivo, "Título: %99[^\n]\n", titulo) != 1 ||
            fscanf(arquivo, "Descrição: %499[^\n]\n", descricao) != 1) {
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
    printf("Qual Área você deseja selecionar (A, B, C, D)? ");
    char area;
    scanf(" %c", &area);
    area = toupper(area);

    int obrasEncontradas = 0;

    printf("\nObras na Área %c:\n", area);
    for (int i = 0; i < contador; i++) {
        if (obras[i].area == area - 'A') {
            obrasEncontradas = 1;
            printf("Obra %d\n", i + 1);
            printf("Título: %s\n", obras[i].titulo);
            printf("Descrição: %s\n\n", obras[i].descricao);
        }
    }

    if (!obrasEncontradas) {
        printf("Nenhuma obra registrada! Escolha outra ÁREA:\n");
        exibirObrasPorArea(obras, contador);
        return;
    }

    int numObra;
    do {
        printf("Qual obra será exibida (insira o número da Obra)? ");
        if (scanf("%d", &numObra) != 1 || numObra < 1 || numObra > contador || obras[numObra - 1].area != area - 'A') {
            printf("Número da Obra inválido. Tente novamente.\n");
            while (getchar() != '\n'); // Limpa o buffer de entrada
        } else {
            numObra--; // Ajuste para converter o número da Obra para o índice
        }
    } while (numObra < 0 || numObra >= contador || obras[numObra].area != area - 'A');

    limparTela();
    imprimirCabecalho();
    printf("\nTítulo: %s\n", obras[numObra].titulo);
    printf("Descrição: %s\n\n", obras[numObra].descricao);

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
    printf("Sua opinião é muito importante. Gostaria de avaliar a obra?\n 1 - Sim\n 2 - Não\n");

    if (scanf("%d", &interesse) != 1 || (interesse != 1 && interesse != 2)) {
        printf("Entrada inválida. Por favor, selecione 1 para 'Sim' ou 2 para 'Não.\n");
        fclose(arquivo);
        return;
    }

    if (interesse == 1) {
        printf("As informações coletadas são confidenciais e se destinam exclusivamente à pesquisa no âmbito do Museu Multitemático.\n\n");
        printf("As perguntas seguintes são respondidas em uma escala de 1 a 5, onde 1 significa 'Nenhum grau de importância' e 5 significa 'Muito'.\n\n");

        do {
            printf("1. Qual o nível de impacto que essa obra teve sobre você (de 1 a 5)?\n");
        } while (scanf("%d", &quest1) != 1 || quest1 < 1 || quest1 > 5);

        do {
            printf("2. Como você considera o nível de importância dessa obra para a sociedade atual (de 1 a 5)?\n");
        } while (scanf("%d", &quest2) != 1 || quest2 < 1 || quest2 > 5);

        do {
            printf("3. Qual a probabilidade de você indicar esta obra para um amigo(a) (de 1 a 5)?\n");
        } while (scanf("%d", &quest3) != 1 || quest3 < 1 || quest3 > 5);

        do {
            printf("4. Qual é o seu nível de satisfação com o tema da exposição (de 1 a 5)?\n");
        } while (scanf("%d", &quest4) != 1 || quest4 < 1 || quest4 > 5);

        media = (quest1 + quest2 + quest3 + quest4) / 4.0;
        printf("O Museu Multitematico agradece pela sua opinião.\n");

        // Grava a avaliação no arquivo, juntamente com o número da Obra
        fprintf(arquivo, "Número da Obra: %d | Pergunta 1: %d | Pergunta 2: %d | Pergunta 3: %d | Pergunta 4: %d | Média: %.2f\n", numObra + 1, quest1, quest2, quest3, quest4, media); // Mudança aqui
    } else {
        printf("O Museu Multitematico agradece pela sua presença!\n");
    }

    fclose(arquivo);
}

void exibirObra(const struct Obra *obra) {
    printf("\nTítulo: %s\n", obra->titulo);
    printf("Descrição: %s\n\n", obra->descricao);
}
