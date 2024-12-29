#include "WD_Hornet.h"
#include "ButtonWidget.h"
#include "TextButtonWidget.h"
#include "UserWidget.h"
#include "ImageWidget.h"
#include "WidgetManager.h"
#include "BarWidget.h"
#include "ResourcesManager.h"
#include "SliderBarWidget.h"
#include "SceneManager.h"

WD_Hornet::WD_Hornet(UserWidget* parent, int zOrder) : UserWidget(parent, zOrder)
{
	//¼ÓÔØÍ¼Æ¬
	IMAGE* hornet_avatar = ResourcesManager::GetInstance().find_image("img_Hornet_avatar")->getImage();

	//ÉèÖÃ±³¾°
	ImageWidget* hornet = new ImageWidget(this, { 1202,80 }, { 90,100 }, 1, _T("hornet_avatar"), WidgetAnchor::MiddleCenter);
	hornet->setImage(hornet_avatar);

	//ÉèÖÃÑªÌõ
	bar_hp = new BarWidget(this, { 840,70 }, { 300,24 }, 1, _T("bar_hp"));
	bar_hp->setDefaultValue(0.0f);
	bar_hp->setSpeed(3);
	bar_hp->setBarColor(RGB(255, 255, 255));
	bar_hp->setEllipseRadius(10);
	bar_hp->setTransitionEnabled(true);
	bar_hp->setTransitionColor(RGB(105, 105, 105));

	/*
	ButtonWidget* button1 = new ButtonWidget(this, { 500,200 }, { 200,50 }, 3, _T("Button1"));
	button1->setButtonColor(RED, ButtonWidget::ButtonState::Default);
	//button1->setIsShowDefaultBackground(false);
	button1->setIsDrawLine(true);
	button1->setLineColor(YELLOW);
	button1->setEllipseRadius(20);
	button1->setOnClickFunc(std::bind(&WD_Hornet::testFunction, this));

	ButtonWidget* button2 = new ButtonWidget(this, { 500,300 }, { 200,50 }, 3, _T("Button1"));
	button2->setButtonColor(RED, ButtonWidget::ButtonState::Default);
	button2->setIsDrawLine(true);
	button2->setLineColor(YELLOW);
	button2->setEllipseRadius(20);
	button2->setOnClickFunc(std::bind(&WD_Hornet::testFunction1, this));
	*/
	
}

void WD_Hornet::testFunction()
{
	bar_hp->setCurrentValue(0.2f);
}

void WD_Hornet::testFunction1()
{
	bar_hp->setCurrentValue(0.8f);
}


void WD_Hornet::setHP(float value) const
{
	if (!bar_hp) return;
	if (value < 0.0f || value > 1.0f) return;
	bar_hp->setCurrentValue(value);
}


