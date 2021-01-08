//
// Created by Mattia Toffanin on 29/12/20.
//
#ifndef RAILWAY_STATION_H
#define RAILWAY_STATION_H

#include <string>
#include <iostream>
#include <deque>
#include "Train.h"


class Station {
public:
    /**
     * Funzione membro che ferma o fa transitare il treno nel binario libero se libero, altrimenti lo parcheggia
     * @param t, il treno da fermare
     * @return intero che indica il binario di stop/transito o il parcheggio (vedi status di train)
     */
    virtual int stop_train(Train *t) = 0;

    /**
     * Funzione membro che fa ripartire il treno dal binario inserito
     * @param track, il binario da liberare
     * @return train che è partito
     */
    virtual Train *leave_train(int track) = 0;

    /**
     * Funzione membro che stampa la situazione della stazione
     */
    virtual void print() const = 0;

    /**
     * Getter di name
     * @return il nome della stazione
     */
    const std::string &get_name() const { return name; };

    /**
     * Getter di ID
     * @return l'identificativo della stazione
     */
    int get_id() const { return ID; }

    /**
     * Getter di distance
     * @return la distanza dall'origine
     */
    int get_distance() const { return distance; }

    /**
     * Funzione membro che restituisce il tipo di stazione
     * @return "13Local_station" se stazione locale, "12Main_station" se stazione principale
     */
    std::string get_type() const { return typeid(*this).name(); };

    /**
     * Costruttore di copia disabilitato
     */
    Station(const Station &) = delete;

    /**
     * Assegnamento di copia disabilitato
     * @return
     */
    Station &operator=(const Station &) = delete;

    /**
     * Distruttore
     */
    virtual ~Station();

protected:
    /**
     * Costruttore parametrico
     * @param name, il nome della stazione
     * @param id, l'identificativo della stazione
     * @param distance, la distanza dall'origine
     */
    explicit Station(const std::string &name, int id, int distance) : name{name}, ID{id}, distance{distance} {}

    /**
     * Funzione membro che controlla se fermare o far transitare il treno nel binario libero se libero, altrimenti se parcheggiarlo
     * @param t il treno da fermare
     * @return intero che indica il binario di stop/transito o il parcheggio (vedi status di train)
     */
    virtual int get_free_binary(Train *t) = 0;

private:
    std::string name; //Nome della stazione
    int ID; //Identificativo della stazione
    int distance; //Distanza dall'origine
};


class Main_station : public Station {
public:
    /**
     * Costruttore parametrico
     * @param name, il nome della stazione
     * @param id, l'identificativo della stazione
     * @param distance, la distanza dall'origine
     */
    explicit Main_station(const std::string &name, int id, int distance) : Station(name, id, distance),
                                                                           standard_track{} {}

    /**
     * Funzione membro che ferma o fa transitare il treno nel binario libero se libero, altrimenti lo parcheggia
     * @param t, il treno da fermare
     * @return intero che indica il binario di stop/transito o il parcheggio (vedi status di train)
     */
    int stop_train(Train *t) override;

    /**
     * Funzione membro che fa ripartire il treno dal binario inserito
     * @param track, il binario da liberare
     * @return train che è partito
     * */
    Train *leave_train(int track) override;

    /**
     * Funzione membro che stampa la situazione della stazione
     */
    void print() const override;

    /**
     * Distruttore
     */
    ~Main_station() override;

protected:
    /**
     * Funzione membro che controlla se fermare o far transitare il treno nel binario libero se libero, altrimenti se parcheggiarlo
     * @param t il treno da fermare
     * @return intero che indica il binario di stop/transito o il parcheggio (vedi status di train)
     */
    int get_free_binary(Train *t) override;

private:
    static const int STANDARD_TRACK_LENGTH = 4; //Lunghezza dell'array per i binari standard
    Train *standard_track[STANDARD_TRACK_LENGTH]; //Binari 0,1: treni andata, Binari 2,3: treni ritorno
    std::deque<Train *> parcking1_stop; //Coda per parcheggio di stop di andata
    std::deque<Train *> parcking2_stop; //Coda per parcheggio di stop di ritorno
};


class Local_station : public Main_station {
public:
    /**
     * Costruttore parametrico
     * @param name, il nome della stazione
     * @param id, l'identificativo della stazione
     * @param distance, la distanza dall'origine
     */
    explicit Local_station(const std::string &name, int id, int distance) : Main_station(name, id, distance),
                                                                            transit_track{} {}

    /**
     * Funzione membro che ferma il treno nel binario libero
     * @param t, il treno da fermare
     * @return intero che indica il binario di stop/transito o il parcheggio (vedi status di train)
     */
    int stop_train(Train *t) override;

    /**
     * Funzione membro che fa ripartire il treno dal binario inserito
     * @param track, il binario da liberare
     * @return train che è partito
     */
    Train *leave_train(int track) override;

    /**
     * Funzione membro che stampa la situazione della stazione
     */
    void print() const override;

    /**
     * Distruttore
     */
    ~Local_station() override;

private:
    static const int TRANSIT_TRACK_LENGTH = 2; //Lunghezza dell'array per i binari di transito
    Train *transit_track[TRANSIT_TRACK_LENGTH]; //Binario 0: treni andata, Binario 1: treni ritorno
    std::deque<Train *> parcking1_transit; //Coda per parcheggio di transito di andata
    std::deque<Train *> parcking2_transit; //Coda per parcheggio di transito di ritorno

    /**
     * Funzione membro che controlla se fermare o far transitare il treno nel binario libero se libero, altrimenti se parcheggiarlo
     * @param t il treno da fermare
     * @return intero che indica il binario di stop/transito o il parcheggio (vedi status di train)
     */
    int get_free_binary(Train *t) override;
};


#endif //RAILWAY_STATION_H