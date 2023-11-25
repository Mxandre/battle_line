#include <iostream>
#include "Chateau.h"
#include <vector>

using namespace Chatrau_name;
using namespace std;

int main() {
    Pioche _pioche;
    Plateau ply1;
    Plateau ply2;
    Chateau_gerer _gerer;
    int type_carte;
//    cout<<_pioche.getNbCartes()<<'\n';
    for(auto i=0;i<7;i++){
        ply1.ajoutercarte(_pioche.getcarte());
        ply2.ajoutercarte(_pioche.getcarte());
    }
    while (1){
        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),  FOREGROUND_RED|FOREGROUND_INTENSITY );
        cout<<"player 1, now is your turn "<<endl;
        Sleep(3000);//缓3s换人
        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),  FOREGROUND_GREEN|FOREGROUND_BLUE|FOREGROUND_RED );
        ply1.retirercarte(1,_pioche,_gerer);
//        cout<<"you want to draw normal carte or carte strategy? 0 for normal; 1 for strategy ";
//        cin>>type_carte;
//        if(type_carte==0)
//            ply1.ajoutercarte(_pioche.getcarte());
//        else if(type_carte==1)
//            ply1.ajouterstrategy(_pioche.getstrategy_carte());
//        else
//            throw "only for 0 and 1";
        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),  FOREGROUND_RED|FOREGROUND_INTENSITY );
        cout<<"player 2, now is your turn "<<endl;
        Sleep(3000);//缓3s换人
        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),  FOREGROUND_GREEN|FOREGROUND_BLUE|FOREGROUND_RED );
        ply2.retirercarte(2,_pioche,_gerer);
    }

    std::cout << "Hello, World!" << std::endl;
    return 0;
}
