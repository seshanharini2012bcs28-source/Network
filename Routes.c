#include <stdio.h>
#include <stdlib.h>

typedef struct Edge {
    int to;         
    struct Edge* next;
} Edge;

void dfs(int node, Edge** graph, int* visited, int* reorderCount) {
    visited[node] = 1;
    
    Edge* curr = graph[node];
    while (curr != NULL) {
        int neighbor = curr->to;
        int nextNode = abs(neighbor);
        
        
        if (!visited[nextNode]) {
           
            if (neighbor > 0) {
                (*reorderCount)++;
            }
           
            dfs(nextNode, graph, visited, reorderCount);
        }
        curr = curr->next;
    }
}

int minReorder(int n, int** connections, int connectionsSize, int* connectionsColSize) {
   
    Edge** graph = (Edge**)calloc(n, sizeof(Edge*));
    int* visited = (int*)calloc(n, sizeof(int));
    int reorderCount = 0;
    
    
    for (int i = 0; i < connectionsSize; i++) {
        int u = connections[i][0];
        int v = connections[i][1];
        
       
        Edge* edge1 = (Edge*)malloc(sizeof(Edge));
        edge1->to = v;
        edge1->next = graph[u];
        graph[u] = edge1;
       
        Edge* edge2 = (Edge*)malloc(sizeof(Edge));
        edge2->to = -u;
        edge2->next = graph[v];
        graph[v] = edge2;
    }
    
    
    dfs(0, graph, visited, &reorderCount);
    
   
    for (int i = 0; i < n; i++) {
        Edge* curr = graph[i];
        while (curr != NULL) {
            Edge* temp = curr;
            curr = curr->next;
            free(temp);
        }
    }
    free(graph);
    free(visited);
    
    return reorderCount;
}
