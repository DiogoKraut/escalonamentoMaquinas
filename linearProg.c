/* Diogo Paris Kraut - GRR 20166365 */

#include <stdio.h>
#include <stdlib.h>
#include "patternGen.h"

void quickSort(int* arr, int *arr2, int low, int high);

void printObjFunction(LP_t *lp) {
    printf("min:");
    for(int i = 0; i < lp->sol_count; i ++)
        printf(" +x%d", i);
    printf(";\n");
}

void printConstraints(LP_t *lp) {
    int i, j;
    // patterns contraints
    for(i = 0; i < lp->sol_count; i++) {
        printf("pattern_%1$02d: x%1$-2d =", i);
        for (j = 0; j < lp->pair_count; j++) {
            // the index of 'x' is its index in the solution matrix + an offset
            // from the extra variables needed to name each pattern
            if(lp->solutions[i * lp->pair_count + j] > 0)
                printf(" +%-2d %3d", lp->solutions[i * lp->pair_count + j], lp->orders[j]);
        }
        printf(";\n");
    }

    // requirement fulfillment constraints
    for(i = 0; i < lp->pair_count; i++) {
        for(j = 0; j < lp->sol_count; j++) {
            if(lp->solutions[j * lp->pair_count + i] > 0)
                printf("+%d x%d ", lp->solutions[j * lp->pair_count + i], j);
        }
        printf(">= %d;\n", lp->order_quants[i]);
    }

    // variables are non-negative
    for(i = 0; i < lp->sol_count; i++) {
        printf("x%d >= 0;\n", i);
    }
}

int main(int argc, char const *argv[]){
    /* INPUT */
    FILE *fp;
    if(argc == 2)
        fp = fopen(argv[1], "r");
    else
        fp = stdin;

    if(!fp) {
        printf("fopen err\n");
        exit(1);
    }

    /* INITIALIZATION */
    LP_t *lp = initLP(fp);
    int *sol_aux = calloc(lp->pair_count, sizeof(int));

    // Sort times array. Maintains parity between members of orders and order_quants
    quickSort(lp->orders, lp->order_quants, 0, lp->pair_count - 1);

    /* GENERATE PATTERNS */
    ValidCombinations(lp, 0, sol_aux);
    // printf("Solutions:\n");
    // print_sols(lp);

    /* FORMAT OUTPUT FOR USE IN lp_solve */
    printObjFunction(lp);

    printConstraints(lp);

    freeLP(lp);
    return 0;
}