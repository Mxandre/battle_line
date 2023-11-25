//
// Created by xiangyang on 2023/10/25.
//

#ifndef SCHOTTEN_TOTTEN_CHATEAU_H
#define SCHOTTEN_TOTTEN_CHATEAU_H

#include<iostream>
#include"Carte.h"
#include<vector>
#include"algorithm"
#include <Windows.h>

using namespace std;
using namespace Carte_name;
namespace Chatrau_name{
    class Chateau_gerer;
}
class Plateau {     //玩家手牌
public:
    Plateau();

    ~Plateau() {
        delete[] cartes;
        delete[] _carte_strategy;
    }

    size_t getNbCartes() const { return nb; }

    void ajoutercarte(const Carte &c);

    void ajouterstrategy(const Carte_Strategy &c);

   void retirercarte(int ply,Pioche& _pioche,Chatrau_name::Chateau_gerer& _gerer);//出牌


    //void print (ostream& f = cout) const;
    Plateau(const Plateau &p) = delete;

    Plateau &operator=(const Plateau &p) = delete;

    void showCarte();

    friend void Judge_special7(Plateau& player,Carte_name::Pioche& _pioche,Chatrau_name::Chateau_gerer& _gerer);
private:
    const Carte **cartes = nullptr;
    const Carte_Strategy **_carte_strategy = nullptr;
    size_t nbMax = 10;
    size_t nb = 0;
    size_t nbstrategy = 0;
};

namespace Chatrau_name {
    using namespace Carte_name;
    enum Ascription {
        neutralite = 0, player1, player2
    };


    class Chateau {
    private:
        Ascription ascription = neutralite; //归属
        bool Si_occupe = 0; //***城堡的归属0：中立；1:被占有
        size_t position = 0;      //数字1~9有效，表示城堡位置
        std::vector<absCarte *> carte1;//玩家1一侧
        std::vector<absCarte *> carte2;//玩家2一侧

    public:
        Chateau(size_t i):position(i){}
        Chateau(const Chateau &) = delete;
        Chateau &operator=(const Chateau &) = delete;
        ~Chateau()=default;

        //这个石头是否包含策略卡用于判定。public为了节省逻辑。public easy to read and to get,
        bool si_tactic5 = 0;        //只包含迷雾（只比较数字）     1有0无
        bool si_tactic6 = 0;        //只包含沼泽（需要四张）       1有0无

//        static std::vector<Chateau> &getInstance_Chateau();
        //***函数内创建static 的城堡对象，保证每个城堡位置不同1~9，方法待优化。

        size_t& getPosition() { return position; }
        Ascription getAscription() const { return ascription; }    //判断有没有归属，并返回归属
        bool getoccupe()const {return Si_occupe;}
        Carte *getCarte(int ply, size_t ind) const;   //返回单张卡，可用于功能牌使用抽取一张
        void getCartes(int ply) const;   //返回城堡内的已有卡牌
        size_t getnb() const { return (carte1.size() + carte2.size()); }   //返回牌数
        void ajouter(absCarte *, int);//将卡牌添加到城堡内,每次调用之后进行判断
        void retirer_8(Chateau* , Chateau* , size_t , int );
        void retirer_9(Chateau* , size_t , int );
        void retirer_10(Chateau* , Chateau* , size_t , int );
        bool needjudge();//判断是否需要进行判断
    };

    class Chateau_gerer{
    private:
        static vector<const Carte*> bye_carte;
        static vector<const Carte_Strategy *> bye_carte_strategy;   //弃牌堆
        static Chateau** ptr_Chateau;
    public:
        Chateau_gerer();
        ~Chateau_gerer();
        static void ajouter_carteused(const Carte* a){bye_carte.push_back(a);}
        static void ajouter_strcarteused(const Carte_Strategy* a){bye_carte_strategy.push_back(a);}
        friend class Chateau;
        friend void Plateau::retirercarte(int ply,Pioche& _pioche,Chateau_gerer& _gerer);
        static void showall();
    };

}

    void Judge_special7(Plateau& player,Carte_name::Pioche& _pioche,Chatrau_name::Chateau_gerer& _gerer);


