//
// Creato e modificato da Tommaso Bicego
//

#ifndef ASSEGNAMENTO2_0_TIME_TABLE_H
#define ASSEGNAMENTO2_0_TIME_TABLE_H

#include "Station.h"
#include "Train.h"

#include "vector"
#include <iostream>
#include<fstream>
#include "string"

using namespace std;

class time_table {
public:
    time_table();

    time_table(const vector<Station *> &listaStazioni);

    void avvia_Simulazione();


    //da spostare a private
    void carica_Tratta();
    void carica_TimeTable();
    vector<string> controlla_Tratta(string text);
    vector<string> controlla_TimeTable(string text);
    void ordina_Tratta();
    vector<string> split(string text);

private:
    vector<Station*> lista_Stazioni;
    vector<Train*> lista_Treni;


    //per test
    void Stampa();


};


#endif //ASSEGNAMENTO2_0_TIME_TABLE_H
