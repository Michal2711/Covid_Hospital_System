#include "Simulation.hpp"
#include <fstream>
#include <list>
#include <iostream>
#include <chrono>
#include <thread>
#include "../Hospital/Humans/Worker.hpp"
#include "../Hospital/Utilities/Equipment.hpp"
#include "../Hospital/Rooms/staff_room.hpp"

Simulation::~Simulation()
{
    for(auto person : generated_medics)
    {
        delete person;
    }
    for (auto person : generated_patients)
    {
        delete person;
    }
}

void Simulation::open_file(std::string path)
{
    std::fstream file_to_read(path, std::ifstream::in);
    if(file_to_read.is_open())
    {

        nlohmann::json data;
        size_t dot = path.find(".");
        std::string name_file = path.substr(0, dot);
        // file_to_read >> data;
        data = nlohmann::json::parse(file_to_read);
        if ( name_file == "parameters")
            read_parameters_from_file(data);
    }
    else
    {
    throw InvalidParametersFileException();
    }
}

void Simulation::read_parameters_from_file(nlohmann::json data)
{
    number_of_covid_rooms = data.at("data").at("covid_rooms").at("number_of_rooms").get<int>();
    number_of_doctors = data.at("data").at("covid_rooms").at("number_of_doctors").get<int>();
    number_of_nurses = data.at("data").at("covid_rooms").at("number_of_nurses").get<int>();
    number_of_stable = data.at("data").at("covid_rooms").at("number_of_stable").get<int>();
    number_of_critical = number_of_covid_rooms - number_of_stable;
    number_of_patients = data.at("data").at("patients").get<int>();
    number_of_actions = data.at("data").at("number_of_actions").get<int>();
    number_of_patient_in_casualty_department = data.at("data").at("number_of_patients_in_casualty_department").get<int>();
    number_of_utility_rooms = data.at("data").at("number_of_utility_rooms").get<int>();
    number_of_stable_EKG = data.at("data").at("equipments").at("stable_covid_room").at("number_of_stable_EKG").get<int>();
    number_of_stable_mds = data.at("data").at("equipments").at("stable_covid_room").at("number_of_stable_mds").get<int>();
    number_of_stable_oxygen_pomps = data.at("data").at("equipments").at("stable_covid_room").at("number_of_stable_oxygen_pomps").get<int>();
    number_of_stable_comp = data.at("data").at("equipments").at("stable_covid_room").at("number_of_stable_comp").get<int>();
    number_of_stable_desk = data.at("data").at("equipments").at("stable_covid_room").at("number_of_stable_desk").get<int>();
    number_of_critical_drip = data.at("data").at("equipments").at("stable_covid_room").at("number_of_stable_drip").get<int>();
    number_of_stable_chair = data.at("data").at("equipments").at("stable_covid_room").at("number_of_stable_chair").get<int>();
    number_of_critical_respirator = data.at("data").at("equipments").at("critical_covid_room").at("number_of_critical_respirator").get<int>();
    number_of_critical_EKG = data.at("data").at("equipments").at("critical_covid_room").at("number_of_critical_EKG").get<int>();
    number_of_critical_mds = data.at("data").at("equipments").at("critical_covid_room").at("number_of_critical_mds").get<int>();
    number_of_critical_oxygen_pomps = data.at("data").at("equipments").at("critical_covid_room").at("number_of_critical_oxygen_pomps").get<int>();
    number_of_critical_comp = data.at("data").at("equipments").at("critical_covid_room").at("number_of_critical_comp").get<int>();
    number_of_critical_desk = data.at("data").at("equipments").at("critical_covid_room").at("number_of_critical_desk").get<int>();
    number_of_critical_drip = data.at("data").at("equipments").at("critical_covid_room").at("number_of_critical_drip").get<int>();
    number_of_critical_chair = data.at("data").at("equipments").at("critical_covid_room").at("number_of_critical_chair").get<int>();
    number_of_casualty_d_mds = data.at("data").at("equipments").at("casualty_department").at("number_of_casualty_d_mds").get<int>();
    number_of_casualty_d_comp = data.at("data").at("equipments").at("casualty_department").at("number_of_casualty_d_comp").get<int>();
    number_of_casualty_d_desk = data.at("data").at("equipments").at("casualty_department").at("number_of_casualty_d_desk").get<int>();
    number_of_casualty_d_chair = data.at("data").at("equipments").at("casualty_department").at("number_of_casualty_d_chair").get<int>();
    number_of_staff_mds = data.at("data").at("equipments").at("staff_room").at("number_of_staff_mds").get<int>();
    number_of_staff_comp = data.at("data").at("equipments").at("staff_room").at("number_of_staff_comp").get<int>();
    number_of_staff_desk = data.at("data").at("equipments").at("staff_room").at("number_of_staff_desk").get<int>();
    number_of_staff_chair = data.at("data").at("equipments").at("staff_room").at("number_of_staff_chair").get<int>();
    number_of_dhs = data.at("data").at("equipments").at("utility_room").at("number_of_dhs").get<int>();
}

