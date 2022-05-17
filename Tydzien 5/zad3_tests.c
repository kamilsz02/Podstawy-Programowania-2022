#include "CUnit/Basic.h"
#include "zad3_functions.c"

void Term_toString_test() {
    Term* term = Term__create(12, 55, 60, WED);
    const char* exp = "\"Sroda 12:55 [60]\"";
    char* res = Term__toString(term);
    CU_ASSERT_STRING_EQUAL(res, exp);
    free(res);
    free(term); 
}

void Lesson_create_init_test() {
    Lesson* les = Lesson_create(12, 40, 60, MON, "BSST");
    CU_ASSERT_EQUAL(les->name, "BSST");
    CU_ASSERT_EQUAL(les->term->day, MON);
    CU_ASSERT_EQUAL(les->term->hour, 12);
    CU_ASSERT_EQUAL(les->term->minute, 40);
    free(les);
}

void Lesson__earlierDay_test() {
    Lesson* les1 = Lesson_create(13, 15, 45, MON, "Algebra");
    Lesson* ex = Lesson_create(13, 15, 45, MON, "Algebra");
    Lesson* les2 = Lesson_create(13, 15, 45, WED, "Algebra");
    Lesson__earlierDay(les1);
    CU_ASSERT_EQUAL(les1->name, ex->name);
    CU_ASSERT_EQUAL(les1->term->day, ex->term->day);
    CU_ASSERT_EQUAL(les1->term->hour, ex->term->hour);
    CU_ASSERT_EQUAL(les1->term->minute, ex->term->minute);
    CU_ASSERT_EQUAL(les1->term->duration, ex->term->duration);
    Lesson__earlierDay(les2);
    CU_ASSERT_EQUAL(les1->name, ex->name);
    CU_ASSERT_EQUAL(les1->term->day, ex->term->day);
    CU_ASSERT_EQUAL(les1->term->hour, ex->term->hour);
    CU_ASSERT_EQUAL(les1->term->minute, ex->term->minute);
    CU_ASSERT_EQUAL(les1->term->duration, ex->term->duration);
    free(les2);
    free(les1);
    free(ex);
}

void Lesson__laterDay_test() {
    Lesson* les1 = Lesson_create(13, 15, 45, FRI, "Algebra");
    Lesson* ex = Lesson_create(13, 15, 45, FRI, "Algebra");
    Lesson* les2 = Lesson_create(13, 15, 45, THU, "Algebra");
    Lesson__laterDay(les1);
    CU_ASSERT_EQUAL(les1->name, ex->name);
    CU_ASSERT_EQUAL(les1->term->day, ex->term->day);
    CU_ASSERT_EQUAL(les1->term->hour, ex->term->hour);
    CU_ASSERT_EQUAL(les1->term->minute, ex->term->minute);
    CU_ASSERT_EQUAL(les1->term->duration, ex->term->duration);
    Lesson__laterDay(les2);
    CU_ASSERT_EQUAL(les1->name, ex->name);
    CU_ASSERT_EQUAL(les1->term->day, ex->term->day);
    CU_ASSERT_EQUAL(les1->term->hour, ex->term->hour);
    CU_ASSERT_EQUAL(les1->term->minute, ex->term->minute);
    CU_ASSERT_EQUAL(les1->term->duration, ex->term->duration);
    free(les2);
    free(les1);
    free(ex);
}

void Lesson__laterTime_test() {
    Lesson* les1 = Lesson_create(15, 45, 45, FRI, "Algebra");
    Lesson* ex = Lesson_create(15, 45, 45, FRI, "Algebra");
    Lesson* les2 = Lesson_create(15, 0, 45, FRI, "Algebra");
    Lesson__laterTime(les1);
    CU_ASSERT_EQUAL(les1->name, ex->name);
    CU_ASSERT_EQUAL(les1->term->day, ex->term->day);
    CU_ASSERT_EQUAL(les1->term->hour, ex->term->hour);
    CU_ASSERT_EQUAL(les1->term->minute, ex->term->minute);
    CU_ASSERT_EQUAL(les1->term->duration, ex->term->duration);
    Lesson__laterTime(les2);
    CU_ASSERT_EQUAL(les1->name, ex->name);
    CU_ASSERT_EQUAL(les1->term->day, ex->term->day);
    CU_ASSERT_EQUAL(les1->term->hour, ex->term->hour);
    CU_ASSERT_EQUAL(les1->term->minute, ex->term->minute);
    CU_ASSERT_EQUAL(les1->term->duration, ex->term->duration);
    free(les2);
    free(les1);
    free(ex);
}

