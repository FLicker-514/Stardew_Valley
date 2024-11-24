#include "Background1.h"
#include "Background2.h"
#include "Player.h"

USING_NS_CC;

Background1::Background1() {}

Background1::~Background1() {}

bool Background1::init()
{
    if (!Scene::init())
    {
        return false;
    }

    // ��ȡ��Ļ�ߴ�
    auto visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();


    // �����˳���ť��"X" ͼ�꣩�����ʱ�˳���Ϸ
    auto closeItem = MenuItemImage::create(
        "CloseNormal.png",  // ��ͨ״̬�µ�ͼƬ
        "CloseSelected.png",  // ��ѡ��״̬�µ�ͼƬ
        CC_CALLBACK_1(Background1::menuCloseCallback, this));  // �����ťʱ���� menuCloseCallback ����


    // ���ð�ťλ�ã�ʹ��λ����Ļ���Ͻ�
    float x = origin.x + visibleSize.width - closeItem->getContentSize().width / 2;
    float y = origin.y + closeItem->getContentSize().height / 2;
    closeItem->setPosition(Vec2(x, y));  // ���ð�ť��λ��


    // �����˵�������ť��ӵ��˵��У������ò˵���λ��
    auto menu = Menu::create(closeItem, NULL);  // �����˵�����Ӱ�ť
    menu->setPosition(Vec2::ZERO);  // ���ò˵���λ��Ϊ��0��0���������½�
    this->addChild(menu, 1);  // ���˵���ӵ���ǰ�����У��㼶ֵΪ 1

    // ��������ʼ�� Label ����ʾ��ɫ��λ��
    _positionLabel = Label::createWithTTF("Position: (0, 0)", "fonts/Marker Felt.ttf", 24);
    if (_positionLabel)
    {
        _positionLabel->setPosition(Vec2(origin.x + 100, origin.y + visibleSize.height - 30));  // ����λ��
        this->addChild(_positionLabel, 2);  // ����ǩ��ӵ������У��㼶Ϊ 2
        _positionLabel->setScale(0.7f);
    }



    // ���ñ���ͼƬ������ 1��
    auto background = Sprite::create("background1.png");  // ���� 1 �ı���ͼ
    background->setPosition(Vec2(visibleSize.width / 2 + origin.x, visibleSize.height / 2 + origin.y));
    this->addChild(background);
    background->setScale(1.5f);

    // ���ü�ʱ����ǩ
    _timerLabel = Label::createWithTTF("Timer: 60", "fonts/Marker Felt.ttf", 24);
    _timerLabel->setPosition(Vec2(origin.x + 100, origin.y + visibleSize.height - 70));
    this->addChild(_timerLabel, 1);


    // ��ʼ����ɫ��������ӵ�����
    _player = Player::create();
    _player->setPosition(Vec2(visibleSize.width / 2 + 5, visibleSize.height / 2 + 3.1));  // ������ҳ�ʼλ��
    _player->setScale(0.17f);
    _player->setSpeed(12.07f);
    this->addChild(_player);

    // ��������ֹ���������
    _player->_restrictedAreas.push_back(Rect(550, 285, 100, 75));    // ���ǵļ�
    _player->_restrictedAreas.push_back(Rect(698, 371, 70, 75));   // ��ֳϵͳ
    _player->_restrictedAreas.push_back(Rect(396, 571, 79, 72));   // ��ֳ��
    _player->_restrictedAreas.push_back(Rect(203, 576, 89, 97));   // ��ͨ���ӣ����ϣ�
    _player->_restrictedAreas.push_back(Rect(758, 81, 75, 63));   // ��ͨ���ӣ����£�
    _player->_restrictedAreas.push_back(Rect(227, 395, 70, 75));   // ũó�г�
    _player->_restrictedAreas.push_back(Rect(565, 480, 149, 96));    // �峤��
    _player->_restrictedAreas.push_back(Rect(649, 81, 61, 83));    // ������
    _player->_restrictedAreas.push_back(Rect(444, 383, 87, 140));    // ˮ�� - 1�����棩
    _player->_restrictedAreas.push_back(Rect(456, 274, 45, 87));     // ˮ�� - 2������խ��
    _player->_restrictedAreas.push_back(Rect(372, 69, 199, 205));    // ˮ�� - 3�������
    _player->_restrictedAreas.push_back(Rect(649, 648, 207, 53));    // ɽ�� - 1
    _player->_restrictedAreas.push_back(Rect(661, 636, 99, 3));    // ɽ�� - 2
    _player->_restrictedAreas.push_back(Rect(782, 636, 63, 3));    // ɽ�� - 3
    _player->_restrictedAreas.push_back(Rect(673, 624, 63, 3));    // ɽ�� - 4
    _player->_restrictedAreas.push_back(Rect(806, 624, 39, 3));    // ɽ�� - 5
    _player->_restrictedAreas.push_back(Rect(685, 612, 51, 3));    // ɽ�� - 6
    _player->_restrictedAreas.push_back(Rect(818, 612, 27, 3));    // ɽ�� - 7
    _player->_restrictedAreas.push_back(Rect(698, 600, 15, 3));    // ɽ�� - 8
    _player->_restrictedAreas.push_back(Rect(830, 600, 15, 3));    // ɽ�� - 9
    _player->_restrictedAreas.push_back(Rect(830, 588, 15, 3));    // ɽ�� - 10
    _player->_restrictedAreas.push_back(Rect(842, 576, 3, 3));    // ɽ�� - 11
    _player->_restrictedAreas.push_back(Rect(179, 57, 670, 3));    // �߽� - 1
    _player->_restrictedAreas.push_back(Rect(166, 69, 5, 652));    // �߽� - 2
    _player->_restrictedAreas.push_back(Rect(179, 709, 670, 3));    // �߽� - 3
    _player->_restrictedAreas.push_back(Rect(852, 69, 3, 652));    // �߽� - 4



    

    // ��ÿ֡���� update ����������ɫ�Ƿ�����ֹ����
    schedule([this](float dt) {
        this->update(dt);  // ÿһ֡���� update ����
        }, "update_key");


    return true;
}

