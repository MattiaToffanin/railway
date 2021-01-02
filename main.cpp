#include <iostream>
#include "Station.h"

using namespace std;


int main() {
    Local_station s("Roma", 1234);
    s.print();
    cout << endl;
    Train t1(1, true, "SUPER VELOCE", 0);
    Train t2(2, true, "VELOCE", 0);
    Train t3(3, true, "VELOCE", 0);
    Train t4(4, true, "REGIONALE", 0);
    Train t5(5, true, "REGIONALE", 0);
    Train t6(6, true, "REGIONALE", 0);


    s.stop_train(&t1);
    s.stop_train(&t2);
    s.stop_train(&t3);
    s.stop_train(&t4);
    s.stop_train(&t5);
    s.stop_train(&t6);

    s.print();





    /*

    s.print();
    cout << endl;

    s.leave_train(1);
    s.print();
    cout << endl;
    s.leave_train(1);
    s.print();
    cout << endl;*/




    return 0;
}