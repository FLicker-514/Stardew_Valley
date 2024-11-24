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
    
    // 添加角色的指针
    Player* _player;

    void update(float dt);


private:

    // 用于显示玩家位置的 Label
    cocos2d::Label* _positionLabel;

    // 用于显示计时的标签
    cocos2d::Label* _timerLabel;

    /* 提示按钮 */
    cocos2d::Label* _hintLabel; 

    // 标记玩家是否进入区域
    bool isInArea;  

    int remainingTime = 60000;

};

#endif // __BACKGROUND2_H__

