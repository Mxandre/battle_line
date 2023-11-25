//
// Created by xiangyang on 2023/10/25.
//

#include "Chateau.h"

using namespace Chatrau_name;
using namespace std;
using namespace Carte_name;

// vector<Chateau> &Chateau::getInstance_Chateau() {
//    static std::vector<Chateau> chateaus(9);//未知问题，析构函数仍然需要检查
//    for (size_t i = 0; i < 9; i++) {
//        chateaus[i].position = i;
//    }
//    return chateaus;
//}

Carte *Chateau::getCarte(int ply, size_t ind) const {
    if (ply == 1) { return dynamic_cast< Carte *>(carte1[ind]); }
    else if (ply == 2) { return dynamic_cast<Carte *>(carte2[ind]); }
    else { throw "Player Error!!"; }
}

void Chateau::getCartes(int ply) const {
    int i=1;
    switch (ply) {
        case 1:
            for(auto it:carte1){
                cout<<"Carte "<<i<<":"<<'\t';
                switch(it->getCouleur()){
                    case rouge:
                        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),  FOREGROUND_RED|FOREGROUND_INTENSITY );
                        cout<<it->getNombre()<<'\t';
                        break;
                    case vert:
                        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),  FOREGROUND_GREEN|FOREGROUND_INTENSITY );
                        cout<<it->getNombre()<<'\t';
                        break;
                    case bleu:
                        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),  FOREGROUND_BLUE|FOREGROUND_INTENSITY );
                        cout<<it->getNombre()<<'\t';
                        break;
                    case jaune:
                        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),  FOREGROUND_RED|FOREGROUND_GREEN|FOREGROUND_INTENSITY );
                        cout<<it->getNombre()<<'\t';
                        break;
                    case violet:
                        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),  FOREGROUND_RED|FOREGROUND_BLUE|FOREGROUND_INTENSITY );
                        cout<<it->getNombre()<<'\t';
                        break;
                    case orange:
                        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),  FOREGROUND_RED|FOREGROUND_GREEN);
                        cout<<it->getNombre()<<'\t';
                        break;
                    default:
                        break;
                }
                i++;
                SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
            }
            break;
        case 2:
            for(auto it:carte2){
                cout<<"Carte "<<i<<":"<<'\t';
                switch(it->getCouleur()){
                    case rouge:
                        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),  FOREGROUND_RED|FOREGROUND_INTENSITY );
                        cout<<it->getNombre()<<'\t';
                        break;
                    case vert:
                        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),  FOREGROUND_GREEN|FOREGROUND_INTENSITY );
                        cout<<it->getNombre()<<'\t';
                        break;
                    case bleu:
                        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),  FOREGROUND_BLUE|FOREGROUND_INTENSITY );
                        cout<<it->getNombre()<<'\t';
                        break;
                    case jaune:
                        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),  FOREGROUND_RED|FOREGROUND_GREEN|FOREGROUND_INTENSITY );
                        cout<<it->getNombre()<<'\t';
                        break;
                    case violet:
                        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),  FOREGROUND_RED|FOREGROUND_BLUE|FOREGROUND_INTENSITY );
                        cout<<it->getNombre()<<'\t';
                        break;
                    case orange:
                        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),  FOREGROUND_RED|FOREGROUND_GREEN);
                        cout<<it->getNombre()<<'\t';
                        break;
                    default:
                        break;
                }
                i++;
                SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
            }
            break;
    }
}


