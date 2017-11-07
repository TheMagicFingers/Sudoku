#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

/**
 * Esta struct especifica onde a thread deve começar a verificar.
 */
typedef struct
{
    // A linha de início.
    int row;
    // A coluna de início.
    int col;
    // O ponteiro para o board.
    int (* board)[9];
} parameters;

// Protótipo da função walk_rows.
void * walk_rows(void * params);

// Protótipo da função walk_cols.
void * walk_cols(void * params);

// Protótipo para os grids 3x3.
void * check_square(void * params);

// Protótipo p/ funcao de ler matriz
void p_matriz(int matriz[9][9]);

                                /********************
                                 * FUNÇÃO PRINCIPAL *
                                 ********************/
int main(void)
{

    // ====== Cria o "board" =======
    int i, j;
	int board[9][9];
	p_matriz(board);

    /*int board[9][9] = {
            {6, 2, 4, 5, 3, 9, 1, 8, 7},
            {5, 1, 9, 7, 2, 8, 6, 3, 4},
            {8, 3, 7, 6, 1, 4, 2, 9, 5},
            {1, 4, 3, 8, 6, 5, 7, 2, 9},
            {9, 5, 8, 2, 4, 7, 3, 6, 1},
            {7, 6, 2, 3, 9, 1, 4, 5, 8},
            {3, 7, 1, 9, 5, 6, 8, 4, 2},
            {4, 9, 6, 1, 8, 2, 5, 7, 3},
            {2, 8, 5, 4, 7, 3, 9, 1, 6}
        };*/

    // ====== Cria o parâmetro para checar as linhas e as colunas =======
    parameters * param0 = (parameters *) malloc(sizeof(parameters));
    param0->row = 0;
    param0->col = 0;
    param0->board = board;

    // ====== Cria os parâmetros para as threads do 3x3 ======

    // Primeiro 3x3
    parameters * param1 = (parameters *) malloc(sizeof(parameters));
    param1->row = 0;
    param1->col = 0;
    param1->board = board;

    // Segundo 3x3
    parameters * param2 = (parameters *) malloc(sizeof(parameters));
    param2->row = 0;
    param2->col = 3;
    param2->board = board;

    // Terceiro 3x3
    parameters * param3 = (parameters *) malloc(sizeof(parameters));
    param3->row = 0;
    param3->col = 6;
    param3->board = board;

    // Quarto 3x3
    parameters * param4 = (parameters *) malloc(sizeof(parameters));
    param4->row = 3;
    param4->col = 0;
    param4->board = board;

    // Quinto 3x3
    parameters * param5 = (parameters *) malloc(sizeof(parameters));
    param5->row = 3;
    param5->col = 3;
    param5->board = board;

    // Sexto 3x3
    parameters * param6 = (parameters *) malloc(sizeof(parameters));
    param6->row = 3;
    param6->col = 6;
    param6->board = board;

    // Sétimo 3x3
    parameters * param7 = (parameters *) malloc(sizeof(parameters));
    param7->row = 6;
    param7->col = 0;
    param7->board = board;

    // Oitavo 3x3
    parameters * param8 = (parameters *) malloc(sizeof(parameters));
    param8->row = 6;
    param8->col = 3;
    param8->board = board;

    // Nono 3x3
    parameters * param9 = (parameters *) malloc(sizeof(parameters));
    param9->row = 6;
    param9->col = 6;
    param9->board = board;

    // ====== Cria as threads ======
    pthread_t thread_rows, thread_cols, thread1, thread2, thread3, thread4, thread5, thread6, thread7, thread8, thread9;

    // ====== Cria os valores de retorno das threads ======
    void * all_rows;
    void * all_cols;
    void * square1;
    void * square2;
    void * square3;
    void * square4;
    void * square5;
    void * square6;
    void * square7;
    void * square8;
    void * square9;

    // ====== Inicializando as threads ======
    pthread_create(&thread_rows, NULL, walk_rows, (void *) param0);
    pthread_create(&thread_cols, NULL, walk_cols, (void *) param0);
    pthread_create(&thread1, NULL, check_square, (void *) param1);
    pthread_create(&thread2, NULL, check_square, (void *) param2);
    pthread_create(&thread3, NULL, check_square, (void *) param3);
    pthread_create(&thread4, NULL, check_square, (void *) param4);
    pthread_create(&thread5, NULL, check_square, (void *) param5);
    pthread_create(&thread6, NULL, check_square, (void *) param6);
    pthread_create(&thread7, NULL, check_square, (void *) param7);
    pthread_create(&thread8, NULL, check_square, (void *) param8);
    pthread_create(&thread9, NULL, check_square, (void *) param9);

    // ======= Join para as threads esperarem as outras terminarem suas tarefas =======
    pthread_join(thread_rows, &all_rows);
    pthread_join(thread_cols, &all_cols);
    pthread_join(thread1, &square1);
    pthread_join(thread2, &square2);
    pthread_join(thread3, &square3);
    pthread_join(thread4, &square4);
    pthread_join(thread5, &square5);
    pthread_join(thread6, &square6);
    pthread_join(thread7, &square7);
    pthread_join(thread8, &square8);
    pthread_join(thread9, &square9);

    FILE *file;
    file = fopen("resposta.txt","w");
    if(file == NULL){
        fprintf(file,"Arquivo nao encontrado.\n");
        exit(0);
    }

    // ====== Verifica se o Sudoku foi resolvido ======
    if (    (int) all_rows == 1 &&
            (int) all_cols == 1 &&
            (int) square1 == 1 &&
            (int) square2 == 1 &&
            (int) square3 == 1 &&
            (int) square4 == 1 &&
            (int) square5 == 1 &&
            (int) square6 == 1 &&
            (int) square7 == 1 &&
            (int) square8 == 1 &&
            (int) square9 == 1 ) {
        fprintf(file,"Parabéns, o Sudoku foi resolvido!\n");
    }
    else {
        fprintf(file,"Ops, tente novamente.\n");
    }
    fclose(file);
    return 0;
}

