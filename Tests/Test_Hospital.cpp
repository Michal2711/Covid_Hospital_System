#include "Test_Hospital.hpp"
#include "../Hospital/Humans/Patient.hpp"
#include "../Hospital/Humans/Medical_worker.hpp"
#include "../Hospital/Rooms/covid_room.hpp"
#include "../Hospital/Rooms/staff_room.hpp"
#include <cassert>

void Tests_Hospital::test_add_patient()
{
    Hospital covid = Hospital("Stadion", "Warszawa");
    Patient patient_stable = Patient("Jan", "Kowalski", "12312312312");
    patient_stable.set_Health(Patient::Health::stable);
    Patient patient_critical = Patient("Pytlu", "Wiktoreski", "78978978978");
    patient_critical.set_Health(Patient::Health::critical);
    covid.add_patient(&patient_stable);
    covid.add_patient(&patient_critical);
    assert(covid.list_of_patients.size() == 2);
    std::cout<<"hospital_test_add_patient - passed"<<std::endl;
}

void Tests_Hospital::test_add_dead_patient()
{
    Hospital covid = Hospital("Stadion", "Warszawa");
    Patient patient_dead = Patient("Jan", "Kowalski", "12312312312");
    covid.add_dead_patient(&patient_dead);
    assert(covid.list_of_killed_patients_by_covid.size() == 1);
    std::cout<<"hospital_test_add_dead_patient - passed"<<std::endl;
}

void Tests_Hospital::test_add_employmee()
{
    Hospital covid = Hospital("Stadion", "Warszawa");
    MedicalWorker doctor = MedicalWorker("Jan", "Kowalski", "12312312312", Worker_positions::Doctor);
    MedicalWorker doctor2 = MedicalWorker("Anna", "Kowalska", "78978978978", Worker_positions::Nurse);
    covid.add_employmee(&doctor);
    covid.add_employmee(&doctor2);
    assert(covid.list_of_doctors.size() == 1 && covid.list_of_nurse.size() == 1);
    std::cout<<"hospital_test_add_employmee - passed"<<std::endl;
}

void Tests_Hospital::test_add_medical_room()
{
    Hospital covid = Hospital("Stadion", "Warszawa");
    CovidHospitalRoom room_stable = CovidHospitalRoom(1, Condition_patients_in_room::stable);
    CovidHospitalRoom room_critical = CovidHospitalRoom(2, Condition_patients_in_room::critical);
    covid.add_medical_room(room_stable);
    covid.add_medical_room(room_critical);
    assert(covid.medical_rooms_stable.size() == 1 && covid.medical_rooms_critical.size() == 1);
    std::cout<<"hospital_test_add_medical_room - passed"<<std::endl;
}

void Tests_Hospital::test_add_staff_room()
{
    Hospital covid = Hospital("Stadion", "Warszawa");
    Staff_room room = Staff_room(1, Staff_room::Profession::janitor);
    covid.add_staff_room(room);
    assert(covid.staff_rooms.size() == 1);
    cout<<"hospital_test_add_staff_room - passed"<<std::endl;
}

void Tests_Hospital::test_remove_patient()
{
    Hospital covid = Hospital("Stadion", "Warszawa");
    Patient patient1 = Patient("Jan", "Kowalski", "12312312312");
    patient1.set_Health(Patient::Health::stable);
    Patient patient2 = Patient("Karol", "OrzechowyRaj", "78978978978");
    patient2.set_Health(Patient::Health::critical);
    CovidHospitalRoom room_stable = CovidHospitalRoom(1, Condition_patients_in_room::stable);
    CovidHospitalRoom room_critical = CovidHospitalRoom(2, Condition_patients_in_room::critical);
    room_stable.setBedsNumber(3);
    room_critical.setBedsNumber(3);
    MedicalWorker doctor("Wiktor", "Pytlewski","00232810417");
    MedicalWorker nurse("Karol", "Orzechowski", "01241010923");
    covid.add_medical_room(room_stable);
    covid.add_medical_room(room_critical);
    covid.add_patient(&patient1);
    covid.add_patient(&patient2);
    covid.add_doctor(&doctor);
    covid.add_nurse(&nurse);
    covid.move_patient_to_medical_room(&patient1);
    covid.move_patient_to_medical_room(&patient2);
    covid.remove_patient(&patient1);
    assert(covid.list_of_patients.size() == 1 );
    std::cout<<"hospital_test_remove_patient - passed"<<std::endl;
}

