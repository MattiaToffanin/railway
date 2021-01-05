#include <iostream>
#include "Train.h"
#include "Station.h"

using namespace std;


int main() {
    Local_station s("Roma", 1234);
    s.print();
    cout << endl;

    RegionalTrain t1{123, false};
    t1.print();

    /*

    s.stop_train(&t1);
    s.stop_train(&t2);
    s.stop_train(&t3);
    s.stop_train(&t4);
    s.stop_train(&t5);
    s.stop_train(&t6);

    s.print();

    s.leave_train(1);

    s.leave_train(4);
    s.leave_train(4);
    s.leave_train(4);

    cout << endl;

    s.print();

   */




    return 0;
}
