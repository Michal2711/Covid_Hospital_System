#include "Hospital.hpp"
#include <algorithm>
#include <iostream>
#include <queue>

Hospital::Hospital(const std::string& name, const std::string& city):
    name(name), city(city), number_of_beds(1000),
    number_of_occupied_beds(0), number_of_repispirators(1000),
    number_of_occupied_respirators(0)
{}

void Hospital::set_name( std::string& new_name )
{
    name = new_name;
}

void Hospital::set_number_of_beds( int& new_number )
{
    number_of_beds = new_number;
}

void Hospital::set_number_of_occupied_beds( int& new_number )
{
    number_of_occupied_beds = new_number;
}

void Hospital::set_number_of_respirators( int& new_number )
{
    number_of_repispirators = new_number;
}

void Hospital::set_number_of_occupied_respirators( int& new_number )
{
    number_of_occupied_respirators = new_number;
}

void Hospital::set_casualty_department( int& max_patient_list,
                                            int mds, int comp, int desk, int chair )
{
    casualty_department = CasualtyDepartment(1, max_patient_list);
    casualty_department.add_item(Name::mobile_disinfection_station, mds);
    casualty_department.add_item(Name::computer, comp);
    casualty_department.add_item(Name::desk, desk);
    casualty_department.add_item(Name::chair, chair);
}

std::string Hospital::get_name() const
{
    return name;
}

std::string Hospital::get_city() const
{
    return city;
}

Hospital::Administrative_unit Hospital::get_admin_unit() const
{
    return administrative_unit;
}

int Hospital::get_number_of_beds() const
{
    return number_of_beds;
}

int Hospital::get_number_of_occupied_beds() const
{
    return number_of_occupied_beds;
}

int Hospital::get_number_of_respirators() const
{
    return number_of_repispirators;
}

int Hospital::get_number_of_occupied_respirators() const
{
    return number_of_occupied_respirators;
}

vector<CovidHospitalRoom> Hospital::get_medical_rooms() const
{
    std::vector<CovidHospitalRoom> merged_rooms{};
    for (auto i = medical_rooms_critical.begin(); i != medical_rooms_critical.end(); i++ )
    {
        merged_rooms.push_back(*i);
    }
    for (auto i = medical_rooms_stable.begin(); i != medical_rooms_stable.end(); i++ )
    {
        merged_rooms.push_back(*i);
    }
    return merged_rooms;
}

void Hospital::add_patient(Patient* new_patient)
{
    if ( (*new_patient).health == Patient::Health::stable)
    {
        casualty_department.add_patient_stable(new_patient);
    }
    else if ( (*new_patient).health == Patient::Health::critical)
    {
        casualty_department.add_patient_critical(new_patient);
    }
    list_of_patients.push_back(new_patient);
    (*new_patient).set_hospital_room(nullptr);
}

void Hospital::add_patient_to_stable_list(Patient* new_patient)
{
    list_of_patients_stable.push_back(new_patient);
}

void Hospital::add_patient_to_critical_list(Patient* new_patient)
{
    list_of_patients_critical.push_back(new_patient);
}

void Hospital::add_employmee(MedicalWorker* new_employee)
{
    if ( new_employee->get_position() == Worker_positions::Doctor)
        add_doctor(new_employee);
    else if ( new_employee->get_position() == Worker_positions::Nurse)
        add_nurse(new_employee);
}

void Hospital::add_doctor(MedicalWorker* new_doctor)
{
    list_of_doctors.push_back(new_doctor);
    doctors_queue.push(new_doctor);
}

void Hospital::add_nurse(MedicalWorker* new_nurse)
{
    list_of_nurse.push_back(new_nurse);
    nurse_queue.push(new_nurse);
}

void Hospital::add_staff_room(Staff_room const& new_room)
{
    staff_rooms.push_back(new_room);
}

void Hospital::add_utility_room(UtilityRoom const& new_room)
{
    utility_rooms.push_back(new_room);
}

void Hospital::add_medical_room(CovidHospitalRoom& new_room)
{
    if (new_room.get_state() == Condition_patients_in_room::stable)
    {
        medical_rooms_stable.push_back(new_room);
        std::push_heap(medical_rooms_stable.begin(), medical_rooms_stable.end(), greater<CovidHospitalRoom>{});
    }
    else if (new_room.get_state() == Condition_patients_in_room::critical)
    {
        medical_rooms_critical.push_back(new_room);
        std::push_heap(medical_rooms_critical.begin(), medical_rooms_critical.end(), greater<CovidHospitalRoom>{});
    }
}

