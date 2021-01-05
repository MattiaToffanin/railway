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
    if (differentSpeed < 0 || differentSpeed > MAX_SPEED)
        throw InvalidSpeed{};
    speed = differentSpeed;
}

int Train::getId() const {
    return ID;
}

int Train::getNextStation() {
    return nextStation++;
}

bool Train::getToward() const {
    return toward;
}

void Train::print() const {
    std::cout << "ID: " << ID << " speed: " << speed << " delay: " << delay << " toward: " << toward
       << " status: " << status << " nextStation: " << nextStation << std::endl;
}