namespace Judge {
    using namespace Carte_name;
    using namespace Chatrau_name;

    enum Type_Cartes {
        general = 0, special
    };

    class Judgement {
    private:
        std::vector<absCarte *>& cartes1;
        std::vector<absCarte *>& cartes2;
        //(某石碑的)玩家一和玩家二的卡牌
        bool si5;//是否有迷雾
        bool si6;//是否有沼泽
    public:
        Judgement(std::vector<absCarte *>& a, std::vector<absCarte *>& b,bool _si5,bool _si6)
                : cartes1(a), cartes2(b), si5(_si5),si6(_si6) {}
        //从chateau获取卡牌和卡牌数量

        bool areConsecutive(int a, int b, int c) {      //连续性判断
            // 创建一个数组存储这三个数
            int numbers[] = {a, b, c};
            // 对数组进行排序
            std::sort(numbers, numbers + 3);
            // 检查它们是否是连续的
            return (numbers[0] + 1 == numbers[1] && numbers[1] + 1 == numbers[2]);
        }//卡牌数字的连续性检查
        bool areConsecutive2(int a,int b,int c, int d){
            int numbers[] = {a, b, c,d};
            // 对数组进行排序
            std::sort(numbers, numbers + 4);
            // 检查它们是否是连续的
            return (numbers[0] + 1 == numbers[1] && numbers[1] + 1 == numbers[2]&& numbers[2]+1 == numbers[3]);
        }//卡牌数字的连续性检查(4张情况)

        //总判断函数
        //调用普通卡牌判断
        const Ascription generatejudge() {
            Ascription c;
            c = Judge_ascription_general();
            return c;
        }

        const Ascription Judge_ascription_general();
        //所有判断

//        const Ascription &Judge_ascription_special2();
//        const Ascription &Judge_ascription_special3();
        static Couleur choosecolor();
        static Nombre choosenombre(int j);//从1-10数字中选择

        /********************************十二个特殊牌型的判断函数，由Judge_ascription_special调用******/

        static void Judge_special_change1(std::vector<absCarte *>& carte);

        static void  Judge_special_change2(std::vector<absCarte *>& carte) ;

        static void  Judge_special_change3_4(std::vector< absCarte *>& carte);//功能牌3/4共用

//          static const Ascription &Judge_ascription_special7() ;//与判定输赢无关,感觉更适合放在Carte内

//        static const Ascription &Judge_ascription_special8() {/*********/}与判定无关

//        static const Ascription &Judge_ascription_special9() {/*********/}
//
//        static const Ascription &Judge_ascription_special0() {/*********/}

        //1cavalry（骑兵）：此牌认为是任意颜色的8
        //2shield（盾牌）: 此牌可认为是任意的颜色的1、2或3
        //3darius（大流士）：此牌可认为任意颜色、任意数字
        //4Alexander（亚历山大）：同上	相同
        //5fog（迷雾）：使该城堡只能通过比较部队卡的数字才能获得胜利而无视牌型
        //6mud（沼泽）：使该城堡需四张部队卡才能组成牌型
        //7scout（侦察）：在卡堆中抓取三张牌，可同时抓取战术卡、部队卡，然后从手牌中放回两张牌
        //说明：放回的手牌类型必须与抓取的牌型相同，抓取两张功能牌，就必须至少放回一张功能牌
        //8redeploy（重新投入）：将已放入一阵地的任意类型的卡放入另一阵地（自己阵地内）
        //9deserter（逃亡者）：弃置未归属的一阵地的任意类型的卡牌（对方阵营）
        //10traitor（叛逆者）：将未归属的阵地中，对方任意类型的卡移动到己方指定的阵地中

    };

}
#endif //SCHOTTEN_TOTTEN_CHATEAU_H
