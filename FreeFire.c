#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>
#include <time.h>

#define MAX_ITENS 10
#define MAX_COMPONENTES 20

typedef struct {
    char nome[30];
    char tipo[20];
    int quantidade;
} Item;

typedef struct No {
    Item dados;
    struct No *proximo;
} No;

typedef struct {
    char nome[30];
    char tipo[20];
    int prioridade; // 1 a 10
} Componente;

/* Funções — Inventário (vetor) */
void inserirItemVetor(Item mochila[], int *qtd);
void removerItemVetor(Item mochila[], int *qtd);
void listarItensVetor(Item mochila[], int qtd);
void ordenarVetor(Item mochila[], int qtd);
int buscarSequencialVetor(Item mochila[], int qtd, char nome[], int *comparacoes);
int buscarBinariaVetor(Item mochila[], int qtd, char nome[], int *comparacoes);

/* Funções — Inventário (lista encadeada) */
No* inserirItemLista(No *inicio);
No* removerItemLista(No *inicio);
void listarItensLista(No *inicio);
int buscarSequencialLista(No *inicio, char nome[], int *comparacoes);

/* Funções — Torre de Resgate (componente / ordenações / busca) */
void cadastrarComponentes(Componente comps[], int *n);
void mostrarComponentes(Componente comps[], int n);
void bubbleSortNome(Componente comps[], int n, long *comparacoes, double *tempo);
void insertionSortTipo(Componente comps[], int n, long *comparacoes, double *tempo);
void selectionSortPrioridade(Componente comps[], int n, long *comparacoes, double *tempo);
int buscaBinariaPorNome(Componente comps[], int n, char chave[], long *comparacoes);

int main() {
    Item mochilaVetor[MAX_ITENS];
    int qtdVetor = 0;
    No *mochilaLista = NULL;
    int opcaoEstrutura, opcao;

    Componente componentes[MAX_COMPONENTES];
    int qtdComponentes = 0;
    bool ordenadoPorNome = false;

    do {
        printf("\n===== MENU PRINCIPAL =====\n");
        printf("1. Mochila com Vetor\n");
        printf("2. Mochila com Lista Encadeada\n");
        printf("3. Torre de Resgate (montagem de componentes)\n");
        printf("0. Sair\n");
        printf("==========================\n");
        printf("Escolha: ");
        if (scanf("%d", &opcaoEstrutura) != 1) { while (getchar() != '\n'); opcaoEstrutura = -1; }
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
                if (scanf("%d", &opcao) != 1) { while (getchar() != '\n'); opcao = -1; }
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
                if (scanf("%d", &opcao) != 1) { while (getchar() != '\n'); opcao = -1; }
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

        else if (opcaoEstrutura == 3) {
            int opcMestre;
            do {
                printf("\n--- TORRE DE RESGATE ---\n");
                printf("1. Cadastrar componentes (max %d)\n", MAX_COMPONENTES);
                printf("2. Mostrar componentes\n");
                printf("3. Ordenar por NOME (Bubble Sort) e buscar chave (binária)\n");
                printf("4. Ordenar por TIPO (Insertion Sort)\n");
                printf("5. Ordenar por PRIORIDADE (Selection Sort)\n");
                printf("6. Buscar componente por NOME (binária) (exige ordenado por nome)\n");
                printf("0. Voltar\n");
                printf("Escolha: ");
                if (scanf("%d", &opcMestre) != 1) { while (getchar() != '\n'); opcMestre = -1; }
                getchar();

                if (opcMestre == 1) {
                    cadastrarComponentes(componentes, &qtdComponentes);
                    ordenadoPorNome = false;
                } else if (opcMestre == 2) {
                    mostrarComponentes(componentes, qtdComponentes);
                } else if (opcMestre == 3) {
                    if (qtdComponentes == 0) {
                        printf("\nNenhum componente cadastrado.\n");
                    } else {
                        long comps = 0;
                        double tempo = 0.0;
                        bubbleSortNome(componentes, qtdComponentes, &comps, &tempo);
                        ordenadoPorNome = true;
                        printf("\nBubble Sort (por nome) - Comparacoes: %ld | Tempo: %.6f s\n", comps, tempo);

                        char chave[30];
                        printf("\nDigite o nome do componente-chave para buscar (ou ENTER para pular): ");
                        fgets(chave, sizeof(chave), stdin);
                        chave[strcspn(chave, "\n")] = '\0';
                        if (strlen(chave) > 0) {
                            long compsBusca = 0;
                            int idx = buscaBinariaPorNome(componentes, qtdComponentes, chave, &compsBusca);
                            printf("Comparacoes (Busca Binaria): %ld\n", compsBusca);
                            if (idx >= 0) {
                                printf("Componente-chave encontrado: %s | %s | %d\n",
                                       componentes[idx].nome, componentes[idx].tipo, componentes[idx].prioridade);
                            } else {
                                printf("Componente-chave NAO encontrado.\n");
                            }
                        }
                    }
                } else if (opcMestre == 4) {
                    if (qtdComponentes == 0) {
                        printf("\nNenhum componente cadastrado.\n");
                    } else {
                        long comps = 0;
                        double tempo = 0.0;
                        insertionSortTipo(componentes, qtdComponentes, &comps, &tempo);
                        ordenadoPorNome = false;
                        printf("\nInsertion Sort (por tipo) - Comparacoes: %ld | Tempo: %.6f s\n", comps, tempo);
                        mostrarComponentes(componentes, qtdComponentes);
                    }
                } else if (opcMestre == 5) {
                    if (qtdComponentes == 0) {
                        printf("\nNenhum componente cadastrado.\n");
                    } else {
                        long comps = 0;
                        double tempo = 0.0;
                        selectionSortPrioridade(componentes, qtdComponentes, &comps, &tempo);
                        ordenadoPorNome = false;
                        printf("\nSelection Sort (por prioridade) - Comparacoes: %ld | Tempo: %.6f s\n", comps, tempo);
                        mostrarComponentes(componentes, qtdComponentes);
                    }
                } else if (opcMestre == 6) {
                    if (qtdComponentes == 0) {
                        printf("\nNenhum componente cadastrado.\n");
                    } else if (!ordenadoPorNome) {
                        printf("\nATENCAO: a busca binaria exige que os componentes estejam ordenados por NOME.\n");
                        printf("Use a opcao 3 para ordenar por nome antes de buscar.\n");
                    } else {
                        char chave[30];
                        printf("\nDigite o nome do componente-chave: ");
                        fgets(chave, sizeof(chave), stdin);
                        chave[strcspn(chave, "\n")] = '\0';
                        long compsBusca = 0;
                        int idx = buscaBinariaPorNome(componentes, qtdComponentes, chave, &compsBusca);
                        printf("Comparacoes (Busca Binaria): %ld\n", compsBusca);
                        if (idx >= 0) {
                            printf("Componente encontrado: %s | %s | %d\n",
                                   componentes[idx].nome, componentes[idx].tipo, componentes[idx].prioridade);
                        } else {
                            printf("Componente NAO encontrado.\n");
                        }
                    }
                }

            } while (opcMestre != 0);
        }

    } while (opcaoEstrutura != 0);

    printf("\nEncerrando o sistema... boa sorte na fuga! 👋\n");
    return 0;
}

