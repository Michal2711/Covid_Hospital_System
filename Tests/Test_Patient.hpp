#ifndef TEST_PATIENT_INCLUDED
#define TEST_PATIENT_INCLUDED
#include <iostream>
#include <string>

using namespace std;

class Tests_Patient
{
public:
    Tests_Patient();
    ~Tests_Patient();
    static void test_equal();
    static void test_assignment();
    static void test_bigger();
    static void test_copy_constructor();
    static void test_print();
    static void test_vaccine_add(string const& new_vaccine);
    static void test_vaccine_remove(string const& vaccine_to_remove);
};

#endif
