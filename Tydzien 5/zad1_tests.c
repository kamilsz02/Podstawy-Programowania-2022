#include "CUnit/Basic.h"
#include "functions.c"

void Day_nextDay_test() {
    CU_ASSERT_EQUAL(Day_nextDay(MON), TUE);
    CU_ASSERT_EQUAL(Day_nextDay(TUE), WED);
    CU_ASSERT_EQUAL(Day_nextDay(WED), THU);
    CU_ASSERT_EQUAL(Day_nextDay(THU), FRI);
    CU_ASSERT_EQUAL(Day_nextDay(FRI), SAT);
    CU_ASSERT_EQUAL(Day_nextDay(SAT), SUN);
    CU_ASSERT_EQUAL(Day_nextDay(SUN), MON);
}

void Day_prevDay_test() {
    CU_ASSERT_EQUAL(Day_prevDay(MON), SUN);
    CU_ASSERT_EQUAL(Day_prevDay(TUE), MON);
    CU_ASSERT_EQUAL(Day_prevDay(WED), TUE);
    CU_ASSERT_EQUAL(Day_prevDay(THU), WED);
    CU_ASSERT_EQUAL(Day_prevDay(FRI), THU);
    CU_ASSERT_EQUAL(Day_prevDay(SAT), FRI);
    CU_ASSERT_EQUAL(Day_prevDay(SUN), SAT);
}

void parse_test() {
    char* in[5] = {"d-", "d+", "t-", "kamil", "t+"};
    int len;
    Action* res = parse(5, in, &len);
    CU_ASSERT_EQUAL(res[0], DAY_EARLIER);
    CU_ASSERT_EQUAL(res[1], DAY_LATER);
    CU_ASSERT_EQUAL(res[2], TIME_EARLIER);
    CU_ASSERT_EQUAL(res[3], TIME_LATER);

    free(res);
}

void shift_test() {
    Action args[4] = {DAY_EARLIER, DAY_EARLIER, DAY_EARLIER, DAY_LATER};
    CU_ASSERT_EQUAL(shift(MON, args, 4), SAT);
}

int main()
{
  CU_pSuite pSuite = NULL;

  if (CUE_SUCCESS != CU_initialize_registry())
    return CU_get_error();

  pSuite = CU_add_suite("Day tests", 0, 0);

  if (NULL == pSuite)
  {
    CU_cleanup_registry();
    return CU_get_error();
  }

  if (NULL == CU_add_test(pSuite, "Day_nextDay_test", Day_nextDay_test))
  {
    CU_cleanup_registry();
    return CU_get_error();
  }

  if (NULL == CU_add_test(pSuite, "Day_prevDay_test", Day_prevDay_test))
  {
    CU_cleanup_registry();
    return CU_get_error();
  }

  if (NULL == CU_add_test(pSuite, "parse_test", parse_test))
  {
    CU_cleanup_registry();
    return CU_get_error();
  }

  if (NULL == CU_add_test(pSuite, "shift_test", shift_test))
  {
    CU_cleanup_registry();
    return CU_get_error();
  }

  CU_basic_set_mode(CU_BRM_VERBOSE);

  CU_basic_run_tests();
  return CU_get_error();
}