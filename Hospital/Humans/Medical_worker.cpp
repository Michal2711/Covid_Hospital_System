#include <iostream>
#include <algorithm>
#include "Medical_worker.hpp"
#include "../Rooms/covid_room.hpp"
#include "Patient.hpp"


MedicalWorker::MedicalWorker(const string& name, const string& surname, const string& pesel, const Worker_positions& position):
    Worker(name, surname, pesel, position),
    patients({}), rooms({})
{}

MedicalWorker::MedicalWorker(const string& name, const string& surname, const string& pesel):
    Worker(name, surname, pesel),
    patients({}), rooms({})
{}

MedicalWorker::MedicalWorker(const MedicalWorker& original):
    Worker(original.name, original.surname, original.pesel, original.position),
    patients(original.patients), rooms(original.rooms)
{
    work_hours = original.get_work_hours();
}

std::vector<Patient*> MedicalWorker::get_patients() const
{
    return patients;
}

std::vector<CovidHospitalRoom> MedicalWorker::get_rooms() const
{
    return rooms;
}

void MedicalWorker::add_patient(Patient* patient)
{
    patients.push_back(patient);
}

void MedicalWorker::add_room(CovidHospitalRoom& room)
{
    rooms.emplace_back(room);
}

void MedicalWorker::delete_patient(Patient* patient)
{
    patients.erase(std::remove(patients.begin(),
                                patients.end(),
                                patient),
                    patients.end());
}

void MedicalWorker::delete_room(CovidHospitalRoom& room)
{
    rooms.erase(std::remove(rooms.begin(),
                            rooms.end(),
                            room),
                rooms.end());
}

MedicalWorker& MedicalWorker::operator=(const MedicalWorker& original)
{
    name = original.name;
    surname = original.surname;
    position = original.position;
    id = original.id;
    salary = original.salary;
    permission_level = original.permission_level;
    patients = original.get_patients();
    rooms = original.get_rooms();
    return *this;
}

bool MedicalWorker::operator>(const MedicalWorker& other) const noexcept
{
    return patients.size() > other.get_patients().size();
}
bool MedicalWorker::operator<(const MedicalWorker& other) const noexcept
{
    return  !(*this > other);
}
bool MedicalWorker::operator>=(const MedicalWorker& other) const noexcept
{
    return patients.size() >= other.get_patients().size();
}
bool MedicalWorker::operator<=(const MedicalWorker& other) const noexcept
{
    return  !(*this >= other);
}
