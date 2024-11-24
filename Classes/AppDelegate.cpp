/****************************************************************************
 Copyright (c) 2017-2018 Xiamen Yaji Software Co., Ltd.

 http://www.cocos2d-x.org

 �����κ������ʹ�ø�����������޸ġ��ϲ����������ַ���������Լ����۸�����ĸ�����ǰ�������и���������Ҫ���ֶ������������Ȩ���������������

 �������"ԭ��"�ṩ���������κ���ʽ�ı�֤�������������ڶ������ԡ��ض���;�����ԺͲ���Ȩ�ı�֤�����κ�����£����߻��Ȩ�����߾�������ʹ�ø��������������ص��κ����⡢�𺦻��������γе����Σ������Ǻ�ͬ����Ȩ��Ϊ��������ʽ��
 ****************************************************************************/

#include "AppDelegate.h"
#include "Background1.h"  // ���� Background1 ����ͷ�ļ�

 // #define USE_AUDIO_ENGINE 1   // �����Ҫʹ����Ƶ���棬����ȡ��ע����һ��

#if USE_AUDIO_ENGINE
#include "audio/include/AudioEngine.h"  // �����������Ƶ���棬��������Ƶ�����ͷ�ļ�
using namespace cocos2d::experimental;  // ʹ����Ƶ����������ռ�
#endif

USING_NS_CC;  // ʹ��cocos2d�������ռ�

// �趨��Ʒֱ��ʵĴ�С
static cocos2d::Size designResolutionSize = cocos2d::Size(1024, 768);  // ��Ʒֱ��ʣ��� 480���� 320
static cocos2d::Size smallResolutionSize = cocos2d::Size(480, 320);   // С���ֱ���
static cocos2d::Size mediumResolutionSize = cocos2d::Size(1024, 768);  // �е���Ļ�ֱ���
static cocos2d::Size largeResolutionSize = cocos2d::Size(2048, 1536); // �����ֱ���

AppDelegate::AppDelegate() {
    // ���캯����AppDelegate����ʱ�����
}

AppDelegate::~AppDelegate() {
    // �����������������ʱ�����
#if USE_AUDIO_ENGINE
    AudioEngine::end();  // ���ʹ������Ƶ���棬ֹͣ��Ƶ����
#endif
}

// ��ʼ�� OpenGL ����������
void AppDelegate::initGLContextAttrs() {
    // ����OpenGL�����ĵ����ԣ��졢�̡�����͸��ͨ����λ���ȡ�ģ��Ͷ��ز���
    GLContextAttrs glContextAttrs = { 8, 8, 8, 8, 24, 8, 0 };  // ���� OpenGL �����ĵ���ɫ����Ȼ��������

    GLView::setGLContextAttrs(glContextAttrs);  // �����õ�����������Ӧ�õ� GLView
}

// �����ͨ������������װ���������Ҫ�޸Ļ�ɾ���������
static int register_all_packages() {
    return 0;  // ��־λ�����ڰ�������
}

// Ӧ��������ɺ����
bool AppDelegate::applicationDidFinishLaunching() {
    // ��ʼ�� Director�������࣬���ڹ������ͻ��ƣ�
    auto director = Director::getInstance();  // ��ȡ Director ʵ��
    auto glview = director->getOpenGLView();  // ��ȡ OpenGL ��ͼ

    if (!glview) {
        // ���û�д��� OpenGL ��ͼ���򴴽�һ��
#if (CC_TARGET_PLATFORM == CC_PLATFORM_WIN32) || (CC_TARGET_PLATFORM == CC_PLATFORM_MAC) || (CC_TARGET_PLATFORM == CC_PLATFORM_LINUX)
        glview = GLViewImpl::createWithFullScreen("MyGame");  // ����ȫ��ģʽ
#else
        glview = GLViewImpl::create("MyGame");
#endif
        director->setOpenGLView(glview);
    }

    // �� FPS ��ʾ
    director->setDisplayStats(true);  // ��ʾ֡��ͳ����Ϣ

    // ����֡�ʡ�Ĭ��ֵΪ 1.0/60���� 60 FPS
    director->setAnimationInterval(1.0f / 60);  // ���ö���֡��Ϊ 60 FPS

    // ������Ʒֱ���
    glview->setDesignResolutionSize(designResolutionSize.width, designResolutionSize.height, ResolutionPolicy::NO_BORDER);
    auto frameSize = glview->getFrameSize();  // ��ȡ��Ļʵ�ʷֱ���

    // �����豸�ֱ��������������ű���
    if (frameSize.height > mediumResolutionSize.height) {
        // ����豸��Ļ�߶ȴ����еȷֱ��ʵĸ߶ȣ������������ű���
        director->setContentScaleFactor(MIN(largeResolutionSize.height / designResolutionSize.height, largeResolutionSize.width / designResolutionSize.width));
    }
    else if (frameSize.height > smallResolutionSize.height) {
        // ����豸��Ļ�߶ȴ���С�ֱ��ʵĸ߶ȣ������������ű���
        director->setContentScaleFactor(MIN(mediumResolutionSize.height / designResolutionSize.height, mediumResolutionSize.width / designResolutionSize.width));
    }
    else {
        // ����豸��Ļ�߶�С��С�ֱ��ʵĸ߶ȣ������������ű���
        director->setContentScaleFactor(MIN(smallResolutionSize.height / designResolutionSize.height, smallResolutionSize.width / designResolutionSize.width));
    }

    register_all_packages();  // ע�����еİ�

    runScene(director);

    return true;  // ���سɹ�
}


// �л������ĺ���
void AppDelegate::runScene(cocos2d::Director* director) {


    // ��ȡ��ǰ��ͼ�Ŀɼ���С��ԭ��λ��
    auto visibleSize = Director::getInstance()->getVisibleSize();  // ��ȡ��Ļ��������Ĵ�С
    Vec2 origin = Director::getInstance()->getVisibleOrigin();  // ��ȡ��Ļԭ���λ�ã����½ǣ�

    // ���иó���һ
    director->runWithScene(Background1::create());

}

// ��Ӧ�ó�������̨ʱ����
void AppDelegate::applicationDidEnterBackground() {
    Director::getInstance()->stopAnimation();  // ֹͣ����

#if USE_AUDIO_ENGINE
    AudioEngine::pauseAll();  // ��ͣ������Ƶ�������������Ƶ���棩
#endif
}

// ��Ӧ�ó������½���ǰ̨ʱ����
void AppDelegate::applicationWillEnterForeground() {
    Director::getInstance()->startAnimation();  // �ָ�����

#if USE_AUDIO_ENGINE
    AudioEngine::resumeAll();  // �ָ�������Ƶ�������������Ƶ���棩
#endif
}
