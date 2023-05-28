#include "Test_Casualty_department.hpp"

void run_tests_casualty_department()
{
    Tests_Casualty_Department::test_add_item();
    Tests_Casualty_Department::test_remove_item();
    Tests_Casualty_Department::test_add_patient_stable();
    Tests_Casualty_Department::test_add_patient_critical();
    Tests_Casualty_Department::test_pop_patient_stable();
    Tests_Casualty_Department::test_pop_patient_critical();
    Tests_Casualty_Department::test_remove_patient_stable();
    Tests_Casualty_Department::test_remove_patient_critical();
}