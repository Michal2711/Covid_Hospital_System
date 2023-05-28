#include "Test_Hospital.hpp"

void run_tests_hospital()
{
    Tests_Hospital::test_add_patient();
    Tests_Hospital::test_add_dead_patient();
    Tests_Hospital::test_add_employmee();
    Tests_Hospital::test_add_medical_room();
    Tests_Hospital::test_add_staff_room();
    Tests_Hospital::test_remove_patient();
    Tests_Hospital::test_move_patient_to_medical_room();
    Tests_Hospital::test_remove_doctor();
    Tests_Hospital::test_remove_nurse();
    Tests_Hospital::test_refresh();
}