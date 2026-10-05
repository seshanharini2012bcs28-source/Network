#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define INF 1e9 

int findCheapestPrice(int n, int** flights, int flightsSize, int* flightsColSize, int src, int dst, int k) {
    
    int* dist = (int*)malloc(n * sizeof(int));
   
    int* temp = (int*)malloc(n * sizeof(int));
    
    
    for (int i = 0; i < n; i++) {
        dist[i] = INF;
    }
    dist[src] = 0;
    
    
    for (int i = 0; i <= k; i++) {
        
        memcpy(temp, dist, n * sizeof(int));
        
        for (int j = 0; j < flightsSize; j++) {
            int u = flights[j][0];
            int v = flights[j][1]; 
            int w = flights[j][2];
            
           
            if (temp[u] != INF) {
                
                if (temp[u] + w < dist[v]) {
                    dist[v] = temp[u] + w;
                }
            }
        }
    }
    
    int result = dist[dst];
    
    free(dist);
    free(temp);
    
    return result == INF ? -1 : result;
}
