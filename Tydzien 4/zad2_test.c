#include "CUnit/Basic.h"
#include "functions.c"

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

  multiply_matrix(A, B, C, 5, 5, 3, 3);

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