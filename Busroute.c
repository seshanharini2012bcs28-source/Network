#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

#define MAX_STOP 1000000


typedef struct {
    int *buses;
    int size;
    int capacity;
} StopToBuses;


typedef struct {
    int bus;
    int depth;
} QueueElement;

int numBusesToDestination(int** routes, int routesSize, int* routesColSize, int source, int target) {
   
    if (source == target) {
        return 0;
    }

   
    StopToBuses* stopMap = (StopToBuses*)calloc(MAX_STOP, sizeof(StopToBuses));
    
   
    for (int i = 0; i < routesSize; i++) {
        for (int j = 0; j < routesColSize[i]; j++) {
            int stop = routes[i][j];
            if (stopMap[stop].buses == NULL) {
                stopMap[stop].capacity = 4;
                stopMap[stop].buses = (int*)malloc(stopMap[stop].capacity * sizeof(int));
                stopMap[stop].size = 0;
            }
            if (stopMap[stop].size >= stopMap[stop].capacity) {
                stopMap[stop].capacity *= 2;
                stopMap[stop].buses = (int*)realloc(stopMap[stop].buses, stopMap[stop].capacity * sizeof(int));
            }
            stopMap[stop].buses[stopMap[stop].size++] = i;
        }
    }

   
    bool* visitedBuses = (bool*)calloc(routesSize, sizeof(bool));
    bool* visitedStops = (bool*)calloc(MAX_STOP, sizeof(bool));

   
    QueueElement* queue = (QueueElement*)malloc(routesSize * sizeof(QueueElement));
    int head = 0;
    int tail = 0;

  
    visitedStops[source] = true;
    for (int i = 0; i < stopMap[source].size; i++) {
        int busIndex = stopMap[source].buses[i];
        if (!visitedBuses[busIndex]) {
            visitedBuses[busIndex] = true;
            queue[tail++] = (QueueElement){busIndex, 1};
        }
    }

    int result = -1;

   
    while (head < tail) {
        QueueElement current = queue[head++];
        int currBus = current.bus;
        int currentDepth = current.depth;

        
        bool foundTarget = false;
        for (int i = 0; i < routesColSize[currBus]; i++) {
            if (routes[currBus][i] == target) {
                result = currentDepth;
                foundTarget = true;
                break;
            }
        }

        if (foundTarget) {
            break;
        }

        
        for (int i = 0; i < routesColSize[currBus]; i++) {
            int nextStop = routes[currBus][i];
            if (visitedStops[nextStop]) continue;
            visitedStops[nextStop] = true;

            for (int j = 0; j < stopMap[nextStop].size; j++) {
                int nextBus = stopMap[nextStop].buses[j];
                if (!visitedBuses[nextBus]) {
                    visitedBuses[nextBus] = true;
                    queue[tail++] = (QueueElement){nextBus, currentDepth + 1};
                }
            }
        }
    }

   
    for (int i = 0; i < MAX_STOP; i++) {
        if (stopMap[i].buses != NULL) {
            free(stopMap[i].buses);
        }
    }
    free(stopMap);
    free(visitedBuses);
    free(visitedStops);
    free(queue);

    return result;
}
