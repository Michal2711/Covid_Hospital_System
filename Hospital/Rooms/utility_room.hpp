#pragma once
#include "room.hpp"

class UtilityRoom: public Room
{
public:
    UtilityRoom(int number);
    UtilityRoom(int number, std::unordered_map <Equipment, int, Hash> items);
    ~UtilityRoom()=default;

    void set_room_number(int new_number);
    int get_room_number() const noexcept;
    void add_item(Equipment item, int quantity) noexcept;
    void remove_item(Equipment const& item, int quantity) noexcept;
    std::unordered_map <Equipment, int, Hash> const& get_items_list() const noexcept;
};