void Simulation::create_hospital()
{
    covid = Hospital("Stadion", "Warszawa");
    RandomPeopleGenerator random_people;
    for(int i = 0; i < number_of_critical; i++)
    {
        CovidHospitalRoom room_to_add = CovidHospitalRoom(200+i, Condition_patients_in_room::critical);
        room_to_add.add_item(Name::respirator, number_of_critical_respirator);
        room_to_add.add_item(Name::EKG, number_of_critical_EKG);
        room_to_add.add_item(Name::mobile_disinfection_station, number_of_critical_mds);
        room_to_add.add_item(Name::computer, number_of_critical_comp);
        room_to_add.add_item(Name::desk, number_of_critical_desk);
        room_to_add.add_item(Name::drip, number_of_critical_drip);
        room_to_add.add_item(Name::chair, number_of_critical_chair);
        covid.add_medical_room(room_to_add);
    }
    for(int i = 0; i < number_of_stable; i++)
    {
        CovidHospitalRoom room_to_add = CovidHospitalRoom(100+i, Condition_patients_in_room::stable);
        room_to_add.add_item(Name::EKG, number_of_stable_EKG);
        room_to_add.add_item(Name::mobile_disinfection_station, number_of_stable_mds);
        room_to_add.add_item(Name::oxygen_pomps, number_of_stable_oxygen_pomps);
        room_to_add.add_item(Name::computer, number_of_stable_comp);
        room_to_add.add_item(Name::desk, number_of_staff_desk);
        room_to_add.add_item(Name::drip, number_of_stable_desk);
        room_to_add.add_item(Name::chair, number_of_stable_chair);
        covid.add_medical_room(room_to_add);

    }
    covid.set_casualty_department(number_of_patient_in_casualty_department,
                                    number_of_casualty_d_mds,
                                    number_of_casualty_d_comp,
                                    number_of_casualty_d_desk,
                                    number_of_casualty_d_chair);


    add_doctors(number_of_doctors);
    add_nurses(number_of_nurses);
    add_patients(number_of_patients);

    Staff_room s_room_to_add = Staff_room(2, Staff_room::Profession::janitor);
    Staff_room s_room_to_add2 = Staff_room(3, Staff_room::Profession::IT_worker);
    s_room_to_add.add_item(Name::mobile_disinfection_station, number_of_staff_mds);
    s_room_to_add.add_item(Name::computer, number_of_staff_comp);
    s_room_to_add.add_item(Name::desk, number_of_staff_desk);
    s_room_to_add.add_item(Name::chair, number_of_staff_chair);
    s_room_to_add2.add_item(Name::mobile_disinfection_station, number_of_staff_mds);
    s_room_to_add2.add_item(Name::computer, number_of_staff_comp);
    s_room_to_add2.add_item(Name::desk, number_of_staff_desk);
    s_room_to_add2.add_item(Name::chair, number_of_staff_chair);
    covid.add_staff_room(s_room_to_add);
    covid.add_staff_room(s_room_to_add2);

    UtilityRoom ut_room = UtilityRoom(4);
    ut_room.add_item(Name::district_heating_substation, number_of_dhs);
    covid.add_utility_room(ut_room);

    covid.accept_patients_stable(covid.casualty_department.get_critical_size());
    covid.accept_patients_critical(covid.casualty_department.get_stable_size());

}

