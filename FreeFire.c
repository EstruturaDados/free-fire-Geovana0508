#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>


#define MAX_ITENS 10

// ======================
// Estruturas de Dados
// ======================
typedef struct {
    char nome[30];
    char tipo[20];
    int quantidade;
} Item;

typedef struct No {
    Item dados;
    struct No *proximo;
} No;

// ======================
// Declarações de Funções
// ======================

// Funções do vetor
void inserirItemVetor(Item mochila[], int *qtd);
void removerItemVetor(Item mochila[], int *qtd);
void listarItensVetor(Item mochila[], int qtd);
void ordenarVetor(Item mochila[], int qtd);
int buscarSequencialVetor(Item mochila[], int qtd, char nome[], int *comparacoes);
int buscarBinariaVetor(Item mochila[], int qtd, char nome[], int *comparacoes);

// Funções da lista encadeada
No* inserirItemLista(No *inicio);
No* removerItemLista(No *inicio);
void listarItensLista(No *inicio);
int buscarSequencialLista(No *inicio, char nome[], int *comparacoes);

// ======================
// Função principal
// ======================
int main() {
    Item mochilaVetor[MAX_ITENS];
    int qtdVetor = 0;
    No *mochilaLista = NULL;
    int opcaoEstrutura, opcao;

    do {
        printf("\n===== SELECIONE A ESTRUTURA =====\n");
        printf("1. Mochila com Vetor (Lista Sequencial)\n");
        printf("2. Mochila com Lista Encadeada\n");
        printf("0. Sair\n");
        printf("=================================\n");
        printf("Escolha: ");
        scanf("%d", &opcaoEstrutura);
        getchar();

        if (opcaoEstrutura == 1) {
            do {
                printf("\n--- MOCHILA (VETOR) ---\n");
                printf("1. Inserir item\n");
                printf("2. Remover item\n");
                printf("3. Listar itens\n");
                printf("4. Ordenar e buscar (Binária)\n");
                printf("0. Voltar\n");
                printf("Escolha: ");
                scanf("%d", &opcao);
                getchar();

                if (opcao == 1)
                    inserirItemVetor(mochilaVetor, &qtdVetor);
                else if (opcao == 2)
                    removerItemVetor(mochilaVetor, &qtdVetor);
                else if (opcao == 3)
                    listarItensVetor(mochilaVetor, qtdVetor);
                else if (opcao == 4) {
                    ordenarVetor(mochilaVetor, qtdVetor);
                    char nomeBusca[30];
                    printf("\nDigite o nome do item para buscar: ");
                    fgets(nomeBusca, sizeof(nomeBusca), stdin);
                    nomeBusca[strcspn(nomeBusca, "\n")] = '\0';
                    int comparacoesSeq = 0, comparacoesBin = 0;
                    buscarSequencialVetor(mochilaVetor, qtdVetor, nomeBusca, &comparacoesSeq);
                    buscarBinariaVetor(mochilaVetor, qtdVetor, nomeBusca, &comparacoesBin);
                    printf("\nComparacoes (Sequencial): %d | (Binaria): %d\n",
                           comparacoesSeq, comparacoesBin);
                }
            } while (opcao != 0);
        }

        else if (opcaoEstrutura == 2) {
            do {
                printf("\n--- MOCHILA (LISTA ENCADEADA) ---\n");
                printf("1. Inserir item\n");
                printf("2. Remover item\n");
                printf("3. Listar itens\n");
                printf("4. Buscar item\n");
                printf("0. Voltar\n");
                printf("Escolha: ");
                scanf("%d", &opcao);
                getchar();

                if (opcao == 1)
                    mochilaLista = inserirItemLista(mochilaLista);
                else if (opcao == 2)
                    mochilaLista = removerItemLista(mochilaLista);
                else if (opcao == 3)
                    listarItensLista(mochilaLista);
                else if (opcao == 4) {
                    char nomeBusca[30];
                    printf("\nDigite o nome do item: ");
                    fgets(nomeBusca, sizeof(nomeBusca), stdin);
                    nomeBusca[strcspn(nomeBusca, "\n")] = '\0';
                    int comparacoes = 0;
                    buscarSequencialLista(mochilaLista, nomeBusca, &comparacoes);
                    printf("\nComparacoes (Sequencial Lista): %d\n", comparacoes);
                }
            } while (opcao != 0);
        }

    } while (opcaoEstrutura != 0);

    printf("\nEncerrando o sistema...\n");
    return 0;
}

// ======================
// Funções — Vetor
// ======================
void inserirItemVetor(Item mochila[], int *qtd) {
    if (*qtd >= MAX_ITENS) {
        printf("\nMochila cheia!\n");
        return;
    }
    Item novo;
    printf("\nNome: ");
    fgets(novo.nome, sizeof(novo.nome), stdin);
    novo.nome[strcspn(novo.nome, "\n")] = '\0';
    printf("Tipo: ");
    fgets(novo.tipo, sizeof(novo.tipo), stdin);
    novo.tipo[strcspn(novo.tipo, "\n")] = '\0';
    printf("Quantidade: ");
    scanf("%d", &novo.quantidade);
    getchar();
    mochila[*qtd] = novo;
    (*qtd)++;
    printf("\nItem inserido!\n");
}