//在城堡添加卡牌 调用判定函数
void Chateau::ajouter(absCarte *carte_ajouter, int ply) {//ply==1/2

    if (Si_occupe == 1)
        throw "mauvaise position";//先判定是否已归属
    //紧接着是瞬时牌,不需要判定容量够不够

    //8 redeploy（重新投入）：将已放入一阵地的任意类型的卡放入另一阵地（自己阵地内）
    if (carte_ajouter->getStrategie() == redeploy) {
            size_t cha_nb, carte_nb;
        cout << "\nQuel Carte vous voulez retirer?" << "\t";
        cin >> carte_nb;//旧城堡中的第几张卡
        cout << "Quel Chateau vous voulez ajouter?" << "\t";
        cin >> cha_nb;//新的城堡
        if(cha_nb<1||cha_nb>9)
            throw "chateau inexistant";
        if(ply==1){
            if(carte_nb<1||carte_nb>carte1.size())
                throw "Carte inexitant";
        }
        else{
            if(carte_nb<1||carte_nb>carte2.size())
                throw "Carte inexitant";
        }
        //从旧的城堡中去除
        //加入新的城堡
        retirer_8(this, Chateau_gerer::ptr_Chateau[cha_nb - 1], carte_nb, ply);
        Chateau_gerer::ajouter_strcarteused(dynamic_cast<const Carte_Strategy *>(carte_ajouter));
    }

    else if (carte_ajouter->getStrategie() == deserter) {//9deserter（逃亡者）：弃置未归属的一阵地的任意类型的卡牌（对方阵营）
            size_t carte_nb;
            cout << "\nQuel Carte vous voulez retirer?" << "\t";
            cin >> carte_nb;//旧城堡中的第几张卡
            if (ply == 1) {
                if (carte_nb < 1 || carte_nb > carte2.size())
                    throw "Carte inexitant";
            } else {
                if (carte_nb < 1 || carte_nb > carte1.size())
                    throw "Carte inexitant";
            }
            //从旧的城堡中去除
            retirer_9(this, carte_nb, ply);    //在函数体内添加弃牌堆的操作
            Chateau_gerer::ajouter_strcarteused(dynamic_cast<const Carte_Strategy *>(carte_ajouter));
        }

    else if (carte_ajouter->getStrategie() == traitor) {//10traitor（叛逆者）：将未归属的阵地中，对方任意类型的卡移动到己方指定的阵地中
            size_t cha_nb, carte_nb;
            cout << "\nQuel Carte vous voulez retirer?" << "\t";
            cin >> carte_nb;//旧城堡中的第几张卡
            cout << "Quel Chateau vous voulez ajouter?" << "\t";
            cin >> cha_nb;//新的城堡
            if (cha_nb < 1 || cha_nb > 9)
                throw "chateau inexistant";
            if (ply == 1) {
                if (carte_nb < 1 || carte_nb > carte2.size())
                    throw "Carte inexitant";
            } else {
                if (carte_nb < 1 || carte_nb > carte1.size())
                    throw "Carte inexitant";
            }
            //从旧的城堡中去除
            //加入新的城堡
            retirer_10(this, Chateau_gerer::ptr_Chateau[cha_nb - 1], carte_nb, ply);
            Chateau_gerer::ajouter_strcarteused(dynamic_cast<const Carte_Strategy *>(carte_ajouter));
             std::cout << "ajouted successfully!" << std::endl;
        }
//接着是否是迷雾或沼泽

    else if (carte_ajouter->getStrategie() == 5) {//是迷雾
        si_tactic5 = 1; //有迷雾（比较数字）
        Chateau_gerer::ajouter_strcarteused(dynamic_cast<const Carte_Strategy *>(carte_ajouter));
        std::cout << "ajouted successfully!" << std::endl;
    }

    else if (carte_ajouter->getStrategie() == 6) {
        si_tactic6 = 1; //有沼泽（四张卡）
        Chateau_gerer::ajouter_strcarteused(dynamic_cast<const Carte_Strategy *>(carte_ajouter));
        std::cout << "ajouted successfully!" << std::endl;
    }
    //紧接着是能进入城堡里的牌，判断是否有位置

    else if (si_tactic6 == 1) {//有沼泽
        switch (ply) {
            case 1:
                if (carte1.size() == 4)
                    throw "cannot ajouter,there is no location";
            case 2:
                if (carte2.size() == 4)
                    throw "cannot ajouter,there is no location";
        }
    } else {//没有沼泽
        switch (ply) {
            case 1:
                if (carte1.size() == 3)
                    throw "cannot ajouter,there is no location";
                break;
            case 2:
                if (carte2.size() == 3)
                    throw "cannot ajouter,there is no location";
                break;
        }
        //开始加牌

        if (carte_ajouter->getStrategie() > 0 && carte_ajouter->getStrategie() < 5)//对判定牌大小有帮助的牌加入str1，str2
        {
            //加入替代数字的牌时需要判定场上是否有位置可以添加
            switch (ply) {
                case 1:
                    switch (carte_ajouter->getStrategie()) {
                        case 1:
                            Judge::Judgement::Judge_special_change1(carte1);
                            Chateau_gerer::ajouter_strcarteused(dynamic_cast<const Carte_Strategy *>(carte_ajouter));
                            break;
                        case 2:
                            Judge::Judgement::Judge_special_change2(carte1);
                            Chateau_gerer::ajouter_strcarteused(dynamic_cast<const Carte_Strategy *>(carte_ajouter));
                            break;
                        case 3:
                        case 4:
                            Judge::Judgement::Judge_special_change3_4(carte1);
                            Chateau_gerer::ajouter_strcarteused(dynamic_cast<const Carte_Strategy *>(carte_ajouter));
                            break;
                        default:
                            throw "error of ajouter cartes";
                    }
                    break;
                case 2:
                    switch (carte_ajouter->getStrategie()) {
                        case 1:
                            Judge::Judgement::Judge_special_change1(carte2);
                            Chateau_gerer::ajouter_strcarteused(dynamic_cast<const Carte_Strategy *>(carte_ajouter));
                            break;
                        case 2:
                            Judge::Judgement::Judge_special_change2(carte2);
                            Chateau_gerer::ajouter_strcarteused(dynamic_cast<const Carte_Strategy *>(carte_ajouter));
                            break;
                        case 3:
                        case 4:
                            Judge::Judgement::Judge_special_change3_4(carte2);
                            Chateau_gerer::ajouter_strcarteused(dynamic_cast<const Carte_Strategy *>(carte_ajouter));
                            break;
                        default:
                            throw "error of ajouter cartes";
                    }
                    break;
            }
            std::cout << "ajouted successfully!" << std::endl;
        } else if (carte_ajouter->getStrategie() == 0){//是普通牌
                     if(ply==1)
                         carte1.push_back(carte_ajouter);
                       else
                         carte2.push_back(carte_ajouter);
            std::cout << "ajouted successfully!" << std::endl;
            }
        }

        if (needjudge()) {
            Judge::Judgement jud(carte1, carte2, si_tactic5, si_tactic6);
            ascription = jud.generatejudge();
            SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_INTENSITY | FOREGROUND_RED );

            if (!ascription)
                cout<<"the score is equal,this chateau has not been occupied by any player"<<endl;
            else
                std::cout << "\n!!Stone monument No." << getPosition()+1 << " has been occupied by player"<<ascription << std::endl;
            Si_occupe = 1;
            Sleep(3000);
            SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_INTENSITY | FOREGROUND_GREEN | FOREGROUND_BLUE|FOREGROUND_RED);

        }
    }

