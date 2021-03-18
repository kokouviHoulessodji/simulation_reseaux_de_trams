#include "Voies.h"
#include "Voie.h"
Voies::Voies() : _tete{nullptr}, _tail{nullptr}
{}

void Voies::ajouterVoie (Voie *v)
{
    if (_tete==nullptr) _tete=v;
    else _tail->_suiv=v;
    _tail=v;
    v->_suiv=nullptr;
}

void Voies::update(int sleepTime)
{
    Voie *crt=_tete;
    while(crt!=nullptr)
    {
        crt->update(sleepTime);
        crt=crt->_suiv;
    }
}

void Voies::dessinVoies() const
{
    Voie *crt=_tete;
    while(crt!=nullptr)
    {
        crt->dessinVoie();
        crt=crt->_suiv;
    }
}

Voies::~Voies()
{
    Voie *crt;
    while (_tete!=_tail)
    {
        crt=_tete;
        _tete=_tete->_suiv;
        delete crt;
    }
    delete _tail;
}
