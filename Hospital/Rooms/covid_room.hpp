#pragma once
#include "room.hpp"
#include "../Humans/Medical_worker.hpp"
#include "../Humans/Patient.hpp"
#include <iostream>

struct InvalidRoomSpecializationException : public std::exception {
    const char * what() const noexcept {
        return "Invalid medical room specialization";
    }
};

struct InvalidBedsNumberException : public std::exception {
    const char * what() const noexcept {
        return "Beds number must be positive.";
    }
};

struct RoomOverflowException : public std::exception {
    const char * what() const noexcept {
        return "There is more patients than beds in room.";
    }
};

enum class Condition_patients_in_room {
        stable, critical
    };

class Patient; // forward declaration

class CovidHospitalRoom: public Room
{
    private:
    int beds_number{};
    Condition_patients_in_room state;
    std::unordered_map <Equipment, int, Hash> items;
    std::vector<Patient> patients{};
    std::vector<MedicalWorker> doctors{};
    std::vector<MedicalWorker> nurses{};
    //oxygen pomps, ekg monitor, patients state
    //isolation suits, computers, desks, drips, respirators
    //pairs type of equipment, number

    public:
    CovidHospitalRoom(int room_number, Condition_patients_in_room state) noexcept;
    CovidHospitalRoom(CovidHospitalRoom const& other) noexcept; //copy constructor
    ~CovidHospitalRoom() noexcept; //destructor

    void swapData(CovidHospitalRoom &other) noexcept;

    int get_room_number() const noexcept;
    Condition_patients_in_room get_state() const;
    int getBedsNumber() const noexcept;
    int getPercentageOfFreeBeds() const;
    int getNumberOfFreeBeds() const;
    std::vector<Patient> getPatientsList() const noexcept;
    std::vector<MedicalWorker> getNursesList() const noexcept;
    std::vector<MedicalWorker> getDoctorsList() const noexcept;

    void checkBedsNumber() const;

    void setBedsNumber(int new_number);
    void set_state(Condition_patients_in_room new_state) noexcept;
    void setPatientsList(std::vector<Patient> const& list) noexcept;
    void setNursesList(std::vector<MedicalWorker> const list) noexcept;
    void setDoctorsList(std::vector<MedicalWorker> const list) noexcept;
    void set_room_number(int new_number) noexcept;


    void removePatient(Patient& patient);
    void removeDoctor(MedicalWorker& doctor) noexcept;
    void removeNurse(MedicalWorker& nurse) noexcept;

    void addPatient(Patient& patient) noexcept;
    void addDoctor(MedicalWorker& doctor) noexcept;
    void addNurse(MedicalWorker& nurse) noexcept;

    void add_item(Equipment item, int quantity) noexcept;
    void remove_item(Equipment const& item, int quantity) noexcept;
    std::unordered_map <Equipment, int, Hash> const& get_items_list() const noexcept;

    friend std::ostream& operator<<(std::ostream& os, CovidHospitalRoom const& room);
    CovidHospitalRoom& operator=(CovidHospitalRoom const& other); //assigment/copy operator
    bool operator==(CovidHospitalRoom const& other) const;
    bool operator!=(CovidHospitalRoom const& other) const;
    bool operator>(const CovidHospitalRoom& other) const;
    bool operator<(const CovidHospitalRoom& other) const;
    bool operator>=(const CovidHospitalRoom& other) const;
    bool operator<=(const CovidHospitalRoom& other) const;

    void printRoom() const noexcept;
};
