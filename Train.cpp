#include <iostream>

#include "Train.h"


int Train::getSpeed() const {
    if (speed < 0 || speed > MAX_SPEED)throw InvalidSpeed{};
    return speed;
}

int Train::getDelay() const {
    return delay;
}

int Train::getStatus() const {
    return status;
}


void Train::setStatus(int s) {
    status = s;
}

void Train::addDelay(int currentDelay) {
    delay += currentDelay;
}

void Train::changeSpeed(int differentSpeed) {
    if (differentSpeed < 0 || differentSpeed > MAX_SPEED)//lancia l'eccezione se la velocità cambiata è invalida
        throw InvalidSpeed{};
    speed = differentSpeed;
}

int Train::getId() const {
    return ID;
}

int Train::getNextStation() {
    if(toward)return nextStation++;
    return nextStation--;
}

bool Train::getToward() const {
    return toward;
}

void Train::print() const {
    std::cout << "ID: " << ID << " speed: " << speed << " delay: " << delay << " toward: " << toward
              << " status: " << status << " nextStation: " << nextStation << std::endl;
}

int Train::getDistance() const {
    return distance;
}

void Train::setDistance(int distance) {
    Train::distance = distance;
}

int Train::incrementDistance(int speed) const {
    return speed / 60;
}
/*Train::~Train()
{
}*/