void Simulation::run_simulation()
{
    // losowe:
    // dodanie kilku pacjentow do izby przyjęć
    // wyzdrowienie pacjenta
    // pogorszenie się stanu pacjenta
    // umrzycie pacjenta
    // przyjęcie pracownika do pracy
    // zwolnienie pracownika
    Patient patient_to_heal = Patient("a", "a", "12312312312");
    Patient patient_to_get_worst = Patient("b", "b" , "78978978978");
    int action{};
    int amount{};
    int max_patient_flow = 3; // defines how many patients can be moved between rooms in hospital
    for ( int i = 0; i < number_of_actions; i++)
    {
        // stałe:
        // przyjęcie pacjentów do szpitala
        // zaszczepienie pacjentó
        covid.accept_patients_critical(max_patient_flow);
        covid.accept_patients_stable(max_patient_flow);
        action = static_cast<int>(generator() % 100 + 1);
        std::cout << "Day:\t" << i + 1 << std::endl;

        if ( action >=1 && action <= 35 )
        {
            std::cout << "Action: Add patients" << std::endl;
            // dodanie pacjentów - 35%
            amount = static_cast<int>(generator() % 5 + 5);
            add_patients(amount);
        }
        else if (action >= 36 && action <=50)
        {
            std::cout << "Action: health improve" << std::endl;
            //polepszenie stanu zdrowia - 15%
            int number_critical = covid.list_of_patients_critical.size();
            if ( number_critical != 0)
            {
                amount = static_cast<int>(generator() % static_cast<int>((number_critical/10)+1) + 1);
                std::cout<<amount<<" patient(s) healed from critical to stable:"<<std::endl;
                for ( int j = 0; j<amount; j++)
                {
                    patient_to_heal = *(covid.list_of_patients_critical[j]);
                    patient_to_heal.set_Health(Patient::Health::stable);
                    std::cout<<patient_to_heal<<std::endl;
                    covid.refresh(&patient_to_heal);
                }
            }
        }
        else if (action >= 51 && action <=65)
        {
            std::cout << "Action: full recover" << std::endl;
            // wyzdrowienie - 15%
            int number_stable = covid.list_of_patients_stable.size();
            if ( number_stable != 0)
            {
                amount = static_cast<int>(generator() % static_cast<int>((number_stable/20)+1) + 1);
                std::cout<<amount<<" patient(s) healed from stable to healthy:"<<std::endl;
                for ( int j = 0; j<amount; j++)
                {
                    patient_to_heal = *(covid.list_of_patients_stable[j]);
                    patient_to_heal.set_Health(Patient::Health::healthy);
                    std::cout<<patient_to_heal<<std::endl;
                    covid.refresh(&patient_to_heal);
                }
            }
        }
        else if ( action >= 66 && action <= 70)
        {
            std::cout << "Action: Death" << std::endl;
            //smierc - 5%
            int number_critical = covid.list_of_patients_critical.size();
            int number_stable = covid.list_of_patients_stable.size();
            int state_to_kill = static_cast<int>(generator() % 11 + 1);
            if ( state_to_kill>=1 && state_to_kill <= 10 && number_critical != 0)
            {
                Patient patient_to_kill = *(covid.list_of_patients_critical[0]);
                std::cout<<"One critical patient was killed by covid:"<<std::endl;
                std::cout<<patient_to_kill<<std::endl;
                patient_to_kill.set_Health(Patient::Health::dead);
                covid.refresh(&patient_to_kill);
            }
            if ( state_to_kill == 11 && number_stable != 0)
            {
                Patient patient_to_kill = *(covid.list_of_patients_stable[0]);
                std::cout<<"One stable patient was killed by covid:"<<std::endl;
                std::cout<<patient_to_kill<<std::endl;
                patient_to_kill.set_Health(Patient::Health::dead);
                covid.refresh(&patient_to_kill);
            }
        }
        else if ( action >= 71 && action <= 80)
        {
            std::cout << "Action: Health detorioration" << std::endl;
            //pogorszenie sie stanu zdrowia - 10%
            int number_stable = covid.list_of_patients_stable.size();
            if ( number_stable != 0)
            {
                amount = static_cast<int>(generator() % static_cast<int>((number_stable/15)+1) + 1);
                std::cout<<amount<<" patient(s) got worst from stable to critical:"<<std::endl;
                for ( int j = 0; j<amount; j++)
                {
                    patient_to_get_worst = *(covid.list_of_patients_stable[j]);
                    std::cout<<patient_to_get_worst<<std::endl;
                    patient_to_get_worst.set_Health(Patient::Health::critical);
                    covid.refresh(&patient_to_get_worst);
                }
            }
        }
        else if ( action >= 81 && action <= 88)
        {
            std::cout << "Action: Add doctors" << std::endl;
            //przyjecie lekarza - 8%
            add_doctors(1);
        }
        else if (action >= 89 && action <= 100)
        {
            std::cout << "Action: Add nurses" << std::endl;
            // przyjecie pielegniarki - 12%
            add_nurses(1);
        }
        std::this_thread::sleep_for(std::chrono::seconds(10));
    }
    print_summary();
}

