#pragma once
#include "room.hpp"
#include <iostream>

class Staff_room: public Room
{
public:
    enum class Profession{
        IT_worker, janitor
    } profession;
    Staff_room(int number, Profession profession);
    Staff_room(int number, std::unordered_map <Equipment, int, Hash> items, Profession profession);
    ~Staff_room()=default;
    void set_profession(Profession _profession);
    void set_room_number(int new_number);
    Profession get_profession();
    int get_room_number() const noexcept;
    void add_item(Equipment item, int quantity) noexcept;
    void remove_item(Equipment const& item, int quantity) noexcept;
    std::unordered_map <Equipment, int, Hash> const& get_items_list() const noexcept;

};

std::ostream& operator<<(std::ostream& os, Staff_room const*obj);
