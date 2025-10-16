#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <stdbool.h>

// --- Estrutura de Dados ---

typedef struct {
    char nome[30];
    char tipo[20];
    int prioridade; // Novo campo: 1 (Mais Alta) a 10 (Mais Baixa)
} Componente;

// --- Variáveis Globais ---
#define MAX_COMPONENTES 20 // Nova Capacidade
Componente torre[MAX_COMPONENTES];
int numComponentes = 0;
long long comparacoes = 0;
bool ordenadoPorNome = false;

// --- Protótipos das Funções ---

void limparBuffer();
void limparTela();
void exibirMenuPrincipal();
void cadastrarComponente();
void mostrarComponentes();
void removerComponente(); // Mantida a funcionalidade de remoção
void medirTempoEOrdenar(void (*algoritmo)(Componente[], int), const char *nomeAlgoritmo, int criterio);
void bubbleSortNome(Componente arr[], int n);
void insertionSortTipo(Componente arr[], int n);
void selectionSortPrioridade(Componente arr[], int n);
void buscaBinariaPorNome();

// --- Funções Auxiliares ---

void limparBuffer() {
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}

void limparTela() {
    printf("\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n");
}

// --- Funções de Gerenciamento ---

void cadastrarComponente() {
    if (numComponentes >= MAX_COMPONENTES) {
        printf("\n\033[31m[ERRO] Torre de Fuga completa! Max. %d componentes.\033[0m\n", MAX_COMPONENTES);
        return;
    }

    printf("\n--- Cadastro de Componente (%d/%d) ---\n", numComponentes + 1, MAX_COMPONENTES);
    
    printf("Nome do Componente (max 29): ");
    limparBuffer();
    fgets(torre[numComponentes].nome, sizeof(torre[numComponentes].nome), stdin);
    torre[numComponentes].nome[strcspn(torre[numComponentes].nome, "\n")] = 0;

    printf("Tipo (ex: controle, suporte, propulsão): ");
    if (scanf("%s", torre[numComponentes].tipo) != 1) {
         printf("\n\033[31m[ERRO] Falha na leitura do tipo.\033[0m\n");
         limparBuffer();
         return;
    }

    printf("Prioridade (1 - Mais Alta, 10 - Mais Baixa): ");
    while (scanf("%d", &torre[numComponentes].prioridade) != 1 || torre[numComponentes].prioridade < 1 || torre[numComponentes].prioridade > 10) {
        printf("\033[33mPrioridade inválida. Digite um valor entre 1 e 10: \033[0m");
        limparBuffer();
    }
    limparBuffer();

    numComponentes++;
    ordenadoPorNome = false;
    printf("\n\033[32m[SUCESSO] Componente '%s' adicionado.\033[0m\n", torre[numComponentes-1].nome);
    mostrarComponentes();
}

void removerComponente() {
    char nomeBusca[30];
    int encontrado = 0;

    if (numComponentes == 0) {
        printf("\n\033[33m[AVISO] Vetor vazio. Nada para descartar.\033[0m\n");
        return;
    }

    printf("\n--- Descartar Componente ---\n");
    printf("Digite o NOME do componente a ser removido: ");
    limparBuffer();
    fgets(nomeBusca, sizeof(nomeBusca), stdin);
    nomeBusca[strcspn(nomeBusca, "\n")] = 0;

    for (int i = 0; i < numComponentes; i++) {
        if (strcmp(torre[i].nome, nomeBusca) == 0) {
            for (int j = i; j < numComponentes - 1; j++) {
                torre[j] = torre[j + 1];
            }

            numComponentes--;
            encontrado = 1;
            ordenadoPorNome = false;
            printf("\n\033[32m[SUCESSO] Componente '%s' removido.\033[0m\n", nomeBusca);
            break;
        }
    }

    if (!encontrado) {
        printf("\n\033[33m[AVISO] Componente '%s' não encontrado.\033[0m\n", nomeBusca);
    }
    mostrarComponentes();
}

