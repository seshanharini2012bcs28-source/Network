#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <math.h>
#include <string.h>


typedef struct {
    int r;
    int c;
} Point;


bool canReachDestination(int** heights, int rows, int* heightsColSize, int maxEffort) {
    int cols = heightsColSize[0];
    
    bool** visited = (bool**)malloc(rows * sizeof(bool*));
    for (int i = 0; i < rows; i++) {
        visited[i] = (bool*)calloc(cols, sizeof(bool));
    }
   
    Point* queue = (Point*)malloc(rows * cols * sizeof(Point));
    int head = 0, tail = 0;
   
    queue[tail++] = (Point){0, 0};
    visited[0][0] = true;
    
    
    int dr[] = {-1, 1, 0, 0};
    int dc[] = {0, 0, -1, 1};
    
    bool reached = false;
    
    while (head < tail) {
        Point curr = queue[head++];
        
       
        if (curr.r == rows - 1 && curr.c == cols - 1) {
            reached = true;
            break;
        }
        
        
        for (int i = 0; i < 4; i++) {
            int nr = curr.r + dr[i];
            int nc = curr.c + dc[i];
            
          
            if (nr >= 0 && nr < rows && nc >= 0 && nc < cols && !visited[nr][nc]) {
                
                int effort = abs(heights[curr.r][curr.c] - heights[nr][nc]);
                if (effort <= maxEffort) {
                    visited[nr][nc] = true;
                    queue[tail++] = (Point){nr, nc};
                }
            }
        }
    }
    
   
    for (int i = 0; i < rows; i++) {
        free(visited[i]);
    }
    free(visited);
    free(queue);
    
    return reached;
}

int minimumEffortPath(int** heights, int heightsSize, int* heightsColSize) {
    int low = 0;
    int high = 1000000;
    int ans = high;
    
    
    while (low <= high) {
        int mid = low + (high - low) / 2;
        
        if (canReachDestination(heights, heightsSize, heightsColSize, mid)) {
            ans = mid;       
            high = mid - 1;
        } else {
            low = mid + 1;  
        }
    }
    
    return ans;
}
