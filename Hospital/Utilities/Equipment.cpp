#include "Equipment.hpp"
#define INSERT_ELEMENT(p) strings[p] = #p

Equipment::Equipment(Name name)
{
    this->name = name;
    this->set_list();
}

void Equipment::set_list()
{
    if (strings.size() == 0){
        INSERT_ELEMENT(Name::respirator);
        INSERT_ELEMENT(Name::EKG);
        INSERT_ELEMENT(Name::mobile_disinfection_station);
        INSERT_ELEMENT(Name::oxygen_pomps);
        INSERT_ELEMENT(Name::computer);
        INSERT_ELEMENT(Name::desk);
        INSERT_ELEMENT(Name::drip);
        INSERT_ELEMENT(Name::chair);
        INSERT_ELEMENT(Name::district_heating_substation);
    }
}

void Equipment::set_name( Name new_name )
{
    name = new_name;
}


Name Equipment::get_name() const
{
    return name;
}

std::map<Name, std::string> Equipment::get_strings() const
{
    return strings;
}

bool Equipment::operator==(const Equipment& other) const
{
    return ( name == other.get_name() );
}


bool Equipment::operator!=(const Equipment& other) const
{
    return !(*this == other );
}


std::ostream& operator<<(std::ostream& out, Equipment const& value)
{
    std::map<Name, std::string> str = value.get_strings();
    return out << str[value.get_name()];
}


std::size_t Hash::operator()(Equipment const& _equipment) const noexcept
{
    return static_cast<std::underlying_type_t<Name>>(_equipment.get_name()); // simple hashing function, linear
}

#undef INSERT_ELEMENT