#ifndef ADD_TEST_PERSON
#define ADD_TEST_PERSON

class Tests
{
public:
    Tests() = default;
    ~Tests() = default;

    static void test_create_person();
    static void test_set_names();
    static void test_calculate_sex();
    static void test_calculate_birth_date();
    static void test_create_person_invalid_pesel_lenght();
    };

#endif
