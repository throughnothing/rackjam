#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void print_table(float** table, int size){
    int i,j;
    for(i = 0; i < size; i++){
        printf("[");
        for(j = 0; j < size; j++){
            printf("%f,", table[i][j]);
        }
        printf("]\n");
    }
}

float max(float a, float b){ return a > b ? a : b; }

char *trim(char* str){
    int len = strlen(str), i = 0, end = 0;
    int altered = 0;
    if(str[len-1] == ' '){ altered = 1; str[len-1] = '\0'; }
    if(str[0] == ' '){ altered = 1; str = &str[1]; }
    return (altered == 0) ? str : trim(str);
}

char *get_path(float **next, int i, int j){
    int m = next[i][j], len;
    char str[200];
    char *reval, *p, *n;

    if(m == -1){ return "";}

    p = get_path(next, i, m); 
    n = get_path(next, m, j);
    sprintf(str, "%s %i %s", p, m, n);
    /*free(p); free(n);*/

    len = strlen(str);
    reval = (char*)malloc(sizeof(char) * (len+1));
    strcpy(reval, str);
    return reval;
}

void solve(float **table, int size){
    int i, j, k, max = 0, brk = 0;
    float **next;
    next = calloc(size, sizeof(int *));
    for(i = 0; i < size; i++){ 
        next[i] = calloc(size, sizeof(int));
        for(j = 0; j < size; j++){ next[i][j] = -1; }
    }

    for (k = 0; k < size; k++){
        for (i = 0; i < size; i++){
            for (j = 0; j < size; j++){
                float val = table[i][k] * table[k][j];
                if ( val > table[i][j]){
                    table[i][j] = val;
                    next[i][j] = k;
                }
            }
        }
        for (i = 0; i < size; i++){
            if (table[i][i] >= 1.01){ brk = 1; }
        }

        if(brk) { break; }
    }
    if(brk){
        for(i = 0; i < size; i++){max = (table[i][i] > table[max][max])?i:max;}
        printf("%i %s %i\n", max + 1, get_path(next, max, max), max + 1);
    }else{
        printf("no arbitrage sequence exists\n");
    }
}

float **build_table(int n){
    float **table;
    int i=0, j=0;

    table = calloc(n, sizeof(float *));
    for(i = 0; i < n; i++){ table[i] = calloc(n, sizeof(float)); }

    for(i = 0; i < n; i++){
        for(j = 0; j < n; j++){
            if(i != j){ scanf("%f", &table[i][j]); }
            else { table[i][j] = 1.0; }
        }
    }
    return table;
}

int main(int argc, char* argv[]){
    int n;
    float **table;
    
    while(scanf("%d", &n) != -1){
        table = build_table(n);
        solve(table, n);
    }
    return 0;
}
