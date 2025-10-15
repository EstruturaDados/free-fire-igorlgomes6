#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// --- Estruturas de Dados ---

// Estrutura para o Item (comum a ambas as mochilas)
typedef struct {
    char nome[30];
    char tipo[20];
    int quantidade;
} Item;

// Estrutura do Nó para a Lista Encadeada
typedef struct No {
    Item dados;
    struct No *proximo;
} No;

// --- Variáveis Globais para o Vetor (Lista Sequencial) ---
#define MAX_ITENS 10
Item mochilaVetor[MAX_ITENS];
int numItensVetor = 0;
long long comparacoesVetor = 0;

// --- Variáveis Globais para a Lista Encadeada ---
No *mochilaLista = NULL;
long long comparacoesLista = 0;

// --- Protótipos das Funções Comuns ---
void limparBuffer();
void exibirMenuPrincipal();
void exibirMenuVetor();
void exibirMenuLista();
void limparTela();

// --- Protótipos das Funções do Vetor ---
void inserirItemVetor();
void removerItemVetor();
void listarItensVetor();
void buscarSequencialVetor();
void ordenarVetor();
void buscarBinariaVetor();

// --- Protótipos das Funções da Lista Encadeada ---
void inserirItemLista();
void removerItemLista();
void listarItensLista();
void buscarSequencialLista();

// --- Funções Auxiliares Comuns ---

void limparBuffer() {
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}

void limparTela() {
    printf("\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n");
}

// --- Funções da Mochila (Vetor / Lista Sequencial) ---

void inserirItemVetor() {
    if (numItensVetor >= MAX_ITENS) {
        printf("\n\033[31m[ERRO] Mochila (Vetor) cheia! Max. %d itens.\033[0m\n", MAX_ITENS);
        return;
    }

    printf("\n--- Coletar Novo Item (Vetor) ---\n");
    
    printf("Nome do Item (max 29): ");
    limparBuffer();
    fgets(mochilaVetor[numItensVetor].nome, sizeof(mochilaVetor[numItensVetor].nome), stdin);
    mochilaVetor[numItensVetor].nome[strcspn(mochilaVetor[numItensVetor].nome, "\n")] = 0;

    printf("Tipo do Item (ex: arma, munição, cura): ");
    if (scanf("%s", mochilaVetor[numItensVetor].tipo) != 1) {
         printf("\n\033[31m[ERRO] Falha na leitura do tipo.\033[0m\n");
         limparBuffer();
         return;
    }

    printf("Quantidade: ");
    while (scanf("%d", &mochilaVetor[numItensVetor].quantidade) != 1 || mochilaVetor[numItensVetor].quantidade <= 0) {
        printf("\033[33mEntrada inválida. Digite um número inteiro positivo: \033[0m");
        limparBuffer();
    }
    limparBuffer();

    numItensVetor++;
    printf("\n\033[32m[SUCESSO] Item '%s' adicionado ao Vetor.\033[0m\n", mochilaVetor[numItensVetor-1].nome);
    listarItensVetor();
}

void removerItemVetor() {
    char nomeBusca[30];
    int encontrado = 0;

    if (numItensVetor == 0) {
        printf("\n\033[33m[AVISO] Mochila (Vetor) vazia. Nada para descartar.\033[0m\n");
        return;
    }

    printf("\n--- Descartar Item (Vetor) ---\n");
    printf("Digite o NOME do item a ser removido: ");
    limparBuffer();
    fgets(nomeBusca, sizeof(nomeBusca), stdin);
    nomeBusca[strcspn(nomeBusca, "\n")] = 0;

    for (int i = 0; i < numItensVetor; i++) {
        if (strcmp(mochilaVetor[i].nome, nomeBusca) == 0) {
            for (int j = i; j < numItensVetor - 1; j++) {
                mochilaVetor[j] = mochilaVetor[j + 1];
            }

            numItensVetor--;
            encontrado = 1;
            printf("\n\033[32m[SUCESSO] Item '%s' removido do Vetor.\033[0m\n", nomeBusca);
            break;
        }
    }

    if (!encontrado) {
        printf("\n\033[33m[AVISO] Item '%s' não encontrado no Vetor.\033[0m\n", nomeBusca);
    }
    listarItensVetor();
}

void listarItensVetor() {
    printf("\n--- Itens na Mochila (Vetor) - (%d/%d) ---\n", numItensVetor, MAX_ITENS);

    if (numItensVetor == 0) {
        printf("\033[36m(Vetor Vazio.)\033[0m\n");
        return;
    }

    printf("| %-29s | %-19s | %-10s |\n", "NOME", "TIPO", "QUANTIDADE");
    printf("---------------------------------------------------------------\n");

    for (int i = 0; i < numItensVetor; i++) {
        printf("| %-29s | %-19s | %-10d |\n",
               mochilaVetor[i].nome,
               mochilaVetor[i].tipo,
               mochilaVetor[i].quantidade);
    }
    printf("---------------------------------------------------------------\n");
}

