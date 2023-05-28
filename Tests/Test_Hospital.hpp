#ifndef TEST_HOSPITAL_INCLUDED
#define TEST_HOSPITAL_INCLUDED
#include <iostream>
#include "../Hospital/Hospital.hpp"

class Tests_Hospital
{
public:
    Tests_Hospital();
    ~Tests_Hospital();
    static void test_add_patient();
    static void test_add_dead_patient();
    static void test_add_employmee();
    static void test_add_medical_room();
    static void test_add_staff_room();

    static void test_remove_patient();
    static void test_move_patient_to_medical_room();
    static void test_remove_doctor();
    static void test_remove_nurse();

    static void test_refresh();
    static void test_patient_heaps();
};

#endif