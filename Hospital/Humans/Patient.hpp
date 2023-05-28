#ifndef PATIENT_INCLUDED
#define PATIENT_INCLUDED
#include <iostream>
#include <unordered_map>
#include <string>
#include "Person.hpp"
#include "../Rooms/covid_room.hpp"

using namespace std;

class CovidHospitalRoom; // forward declaration

// std::ostream& operator<<(std::ostream& out, const Patient::Health value){
//     static std::map<Patient::Health, std::string> strings;
//     if (strings.size() == 0){
// #define INSERT_ELEMENT(p) strings[p] = #p
//         INSERT_ELEMENT(Patient::Health::stable);
//         INSERT_ELEMENT(Patient::Health::critical);
//         INSERT_ELEMENT(Patient::Health::dead);
//         INSERT_ELEMENT(Patient::Health::healthy);
// #undef INSERT_ELEMENT
//     }

//     return out << strings[value];
// }

class Patient: public Person
{
public:
    unordered_map <string, bool> vaccine;
    enum class ID_doc {
        id_card, driving_license, student_id_card, passport
    } id_doc;
    CovidHospitalRoom* hospital_room; // has to be pointer because of initialization wihout room
    int bed;
    enum class Health {
        stable, critical, dead, healthy
    } health;
    bool if_respirator;
    MedicalWorker* doctor;
    MedicalWorker* nurse;

    // Patient()=default;
    Patient(const string& name, const string& surname, const string& pesel);
    ~Patient()=default;
    void set_age( int new_age );
    void set_ID_doc( ID_doc new_id_doc);
    void set_hospital_room( CovidHospitalRoom* new_hospital_room);
    void set_bed( int new_bed );
    void set_Health( Health new_health );
    void set_if_respirator( bool new_if_respirator );
    void set_doctor( MedicalWorker* new_doctor );
    void set_nurse( MedicalWorker* new_nurse );

    int get_age() const;
    ID_doc get_id_doc() const;
    CovidHospitalRoom* get_hospital_room() const;
    int get_bed() const;
    Health get_health() const;
    bool get_if_respirator() const;
    MedicalWorker* get_doctor() const;
    MedicalWorker* get_nurse() const;
    bool add_vaccine(string const& new_vaccine);
    bool remove_vaccine(string const& vaccine_to_remove);

    Patient& operator=(Patient const& _patient);
    bool operator>(const Patient& other) const;
    bool operator<(const Patient& other) const;
    bool operator>=(const Patient& other) const;
    bool operator<=(const Patient& other) const;
    Patient(Patient const& _patient);

};


#endif
