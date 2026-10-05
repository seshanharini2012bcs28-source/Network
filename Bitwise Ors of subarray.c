#include <stdlib.h>

int compareInts(const void* a, const void* b) {
    int valA = *(const int*)a;
    int valB = *(const int*)b;
    if (valA < valB) return -1;
    if (valA > valB) return 1;
    return 0;
}

int subarrayBitwiseORs(int* arr, int arrSize) {
    
    int* s = (int*)malloc(32 * arrSize * sizeof(int));
    int sSize = 0;
    
    int l = 0; 
    
    for (int i = 0; i < arrSize; i++) {
        int a = arr[i];
        int r = sSize; 
        s[sSize++] = a;
        
      
        for (int j = l; j < r; j++) {
            int newOr = s[j] | a;
           
            if (s[sSize - 1] != newOr) {
                s[sSize++] = newOr;
            }
        }
        
       
        l = r;
    }
    
   
    qsort(s, sSize, sizeof(int), compareInts);
    
    int uniqueCount = 0;
    if (sSize > 0) {
        uniqueCount = 1;
        for (int i = 1; i < sSize; i++) {
            if (s[i] != s[i - 1]) {
                uniqueCount++;
            }
        }
    }
    
    free(s);
    return uniqueCount;
}
