#pragma once
#include <cstddef>
#include <string>
#include <map>


enum class Name
{
    respirator, EKG, mobile_disinfection_station,
    oxygen_pomps, computer, desk, drip, chair,
    district_heating_substation
};


class Equipment
{
protected:
    Name name;

public:
    void set_name( Name new_name );
    std::map<Name, std::string> strings;

    Name get_name() const;
    std::map<Name, std::string> get_strings() const;
    void set_list();

    Equipment()=default;
    Equipment(Name name);
    ~Equipment()=default;

    bool operator==(const Equipment& other) const;
    bool operator!=(const Equipment& other) const;
    friend std::ostream& operator<<(std::ostream& out, Equipment const& value);
};


struct Hash
{
    std::size_t operator()(Equipment const& _equipment) const noexcept;
};