/* Inserir item em vetor */
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
    if (scanf("%d", &novo.quantidade) != 1) { while (getchar() != '\n'); novo.quantidade = 1; }
    getchar();
    mochila[*qtd] = novo;
    (*qtd)++;
    printf("\nItem inserido!\n");
}

/* Remover item do vetor por nome */
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

/* Listar itens em vetor */
void listarItensVetor(Item mochila[], int qtd) {
    if (qtd == 0) {
        printf("\nMochila vazia!\n");
        return;
    }
    printf("\n--- Itens na Mochila (Vetor) ---\n");
    for (int i = 0; i < qtd; i++)
        printf("%d. %s | %s | %d\n", i + 1, mochila[i].nome, mochila[i].tipo, mochila[i].quantidade);
}

/* Ordenar vetor de itens por nome (bubble) */
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

/* Busca sequencial no vetor de itens */
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

/* Busca binária no vetor de itens (por nome) */
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

/* Inserir item em lista encadeada (no início) */
No* inserirItemLista(No *inicio) {
    No *novo = (No*) malloc(sizeof(No));
    if (!novo) {
        printf("\nErro de memoria!\n");
        return inicio;
    }
    printf("\nNome: ");
    fgets(novo->dados.nome, sizeof(novo->dados.nome), stdin);
    novo->dados.nome[strcspn(novo->dados.nome, "\n")] = '\0';
    printf("Tipo: ");
    fgets(novo->dados.tipo, sizeof(novo->dados.tipo), stdin);
    novo->dados.tipo[strcspn(novo->dados.tipo, "\n")] = '\0';
    printf("Quantidade: ");
    if (scanf("%d", &novo->dados.quantidade) != 1) { while (getchar() != '\n'); novo->dados.quantidade = 1; }
    getchar();

    novo->proximo = inicio;
    inicio = novo;
    printf("\nItem inserido na lista!\n");
    return inicio;
}

/* Remover item da lista por nome */
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

/* Listar itens da lista encadeada */
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

/* Busca sequencial na lista encadeada */
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

