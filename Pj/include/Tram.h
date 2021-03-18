#ifndef TRAM_H_INCLUDED
#define TRAM_H_INCLUDED
#include <iostream>
#include "Ligne.h"
#include "Voie.h"
#include "graphics.h"
#include"Position.h"

typedef int color;
class Station;
class Voie;
class Ligne;
class Tram
{
    public:
        static int distanceSec;
        color goColor=RED;
        color backColor=BLUE;
        Tram(Station* depart, Ligne *l, double vitesse);
        void update(int);
        friend class Voie;

    // Private Function
    private:
        bool aDepasserDestination() const;
        bool faitDemiTour() const;
        void changeSens();
        void changeDestination();
        void changeVoie();
        void avancer();
        double distanceEntreTram () const;
        bool bonneDistance () const;
        double distanceEntreTramEtStationReceiver () const;
        bool stationPossible () const;
        void dessiner() const;

    // Private Variable
    private:
        int tempsStationMS;// ni time tram igomba kumara kuri station
        int tempsPasserStation;// ni time tram imaze kuri station
        double _vitesse;
        Position posT;
        Position pos;
        bool _deplaceVersLaDroite, _estSurUnStation, _aFaitDemiTour;
        int _indDest;
        Ligne *_ligne;
        Voie *_voie;
        Tram *_suiv, *_prec;
};

#endif // TRAM_H_INCLUDED
