#include "CUnit/Basic.h"
#include "zad2.c"

void Term_create_and_init_test() {
    Term* new_term = Term__create(14, 30, 90);
    CU_ASSERT_EQUAL(new_term->hour, 14);
    CU_ASSERT_EQUAL(new_term->minute, 30);
    CU_ASSERT_EQUAL(new_term->duration, 90);
}

void Term_toString_test() {
    Term* new_term = Term__create(14, 30, 90);
    char* res = Term__toString(new_term);
    CU_ASSERT_STRING_EQUAL(res, "\"14:30 [90]\"");
    free(res);    
}

int main()
{
  CU_pSuite pSuite = NULL;

  if (CUE_SUCCESS != CU_initialize_registry())
    return CU_get_error();

  pSuite = CU_add_suite("Term tests", 0, 0);

  if (NULL == pSuite)
  {
    CU_cleanup_registry();
    return CU_get_error();
  }

  if (NULL == CU_add_test(pSuite, "Term_create_and_init_test", Term_create_and_init_test))
  {
    CU_cleanup_registry();
    return CU_get_error();
  }

  if (NULL == CU_add_test(pSuite, "Term_toString_test", Term_toString_test))
  {
    CU_cleanup_registry();
    return CU_get_error();
  }

  CU_basic_set_mode(CU_BRM_VERBOSE);

  CU_basic_run_tests();
  return CU_get_error();
}