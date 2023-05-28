#include "Test_Patient.hpp"

void run_tests_patient()
{
    string new_vaccine = "Covid", vaccine_to_remove = "Covid";
    Tests_Patient::test_equal();
    Tests_Patient::test_assignment();
    Tests_Patient::test_bigger();
    Tests_Patient::test_copy_constructor();
    Tests_Patient::test_print();
    Tests_Patient::test_vaccine_add(new_vaccine);
    Tests_Patient::test_vaccine_remove(vaccine_to_remove);
}