/**
 * Varifica se cada linha contém todos os digitos de 1-9.
 * @param   void *      The parameters (pointer).
 * @return  void *      1 se todas as linhas contêm os digítos 1-9, se não retorna 0.
 */
void * walk_rows(void * params) {
    parameters * data = (parameters *) params;
    int startRow = data->row;
    int startCol = data->col;
    int i,j;
    for (i = startRow; i < 9; ++i) {
        int row[10] = {0};
        for (j = startCol; j < 9; ++j) {
            int val = data->board[i][j];
            if (row[val] != 0) {
                return (void *) 0;
            }
            else{
                row[val] = 1;
            }
        }
    }
    return (void *) 1;
}

/**
 * Verifica se cada coluna contém os digitos de 1-9.
 * @param   void *      The parameters (pointer).
 * @return  void *      1 se todas as colunas contêm os digítos 1-9, se não retorna 0.
 */
void * walk_cols(void * params) {
    parameters * data = (parameters *) params;
    int startRow = data->row;
    int startCol = data->col;
    int i,j;
    for (i = startCol; i < 9; ++i) {
        int col[10] = {0};
        for (j = startRow; j < 9; ++j) {
            int val = data->board[j][i];
            if (col[val] != 0) {
                return (void *) 0;
            }
            else{
                col[val] = 1;
            }
        }
    }
    return (void *) 1;
}

/**
 * Checa se o 3x3 contém todos os números 1-9.
 * @param   void *      The parameters (pointer).
 * @return  void *      1 se tém os números 1-9, 0 caso contrário.
 */
void * check_square(void * params) {
    parameters * data = (parameters *) params;
    int startRow = data->row;
    int startCol = data->col;
    int saved[10] = {0};
    int i,j;
    for (i = startRow; i < startRow + 3; ++i) {
        for (j = startCol; j < startCol + 3; ++j) {
            int val = data->board[i][j];
            if (saved[val] != 0) {
                return (void *) 0;
            }
            else{
                saved[val] = 1;
            }
        }
    }
    return (void *) 1;
}

void p_matriz(int mat[9][9]){
	FILE *file;
	file = fopen("matriz.txt", "r");
    int i,j;

	for(i = 0; i < 9; i++){
		for(j = 0; j < 9; j++){
			fscanf(file, "%d", &mat[i][j]);
		}
	}
	fclose(file);
}
