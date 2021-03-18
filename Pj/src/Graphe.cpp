#include "Graphe.h"
#include <windows.h>
#include "graphics.h"

Graphe::Graphe() :
    _sleepTime{100},
	_tempsStationMS{500},
	_distanceSecuritePixel{30},
	_dureeSimulationMS{60000}
{
    menu();
}
void Graphe::parametre(){
    std::cout<<"######PARAMETRE DE SIMULATION######"<<std::endl<<std::endl;
        std::cout<<"\t1.Changer la distance de securité entre tram "<<std::endl;
        std::cout<<"\t2.Changer la duree de simulation"<<std::endl;
        std::cout<<"\t3.Changer le temps que le tram doit passer sur station"<<std::endl;
        std::cout<<"\t4.Changer lvitesse de simulation"<<std::endl;
        std::cout<<"\t5.Exit_\n\n\n"<<std::endl;
        int variable=1;
        std::cout<<"8Tchoix : ";std::cin>>variable;
        switch(variable) {
            case 1:
                std::cout<<"Le nouveau distance de securité(Pixels) : ";
                std::cin>>_distanceSecuritePixel;
                break;
            case 2:
                std::cout<<"la nouvelle duree de simulation(MS) : ";
                std::cin>>_dureeSimulationMS;
                break;
            case 3:
                std::cout<<"le nouveau temps d'arret sur chaque station (MS)  : ";
                std::cin>>_tempsStationMS;
                break;
            case 4:
                std::cout<<"Valeur de sleep time (Initialise a 100)  : ";
                std::cin>>_sleepTime;
                break;
            case 5:
                break;
            default:
                break;
        }
        menu();
}
void Graphe::menu(){
    char *f1="Station3.xml";
    char *f2="Station2.xml";
    char *f3="Station1.xml";


    bool t=true;
    while(t){
        std::cout<<"######CHOISIR LE FICHIER######"<<std::endl<<std::endl;
        std::cout<<"\t1.Fichier 1"<<std::endl;
        std::cout<<"\t2.Fichier 2"<<std::endl;
        std::cout<<"\t3.Fichier 3"<<std::endl;
        std::cout<<"\t4.Parametre de simuation"<<std::endl;
        std::cout<<"\t5.Exit"<<std::endl;
        int variable=1;
        std::cout<<"choix : ";std::cin>>variable;
        switch(variable) {
            case 1:
                charger(f1);
                break;
            case 2:
                charger(f2);
                break;
            case 3:
                charger(f3);
                break;
            case 4:
                parametre();
                break;
            case 5:
                exit(0);
                break;
            default:
                charger(f3);
        }
        lancer();
        decharger();

    }
}

Graphe::~Graphe(){
    decharger();
}

Station* Graphe::stationID (int id) const{
    unsigned int i=0;
    while (i<_stations.size() && _stations[i]->getID()!=id)
        i++;
    return i<_stations.size() ? _stations[i] : nullptr;
}

Ligne* Graphe::ligneID (int id) const{
    int i=0;
    while (i<_lignes.size() && _lignes[i]->getID()!=id)
        i++;
    return i<_lignes.size() ? _lignes[i] : nullptr;
}

