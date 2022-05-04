#include "functions.c"

int main(int argc, char** argv) {
    FILE* lista;
    int mode;

    if(argc != 3) {
        printf("Invalid number of args");
        return 1;
    }
    else{
        lista = fopen(argv[1], "r");
        mode = stoi(argv[2]);
    }

    char* f1 = calloc(MAX_LINE_LEN, sizeof(char));
    char* f2 = calloc(MAX_LINE_LEN, sizeof(char));
    char* f3 = calloc(MAX_LINE_LEN, sizeof(char));

    while(fscanf(lista, "%s %s %s", f1, f2, f3) > 0) {
        FILE* file_A;
        FILE* file_B;
        FILE* file_C;
        file_A = fopen(f1, "r");
        file_B = fopen(f2, "r");

        int col_A = 0, col_B = 0, row_A = 0, row_B = 0;
        get_dim(file_A, &col_A, &row_A);
        get_dim(file_B, &col_B, &row_B);

        if(col_A != row_B){
            printf("Cannot multiply matrices - mismatching dimensions.");
            fclose(file_A);
            fclose(file_B);
            fclose(file_C);
            return 1;
        }

        int tmp = col_B;
        int k = col_B / 2;
        int offset_1 = 0;
        int offset_2 = 0;
        if(mode == 1) {
            file_C = fopen(f3, "r+");
            if(file_C == NULL) {
                file_C = fopen(f3, "w");
                flock(file_C->_fileno, LOCK_EX);
                if(tmp & 1) {
                offset_1 = k * 2;
                }
                else offset_1 = k;
                multiply_and_fill_matrix(file_A, file_B, file_C, col_A, row_B, row_A, col_B, offset_1, offset_2);
                flock(file_C->_fileno, LOCK_UN);
            }
            else {
                int fd = file_C->_fileno;
                flock(fd, LOCK_EX);
                if(tmp & 1) {
                    offset_1 = k * 2;
                }
                else offset_1 = k;
                multiply_matrix(file_A, file_B, file_C, col_A, row_B, row_A, k, offset_1, offset_2);
                flock(fd, LOCK_UN);
            }
        }
        else {
            offset_1 = k;
            offset_2 = k;
            file_C = fopen(f3, "r+");
            if(file_C == NULL) {
                file_C = fopen(f3, "w");
                flock(file_C->_fileno, LOCK_EX);
                multiply_and_fill_matrix(file_A, file_B, file_C, col_A, row_B, row_A, col_B, offset_1, offset_2);
                flock(file_C->_fileno, LOCK_UN);
            }
            else {
                int fd = file_C->_fileno;
                flock(fd, LOCK_EX);
                multiply_matrix(file_A, file_B, file_C, col_A, row_B, row_A, col_B, offset_1, offset_2); 
                flock(fd, LOCK_UN);
            }
        }

        fclose(file_A);
        fclose(file_B);
        fclose(file_C);
    }

    free(f1);
    free(f2);
    free(f3);
    fclose(lista);

    return 0;
}