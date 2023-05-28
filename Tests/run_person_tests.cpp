#include "Test_Person.hpp"

void run_tests_person()
{
    Tests::test_create_person();
    Tests::test_set_names();
    Tests::test_calculate_sex();
    Tests::test_calculate_birth_date();
    Tests::test_create_person_invalid_pesel_lenght();
}

