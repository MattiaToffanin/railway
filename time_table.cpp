//
// Creato e modificato da Tommaso Bicego, 1190444
//

#include "time_table.h"
#include "Station.h"
#include "Train.h"

#include "vector"
#include <iostream>
#include<fstream>
#include "string"

using namespace std;

time_table::time_table() {
    carica_TimeTable();
    carica_Tratta();
}

void time_table::avvia_Simulazione() {

    Train *regionale = new RegionalTrain();
    Train *veloce = new HighSpeedTrain();
    Train *moltoveloce = new SuperHighSpeedTrain();

    for (int i = 0; i < 1440; ++i) {
        for (int j = 0; j < lista_Treni.size(); ++j) {


            //parte il treno
            if (i == lista_Treni[j]->getOrario(0)) {
                lista_Treni[j]->incrementNextStation();
                if (lista_Treni[j]->getType() == regionale->getType())
                    lista_Treni[j]->changeSpeed(160);
                else if (lista_Treni[j]->getType() == veloce->getType())
                    lista_Treni[j]->changeSpeed(240);
                else if (lista_Treni[j]->getType() == regionale->getType())
                    lista_Treni[j]->changeSpeed(300);
            }



            //Controlla se è a meno di 5 km dalla stazione
            if (lista_Treni[j]->getStatus() != 999 &&
                lista_Treni[j]->getDistance() > lista_Stazioni[lista_Treni[j]->getNextStation()]->get_distance() - 5 &&
                lista_Treni[j]->getDistance() < lista_Stazioni[lista_Treni[j]->getNextStation()]->get_distance() &&
                !lista_Treni[j]->isInStation()) {
                lista_Treni[j]->setDistance(lista_Stazioni[lista_Treni[j]->getNextStation()]->get_distance() -
                                            5); //c'è un piccolo spreco di tempo di masimo 2/3 minuti
                lista_Treni[j]->setInStation(true);

                int status = lista_Stazioni[lista_Treni[j]->getNextStation()]->stop_train(lista_Treni[j]);
                cout << "il treno " << lista_Treni[j]->getId() << " sta per arrivare alla stazione "
                     << lista_Stazioni[lista_Treni[j]->getNextStation()]->get_name() << "\n";

                switch (status) {
                    case -5:
                        lista_Treni[j]->setStatus(status);
                        lista_Treni[j]->changeSpeed(0);
                        cout << "il treno " << lista_Treni[j]->getId()
                             << " si ferma nel parcheggio transito ritorno \n";
                        break;
                    case -4:
                        lista_Treni[j]->setStatus(status);
                        lista_Treni[j]->changeSpeed(0);
                        cout << "il treno " << lista_Treni[j]->getId() << " si ferma nel parcheggio transito andata \n";
                        break;
                    case -2:
                        lista_Treni[j]->setStatus(status);
                        lista_Treni[j]->changeSpeed(0);
                        cout << "il treno " << lista_Treni[j]->getId() << " si ferma nel parcheggio stop ritorno \n";
                        break;
                    case -1:
                        lista_Treni[j]->setStatus(status);
                        lista_Treni[j]->changeSpeed(0);
                        cout << "il treno " << lista_Treni[j]->getId() << " si ferma nel parcheggio stop andata \n";
                        break;
                    case 0:
                        lista_Treni[j]->setStatus(status);
                        lista_Treni[j]->changeSpeed(80);
                        cout << "il treno " << lista_Treni[j]->getId() << " si dirige verso binari stop di andata 1 \n";
                        break;
                    case 1:
                        lista_Treni[j]->setStatus(status);
                        lista_Treni[j]->changeSpeed(80);
                        cout << "il treno " << lista_Treni[j]->getId() << " si dirige verso binari stop di andata 2 \n";
                        break;
                    case 2:
                        lista_Treni[j]->setStatus(status);
                        lista_Treni[j]->changeSpeed(80);
                        cout << "il treno " << lista_Treni[j]->getId()
                             << " si dirige verso binari stop di ritorno 1 \n";
                        break;
                    case 3:
                        lista_Treni[j]->setStatus(status);
                        lista_Treni[j]->changeSpeed(80);
                        cout << "il treno " << lista_Treni[j]->getId()
                             << " si dirige verso binari stop di ritorno 2 \n";
                        break;
                    case 4:
                        lista_Treni[j]->setStatus(status);
                        cout << "il treno " << lista_Treni[j]->getId() << " si dirige verso binario transito andata \n";
                        break;
                    case 5:
                        lista_Treni[j]->setStatus(status);
                        cout << "il treno " << lista_Treni[j]->getId()
                             << " si dirige verso binario transito ritorno \n";
                        break;
                    case 100:
                        //non dovrebbe uscire
                        break;
                }

            }
            //si ferma alla stazione per descesa e salita passeggeri
            if (lista_Treni[j]->isInStation()) {
                //arriva in stazione
                if (lista_Treni[j]->getDistance() >= lista_Stazioni[lista_Treni[j]->getNextStation()]->get_distance() &&
                    lista_Treni[j]->getStatus() != 4 && lista_Treni[j]->getStatus() != 5 &&
                    lista_Treni[j]->getWait() < 0) {
                    lista_Treni[j]->setDistance(lista_Stazioni[lista_Treni[j]->getNextStation()]->get_distance());
                    lista_Treni[j]->changeSpeed(0);
                    lista_Treni[j]->setWait(5);
                }
                //riparte dalla stazione
                if (lista_Treni[j]->getDistance() == lista_Stazioni[lista_Treni[j]->getNextStation()]->get_distance() &&
                    lista_Treni[j]->decrementWait()) {

                    Train *temp = lista_Stazioni[lista_Treni[j]->getNextStation()]->leave_train(
                            lista_Treni[j]->getStatus());
                    cout << "alle ore " << i << " il treno " << lista_Treni[j]->getId()
                         << " è ripartito dalla stazione "
                         << lista_Stazioni[lista_Treni[j]->getNextStation()]->get_name() << " \n";
                    if (temp) {
                        temp->setStatus(lista_Treni[j]->getStatus());
                        temp->changeSpeed(80);
                    }
                    lista_Treni[j]->setStatus(100);
                    lista_Treni[j]->changeSpeed(80);
                    lista_Treni[j]->setInStation(false);
                }
            }

            if (lista_Treni[j]->getDistance() >= lista_Stazioni[lista_Treni[j]->getNextStation()]->get_distance() + 5) {


                if (lista_Treni[j]->getNextStation() + 1 != lista_Stazioni.size()) {
                    lista_Treni[j]->incrementNextStation();
                    if (lista_Treni[j]->getType() == regionale->getType())
                        lista_Treni[j]->changeSpeed(160);
                    else if (lista_Treni[j]->getType() == veloce->getType())
                        lista_Treni[j]->changeSpeed(240);
                    else if (lista_Treni[j]->getType() == regionale->getType())
                        lista_Treni[j]->changeSpeed(300);
                } else {
                    lista_Treni[j]->changeSpeed(0);
                    lista_Treni[j]->setStatus(999);
                    lista_Treni[j]->setDistance(lista_Stazioni[lista_Treni[j]->getNextStation()]->get_distance());
                }

            }

            lista_Treni[j]->setDistance(
                    lista_Treni[j]->getDistance() + lista_Treni[j]->incrementDistance(lista_Treni[j]->getSpeed()));
        }
    }
    //Stampa();
}

