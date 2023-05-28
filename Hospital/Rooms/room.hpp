#ifndef ADD_ROOM
#define ADD_ROOM
#include <vector>
#include <unordered_map>
#include "../Utilities/Equipment.hpp"

class Room
{
    protected:
    int room_number{};
    std::unordered_map <Equipment, int, Hash> items;
    public:
    Room() = default;
    Room(int number)
    {
        room_number = number;
    };
    Room(int number, std::unordered_map <Equipment, int, Hash> items)
    {
        room_number = number;
        this->items = items;
        };
    virtual ~Room() = default;
    virtual void set_room_number(int new_number) = 0;
    virtual int get_room_number() const = 0;
    virtual void add_item(Equipment item, int quantity) = 0;
    virtual void remove_item(Equipment const& item, int quantity) = 0;
    virtual std::unordered_map <Equipment, int, Hash> const& get_items_list() const = 0;
};

#endif
