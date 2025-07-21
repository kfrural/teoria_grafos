// hierholzer_gdb.c
#include <stdio.h>
#include <stdlib.h>

/* ---------- Estruturas ---------- */
typedef struct Edge Edge;
struct Edge { int to, id; Edge *next; };

Edge **adj      = NULL;   /* vetor de ponteiros p/ listas            */
int   *deg      = NULL;   /* grafo de cada vértice                    */
int   *vis_edge = NULL;   /* marca aresta já usada (tam = E)         */
int   *vis_v    = NULL;   /* vértices visitados p/ conectividade     */

/* ---------- Adiciona aresta u-v ---------- */
void add_edge(int u, int v, int id) {
    Edge *a = malloc(sizeof(Edge));
    a->to = v; a->id = id; a->next = adj[u]; adj[u] = a;

    Edge *b = malloc(sizeof(Edge));
    b->to = u; b->id = id; b->next = adj[v]; adj[v] = b;

    deg[u]++; deg[v]++;
}

/* ---------- DFS iterativa p/ conectividade ---------- */
void dfs(int start, int V) {
    int *stack = malloc(V * sizeof(int));
    int  top   = 0;
    stack[top++] = start;
    vis_v[start] = 1;

    while (top) {
        int u = stack[--top];
        for (Edge *e = adj[u]; e; e = e->next)
            if (!vis_v[e->to]) {
                vis_v[e->to] = 1;
                stack[top++] = e->to;
            }
    }
    free(stack);
}

/* ---------- Hierholzer ---------- */
int *ciclo = NULL, clen = 0;            /* ciclo reverso       */
int *S       = NULL, stop  = 0;           /* pilha do percurso      */

void hierholzer(int start, int E) {
    S[stop++] = start;
    while (stop) {
        int v = S[stop - 1];
        Edge *e;
        for(e = adj[v]; e && vis_edge[e->id]; e = e->next) ;
        if (e) {                          /* avança por aresta livre */
            vis_edge[e->id] = 1;
            S[stop++] = e->to;
        } else {                          /* sem arestas → registra */
            ciclo[clen++] = v;
            --stop;
        }
    }
}

/* ---------- Função para ler o arquivo de entrada ---------- */
int read_input(const char *filename, int *V, int *E) {
    FILE *file = fopen(filename, "r");
    if (!file) {
        fprintf(stderr, "Erro ao abrir arquivo '%s'\n", filename);
        return 0;
    }

    // Lê número de vértices e arestas
    if (fscanf(file, "%d %d", V, E) != 2) {
        fprintf(stderr, "Formato inválido no arquivo\n");
        fclose(file);
        return 0;
    }

    // Alocação dinâmica dos vetores
    adj      = calloc(*V, sizeof(Edge*));
    deg      = calloc(*V, sizeof(int));
    vis_v    = calloc(*V, sizeof(int));
    vis_edge = calloc(*E, sizeof(int));
    ciclo    = malloc((*E + 1) * sizeof(int));
    S        = malloc((*E + 1) * sizeof(int));

    // Lê as arestas
    int u, v, id;
    for(id = 0; id < *E; id++) {
        if (fscanf(file, "%d %d", &u, &v) != 2 || 
            u >= *V || v >= *V) {
            fprintf(stderr, "Formato inválido ou vértice fora do intervalo\n");
            fclose(file);
            return 0;
        }
        add_edge(u, v, id);
    }

    fclose(file);
    return 1;
}

int is_semi_euleriano(int V) {
    int impares = 0;
    int start = -1;
    
    for(int i = 0; i < V; ++i) {
        if (deg[i] & 1) {
            impares++;
        }
        if (deg[i]) start = i;
    }
    
    if (impares != 2) {
        return 0;
    }
    
    dfs(start, V);
    for(int i = 0; i < V; ++i) {
        if (deg[i] && !vis_v[i]) {
            return 0;
        }
    }
    
    return 1;
}

/* ---------- MAIN MODIFICADO PARA TESTE DIRETO ---------- */
int main() {
    int V, E;

    // Tenta ler os dados do arquivo
    if (!read_input("arquivo3.txt", &V, &E)) {
        printf("SEM CAMINHO\n");
        return 0;
    }

    if (!is_semi_euleriano(V)) {
        printf("Nao eh semi-euleriano\n");
        return 0;
    }

    int inicio = -1, fim = -1;
    for(int i = 0; i < V; ++i) {
        if (deg[i] & 1) {
            if (inicio == -1) inicio = i;
            else fim = i;
        }
    }

    // Executa Hierholzer a partir do vértice de início
    hierholzer(inicio, E);
    if (clen != E + 1) {
        printf("SEM CAMINHO\n");
        return 0;
    }

    // Imprime o caminho euleriano encontrado
    for(int i = clen - 1; i >= 0; --i)
        printf("%d%c", ciclo[i], i ? ' ' : '\n');

    return 0;
}