void Graphe::charger(char *f){
    // Charge les lignes
    _document.load_file(f);
    int nombreStation = 0, nombreLigne = 0;

    nombreLigne = atoi(_document.child("Stations").child("NombreLigne").child_value());
    nombreStation = atoi(_document.child("Stations").child("NombreStation").child_value());
    std::cout<<">>>>  Nombre ligne :"<<nombreLigne<<"     Nombre Stations(Arret): "<<nombreStation<<std::endl;
    _lignes.reserve(nombreLigne);
    std::cout<<">>>>  _lignes.reserve("<<nombreLigne<<");    succedded!"<<std::endl;
    for(pugi::xml_node val = _document.child("Stations").child("Ligne"); val; val = val.next_sibling("Ligne")){
        std::vector<int> tmp;
        unsigned int ID = val.attribute("ID").as_int();
        int COLOR =  val.attribute("color").as_int();
        std::cout<<">>Laoding Ligne ID:"<<ID<<std::endl;
        for(pugi::xml_node attr = val.first_child(); attr; attr = attr.next_sibling()){
            tmp.push_back(atoi(attr.child_value()));
            std::cout<<"        >>Station ID "<< atoi(attr.child_value()) <<std::endl;
        }
        std::cout<<"loading Ligne end"<<std::endl;
        _lignes.emplace_back(new Ligne{ID, COLOR, tmp});
    }
    std::cout<<"...........loading Lignes end"<<std::endl;
    // Charge les stations
    _stations.reserve(nombreStation);
    std::cout<<">>>>  _stations.reserve("<<nombreStation<<");    succedded!"<<std::endl;
    for(pugi::xml_node val = _document.child("Stations").child("Station"); val; val = val.next_sibling("Station")){
        std::vector<int> value;
        for(pugi::xml_node attr = val.first_child(); attr; attr = attr.next_sibling()){
            value.push_back(atoi(attr.child_value()));
        }
        _stations.emplace_back(new Station{value[0], Position(value[1], value[2])});
        std::cout<<">>>>  Loading Station ID:"<<value[0]<<", Pos("<< value[1]<<","<< value[2] <<")succedded!"<<std::endl;
    }
    std::cout<<std::endl<<"Loaded all Stations ended with success"<<std::endl;
    // Créer les voies
    Voie *vTmp;
    std::vector<std::vector<bool> > tb(_stations.size(), std::vector<bool>(_stations.size(), false));

    _voies = new Voies{};
    std::cout<<"\n\n\n        Creation des voies    class Voie(Station* sender,Station* receiver)"<<std::endl;
    std::cout<<"________________________________________________________________________"<<std::endl;
    for (unsigned int b=0;b<_lignes.size();b++){
        for (int c=0;c<_lignes[b]->getTaille()-1;c++){
            int env=_lignes[b]->getStationInd(c), desti=_lignes[b]->getStationInd(c+1);
            if (!tb[env][desti]){

                vTmp=new Voie {stationID(env),stationID(desti)};
                _voies->ajouterVoie(vTmp);
                tb[env][desti]=true;
                std::cout<<"-->  creation du voie Voie(StationID "<<env<<",StationID "<<desti<<")"<<std::endl;
            }
            if (!tb[desti][env]){
                vTmp=new Voie {stationID(desti),stationID(env)};
                _voies->ajouterVoie(vTmp);
                tb[desti][env]=true;
                std::cout<<"<--  creation du voie Voie(StationID "<<desti<<",StationID "<<env<<")"<<std::endl;
            }
        }
    }
    std::vector< std::vector<Voie*> > vvV(_stations.size(), std::vector<Voie*>(0));
    Voie *crt= _voies->getTete();
    while (crt)
    {
        vvV[crt->getEnvoyeur()->getID()].push_back(crt);
        crt=crt->getSuivant();
    }
    Station *tmp;
    for (unsigned int i=0; i < _stations.size();i++)
    {
        tmp=stationID(i);
        tmp->remplieLeVector(vvV[i]);
    }
    std::cout<<"Chargement des Tram"<<std::endl;
    for(pugi::xml_node val = _document.child("Stations").child("Tram"); val; val = val.next_sibling("Tram"))
    {
        std::vector<double> value;
        for(pugi::xml_node attr = val.first_child(); attr; attr = attr.next_sibling())
        {
            value.push_back(atof(attr.child_value()));
        }
        Tram *t = new Tram{stationID (static_cast<int>(value[0])), ligneID(static_cast<int>(value[1])), value[2]};
    }

    Tram::distanceSec = _distanceSecuritePixel;

}

void Graphe::decharger(){

	// voies station ligne
    delete _voies;
    std::cout<<">>> Voies decharges\n";
    for(unsigned int i = 0; i < _stations.size(); i++)
    {
        delete _stations[i];
    }
    std::cout<<">>> Arrêts décharges\n";

    for(unsigned int i = 0; i < _lignes.size(); i++)
    {
        delete _lignes[i];
    }
    std::cout<<">>> Lignes déchargees\n";

    _stations.clear();
    _lignes.clear();

}

void Graphe::lancer(){

    initwindow(900, 600);
    int time = 0;
    while(time < _dureeSimulationMS)
    {
        _voies->dessinVoies();
        for (unsigned int i=0;i< _stations.size();i++)
            _stations[i]->dessiner();

        _voies->update(_sleepTime);

        Sleep(_sleepTime);
        time += _sleepTime;
        cleardevice();
    }
    std::cout<<"Fin de simulation!\n";
    closegraph();
}


