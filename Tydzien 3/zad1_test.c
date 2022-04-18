#include "CUnit/Basic.h"
#include "encrypt_function.c"

void encrypt_test()
{
  char input1[] = "to be or not to be";
  encrypt(input1);
  CU_ASSERT_STRING_EQUAL(input1, "vq dg qt pqv vq dg");

  char input2[] = "ala ma kota";
  encrypt(input2);
  CU_ASSERT_STRING_EQUAL(input2, "dod pd nrwd");

  char input3[] = "abcdefghijklmnopqrstuvwxyz";
  encrypt(input3);
  CU_ASSERT_STRING_EQUAL(input3, "abcdefghijklmnopqrstuvwxyz");

  char input4[] = "a b c d e f g h i j k l m n o p q r s t u v w x y z";
  encrypt(input4);
  CU_ASSERT_STRING_EQUAL(input4, "b c d e f g h i j k l m n o p q r s t u v w x y z a");
}

int main()
{
  CU_pSuite pSuite = NULL;

  if (CUE_SUCCESS != CU_initialize_registry())
    return CU_get_error();

  pSuite = CU_add_suite("encrypt_test_suite", 0, 0);

  if (NULL == pSuite)
  {
    CU_cleanup_registry();
    return CU_get_error();
  }

  if (NULL == CU_add_test(pSuite, "encrypt_test", encrypt_test))
  {
    CU_cleanup_registry();
    return CU_get_error();
  }

  CU_basic_set_mode(CU_BRM_VERBOSE);

  CU_basic_run_tests();
  return CU_get_error();
}