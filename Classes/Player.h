#ifndef __PLAYER_H__
#define __PLAYER_H__

#include "cocos2d.h"

class Player : public cocos2d::Sprite
{
public:
    Player();
    ~Player();

    // ���� Player ����Ĺ�������
    static Player* create();

    // �����ƶ��ٶ�
    void setSpeed(float speed);

    // ���̰����¼��Ļص�����
    void onKeyPressed(cocos2d::EventKeyboard::KeyCode keyCode, cocos2d::Event* event);

    // �����ͷ��¼��Ļص�����
    void onKeyReleased(cocos2d::EventKeyboard::KeyCode keyCode, cocos2d::Event* event);

    bool isInRestrictedArea(float x, float y);

    std::vector<cocos2d::Rect> _restrictedAreas; // ��ֹ������б�

    cocos2d::Rect myhouse;     // ������ŵ�����

    bool ready_go_myhouse = 0;

private:
    // ��ʼ����ɫ
    bool init();

    // ��ɫ���ƶ��ٶ�
    float speed;

    // ��ɫ���ƶ�����
    bool moveUp, moveDown, moveLeft, moveRight;
};

#endif // __PLAYER_H__