//判断是否判定
bool Chateau::needjudge(){
    if (!si_tactic6)//     无6策略 沼泽（四张卡）
    return carte1.size()+carte2.size()==6;
    else //  有6号策略 沼泽（四张卡）
        return carte1.size()+carte2.size()==8;
 }

 //-----------------chateau_gerer-----------------//

    Chateau** Chatrau_name::Chateau_gerer:: ptr_Chateau=new Chateau*[9];
    vector<const Carte*> Chatrau_name::Chateau_gerer::bye_carte={};
    vector<const Carte_Strategy *>  Chatrau_name::Chateau_gerer::bye_carte_strategy={};

Chatrau_name::Chateau_gerer::Chateau_gerer(){
    for(size_t i=0;i<9;i++)
        ptr_Chateau[i]=new Chateau(i);      //*ptr_Chateau 访问；
}//9个城堡

Chatrau_name::Chateau_gerer::~Chateau_gerer() {
    for(size_t i=0 ; i<10 ; i++)
        delete []ptr_Chateau[i];//元素里不是数组形势new出来的，需要[]吗?
    delete []ptr_Chateau;//?
}

void Chatrau_name::Chateau_gerer::showall() {
    for (int i = 0; i < 9; i++) {
        cout<<"player 1 :\t";
        ptr_Chateau[i]->getCartes(1);
        if(ptr_Chateau[i]->getoccupe()){
            SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_INTENSITY | FOREGROUND_RED);
            cout<<"Chateau"<<i+1<<"("<<ptr_Chateau[i]->getAscription()<<")"<<'\t';
            SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_INTENSITY | FOREGROUND_RED|FOREGROUND_GREEN|FOREGROUND_BLUE);
        }
        else{
            if(ptr_Chateau[i]->si_tactic5==1&& ptr_Chateau[i]->si_tactic6==1){
                cout<<"Chateau"<<i+1<<'\t';
                SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),FOREGROUND_RED|FOREGROUND_INTENSITY);
                cout<<"fog"<<'\t'<<"mud"<<'\t';
                SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
            }
            else if(ptr_Chateau[i]->si_tactic5==1){
                cout<<"Chateau"<<i+1<<'\t';
                SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),FOREGROUND_RED|FOREGROUND_INTENSITY);
                cout<<"fog"<<'\t';
                SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
            }
            else if(ptr_Chateau[i]->si_tactic6==1){
                cout<<"Chateau"<<i+1<<'\t';
                SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),FOREGROUND_RED|FOREGROUND_INTENSITY);
                cout<<"mud"<<'\t';
                SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
            }
            else{
                cout<<"Chateau"<<i+1<<'\t';
            }
        }
        cout<<"player 2 :\t";
        ptr_Chateau[i]->getCartes(2);
        cout<<'\n';
    }
}


