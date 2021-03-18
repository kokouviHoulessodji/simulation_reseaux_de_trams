#include "Tram.h"
#include "Station.h"
#include "graphics.h"
#include <cmath>
#include <iostream>
int Tram::distanceSec = 25;
//distanceEntreTramEtStationReceiver
Tram::Tram(Station *depart, Ligne *l, double vitesse) :

    _vitesse{vitesse},
    _ligne{l},
    _suiv{nullptr},
    _prec{nullptr},
    _aFaitDemiTour{false},
    pos{depart->getPosition()},
    posT{0,0}
{
    _indDest=_ligne->getIndStation(depart->getID());
    if (_ligne->getStationSuivant(_indDest)!=-1)
    {
        _deplaceVersLaDroite=true;
        _indDest=_ligne->getStationSuivant(_indDest);
    }
    else if (_ligne->getStationPrecedent(_indDest)!=-1)
    {
        _deplaceVersLaDroite=false;
        _indDest=_ligne->getStationPrecedent(_indDest);
    }
    _voie=depart->getVoieVers(_ligne->_StationsID[_indDest]);
    _voie->ajouteTram(this);
    avancer();
    _estSurUnStation=false;
    tempsStationMS = 500;
    tempsPasserStation = 0;
}

bool Tram::faitDemiTour() const{
    return ( _deplaceVersLaDroite ? ( _ligne->getStationSuivant(_indDest) == -1 ) : (_ligne->getStationPrecedent(_indDest) == -1) );
}

void Tram::changeSens(){
    _deplaceVersLaDroite = !_deplaceVersLaDroite;
}

void Tram::changeDestination(){
    _indDest = ( _deplaceVersLaDroite ? _ligne->getStationSuivant(_indDest) : _ligne->getStationPrecedent(_indDest) );
}

void Tram::changeVoie(){
    _voie->enleveTete();
    _voie=_voie->_receiver->getVoieVers(_ligne->_StationsID[_indDest]);
    _voie->ajouteTram(this);
}

void Tram::avancer(){

    /* (receiver-pos)/time
    */
    double x = _voie->_receiver->getPosition().getX() - pos.getX();
    double y = _voie->_receiver->getPosition().getY() - pos.getY();
    double time = _voie->getDistance() / _vitesse;

    posT.setPosition(x / time,y / time);

}

bool Tram::aDepasserDestination() const{

    Position p(pos.getX()+posT.getX(),pos.getY()+posT.getY());

    double distance = p.getDistance(_voie->_sender->getPosition());         //

    return distance >= _voie->getDistance();
}

double Tram::distanceEntreTram () const{
    return _prec->pos.getDistance(pos);
}

bool Tram::bonneDistance () const{
    return ( _prec!=nullptr ? distanceEntreTram()>distanceSec : true );
}
double Tram::distanceEntreTramEtStationReceiver () const{
    return _voie->_receiver->getPosition().getDistance(pos);
}

bool Tram::stationPossible () const{
    if ( !(_voie->_receiver->getOccuper(_deplaceVersLaDroite)) ) return true;
    return distanceEntreTramEtStationReceiver()>distanceSec;
}

void Tram::dessiner() const{
    setcolor(_ligne->_couleur);
    rectangle( pos.getX()-8, pos.getY()-8, pos.getX()+5, pos.getY()+8 );
    color c=( _deplaceVersLaDroite ^ _aFaitDemiTour ? goColor : backColor );
    setcolor(c);
    circle(pos.getX(), pos.getY(), 5);
}

void Tram::update(int sleepTime){
    if(not bonneDistance() or not stationPossible());
    else if(_estSurUnStation)
    {
        if(tempsPasserStation < tempsStationMS){
            tempsPasserStation += sleepTime;
        }else{
            tempsPasserStation = 0;
            if ( _aFaitDemiTour ){
                _voie->_sender->rendLibre(!_deplaceVersLaDroite);
                _voie->_sender->rendOccupe(_deplaceVersLaDroite);
                _aFaitDemiTour=false;
            }else{
                _estSurUnStation = false;
                _voie->_sender->rendLibre(_deplaceVersLaDroite);
            }
        }
    }
    else if(aDepasserDestination()){
        pos.setX(_voie->_receiver->getPosition().getX());
        pos.setY(_voie->_receiver->getPosition().getY());
        _voie->_receiver->rendOccupe(_deplaceVersLaDroite);
        if (faitDemiTour())
        {
            changeSens();
            _aFaitDemiTour=true;
        }
        changeDestination();
        changeVoie();
        avancer();
        _estSurUnStation = true;
    }
    else
    {
        pos.setPosition(pos.getX()+posT.getX(),pos.getY()+posT.getY());
    }
    dessiner();
}
