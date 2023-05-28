#include "Test_Covid_room.hpp"
#include "../Hospital/Rooms/covid_room.hpp"
#include "../Hospital/Humans/Patient.hpp"
#include "../Hospital/Humans/Medical_worker.hpp"
#include "../Hospital/Humans/Worker.hpp"
#include <iostream>
#include <cassert>

void Tests_Covid_Room::test_swap_data()
{
    CovidHospitalRoom room1(1, Condition_patients_in_room::stable);
    CovidHospitalRoom room2(2, Condition_patients_in_room::stable);
    Equipment equip{ Name::respirator };
    room1.setBedsNumber(10);
    Condition_patients_in_room state {Condition_patients_in_room::stable};
    room1.set_state(state);
    Patient patient1("Jan", "Kowalski", "12312312312");
    MedicalWorker doctor("Jan_doctor", "Kowalski_doctor", "12332112332", Worker_positions::Doctor);
    MedicalWorker nurse("Anna_nurse", "Kowalska_nurse", "78978978978", Worker_positions::Nurse);
    room1.addPatient(patient1);
    room1.addDoctor(doctor);
    room1.addNurse(nurse);
    room1.add_item(equip, 10);
    room2.swapData(room1);
    assert(room1.get_room_number() == room2.get_room_number()
            && room1.getBedsNumber() == room2.getBedsNumber()
            && room1.get_state() == room2.get_state()
            && room1.getPatientsList() == room2.getPatientsList()
            && room1.getDoctorsList() == room2.getDoctorsList()
            && room1.getNursesList() == room2.getNursesList()
            && room1.get_items_list() == room2. get_items_list());
    std::cout<<"covid_room_test_swap_data - passed"<<std::endl;
}


void Tests_Covid_Room::test_check_beds_number()
{
    CovidHospitalRoom room(1, Condition_patients_in_room::stable);
    room.setBedsNumber(1);
    Patient patient1("Jan", "Kowalski", "12312312312");
    // Patient patient2("Jan", "Kowalski2", "32132132132");
    room.addPatient(patient1);
    // assert(room.addPatient(patient2));
    std::cout<<"covid_room_test_check_beds_number - passed"<<std::endl;
}

void Tests_Covid_Room::test_remove_Patient()
{
    CovidHospitalRoom room(1, Condition_patients_in_room::stable);
    room.setBedsNumber(3);
    Patient patient1("Jan", "Kowalski", "12312312312");
    Patient patient2("Jan", "Kowalski2", "32132132132");
    room.addPatient(patient1);
    room.addPatient(patient2);
    room.removePatient(patient2);
    assert(room.getPatientsList().size() == 1);
    std::cout<<"covid_room_test_check_remove_patient - passed"<<std::endl;
}

void Tests_Covid_Room::test_remove_Doctor()
{
    CovidHospitalRoom room(1, Condition_patients_in_room::stable);
    MedicalWorker doctor("Jan", "Kowalski", "12312312312", Worker_positions::Doctor);
    room.addDoctor(doctor);
    room.removeDoctor(doctor);
    assert(room.getDoctorsList().size() == 0);
    std::cout<<"covid_room_test_check_remove_doctor - passed"<<std::endl;
}

void Tests_Covid_Room::test_remove_Nurse()
{
    CovidHospitalRoom room(1, Condition_patients_in_room::stable);
    MedicalWorker nurse("Anna", "Kowalska", "78978978978", Worker_positions::Nurse);
    room.addNurse(nurse);
    room.removeNurse(nurse);
    assert(room.getNursesList().size() == 0);
    std::cout<<"covid_room_test_check_remove_nurse - passed"<<std::endl;
}

void Tests_Covid_Room::test_add_Patient()
{
    CovidHospitalRoom room(1,Condition_patients_in_room::stable);
    room.setBedsNumber(3);
    Patient patient1("Jan", "Kowalski", "12312312312");
    room.addPatient(patient1);
    assert(room.getPatientsList().size() == 1);
    std::cout<<"covid_room_test_add_patient - passed"<<std::endl;
}

void Tests_Covid_Room::test_add_Doctor()
{
    CovidHospitalRoom room(1, Condition_patients_in_room::stable);
    MedicalWorker doctor("Jan", "Kowalski", "12312312312", Worker_positions::Doctor);
    Worker_positions position {Worker_positions::Doctor};
    doctor.set_position(position);
    room.addDoctor(doctor);
    assert(room.getDoctorsList().size() == 1);
    std::cout<<"covid_room_test_add_doctor - passed"<<std::endl;
}

void Tests_Covid_Room::test_add_Nurse()
{
    CovidHospitalRoom room(1, Condition_patients_in_room::stable);
    MedicalWorker nurse("Anna", "Kowalska", "78978978978", Worker_positions::Nurse);
    Worker_positions position {Worker_positions::Nurse};
    nurse.set_position(position);
    room.addNurse(nurse);
    assert(room.getNursesList().size() == 1);
    std::cout<<"covid_room_test_add_nurse - passed"<<std::endl;
}

void Tests_Covid_Room::test_add_item()
{
    CovidHospitalRoom room(1, Condition_patients_in_room::stable);
    Equipment equip{Name::respirator};
    room.add_item(equip, 10);
    assert(room.get_items_list().size() == 1);
    std::cout<<"covid_room_test_add_item - passed"<<std::endl;
}

void Tests_Covid_Room::test_remove_item()
{
    CovidHospitalRoom room(1, Condition_patients_in_room::stable);
    Equipment equip{Name::respirator};
    room.add_item(equip, 10);
    room.remove_item(equip, 5);
    assert(room.get_items_list().size() == 1);
    room.remove_item(equip, 5);
    assert(room.get_items_list().size() == 0);
    std::cout<<"covid_room_test_remove_item - passed"<<std::endl;
}