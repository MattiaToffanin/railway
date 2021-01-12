//
// Creato e modificato da Tommaso Bicego
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

void time_table ::avvia_Simulazione(){
    for (int i = 0; i < 1440; ++i) {

    }
}

void time_table ::carica_TimeTable(){
    ifstream timetables;
    timetables.open("timetables.txt");
    string text;
    vector<string> tratta;

    if(timetables.is_open()){
        while(getline(timetables,text)){
            tratta = controlla_TimeTable(text);

            Train* treno;

            int id = stoi(tratta[0]);

            bool toward = true;
            if (stoi(tratta[1]) == 1)
                toward = false;

            if (stoi(tratta[2])==1){
                treno=new RegionalTrain(id,toward);
            }
            else if (stoi(tratta[2])==2){
                treno = new HighSpeedTrain(id,toward);
            }
            else if (stoi(tratta[2])==3){
                treno = new SuperHighSpeedTrain(id,toward);
            }
            else{
                //errore
            }
            lista_Treni.push_back(treno);
        }
    }
    timetables.close();
}

void time_table::ordina_Tratta() {

    Station* temp;
    int n = lista_Stazioni.size();

    for(int i=0; i<n-1; i++)
    {
        int min = i;
        for(int j=i+1; j<n; j++)
            if(lista_Stazioni[j]->get_distance() < lista_Stazioni[min]->get_distance())
                min = j;
        temp=lista_Stazioni[min];
        lista_Stazioni[min]=lista_Stazioni[i];
        lista_Stazioni[i]=temp;
    }
}


vector<string> time_table::controlla_TimeTable(string text) {

    vector<string> orari_treno = split(text);
    vector<Station*> temp_main;
    for (int i = 0; i < lista_Stazioni.size(); ++i) {
        if(lista_Stazioni[i]->get_type().compare("class Main_station")){
            temp_main.push_back(lista_Stazioni[i]);
        }
    }

    int tipoT = stoi(orari_treno[1]);
    for (int i = 3; i < orari_treno.size()-1; ++i) {
        int tempo=(stoi(orari_treno[i])-stoi(orari_treno[i+1]));

        int tempo_min = 0;

        int distanza_stazioni;

        switch (tipoT) {
            case 1:
                distanza_stazioni = lista_Stazioni[i+1]->get_distance() - lista_Stazioni[i]->get_distance();
                distanza_stazioni =(distanza_stazioni-10)*60;
                if (distanza_stazioni<0)
                    distanza_stazioni = - distanza_stazioni;
                tempo_min = (distanza_stazioni  /160 ) + 8;
                if (tempo < tempo_min){
                    orari_treno[i+1] = stoi(orari_treno[i]) + tempo_min;
                    cout<<"ritardo";
                }
                break;
            case 2:
                distanza_stazioni = temp_main[i+1]->get_distance() - temp_main[i]->get_distance();
                distanza_stazioni =(distanza_stazioni-10)*60;
                if (distanza_stazioni<0)
                    distanza_stazioni = - distanza_stazioni;
                tempo_min = (distanza_stazioni  /240 ) + 8;
                if (tempo < tempo_min){
                    orari_treno[i+1] = stoi(orari_treno[i]) + tempo_min;
                    cout<<"ritardo";
                }
                break;
            case 3:
                distanza_stazioni = temp_main[i+1]->get_distance() - temp_main[i]->get_distance();
                distanza_stazioni =(distanza_stazioni-10)*60;
                if (distanza_stazioni<0)
                    distanza_stazioni = - distanza_stazioni;
                tempo_min = (distanza_stazioni /300 ) + 8;
                if (tempo < tempo_min){
                    orari_treno[i+1] = stoi(orari_treno[i]) + tempo_min;
                    cout<<"ritardo";
                }
                break;
        }
        return orari_treno;
    }
}


void time_table ::carica_Tratta(){
    int primo=0;
    string text = "";

    ifstream tratta;
    tratta.open("line_description.txt");
    if(tratta.is_open()){
        while(getline(tratta,text)){
            vector<string> temp = split(text);

            Station* stazione;

            string nome = "";
            int distanza = 0;

            if (primo==0){
                for (int i = 0; i < temp.size(); ++i) {
                    nome=nome+" "+temp[i];
                }
                stazione = new Main_station(nome,0,0);
                primo++;
            }
            else {
                string type = temp[temp.size() - 2];
                int distanza = stoi(temp[temp.size()-1]);

                for (int i = 0; i < temp.size()-2; ++i) {
                    nome=nome+" "+temp[i];
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
    Stampa();
}

vector<string> time_table::split(string text) {
    string temp;
    vector<string> utility;
    for (int i = 0; i < text.size(); ++i) {

        if (text[i]!=' '){
            temp= temp+text[i];
        }
        else{
            utility.push_back(temp);
            temp="";
        }
    }
    utility.push_back(temp);
    return utility;
}

void time_table::Stampa(){
    for (int i = 0; i < lista_Stazioni.size(); ++i) {
        string nome = lista_Stazioni[i]->get_name();
        int distanza = lista_Stazioni[i]->get_distance();

        cout<<nome<<" "<< distanza<<'\n';
    }
}