void mostrarComponentes() {
    printf("\n--- Componentes da Torre de Fuga (%d/%d) ---\n", numComponentes, MAX_COMPONENTES);

    if (numComponentes == 0) {
        printf("\033[36m(Nenhum componente cadastrado.)\033[0m\n");
        return;
    }

    printf("| %-29s | %-19s | %-10s |\n", "NOME", "TIPO", "PRIORIDADE");
    printf("---------------------------------------------------------------\n");

    for (int i = 0; i < numComponentes; i++) {
        printf("| %-29s | %-19s | %-10d |\n",
               torre[i].nome,
               torre[i].tipo,
               torre[i].prioridade);
    }
    printf("---------------------------------------------------------------\n");
}

// --- Algoritmos de Ordenação ---

void bubbleSortNome(Componente arr[], int n) {
    int i, j;
    Componente temp;
    comparacoes = 0;

    for (i = 0; i < n - 1; i++) {
        for (j = 0; j < n - i - 1; j++) {
            comparacoes++;
            if (strcmp(arr[j].nome, arr[j + 1].nome) > 0) {
                temp = arr[j];
                arr[j] = arr[j + 1];
                arr[j + 1] = temp;
            }
        }
    }
}

void insertionSortTipo(Componente arr[], int n) {
    int i, j;
    Componente chave;
    comparacoes = 0;

    for (i = 1; i < n; i++) {
        chave = arr[i];
        j = i - 1;

        while (j >= 0) {
            comparacoes++;
            if (strcmp(arr[j].tipo, chave.tipo) > 0) {
                arr[j + 1] = arr[j];
                j = j - 1;
            } else {
                break;
            }
        }
        arr[j + 1] = chave;
    }
}

void selectionSortPrioridade(Componente arr[], int n) {
    int i, j, min_idx;
    Componente temp;
    comparacoes = 0;

    for (i = 0; i < n - 1; i++) {
        min_idx = i;
        for (j = i + 1; j < n; j++) {
            comparacoes++;
            if (arr[j].prioridade < arr[min_idx].prioridade) {
                min_idx = j;
            }
        }
        if (min_idx != i) {
            temp = arr[i];
            arr[i] = arr[min_idx];
            arr[min_idx] = temp;
        }
    }
}

void medirTempoEOrdenar(void (*algoritmo)(Componente[], int), const char *nomeAlgoritmo, int criterio) {
    if (numComponentes < 1) {
        printf("\n\033[33m[AVISO] Cadastre componentes antes de ordenar.\033[0m\n");
        return;
    }

    clock_t inicio, fim;
    double tempo;

    ordenadoPorNome = false;

    if (numComponentes < 2) {
        printf("\n\033[33m[AVISO] Necessário pelo menos 2 componentes para ordenar.\033[0m\n");
        return;
    }

    inicio = clock();
    algoritmo(torre, numComponentes);
    fim = clock();

    tempo = ((double)(fim - inicio)) / CLOCKS_PER_SEC;

    if (criterio == 1) {
        ordenadoPorNome = true;
    }
    
    printf("\n\033[32m[SUCESSO] Ordenação por %s concluída!\033[0m\n", nomeAlgoritmo);
    printf("\033[34m[PERFORMANCE] Comparações: %lld\033[0m\n", comparacoes);
    printf("\033[34m[PERFORMANCE] Tempo de Execução: %.6f segundos\033[0m\n", tempo);
    
    mostrarComponentes();
}

// --- Algoritmo de Busca ---