void removerItemVetor(Item mochila[], int *qtd) {
    if (*qtd == 0) {
        printf("\nMochila vazia!\n");
        return;
    }
    char nome[30];
    printf("\nDigite o nome do item a remover: ");
    fgets(nome, sizeof(nome), stdin);
    nome[strcspn(nome, "\n")] = '\0';
    int i, encontrado = 0;
    for (i = 0; i < *qtd; i++) {
        if (strcmp(mochila[i].nome, nome) == 0) {
            encontrado = 1;
            for (int j = i; j < *qtd - 1; j++)
                mochila[j] = mochila[j + 1];
            (*qtd)--;
            printf("\nItem removido!\n");
            break;
        }
    }
    if (!encontrado)
        printf("\nItem nao encontrado!\n");
}

void listarItensVetor(Item mochila[], int qtd) {
    if (qtd == 0) {
        printf("\nMochila vazia!\n");
        return;
    }
    printf("\n--- Itens na Mochila (Vetor) ---\n");
    for (int i = 0; i < qtd; i++)
        printf("%d. %s | %s | %d\n", i + 1, mochila[i].nome, mochila[i].tipo, mochila[i].quantidade);
}

void ordenarVetor(Item mochila[], int qtd) {
    for (int i = 0; i < qtd - 1; i++) {
        for (int j = 0; j < qtd - i - 1; j++) {
            if (strcmp(mochila[j].nome, mochila[j + 1].nome) > 0) {
                Item temp = mochila[j];
                mochila[j] = mochila[j + 1];
                mochila[j + 1] = temp;
            }
        }
    }
    printf("\nItens ordenados por nome.\n");
}

int buscarSequencialVetor(Item mochila[], int qtd, char nome[], int *comparacoes) {
    for (int i = 0; i < qtd; i++) {
        (*comparacoes)++;
        if (strcmp(mochila[i].nome, nome) == 0) {
            printf("\n[Busca Sequencial Vetor] Item encontrado: %s | %s | %d\n",
                   mochila[i].nome, mochila[i].tipo, mochila[i].quantidade);
            return i;
        }
    }
    printf("\n[Busca Sequencial Vetor] Item nao encontrado.\n");
    return -1;
}

int buscarBinariaVetor(Item mochila[], int qtd, char nome[], int *comparacoes) {
    int inicio = 0, fim = qtd - 1;
    while (inicio <= fim) {
        int meio = (inicio + fim) / 2;
        (*comparacoes)++;
        int cmp = strcmp(mochila[meio].nome, nome);
        if (cmp == 0) {
            printf("\n[Busca Binaria Vetor] Item encontrado: %s | %s | %d\n",
                   mochila[meio].nome, mochila[meio].tipo, mochila[meio].quantidade);
            return meio;
        } else if (cmp < 0) {
            inicio = meio + 1;
        } else {
            fim = meio - 1;
        }
    }
    printf("\n[Busca Binaria Vetor] Item nao encontrado.\n");
    return -1;
}

// ======================
// Funções — Lista Encadeada
// ======================
No* inserirItemLista(No *inicio) {
    No *novo = (No*) malloc(sizeof(No));
    printf("\nNome: ");
    fgets(novo->dados.nome, sizeof(novo->dados.nome), stdin);
    novo->dados.nome[strcspn(novo->dados.nome, "\n")] = '\0';
    printf("Tipo: ");
    fgets(novo->dados.tipo, sizeof(novo->dados.tipo), stdin);
    novo->dados.tipo[strcspn(novo->dados.tipo, "\n")] = '\0';
    printf("Quantidade: ");
    scanf("%d", &novo->dados.quantidade);
    getchar();

    novo->proximo = inicio;
    printf("\nItem inserido na lista!\n");
    return novo;
}

No* removerItemLista(No *inicio) {
    if (inicio == NULL) {
        printf("\nLista vazia!\n");
        return NULL;
    }
    char nome[30];
    printf("\nDigite o nome do item a remover: ");
    fgets(nome, sizeof(nome), stdin);
    nome[strcspn(nome, "\n")] = '\0';
    No *atual = inicio, *anterior = NULL;
    while (atual != NULL && strcmp(atual->dados.nome, nome) != 0) {
        anterior = atual;
        atual = atual->proximo;
    }
    if (atual == NULL) {
        printf("\nItem nao encontrado!\n");
        return inicio;
    }
    if (anterior == NULL)
        inicio = atual->proximo;
    else
        anterior->proximo = atual->proximo;
    free(atual);
    printf("\nItem removido!\n");
    return inicio;
}

void listarItensLista(No *inicio) {
    if (inicio == NULL) {
        printf("\nLista vazia!\n");
        return;
    }
    printf("\n--- Itens na Mochila (Lista Encadeada) ---\n");
    No *aux = inicio;
    int i = 1;
    while (aux != NULL) {
        printf("%d. %s | %s | %d\n", i, aux->dados.nome, aux->dados.tipo, aux->dados.quantidade);
        aux = aux->proximo;
        i++;
    }
}

int buscarSequencialLista(No *inicio, char nome[], int *comparacoes) {
    No *aux = inicio;
    while (aux != NULL) {
        (*comparacoes)++;
        if (strcmp(aux->dados.nome, nome) == 0) {
            printf("\n[Busca Sequencial Lista] Item encontrado: %s | %s | %d\n",
                   aux->dados.nome, aux->dados.tipo, aux->dados.quantidade);
            return 1;
        }
        aux = aux->proximo;
    }
    printf("\n[Busca Sequencial Lista] Item nao encontrado.\n");
    return 0;
}