/* Cadastrar componentes (até MAX_COMPONENTES) */
void cadastrarComponentes(Componente comps[], int *n) {
    int opc;
    do {
        if (*n >= MAX_COMPONENTES) {
            printf("\nLimite de componentes atingido (%d).\n", MAX_COMPONENTES);
            return;
        }
        printf("\n--- Cadastro de Componente (%d/%d) ---\n", *n + 1, MAX_COMPONENTES);
        printf("Nome: ");
        fgets(comps[*n].nome, sizeof(comps[*n].nome), stdin);
        comps[*n].nome[strcspn(comps[*n].nome, "\n")] = '\0';
        printf("Tipo (ex: controle/suporte/propulsao): ");
        fgets(comps[*n].tipo, sizeof(comps[*n].tipo), stdin);
        comps[*n].tipo[strcspn(comps[*n].tipo, "\n")] = '\0';
        do {
            printf("Prioridade (1-10): ");
            if (scanf("%d", &comps[*n].prioridade) != 1) {
                while (getchar() != '\n');
                comps[*n].prioridade = -1;
            }
            getchar();
        } while (comps[*n].prioridade < 1 || comps[*n].prioridade > 10);
        (*n)++;
        printf("\nComponente cadastrado!\n");
        if (*n < MAX_COMPONENTES) {
            printf("Deseja cadastrar mais? 1-Sim / 0-Nao: ");
            if (scanf("%d", &opc) != 1) { while (getchar() != '\n'); opc = 0; }
            getchar();
        } else {
            opc = 0;
        }
    } while (opc != 0);
}

/* Mostrar lista de componentes */
void mostrarComponentes(Componente comps[], int n) {
    if (n == 0) {
        printf("\nNenhum componente cadastrado.\n");
        return;
    }
    printf("\n--- Componentes (%d) ---\n", n);
    for (int i = 0; i < n; i++) {
        printf("%d. %s | %s | %d\n", i + 1, comps[i].nome, comps[i].tipo, comps[i].prioridade);
    }
}

/* Bubble Sort por nome (conta comparações e mede tempo) */
void bubbleSortNome(Componente comps[], int n, long *comparacoes, double *tempo) {
    *comparacoes = 0;
    clock_t start = clock();
    for (int i = 0; i < n - 1; i++) {
        for (int j = 0; j < n - i - 1; j++) {
            (*comparacoes)++;
            if (strcmp(comps[j].nome, comps[j + 1].nome) > 0) {
                Componente tmp = comps[j];
                comps[j] = comps[j + 1];
                comps[j + 1] = tmp;
            }
        }
    }
    clock_t end = clock();
    *tempo = (double)(end - start) / CLOCKS_PER_SEC;
    printf("\nComponentes ordenados por NOME (Bubble Sort).\n");
}

/* Insertion Sort por tipo (conta comparações e mede tempo) */
void insertionSortTipo(Componente comps[], int n, long *comparacoes, double *tempo) {
    *comparacoes = 0;
    clock_t start = clock();
    for (int i = 1; i < n; i++) {
        Componente key = comps[i];
        int j = i - 1;
        while (j >= 0) {
            (*comparacoes)++;
            if (strcmp(comps[j].tipo, key.tipo) > 0) {
                comps[j + 1] = comps[j];
                j--;
            } else {
                break;
            }
        }
        comps[j + 1] = key;
    }
    clock_t end = clock();
    *tempo = (double)(end - start) / CLOCKS_PER_SEC;
    printf("\nComponentes ordenados por TIPO (Insertion Sort).\n");
}

/* Selection Sort por prioridade (conta comparações e mede tempo) */
void selectionSortPrioridade(Componente comps[], int n, long *comparacoes, double *tempo) {
    *comparacoes = 0;
    clock_t start = clock();
    for (int i = 0; i < n - 1; i++) {
        int min_idx = i;
        for (int j = i + 1; j < n; j++) {
            (*comparacoes)++;
            if (comps[j].prioridade < comps[min_idx].prioridade) {
                min_idx = j;
            }
        }
        if (min_idx != i) {
            Componente tmp = comps[i];
            comps[i] = comps[min_idx];
            comps[min_idx] = tmp;
        }
    }
    clock_t end = clock();
    *tempo = (double)(end - start) / CLOCKS_PER_SEC;
    printf("\nComponentes ordenados por PRIORIDADE (Selection Sort).\n");
}

/* Busca binária por nome (assume vetor ordenado por nome) */
int buscaBinariaPorNome(Componente comps[], int n, char chave[], long *comparacoes) {
    int inicio = 0, fim = n - 1;
    *comparacoes = 0;
    while (inicio <= fim) {
        int meio = (inicio + fim) / 2;
        (*comparacoes)++;
        int cmp = strcmp(comps[meio].nome, chave);
        if (cmp == 0) return meio;
        else if (cmp < 0) inicio = meio + 1;
        else fim = meio - 1;
    }
    return -1;
}
