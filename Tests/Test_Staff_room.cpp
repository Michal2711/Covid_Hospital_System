#include "Test_Staff_room.hpp"
#include "../Hospital/Rooms/staff_room.hpp"
#include <cassert>

void Tests_Staff_Room::test_add_item()
{
    Staff_room room(1, Staff_room::Profession::janitor);
    Equipment equip{Name::respirator};
    room.add_item(equip, 10);
    assert(room.get_items_list().size() == 1);
    std::cout<<"staff_room_add_item - passed"<<std::endl;
}

void Tests_Staff_Room::test_remove_item()
{
    Staff_room room(1, Staff_room::Profession::janitor);
    Equipment equip{Name::respirator};
    room.add_item(equip, 10);
    room.remove_item(equip, 5);
    assert(room.get_items_list().size() == 1);
    room.remove_item(equip, 5);
    assert(room.get_items_list().size() == 0);
    std::cout<<"staff_room_remove_item - passed"<<std::endl;
}