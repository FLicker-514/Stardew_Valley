#ifndef __BACKGROUND2_H__
#define __BACKGROUND2_H__

#include "cocos2d.h"
#include "Player.h"
#include "Background1.h"

class Background2 : public Background1
{
public:
   
    Background2();
    ~Background2();

    bool init();
    static Background2* create();
    
    // ��ӽ�ɫ��ָ��
    Player* _player;

    void update(float dt);


private:

    // ������ʾ���λ�õ� Label
    cocos2d::Label* _positionLabel;

    // ������ʾ��ʱ�ı�ǩ
    cocos2d::Label* _timerLabel;

    /* ��ʾ��ť */
    cocos2d::Label* _hintLabel; 

    // �������Ƿ��������
    bool isInArea;  

    int remainingTime = 60000;

};

#endif // __BACKGROUND2_H__

