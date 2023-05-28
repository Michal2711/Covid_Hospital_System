#include "utility_room.hpp"


UtilityRoom::UtilityRoom(int number)
{
    this->room_number = number;
}

UtilityRoom::UtilityRoom(int number, std::unordered_map <Equipment, int, Hash> items)
{
    this->room_number = number;
    this->items = items;
}

void UtilityRoom::set_room_number(int new_number)
{
    this->room_number = new_number;
}

int UtilityRoom::get_room_number() const noexcept
{
    return this->room_number;
}

void UtilityRoom::add_item(Equipment item, int quantity) noexcept
{
    items.insert( std::pair<Equipment const, int>(item, quantity));

}

void UtilityRoom::remove_item(Equipment const& item, int quantity) noexcept
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

std::unordered_map <Equipment, int, Hash> const& UtilityRoom::get_items_list() const noexcept
{
    return items;
}
