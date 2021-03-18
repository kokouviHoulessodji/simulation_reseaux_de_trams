#ifndef LIGNE_H_INCLUDED
#define LIGNE_H_INCLUDED
#include <iostream>
#include <vector>
#include "Station.h"
#include "graphics.h"

typedef int color;

class Tram;
class Ligne
{
    public:
        Ligne(int numero, color couleur, const std::vector< int>& IDs);
        int getStationSuivant(int actuel) const;
        int getStationPrecedent(int actuel) const;
        int getIndStation (int id) const;
        int getID() const;
        inline int getTaille() const {return _StationsID.size();};
        inline int getStationInd(int ind) const {return _StationsID[ind];};
        friend class Tram;
    private:
        unsigned int _ID;
        std::vector<int> _StationsID;
        color _couleur;
};

#endif // LIGNE_H_INCLUDED
