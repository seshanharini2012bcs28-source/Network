#include <string.h>

#define INF 1e9

int networkDelayTime(int** times, int timesSize, int* timesColSize, int n, int k) {
    int graph[101][101];
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= n; j++) {
            graph[i][j] = INF;
        }
    }
    
    for (int i = 0; i < timesSize; i++) {
        int u = times[i][0];
        int v = times[i][1];
        int w = times[i][2];
        graph[u][v] = w;
    }
    
    
    int dist[101];
    int visited[101];
    for (int i = 1; i <= n; i++) {
        dist[i] = INF;
        visited[i] = 0;
    }
    
    dist[k] = 0;
    

    for (int count = 0; count < n; count++) {
        int min_node = -1;
        int min_dist = INF;
        
        for (int i = 1; i <= n; i++) {
            if (!visited[i] && dist[i] < min_dist) {
                min_dist = dist[i];
                min_node = i;
            }
        }
        
        if (min_node == -1) break;
        
        visited[min_node] = 1;
        
        for (int i = 1; i <= n; i++) {
            if (graph[min_node][i] != INF) {
                if (dist[min_node] + graph[min_node][i] < dist[i]) {
                    dist[i] = dist[min_node] + graph[min_node][i];
                }
            }
        }
    }
    
    int max_time = 0;
    for (int i = 1; i <= n; i++) {
        if (dist[i] == INF) {
            return -1;
        }
        if (dist[i] > max_time) {
            max_time = dist[i];
        }
    }
    
    return max_time;
}