void buscarSequencialVetor() {
    char nomeBusca[30];
    int encontrado = 0;
    comparacoesVetor = 0;

    if (numItensVetor == 0) {
        printf("\n\033[33m[AVISO] Vetor vazio. Nada para buscar.\033[0m\n");
        return;
    }

    printf("\n--- Busca Sequencial (Vetor) ---\n");
    printf("Digite o NOME do item: ");
    limparBuffer();
    fgets(nomeBusca, sizeof(nomeBusca), stdin);
    nomeBusca[strcspn(nomeBusca, "\n")] = 0;

    for (int i = 0; i < numItensVetor; i++) {
        comparacoesVetor++;
        if (strcmp(mochilaVetor[i].nome, nomeBusca) == 0) {
            printf("\n\033[32m[ENCONTRADO!] Item: %s | Tipo: %s | Qtd: %d\033[0m\n",
                   mochilaVetor[i].nome, mochilaVetor[i].tipo, mochilaVetor[i].quantidade);
            encontrado = 1;
            break;
        }
    }

    if (!encontrado) {
        printf("\n\033[33m[AVISO] Item '%s' não foi encontrado.\033[0m\n", nomeBusca);
    }
    printf("\n\033[34m[PERFORMANCE] Comparações Sequenciais: %lld\033[0m\n", comparacoesVetor);
}

void ordenarVetor() {
    if (numItensVetor <= 1) {
        printf("\n\033[33m[AVISO] O vetor precisa de pelo menos 2 itens para ordenar.\033[0m\n");
        return;
    }

    int i, j, min_idx;
    Item temp;
    comparacoesVetor = 0;

    // Selection Sort
    for (i = 0; i < numItensVetor - 1; i++) {
        min_idx = i;
        for (j = i + 1; j < numItensVetor; j++) {
            comparacoesVetor++;
            // Compara os nomes para ordenação alfabética
            if (strcmp(mochilaVetor[j].nome, mochilaVetor[min_idx].nome) < 0) {
                min_idx = j;
            }
        }
        // Troca o item encontrado pelo primeiro não ordenado
        if (min_idx != i) {
            temp = mochilaVetor[i];
            mochilaVetor[i] = mochilaVetor[min_idx];
            mochilaVetor[min_idx] = temp;
        }
    }

    printf("\n\033[32m[SUCESSO] Vetor ordenado por NOME (Selection Sort).\033[0m\n");
    printf("\n\033[34m[PERFORMANCE] Comparações na Ordenação: %lld\033[0m\n", comparacoesVetor);
    listarItensVetor();
}

void buscarBinariaVetor() {
    char nomeBusca[30];
    int encontrado = 0;
    comparacoesVetor = 0;

    if (numItensVetor == 0) {
        printf("\n\033[33m[AVISO] Vetor vazio. Nada para buscar.\033[0m\n");
        return;
    }

    printf("\n--- Busca Binária (Vetor Ordenado) ---\n");
    printf("Digite o NOME do item: ");
    limparBuffer();
    fgets(nomeBusca, sizeof(nomeBusca), stdin);
    nomeBusca[strcspn(nomeBusca, "\n")] = 0;

    int esq = 0;
    int dir = numItensVetor - 1;
    int meio;
    int resultadoComp;

    while (esq <= dir) {
        comparacoesVetor++;
        meio = esq + (dir - esq) / 2;
        resultadoComp = strcmp(mochilaVetor[meio].nome, nomeBusca);

        if (resultadoComp == 0) {
            printf("\n\033[32m[ENCONTRADO!] Item: %s | Tipo: %s | Qtd: %d\033[0m\n",
                   mochilaVetor[meio].nome, mochilaVetor[meio].tipo, mochilaVetor[meio].quantidade);
            encontrado = 1;
            break;
        } else if (resultadoComp < 0) {
            esq = meio + 1;
        } else {
            dir = meio - 1;
        }
    }

    if (!encontrado) {
        printf("\n\033[33m[AVISO] Item '%s' não foi encontrado.\033[0m\n", nomeBusca);
    }
    printf("\n\033[34m[PERFORMANCE] Comparações Binárias: %lld\033[0m\n", comparacoesVetor);
}

// --- Funções da Mochila (Lista Encadeada) ---