void Lesson__earlierTime_test() {
    Lesson* les1 = Lesson_create(8, 30, 45, THU, "Algebra");
    Lesson* ex = Lesson_create(8, 30, 45, THU, "Algebra");
    Lesson* les2 = Lesson_create(9, 15, 45, THU, "Algebra");
    Lesson__earlierTime(les1);
    CU_ASSERT_EQUAL(les1->name, ex->name);
    CU_ASSERT_EQUAL(les1->term->day, ex->term->day);
    CU_ASSERT_EQUAL(les1->term->hour, ex->term->hour);
    CU_ASSERT_EQUAL(les1->term->minute, ex->term->minute);
    CU_ASSERT_EQUAL(les1->term->duration, ex->term->duration);
    Lesson__earlierTime(les2);
    CU_ASSERT_EQUAL(les1->name, ex->name);
    CU_ASSERT_EQUAL(les1->term->day, ex->term->day);
    CU_ASSERT_EQUAL(les1->term->hour, ex->term->hour);
    CU_ASSERT_EQUAL(les1->term->minute, ex->term->minute);
    CU_ASSERT_EQUAL(les1->term->duration, ex->term->duration);
    free(les2);
    free(les1);
    free(ex);
}

void Lesson_toString_test() {
    Lesson* term = Lesson_create(12, 55, 60, WED, "Analiza 2");
    const char* exp = "\"Analiza 2, Sroda 12:55 [60]\"";
    char* res = Lesson__toString(term);
    CU_ASSERT_STRING_EQUAL(res, exp);
    free(res);
    free(term); 
}

void zad3_test() {
    char** argv = malloc(4 * sizeof(char*));
    argv[0] = "d+";
    argv[1] = "d+";
    argv[2] = "d+";
    argv[3] = "t-";
    int len;
    Lesson* les = Lesson_create(12, 50, 90, WED, "Podstawy Programowania");
    Action* actions = parse(4, argv, &len);
    for(int i = 0; i < len; i++) {
        Action el = actions[i];
        switch (el)
        {
        case DAY_EARLIER:
            Lesson__earlierDay(les);
            break;
        case DAY_LATER:
            Lesson__laterDay(les);
            break;
        case TIME_EARLIER:
            Lesson__earlierTime(les);
            break;
        case TIME_LATER:
            Lesson__laterTime(les);
            break;
        default:
            break;
        }
    }

    Lesson* ex = Lesson_create(11, 20, 90, FRI, "Podstawy Programowania");
    CU_ASSERT_EQUAL(les->name, ex->name);
    CU_ASSERT_EQUAL(les->term->day, ex->term->day);
    CU_ASSERT_EQUAL(les->term->hour, ex->term->hour);
    CU_ASSERT_EQUAL(les->term->minute, ex->term->minute);
    CU_ASSERT_EQUAL(les->term->duration, ex->term->duration);

    free(argv);
    free(ex);
    free(les);
    free(actions); 
}

int main()
{
  make_bounds();
  CU_pSuite pSuite = NULL;

  if (CUE_SUCCESS != CU_initialize_registry())
    return CU_get_error();

  pSuite = CU_add_suite("Lesson tests", 0, 0);

  if (NULL == pSuite)
  {
    CU_cleanup_registry();
    return CU_get_error();
  }

  if (NULL == CU_add_test(pSuite, "Lesson_create_init_test", Lesson_create_init_test))
  {
    CU_cleanup_registry();
    return CU_get_error();
  }

  if (NULL == CU_add_test(pSuite, "Term_toString_test", Term_toString_test))
  {
    CU_cleanup_registry();
    return CU_get_error();
  }

  if (NULL == CU_add_test(pSuite, "Lesson__earlierDay_test", Lesson__earlierDay_test))
  {
    CU_cleanup_registry();
    return CU_get_error();
  }

  if (NULL == CU_add_test(pSuite, "Lesson__laterDay_test", Lesson__laterDay_test))
  {
    CU_cleanup_registry();
    return CU_get_error();
  }

  if (NULL == CU_add_test(pSuite, "Lesson__laterTime_test", Lesson__laterTime_test))
  {
    CU_cleanup_registry();
    return CU_get_error();
  }

  if (NULL == CU_add_test(pSuite, "Lesson__earlierTime_test", Lesson__earlierTime_test))
  {
    CU_cleanup_registry();
    return CU_get_error();
  }

  if (NULL == CU_add_test(pSuite, "Lesson_toString_test", Lesson_toString_test))
  {
    CU_cleanup_registry();
    return CU_get_error();
  }

  if (NULL == CU_add_test(pSuite, "zad3_test", zad3_test))
  {
    CU_cleanup_registry();
    return CU_get_error();
  }  

  CU_basic_set_mode(CU_BRM_VERBOSE);

  CU_basic_run_tests();
  return CU_get_error();
}