//---------------------plateau---------------------//

Plateau::Plateau() {
    cartes = new const Carte *[nbMax];
    _carte_strategy = new const Carte_Strategy *[nbMax];
}

void Plateau::ajoutercarte(const Carte &c) {
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

void Plateau::ajouterstrategy(const Carte_Strategy &c) {
    _carte_strategy[nbstrategy++] = &c;
}

void Plateau::retirercarte(int ply,Pioche& _pioche,Chateau_gerer& _gerer) {
    size_t j=0;
    int type_carte;
    size_t carte_num;
    Chateau_gerer::showall();//
    showCarte();
    cout<<"you want to retirer quelle type de Carte?enter 0 pour normal,1 pour strategy"<<endl;
    cin>>type_carte;
    if(type_carte==0){
        cout<<"you want to retirer quelle Carte ?please enter the ordre numer"<<endl;
        cin>>carte_num;//哪一张牌
        if (carte_num > nb) throw gameException("Carte inexistante");
        cout<<"you want to ajouter dans quel chateau 1~9"<<endl;
        cin>>j;//哪一个城堡
        _gerer.ptr_Chateau[j-1]->ajouter(const_cast<Carte*>(cartes[--carte_num]),ply);
        ++carte_num;
        while (carte_num < nb) {
            cartes[carte_num - 1] = cartes[carte_num];
            ++carte_num;
        }
        nb--;
        cout<<"you want to draw normal carte or carte strategy? 0 for normal; 1 for strategy ";
        cin>>type_carte;
        if(type_carte==0)
            ajoutercarte(_pioche.getcarte());
        else if(type_carte==1)
            ajouterstrategy(_pioche.getstrategy_carte());
        else
            throw "only for 0 and 1";
    }
    else{
        cout<<"you want to retirer quelle Carte ?please enter the ordre numer"<<endl;
        cin>>carte_num;//哪一张牌
        if (carte_num > nbstrategy) throw gameException("Carte inexistante");
        if(_carte_strategy[carte_num-1]->getStrategie()==7){//是抽牌的功能卡//这种情况出完牌后不用抽牌
            if(carte_num==nbstrategy)
                _carte_strategy[carte_num-1]= nullptr;//如果使用7后手牌中还是只有一张功能牌，此时无法递归覆盖原有的，直接置为空指针
            else {
                while (carte_num < nbstrategy) {    //若此时手牌只有一张功能牌，应该变为空指针
                    _carte_strategy[carte_num - 1] = _carte_strategy[carte_num];//功能牌重新更新
                    carte_num++;
                }//得先把牌拿掉，才能方便进行后面的选牌弃掉
            }
            nbstrategy--;
            Judge_special7(*this,_pioche,_gerer);
        }
        else{
            cout<<"you want to ajouter dans quel chateau 1~9"<<endl;
            cin>>j;//哪一个城堡
            //cout<<j;
            _gerer.ptr_Chateau[j-1]->ajouter(const_cast<Carte_Strategy*>(_carte_strategy[--carte_num]),ply);
            //Chatrau_name::Chateau_gerer::ptr_Chateau[j-1]->ajouter(const_cast<Carte_Strategy*>(_carte_strategy[--carte_num]),ply);//送到对应城堡
            ++carte_num;    //剔除的下一张数组序号
            if(nbstrategy==1)
                _carte_strategy[carte_num-1]= nullptr;//如果使用7后手牌中还是只有一张功能牌，此时无法递归覆盖原有的，直接置为空指针
            else{
                while (carte_num < nbstrategy) {    //若此时手牌只有一张功能牌，应该变为空指针
                    _carte_strategy[carte_num - 1] = _carte_strategy[carte_num];//功能牌重新更新
                    carte_num++;
                }
            }
            nbstrategy--;
            cout<<"you want to draw normal carte or carte strategy? 0 for normal; 1 for strategy ";
            cin>>type_carte;
            if(type_carte==0)
                ajoutercarte(_pioche.getcarte());
            else if(type_carte==1)
                ajouterstrategy(_pioche.getstrategy_carte());
            else
                throw "only for 0 and 1";
        }
    }
}


void Plateau::showCarte() {
    cout<<"this is your cartes"<<endl;
    for(auto i=0;i<nb;i++){
        std::cout<<"Carte"<<i+1<<":";
        switch(cartes[i]->getCouleur()){
            case rouge:
                SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),  FOREGROUND_RED|FOREGROUND_INTENSITY );
                cout<<cartes[i]->getNombre()<<'\t';
                break;
            case vert:
                SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),  FOREGROUND_GREEN|FOREGROUND_INTENSITY );
                cout<<cartes[i]->getNombre()<<'\t';
                break;
            case bleu:
                SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),  FOREGROUND_BLUE|FOREGROUND_INTENSITY );
                cout<<cartes[i]->getNombre()<<'\t';
                break;
            case jaune:
                SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),  FOREGROUND_RED|FOREGROUND_GREEN|FOREGROUND_INTENSITY );
                cout<<cartes[i]->getNombre()<<'\t';
                break;
            case violet:
                SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),  FOREGROUND_RED|FOREGROUND_BLUE|FOREGROUND_INTENSITY );
                cout<<cartes[i]->getNombre()<<'\t';
                break;
            case orange:
                SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),  FOREGROUND_RED|FOREGROUND_GREEN);
                cout<<cartes[i]->getNombre()<<'\t';
                break;
            default:
                break;
        }
        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
    }
    cout<<'\n';
    for(auto i=0;i<nbstrategy;i++){
        std::cout<<"Strategie"<<i+1<<":";
        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),FOREGROUND_INTENSITY|FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);//加粗白字体，显示策略名称
        cout<<getstring(_carte_strategy[i]->getStrategie())<<'\t';
        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
    }
    cout<<'\n';
}

