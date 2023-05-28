#include "staff_room.hpp"
#include <tuple>

Staff_room::Staff_room(int number, Profession profession)
{
    this->room_number = number;
    this->set_profession(profession);
}

void Staff_room::set_profession(Profession _profession)
{
    profession = _profession;
}

void Staff_room::set_room_number(int new_number)
{
    room_number = new_number;
}

Staff_room::Profession Staff_room::get_profession()
{
    return profession;
}

int Staff_room::get_room_number() const noexcept
{
    return room_number;
}

void Staff_room::add_item(Equipment item, int quantity) noexcept
{
    items.insert( std::pair<Equipment const, int>(item, quantity));
}

void Staff_room::remove_item(Equipment const& item, int quantity) noexcept
{
    auto itr = items.find(item);
    if (itr != items.end())
    {
        int new_quantity = itr->second - quantity;
        if (new_quantity < 1)
        {
            items.erase(item);
        }
        else
        {
            itr->second = new_quantity;
        }

    }
}

std::unordered_map <Equipment, int, Hash> const& Staff_room::get_items_list() const noexcept
{
    return items;
}