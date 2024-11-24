#ifndef __PLAYER_H__
#define __PLAYER_H__

#include "cocos2d.h"

class Player : public cocos2d::Sprite
{
public:
    Player();
    ~Player();

    // 创建 Player 对象的工厂方法
    static Player* create();

    // 设置移动速度
    void setSpeed(float speed);

    // 键盘按下事件的回调函数
    void onKeyPressed(cocos2d::EventKeyboard::KeyCode keyCode, cocos2d::Event* event);

    // 键盘释放事件的回调函数
    void onKeyReleased(cocos2d::EventKeyboard::KeyCode keyCode, cocos2d::Event* event);

    bool isInRestrictedArea(float x, float y);

    std::vector<cocos2d::Rect> _restrictedAreas; // 禁止区域的列表

    cocos2d::Rect myhouse;     // 进入家门的区域

    bool ready_go_myhouse = 0;

private:
    // 初始化角色
    bool init();

    // 角色的移动速度
    float speed;

    // 角色的移动方向
    bool moveUp, moveDown, moveLeft, moveRight;
};

#endif // __PLAYER_H__
