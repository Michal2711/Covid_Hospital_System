#include "Test_Patient.hpp"
#include "../Hospital/Humans/Patient.hpp"

using namespace std;

    Tests_Patient::Tests_Patient()
    {}

    Tests_Patient::~Tests_Patient()
    {}

    // Tests_Patient if patients are equal
    void Tests_Patient::test_equal()
    {
        Patient patient1("Jan", "Kowalski", "12312312312");
        Patient patient2("Jan", "Kowalski", "34534534534");
        if(patient1 == patient2) cout<<"Equal patients"<<endl;
        else cout<<"patients_test_eqaul - passed"<<endl;
    }

    void Tests_Patient::test_assignment()
    {
        Patient patient1("Jan", "Kowalski", "12312312312");
        Patient patient2("Piotr", "Nowak", "34534534534");
        patient1 = patient2;
        if(patient1 == patient2) cout<<"OK"<<endl;
        else cout<<"patients_test_assignment - passed"<<endl;
    }

    void Tests_Patient::test_bigger()
    {
        Patient patient1("Jan", "Kowalski", "12312312312");
        Patient patient2("Piotr", "Nowak", "34534534534");
        patient1.set_Health(Patient::Health::stable);
        patient2.set_Health(Patient::Health::critical);
        if (patient2 > patient1) cout<<"> OK"<<endl;
        else cout<<"patients_test_> - passed"<<endl;

    }

    void Tests_Patient::test_copy_constructor()
    {
        Patient patient1("Jan", "Kowalski", "12312312312");
        Patient patient2(patient1);
        if(patient1 == patient2) cout<<"patients_test_constructor - passed"<<endl;
        else cout<<"patients_constructor - not passed"<<endl;
    }

    // Tests_Patient if print patient works
    void Tests_Patient::test_print()
    {
        Patient patient1("Jan", "Kowalski", "12312312312");
        cout<<patient1<<" print - passed"<<endl;

    }

    // Tests_Patient adding vaccine
    void Tests_Patient::test_vaccine_add(string const& new_vaccine)
    {
        Patient patient1("Jan", "Kowalski", "12312312312");
        if(patient1.add_vaccine(new_vaccine)) cout<<"patients_test_vaccine_added - passed"<<endl;
        else cout<<"vaccine not added"<<endl;

    }

    // Tests_Patient removing vaccine
    void Tests_Patient::test_vaccine_remove(string const& vaccine_to_remove)
    {
        Patient patient1("Jan", "Kowalski", "12312312312");
        if(patient1.add_vaccine(vaccine_to_remove))
        {
            if(patient1.remove_vaccine(vaccine_to_remove)) cout<<"patients_test_vaccine_removed - passed"<<endl;
            else cout<<"vaccine not removed"<<endl;
        }

    }
