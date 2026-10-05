#include <string.h>
#include <stdlib.h>

char* addBinary(char* a, char* b) {
    int len_a = strlen(a);
    int len_b = strlen(b);
    
    
    int max_len = (len_a > len_b ? len_a : len_b);
    char* result = (char*)malloc((max_len + 2) * sizeof(char));
    
    int i = len_a - 1;
    int j = len_b - 1;
    int carry = 0;
    int k = max_len + 1; 
    
    result[k--] = '\0'; 
    
    
    while (i >= 0 || j >= 0 || carry > 0) {
        int sum = carry;
        
        if (i >= 0) {
            sum += a[i--] - '0';
        }
        if (j >= 0) {
            sum += b[j--] - '0';
        }
        
        carry = sum / 2;      
        result[k--] = (sum % 2) + '0';
    }
    
  
    return &result[k + 1];
}