void buscaBinariaPorNome() {
    char nomeBusca[30];
    int encontrado = 0;
    long long comparacoesBusca = 0;

    if (numComponentes == 0) {
        printf("\n\033[33m[AVISO] Nenhum componente para buscar.\033[0m\n");
        return;
    }

    if (!ordenadoPorNome) {
        printf("\n\033[31m[ERRO] A busca binária exige ordenação por NOME (Opção 3)!\033[0m\n");
        return;
    }

    printf("\n--- Busca Binária (Componente-Chave) ---\n");
    printf("Digite o NOME do componente-chave: ");
    limparBuffer();
    fgets(nomeBusca, sizeof(nomeBusca), stdin);
    nomeBusca[strcspn(nomeBusca, "\n")] = 0;

    int esq = 0;
    int dir = numComponentes - 1;
    int meio;
    int resultadoComp;

    while (esq <= dir) {
        comparacoesBusca++;
        meio = esq + (dir - esq) / 2;
        resultadoComp = strcmp(torre[meio].nome, nomeBusca);

        if (resultadoComp == 0) {
            printf("\n\033[32m[CHAVE ENCONTRADA!] Montagem da Torre HABILITADA.\033[0m\n");
            printf(" Componente: %s | Tipo: %s | Prioridade: %d\n",
                   torre[meio].nome, torre[meio].tipo, torre[meio].prioridade);
            encontrado = 1;
            break;
        } else if (resultadoComp < 0) {
            esq = meio + 1;
        } else {
            dir = meio - 1;
        }
    }

    if (!encontrado) {
        printf("\n\033[33m[AVISO] Componente-chave '%s' NÃO encontrado.\033[0m\n", nomeBusca);
    }
    printf("\n\033[34m[PERFORMANCE] Comparações Binárias: %lld\033[0m\n", comparacoesBusca);
}

// --- Menu Principal ---

void exibirMenuPrincipal() {
    int opcao;
    do {
        limparTela();
        printf("\n================================================\n");
        printf("| BATTLE ROYALE - MÓDULO TORRE DE FUGA (MESTRE) |\n");
        printf("================================================\n");
        printf("1. Cadastrar Componente (%d/%d)\n", numComponentes, MAX_COMPONENTES);
        printf("2. Remover Componente\n");
        printf("3. Ordenar por NOME (Bubble Sort)\n");
        printf("4. Ordenar por TIPO (Insertion Sort)\n");
        printf("5. Ordenar por PRIORIDADE (Selection Sort)\n");
        printf("6. Buscar Componente-Chave (Busca Binária)\n");
        printf("7. Listar Componentes Atuais\n");
        printf("0. Sair do Jogo\n");
        printf("------------------------------------------------\n");
        printf("Status Busca Binária: %s\n", ordenadoPorNome ? "\033[32mHABILITADA\033[0m" : "\033[31mDESABILITADA (Ordenar por Nome)\033[0m");
        printf("------------------------------------------------\n");
        printf("Opção: ");

        if (scanf("%d", &opcao) != 1) {
            printf("\n\033[31m[ERRO] Opção inválida.\033[0m\n");
            limparBuffer();
            opcao = -1;
            continue;
        }

        switch (opcao) {
            case 1: cadastrarComponente(); break;
            case 2: removerComponente(); break;
            case 3: medirTempoEOrdenar(bubbleSortNome, "Bubble Sort (NOME)", 1); break;
            case 4: medirTempoEOrdenar(insertionSortTipo, "Insertion Sort (TIPO)", 0); break;
            case 5: medirTempoEOrdenar(selectionSortPrioridade, "Selection Sort (PRIORIDADE)", 0); break;
            case 6: buscaBinariaPorNome(); break;
            case 7: mostrarComponentes(); break;
            case 0: printf("\n\033[34m[FIM DE JOGO] Desafios de Estrutura de Dados concluídos!\033[0m\n"); break;
            default: printf("\n\033[31m[ERRO] Opção inexistente.\033[0m\n");
        }
        
        if (opcao != 0) {
            printf("\nPressione ENTER para continuar...\n");
            limparBuffer();
            getchar();
        }

    } while (opcao != 0);
}

// --- Função Principal ---

int main() {
    exibirMenuPrincipal();
    return 0;
}
