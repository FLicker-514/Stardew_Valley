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

    // 获取屏幕尺寸
    auto visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();


    // 创建退出按钮（"X" 图标），点击时退出游戏
    auto closeItem = MenuItemImage::create(
        "CloseNormal.png",  // 普通状态下的图片
        "CloseSelected.png",  // 被选中状态下的图片
        CC_CALLBACK_1(Background1::menuCloseCallback, this));  // 点击按钮时调用 menuCloseCallback 方法


    // 设置按钮位置，使其位于屏幕右上角
    float x = origin.x + visibleSize.width - closeItem->getContentSize().width / 2;
    float y = origin.y + closeItem->getContentSize().height / 2;
    closeItem->setPosition(Vec2(x, y));  // 设置按钮的位置


    // 创建菜单，将按钮添加到菜单中，并设置菜单的位置
    auto menu = Menu::create(closeItem, NULL);  // 创建菜单并添加按钮
    menu->setPosition(Vec2::ZERO);  // 设置菜单的位置为（0，0），即左下角
    this->addChild(menu, 1);  // 将菜单添加到当前场景中，层级值为 1

    // 创建并初始化 Label 来显示角色的位置
    _positionLabel = Label::createWithTTF("Position: (0, 0)", "fonts/Marker Felt.ttf", 24);
    if (_positionLabel)
    {
        _positionLabel->setPosition(Vec2(origin.x + 100, origin.y + visibleSize.height - 30));  // 设置位置
        this->addChild(_positionLabel, 2);  // 将标签添加到场景中，层级为 2
        _positionLabel->setScale(0.7f);
    }



    // 设置背景图片（背景 1）
    auto background = Sprite::create("background1.png");  // 场景 1 的背景图
    background->setPosition(Vec2(visibleSize.width / 2 + origin.x, visibleSize.height / 2 + origin.y));
    this->addChild(background);
    background->setScale(1.5f);

    // 设置计时器标签
    _timerLabel = Label::createWithTTF("Timer: 60", "fonts/Marker Felt.ttf", 24);
    _timerLabel->setPosition(Vec2(origin.x + 100, origin.y + visibleSize.height - 70));
    this->addChild(_timerLabel, 1);


    // 初始化角色并将其添加到场景
    _player = Player::create();
    _player->setPosition(Vec2(visibleSize.width / 2 + 5, visibleSize.height / 2 + 3.1));  // 设置玩家初始位置
    _player->setScale(0.17f);
    _player->setSpeed(12.07f);
    this->addChild(_player);

    // 定义多个禁止进入的区域
    _player->_restrictedAreas.push_back(Rect(550, 285, 100, 75));    // 主角的家
    _player->_restrictedAreas.push_back(Rect(698, 371, 70, 75));   // 养殖系统
    _player->_restrictedAreas.push_back(Rect(396, 571, 79, 72));   // 养殖户
    _player->_restrictedAreas.push_back(Rect(203, 576, 89, 97));   // 普通房子（左上）
    _player->_restrictedAreas.push_back(Rect(758, 81, 75, 63));   // 普通房子（右下）
    _player->_restrictedAreas.push_back(Rect(227, 395, 70, 75));   // 农贸市场
    _player->_restrictedAreas.push_back(Rect(565, 480, 149, 96));    // 村长家
    _player->_restrictedAreas.push_back(Rect(649, 81, 61, 83));    // 铁匠铺
    _player->_restrictedAreas.push_back(Rect(444, 383, 87, 140));    // 水域 - 1（上面）
    _player->_restrictedAreas.push_back(Rect(456, 274, 45, 87));     // 水域 - 2（下面窄）
    _player->_restrictedAreas.push_back(Rect(372, 69, 199, 205));    // 水域 - 3（下面宽）
    _player->_restrictedAreas.push_back(Rect(649, 648, 207, 53));    // 山脉 - 1
    _player->_restrictedAreas.push_back(Rect(661, 636, 99, 3));    // 山脉 - 2
    _player->_restrictedAreas.push_back(Rect(782, 636, 63, 3));    // 山脉 - 3
    _player->_restrictedAreas.push_back(Rect(673, 624, 63, 3));    // 山脉 - 4
    _player->_restrictedAreas.push_back(Rect(806, 624, 39, 3));    // 山脉 - 5
    _player->_restrictedAreas.push_back(Rect(685, 612, 51, 3));    // 山脉 - 6
    _player->_restrictedAreas.push_back(Rect(818, 612, 27, 3));    // 山脉 - 7
    _player->_restrictedAreas.push_back(Rect(698, 600, 15, 3));    // 山脉 - 8
    _player->_restrictedAreas.push_back(Rect(830, 600, 15, 3));    // 山脉 - 9
    _player->_restrictedAreas.push_back(Rect(830, 588, 15, 3));    // 山脉 - 10
    _player->_restrictedAreas.push_back(Rect(842, 576, 3, 3));    // 山脉 - 11
    _player->_restrictedAreas.push_back(Rect(179, 57, 670, 3));    // 边界 - 1
    _player->_restrictedAreas.push_back(Rect(166, 69, 5, 652));    // 边界 - 2
    _player->_restrictedAreas.push_back(Rect(179, 709, 670, 3));    // 边界 - 3
    _player->_restrictedAreas.push_back(Rect(852, 69, 3, 652));    // 边界 - 4



    

    // 在每帧调用 update 方法，检查角色是否进入禁止区域
    schedule([this](float dt) {
        this->update(dt);  // 每一帧调用 update 方法
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

// update 方法：检查角色是否进入禁止区域并更新角色位置标签
void Background1::update(float dt)
{
    if (_player)
    {
        // 获取角色的当前位置
        float playerX = _player->getPositionX();
        float playerY = _player->getPositionY();

        // 更新位置标签的内容
        if (_positionLabel)
        {
            _positionLabel->setString("Position: (" + std::to_string(static_cast<int>(playerX)) + ", " + std::to_string(static_cast<int>(playerY)) + ")");
        }

        // 减少剩余时间
        remainingTime--;

        // 更新计时器显示
        _timerLabel->setString("Timer: " + std::to_string(remainingTime / 60));

        // 当时间到了，切换场景
        if (remainingTime <= 0)
        {

            // 切换到下一个场景
            auto nextScene = Background2::create();  // 创建下一个场景
            Director::getInstance()->replaceScene(TransitionCrossFade::create(1.0f, nextScene));  // 用淡入效果切换场景


        }

    }
}


// 退出按钮的回调函数
void Background1::menuCloseCallback(Ref* pSender)
{
    // 退出程序，结束当前游戏场景
    Director::getInstance()->end();

    /* 如果不希望退出整个应用，而是仅关闭当前场景，可以考虑使用以下代码：
       此部分代码用于在 iOS 上返回到原生屏幕，避免直接退出应用：

       EventCustom customEndEvent("game_scene_close_event");
       _eventDispatcher->dispatchEvent(&customEndEvent);
    */
}

    