void remove_patient_from_list(vector<Patient*> &patient_list, Patient const* patient_to_remove)
{
    for(auto index = patient_list.begin(); index!=patient_list.end();)
    {
        if ( *index == patient_to_remove)
        {
            patient_list.erase(index);
            // return;  // has to be return because of reducing size of vector
        }
        else{
            index++;
        }
    }
}

void Hospital::remove_patient(Patient* patient_to_remove)
{
    remove_patient_from_list(list_of_patients, patient_to_remove);

    if ( (*patient_to_remove).health == Patient::Health::stable )
        remove_patient_from_list(list_of_patients_stable, patient_to_remove);

    else if ( (*patient_to_remove).health == Patient::Health::critical )
        remove_patient_from_list(list_of_patients_critical, patient_to_remove);

    if ( (*patient_to_remove).health == Patient::Health::dead )
        Hospital::add_dead_patient(patient_to_remove);

    (*patient_to_remove).get_doctor()->delete_patient(patient_to_remove);
    // patient_to_remove.get_nurse()->delete_patient(patient_to_remove);
    (*patient_to_remove).get_hospital_room()->removePatient(*patient_to_remove);
    (*patient_to_remove).set_hospital_room(nullptr);
}

void Hospital::remove_doctor(MedicalWorker const* doctor_to_remove)
{
    for(auto index = list_of_doctors.begin(); index!=list_of_doctors.end(); index++)
    {
        if ( *index == doctor_to_remove) list_of_doctors.erase(index);
    }
}

void Hospital::remove_nurse(MedicalWorker const* nurse_to_remove)
{
    for(auto index = list_of_nurse.begin(); index!=list_of_nurse.end(); index++)
    {
        if ( *index == nurse_to_remove) list_of_nurse.erase(index);
    }
}

void Hospital::add_dead_patient(Patient* new_patient)
{
    list_of_killed_patients_by_covid.push_back(new_patient);
}

bool Hospital::operator!=(const Hospital& other) const
{
    return !(*this == other);
}

void Hospital::refresh_rooms() noexcept
{
    std::make_heap(medical_rooms_stable.begin(), medical_rooms_stable.end(), greater<CovidHospitalRoom>{});
    std::make_heap(medical_rooms_critical.begin(), medical_rooms_critical.end(), greater<CovidHospitalRoom>{});
}

void add_patient_to_medical_room(Patient& patient, std::vector<CovidHospitalRoom>& medical_room)
{
    if(medical_room.back().getNumberOfFreeBeds() > 0)
    {
        std::cout << medical_room.back() << std::endl;
        // std::make_heap(medical_room.begin(), medical_room.end(), greater<CovidHospitalRoom>{});
        std::pop_heap(medical_room.begin(), medical_room.end(), greater<CovidHospitalRoom>{});
        patient.set_hospital_room(&(medical_room.back()));
        medical_room.back().addPatient(patient);
        std::push_heap(medical_room.begin(), medical_room.end(), greater<CovidHospitalRoom>{});
    }
    else
    {
        std::cout<<"Hospital is full. We can't take more patients."<<std::endl;
    }
}

void Hospital::move_patient_to_medical_room(Patient* patient)
{
    if((*patient).get_health() == Patient::Health::stable)
    {
        add_patient_to_medical_room(*patient, medical_rooms_stable);
        list_of_patients_stable.push_back(patient);
    }
    else if((*patient).get_health() == Patient::Health::critical)
    {
        add_patient_to_medical_room(*patient, medical_rooms_critical);
        list_of_patients_critical.push_back(patient);
    }
    assign_doctor_to_patient(patient);
    assign_doctor_to_nurse(patient);
}

void Hospital::change_patient_room(Patient* patient, std::vector<CovidHospitalRoom>& medical_room)
{
    if(medical_room.back().getNumberOfFreeBeds() > 0)
    {
        MedicalWorker* doctor;
        doctor = (*patient).get_doctor();

        MedicalWorker* nurse;
        nurse = (*patient).get_nurse();

        // delete old room from nurse and doctor
        CovidHospitalRoom* room_before;
        room_before = (*patient).get_hospital_room();
        doctor->delete_room(*room_before);
        nurse->delete_room(*room_before);

        // delete patient from old room
        remove_patient_from_covid_room(patient->get_hospital_room(), medical_room);

        // add patient to new medical room
        add_patient_to_medical_room(*patient, medical_room);

        // nurse and doctor add new room
        CovidHospitalRoom* room_after;
        room_after = (*patient).get_hospital_room();
        room_after->addDoctor(*doctor);
        room_after->addNurse(*nurse);
    }
    else
    {
        // skip_patient();
        return;
    }
}