//----------------------Judge7----------------------//

void Judge_special7(Plateau& player,Carte_name::Pioche& _pioche,Chatrau_name::Chateau_gerer& _gerer) {
    int num1, num2; //num1: general  num2: statique
    cout << "vous voulez combien de carte normal et combien de carte strategie?" << endl;
    cin >> num1 >> num2;
    if (num1 < 0 || num1 > 3 || num2 < 0 || num2 > 3)
        throw "number incorrect";
    for (auto i = 0; i < num1; i++) {
        player.ajoutercarte(_pioche.getcarte());
    }
    for (auto i = 0; i < num2; i++) {
        player.ajouterstrategy(_pioche.getstrategy_carte());
    }
    player.showCarte();
    int renum1, renum2;
    cout << "vous voulez retirer combien de carte normal et combien de carte strategie?(how many)" << endl;
    cin >> renum1 >> renum2;
    if(renum1<0||renum1>2||renum2<0||renum2>2)
        throw "error of the nombre de retirer";
    if (num1 == 0) {//抽了0张普通
        if (renum1 != 0)
            throw "must retirer le same type  of carte";
    } else if (num1 == 1 || num1 == 2) {//抽了一张或两张普通
        if (renum2 == 0 || renum2 > 1)//还了0张功能或全是功能
            throw "must retirer le same type  of carte";
    }
    else if(num1==3){
        if (renum2!=0)
            throw "must retirer le same type  of carte";
    }
    int car[2];
    if(renum1==2&&renum2==0){
        cout<<"vous voulez quelles cartes pour retirer?(which one)"<<endl;
        cin>>car[0]>>car[1];
        if(car[0]<car[1]){//先把后面的整理好
            for(auto i=1;i>=0;i--){
                _gerer.ajouter_carteused(player.cartes[--car[i]]);//放入弃牌堆中
                car[i]++;
                while (car[i] < player.nb) {
                    player.cartes[car[i]-1] = player.cartes[car[i]];
                    car[i]++;
                }
                player.nb--;
            }
        }
        else if(car[0]>car[1]){
            for(auto i=0;i<=renum1;i++){
                _gerer.ajouter_carteused(player.cartes[--car[i]]);//放入弃牌堆中
                car[i]++;
                while (car[i] < player.nb) {
                    player.cartes[car[i]-1] = player.cartes[car[i]];
                    car[i]++;
                }
                player.nb--;
            }
        }
        else {
            throw "please choose different cartes";
        }
    }
    else if(renum1==1&&renum2==1){
        cout<<"vous voulez quelle carte normalle et carte strategie pour retirer?(which one)"<<endl;
        cin>>car[0]>>car[1];
        _gerer.ajouter_carteused(player.cartes[--car[0]]);//放入弃牌堆中
        car[0]++;
        while (car[0] < player.nb) {
            player.cartes[car[0]-1] = player.cartes[car[0]];
            car[0]++;
        }
        player.nb--;
        //---------------先把普通牌搞定--------------//
        _gerer.ajouter_strcarteused(player._carte_strategy[--car[1]]);//加入弃牌堆中
        car[1]++;
        while (car[1] < player.nbstrategy) {
            player._carte_strategy[car[1]-1] = player._carte_strategy[car[1]];
            car[1]++;
        }
        player.nbstrategy--;
    }
    else if (renum2==2&& renum1==0){
        cout<<"vous voulez quelles cartes pour retirer?(which one)"<<endl;
        cin>>car[0]>>car[1];
        if(car[0]<car[1]){//先把后面的整理好
            for(auto i=1;i>=0;i--){
                _gerer.ajouter_strcarteused(player._carte_strategy[--car[i]]);//放入弃牌堆中
                car[i]++;
                while (car[i] < player.nbstrategy) {
                    player._carte_strategy[car[i]-1] = player._carte_strategy[car[i]];
                    car[i]++;
                }
                player.nbstrategy--;
            }
        }
        else if(car[0]>car[1]){
            for(auto i=0;i<=renum1;i++){
                _gerer.ajouter_strcarteused(player._carte_strategy[--car[i]]);//放入弃牌堆中
                car[i]++;
                while (car[i] < player.nbstrategy) {
                    player._carte_strategy[car[i]-1] = player._carte_strategy[car[i]];
                    car[i]++;
                }
                player.nbstrategy--;
            }
        }
        else {
            throw "please choose different cartes";
        }


    }
}


