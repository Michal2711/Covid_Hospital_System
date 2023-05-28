#pragma once
#include "room.hpp"
#include <queue>
#include "../Humans/Patient.hpp"

class CasualtyDepartment : public Room
{
protected:
    //std::priority_queue<Patient> patients;
    std::queue<Patient*> patients_critical;
    std::queue<Patient*> patients_stable;
    int max_patients_number{};
public:
    CasualtyDepartment() = default;
    CasualtyDepartment(int number, int max_patients_number);
    void set_room_number(int new_number);
    void set_max_patients_number(int new_number);
    size_t get_critical_size() const noexcept;
    size_t get_stable_size() const noexcept;

    std::queue<Patient*> getPatientsStableList() const noexcept;

    int get_room_number() const;
    int get_max_patients_number() const;
    void add_item(Equipment item, int quantity) noexcept;
    void remove_item(Equipment const& item, int quantity) noexcept;
    unordered_map <Equipment, int, Hash> const& get_items_list() const;
    void add_patient_stable(Patient* patient);
    void add_patient_critical(Patient* patient);
    Patient* pop_patient_stable();
    Patient* pop_patient_critical();
    void remove_patient_stable();
    void remove_patient_critical();

};
