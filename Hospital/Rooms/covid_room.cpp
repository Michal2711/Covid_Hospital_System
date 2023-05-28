#include "covid_room.hpp"
#include "../Humans/Patient.hpp"
#include "../Humans/Medical_worker.hpp"
#include "../Humans/Worker.hpp"
#include <cmath>
#include <algorithm>

CovidHospitalRoom::CovidHospitalRoom(int room_number, Condition_patients_in_room state) noexcept
{
    this->room_number = room_number;
    this->set_state(state);
    this->setBedsNumber(10);
}

CovidHospitalRoom::CovidHospitalRoom(CovidHospitalRoom const& other) noexcept: Room(other)
{
    room_number = other.get_room_number();
    beds_number = other.getBedsNumber();
    state = other.get_state();

    patients = other.getPatientsList();
    doctors = other.getDoctorsList();
    nurses = other.getNursesList();
    items = other.get_items_list();

}

CovidHospitalRoom::~CovidHospitalRoom() noexcept
{}

void CovidHospitalRoom::swapData(CovidHospitalRoom &other) noexcept
{
    room_number = other.get_room_number();
    beds_number = other.getBedsNumber();
    state = other.get_state();

    patients = other.getPatientsList();
    doctors = other.getDoctorsList();
    nurses = other.getNursesList();
    items = other.get_items_list();
}

int CovidHospitalRoom::get_room_number() const noexcept
{
    return room_number;
}

Condition_patients_in_room CovidHospitalRoom::get_state() const
{
    return state;
}

int CovidHospitalRoom::getBedsNumber() const noexcept
{
    return beds_number;
}

int CovidHospitalRoom::getPercentageOfFreeBeds() const
{
    if (beds_number <= 0) throw InvalidBedsNumberException();
    return static_cast<int>(round(((beds_number - patients.size()) * 100) / beds_number)); // percentage of free beds in room, its used to spead patients equaly
}

std::vector<Patient> CovidHospitalRoom::getPatientsList() const noexcept
{
    return patients;
}

std::vector<MedicalWorker> CovidHospitalRoom::getDoctorsList() const noexcept
{
    return doctors;
}

std::vector<MedicalWorker> CovidHospitalRoom::getNursesList() const noexcept
{
    return nurses;
}

int CovidHospitalRoom::getNumberOfFreeBeds() const
{
    return beds_number - patients.size();
}

void CovidHospitalRoom::setBedsNumber(int beds_number)
{
    if (beds_number <= 0) throw InvalidBedsNumberException();
    this->beds_number = beds_number;
}

void CovidHospitalRoom::set_state(Condition_patients_in_room new_state) noexcept
{
    state = new_state;
}

void CovidHospitalRoom::checkBedsNumber() const
{
    size_t beds = beds_number;
    if(beds < patients.size()) throw RoomOverflowException();
}

void CovidHospitalRoom::setPatientsList(std::vector<Patient> const& patients) noexcept
{
    checkBedsNumber();
    this->patients = patients;
}

void CovidHospitalRoom::setNursesList(std::vector<MedicalWorker> const nurses) noexcept
{
    this->nurses = nurses;
}

void CovidHospitalRoom::setDoctorsList(std::vector<MedicalWorker> const doctors) noexcept
{
    this->doctors = doctors;
}

void CovidHospitalRoom::set_room_number(int new_number) noexcept
{
    this->room_number = new_number;
}

void CovidHospitalRoom::addPatient(Patient& patient) noexcept
{
    patient.set_hospital_room(this);
    patients.push_back(patient); // copies of patients in vector, maybe destructor of patient should remove him from list
    checkBedsNumber();
}

void CovidHospitalRoom::addDoctor(MedicalWorker& doctor) noexcept
{
    doctor.add_room(*this);
    doctors.push_back(doctor);
}

void CovidHospitalRoom::addNurse(MedicalWorker& nurse) noexcept
{
    nurse.add_room(*this);
    nurses.push_back(nurse);
}


void CovidHospitalRoom::removePatient(Patient& patient) // adds iterator to pointers list
{
    for (auto i = patients.begin(); i < patients.end(); i++){
        if(*i == patient) // if are pointing to the same object we got it
        {
            patients.erase(i);
            return;
        }
    }
}

void CovidHospitalRoom::removeDoctor(MedicalWorker& doctor) noexcept
{
    for (auto i = doctors.begin(); i < doctors.end(); i++){
        if(*i == doctor)
        {
            doctors.erase(i);
            return;
        }
    }
}

void CovidHospitalRoom::removeNurse(MedicalWorker& nurse) noexcept
{
    for (auto i = nurses.begin(); i < nurses.end(); i++){
        if(*i == nurse)
        {
            nurses.erase(i);
            return;
        }
    }
}

void CovidHospitalRoom::add_item(Equipment item, int quantity) noexcept
{
    items.insert( std::pair<Equipment const, int>(item, quantity));
}

void CovidHospitalRoom::remove_item(Equipment const& item, int quantity) noexcept
{
    auto itr = items.find(item);
    if (itr != items.end())
    {
        int new_quantity = itr->second - quantity;
        if (new_quantity < 1)
        {
            items.erase(item);
        }
        else
        {
            itr->second = new_quantity;
        }

    }
}

std::unordered_map <Equipment, int, Hash> const& CovidHospitalRoom::get_items_list() const noexcept
{
    return items;
}

std::ostream& operator<<(std::ostream& os, CovidHospitalRoom const& room)
{
    os << "Room nr: " <<room.get_room_number();
    os << "\nNumber of free beds:\n " << room.getNumberOfFreeBeds() << std::endl;
    return os;
}

CovidHospitalRoom& CovidHospitalRoom::operator=(CovidHospitalRoom const& other)
{
    CovidHospitalRoom tmp(other);
    swapData(tmp);
    return *this;
}

bool CovidHospitalRoom::operator==(CovidHospitalRoom const& other) const
{
    return room_number == other.get_room_number();
}

bool CovidHospitalRoom::operator!=(CovidHospitalRoom const& other) const
{
    return !(*this == other);
}

bool CovidHospitalRoom::operator>(const CovidHospitalRoom& other) const
{
    return getPercentageOfFreeBeds() < other.getPercentageOfFreeBeds();
}
bool CovidHospitalRoom::operator<(const CovidHospitalRoom& other) const
{
    return  !(*this > other);
}
bool CovidHospitalRoom::operator>=(const CovidHospitalRoom& other) const
{
    return getPercentageOfFreeBeds() <= other.getPercentageOfFreeBeds();
}
bool CovidHospitalRoom::operator<=(const CovidHospitalRoom& other) const
{
    return  !(*this >= other);
}

void CovidHospitalRoom::printRoom() const noexcept
{
    std::cout << *this;
}