void Simulation::print_summary()
{
    std::vector<CovidHospitalRoom> rooms = covid.get_medical_rooms();
    for (auto room : rooms)
    {
        std::cout <<"\n"<< room << std::endl;
        for(auto doctor : room.getDoctorsList())
        {
            std::cout << "Doctor:\n" << std::endl;
            std::cout << doctor;
            Timetable hours = doctor.get_work_hours();
            std::cout << hours << std::endl;
            for(auto patient : doctor.get_patients())
            {
                std::cout << doctor.get_surname() << " patient:"<<std::endl;
                std::cout << *patient << std::endl;
            }
        }

        std::cout<<"Nurses in room: "<<std::endl;
        for(auto nurse: room.getNursesList())
        {
            std::cout<<"Nurse "<<nurse<<std::endl;
        }

        std::cout << "Items in room" << std::endl;
        for (auto eq: room.get_items_list())
        {
            std::cout<<eq.first<<" : "<<eq.second<<"\t";
        }
        std::cout<<std::endl;
        std::this_thread::sleep_for(std::chrono::seconds(10));
    }
}

void Simulation::generaiting_random_health(Patient& patient)
{
    int health;
    health = static_cast<int>(generator() % 2);
    Patient::Health health_enum = static_cast<Patient::Health>(health);
    patient.set_Health(health_enum);
}

void Simulation::add_patients(int amount_patients)
{
    std::vector<Patient*> patients = random_people.get_patient(amount_patients);
    std::cout<<patients.size()<<" new patients"<<std::endl;
    for (auto patient: patients)
    {
        generated_patients.push_back(patient);
        int health;
        health = static_cast<int>(generator() % 2);
        Patient::Health health_enum = static_cast<Patient::Health>(health);
        (*patient).set_Health(health_enum);
        covid.add_patient(patient);
        std::cout<<"New patient:\n"<<*patient<<std::endl;
    }
}

void Simulation::add_doctors(int amount_doctors)
{
    std::vector<MedicalWorker*> doctors = random_people.get_medical_worker(amount_doctors);
    std::cout<<doctors.size()<<" new employees"<<std::endl;
    for (auto doctor: doctors)
    {
        generated_medics.push_back(doctor);
        (*doctor).set_position(Worker_positions::Doctor);

        covid.add_employmee(doctor);
        std::cout<<"New employee - doctor:\n"<<*doctor<<std::endl;
    }
}

void Simulation::add_nurses(int amount_nurses)
{
    std::vector<MedicalWorker*> nurses = random_people.get_medical_worker(amount_nurses);
    std::cout<<nurses.size()<<" new employees"<<std::endl;
    for (auto nurse: nurses)
    {
        generated_medics.push_back(nurse);
        (*nurse).set_position(Worker_positions::Nurse);
        covid.add_employmee(nurse);
        std::cout<<"New employee - Nurse:\n" << *nurse << std::endl;
    }
}