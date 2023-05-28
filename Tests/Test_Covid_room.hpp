#ifndef TEST_COVID_ROOM_INCLUDED
#define TEST_COVID_ROOM_INCLUDED
#include <iostream>

class Tests_Covid_Room
{
public:
    Tests_Covid_Room();
    ~Tests_Covid_Room();

    static void test_swap_data();
    static void test_check_beds_number();
    static void test_remove_Patient();
    static void test_remove_Doctor();
    static void test_remove_Nurse();
    static void test_add_Patient();
    static void test_add_Doctor();
    static void test_add_Nurse();
    static void test_add_item();
    static void test_remove_item();

};


#endif