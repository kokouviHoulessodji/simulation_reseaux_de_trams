#include "Station.h"

Station::Station(int id, const Position& p) :
    _ID{id},
    _occupeVersGauche{false},
    _occupeVersDroite{false},
    pos{p}
{}
Position Station::getPosition()const{return pos;}
void Station::remplieLeVector (std::vector<Voie*> relier)
{
    _arreteRelier=relier;
}

int Station::getID() const
{
    return _ID;
}

void Station::rendOccupe(bool VersDroite)
{
    if (VersDroite) _occupeVersDroite=true;
    else _occupeVersGauche=true;
}

void Station::rendLibre(bool VersDroite)
{
    if (VersDroite) _occupeVersDroite=false;
    else _occupeVersGauche=false;
}

bool Station::getOccuper (bool VersDroite) const
{
    return ( VersDroite ? _occupeVersDroite : _occupeVersGauche );
}

Voie* Station::getVoieVers (int idDest) const
{
    int i=0;
    while (i<_arreteRelier.size() && _arreteRelier[i]->_receiver->_ID!=idDest){i++;}

    return (i==_arreteRelier.size() ? nullptr : _arreteRelier[i]);
}

void Station::dessiner() const
{
    setcolor(WHITE);
    circle(pos.getX(), pos.getY(), 5);
    setcolor(BLACK);
    fillellipse(pos.getX(), pos.getY(), 4, 4);
}