void Hospital::remove_patient_from_covid_room(CovidHospitalRoom* room, std::vector<CovidHospitalRoom>& medical_room)
{
    medical_room.erase(std::remove(medical_room.begin(),
                                medical_room.end(),
                                *room),
                    medical_room.end());
}

void Hospital::refresh(Patient* patient) noexcept
{
    // patient will have his prev room saved but current state so only we have to check if he is to be removed from hospital
    Patient::Health state = (*patient).get_health();
    CovidHospitalRoom room = *((*patient).get_hospital_room()); //unpacking pointer
    room.removePatient(*patient);
    Condition_patients_in_room room_state = room.get_state(); //

    switch (state)
    {
    case Patient::Health::dead:
        list_of_killed_patients_by_covid.push_back(patient);
        remove_patient(patient);
        break;

    case Patient::Health::healthy:
        // list_of_convalescent_patients.push_back(patient);
        remove_patient(patient);
        break;

    case Patient::Health::critical:
        std::pop_heap(medical_rooms_critical.begin(), medical_rooms_critical.end(), greater<CovidHospitalRoom>{});
        change_patient_room(patient, medical_rooms_critical);
        add_patient_to_critical_list(patient);
        break;

    case Patient::Health::stable:
        std::pop_heap(medical_rooms_stable.begin(), medical_rooms_stable.end(), greater<CovidHospitalRoom>{});
        change_patient_room(patient, medical_rooms_stable);
        add_patient_to_stable_list(patient);
        break;

    default:
        break;
    }

    if(room_state == Condition_patients_in_room::stable)
    {
        remove_patient_from_list(list_of_patients_stable, patient);
    }
    if(room_state == Condition_patients_in_room::critical)
    {
        remove_patient_from_list(list_of_patients_critical, patient);
    }
}

// MedicalWorker* Hospital::find_doctor(MedicalWorker& doctor_to_add)
// {
//     for (auto i = list_of_doctors.begin(); i != list_of_doctors.end(); i++)
//     {
//         if (*i == doctor_to_add)
//         {
//             return &(*i);
//         }
//     }
// }

void Hospital::assign_doctor_to_patient(Patient* patient)
{
    MedicalWorker* doctor_to_add = doctors_queue.front();
    // MedicalWorker* doctor_to_assign = find_doctor(doctor_to_add);
    (*patient).set_doctor(doctor_to_add);
    doctor_to_add->add_patient(patient);
    (*patient).get_hospital_room()->addDoctor(*doctor_to_add);
    doctors_queue.push(doctor_to_add);
    doctors_queue.pop();
}

void Hospital::assign_doctor_to_nurse(Patient* patient)
{
    MedicalWorker* nurse_to_add = nurse_queue.front();
    (*patient).set_nurse(nurse_to_add);

    nurse_to_add->add_patient(patient);
    (*patient).get_hospital_room()->addNurse(*nurse_to_add);
    nurse_queue.push(nurse_to_add);
    nurse_queue.pop();
}

void Hospital::accept_patients_critical(int amount)
{
    for(int i=0; i<amount; i++)
    {
        if(casualty_department.get_critical_size()>0)
        {
            Patient* patient_to_add = casualty_department.pop_patient_critical();
            std::cout << "Patient popped from casualty: " << *patient_to_add << std::endl;
            move_patient_to_medical_room(patient_to_add);
        }
    }
}

void Hospital::accept_patients_stable(int amount)
{
    for(int i=0; i<amount; i++)
    {
        if(casualty_department.get_stable_size()>0)
        {
            Patient* patient_to_add = casualty_department.pop_patient_stable();
            std::cout << "Patient popped from casualty: " << *patient_to_add << std::endl;
            move_patient_to_medical_room(patient_to_add);
        }
    }
}

bool Hospital::operator==(const Hospital& other) const
{
    if ( name==other.get_name() && city == other.get_city() && administrative_unit == other.get_admin_unit())
    {
        return true;
    }
    return false;
}

std::ostream& operator<<(std::ostream& os, Hospital const& obj)
{
    os << obj.get_name() << " in " << obj.get_city();
    return os;
}
