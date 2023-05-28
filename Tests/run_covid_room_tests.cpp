#include "Test_Covid_room.hpp"

void run_tests_covid_room()
{
    Tests_Covid_Room::test_swap_data();
    Tests_Covid_Room::test_check_beds_number();
    Tests_Covid_Room::test_remove_Patient();
    Tests_Covid_Room::test_remove_Doctor();
    Tests_Covid_Room::test_remove_Nurse();
    Tests_Covid_Room::test_add_Patient();
    Tests_Covid_Room::test_add_Doctor();
    Tests_Covid_Room::test_add_Nurse();
    Tests_Covid_Room::test_add_item();
    Tests_Covid_Room::test_remove_item();
}