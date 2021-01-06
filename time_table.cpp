//
// Created by tomma on 05/01/2021.
//

#include "time_table.h"
#include "vector"
#include <iostream>
#include<fstream>
#include "string"

using namespace std;

time_table ::time_table() {
    carica_TimeTable();
    carica_Tratta();
}

void time_table ::avvia_Simulazione(){
    for (int i = 0; i < 1440; ++i) {
                
    }
}



void time_table ::carica_Tratta(){
    ifstream tratta;
    tratta.open("line_description.txt");
    string text;
    if(tratta.is_open()){
        while(getline(tratta,text)){
            vector<string> temp= split(text);
            //i primi elementi sono il nome
            //il penultimo bisogna convertirlo in int ed è il tipo stazione
            //l'ultimo bisogna convertirlo in int ed è la distanza dall'origine
        }
    }
    tratta.close();
}

void time_table ::carica_TimeTable(){
    ifstream timetables;
    timetables.open("timetables.txt");
    string text;
    if(timetables.is_open()){
        while(getline(timetables,text)){

        }
    }
    timetables.close();
}

vector<string> time_table::controlla_Tratta(vector<string> tratta_s) {
    int tipoT = stoi(tratta_s[1]);
    for (int i = 3; i < tratta_s.size()-1; ++i) {

        int tempo=(stoi(tratta_s[i])-stoi(tratta_s[i+1]));
        if(tempo<0)
            tempo=-tempo;

        int tempo_min = 0;

        switch (tipoT) {
            case 1:
                tempo_min = (160 * (distanza_stazioni-5)) + 16;
                if (tempo < tempo_min){
                    tratta_s[i+1] = stoi(tratta_s[i]) + tempo_min;
                }
                break;
            case 2:
                tempo_min = (240 * (distanza_stazioni-5)) + 16;
                if (tempo < tempo_min){
                    tratta_s[i+1] = stoi(tratta_s[i]) + tempo_min;
                }
                break;
            case 3:
                tempo_min = (300 * (distanza_stazioni-5)) + 16;
                if (tempo < tempo_min){
                    tratta_s[i+1] = stoi(tratta_s[i]) + tempo_min;
                }
                break;
        }
        return tratta_s;
    }
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