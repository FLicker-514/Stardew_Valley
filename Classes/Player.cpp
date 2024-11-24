#include "Player.h"
#include "myhouse.h"

USING_NS_CC;

Player::Player() : speed(100.0f), moveUp(false), moveDown(false), moveLeft(false), moveRight(false) {}

Player::~Player() {}

bool Player::init()
{
    if (!Sprite::init())
    {
        return false;
    }

    // 加载角色的图片
    this->initWithFile("player_stop.png");


    // 注册键盘事件
    auto listener = EventListenerKeyboard::create();
    listener->onKeyPressed = CC_CALLBACK_2(Player::onKeyPressed, this);
    listener->onKeyReleased = CC_CALLBACK_2(Player::onKeyReleased, this);

    // 将键盘事件监听器添加到事件分发器
    _eventDispatcher->addEventListenerWithSceneGraphPriority(listener, this);

    return true;
}

Player* Player::create()
{
    Player* player = new Player();
    if (player && player->init())
    {
        player->autorelease();
        return player;
    }
    CC_SAFE_DELETE(player);
    return nullptr;
}

void Player::setSpeed(float speed)
{
    this->speed = speed;
}


void Player::onKeyPressed(EventKeyboard::KeyCode keyCode, Event* event)
{

    float X = this->getPositionX();
    float Y = this->getPositionY();


    if (ready_go_myhouse == true) {

        if (keyCode == EventKeyboard::KeyCode::KEY_ENTER) {
            auto nextScene = myhouse::create();  // 创建下一个场景
            Director::getInstance()->replaceScene(TransitionCrossFade::create(1.0f, nextScene));  // 用淡入效果切换场景
        }

    }

    // 判断按下的方向键，并更新角色的移动状态
    if (keyCode == EventKeyboard::KeyCode::KEY_UP_ARROW && !moveUp)  // 上箭头
    {
        moveUp = true;
        if (!isInRestrictedArea(X, Y + speed)) {
            this->setPositionY(this->getPositionY() + speed);  // 只移动一次
            this->setTexture("player_up.png");  
        }
    }
    else if (keyCode == EventKeyboard::KeyCode::KEY_DOWN_ARROW && !moveDown)  // 下箭头
    {
        moveDown = true;
        if (!isInRestrictedArea(X, Y - speed)) {
            this->setPositionY(this->getPositionY() - speed);  
            this->setTexture("player_down.png"); 
        }
    }
    else if (keyCode == EventKeyboard::KeyCode::KEY_LEFT_ARROW && !moveLeft)  // 左箭头
    {
        moveLeft = true;
        if (!isInRestrictedArea(X - speed, Y)) {
            this->setPositionX(this->getPositionX() - speed);  // 只移动一次
            this->setTexture("player_left.png");  
        }
    }
    else if (keyCode == EventKeyboard::KeyCode::KEY_RIGHT_ARROW && !moveRight)  // 右箭头
    {
        moveRight = true;
        if (!isInRestrictedArea(X + speed, Y)) {
            this->setPositionX(this->getPositionX() + speed);  // 只移动一次
            this->setTexture("player_right.png");  
        }
    }
}

void Player::onKeyReleased(EventKeyboard::KeyCode keyCode, Event* event)
{
    // 判断松开的方向键，并更新角色的移动状态
    if (keyCode == EventKeyboard::KeyCode::KEY_UP_ARROW)  // 上箭头
    {
        moveUp = false;
        this->setTexture("player_stop.png");  // 切换到“下走”图像
    }
    else if (keyCode == EventKeyboard::KeyCode::KEY_DOWN_ARROW)  // 下箭头
    {
        moveDown = false;
        this->setTexture("player_stop.png");  // 切换到“下走”图像
    }
    else if (keyCode == EventKeyboard::KeyCode::KEY_LEFT_ARROW)  // 左箭头
    {
        moveLeft = false;
        this->setTexture("player_stop.png");  // 切换到“下走”图像
    }
    else if (keyCode == EventKeyboard::KeyCode::KEY_RIGHT_ARROW)  // 右箭头
    {
        moveRight = false;
        this->setTexture("player_stop.png");  // 切换到“下走”图像
    }
}

// 检查角色是否进入任何一个禁止区域
bool Player::isInRestrictedArea(float x, float y)
{
    // 遍历所有禁止区域
    for (const auto& area : _restrictedAreas)
    {
        if (area.containsPoint(Vec2(x, y)))
        {
            return true; // 如果位置在禁止区域内，返回 true
        }
    }
    return false; // 否则返回 false
}


