#pragma once
#include "../Humans/Patient.hpp"
#include "../Hospital.hpp"
#include <random>
#include"../Humans/Worker.hpp"
#include <tuple>
#include <exception>

struct InvalidDataBaseFileException : public std::exception {
    const char * what() const noexcept {
        return "Cannot access database file.";
    }
};

class RandomPeopleGenerator
{
private:
    std::unordered_map<std::string, std::pair<std::string, std::string>> people;
    void get_pesels_list(); // gets vector of json objects from people.json
/*
in order to reset people database
run python script from /script
*/
public:
    int const threshold_age = 25;
    std::random_device generator;
    RandomPeopleGenerator();
    ~RandomPeopleGenerator() = default;

    std::vector<Patient*> get_patient(int number);
    std::vector<MedicalWorker*> get_medical_worker(int number);
};
