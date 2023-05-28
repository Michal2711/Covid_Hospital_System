#ifndef ADD_TIMETABLE
#define ADD_TIMETABLE

#include <iostream>
#include <map>

class Timetable
{
    protected:
        std::map<std::string, bool> shifts = {
            {"mon", false},
            {"tue", false},
            {"wed", false},
            {"thu", false},
            {"fri", false},
            {"sat", false},
            {"sun", false},
        };

    public:
        Timetable(std::map<std::string, bool>_shifts);
        Timetable() = default;
        Timetable(const Timetable& original);
        ~Timetable() = default;

        void set_shift_day(tm day, bool shift);
        void set_shifts(std::map<std::string, bool>new_shifts);

        std::map<std::string, bool> get_shifts() const;
        bool get_shift_day(tm day);
        void print() const;

        std::string translate_day(int day_num);
        std::string translate_shift(bool shift) const;

        Timetable& operator=(const Timetable& original);
        bool operator==(const Timetable& other) const;
        bool operator!=(const Timetable& other) const;

    friend
        std::ostream& operator<< (std::ostream& os, const Timetable& timetable);
};

#endif