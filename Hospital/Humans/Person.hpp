#ifndef ADD_PERSON
#define ADD_PERSON
#include <iostream>
#include <exception>
#include <time.h>

struct InvalidPeselException : public std::exception {
    const char * what() const noexcept {
        return "Invalid PESEL number";
    }
};

class Person
{
    protected:
        std::string name{};
        std::string surname{};
        std::string pesel{};
        std::string sex{};
        struct tm birthdate;
        unsigned int age;
        void calculate_sex();
        void calculate_birth_date();
        void calculate_age();
        void check_pesel();
        // void swap(const Person& original);

    public:
        Person() = default;
        Person(std::string name, std::string surname, std::string pesel);
        Person(Person const& original);
        virtual ~Person() = default;

        void set_name(std::string name);
        void set_surname(std::string surname);

        std::string get_name() const;
        std::string get_surname() const;
        std::string get_pesel() const;
        std::string get_sex() const;
        tm get_birthdate() const;
        int get_age() const;

        Person& operator=(const Person& original);
        bool operator!=(const Person& other) const;
        bool operator==(const Person& other) const;
        friend std::ostream& operator<<(std::ostream& os, Person const& obj);
};



#endif
