//
// Creato e modificato da Tommaso Bicego
//

#ifndef UNTITLED2_TIME_TABLE_H
#define UNTITLED2_TIME_TABLE_H

//#include "Station.h"
//#include "Train.h"


#include "vector"
#include <iostream>
#include<fstream>
#include "string"


using namespace std;

class time_table {
public:
    time_table();
    void avvia_Simulazione();

private:
    vector<vector<string>> tabella_orari;
    //vector<Station> tabella_stazioni;

    void carica_Tratta();
    void carica_TimeTable();
    vector<string> controlla_Tratta(string text);
    vector<string> split(string text);
};


#endif //UNTITLED2_TIME_TABLE_H
