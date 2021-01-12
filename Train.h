#ifndef RAILWAY_TRAIN_H
#define RAILWAY_TRAIN_H

#include <string>
#include <ostream>
#include <vector>

/**
 * @author Collesei Matteo
 * Classe Train che identifica un treno in una stazione ferroviaria
 */
class Train {
private:
    int ID; //identificativo del treno
    int speed; //velocità del treno
    int delay; //ritardo accumulato
    bool toward; //verso della tratta: vero se andata, falso se ritorno
    /**
     * -5 parcheggio transito ritorno
     * -4 parcheggio transito andata
     * -2 parcheggio stop ritorno
     * -1 parcheggio stop andata
     * 0,1 binari stop di andata
     * 2,3 binari stop ritorno
     * 4 binario transito andata
     * 5 binario transito ritorno
     * 100 in movimento
     */
    int status;
    int nextStation; //identificativo della stazione successiva
    int distance;
    int wait;
    static const int LIMIT_SPEED = 80; //limite di velocità nelle stazioni
    std::vector<int> orari;

protected:
    /**
     * costruttore di un treno
     * @param ID id del treno
     * @param toward verso di percorrenza
     * @param speed velocità iniziale
     * @param delay ritardo iniziale
     * @param firstStation id della prima stazione
     * @param status stato iniziale
     */
    explicit Train(int ID = 0, bool toward = true, const std::vector<int> &orari = {}, int speed = 0, int delay = 0,
                   int firstStation = 0, int status = 100, int distance = 0, int wait = 0)
            : ID{ID}, speed{speed}, delay{delay}, nextStation{firstStation}, status{status}, toward{toward},
              distance{distance}, orari{orari}, wait{wait} {}

protected:
    virtual int MAX_SPEED() const = 0;

public:

    /**
     * funzione che varia la velocità del treno
     * @param differentSpeed velocità variata
     */
    void changeSpeed(int differentSpeed);

    /**
     * funzione che aggiunge ritardo
     * @param currentDelay ritardo attuale sommato a quello totale
     */
    void addDelay(int currentDelay);

    /**
     * funzione che restituisce la velocità
     * @return velocità attuale
     */
    int getSpeed() const;

    /**
     * funzione che restituisce il ritardo accumulato
     * @return ritardo totale
     */
    int getDelay() const;

    /**
     * funzione che restituisce l'identificativo del treno
     * @return id del treno
     */
    int getId() const;

    /**
     * funzione che restituisce il verso di percorrenza del treno
     * @return 1 se andata,0 se ritorno
     */
    bool getToward() const;

    /**
     * funione che restituisce l'identificativo della stazione successiva
     * @return id della stazione successiva
     */
    int getNextStation() const;

    /**
     * funzione che incrementa la prossiam stazione in base al verso del treno
     */
    void incrementNextStation();

    /**
     * funzione che restituisce lo stato del treno
     * @return stato del treno
     */
    int getStatus() const;

    /**
     * funzione che cambia lo stato del treno
     * @param status1 stato aggiornato
     */
    void setStatus(int status1);

    /**
     * funzione che restituisce la distanza dall'origine del treno
     * @return distanza dall'origine del treno
     */
    int getDistance() const;

    /**
     * funzione che cambia la distanza dall'origine del treno
     * @param distance distanza aggiornata
     */
    void setDistance(int distance);

    /**
     * funzione che restituisce la distanza percorsa in un minuto a velocità definita
     * @param speed, la velocità definita
     * @return la distanza percorsa in un minuto a velocità definita
     */
    int incrementDistance(int speed) const;

    /**
     * funzione che restituisce l'orario in base all'indice passato
     * @param i, l'indice
     * @return l'orario corrispondente
     */
    int getOrario(int i) const;

    /**
     * funzione che modifica il tempo di attesa del treno
     * @param wait il tempo di attesa
     */
    void setWait(int wait);

    /**
     * funzione che decrementa il tempo di attesa
     * @return true se attesa = 0, false altrimenti
     */
    bool decrementWait();

    /**
     * funzione che restituisce il tipo di treno
     * @return tipo di treno
     */
    std::string getType() { return typeid(*this).name(); };

    /**
     * distruttore
     */
    virtual ~Train() = default;

    /**
     * funzione che stampa un riepilogo del treno
     */
    void print() const;

    /**
     * classe che descrive una velocità non valida
     */
    class InvalidSpeed {
    };

    /**
     * class che descrive un indice passato non valido
     */
    class InvalidIndex {
    };

};

/**
 * classe che rappresenta un treno regionale
 */
class RegionalTrain : public Train {
public:
    /**
     * costruttore del treno regionale
     * @param ID id del treno
     * @param toward verso di percorrenza
     * @param speed velocità iniziale
     * @param delay ritardo iniziale
     * @param firstStation id della prima stazione
     * @param status stato iniziale
     */
    explicit RegionalTrain(int ID = 0, bool toward = true, const std::vector<int> &orari = {}, int speed = 0,
                           int delay = 0, int firstStation = 0,
                           int status = 100, int distance = 0)
            : Train(ID, toward, orari, speed, delay, firstStation, status, distance) {};

private:
    int MAX_SPEED() const { return 160; };
};

/**
 * classe che rappresenta un treno ad alta velocità
 */
class HighSpeedTrain : public Train {
public:
    /**
     * costruttore del treno ad alta velocità
     * @param ID ide del treno
     * @param toward verso di percorrenza
     * @param speed velocità iniziale
     * @param delay ritardo iniziale
     * @param firstStation id della prima stazione
     * @param status stato iniziale
     */
    explicit HighSpeedTrain(int ID = 0, bool toward = true, const std::vector<int> & orari = {}, int speed = 0, int delay = 0, int firstStation = 0,
                            int status = 100, int distance = 0)
            : Train(ID, toward, orari, speed, delay, firstStation, status, distance) {};

private:
    int MAX_SPEED() const { return 240; };
};

/**
 * classe che rappresenta un treno ad alta velocità super
 */
class SuperHighSpeedTrain : public Train {
public:
    /**
     * costruttore del treno ad alta velocità super
     * @param ID id del treno
     * @param toward verso di percorrenza
     * @param speed velocità iniziale
     * @param delay ritardo iniziale
     * @param firstStation id della prima stazione
     * @param status stato iniziale
     */
    explicit SuperHighSpeedTrain(int ID = 0, bool toward = true, const std::vector<int> &orari = {}, int speed = 0,
                                 int delay = 0, int firstStation = 0,
                                 int status = 100, int distance = 0)
            : Train(ID, toward, orari, speed, delay, firstStation, status, distance) {};

private:
    int MAX_SPEED() const { return 300; };

};

#endif //RAILWAY_Train_H