#include <string>
#include <ostream>

#ifndef RAILWAY_TRAIN_H
#define RAILWAY_TRAIN_H


class Train {
private:
    int ID;
    int speed;
    int delay;
    bool toward;
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
    int nextStation;
    static const int LIMIT_SPEED = 80;

protected:
    explicit Train(int ID = 0, bool toward = true, int speed = 0, int delay = 0, int firstStation = 0, int status = 0)
            : ID{ID}, speed{speed}, delay{delay}, nextStation{firstStation}, status{status}, toward{toward} {}

protected:
    static const int MAX_SPEED = 0;

public:

    void changeSpeed(int differentSpeed);

    void addDelay(int currentDelay);

    int getSpeed() const;

    int getDelay() const;

    int getId() const;

    bool getToward() const;

    int getNextStation();

    int getStatus() const;

    void setStatus(int status1);

    std::string getType() { return typeid(*this).name(); };

    virtual ~Train() = default;

    void print() const;

    class InvalidSpeed {
    };

};


class RegionalTrain : public Train {
public:
    explicit RegionalTrain(int ID = 0, bool toward = true, int speed = 0, int delay = 0, int firstStation = 0,
                           int status = 0)
            : Train(ID, toward, speed, delay, firstStation, status) {};

private:
    static const int MAX_SPEED = 160;
};

class HighSpeedTrain : public Train {
public:
    explicit HighSpeedTrain(int ID = 0, bool toward = true, int speed = 0, int delay = 0, int firstStation = 0,
                            int status = 0)
            : Train(ID, toward, speed, delay, firstStation, status) {};

private:
    static const int MAX_SPEED = 240;
};

class SuperHighSpeedTrain : public Train {
public:
    explicit SuperHighSpeedTrain(int ID = 0, bool toward = true, int speed = 0, int delay = 0, int firstStation = 0,
                                 int status = 0)
            : Train(ID, toward, speed, delay, firstStation, status) {};

private:
    static const int MAX_SPEED = 300;
};

#endif //RAILWAY_Train_H