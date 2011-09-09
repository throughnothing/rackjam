#include <stdio.h>
#include <stdlib.h>

float **build_table(int n, FILE *ifp){
    float f, **table;
    int i=0, j=0, k=0;

    table = malloc(n * sizeof(float *));
    for(k = 0; k < n; k++)
        table[k] = malloc(n * sizeof(float));

    for(i = 0; i < n; i++){
        for(j = 0; j < n; j++){
            if(i != j){
                fscanf(ifp, "%f", &f);
                table[i][j] = f;
            }else { table[i][j] = 1.0; }
        }
    }
    return table;
}

int main(int argc, char* argv[]){
    if(argc < 2){ fprintf(stderr, "Must give me a file!\n"); return 1; }

    int n;
    float **table;
    FILE *ifp;
    
    ifp = fopen(argv[1], "r");

    while(fscanf(ifp, "%d", &n) != -1){
        table = build_table(n, ifp);
    }
    
    fclose(ifp);
    return 0;
}
