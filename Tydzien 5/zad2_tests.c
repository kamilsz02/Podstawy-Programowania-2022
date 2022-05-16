#include "CUnit/Basic.h"
#include "zad2.c"

void Term_create_and_init_test() {
    Term* new_term = Term__create(14, 30, 90);
    CU_ASSERT_EQUAL(new_term->hour, 14);
    CU_ASSERT_EQUAL(new_term->minute, 30);
    CU_ASSERT_EQUAL(new_term->duration, 90);
    Term__destroy(new_term);
}

void Term_toString_test() {
    Term* new_term = Term__create(14, 30, 90);
    char* res = Term__toString(new_term);
    CU_ASSERT_STRING_EQUAL(res, "\"14:30 [90]\"");
    free(res);    
    Term__destroy(new_term);
}

void Term__earlierThan_test() {
    Term* term1 = Term__create(13, 30, 90);
    Term* term2 = Term__create(14, 30, 90);
    CU_ASSERT_EQUAL(Term__earlierThan(term1, term2), true);
    CU_ASSERT_EQUAL(Term__earlierThan(term2, term1), false);
    Term__destroy(term1);
    Term__destroy(term2);
}

void Term__laterThan_test() {
    Term* term1 = Term__create(15, 30, 90);
    Term* term2 = Term__create(14, 30, 90);
    CU_ASSERT_EQUAL(Term__laterThan(term1, term2), true);
    CU_ASSERT_EQUAL(Term__laterThan(term2, term1), false);
    Term__destroy(term1);
    Term__destroy(term2);
}

void Term__equals_test() {
    Term* term1 = Term__create(15, 30, 90);
    Term* term2 = Term__create(15, 30, 90);
    Term* term3 = Term__create(14, 30, 45);
    CU_ASSERT_EQUAL(Term__equals(term1, term2), true);
    CU_ASSERT_EQUAL(Term__equals(term1, term3), false);
    Term__destroy(term1);
    Term__destroy(term2);
    Term__destroy(term3);
}

void Term__endTerm_test() {
    Term* term1 = Term__create(10, 25, 45);
    Term* term2 = Term__create(11, 45, 90);
    Term* res1 = Term__endTerm(term1, term2);
    CU_ASSERT_EQUAL(res1->hour, 10);
    CU_ASSERT_EQUAL(res1->minute, 25)
    CU_ASSERT_EQUAL(res1->duration, 80);
    Term* res2 = Term__endTerm(term2, term1);
    CU_ASSERT_EQUAL(res2->hour, -1);
    CU_ASSERT_EQUAL(res2->minute, -1);
    CU_ASSERT_EQUAL(res2->duration, -1);
    Term__destroy(res1);
    Term__destroy(res2);
    Term__destroy(term1);
    Term__destroy(term2);
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

  if (NULL == CU_add_test(pSuite, "Term__earlierThan_test", Term__earlierThan_test))
  {
    CU_cleanup_registry();
    return CU_get_error();
  }

  if (NULL == CU_add_test(pSuite, "Term__laterThan_test", Term__laterThan_test))
  {
    CU_cleanup_registry();
    return CU_get_error();
  }

  if (NULL == CU_add_test(pSuite, "Term__equals_test", Term__equals_test))
  {
    CU_cleanup_registry();
    return CU_get_error();
  }

  if (NULL == CU_add_test(pSuite, "Term__endTerm_test", Term__endTerm_test))
  {
    CU_cleanup_registry();
    return CU_get_error();
  }

  CU_basic_set_mode(CU_BRM_VERBOSE);

  CU_basic_run_tests();
  return CU_get_error();
}