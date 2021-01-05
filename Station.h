//
// Created by Mattia Toffanin on 29/12/20.
//
#ifndef RAILWAY_STATION_H
#define RAILWAY_STATION_H
#include <string>
#include <iostream>
#include <deque>
#include "Train.h"

class Train;

/**
 * Classe provvisoria di Train solo per debug
 */

class Station {
public:
    virtual int stop_train(Train *t) = 0; //Ferma il treno nel binario libero

    virtual Train *leave_train(int track) = 0; //Fa ripartire il treno dal binario inserito

    virtual void print() = 0;

    const std::string &get_name() const { return name; };

    int get_id() const { return ID; }

    std::string get_type() { return typeid(*this).name(); };

    Station(const Station &) = delete;

    Station &operator=(const Station &) = delete;

    virtual ~Station() = default;

protected:
    explicit Station(const std::string &name, int id) : name{name}, ID{id} {}

    virtual int get_free_binary(Train *t) = 0; //Restituisce il binario vuoto dove ci si può fermare

private:
    std::string name;
    int ID;
};


class Main_station : public Station {
public:
    explicit Main_station(const std::string &name, int id) : Station(name, id), standard_track{} {}

    int stop_train(Train *t) override;

    Train *leave_train(int track) override;

    /*
     * Funzione di testing
     */
    void print() override;

    static const std::string TYPE;
protected:
    int get_free_binary(Train *t) override;


private:
    static const int STANDARD_TRACK_LENGTH = 4;
    Train *standard_track[STANDARD_TRACK_LENGTH]; //Binari 0,1: treni andata, Binari 2,3: treni ritorno
    std::deque<Train *> parcking1_stop;
    std::deque<Train *> parcking2_stop;
};


class Local_station : public Main_station {
public:
    explicit Local_station(const std::string &name, int id) : Main_station(name, id), transit_track{} {}

    int stop_train(Train *t) override;

    Train *leave_train(int track) override;

    /*
     * Funzione di testing
     */
    void print() override;

private:
    static const int transit_track_length = 2;
    Train *transit_track[transit_track_length]; //Binari 0,1: treni andata, Binari 2,3: treni ritorno

    int get_free_binary(Train *t) override;

    std::deque<Train *> parcking1_transit;
    std::deque<Train *> parcking2_transit;
};


#endif //RAILWAY_STATION_H