void inserirItemLista() {
    No *novoNo = (No*)malloc(sizeof(No));
    if (novoNo == NULL) {
        printf("\n\033[31m[ERRO] Falha na alocação de memória (Lista).\033[0m\n");
        return;
    }

    printf("\n--- Coletar Novo Item (Lista) ---\n");
    
    printf("Nome do Item (max 29): ");
    limparBuffer();
    fgets(novoNo->dados.nome, sizeof(novoNo->dados.nome), stdin);
    novoNo->dados.nome[strcspn(novoNo->dados.nome, "\n")] = 0;

    printf("Tipo do Item (ex: arma, munição, cura): ");
    if (scanf("%s", novoNo->dados.tipo) != 1) {
         printf("\n\033[31m[ERRO] Falha na leitura do tipo.\033[0m\n");
         limparBuffer();
         free(novoNo);
         return;
    }

    printf("Quantidade: ");
    while (scanf("%d", &novoNo->dados.quantidade) != 1 || novoNo->dados.quantidade <= 0) {
        printf("\033[33mEntrada inválida. Digite um número inteiro positivo: \033[0m");
        limparBuffer();
    }
    limparBuffer();

    // Inserção no início da lista (mais eficiente)
    novoNo->proximo = mochilaLista;
    mochilaLista = novoNo;

    printf("\n\033[32m[SUCESSO] Item '%s' adicionado à Lista Encadeada.\033[0m\n", novoNo->dados.nome);
    listarItensLista();
}

void removerItemLista() {
    char nomeBusca[30];
    int encontrado = 0;

    if (mochilaLista == NULL) {
        printf("\n\033[33m[AVISO] Mochila (Lista) vazia. Nada para descartar.\033[0m\n");
        return;
    }

    printf("\n--- Descartar Item (Lista) ---\n");
    printf("Digite o NOME do item a ser removido: ");
    limparBuffer();
    fgets(nomeBusca, sizeof(nomeBusca), stdin);
    nomeBusca[strcspn(nomeBusca, "\n")] = 0;

    No *atual = mochilaLista;
    No *anterior = NULL;

    while (atual != NULL) {
        if (strcmp(atual->dados.nome, nomeBusca) == 0) {
            if (anterior == NULL) {
                mochilaLista = atual->proximo; // Remoção do primeiro nó
            } else {
                anterior->proximo = atual->proximo; // Remoção de nó no meio/fim
            }
            printf("\n\033[32m[SUCESSO] Item '%s' removido da Lista Encadeada.\033[0m\n", atual->dados.nome);
            free(atual);
            encontrado = 1;
            break;
        }
        anterior = atual;
        atual = atual->proximo;
    }

    if (!encontrado) {
        printf("\n\033[33m[AVISO] Item '%s' não encontrado na Lista.\033[0m\n", nomeBusca);
    }
    listarItensLista();
}

void listarItensLista() {
    No *atual = mochilaLista;
    int count = 0;

    printf("\n--- Itens na Mochila (Lista Encadeada) ---\n");

    if (mochilaLista == NULL) {
        printf("\033[36m(Lista Encadeada Vazia.)\033[0m\n");
        return;
    }

    printf("| %-29s | %-19s | %-10s |\n", "NOME", "TIPO", "QUANTIDADE");
    printf("---------------------------------------------------------------\n");

    while (atual != NULL) {
        printf("| %-29s | %-19s | %-10d |\n",
               atual->dados.nome,
               atual->dados.tipo,
               atual->dados.quantidade);
        atual = atual->proximo;
        count++;
    }
    printf("---------------------------------------------------------------\n");
    printf("Total de itens: %d\n", count);
}

void buscarSequencialLista() {
    char nomeBusca[30];
    int encontrado = 0;
    comparacoesLista = 0;

    if (mochilaLista == NULL) {
        printf("\n\033[33m[AVISO] Lista vazia. Nada para buscar.\033[0m\n");
        return;
    }

    printf("\n--- Busca Sequencial (Lista Encadeada) ---\n");
    printf("Digite o NOME do item: ");
    limparBuffer();
    fgets(nomeBusca, sizeof(nomeBusca), stdin);
    nomeBusca[strcspn(nomeBusca, "\n")] = 0;

    No *atual = mochilaLista;

    while (atual != NULL) {
        comparacoesLista++;
        if (strcmp(atual->dados.nome, nomeBusca) == 0) {
            printf("\n\033[32m[ENCONTRADO!] Item: %s | Tipo: %s | Qtd: %d\033[0m\n",
                   atual->dados.nome, atual->dados.tipo, atual->dados.quantidade);
            encontrado = 1;
            break;
        }
        atual = atual->proximo;
    }

    if (!encontrado) {
        printf("\n\033[33m[AVISO] Item '%s' não foi encontrado.\033[0m\n", nomeBusca);
    }
    printf("\n\033[34m[PERFORMANCE] Comparações Sequenciais: %lld\033[0m\n", comparacoesLista);
}

