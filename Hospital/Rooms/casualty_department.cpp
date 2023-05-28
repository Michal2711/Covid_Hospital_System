#include "casualty_department.hpp"

CasualtyDepartment::CasualtyDepartment(int room_number, int max_patients_number)
{
    this->max_patients_number = max_patients_number;
    this->room_number = room_number;
}


void CasualtyDepartment::set_room_number(int new_room_number)
{
    room_number = new_room_number;
}

void CasualtyDepartment::set_max_patients_number(int new_number)
{
    max_patients_number = new_number;
}

int CasualtyDepartment::get_room_number() const
{
    return room_number;
}

int CasualtyDepartment::get_max_patients_number() const
{
    return max_patients_number;
}

void CasualtyDepartment::add_item(Equipment item, int quantity) noexcept
{
    items.insert( std::pair<Equipment const, int>(item, quantity));
}

void CasualtyDepartment::remove_item(Equipment const& item, int quantity) noexcept
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

std::unordered_map <Equipment, int, Hash> const& CasualtyDepartment::get_items_list() const
{
    return items;
}

void CasualtyDepartment::add_patient_stable(Patient* patient)
{
    patients_stable.push(patient);

}

void CasualtyDepartment::add_patient_critical(Patient* patient)
{
    patients_critical.push(patient);
}

void CasualtyDepartment::remove_patient_stable()
{
    patients_stable.pop();
}

void CasualtyDepartment::remove_patient_critical()
{
    patients_critical.pop();
}

//remove refrences if it wont work

Patient* CasualtyDepartment::pop_patient_stable()
{
    Patient* person = patients_stable.front();
    patients_stable.pop();
    return person;
}

Patient* CasualtyDepartment::pop_patient_critical()
{
    Patient* person = patients_critical.front();
    patients_critical.pop();
    return person;
}

size_t CasualtyDepartment::get_critical_size() const noexcept
{
    return patients_critical.size();
}

size_t CasualtyDepartment::get_stable_size() const noexcept
{
    return patients_stable.size();
}

std::queue<Patient*> CasualtyDepartment::getPatientsStableList() const noexcept
{
    return patients_stable;
}