//常规性胜利判定
const Ascription Judge::Judgement::Judge_ascription_general() {
    int sco1 = 0, sco2 = 0; //sco1 玩家1得分    sco2 玩家二得分
    if (si5 == 0 && si6 == 0) {//没有迷雾和沼泽
        //有牌型的判断
        if (areConsecutive(cartes1[0]->getNombre(), cartes1[1]->getNombre(), cartes1[2]->getNombre())) {
            sco1 += 2;  //顺子加2
            if (cartes1[0]->getCouleur() == cartes1[1]->getCouleur() &&
                cartes1[2]->getCouleur() == cartes1[1]->getCouleur()) {
                sco1 += 3;  //同花加2 同花伴随顺子，同花顺大于三条大于顺子
            }
        }

        if (cartes1[0]->getNombre() == cartes1[1]->getNombre() &&
            cartes1[1]->getNombre() == cartes1[2]->getNombre()) {
            sco1 += 4;  //三条加4
        }


        //玩家一结束
        if (areConsecutive(cartes2[0]->getNombre(), cartes2[1]->getNombre(), cartes2[2]->getNombre())) {
            sco2 += 2;
            if (cartes2[0]->getCouleur() == cartes2[1]->getCouleur() &&
                cartes2[2]->getCouleur() == cartes2[1]->getCouleur()) {
                sco2 += 3;
            }
        }

        if (cartes2[0]->getNombre() == cartes2[1]->getNombre() &&
            cartes2[1]->getNombre() == cartes2[2]->getNombre()) {
            sco2 += 4;
        }

        if (sco1 != sco2) {
            bool winner = sco1 > sco2;
            switch (winner) {
                case true:
                    return player1;
                case false:
                    return player2;
            }// judge here once in order to reduce amount of calculation.
        }

            //高牌判断
        else {
            sco1 += cartes1[0]->getNombre();
            sco1 += cartes1[1]->getNombre();
            sco1 += cartes1[2]->getNombre();
            sco2 += cartes2[0]->getNombre();
            sco2 += cartes2[1]->getNombre();
            sco2 += cartes2[2]->getNombre();
        }

        if (sco1 != sco2) {
            bool winner = sco1 > sco2;
            switch (winner) {
                case true:
                    return player1;
                case false:
                    return player2;
            }// judge finale.
        }
        return neutralite;
    }
    else  if(si6==1)//有沼泽
    {
        if (si5 == 1)//也有迷雾，此时只用比较大小
        {
            sco1 += cartes1[0]->getNombre();
            sco1 += cartes1[1]->getNombre();
            sco1 += cartes1[2]->getNombre();
            sco1 += cartes1[3]->getNombre();
            sco2 += cartes2[0]->getNombre();
            sco2 += cartes2[1]->getNombre();
            sco2 += cartes2[2]->getNombre();
            sco2 += cartes2[3]->getNombre();
            if (sco1 != sco2) {
                bool winner = sco1 > sco2;
                switch (winner) {
                    case true:
                        return player1;
                    case false:
                        return player2;
                }// judge finale.
            } else
                return neutralite;
        } else {//没有迷雾，正常4张比较
            if (areConsecutive2(cartes1[0]->getNombre(), cartes1[1]->getNombre(),
                                cartes1[2]->getNombre(), cartes1[3]->getNombre())) {
                sco1 += 2;  //顺子加3
                if (cartes1[0]->getCouleur() == cartes1[1]->getCouleur() &&
                    cartes1[1]->getCouleur() == cartes1[2]->getCouleur() &&
                    cartes1[2]->getCouleur() == cartes1[3]->getCouleur()) {
                    sco1 += 3;  //同花加2 同花伴随顺子，同花顺大于三条大于顺子
                }
            }

            if (cartes1[0]->getNombre() == cartes1[1]->getNombre() &&
                cartes1[1]->getNombre() == cartes1[2]->getNombre() &&
                cartes1[2]->getNombre() == cartes1[3]->getNombre()) {
                sco1 += 4;  //三条加4
            }


            //玩家一结束
            if (areConsecutive2(cartes2[0]->getNombre(), cartes2[1]->getNombre(), cartes2[2]->getNombre(),
                                cartes2[3]->getNombre())) {
                sco2 += 2;
                if (cartes2[0]->getCouleur() == cartes2[1]->getCouleur() &&
                    cartes2[2]->getCouleur() == cartes2[1]->getCouleur() &&
                    cartes2[2]->getCouleur() == cartes2[3]->getCouleur()) {
                    sco2 += 3;
                }
            }

            if (cartes2[0]->getNombre() == cartes2[1]->getNombre() &&
                cartes2[1]->getNombre() == cartes2[2]->getNombre() &&
                cartes2[2]->getNombre() == cartes2[3]->getNombre()) {
                sco2 += 4;
            }

            if (sco1 != sco2) {
                bool winner = sco1 > sco2;
                switch (winner) {
                    case true:
                        return player1;
                    case false:
                        return player2;
                }// judge here once in order to reduce amount of calculation.
            }

                //高牌判断
            else {
                sco1 += cartes1[0]->getNombre();
                sco1 += cartes1[1]->getNombre();
                sco1 += cartes1[2]->getNombre();
                sco1 += cartes1[3]->getNombre();
                sco2 += cartes2[0]->getNombre();
                sco2 += cartes2[1]->getNombre();
                sco2 += cartes2[2]->getNombre();
                sco2 += cartes2[3]->getNombre();
                if (sco1 != sco2) {
                    bool winner = sco1 > sco2;
                    switch (winner) {
                        case true:
                            return player1;
                        case false:
                            return player2;
                    }// judge finale.
                } else
                    return neutralite;
            }

        }
    }
    else{//只有迷雾，3张比大小
        sco1 += cartes1[0]->getNombre();
        sco1 += cartes1[1]->getNombre();
        sco1 += cartes1[2]->getNombre();
        sco2 += cartes2[0]->getNombre();
        sco2 += cartes2[1]->getNombre();
        sco2 += cartes2[2]->getNombre();
        if (sco1 != sco2) {
            bool winner = sco1 > sco2;
            switch (winner) {
                case true:
                    return player1;
                case false:
                    return player2;
            }// judge finale.
        } else
            return neutralite;
    }

}


