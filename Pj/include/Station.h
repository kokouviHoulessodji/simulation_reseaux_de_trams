#ifndef STATION_H_INCLUDED
#define STATION_H_INCLUDED
#include <iostream>
#include <vector>
#include "Voie.h"
#include "Position.h"
class Tram;
class Voie;
class Ligne;
class Station
{
    public:
        Station(int id, const Position& p);
        void remplieLeVector (std::vector<Voie*> relier);

        Position getPosition()const;
        int getID() const;
        void rendOccupe (bool VersDroite);
        void rendLibre (bool VersDroite);
        bool getOccuper (bool VersDroite) const;
        Voie* getVoieVers (int idDest) const;
        void dessiner() const;
    private:
        int _ID;
        Position pos;
        bool _occupeVersGauche, _occupeVersDroite;
        std::vector<Voie*> _arreteRelier;
};

#endif // STATION_H_INCLUDED
