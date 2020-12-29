//
// Created by Mattia Toffanin on 29/12/20.
//
#include <string>
#include <iostream>
#include <deque>


#ifndef RAILWAY_STATION_H
#define RAILWAY_STATION_H

/**
 * Classe provvisoria di Train solo per debug
 */
class Train {
public:
    Train() {}

    Train(int id, bool toward, const std::string &type, int delay) : ID{id}, toward{toward}, type{type}, delay{delay} {}

    const bool &getToward() const { return toward; }

    const std::string &getType() const { return type; }

    int getId() const { return ID; }

private:
    int ID;
    bool toward; //true andata, false ritorno
    std::string type;
    int delay;
};


class Station {
public:

    virtual int
    get_free_binary(Train *t) = 0; //Restituisce il binario vuoto dove ci si può fermare (!!!Non usare se non necessario!!!)

    virtual int stop_train(Train *t) = 0; //Ferma il treno nel binario libero

    virtual Train *leave_train(int track) = 0; //Fa ripartire il treno dal binario inserito


    const std::string &get_name() const { return name; };

    int get_id() const { return ID; }

    Station(const Station &) = delete;

    Station &operator=(const Station &) = delete;

    virtual ~Station() {}

protected:
    explicit Station(const std::string &name, int id) : name{name}, ID{id} {}


private:
    std::string name;
    int ID;
};


class Main_station : public Station {
public:
    explicit Main_station(const std::string &name, int id) : Station(name, id), standard_track{} {}

    int get_free_binary(Train *t) override;

    int stop_train(Train *t) override;

    Train *leave_train(int track) override;

    /*
     * Classe di testing
     */
    void print() {
        std::cout << "name: " << get_name() << ", id: " << get_id() << std::endl << "tracks: " << std::endl;
        for (Train *t: standard_track)
            if (t)
                std::cout << t->getId() << ", " << t->getType() << ", "
                          << t->getToward() << std::endl;
            else
                std::cout << "nullptr" << std::endl;
        std::cout << "parking: " << std::endl;
        for (Train *t: parcking1)
            std::cout << t->getId() << ", " << t->getType() << ", " << t->getToward() << std::endl;
        for (Train *t: parcking2)
            std::cout << t->getId() << ", " << t->getType() << ", " << t->getToward() << std::endl;
    }


private:
    static const int standard_track_length = 4;
    Train *standard_track[standard_track_length]; //Binari 0,1: treni andata, Binari 2,3: treni ritorno
    std::deque<Train *> parcking1;
    std::deque<Train *> parcking2;
};


class Local_station : public Station {
public:
};


#endif //RAILWAY_STATION_H