// --- Funções de Menu ---

void exibirMenuVetor() {
    int opcao;
    do {
        limparTela();
        printf("\n================================================\n");
        printf("|    MOCHILA - VETOR (LISTA SEQUENCIAL)      |\n");
        printf("================================================\n");
        printf("1. Inserir Item\n");
        printf("2. Remover Item por Nome\n");
        printf("3. Listar Itens\n");
        printf("4. Buscar Sequencial por Nome\n");
        printf("5. Ordenar por Nome (Selection Sort)\n");
        printf("6. Buscar Binária por Nome\n");
        printf("0. Voltar ao Menu Principal\n");
        printf("------------------------------------------------\n");
        printf("Escolha uma opção: ");

        if (scanf("%d", &opcao) != 1) {
            printf("\n\033[31m[ERRO] Opção inválida.\033[0m\n");
            limparBuffer();
            opcao = -1;
            continue;
        }

        switch (opcao) {
            case 1: inserirItemVetor(); break;
            case 2: removerItemVetor(); break;
            case 3: listarItensVetor(); break;
            case 4: buscarSequencialVetor(); break;
            case 5: ordenarVetor(); break;
            case 6: buscarBinariaVetor(); break;
            case 0: printf("\nVoltando...\n"); break;
            default: printf("\n\033[31m[ERRO] Opção inexistente.\033[0m\n");
        }
        if (opcao != 0) {
            printf("\nPressione ENTER para continuar...\n");
            limparBuffer();
            getchar();
        }

    } while (opcao != 0);
}

void exibirMenuLista() {
    int opcao;
    do {
        limparTela();
        printf("\n================================================\n");
        printf("|    MOCHILA - LISTA (LISTA ENCADEDA)        |\n");
        printf("================================================\n");
        printf("1. Inserir Item\n");
        printf("2. Remover Item por Nome\n");
        printf("3. Listar Itens\n");
        printf("4. Buscar Sequencial por Nome\n");
        printf("0. Voltar ao Menu Principal\n");
        printf("------------------------------------------------\n");
        printf("Escolha uma opção: ");

        if (scanf("%d", &opcao) != 1) {
            printf("\n\033[31m[ERRO] Opção inválida.\033[0m\n");
            limparBuffer();
            opcao = -1;
            continue;
        }

        switch (opcao) {
            case 1: inserirItemLista(); break;
            case 2: removerItemLista(); break;
            case 3: listarItensLista(); break;
            case 4: buscarSequencialLista(); break;
            case 0: printf("\nVoltando...\n"); break;
            default: printf("\n\033[31m[ERRO] Opção inexistente.\033[0m\n");
        }
        if (opcao != 0) {
            printf("\nPressione ENTER para continuar...\n");
            limparBuffer();
            getchar();
        }

    } while (opcao != 0);
}

void exibirMenuPrincipal() {
    int opcao;
    do {
        limparTela();
        printf("\n================================================\n");
        printf("| BATTLE ROYALE - INVENTÁRIO (NÍVEL AVENTUREIRO) |\n");
        printf("================================================\n");
        printf("Escolha a Estrutura de Dados para a Mochila:\n");
        printf("1. Vetor (Lista Sequencial)\n");
        printf("2. Lista Encadeada (Estrutura Dinâmica)\n");
        printf("0. Sair do Jogo\n");
        printf("------------------------------------------------\n");
        printf("Opção: ");

        if (scanf("%d", &opcao) != 1) {
            printf("\n\033[31m[ERRO] Opção inválida.\033[0m\n");
            limparBuffer();
            opcao = -1;
            continue;
        }
        limparBuffer();

        switch (opcao) {
            case 1: exibirMenuVetor(); break;
            case 2: exibirMenuLista(); break;
            case 0: printf("\n\033[34m[FIM] Comparação de estruturas finalizada.\033[0m\n"); break;
            default: printf("\n\033[31m[ERRO] Opção inexistente. Tente 0, 1 ou 2.\033[0m\n");
        }
        
        if (opcao != 0) {
            printf("\nPressione ENTER para voltar ao menu principal...\n");
            getchar();
        }

    } while (opcao != 0);
}

// --- Função Principal ---

int main() {
    exibirMenuPrincipal();
    
    // Libera a memória da lista encadeada ao sair, se necessário.
    No *atual = mochilaLista;
    No *proximo;
    while (atual != NULL) {
        proximo = atual->proximo;
        free(atual);
        atual = proximo;
    }

    return 0;
}
