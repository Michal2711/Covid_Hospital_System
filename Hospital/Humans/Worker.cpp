// #include <iostream>
#include "Worker.hpp"
#include "../Rooms/room.hpp"
#include "Patient.hpp"


Worker::Worker(const std::string& name, const std::string& surname,
                const std::string& pesel, const Worker_positions& position):
    Person(name, surname, pesel),
        position(position), salary(0), permission_level(0)
{}

Worker::Worker(const std::string& name, const std::string& surname,
                const std::string& pesel):
    Person(name, surname, pesel),
        salary(0), permission_level(0)
{}

Worker::Worker(const Worker& original):
    Person(original.name, original.surname, original.pesel)
{
    operator=(original);
}

void Worker::set_position(Worker_positions position)
{
    this->position = position;
}

void Worker::set_salary(int salary)
{
    this->salary = salary;
}

void Worker::set_permission_level(int level)
{
    permission_level = level;
}

void Worker::set_shift_day(tm day, bool shift)
{
    work_hours.set_shift_day(day, shift);
}

void Worker::set_shifts(std::map<std::string, bool> new_shifts)
{
    work_hours.set_shifts(new_shifts);
}

// int Worker::get_id() const
// {
//     return id;
// }

Worker_positions Worker::get_position() const
{
    return position;
}

int Worker::get_salary() const
{
    return salary;
}

int Worker::get_permission_level() const
{
    return permission_level;
}



Timetable Worker::get_work_hours() const
{
    return work_hours;
}

bool Worker::get_work_hours_day(tm day)
{
    return work_hours.get_shift_day(day);
}


bool Worker::check_if_in_work(tm day)
{
    bool shift = work_hours.get_shift_day(day); //true if shift is PM
    if (day.tm_hour < 12) return !shift;
    return shift;
}

void Worker::print() const
{
    std::cout << *this;
}

// void Worker::copy_fields(const Worker& original)
// {
//     id = original.get_id();
//     name = original.get_name();
//     surname = original.get_surname();
//     position = original.get_position();
//     salary = original.get_salary();
//     permission_level = original.get_permission_level();
//     // work_hours = original.get_work_hours();
// }

Worker& Worker::operator=(const Worker& original)
{
    name = original.name;
    surname = original.surname;
    pesel = original.pesel;
    age = original.age;
    id = original.age;
    position = original.position;
    salary = original.salary;
    permission_level = original.permission_level;
    // copy_fields(original);
    return *this;
}

// bool Worker::operator==(const Worker& other) const
// {
//     return pesel == other.get_pesel();
// }

// bool Worker::operator!=(const Worker& other) const
// {
//     return !(*this == other);
// }

std::ostream& operator<<(std::ostream& os, const Worker& worker)
{
    os << "name: " << worker.get_name() << "\t";
    os << "surname: " << worker.get_surname() << "\t";
    // os << "id: " << worker.get_id() << std::endl;
    os << "pesel: " << worker.get_pesel() << std::endl;
    return os;
}