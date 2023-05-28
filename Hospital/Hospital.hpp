#ifndef HOSPITAL_INCLUDED
#define HOSPITAL_INCLUDED
#include <iostream>
#include <vector>
#include <queue>
#include "Humans/Patient.hpp"
#include "Rooms/room.hpp"
#include "Rooms/staff_room.hpp"
#include "Rooms/covid_room.hpp"
#include "Utilities/Equipment.hpp"
#include "Rooms/casualty_department.hpp"
#include "Rooms/utility_room.hpp"

class Hospital
{
protected:
    std::string name{};
    std::string city{};
    enum class Administrative_unit {
       provincial_hospital, community_hospital
    } administrative_unit;
    int number_of_beds;
    int number_of_occupied_beds;
    int number_of_repispirators;
    int number_of_occupied_respirators;
    std::queue<MedicalWorker*> doctors_queue;
    std::queue<MedicalWorker*> nurse_queue;


public:
    CasualtyDepartment casualty_department;
    vector<Patient*> list_of_patients;
    vector<Patient*> list_of_patients_stable;
    vector<Patient*> list_of_patients_critical;
    vector<Patient*> list_of_killed_patients_by_covid;
    vector<Staff_room> staff_rooms;
    vector<UtilityRoom> utility_rooms;
    vector<CovidHospitalRoom> medical_rooms_stable;
    vector<CovidHospitalRoom> medical_rooms_critical;
    //override comp to compare with free beds number
    vector<MedicalWorker*> list_of_doctors;
    vector<MedicalWorker*> list_of_nurse;

    Hospital()=default;
    Hospital(const std::string& name, const std::string& city);
    ~Hospital()=default;

    void set_name( std::string& new_name );
    void set_number_of_beds( int& new_number );
    void set_number_of_occupied_beds( int& new_number );
    void set_number_of_respirators( int& new_number );
    void set_number_of_occupied_respirators( int& new_number );
    void set_casualty_department( int& max_patient_list,
                                    int mds, int comp, int desk, int chair);

    std::string get_name() const;
    std::string get_city() const;
    Administrative_unit get_admin_unit() const;
    int get_number_of_beds() const;
    int get_number_of_occupied_beds() const;
    int get_number_of_respirators() const;
    int get_number_of_occupied_respirators() const;
    vector<CovidHospitalRoom> get_medical_rooms() const;

    void add_patient(Patient* new_patient);
    void add_patient_to_stable_list(Patient* new_patient);
    void add_patient_to_critical_list(Patient* new_patient);
    void add_dead_patient(Patient* new_patient);
    void add_employmee(MedicalWorker* new_employee);
    void add_doctor(MedicalWorker* new_doctor);
    void add_nurse(MedicalWorker* new_nurse);
    void add_medical_room(CovidHospitalRoom& new_room);
    void add_staff_room(Staff_room const& new_room);
    void add_utility_room(UtilityRoom const& new_room);

    void remove_patient_from_covid_room(CovidHospitalRoom* room, std::vector<CovidHospitalRoom>& medical_room);
    void remove_patient(Patient* patient_to_remove);
    void change_patient_room(Patient* patient, std::vector<CovidHospitalRoom>& medical_room);
    void move_patient_to_medical_room(Patient* patient);
    void remove_doctor(MedicalWorker const* doctor_to_remove);
    void remove_nurse(MedicalWorker const* nurse_to_remove);
    void refresh(Patient* patient) noexcept; // moves patient to stable if he was healed from critical, restores rooms heaps
    void refresh_rooms() noexcept;
    void assign_doctor_to_patient(Patient* patient);
    void assign_doctor_to_nurse(Patient* patient);
    void accept_patients_critical(int amount);
    void accept_patients_stable(int amount);

    MedicalWorker* find_doctor(MedicalWorker* doctor_to_add);

    Hospital& operator=(Hospital const& _hospital)=default;
    bool operator!=(const Hospital& other) const;
    bool operator==(const Hospital& other) const;
    Hospital(Hospital const& _hospital)=default;
};

std::ostream& operator<<(std::ostream& os, Hospital const& obj);

#endif
