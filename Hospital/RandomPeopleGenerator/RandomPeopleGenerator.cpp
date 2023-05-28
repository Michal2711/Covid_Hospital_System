#include <fstream>
#include "RandomPeopleGenerator.hpp"
#include "../../include/single_include/nlohmann/json.hpp"
#include <iterator>
#include <algorithm>
#include <random>

using json = nlohmann::json;

RandomPeopleGenerator::RandomPeopleGenerator()
{
    get_pesels_list();
}

void RandomPeopleGenerator::get_pesels_list()
{
    std::ifstream database("Hospital/RandomPeopleGenerator/people.json", std::ifstream::in); // has to be relative path to file, otherwhise not working
    json json_people;
    if (database.is_open())
    {
        json_people = json::parse(database);
    }
    else
    {
        throw InvalidDataBaseFileException();
    }
    database.close();
    std::vector<json> pesels = json_people.at("people").get<std::vector<json>>();

    for (auto i = pesels.begin(); i != pesels.end(); ++i)
    {
        auto names = std::make_pair((*i).at("name"), (*i).at("surname"));
        people.insert(std::make_pair((*i).at("pesel"), names));
    }
}

/*
    Deleting from the end of vector is easier, because pointer to the first
    element won't change.
*/

std::vector<Patient*> RandomPeopleGenerator::get_patient(int number)
{
    std::vector<std::string> keys_to_delete{};
    std::vector<Patient*> patients{};
    for (auto i = people.begin(); i != people.end() && number > 0; i++)
    {
        Patient* temp = new Patient((*i).second.first, (*i).second.second, (*i).first);
        patients.emplace_back(temp);
        keys_to_delete.emplace_back((*i).first);
        number--;
    }
    for(auto key : keys_to_delete)
    {
        people.erase(key);
    }

    return patients;
}

std::vector<MedicalWorker*> RandomPeopleGenerator::get_medical_worker(int number)
{
    std::vector<std::string> keys_to_delete{};
    std::vector<MedicalWorker*> workers{};
    for (auto i = people.begin(); i != people.end() && number > 0; i++)
    {
        MedicalWorker* temp = new MedicalWorker((*i).second.first, (*i).second.second, (*i).first);
        if ((*temp).get_age() > threshold_age)
        {
            struct tm days; // sets random shifts for worker
            bool shift;
            std::random_device generator;
            for(int i=0; i<6; i++)
            {
                days.tm_wday = i;
                shift = static_cast<bool>(generator() % 2);
                (*temp).set_shift_day(days, shift);
            }
            workers.emplace_back(temp);
            keys_to_delete.emplace_back((*i).first);
            number--;
        }
    }
    for(auto key : keys_to_delete)
        {
            people.erase(key);
        }
    return workers;
}
