#ifndef __BACKGROUND1_H__
#define __BACKGROUND1_H__

#include "cocos2d.h"
#include "Player.h"

class Background1 : public cocos2d::Scene
{
public:
    Background1();
    ~Background1();

    virtual bool init();
    static Background1* create();

    // �˳���ť�Ļص�����������˳���ťʱִ�еĲ���
    virtual void menuCloseCallback(cocos2d::Ref* pSender);

    // ��ӽ�ɫ��ָ��
    Player* _player;

    virtual void update(float dt);


private:

    // ������ʾ���λ�õ� Label
    cocos2d::Label* _positionLabel;

    // ������ʾ��ʱ�ı�ǩ
    cocos2d::Label* _timerLabel;  

    int remainingTime = 1200;

};

#endif // __BACKGROUND1_H__
