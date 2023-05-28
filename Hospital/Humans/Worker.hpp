#ifndef ADD_WORKER
#define ADD_WORKER

#include "Person.hpp"
#include <map>
#include "../Utilities/Timetable.hpp"

enum class Worker_positions {
    Doctor, Nurse, Janitor, IT_Worker
};

class Worker: public Person
{
    protected:
        int id;
        Worker_positions position;
        int salary = 0;
        int permission_level = 0;
        Timetable work_hours;


    public:
        Worker(const std::string& name, const std::string& surname, const std::string& pesel);
        Worker(const std::string& name, const std::string& surname, const std::string& pesel, const Worker_positions& position);
        ~Worker()=default;
        Worker(const Worker& original);

        // void set_id(int id);
        void set_position(Worker_positions position);
        void set_salary(int salary);
        void set_permission_level(int level);
        void set_shift_day(tm day, bool shift);
        void set_shifts(std::map<std::string, bool> new_shifts);

        // int get_id() const;
        Worker_positions get_position() const;
        int get_salary() const;
        int get_permission_level() const;
        Timetable get_work_hours() const;
        bool get_work_hours_day(tm day);

        bool check_if_in_work(tm day);
        void print_work_hours() const;

        void print() const;
        void copy_fields(const Worker& original);

        Worker& operator=(const Worker& original);
        // bool operator!=(const Worker& other) const;
        // bool operator==(const Worker& other) const;

    friend
    std::ostream& operator<<(std::ostream& os, const Worker& worker);
};

#endif