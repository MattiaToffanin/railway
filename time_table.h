//
// Creato e modificato da Tommaso Bicego, 1190444
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
    vector<int> Orari(vector<string>);

private:
    vector<Station*> lista_Stazioni;
    vector<Station*> lista_MainS;
    vector<Train*> lista_Treni;


    //per test
    void Stampa();


};


#endif //ASSEGNAMENTO2_0_TIME_TABLE_H
