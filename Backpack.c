#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

// -------------------------------------------
// Definição da struct Componente
// Cada componente possui:
// - nome: nome do item
// - tipo: tipo do item (controle, suporte, propulsão, etc.)
// - prioridade: prioridade de 1 a 10
// -------------------------------------------
typedef struct {
    char nome[30];
    char tipo[20];
    int prioridade;
} Componente;

// -------------------------------------------
// Função: mostrarComponentes
// Mostra todos os componentes cadastrados
// -------------------------------------------
void mostrarComponentes(Componente comps[], int n) {
    printf("\n%-30s %-20s %-10s\n", "NOME", "TIPO", "PRIORIDADE");
    printf("-------------------------------------------------------------\n");
    for(int i = 0; i < n; i++) {
        printf("%-30s %-20s %-10d\n", comps[i].nome, comps[i].tipo, comps[i].prioridade);
    }
    printf("\n");
}

// -------------------------------------------
// Bubble Sort por nome
// Ordena o vetor de componentes por ordem alfabética do nome
// contagem de comparações é retornada via ponteiro comparacoes
// -------------------------------------------
void bubbleSortNome(Componente comps[], int n, int *comparacoes) {
    *comparacoes = 0; // zerar contador
    for(int i = 0; i < n-1; i++) {
        for(int j = 0; j < n-i-1; j++) {
            (*comparacoes)++;
            if(strcmp(comps[j].nome, comps[j+1].nome) > 0) {
                // Troca os componentes se estiverem fora de ordem
                Componente temp = comps[j];
                comps[j] = comps[j+1];
                comps[j+1] = temp;
            }
        }
    }
}

// -------------------------------------------
// Insertion Sort por tipo
// Ordena o vetor de componentes por tipo (string)
// contagem de comparações é retornada via ponteiro comparacoes
// -------------------------------------------
void insertionSortTipo(Componente comps[], int n, int *comparacoes) {
    *comparacoes = 0;
    for(int i = 1; i < n; i++) {
        Componente key = comps[i];
        int j = i - 1;
        // Move os elementos maiores que a chave para a direita
        while(j >= 0 && (++(*comparacoes), strcmp(comps[j].tipo, key.tipo) > 0)) {
            comps[j+1] = comps[j];
            j--;
        }
        comps[j+1] = key;
    }
}

// -------------------------------------------
// Selection Sort por prioridade
// Ordena o vetor de componentes por prioridade (int)
// contagem de comparações é retornada via ponteiro comparacoes
// -------------------------------------------
void selectionSortPrioridade(Componente comps[], int n, int *comparacoes) {
    *comparacoes = 0;
    for(int i = 0; i < n-1; i++) {
        int min_idx = i;
        for(int j = i+1; j < n; j++) {
            (*comparacoes)++;
            if(comps[j].prioridade < comps[min_idx].prioridade) {
                min_idx = j;
            }
        }
        // Troca o menor encontrado com a posição i
        if(min_idx != i) {
            Componente temp = comps[i];
            comps[i] = comps[min_idx];
            comps[min_idx] = temp;
        }
    }
}

// -------------------------------------------
// Busca binária por nome
// Retorna a posição do componente ou -1 se não encontrado
// contagem de comparações é retornada via ponteiro comparacoes
// -------------------------------------------
int buscaBinariaPorNome(Componente comps[], int n, char chave[], int *comparacoes) {
    int inicio = 0;
    int fim = n - 1;
    *comparacoes = 0;
    while(inicio <= fim) {
        int meio = (inicio + fim)/2;
        (*comparacoes)++;
        int cmp = strcmp(chave, comps[meio].nome);
        if(cmp == 0) return meio; // componente encontrado
        else if(cmp < 0) fim = meio -1; // procurar na metade inferior
        else inicio = meio +1; // procurar na metade superior
    }
    return -1; // não encontrado
}

