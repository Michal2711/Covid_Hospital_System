#pragma once
#include <random>
#include "../include/single_include/nlohmann/json.hpp"
#include "../Hospital/Hospital.hpp"
#include "../Hospital/Humans/Patient.hpp"
#include "../Hospital/RandomPeopleGenerator/RandomPeopleGenerator.hpp"


struct InvalidParametersFileException : public std::exception {
    const char * what() const noexcept {
        return "parameters.json cannot be accessed.";
    }
};

enum class Action {
    add_patient_to_casualty_department,
    patient_recovery,
    patient_get_worse,
    patient_dead,
    worker_get_hire,
    worker_get_fired
};

class Simulation
{
private:
    Hospital covid;
    RandomPeopleGenerator random_people;
    int number_of_covid_rooms = 0;
    int number_of_doctors = 0;
    int number_of_nurses = 0;
    int number_of_stable = 0;
    int number_of_critical = 0;
    int number_of_patients = 0;
    int number_of_actions = 0;
    int number_of_staff_rooms = 0;
    int number_of_patient_in_casualty_department = 0;
    int number_of_utility_rooms = 0;
    int number_of_days = 0;
    int number_of_stable_EKG = 0;
    int number_of_stable_mds = 0;
    int number_of_stable_oxygen_pomps = 0;
    int number_of_stable_comp = 0;
    int number_of_stable_desk = 0;
    int number_of_stable_drip = 0;
    int number_of_stable_chair = 0;
    int number_of_critical_respirator;
    int number_of_critical_EKG = 0;
    int number_of_critical_mds = 0;
    int number_of_critical_oxygen_pomps = 0;
    int number_of_critical_comp = 0;
    int number_of_critical_desk = 0;
    int number_of_critical_drip = 0;
    int number_of_critical_chair = 0;
    int number_of_casualty_d_mds = 0;
    int number_of_casualty_d_comp = 0;
    int number_of_casualty_d_desk = 0;
    int number_of_casualty_d_chair = 0;
    int number_of_staff_mds = 0;
    int number_of_staff_comp = 0;
    int number_of_staff_desk = 0;
    int number_of_staff_chair = 0;
    int number_of_dhs = 0;
    std::random_device generator;
    std::vector<MedicalWorker*> generated_medics{};
    std::vector<Patient*> generated_patients{};

public:
    Simulation() = default;
    ~Simulation();

    void open_file(std::string path);
    // bool read_patients_from_file(nlohmann::json data);
    void read_parameters_from_file(nlohmann::json data);

    void generaiting_random_health(Patient& patient);
    void add_patients(int amount_patients);
    void add_doctors(int amount_doctors);
    void add_nurses(int amount_nurses);

    void create_hospital();
    void run_simulation();
    void print_summary();

};