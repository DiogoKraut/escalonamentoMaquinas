/* Diogo Paris Kraut - GRR 20166365 */

#include <stdlib.h>
#include <stdio.h>
#include "patternGen.h"

LP_t *initLP(FILE *fp) {
    int i;
    LP_t *lp = malloc(sizeof(LP_t));
    fscanf(fp, "%d %d", &lp->machine_count, &lp->pair_count);
    lp->max_time = 540 * lp->machine_count;
    lp->sol_count = 0;
    lp->max_sols = lp->pair_count;

    lp->solutions    = malloc(sizeof(int) * lp->pair_count * lp->pair_count);
    lp->orders       = malloc(sizeof(int) * lp->pair_count);
    lp->order_quants = malloc(sizeof(int) * lp->pair_count);
   
    for(i = 0; i < lp->pair_count; i++) {
        fscanf(fp, "%d %d", &lp->order_quants[i], &lp->orders[i]);
    }
    return lp;
}

void freeLP(LP_t *lp) {
    free(lp->solutions);
    free(lp->orders);
    free(lp->order_quants);
    free(lp);
}

void realloc_solutions(LP_t *lp) {
    lp->max_sols *= 3;
    int *aux = realloc(lp->solutions, sizeof(int) * (lp->max_sols * lp->pair_count));
    if(!aux) {
        fprintf(stderr, "Realloc err\n");
        exit(1);
    }
    lp->solutions = aux;
}

void print_sol(LP_t *lp, int *sol) {
    for(int j = 0; j < lp->pair_count; j++) {
        printf("%d ", sol[j]);
    }
    printf("\n");
}

void print_sols(LP_t *lp) {
    for(int i = 0; i < lp->sol_count; i++) {
        for(int j = 0; j < lp->pair_count; j++) {
            printf("%d ", lp->solutions[i * lp->pair_count +j]);
        }
        printf("\n");
    }
}

void StoreSolution(LP_t *lp, int *sol) {
    for(int i = 0; i < lp->pair_count; i++) {
        if(lp->sol_count == lp->max_sols) {
            realloc_solutions(lp);
        }
        lp->solutions[lp->sol_count * lp->pair_count + i] = sol[i];
    }
    lp->sol_count++;
}

int ValidCombinations(LP_t *lp, int j, int *sol) {

    /* Calculate total sum of current pattern */
    int sum = 0;
    for(int i = 0; i < lp->pair_count; i++)
        sum += sol[i]*lp->orders[i];

    if(sum > lp->max_time) { // sum exceeds max time of a machine-day
        return -1;
    }

    if(j >= lp->pair_count) { // reached leaf node
        return -2;
    }

    if(lp->max_time - sum < lp->orders[0]) { // leftover time is less than smallest order?
        StoreSolution(lp, sol);
        // print_sol(sol);
        return 0;
    }

    int end_of_branch = 0;
    /* Increase sol[j] if it hasnt reached its maximum value */
    if(sol[j] < lp->order_quants[j]) {
        sol[j]++;
        end_of_branch = ValidCombinations(lp, j, sol);
        sol[j]--;
    }
    /* Go down to every other sol index greater than j */
    while(end_of_branch >= 0) {
        j++;
        sol[j]++;
        end_of_branch = ValidCombinations(lp, j, sol);
        sol[j]--;
    }
    return 1;
}