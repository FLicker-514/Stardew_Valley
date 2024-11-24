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

    // ���ؽ�ɫ��ͼƬ
    this->initWithFile("player_stop.png");


    // ע������¼�
    auto listener = EventListenerKeyboard::create();
    listener->onKeyPressed = CC_CALLBACK_2(Player::onKeyPressed, this);
    listener->onKeyReleased = CC_CALLBACK_2(Player::onKeyReleased, this);

    // �������¼���������ӵ��¼��ַ���
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
            auto nextScene = myhouse::create();  // ������һ������
            Director::getInstance()->replaceScene(TransitionCrossFade::create(1.0f, nextScene));  // �õ���Ч���л�����
        }

    }

    // �жϰ��µķ�����������½�ɫ���ƶ�״̬
    if (keyCode == EventKeyboard::KeyCode::KEY_UP_ARROW && !moveUp)  // �ϼ�ͷ
    {
        moveUp = true;
        if (!isInRestrictedArea(X, Y + speed)) {
            this->setPositionY(this->getPositionY() + speed);  // ֻ�ƶ�һ��
            this->setTexture("player_up.png");  
        }
    }
    else if (keyCode == EventKeyboard::KeyCode::KEY_DOWN_ARROW && !moveDown)  // �¼�ͷ
    {
        moveDown = true;
        if (!isInRestrictedArea(X, Y - speed)) {
            this->setPositionY(this->getPositionY() - speed);  
            this->setTexture("player_down.png"); 
        }
    }
    else if (keyCode == EventKeyboard::KeyCode::KEY_LEFT_ARROW && !moveLeft)  // ���ͷ
    {
        moveLeft = true;
        if (!isInRestrictedArea(X - speed, Y)) {
            this->setPositionX(this->getPositionX() - speed);  // ֻ�ƶ�һ��
            this->setTexture("player_left.png");  
        }
    }
    else if (keyCode == EventKeyboard::KeyCode::KEY_RIGHT_ARROW && !moveRight)  // �Ҽ�ͷ
    {
        moveRight = true;
        if (!isInRestrictedArea(X + speed, Y)) {
            this->setPositionX(this->getPositionX() + speed);  // ֻ�ƶ�һ��
            this->setTexture("player_right.png");  
        }
    }
}

void Player::onKeyReleased(EventKeyboard::KeyCode keyCode, Event* event)
{
    // �ж��ɿ��ķ�����������½�ɫ���ƶ�״̬
    if (keyCode == EventKeyboard::KeyCode::KEY_UP_ARROW)  // �ϼ�ͷ
    {
        moveUp = false;
        this->setTexture("player_stop.png");  // �л��������ߡ�ͼ��
    }
    else if (keyCode == EventKeyboard::KeyCode::KEY_DOWN_ARROW)  // �¼�ͷ
    {
        moveDown = false;
        this->setTexture("player_stop.png");  // �л��������ߡ�ͼ��
    }
    else if (keyCode == EventKeyboard::KeyCode::KEY_LEFT_ARROW)  // ���ͷ
    {
        moveLeft = false;
        this->setTexture("player_stop.png");  // �л��������ߡ�ͼ��
    }
    else if (keyCode == EventKeyboard::KeyCode::KEY_RIGHT_ARROW)  // �Ҽ�ͷ
    {
        moveRight = false;
        this->setTexture("player_stop.png");  // �л��������ߡ�ͼ��
    }
}

// ����ɫ�Ƿ�����κ�һ����ֹ����
bool Player::isInRestrictedArea(float x, float y)
{
    // �������н�ֹ����
    for (const auto& area : _restrictedAreas)
    {
        if (area.containsPoint(Vec2(x, y)))
        {
            return true; // ���λ���ڽ�ֹ�����ڣ����� true
        }
    }
    return false; // ���򷵻� false
}


