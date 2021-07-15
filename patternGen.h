/* Diogo Paris Kraut - GRR 20166365 */

typedef struct LP_t {
	int machine_count;
	int pair_count;
	int *orders;
	int *order_quants;
	int max_time;
	int *solutions;
	int sol_count;
	int max_sols;
} LP_t;

LP_t *initLP(FILE *fp);
int ValidCombinations(LP_t *lp, int j, int *sol);
void StoreSolution(LP_t *lp, int *sol);
void print_sols(LP_t *lp);
void print_sol(LP_t *lp, int *sol);
void realloc_solutions(LP_t *lp);
void freeLP(LP_t *lp);