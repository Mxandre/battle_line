//
// Created by xiangyang on 2023/10/25.
//

#ifndef SCHOTTEN_TOTTEN_CARTE_H
#define SCHOTTEN_TOTTEN_CARTE_H

#include<string>
#include<iostream>
#include<time.h>
//#include "Chateau.h"
//extern void Judge_special7(Carte_name::Plateau& player,Carte_name::Pioche& _pioche,Chatrau_name::Chateau_gerer& gerer);
using namespace std;
class gameException {
    std::string info;
public:
    gameException(const std::string &s) : info(s) {}

    const std::string &get_info() const { return info; }
};

namespace Carte_name {




    enum Nombre {
        nombre_default=0, un , deux, trois, quatre, cinq, six, sept, huit, neuf, dix
    };    // nombre_default
    //号码

    enum Couleur {
        couleur_default=0 , jaune , vert, rouge, bleu, orange, violet
    };    //couleur_default
    //花色

    enum Strategie {
        non = 0, cavalry , shield, darius, alxandre, fod, mud, scout, redeploy, deserter, traitor
    };

    std::string getstring(Nombre nom);

    std::string getstring(Couleur cou);

    std::string getstring(Strategie str);


    class absCarte {
    public:
        //virtual size_t getType() const = 0;
        virtual Nombre getNombre() const = 0;
        // virtual std::string getNombre() const = 0;
        virtual Couleur getCouleur() const = 0;
        //virtual std::string getCouleur() const = 0;
        virtual Strategie getStrategie() const { return non; }
        //virtual std::string getStrategie() const = 0;
        virtual ~absCarte() = default;
    };

    class Carte : public absCarte {
    private:
        Nombre nombre;
        Couleur couleur;
        const static size_t TYPE = 0;   //0一般卡
    public:
        Carte(Nombre n, Couleur c) : nombre(n), couleur(c) {}

        Nombre getNombre() const { return nombre; }
        //std::string getNombre() const{return getstring(nombre);}

        Couleur getCouleur() const { return couleur; }
        //std::string getCouleur() const { return getstring(couleur);}
        void getCarte() {}   //**********获取卡牌，之后利用QT

        Strategie getStrategie() const { return non; }

        //size_t getType() const override { return TYPE; }

        ~Carte() = default; // optionnel

        Carte(const Carte &c) = delete; // 禁止重复出现相同卡牌

        Carte &operator=(const Carte &c) = delete; // 禁止重复出现相同卡牌

        void affiche() const {
            std::cout<<getstring(getNombre())<<std::endl;
            std::cout << getstring(getCouleur()) << std::endl;
        }


    };

    class Carte_Strategy : public absCarte {
    private:
        Strategie description;        //策略名称
        size_t nb_stra;
        const static size_t TYPE = 1;
    public:
        Nombre getNombre() const { return nombre_default; }

        Couleur getCouleur() const { return couleur_default; }

        Strategie getStrategie() const { return description; }

        Carte_Strategy(Strategie descri) : description(descri) {}

        Carte_Strategy(Strategie descri, size_t n) : description(descri),nb_stra(n){}

        ~Carte_Strategy() = default;

        size_t getType()const { return TYPE; }


        Carte_Strategy(const Carte_Strategy &c) = delete; // 禁止重复出现相同策略卡牌
        Carte_Strategy &operator=(const Carte_Strategy &c) = delete; // 禁止重复出现相同策略卡牌

        void affiche() const{
            std::cout<<getstring(getStrategie())<<std::endl;
        }
    };
//
//
    class Jeu {
    public:
        static Jeu &getInstance() { //对卡牌地址的复用要通过Jeu的单例模式Jeu::getInstance实现
            static Jeu jeu;
            return jeu;
        }

        size_t getNbCartes() const { return 60; }

        size_t getNbCartes_Strategy() const {return 10;}

        //size_t getNbCarte_strategy() const { return 10; }

        const Carte &getCarte(size_t i) const {
            if (i >= 60)
                throw gameException("Carte invalide");
            return *cartes[i];
        }

        const Carte_Strategy &getCarte_Strategy(size_t i) const {
            if (i >= 10)
                throw gameException("Carte invalide");
            return *_carte_strategy[i];
        }

    private:
        Jeu();

        Jeu(const Jeu &j) = delete;

        Jeu &operator=(const Jeu &j) = delete;

        ~Jeu();

        const Carte *cartes[60];
        const Carte_Strategy *_carte_strategy[10];
    };

//
    class Pioche {// désigne un paquet de cartes on l'on ne peut que piocher : prendre une carte au hasard 牌堆
    public:
        Pioche();    // construction d'une pioche à partir du jeu

        bool estVide() const { return nb == 0; }

        size_t getNbCartes() const { return nb; }

        size_t getNbcarte_strategy() const { return nbstrategy; }

        const Carte &getcarte();

        const Carte_Strategy &getstrategy_carte();

        void ajoutercarte(const Carte &c);

        void ajouterstrategy(const Carte_Strategy &c);

        ~Pioche();

        Pioche(const Pioche &p) = delete;

        Pioche &operator=(const Pioche &p) = delete;

        void affiche();

        //friend void Judge_special7(Carte_name::Plateau& player,Carte_name::Pioche& _pioche,Chatrau_name::Chateau_gerer& gerer);
    private:
        const Carte **cartes = nullptr;
        const Carte_Strategy **_carte_strtegy = nullptr;
        size_t nb = 0;
        size_t nbstrategy = 0;
    };

    ostream & operator<<(ostream& f,const Carte& _carte);

}

#endif //SCHOTTEN_TOTTEN_CARTE_H