//特殊卡，变换型 1~4
void    Judge::Judgement::Judge_special_change1(std::vector<absCarte *>& carte){
    carte.push_back(new Carte(huit,choosecolor()));
 }//代替任何颜色的8

void    Judge::Judgement::Judge_special_change2(std::vector<absCarte *>& carte){
     carte.push_back(new Carte(choosenombre(3),choosecolor()));
 }//任意颜色的1，2，3

void  Judge::Judgement::Judge_special_change3_4(std::vector< absCarte *>& carte){
     carte.push_back(new Carte(choosenombre(10),choosecolor()));
 }//代替任何颜色任何数字
 //直接在Chateau  的卡内添加选择好的新卡

 //特殊卡， 替换添补类型 8~10

 //retirer 定义在Chateau内的函数
//自己的阵地中的卡牌调动
 void Chateau::retirer_8(Chateau * ptr_old, Chateau * ptr_new, size_t nb_carte, int palyer) {
     if (palyer==1){
         ptr_new->ajouter(ptr_old->carte1[nb_carte-1],player1);
         ptr_old->carte1.erase(ptr_old->carte1.begin() + nb_carte - 1);}
     else{
         ptr_new->ajouter(ptr_old->carte2[nb_carte-1],player2);
         ptr_old->carte2.erase(ptr_old->carte2.begin() + nb_carte - 1);}
 }//
