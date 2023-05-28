#include "Test_Casualty_department.hpp"
#include "../Hospital/Rooms/casualty_department.hpp"
#include "../Hospital/Humans/Patient.hpp"
#include <cassert>

void Tests_Casualty_Department::test_add_item()
{
    CasualtyDepartment room(1, 100);
    Equipment equip{Name::respirator};
    room.add_item(equip, 10);
    assert(room.get_items_list().size() == 1);
    std::cout<<"casualty_department_test_add_item - passed"<<std::endl;
}

void Tests_Casualty_Department::test_remove_item()
{
    CasualtyDepartment room(1, 100);
    Equipment equip{Name::respirator};
    room.add_item(equip, 10);
    room.remove_item(equip, 1);
    auto got = room.get_items_list().find(equip);
    assert(got->second == 9);
    std::cout<<"casualty_department_test_remove_item - passed"<<std::endl;
}

void Tests_Casualty_Department::test_add_patient_stable()
{
    CasualtyDepartment room(1, 100);
    Patient patient("Jan", "Kowalski", "12312312312");
    Patient::Health health{Patient::Health::stable};
    patient.set_Health(health);
    room.add_patient_stable(&patient);
    assert(room.get_stable_size() == 1);
    std::cout<<"casualty_department_test_add_patient_stable - passed"<<std::endl;
}

void Tests_Casualty_Department::test_add_patient_critical()
{
    CasualtyDepartment room(1, 100);
    Patient patient("Jan", "Kowalski", "12312312312");
    Patient::Health health{Patient::Health::critical};
    patient.set_Health(health);
    room.add_patient_critical(&patient);
    assert(room.get_critical_size() == 1);
    std::cout<<"casualty_department_test_add_patient_critical - passed"<<std::endl;
}

void Tests_Casualty_Department::test_pop_patient_stable()
{
    CasualtyDepartment room(1, 100);
    Patient patient("Jan", "Kowalski", "12312312312");
    Patient::Health health{Patient::Health::stable};
    patient.set_Health(health);
    room.add_patient_stable(&patient);
    if(room.pop_patient_stable() == &patient)
        std::cout<<"casualty_department_test_pop_patient_stable - passed"<<std::endl;
}

void Tests_Casualty_Department::test_pop_patient_critical()
{
    CasualtyDepartment room(1, 100);
    Patient patient("Jan", "Kowalski", "12312312312");
    Patient::Health health{Patient::Health::critical};
    patient.set_Health(health);
    room.add_patient_critical(&patient);
    if(room.pop_patient_critical() == &patient)
        std::cout<<"casualty_department_test_pop_patient_critical - passed"<<std::endl;
}

void Tests_Casualty_Department::test_remove_patient_stable()
{
    CasualtyDepartment room(1, 100);
    Patient patient("Jan", "Kowalski", "12312312312");
    Patient::Health health{Patient::Health::stable};
    patient.set_Health(health);
    room.add_patient_stable(&patient);
    room.remove_patient_stable();
    assert(room.get_stable_size() == 0);
    std::cout<<"casualty_department_test_remove_patient_stable - passed"<<std::endl;
}

void Tests_Casualty_Department::test_remove_patient_critical()
{
    CasualtyDepartment room(1, 100);
    Patient patient("Jan", "Kowalski", "12312312312");
    Patient::Health health{Patient::Health::critical};
    patient.set_Health(health);
    room.add_patient_critical(&patient);
    room.remove_patient_critical();
    assert(room.get_critical_size() == 0);
    std::cout<<"casualty_department_test_remove_patient_critical - passed"<<std::endl;
}