#include <stdio.h>
#include <stdlib.h>
#include "CUnit/Basic.h"
#define MAX_LINE_LEN 128

void multiply_matrix(FILE* A, FILE* B, FILE* C, int col_A, int row_B, int row_A, int col_B, int offset_1, int offset_2){
   int res = 0;
   for(int i = 0; i < row_A; i++){
       for(int j = 0; j < col_B; j++){
           res = 0;
           for(int k = 0; k < col_A; k++){
               res += read(A, i * col_A + k) * read(B, k * (col_B + offset_1) + j + offset_2); 
           }
           fprintf(C, "%i ", res);
       }
      fprintf(C, "%c", '\n');
   }
}

void get_dim(FILE* file, int* col, int* row){
    char* first_line = NULL;
    size_t size = MAX_LINE_LEN;
    (*col) = 0;
    (*row) = 1;
    int r_val = getline(&first_line, &size, file);
    if(r_val == -1){
        free(first_line);
        return;
    }
    int i = 0;
    int j = 0;

    while(*(first_line + i) == 32){ //strip off leading spaces
        i++;
    }

    while(*(first_line + i) != '\0') {
        if(*(first_line + i) == ' ' && (*(first_line + i + 1) != ' ' && *(first_line + i + 1) != '\0' && *(first_line + i + 1) != '\n')){
            (*col)++;
        }
        i++;
    }

    (*col)++;

    while(getline(&first_line, &size, file) != -1) {
        (*row)++;
    }

    free(first_line);
}

void get_dim_test() {
    FILE* file_1;
    FILE* file_2;
    file_1 = fopen("./test_files/test1.txt", "r"); 
    file_2 = fopen("./test_files/test2.txt", "r"); 

    int col_1, col_2, row_1, row_2;

    get_dim(file_1, &col_1, &row_1);
    get_dim(file_2, &col_2, &row_2);

    CU_ASSERT_EQUAL(col_1, 5);
    CU_ASSERT_EQUAL(row_1, 3);
    CU_ASSERT_EQUAL(col_2, 3);
    CU_ASSERT_EQUAL(row_2, 5);

    fclose(file_1);
    fclose(file_2);
}

void multiply_matrix_test(){
  FILE* A;
  FILE* B;
  FILE* C;
  A = fopen("./test_files/test1.txt", "r");
  B = fopen("./test_files/test2.txt", "r");
  C = fopen("./test_files/test3.txt", "w");

  multiply_matrix(A, B, C, 5, 5, 3, 3, 0, 0);

  fclose(C);
  C = fopen("./test_files/test3.txt", "r");  
  FILE* RES;
  RES = fopen("./test_files/result.txt", "r");

  char* RES_buf = NULL;
  char* C_buf = NULL;
  size_t RES_size = MAX_LINE_LEN;
  size_t C_size = MAX_LINE_LEN;

  while(getline(&RES_buf, &RES_size, RES) != -1 && getline(&C_buf, &C_size, C) != -1) {
    CU_ASSERT_STRING_EQUAL(C_buf, RES_buf);
  }

  free(RES_buf);
  free(C_buf);
  fclose(A);
  fclose(B);
  fclose(C);
  fclose(RES);
}

int main()
{
  CU_pSuite pSuite = NULL;

  if (CUE_SUCCESS != CU_initialize_registry())
    return CU_get_error();

  pSuite = CU_add_suite("matrix multiplication tests", 0, 0);

  if (NULL == pSuite)
  {
    CU_cleanup_registry();
    return CU_get_error();
  }

  if (NULL == CU_add_test(pSuite, "multiply_matrix_test", multiply_matrix_test))
  {
    CU_cleanup_registry();
    return CU_get_error();
  }

  if (NULL == CU_add_test(pSuite, "get_dim_test", get_dim_test))
  {
    CU_cleanup_registry();
    return CU_get_error();
  }

  CU_basic_set_mode(CU_BRM_VERBOSE);

  CU_basic_run_tests();
  return CU_get_error();
}