#ifndef GRAPHE_H_INCLUDED
#define GRAPHE_H_INCLUDED


#include "C:\\Users\\muhir\\Documents\\web development\\CV\\Pj\\pugixml.hpp"
#include <vector>
#include "Ligne.h"
#include "Tram.h"
#include "Voie.h"
#include "Station.h"
#include "Voies.h"


class Graphe
{

    public:
        Graphe();
        ~Graphe();


    private:

        void charger(char *f);
        void lancer();
        void decharger();
        Station* stationID (int) const;
        Ligne* ligneID (int) const;

private:
        int _sleepTime;
        int _tempsStationMS;
        int _distanceSecuritePixel;
        int _dureeSimulationMS;


        pugi::xml_document _document;
        std::vector<Ligne*> _lignes;
        std::vector<Station*> _stations;
        Voies *_voies;


        void menu();
        void parametre();
};

#endif // GRAPHE_H_INCLUDED

