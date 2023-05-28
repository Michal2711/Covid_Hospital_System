#ifndef ADD_MEDICAL_WORKER
#define ADD_MEDICAL_WORKER

#include <iostream>
#include <vector>
#include "Worker.hpp"

class Patient;
class CovidHospitalRoom;

using namespace std;

class MedicalWorker: public Worker
{
    protected:
        std::vector<Patient*> patients;
        std::vector<CovidHospitalRoom> rooms;

    public:
        MedicalWorker(const string& name, const string& surname, const string& pesel);
        MedicalWorker(const string& name, const string& surname, const string& pesel, const Worker_positions& position);
        ~MedicalWorker()=default;
        MedicalWorker(const MedicalWorker& original);

        std::vector<Patient*> get_patients() const;
        std::vector<CovidHospitalRoom> get_rooms() const;

        void add_patient(Patient* patient);
        void add_room(CovidHospitalRoom& room);

        void delete_patient(Patient* patient);
        void delete_room(CovidHospitalRoom& room);

        void copy_fields(const MedicalWorker& original);

        MedicalWorker& operator=(const MedicalWorker& original);
        bool operator>(const MedicalWorker& other) const noexcept;
        bool operator<(const MedicalWorker& other) const noexcept;
        bool operator>=(const MedicalWorker& other) const noexcept;
        bool operator<=(const MedicalWorker& other) const noexcept;
};

#endif