//弃置对面阵地卡牌
void Chateau::retirer_9(Chateau * ptr, size_t nb_carte, int palyer) {
    //先放入弃牌堆，再将chateau内的卡牌删除
    if (palyer==1){
        Chateau_gerer::ajouter_carteused(dynamic_cast<Carte*>(ptr->carte2[nb_carte-1]));
        ptr->carte2.erase(ptr->carte2.begin() + nb_carte - 1);
    }
    else{
        Chateau_gerer::ajouter_carteused(dynamic_cast<Carte*>(ptr->carte2[nb_carte-1]));
        ptr->carte1.erase(ptr->carte1.begin() + nb_carte - 1);
    }
}
//对方牌移到自己这
void Chateau::retirer_10(Chateau * ptr_old, Chateau * ptr_new, size_t nb_carte, int palyer) {
    if (palyer==1){
        ptr_new->ajouter(ptr_old->carte2[nb_carte-1],player1);
        ptr_old->carte2.erase(ptr_old->carte2.begin() + nb_carte - 1);
        cout<<"hello";
    }
    else{
        ptr_new->ajouter(ptr_old->carte1[nb_carte-1],player2);
        ptr_old->carte1.erase(ptr_old->carte1.begin() + nb_carte - 1);
        cout<<"hello";

    }
}//对方牌移到自己这

//颜色选择
Couleur Judge::Judgement::choosecolor(){
     int i;
     cout<<"vous voulez quelle couleur?jaune est 1, vert 2, rouge 3, bleu 4, orange 5, violet 6"<<endl;
     cin>>i;
    switch (i){
        case 1:
            return jaune;
        case 2:
            return vert;
        case 3:
            return rouge;
        case 4:
            return bleu;
        case 5:
            return orange;
        case 6:
            return violet;
        default:
            throw "error de numero";
    }
 }

 //数字选择
Nombre  Judge::Judgement::choosenombre(int j){
     int i;
     cout<<"vous voulez quelle numero?1-"<<j<<endl;
     cin>>i;
     if(i>j||i<0)
         throw "error of numero";
     else{
         switch (i) {
             case 1:
                 return un;
             case 2:
                 return deux;
             case 3:
                 return trois;
             case 4:
                 return quatre;
             case 5:
                 return cinq;
             case 6:
                 return six;
             case 7:
                 return sept;
             case 8:
                 return huit;
             case 9:
                 return neuf;
             case 10:
                 return dix;
             default:
                 throw "error";
         }
     }
 }

