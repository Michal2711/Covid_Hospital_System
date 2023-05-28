#include "Test_Person.hpp"
#include "../Hospital/Humans/Person.hpp"
#include <cassert>

void Tests::test_create_person()
{
    Person person = Person("Wiktor", "Pytleski", "12312312312");
    std::string name = "Wiktor";
    std::string surname = "Pytleski";
    assert(person.get_name() == name && person.get_surname() == surname);
    std::cout << "test_create_person - passed" << std::endl;
}
void Tests::test_set_names()
{
    Person person = Person("Wiktor", "Pytleski", "12312312312");
    person.set_name("Olgierd");
    std::string name = "Olgierd";
    std::string surname = "Pytleski";
    assert(person.get_name() == name);
    std::cout << "test_set_names - passed" << std::endl;
}
void Tests::test_calculate_sex()
{
    Person person = Person("Wiktor", "Pytleski", "12312312312");
    std::string sex = "Male";
    assert(person.get_sex() == sex);
    std::cout << "test_calculate_sex - passed" << std::endl;
}
void Tests::test_calculate_birth_date()
{
    Person person = Person("Wiktor", "Pytleski", "01241031231"); // 10/04/2001
    struct tm mock_date;
    mock_date.tm_year = 2001;
    mock_date.tm_mon = 3;
    mock_date.tm_yday = 9;
    assert(person.get_birthdate().tm_mon == mock_date.tm_mon
            && person.get_birthdate().tm_year == mock_date.tm_year
            && person.get_birthdate().tm_yday == mock_date.tm_yday);
    std::cout << "test_calculate_birth_date - passed" << std::endl;
}

void Tests::test_create_person_invalid_pesel_lenght()
{
    bool test_result = false;
    try
    {
        Person person = Person("Wiktor", "Pytleski", "123123123");
    }
    catch(const InvalidPeselException& e)
    {
        test_result = true;
        std::cout << "test_create_person_invalid_pesel_length" << std::endl;
    }
    assert(test_result);
}
