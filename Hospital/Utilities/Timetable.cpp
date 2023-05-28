#include <iostream>
#include "Timetable.hpp"


Timetable::Timetable(std::map<std::string, bool>_shifts):
    shifts(_shifts)
{}

Timetable::Timetable(const Timetable& original):
    shifts(original.shifts)
{}

std::string Timetable::translate_day(int day_num)
{
    switch (day_num)
    {
        case 0: return "mon";
        case 1: return "tue";
        case 2: return "wed";
        case 3: return "thu";
        case 4: return "fri";
        case 5: return "sat";
        case 6: return "sun";
    }
    return "";
}

void Timetable::set_shift_day(tm day, bool shift)
{
    shifts[this->translate_day(day.tm_wday)] = shift;
}

void Timetable::set_shifts(std::map<std::string, bool>new_shifts)
{
    shifts = new_shifts;
}

std::map<std::string, bool> Timetable::get_shifts() const
{
    return shifts;
}

bool Timetable::get_shift_day(tm day)
{
    switch (day.tm_wday)
    {
        case 0: return shifts["mon"];
        case 1: return shifts["tue"];
        case 2: return shifts["wed"];
        case 3: return shifts["thu"];
        case 4: return shifts["fri"];
        case 5: return shifts["sat"];
        case 6: return shifts["sun"];
    }
    return false;
}

void Timetable::print() const
{
    std::cout << *this;
}

std::string Timetable::translate_shift(bool shift) const
{
    if(shift) return "0:00 - 12:00";
    return "12:00 - 24:00";
}

Timetable& Timetable::operator=(const Timetable& original)
{
    shifts = original.get_shifts();
    return *this;
}

bool Timetable::operator==(const Timetable& other) const
{
    return shifts == other.get_shifts();
}

bool Timetable::operator!=(const Timetable& other) const
{
    return !(*this == other);
}

std::ostream& operator<<(std::ostream& os, const Timetable& timetable)
{
    std::map<std::string, bool> shifts = timetable.get_shifts();
    os << "Poniedziałek: " << timetable.translate_shift(shifts["mon"]) << std::endl;
    os << "Wtorek: " << timetable.translate_shift(shifts["tue"]) << std::endl;
    os << "Środa: " << timetable.translate_shift(shifts["wed"]) << std::endl;
    os << "Czwartek: " << timetable.translate_shift(shifts["thu"]) << std::endl;
    os << "Piątek: " << timetable.translate_shift(shifts["fri"]) << std::endl;
    os << "Sobota: " << timetable.translate_shift(shifts["sat"]) << std::endl;
    os << "Niedziela: " << timetable.translate_shift(shifts["sun"]) << std::endl;
    return os;
}