// -------------------------------------------
// Função principal
// Menu interativo para cadastro, ordenação, busca e exibição
// -------------------------------------------
int main() {
    Componente componentes[20]; // vetor com capacidade para 20 componentes
    int n = 0; // número atual de componentes cadastrados
    int escolha; // variável para escolha do menu
    srand(time(NULL)); // inicializa gerador de números aleatórios (se necessário)

    do {
        // Menu principal
        printf("\n--- MONTAGEM DA TORRE DE FUGA ---\n");
        printf("1 - Cadastrar componentes\n");
        printf("2 - Bubble Sort por nome\n");
        printf("3 - Insertion Sort por tipo\n");
        printf("4 - Selection Sort por prioridade\n");
        printf("5 - Busca binaria por nome (após Bubble Sort)\n");
        printf("6 - Mostrar componentes\n");
        printf("0 - Sair\n");
        printf("Escolha uma opcao: ");
        scanf("%d", &escolha);
        getchar(); // limpar '\n' do buffer

        switch(escolha) {

            // Cadastro de componentes
            case 1:
                if(n >= 20) {
                    printf("Capacidade maxima atingida.\n");
                    break;
                }
                printf("Quantos componentes deseja cadastrar? (1 a %d): ", 20 - n);
                int qtd;
                scanf("%d", &qtd);
                getchar(); // limpar '\n'
                if(qtd < 1 || qtd > 20-n) {
                    printf("Quantidade invalida.\n");
                    break;
                }
                for(int i = 0; i < qtd; i++) {
                    printf("\nComponente %d\n", n+1);
                    printf("Nome: ");
                    fgets(componentes[n].nome, sizeof(componentes[n].nome), stdin);
                    componentes[n].nome[strcspn(componentes[n].nome, "\n")] = 0; // remove \n
                    printf("Tipo: ");
                    fgets(componentes[n].tipo, sizeof(componentes[n].tipo), stdin);
                    componentes[n].tipo[strcspn(componentes[n].tipo, "\n")] = 0;
                    printf("Prioridade (1 a 10): ");
                    scanf("%d", &componentes[n].prioridade);
                    getchar();
                    n++;
                }
                break;

            // Bubble Sort por nome
            case 2: {
                int comp = 0;
                clock_t inicio = clock();
                bubbleSortNome(componentes, n, &comp);
                clock_t fim = clock();
                printf("\nComponentes ordenados por nome (Bubble Sort):\n");
                mostrarComponentes(componentes, n);
                printf("Comparacoes realizadas: %d\n", comp);
                printf("Tempo de execucao: %.6f segundos\n", (double)(fim-inicio)/CLOCKS_PER_SEC);
                break;
            }

            // Insertion Sort por tipo
            case 3: {
                int comp = 0;
                clock_t inicio = clock();
                insertionSortTipo(componentes, n, &comp);
                clock_t fim = clock();
                printf("\nComponentes ordenados por tipo (Insertion Sort):\n");
                mostrarComponentes(componentes, n);
                printf("Comparacoes realizadas: %d\n", comp);
                printf("Tempo de execucao: %.6f segundos\n", (double)(fim-inicio)/CLOCKS_PER_SEC);
                break;
            }

            // Selection Sort por prioridade
            case 4: {
                int comp = 0;
                clock_t inicio = clock();
                selectionSortPrioridade(componentes, n, &comp);
                clock_t fim = clock();
                printf("\nComponentes ordenados por prioridade (Selection Sort):\n");
                mostrarComponentes(componentes, n);
                printf("Comparacoes realizadas: %d\n", comp);
                printf("Tempo de execucao: %.6f segundos\n", (double)(fim-inicio)/CLOCKS_PER_SEC);
                break;
            }

            // Busca binária por nome
            case 5: {
                if(n == 0) {
                    printf("Nenhum componente cadastrado.\n");
                    break;
                }
                char chave[30];
                printf("Digite o nome do componente para buscar: ");
                fgets(chave, sizeof(chave), stdin);
                chave[strcspn(chave, "\n")] = 0; // remove \n
                int comp = 0;
                int pos = buscaBinariaPorNome(componentes, n, chave, &comp);
                if(pos != -1) {
                    printf("Componente encontrado na posicao %d:\n", pos+1);
                    printf("Nome: %s\nTipo: %s\nPrioridade: %d\n", 
                        componentes[pos].nome, componentes[pos].tipo, componentes[pos].prioridade);
                } else {
                    printf("Componente nao encontrado.\n");
                }
                printf("Comparacoes realizadas: %d\n", comp);
                break;
            }

            // Mostrar todos os componentes
            case 6:
                if(n == 0) printf("Nenhum componente cadastrado.\n");
                else mostrarComponentes(componentes, n);
                break;

            case 0:
                printf("Encerrando o programa.\n");
                break;

            default:
                printf("Opcao invalida.\n");
        }

    } while(escolha != 0);

    return 0;
}
