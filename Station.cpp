//
// Created by Mattia Toffanin on 29/12/20.
//

#include "Station.h"


int Main_station::get_free_binary(Train *t) {
    if (t->getToward()) {
        if (!standard_track[0])
            return 0;
        if (!standard_track[1])
            return 1;
        return -1;
    } else {
        if (!standard_track[2])
            return 2;
        if (!standard_track[3])
            return 3;
        return -2;
    }
}

int Main_station::stop_train(Train *t) {
    switch (get_free_binary(t)) {
        case -2:
            parcking2.push_back(t);
            break;
        case -1:
            parcking1.push_back(t);
            break;
        case 0:
            standard_track[0] = t;
            break;
        case 1:
            standard_track[1] = t;
            break;
        case 2:
            standard_track[2] = t;
            break;
        case 3:
            standard_track[3] = t;
            break;
    }
    return get_free_binary(t);
}

Train *Main_station::leave_train(int track) {
    if (!standard_track[track] || track < 0 || track > 3)
        throw;

    Train *ret = standard_track[track];
    standard_track[track] = nullptr;

    if (track < 2)
        if (!parcking1.empty()) {
            stop_train(parcking1.front());
            parcking1.pop_front();
        } else if (!parcking2.empty()) {
            stop_train(parcking2.front());
            parcking2.pop_front();
        }

    return ret;
}
