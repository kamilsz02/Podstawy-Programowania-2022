#include "CUnit/Basic.h"
#include "zad2.c"
#define N 100

void getHexAscii_test()
{
    char* out = getHexAscii('(');  
    CU_ASSERT_STRING_EQUAL(out, "28");
    free(out);

    out = getHexAscii(')');  
    CU_ASSERT_STRING_EQUAL(out, "29");
    free(out);

    out = getHexAscii('%');  
    CU_ASSERT_STRING_EQUAL(out, "25");
    free(out);
}

void compress_test(){
    char** in = calloc(N, sizeof(char*));

    *(in) = "((((()  a h";
    char* out = compress(in, 1);
    CU_ASSERT_STRING_EQUAL(out, "%28(5)%29(1)  a h");

    *(in) = "((((aaaaaaaa     ))))) ";
    out = compress(in, 1);
    CU_ASSERT_STRING_EQUAL(out, "%28(4)a(8) (5)%29(5) ");

    *(in) = "aaaa kamil bbbbb";
    *(in + 1) = "((( )) %";
    out = compress(in, 2);
    CU_ASSERT_STRING_EQUAL(out, "aaaa kamil b(5)%28(3) %29(2) %25(1)");
    free(in);
    free(out);
    
}

void decompress_test(){
    char** in = calloc(N, sizeof(char*));

    *(in) = "%28(5)%29(1)  a h";
    char* out = decompress(in, 1);
    CU_ASSERT_STRING_EQUAL(out, "((((()  a h");

    *(in) = "%28(4)a(8) (5)%29(5) ";
    out = decompress(in, 1);
    CU_ASSERT_STRING_EQUAL(out, "((((aaaaaaaa     ))))) ");

    *(in) = "aaaa kamil b(5)";
    *(in + 1) = "%28(3) %29(2) %25(1)";
    out = decompress(in, 2);
    CU_ASSERT_STRING_EQUAL(out, "aaaa kamil bbbbb((( )) %");

    free(in);
    free(out);
}

void getData_test(){
    test = 1;
    int ctr = 0;
    char** data = getData(&ctr);
    CU_ASSERT_EQUAL(ctr, 5);
    CU_ASSERT_STRING_EQUAL(*data, "kamil1\n"); 
    CU_ASSERT_STRING_EQUAL(*(data + 1), "ala ma kota\n");
    CU_ASSERT_STRING_EQUAL(*(data + 2), "aaa bb\n");
    CU_ASSERT_STRING_EQUAL(*(data + 3), "pies kot\n");
    CU_ASSERT_STRING_EQUAL(*(data + 4), "aaa b\n");

    free(data);
}

int main()
{
  CU_pSuite pSuite = NULL;

  if (CUE_SUCCESS != CU_initialize_registry())
    return CU_get_error();

  pSuite = CU_add_suite("tests_suite", 0, 0);

  if (NULL == pSuite)
  {
    CU_cleanup_registry();
    return CU_get_error();
  }

  if (NULL == CU_add_test(pSuite, "getHexAscii_test", getHexAscii_test))
  {
    CU_cleanup_registry();
    return CU_get_error();
  }

  if (NULL == CU_add_test(pSuite, "compress_test", compress_test))
  {
    CU_cleanup_registry();
    return CU_get_error();
  }

  if(NULL == CU_add_test(pSuite, "decompress_test", decompress_test)){
    CU_cleanup_registry();
    return CU_get_error();
  }

  if(NULL == CU_add_test(pSuite, "getData_test", getData_test)){
    CU_cleanup_registry();
    return CU_get_error();
  }

  CU_basic_set_mode(CU_BRM_VERBOSE);

  CU_basic_run_tests();
  return CU_get_error();
}