void time_table::carica_TimeTable() {
    ifstream timetables;
    timetables.open("timetables.txt");
    string text;
    vector<string> tratta;

    if (timetables.is_open()) {
        while (getline(timetables, text)) {
            tratta = controlla_TimeTable(text);

            Train *treno;

            vector<int> orario = Orari(tratta);

            int id = stoi(tratta[0]);

            bool toward = true;
            if (stoi(tratta[1]) == 1)
                toward = false;

            if (stoi(tratta[2]) == 1) {
                treno = new RegionalTrain(id, toward, orario);
            } else if (stoi(tratta[2]) == 2) {
                treno = new HighSpeedTrain(id, toward, orario);
            } else if (stoi(tratta[2]) == 3) {
                treno = new SuperHighSpeedTrain(id, toward, orario);
            } else {
                //errore
            }
            lista_Treni.push_back(treno);
        }
    }
    timetables.close();
}


void time_table::ordina_Tratta() {

    Station *temp;
    int n = lista_Stazioni.size();

    for (int i = 0; i < n - 1; i++) {
        int min = i;
        for (int j = i + 1; j < n; j++)
            if (lista_Stazioni[j]->get_distance() < lista_Stazioni[min]->get_distance())
                min = j;
        temp = lista_Stazioni[min];
        lista_Stazioni[min] = lista_Stazioni[i];
        lista_Stazioni[i] = temp;
    }
}


