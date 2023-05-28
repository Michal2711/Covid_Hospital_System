#include "Patient.hpp"
#include "../Rooms/room.hpp"

using namespace std;

Patient::Patient(const string& _name, const string& _surname, const string& _pesel):
    Person(_name, _surname, _pesel),
    id_doc(ID_doc::id_card), hospital_room(nullptr), bed(0),
    health(Health::stable), doctor(nullptr), nurse(0)
{
    check_pesel();
    calculate_sex();
    calculate_birth_date();
    calculate_age();
}

// setters
void Patient::set_age( int new_age )
{
    age = new_age;
}

void Patient::set_ID_doc( ID_doc new_id_doc )
{
    id_doc = new_id_doc;
}

void Patient::set_hospital_room ( CovidHospitalRoom* new_hospital_room )
{
    hospital_room = new_hospital_room;
}

void Patient::set_bed( int new_bed )
{
    bed = new_bed;
}

void Patient::set_Health( Health new_health )
{
    health = new_health;
}

void Patient::set_if_respirator( bool new_if_respirator )
{
    if_respirator = new_if_respirator;
}

void Patient::set_doctor( MedicalWorker* new_doctor )
{
    doctor = new_doctor;
}

void Patient::set_nurse( MedicalWorker* new_nurse )
{
    nurse = new_nurse;
}

// getters
int Patient::get_age() const
{
    return age;
}

Patient::ID_doc Patient::get_id_doc() const
{
    return id_doc;
}

CovidHospitalRoom* Patient::get_hospital_room() const
{
    return hospital_room;
}

int Patient::get_bed() const
{
    return bed;
}

Patient::Health Patient::get_health() const
{
    return health;
}

bool Patient::get_if_respirator() const
{
    return if_respirator;
}

MedicalWorker* Patient::get_doctor() const
{
    return doctor;
}

MedicalWorker* Patient::get_nurse() const
{
    return nurse;
}

// function to add vaccine
bool Patient::add_vaccine(string const& new_vaccine)
{
    pair<unordered_map<string, bool>::iterator, bool> result = vaccine.insert(
        pair<string const, bool>(new_vaccine, true)
    );
    return result.second;
}

// function to remove vaccine
bool Patient::remove_vaccine(string const& vaccine_to_remove)
{
    return vaccine.erase(vaccine_to_remove);
}

bool Patient::operator>(const Patient& other) const
{
    if ( health > other.get_health() )
    {
        return true;
    }
    return false;
}

bool Patient::operator<(const Patient& other) const
{
    if ( health < other.get_health() )
    {
        return true;
    }
    return false;
}

bool Patient::operator>=(const Patient& other) const
{
    if ( health >= other.get_health() )
    {
        return true;
    }
    return false;
}

bool Patient::operator<=(const Patient& other) const
{
    if ( health <= other.get_health() )
    {
        return true;
    }
    return false;
}

// overload =
Patient& Patient::operator=(Patient const& _patient)
{
    name = _patient.name;
    surname = _patient.surname;
    pesel = _patient.pesel;
    age = _patient.age;
    vaccine = _patient.vaccine;
    id_doc = _patient.id_doc;
    hospital_room = _patient.hospital_room;
    bed = _patient.bed;
    health = _patient.health;
    // if_respirator = _patient.if_respirator;
    doctor = _patient.doctor;
    nurse = _patient.nurse;

    return *this;
}

// copy constructor
Patient::Patient(Patient const& _patient):
    Person(_patient.name, _patient.surname, _patient.pesel),
    vaccine(_patient.vaccine), id_doc(_patient.id_doc),
    hospital_room(_patient.hospital_room), bed(_patient.bed),
    health(_patient.health), //if_respirator(_patient.if_respirator),
    doctor(_patient.doctor), nurse(_patient.nurse)
{}
