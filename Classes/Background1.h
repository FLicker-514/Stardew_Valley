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

    // 退出按钮的回调函数，点击退出按钮时执行的操作
    virtual void menuCloseCallback(cocos2d::Ref* pSender);

    // 添加角色的指针
    Player* _player;

    virtual void update(float dt);


private:

    // 用于显示玩家位置的 Label
    cocos2d::Label* _positionLabel;

    // 用于显示计时的标签
    cocos2d::Label* _timerLabel;  

    int remainingTime = 1200;

};

#endif // __BACKGROUND1_H__
