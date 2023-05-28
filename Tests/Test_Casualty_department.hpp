#ifndef TEST_CASUALTY_DEPARTMENT_INCLUDED
#define TEST_CASUALTY_DEPARTMENT_INCLUDED
#include <iostream>


class Tests_Casualty_Department
{
public:
    Tests_Casualty_Department();
    ~Tests_Casualty_Department();

    static void test_add_item();
    static void test_remove_item();
    static void test_add_patient_stable();
    static void test_add_patient_critical();
    static void test_pop_patient_stable();
    static void test_pop_patient_critical();
    static void test_remove_patient_stable();
    static void test_remove_patient_critical();

};

#endif

