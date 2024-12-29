#include "WD_Player.h"
#include "ButtonWidget.h"
#include "TextButtonWidget.h"
#include "UserWidget.h"
#include "ImageWidget.h"
#include "WidgetManager.h"
#include "BarWidget.h"
#include "ResourcesManager.h"
#include "SliderBarWidget.h"
#include "SceneManager.h"
#include "../Parameter/GlobeGameParameters.h"


WD_Player::WD_Player(UserWidget* parent, int zOrder) : UserWidget(parent, zOrder)
{
	//加载图片
	IMAGE* player_avatar = ResourcesManager::GetInstance().find_image("img_Katana_avatar")->getImage();

	//设置背景
	ImageWidget* player = new ImageWidget(this, {80,80 }, { 107,112 }, 1, _T("player_avatar"), WidgetAnchor::MiddleCenter);
	player->setImage(player_avatar);

	//设置血条
	bar_hp = new BarWidget(this, { 140,46 }, { 230,24 }, 1, _T("bar_hp"));
	bar_hp->setDefaultValue(1.0f);
	bar_hp->setSpeed(8);
	bar_hp->setBarColor(RED);
	bar_hp->setEllipseRadius(10);
	bar_hp->setTransitionEnabled(true);
	bar_hp->setTransitionColor(RGB(60,0,0));

	//设置魔法条
	bar_mp = new BarWidget(this, { 140,80 }, { 200,10 }, 1, _T("bar_mp"));
	bar_mp->setDefaultValue(1.0f);
	bar_mp->setSmoothEnabled(false);
	bar_mp->setBarColor(RGB(186, 85, 211));
	bar_mp->setEllipseRadius(5);

	//设置体力条
	bar_stamina = new BarWidget(this, { 140,100 }, { 200,10 }, 1, _T("bar_mp"));
	bar_stamina->setDefaultValue(1.0f);
	bar_stamina->setSmoothEnabled(false);
	bar_stamina->setBarColor(RGB(255, 140, 0));
	bar_stamina->setEllipseRadius(5);

	/*
	ButtonWidget* button1 = new ButtonWidget(this, { 500,200 }, { 200,50 }, 3, _T("Button1"));
	button1->setButtonColor(RED, ButtonWidget::ButtonState::Default);
	//button1->setIsShowDefaultBackground(false);
	button1->setIsDrawLine(true);
	button1->setLineColor(YELLOW);
	button1->setEllipseRadius(20);
	button1->setOnClickFunc(std::bind(&WD_Player::testFunction, this));

	ButtonWidget* button2 = new ButtonWidget(this, { 500,300 }, { 200,50 }, 3, _T("Button1"));
	button2->setButtonColor(RED, ButtonWidget::ButtonState::Default);
	button2->setIsDrawLine(true);
	button2->setLineColor(YELLOW);
	button2->setEllipseRadius(20);
	button2->setOnClickFunc(std::bind(&WD_Player::testFunction1, this));

	*/


	text_tips = new TextWidget(this, { WIN_WIDTH / 2 - 100,WIN_HEIGHT / 2 }, { 200,50 }, 1, _T("tips"));
	text_tips->setVisible(false);
	text_tips->setText(_T("还是做不到吗？"));
	text_tips->setTextColor(WHITE);
	text_tips->setFontSize(24);
	text_tips->setFont(_T("黑体"));

}


void WD_Player::testFunction()
{
	bar_hp->setCurrentValue(0.2f);
}

void WD_Player::testFunction1()
{
	bar_hp->setCurrentValue(0.8f);
}

void WD_Player::setTips(const std::wstring& newText) const
{
	text_tips->setVisible(true);
	text_tips->setText(newText);
}

void WD_Player::setHP(float value) const
{
	if(!bar_hp) return;
	if(value < 0.0f || value > 1.0f) return;
	bar_hp->setCurrentValue(value);
}

void WD_Player::setMP(float value) const
{
	if(!bar_mp) return;
	if (value < 0.0f || value > 1.0f) return;
	bar_mp->setCurrentValue(value);

}

void WD_Player::setStamina(float value) const
{
	if(!bar_stamina) return;
	if (value < 0.0f || value > 1.0f) return;
	bar_stamina->setCurrentValue(value);
}


