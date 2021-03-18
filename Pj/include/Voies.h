#ifndef VOIES_H
#define VOIES_H
#include "Voies.h"

class Voie;
class Voies
{
    public:
        Voies();
        void ajouterVoie (Voie *v);
        inline Voie* getTete() const {return _tete;};
        void update(int);
        void dessinVoies() const;
        ~Voies();
    private:
        Voie *_tete, *_tail;
};

#endif // VOIES_H