Background1* Background1::create()
{
    Background1* scene = new Background1();
    if (scene && scene->init())
    {
        scene->autorelease();
        return scene;
    }
    CC_SAFE_DELETE(scene);
    return nullptr;
}

// update ����������ɫ�Ƿ�����ֹ���򲢸��½�ɫλ�ñ�ǩ
void Background1::update(float dt)
{
    if (_player)
    {
        // ��ȡ��ɫ�ĵ�ǰλ��
        float playerX = _player->getPositionX();
        float playerY = _player->getPositionY();

        // ����λ�ñ�ǩ������
        if (_positionLabel)
        {
            _positionLabel->setString("Position: (" + std::to_string(static_cast<int>(playerX)) + ", " + std::to_string(static_cast<int>(playerY)) + ")");
        }

        // ����ʣ��ʱ��
        remainingTime--;

        // ���¼�ʱ����ʾ
        _timerLabel->setString("Timer: " + std::to_string(remainingTime / 60));

        // ��ʱ�䵽�ˣ��л�����
        if (remainingTime <= 0)
        {

            // �л�����һ������
            auto nextScene = Background2::create();  // ������һ������
            Director::getInstance()->replaceScene(TransitionCrossFade::create(1.0f, nextScene));  // �õ���Ч���л�����


        }

    }
}


// �˳���ť�Ļص�����
void Background1::menuCloseCallback(Ref* pSender)
{
    // �˳����򣬽�����ǰ��Ϸ����
    Director::getInstance()->end();

    /* �����ϣ���˳�����Ӧ�ã����ǽ��رյ�ǰ���������Կ���ʹ�����´��룺
       �˲��ִ��������� iOS �Ϸ��ص�ԭ����Ļ������ֱ���˳�Ӧ�ã�

       EventCustom customEndEvent("game_scene_close_event");
       _eventDispatcher->dispatchEvent(&customEndEvent);
    */
}

    