void Tests_Hospital::test_move_patient_to_medical_room()
{
    Hospital covid = Hospital("Stadion", "Warszawa");
    CovidHospitalRoom room_stable = CovidHospitalRoom(1, Condition_patients_in_room::stable);
    CovidHospitalRoom room_critical = CovidHospitalRoom(2, Condition_patients_in_room::critical);
    MedicalWorker doctor("Wiktor", "Pytlewski","00232810417");
    MedicalWorker nurse("Karol", "Orzechowski", "01241010923");
    Patient patient_stable = Patient("Jan", "Kowalski", "12312312312");
    Patient patient_critical = Patient("Karol", "OrzechowyRaj", "78978978978");

    room_stable.setBedsNumber(3);
    room_critical.setBedsNumber(3);
    covid.add_medical_room(room_stable);
    covid.add_medical_room(room_critical);
    covid.add_doctor(&doctor);
    covid.add_nurse(&nurse);
    covid.add_patient(&patient_stable);
    covid.add_patient(&patient_critical);
    patient_stable.set_Health(Patient::Health::stable);
    patient_critical.set_Health(Patient::Health::critical);
    covid.move_patient_to_medical_room(&patient_stable);
    covid.move_patient_to_medical_room(&patient_critical);

    CovidHospitalRoom* room_stable_patient = patient_stable.get_hospital_room();
    Condition_patients_in_room con_stable = room_stable_patient->get_state();
    CovidHospitalRoom* room_critical_patient = patient_critical.get_hospital_room();
    Condition_patients_in_room con_critical = room_critical_patient->get_state();

    assert( con_stable == Condition_patients_in_room::stable &&
                con_critical == Condition_patients_in_room::critical);
    std::cout<<"hospital_test_move_patient_to_medical_room - passed"<<std::endl;
}

void Tests_Hospital::test_remove_doctor()
{
    Hospital covid = Hospital("Stadion", "Warszawa");
    MedicalWorker doctor1 = MedicalWorker("Jan", "Kowalski", "12312312312", Worker_positions::Doctor);
    MedicalWorker doctor2 = MedicalWorker("Anna", "Kowalska", "78978978978", Worker_positions::Doctor);
    covid.add_employmee(&doctor1);
    covid.add_employmee(&doctor2);
    covid.remove_doctor(&doctor1);
    assert(covid.list_of_doctors.size() == 1);
    std::cout<<"hospital_test_remove_doctor - passed"<<std::endl;
}

void Tests_Hospital::test_remove_nurse()
{
    Hospital covid = Hospital("Stadion", "Warszawa");
    MedicalWorker nurse1 = MedicalWorker("Jan", "Kowalski", "12312312312", Worker_positions::Nurse);
    MedicalWorker nurse2 = MedicalWorker("Anna", "Kowalska", "78978978978", Worker_positions::Nurse);
    covid.add_employmee(&nurse1);
    covid.add_employmee(&nurse2);
    covid.remove_nurse(&nurse1);
    assert(covid.list_of_nurse.size() == 1);
    std::cout<<"hospital_test_remove_nurse - passed"<<std::endl;
}

void Tests_Hospital::test_refresh()
{
    Hospital covid = Hospital("Stadion", "Warszawa");
    Patient patient = Patient("Jan", "Kowalski", "12312312312");
    CovidHospitalRoom room_stable = CovidHospitalRoom(1, Condition_patients_in_room::stable);
    CovidHospitalRoom room_critical = CovidHospitalRoom(2, Condition_patients_in_room::critical);
    MedicalWorker doctor("Wiktor", "Pytlewski","00232810417");
    MedicalWorker nurse("Karol", "Orzechowski", "01241010923");
    room_critical.setBedsNumber(3);
    room_stable.setBedsNumber(3);
    covid.add_medical_room(room_stable);
    covid.add_medical_room(room_critical);
    covid.add_doctor(&doctor);
    covid.add_nurse(&nurse);
    patient.set_Health(Patient::Health::stable);
    covid.move_patient_to_medical_room(&patient);
    patient.set_Health(Patient::Health::critical);
    CovidHospitalRoom* room_before = patient.get_hospital_room();
    Condition_patients_in_room con_before = room_before->get_state();
    covid.refresh(&patient);
    CovidHospitalRoom* room_after = patient.get_hospital_room();
    Condition_patients_in_room con_after = room_after->get_state();
    assert( con_before == Condition_patients_in_room::stable &&
                con_after == Condition_patients_in_room::critical);
    std::cout<<"hospital_test_refresh - passed"<<std::endl;
}
