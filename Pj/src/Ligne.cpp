#include "Ligne.h"
#include "graphics.h"

Ligne::Ligne(int ID, color couleur, const std::vector<int>& IDs) :
    _ID{ID},
    _couleur{couleur},
    _StationsID{IDs}
{}

int Ligne::getStationSuivant(int actuel) const
{
    return ( actuel>=0 && actuel<_StationsID.size()-1 ? actuel+1 : -1);
}

int Ligne::getStationPrecedent(int actuel) const
{
    return ( actuel>0 && actuel<=_StationsID.size()-1 ? actuel-1 : -1);
}

int Ligne::getID() const
{
    return _ID;
}
 int Ligne::getIndStation (int id) const
 {
     int i=0;
     while (i<_StationsID.size() && id!=_StationsID[i])
        i++;
     return (i==_StationsID.size() ? -1 : i);
 }
