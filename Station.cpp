//
// Created by Mattia Toffanin on 29/12/20.
//

#include "Station.h"

using namespace std;

Station::~Station() {
    name.clear();
    ID = 0;
}


int Main_station::get_free_binary(Train *t) {
    if (t->getToward()) { //Controllo il verso del treno
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
    if (!standard_track[track] || track < 0 || track > 3) //Controllo se binario è pieno o
        throw EmptyTrack{};

    if (track < 0 || track > 3) //Controllo se binario è compreso tra 0 e 3
        throw InvalidTrack{};

    Train *ret = nullptr;
    standard_track[track] = nullptr; //Svuoto il binatio
    if (track < 2) { //Controllo se binario andata o ritorno
        if (!parcking1_stop.empty()) { //Controllo se parcheggio vuoto
            ret = parcking1_stop.front();
            stop_train(parcking1_stop.front()); //Fermo un treno in parcheggio
            parcking1_stop.pop_front();
        }
    } else {
        if (!parcking2_stop.empty()) {
            ret = parcking2_stop.front();
            stop_train(parcking2_stop.front());
            parcking2_stop.pop_front();
        }
    }
    return ret;
}

void Main_station::print() const {
    cout << "type: " << get_type() << ", name: " << get_name() << ", id: " << get_id() << ", distance: "
         << get_distance() << endl << "standard tracks: "
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

Main_station::~Main_station() {
    for (int i = 0; i < STANDARD_TRACK_LENGTH; ++i)
        standard_track[i] = nullptr; //Non distruggo i puntatori di Train perchè può essere che servano a qualcun altro
    parcking1_stop.clear(); //Clear pulisce solo la coda ma non distrugge i puntatori all'interno
    parcking2_stop.clear();
}


int Local_station::get_free_binary(Train *t) {
    RegionalTrain regional_train_to_compare; //Oggetto treno regionale per vedere se treno passato è regionale
    if (t->getType() == regional_train_to_compare.getType()) //Controllo il tipo di treno
        return Main_station::get_free_binary(t); //Se regionale allora è come se fosse una stazione principale

    if (t->getToward()) { //Se non regionale controlla il verso
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
    RegionalTrain regional_train_to_compare; //Oggetto treno regionale per vedere se treno passato è regionale
    if (t->getType() == regional_train_to_compare.getType()) //Controllo il tipo di treno
        return Main_station::stop_train(t); //Se regionale allora è come se fosse una stazione principale

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
    if (track < 0 || track > 5) //Controllo se binario è compreso tra 0 e 3
        throw InvalidTrack{};

    if (track <= 3) //Controllo il tipo di binario
        return Main_station::leave_train(track); //Se standard è come se fosse una stazione principale

    Train *ret = nullptr;
    if (track == 4) {
        if (!transit_track[0])
            throw EmptyTrack{};
        transit_track[0] = nullptr;
        if (!parcking1_transit.empty()) {
            ret = parcking1_transit.front();
            stop_train(parcking1_transit.front());
            parcking1_transit.pop_front();
        }
    } else if (track == 5) { //Inutile ma va bene così
        if (!transit_track[1])
            throw EmptyTrack{};
        transit_track[1] = nullptr;
        if (!parcking2_transit.empty()) {
            ret = parcking2_transit.front();
            stop_train(parcking2_transit.front());
            parcking2_transit.pop_front();
        }
    }
    return ret;
}

void Local_station::print() const {
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

Local_station::~Local_station() {
    for (int i = 0; i < TRANSIT_TRACK_LENGTH; ++i)
        transit_track[i] = nullptr; //Non distruggo i puntatori di Train perchè può essere che servano a qualcun altro
    parcking1_transit.clear(); //Clear pulisce solo la coda ma non distrugge i puntatori all'interno
    parcking2_transit.clear();
}