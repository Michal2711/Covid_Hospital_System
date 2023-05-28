#include "Person.hpp"
#include <vector>

Person::Person(std::string name_, std::string surname_, std::string pesel_)
// name(name_), surname(surname_), pesel(pesel_)
{
    name = name_;
    surname = surname_;
    pesel = pesel_;
    check_pesel();
    calculate_sex();
    calculate_birth_date();
    calculate_age();
}

Person::Person(Person const& original)
{
    operator=(original);
}

void Person::check_pesel()
{
    //due to simplicity of testing now is checking only a length of pesel
    if (pesel.length() != 11)
    {
        throw InvalidPeselException();
    }
}

/*

Days of months and monts are itareted from 0

*/

void Person::calculate_birth_date()
{
    int year{}, month{}, day{};

    year = 10 * (static_cast<int>(pesel[0]) - 48); // minus zero ascii, its converting char to numeric value 0 -> 48
    year += (static_cast<int>(pesel[1]) - 48);

    month = 10 * (static_cast<int>(pesel[2]) - 48);
    month += (static_cast<int>(pesel[3]) - 48);

    day = 10 * (static_cast<int>(pesel[4]) - 48);
    day += (static_cast<int>(pesel[5]) - 48);

    if(month > 0 && month < 13)
    {
        year += 1900;
    }
    else if (month > 20 && month < 33)
    {
        year += 2000;
        month -= 20;
    }

    bool leap_year = false;
    if (year % 4 == 0)
    {
        if (year % 100 == 0)
        {
            if (year % 400 == 0)
            {
                leap_year = true;
            }
            else
            {
                leap_year = false;
            }
        }
        else
        {
            leap_year = true;
        }
    }

    std::vector<int> days_in_months = {31, 28, 31, 30, 31, 30,
                                        31, 31, 30, 31, 30, 31};

    int sum_days = 0;

    for(int i = 0; i < 12; i++)
    {
        // std::cout << days_in_months.size() << " " << i<<std::endl;
        sum_days += days_in_months[i];
    }
    sum_days += day;

    if (leap_year && month > 2)
    {
        sum_days++;
    }

    birthdate.tm_year = year;
    birthdate.tm_mon = month - 1;
    birthdate.tm_yday = day - 1;
}

void Person::calculate_age()
{
    time_t now = time(0);
    struct tm *current_date = localtime(&now);


    if(birthdate.tm_mon > 1+current_date->tm_mon ||
        (birthdate.tm_mon == 1+current_date->tm_mon &&
        birthdate.tm_mday > current_date->tm_mday))
    {
        age = 1900+current_date->tm_year - birthdate.tm_year - 1;
    }
    else
        age = 1900+current_date->tm_year - birthdate.tm_year;

}

void Person::calculate_sex()
{
    (pesel[9] % 2 == 1) ? sex = "Male" : sex = "Female";
}

void Person::set_name(std::string name)
{
    this->name = name;
}

void Person::set_surname(std::string surname)
{
    this->surname = surname;
}

std::string Person::get_name() const
{
    return name;
}
std::string Person::get_surname() const
{
    return surname;
}

std::string Person::get_pesel() const
{
    return pesel;
}

std::string Person::get_sex() const
{
    return sex;
}

tm Person::get_birthdate() const
{
    return birthdate;
}

int Person::get_age() const
{
    return age;
}

// void Person::swap(const Person& original)
// {
//     name = original.get_name();
//     surname = original.get_surname();
//     pesel = original.get_pesel();
//     calculate_birth_date();
//     calculate_sex();
// }

std::ostream& operator<<(std::ostream& os, Person const& obj)
{
    os << "name: " << obj.get_name() << "\t" << "surname: "<< obj.get_surname() << "\t" << "pesel: " << obj.get_pesel()<<"\t"<<"age: "<<obj.get_age()<<std::endl;
    return os;
}

Person& Person::operator=(const Person& original)
{
    name = original.name;
    surname = original.surname;
    pesel = original.pesel;
    calculate_birth_date();
    calculate_sex();
    return *this;

}


bool Person::operator!=(const Person& other) const
{
    return !(*this == other);
}

bool Person::operator==(const Person& other) const
{
    return pesel == other.get_pesel();
}