vector<string> time_table::controlla_TimeTable(string text) {

    vector<string> orari_treno = split(text);
    for (int i = 0; i < lista_Stazioni.size(); ++i) {
        if (lista_Stazioni[i]->get_type().compare("class Main_station")) {
            lista_MainS.push_back(lista_Stazioni[i]);
        }
    }

    int tipoT = stoi(orari_treno[1]);

    for (int i = 3; i < orari_treno.size() - 1; ++i) {
        int tempo = (stoi(orari_treno[i]) - stoi(orari_treno[i + 1]));

        int tempo_min = 0;

        int distanza_stazioni;

        switch (tipoT) {
            case 1:
                distanza_stazioni = lista_Stazioni[i + 1]->get_distance() - lista_Stazioni[i]->get_distance();
                distanza_stazioni = (distanza_stazioni - 10) * 60;
                if (distanza_stazioni < 0)
                    distanza_stazioni = -distanza_stazioni;
                tempo_min = (distanza_stazioni / 160) + 8;
                if (tempo < tempo_min) {
                    orari_treno[i + 1] = stoi(orari_treno[i]) + tempo_min;
                    cout << "ritardo";
                }
                break;
            case 2:
                distanza_stazioni = lista_MainS[i + 1]->get_distance() - lista_MainS[i]->get_distance();
                distanza_stazioni = (distanza_stazioni - 10) * 60;
                if (distanza_stazioni < 0)
                    distanza_stazioni = -distanza_stazioni;
                tempo_min = (distanza_stazioni / 240) + 8;
                if (tempo < tempo_min) {
                    orari_treno[i + 1] = stoi(orari_treno[i]) + tempo_min;
                    cout << "ritardo";
                }
                break;
            case 3:
                distanza_stazioni = lista_MainS[i + 1]->get_distance() - lista_MainS[i]->get_distance();
                distanza_stazioni = (distanza_stazioni - 10) * 60;
                if (distanza_stazioni < 0)
                    distanza_stazioni = -distanza_stazioni;
                tempo_min = (distanza_stazioni / 300) + 8;
                if (tempo < tempo_min) {
                    orari_treno[i + 1] = stoi(orari_treno[i]) + tempo_min;
                    cout << "ritardo";
                }
                break;
        }
    }
    return orari_treno;
}


void time_table::carica_Tratta() {
    int primo = 0;
    string text = "";

    ifstream tratta;
    tratta.open("line_description.txt");
    if (tratta.is_open()) {
        while (getline(tratta, text)) {
            vector<string> temp = split(text);

            Station *stazione;

            string nome = "";
            int distanza = 0;

            if (primo == 0) {
                for (int i = 0; i < temp.size(); ++i) {
                    nome = nome + " " + temp[i];
                }
                stazione = new Main_station(nome, 0, 0);
                primo++;
            } else {
                string type = temp[temp.size() - 2];
                int distanza = stoi(temp[temp.size() - 1]);

                for (int i = 0; i < temp.size() - 2; ++i) {
                    nome = nome + " " + temp[i];
                }
                switch (stoi(type)) {
                    case 0:
                        stazione = new Main_station(nome, 0, distanza);
                        break;
                    case 1:
                        stazione = new Local_station(nome, 0, distanza);
                        break;
                }
            }
            lista_Stazioni.push_back(stazione);
        }
    }
    tratta.close();
    ordina_Tratta();
}

vector<int> time_table::Orari(vector<string> treno) {
    vector<int> orario;
    for (int i = 3; i < treno.size(); ++i) {
        cout << treno[i] << "\n";
        orario.push_back(stoi(treno[i]));
    }
    return orario;
}

vector<string> time_table::split(string text) {
    string temp;
    vector<string> utility;
    for (int i = 0; i < text.size(); ++i) {

        if (text[i] != ' ') {
            temp = temp + text[i];
        } else {
            utility.push_back(temp);
            temp = "";
        }
    }
    utility.push_back(temp);
    return utility;
}

void time_table::Stampa() {
    for (int i = 0; i < lista_Stazioni.size(); ++i) {
        string nome = lista_Stazioni[i]->get_name();
        int distanza = lista_Stazioni[i]->get_distance();

        lista_Stazioni[i]->print();

        cout << "--------------------------------" << '\n';
    }
}