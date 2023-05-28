#include "Hospital/Hospital.hpp"
#include <iostream>
#include "Hospital/Rooms/casualty_department.hpp"
#include "Tests/Test_Person.hpp"
#include "Tests/Test_Patient.hpp"
#include "Tests/Test_Casualty_department.hpp"
#include "Tests/Test_Staff_room.hpp"
#include "Tests/Test_Covid_room.hpp"
#include "Tests/Test_Hospital.hpp"
#include "Simulation/Simulation.hpp"

void run_tests_person();
void run_tests_patient();
void run_tests_casualty_department();
void run_tests_staff_room();
void run_tests_covid_room();
void run_tests_hospital();

int main()
{
    Simulation sim1;
    sim1.open_file("parameters.json");
    std::cout << "Starting app.." << std::endl;
    std::cout << "Checking files..."<< std::endl;
    run_tests_person();
    run_tests_patient();
    run_tests_casualty_department();
    run_tests_staff_room();
    run_tests_covid_room();
    run_tests_hospital();
    std::string promt = "\nCOVID HOSPITAL MANAGER v1.1\nWelcome to simple Covid Hospital Manager Simulator.\nSimulation parameters can be set up by editing parameters.json\n";
    std::cout<<promt<<std::endl;
    sim1.create_hospital();
    sim1.run_simulation();

    return 0;
}
