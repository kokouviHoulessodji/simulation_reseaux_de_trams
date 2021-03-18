#include "Voie.h"
#include "graphics.h"
#include <cmath>

Voie::Voie (Station* s, Station* r) :
    _tete{nullptr},
    _tail{nullptr},
    _receiver{r},
    _sender{s},
    _suiv{nullptr}
{}

void Voie::ajouteTram (Tram *t)
{
    if (_tete==nullptr)
    {
        _tete=t;
        t->_prec=nullptr;
    }
    else
    {
        _tail->_suiv=t;
        t->_prec=_tail;
    }
    _tail=t;
    t->_suiv=nullptr;
}

void Voie::enleveTete()
{
    if (_tete->_suiv!=nullptr) _tete->_suiv->_prec=nullptr;
    else _tail=_tail->_prec;
    _tete=_tete->_suiv;
}

void Voie::update(int sleepTime)
{
    Tram *crt=_tete;
    while(crt!=nullptr)
    {
        crt->update(sleepTime);
        crt=crt->_suiv;
    }
}

void Voie::dessinVoie() const
{
    setcolor(WHITE);
    moveto(_sender->getPosition().getX(), _sender->getPosition().getY());
    lineto(_receiver->getPosition().getX(), _receiver->getPosition().getY());
}
double Voie::getDistance()const{
    return _receiver->getPosition().getDistance(_sender->getPosition());
}
Voie::~Voie()
{
    Tram *crt;
    while (_tete!=_tail)
    {
        crt=_tete;
        _tete=_tete->_suiv;
        delete crt;
    }
    delete _tail;
}
