#include <iostream>
#include "Train.h"
#include "Station.h"

using namespace std;


int main() {
    Local_station s("Roma", 1234);
    s.print();
    cout << endl;

    RegionalTrain t1{1, true};
    RegionalTrain t2{2, true};
    RegionalTrain t3{3, true};
    HighSpeedTrain t4{4, true};
    HighSpeedTrain t5{5, true};
    HighSpeedTrain t6{6, true};

    s.stop_train(&t1);
    s.stop_train(&t2);
    s.stop_train(&t3);
    s.stop_train(&t4);
    s.stop_train(&t5);
    s.stop_train(&t6);

    s.print();
    cout << endl;

    s.leave_train(0);
    s.leave_train(4);

    s.print();






    return 0;
}
