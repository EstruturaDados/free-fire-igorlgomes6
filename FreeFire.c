#include <stdio.h>
#include <string.h>
#include <stdlib.h>

typedef struct {
    char nome[30];
    char tipo[20];
    int quantidade;
} Item;

#define MAX_ITENS 10
Item mochila[MAX_ITENS];
int numItens = 0;

void limparBuffer();
void inserirItem();
void removerItem();
void listarItens();
void buscarItem();
void menuPrincipal();

void limparBuffer() {
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}

void inserirItem() {
    if (numItens >= MAX_ITENS) {
        printf("\n\033[31m[ERRO] Mochila cheia! Max. %d itens.\033[0m\n", MAX_ITENS);
        return;
    }

    printf("\n--- Coletar Novo Item ---\n");
    
    printf("Nome do Item (max 29 caracteres): ");
    limparBuffer();
    fgets(mochila[numItens].nome, sizeof(mochila[numItens].nome), stdin);
    mochila[numItens].nome[strcspn(mochila[numItens].nome, "\n")] = 0;

    printf("Tipo do Item (ex: arma, munição, cura): ");
    if (scanf("%s", mochila[numItens].tipo) != 1) {
         printf("\n\033[31m[ERRO] Falha na leitura do tipo.\033[0m\n");
         limparBuffer();
         return;
    }

    printf("Quantidade: ");
    while (scanf("%d", &mochila[numItens].quantidade) != 1 || mochila[numItens].quantidade <= 0) {
        printf("\033[33mEntrada inválida. Digite um número inteiro positivo: \033[0m");
        limparBuffer();
    }
    limparBuffer();

    numItens++;
    printf("\n\033[32m[SUCESSO] Item '%s' adicionado.\033[0m\n", mochila[numItens-1].nome);
    listarItens();
}

void removerItem() {
    char nomeBusca[30];
    int encontrado = 0;

    if (numItens == 0) {
        printf("\n\033[33m[AVISO] A mochila está vazia. Nada para descartar.\033[0m\n");
        return;
    }

    printf("\n--- Descartar Item ---\n");
    printf("Digite o NOME do item a ser removido: ");
    limparBuffer();
    fgets(nomeBusca, sizeof(nomeBusca), stdin);
    nomeBusca[strcspn(nomeBusca, "\n")] = 0;

    for (int i = 0; i < numItens; i++) {
        if (strcmp(mochila[i].nome, nomeBusca) == 0) {
            for (int j = i; j < numItens - 1; j++) {
                mochila[j] = mochila[j + 1];
            }

            numItens--;
            encontrado = 1;
            printf("\n\033[32m[SUCESSO] Item '%s' removido da mochila.\033[0m\n", nomeBusca);
            break;
        }
    }

    if (!encontrado) {
        printf("\n\033[33m[AVISO] Item '%s' não encontrado.\033[0m\n", nomeBusca);
    }

    listarItens();
}

void listarItens() {
    printf("\n--- Itens Atuais na Mochila (%d/%d) ---\n", numItens, MAX_ITENS);

    if (numItens == 0) {
        printf("\033[36m(Mochila vazia. Hora de coletar loot!)\033[0m\n");
        return;
    }

    printf("| %-29s | %-19s | %-10s |\n", "NOME", "TIPO", "QUANTIDADE");
    printf("---------------------------------------------------------------\n");

    for (int i = 0; i < numItens; i++) {
        printf("| %-29s | %-19s | %-10d |\n",
               mochila[i].nome,
               mochila[i].tipo,
               mochila[i].quantidade);
    }
    printf("---------------------------------------------------------------\n");
}

void buscarItem() {
    char nomeBusca[30];
    int encontrado = 0;

    if (numItens == 0) {
        printf("\n\033[33m[AVISO] A mochila está vazia. Nada para buscar.\033[0m\n");
        return;
    }

    printf("\n--- Busca Sequencial de Item ---\n");
    printf("Digite o NOME do item que você procura: ");
    limparBuffer();
    fgets(nomeBusca, sizeof(nomeBusca), stdin);
    nomeBusca[strcspn(nomeBusca, "\n")] = 0;

    for (int i = 0; i < numItens; i++) {
        if (strcmp(mochila[i].nome, nomeBusca) == 0) {
            printf("\n\033[32m[ENCONTRADO!] Item localizado:\033[0m\n");
            printf("--------------------------------------------\n");
            printf(" Nome: %s\n", mochila[i].nome);
            printf(" Tipo: %s\n", mochila[i].tipo);
            printf(" Quantidade: %d\n", mochila[i].quantidade);
            printf("--------------------------------------------\n");
            encontrado = 1;
            break;
        }
    }

    if (!encontrado) {
        printf("\n\033[33m[AVISO] Item '%s' não foi encontrado na mochila.\033[0m\n", nomeBusca);
    }
    
    listarItens();
}

void menuPrincipal() {
    int opcao;

    do {
        printf("\n============================================\n");
        printf("|   BATTLE ROYALE - INVENTÁRIO (NÍVEL 1)   |\n");
        printf("============================================\n");
        printf("1. Coletar Item (Cadastrar)\n");
        printf("2. Descartar Item (Remover)\n");
        printf("3. Listar Itens da Mochila\n");
        printf("4. Buscar Item por Nome (Busca Sequencial)\n");
        printf("0. Sair do Jogo\n");
        printf("--------------------------------------------\n");
        printf("Escolha uma opção: ");

        if (scanf("%d", &opcao) != 1) {
            printf("\n\033[31m[ERRO] Opção inválida. Tente novamente.\033[0m\n");
            limparBuffer();
            opcao = -1;
            continue;
        }

        switch (opcao) {
            case 1:
                inserirItem();
                break;
            case 2:
                removerItem();
                break;
            case 3:
                listarItens();
                break;
            case 4:
                buscarItem();
                break;
            case 0:
                printf("\n\033[34m[FIM] Inventário finalizado. Preparar para o combate!\033[0m\n");
                break;
            default:
                printf("\n\033[31m[ERRO] Opção inexistente. Por favor, escolha um número de 0 a 4.\033[0m\n");
        }

    } while (opcao != 0);
}

int main() {
    printf("Bem-vindo ao Battle Royale - Fase de Coleta de Loot!\n");
    printf("Seu inventário inicial está pronto.\n");
    
    menuPrincipal();

    return 0;
}
