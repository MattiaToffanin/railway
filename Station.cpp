//
// Created by Mattia Toffanin on 29/12/20.
//

/*
 * !!!!!!IMPORTANTE!!!!!!
 * Stavo pensando che si potrebbe usare un intero dentro il treno per individuare la posizione in cui si trova,
 * visto che stop_train di Station restituisce un intero e leave_train riceve un intero.
 */
#include "Station.h"

using namespace std;

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
            parcking2_stop.push_back(t);
            break;
        case -1:
            parcking1_stop.push_back(t);
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

    if (track < 2) {
        if (!parcking1_stop.empty()) {
            stop_train(parcking1_stop.front());
            parcking1_stop.pop_front();
        }
    } else {
        if (!parcking2_stop.empty()) {
            stop_train(parcking2_stop.front());
            parcking2_stop.pop_front();
        }
    }
    return ret;
}

void Main_station::print() {
    cout << "type: " << get_type() << ", name: " << get_name() << ", id: " << get_id() << endl << "standard tracks: "
         << endl;
    for (Train *t: standard_track)
        if (t)
            t->print();
        else
            cout << "nullptr" << endl;
    cout << "stop parking: ->" << endl;
    for (Train *t: parcking1_stop)
        t->print();
    cout << "stop parking: <-" << endl;
    for (Train *t: parcking2_stop)
        t->print();
}


void Local_station::print() {
    Main_station::print();
    cout << "transit track: " << endl;
    for (Train *t: transit_track)
        if (t)
            t->print();
        else
            cout << "nullptr" << endl;
    cout << "transit parking: ->" << endl;
    for (Train *t: parcking1_transit)
        t->print();
    cout << "transit parking: <-" << endl;
    for (Train *t: parcking2_transit)
        t->print();

}

int Local_station::get_free_binary(Train *t) {
    if (t->getType() == "13RegionalTrain")
        return Main_station::get_free_binary(t);

    if (t->getToward()) {
        if (!transit_track[0])
            return 4;
        return -4;
    } else {
        if (!transit_track[1])
            return 5;
        return -5;
    }
}

int Local_station::stop_train(Train *t) {
    if (t->getType() == "13RegionalTrain")
        return Main_station::stop_train(t);

    switch (get_free_binary(t)) {
        case -5:
            parcking2_transit.push_back(t);
            break;
        case -4:
            parcking1_transit.push_back(t);
            break;
        case 4:
            transit_track[0] = t;
            break;
        case 5:
            transit_track[1] = t;
            break;
    }
    return get_free_binary(t);
}

Train *Local_station::leave_train(int track) {
    if (track < 0 || track > 5)
        throw;

    if (track <= 3)
        return Main_station::leave_train(track);

    Train *ret = nullptr;

    if (track == 4) {
        if (!transit_track[0])
            throw;
        ret = transit_track[0];
        transit_track[0] = nullptr;
        if (!parcking1_transit.empty()) {
            stop_train(parcking1_transit.front());
            parcking1_transit.pop_front();
        }
    } else if (track == 5) { //Inutile ma va bene così
        if (!transit_track[1])
            throw;
        ret = transit_track[1];
        transit_track[1] = nullptr;
        if (!parcking2_transit.empty()) {
            stop_train(parcking2_transit.front());
            parcking2_transit.pop_front();
        }
    }
    return ret;
}



