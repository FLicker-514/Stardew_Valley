/****************************************************************************
 Copyright (c) 2017-2018 Xiamen Yaji Software Co., Ltd.

 http://www.cocos2d-x.org

 允许任何人免费使用该软件，包括修改、合并、发布、分发、再许可以及销售该软件的副本，前提是所有副本或者重要部分都必须包含本版权声明和许可声明。

 该软件按"原样"提供，不附带任何形式的保证，包括但不限于对适销性、特定用途适用性和不侵权的保证。在任何情况下，作者或版权持有者均不对因使用该软件或与该软件相关的任何索赔、损害或其他责任承担责任，无论是合同、侵权行为或其他方式。
 ****************************************************************************/

#include "AppDelegate.h"
#include "Background1.h"  // 引入 Background1 场景头文件

 // #define USE_AUDIO_ENGINE 1   // 如果需要使用音频引擎，可以取消注释这一行

#if USE_AUDIO_ENGINE
#include "audio/include/AudioEngine.h"  // 如果启用了音频引擎，则引入音频引擎的头文件
using namespace cocos2d::experimental;  // 使用音频引擎的命名空间
#endif

USING_NS_CC;  // 使用cocos2d的命名空间

// 设定设计分辨率的大小
static cocos2d::Size designResolutionSize = cocos2d::Size(1024, 768);  // 设计分辨率：宽 480，高 320
static cocos2d::Size smallResolutionSize = cocos2d::Size(480, 320);   // 小屏分辨率
static cocos2d::Size mediumResolutionSize = cocos2d::Size(1024, 768);  // 中等屏幕分辨率
static cocos2d::Size largeResolutionSize = cocos2d::Size(2048, 1536); // 大屏分辨率

AppDelegate::AppDelegate() {
    // 构造函数：AppDelegate构造时会调用
}

AppDelegate::~AppDelegate() {
    // 析构函数：程序结束时会调用
#if USE_AUDIO_ENGINE
    AudioEngine::end();  // 如果使用了音频引擎，停止音频引擎
#endif
}

// 初始化 OpenGL 上下文属性
void AppDelegate::initGLContextAttrs() {
    // 设置OpenGL上下文的属性：红、绿、蓝、透明通道的位深，深度、模板和多重采样
    GLContextAttrs glContextAttrs = { 8, 8, 8, 8, 24, 8, 0 };  // 设置 OpenGL 上下文的颜色和深度缓冲等属性

    GLView::setGLContextAttrs(glContextAttrs);  // 将设置的上下文属性应用到 GLView
}

// 如果想通过包管理器安装更多包，不要修改或删除这个函数
static int register_all_packages() {
    return 0;  // 标志位，用于包管理器
}

// 应用启动完成后调用
bool AppDelegate::applicationDidFinishLaunching() {
    // 初始化 Director（导演类，用于管理场景和绘制）
    auto director = Director::getInstance();  // 获取 Director 实例
    auto glview = director->getOpenGLView();  // 获取 OpenGL 视图

    if (!glview) {
        // 如果没有创建 OpenGL 视图，则创建一个
#if (CC_TARGET_PLATFORM == CC_PLATFORM_WIN32) || (CC_TARGET_PLATFORM == CC_PLATFORM_MAC) || (CC_TARGET_PLATFORM == CC_PLATFORM_LINUX)
        glview = GLViewImpl::createWithFullScreen("MyGame");  // 设置全屏模式
#else
        glview = GLViewImpl::create("MyGame");
#endif
        director->setOpenGLView(glview);
    }

    // 打开 FPS 显示
    director->setDisplayStats(true);  // 显示帧率统计信息

    // 设置帧率。默认值为 1.0/60，即 60 FPS
    director->setAnimationInterval(1.0f / 60);  // 设置动画帧率为 60 FPS

    // 设置设计分辨率
    glview->setDesignResolutionSize(designResolutionSize.width, designResolutionSize.height, ResolutionPolicy::NO_BORDER);
    auto frameSize = glview->getFrameSize();  // 获取屏幕实际分辨率

    // 根据设备分辨率设置内容缩放比例
    if (frameSize.height > mediumResolutionSize.height) {
        // 如果设备屏幕高度大于中等分辨率的高度，设置内容缩放比例
        director->setContentScaleFactor(MIN(largeResolutionSize.height / designResolutionSize.height, largeResolutionSize.width / designResolutionSize.width));
    }
    else if (frameSize.height > smallResolutionSize.height) {
        // 如果设备屏幕高度大于小分辨率的高度，设置内容缩放比例
        director->setContentScaleFactor(MIN(mediumResolutionSize.height / designResolutionSize.height, mediumResolutionSize.width / designResolutionSize.width));
    }
    else {
        // 如果设备屏幕高度小于小分辨率的高度，设置内容缩放比例
        director->setContentScaleFactor(MIN(smallResolutionSize.height / designResolutionSize.height, smallResolutionSize.width / designResolutionSize.width));
    }

    register_all_packages();  // 注册所有的包

    runScene(director);

    return true;  // 返回成功
}


// 切换场景的函数
void AppDelegate::runScene(cocos2d::Director* director) {


    // 获取当前视图的可见大小和原点位置
    auto visibleSize = Director::getInstance()->getVisibleSize();  // 获取屏幕可视区域的大小
    Vec2 origin = Director::getInstance()->getVisibleOrigin();  // 获取屏幕原点的位置（左下角）

    // 运行该场景一
    director->runWithScene(Background1::create());

}

// 当应用程序进入后台时调用
void AppDelegate::applicationDidEnterBackground() {
    Director::getInstance()->stopAnimation();  // 停止动画

#if USE_AUDIO_ENGINE
    AudioEngine::pauseAll();  // 暂停所有音频（如果启用了音频引擎）
#endif
}

// 当应用程序重新进入前台时调用
void AppDelegate::applicationWillEnterForeground() {
    Director::getInstance()->startAnimation();  // 恢复动画

#if USE_AUDIO_ENGINE
    AudioEngine::resumeAll();  // 恢复所有音频（如果启用了音频引擎）
#endif
}
