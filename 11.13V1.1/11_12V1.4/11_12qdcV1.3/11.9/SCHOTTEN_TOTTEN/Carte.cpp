//
// Created by xiangyang on 2023/10/25.
//
#include<iostream>
#include "Chateau.h"
#include <cstdlib>
#include <time.h>
namespace Carte_name {

/*_______________________________文本转换————————————————————————————————————————*/
    std::string getstring(Nombre nom) {
        switch (nom) {
            case 1:
                //std::cout<<"un";
                return "un";
            case 2:
                //std::cout<<"deux";
                return "deux";
            case 3:
                //std::cout<<"trois";
                return "trois";
            case 4:
                //std::cout<<"quatre";
                return "quatre";
            case 5:
                //std::cout<<"cinq";
                return "cinq";
            case 6:
                //std::cout<<"six";
                return "six";
            case 7:
                //std::cout<<"sept";
                return "sept";
            case 8:
                //std::cout<<"huit";
                return "huit";
            case 9:
                //std::cout<<"neuf";
                return "neuf";
            case 10:
                //std::cout<<"neuf"
                return "dix";
            default:
                //std::cout<<"error";
                throw "error";
        }
    }

    std::string getstring(Couleur cou) {
        switch (cou) {
            case 1:
                return "jaune";
            case 2:
                return "vert";
            case 3:
                return "rouge";
            case 4:
                return "bleu";
            case 5:
                return "orange";
            case 6:
                return "violet";
            default:
                throw "error";
        }
    }

    std::string getstring(Strategie str) {
        switch (str) {
            case 1:
                return "cavalry";
            case 2:
                return "shield";
            case 3:
                return "darius";
            case 4:
                return "alxandre";
            case 5:
                return "fog";
            case 6:
                return "mud";
            case 7:
                return "scout";
            case 8:
                return "redeploy";
            case 9:
                return "deserter";
            case 10:
                return "traitor";
            default:
                throw "error";

        }
    }
    /*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~卡牌类型的静态变量~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/



    /*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~Jeu类型的实现（单例模式）~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/


    Jeu::~Jeu() {
        for (size_t i = 0; i < getNbCartes(); i++) delete cartes[i];
    }

    Jeu::Jeu() {
        size_t i = 0;
//        Nombre n_dft ;
//        Couleur c_dft  ;
        std::initializer_list<Nombre> Nombres = {un, deux, trois, quatre, cinq, six, sept, huit, neuf, dix};
        std::initializer_list<Couleur> Couleurs = {jaune, vert, rouge, bleu, orange, violet};
        std::initializer_list<Strategie> Strategies = {cavalry, shield, darius, alxandre, fod, mud, scout, redeploy,
                                                       deserter, traitor};
        for (auto n: Nombres){
            for (auto c: Couleurs){
                cartes[i++] = new Carte(n, c);
            }
        }
        i=0;
        for (auto s: Strategies) {

            _carte_strategy[i++] = new Carte_Strategy(s,i+1);
        }
    }
//
    /*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~Pioche实现~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
    Pioche::Pioche() : cartes(new const Carte *[Jeu::getInstance().getNbCartes()]),
                       nb(Jeu::getInstance().getNbCartes()),
                       _carte_strtegy(new const Carte_Strategy *[Jeu::getInstance().getNbCartes_Strategy()]),
                       nbstrategy(Jeu::getInstance().getNbCartes_Strategy()) {
        for (size_t i = 0; i < nb; i++) cartes[i] = &Jeu::getInstance().getCarte(i);
        for (size_t i = 0; i < nbstrategy; i++) _carte_strtegy[i] = &Jeu::getInstance().getCarte_Strategy(i);
//        for(int i=0; i<=nb;i++) {
//            //std::cout<<(*(cartes + i))->getCouleur();
//            //std::cout<<(*(cartes + i))->getNombre();
//            //std::cout<<(*(cartes + i))->getType();
//            //std::cout<<(*(cartes + i))->getStrategie();
//            std::cout<<"\n"<<i<<"\n";
//        }
    }


    const Carte &Pioche::getcarte() {
        if (nb == 0) throw gameException("Pioche vide");
        srand(time(0));
        size_t x = rand()%nb; // on tire une position entre 0 et nb-1
        const Carte *c = cartes[x]; // on retient l'adresse
        for (size_t i = x + 1; i < nb; i++)
            cartes[i - 1] = cartes[i]; // on décale toutes les cartes aux rangs suivants
        nb--;
        return *c;
    }
/*****************************************以下是策略卡的特殊测试*****************************************************/
//    const Carte_Strategy &Pioche::getstrategy_carte() {
//        if (nbstrategy == 0) throw gameException("Pioche vide");
//        //srand(time(0));
//        size_t x = 9;//rand() % nbstrategy; // on tire une position entre 0 et nb-1
//        const Carte_Strategy *c = _carte_strtegy[x]; // on retient l'adresse
//        for (size_t i = x + 1; i < nbstrategy; i++)
//            _carte_strtegy[i - 1] = _carte_strtegy[i]; // on décale toutes les cartes aux rangs suivants
//        nbstrategy--;
//        return *c;
//    }

/**************************************************************以下是策略卡的正常抽取*******************************/
    const Carte_Strategy &Pioche::getstrategy_carte() {
        if (nbstrategy == 0) throw gameException("Pioche vide");
        srand(time(0));
        size_t x = rand() % nbstrategy; // on tire une position entre 0 et nb-1
        const Carte_Strategy *c = _carte_strtegy[x]; // on retient l'adresse
        for (size_t i = x + 1; i < nbstrategy; i++)
            _carte_strtegy[i - 1] = _carte_strtegy[i]; // on décale toutes les cartes aux rangs suivants
        nbstrategy--;
        return *c;
    }

    void Pioche::ajoutercarte(const Carte &c) {
//        if (nb == nbMax) {
//            const Carte **newtab = new const Carte *[(nbMax + 1) * 2];
//            for (size_t i = 0; 1 < nb; i++)
//                newtab[i] = cartes[i];
//            auto old = cartes;
//            cartes = newtab;
//            nbMax = (nbMax + 1) * 2;
//            delete[] old;
//        }
        cartes[nb++] = &c;
    }
    void Pioche::affiche() {
        for(int i=0 ; i<60 ; i++){
            std::cout<<getstring(cartes[i]->getNombre())<<std::endl;
            std::cout<<getstring(cartes[i]->getCouleur())<<std::endl;
        }
//        std::cout<<"all the generala";
        for(int j=0 ; j<10 ; j++){
            std::cout<<getstring(_carte_strtegy[j]->getStrategie())<<std::endl;
        }
    }

    void Pioche::ajouterstrategy(const Carte_Strategy &c) {
        _carte_strtegy[nbstrategy++] = &c;
    }

    Pioche::~Pioche() {
        delete[] cartes;
        delete[] _carte_strtegy;
    }

    ostream & operator<<(ostream& f,const Carte& _carte){
        f<<"Nombre:"<<_carte.getNombre()<<"\nCouleur:"<<getstring(_carte.getCouleur())<<endl;
        return f;
    }


}