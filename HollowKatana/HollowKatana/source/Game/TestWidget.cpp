#include "TestWidget.h"
#include "ButtonWidget.h"
#include "TextButtonWidget.h"
#include "UserWidget.h"
#include "ImageWidget.h"
#include "WidgetManager.h"
#include "BarWidget.h"
#include "ResourcesManager.h"
#include "SliderBarWidget.h"
#include "SceneManager.h"

TestWidget::TestWidget(UserWidget* parent, int zOrder) : UserWidget(parent, zOrder)
{
	
	IMAGE* image1 = ResourcesManager::GetInstance().find_image("img_btn_bg_1")->getImage();
	IMAGE* image2 = ResourcesManager::GetInstance().find_image("img_btn_bg_2")->getImage();


	button = new TextButtonWidget(this,{ 200,180 }, {200,50},2,_T("Button"));

	button->setText(_T("开始游戏"));
	button->setFontSize(25);
	button->setFont(_T("黑体"));
	button->setIsShowBackground(false, ButtonWidget::ButtonState::Default);
	button->setTextColor(RGB(0, 0, 0), ButtonWidget::ButtonState::Hover);
	button->setTextColor(RGB(49, 49, 49), ButtonWidget::ButtonState::Press);
	//button->setText(_T("悬停状态"), ButtonWidget::ButtonState::Hover);
	//button->setText(_T("按下状态"), ButtonWidget::ButtonState::Press);
	button->setBGImage(image1, ButtonWidget::ButtonState::Hover);
	button->setBGImage(image2, ButtonWidget::ButtonState::Press);
	button->setImageOffset(-75,-4);

	button->setOnClickFunc(std::bind(&TestWidget::testFunction1, this));

	//button->setVisible(false);

	ButtonWidget* button1 = new ButtonWidget(this, { 500,200 }, { 200,50 }, 3,_T("Button1"));
	button1->setButtonColor(RED, ButtonWidget::ButtonState::Default);
	//button1->setIsShowDefaultBackground(false);
	button1->setIsDrawLine(true);
	button1->setLineColor(YELLOW);
	button1->setEllipseRadius(20);
	button1->setOnClickFunc(std::bind(&TestWidget::testFunction, this));


	bar = new BarWidget(this, { 700,300 }, { 200,20 }, 4, _T("bar"));
	bar->setDefaultValue(0.0f);
	bar->setSpeed(10);
	//bar->setBorderEnabled(true);
	//bar->setEllipseRadius(10);
	//bar->setDirection(BarWidget::BarDirection::Center);


	SliderBarWidget *slider = new SliderBarWidget(this, { 700,400 }, { 200,20 }, 5, _T("slider"));
	//slider->setCurrentValue(0.5f);

}

void TestWidget::testButton(Vector2 position, LPCWSTR text)
{
	button = new TextButtonWidget(this, position, { 200,50 }, 2, text);
	button->setText(text);
}


void TestWidget::testFunction()
{
	printf("Test Function\n");
	if (bar)
	{
		//button->canDestroy();
		//button = nullptr;
		bar->addCurrentValue(-0.5f);
		
	}
}


void TestWidget::testFunction1()
{
	printf("Test Function1\n");
	SceneManager::GetInstance().switch_to(SceneManager::SceneType::Level1);
}
