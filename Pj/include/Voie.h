#ifndef VOIE_H
#define VOIE_H
#include "Tram.h"
#include "Station.h"

class Station;
class Tram;
class Voie
{
    public:
        Voie(Station *s, Station *r);
        void ajouteTram (Tram *t);
        void enleveTete();
        inline Tram* getTete() const {return _tete;};
        inline Voie* getSuivant() const {return _suiv;};
        inline Station* getEnvoyeur() const {return _sender;};
        void dessinVoie() const;
        void update(int);
        double getDistance()const;
        ~Voie ();
        friend class Station;
        friend class Tram;
        friend class Voies;
    private:
        Tram *_tete;
        Tram *_tail;
        Station *_receiver;
        Station *_sender;
        //double _distance;
        Voie *_suiv;
};

#endif // VOIE_H
