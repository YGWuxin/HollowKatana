#include "SliderBarWidget.h"
#include "BarWidget.h"
#include "ButtonWidget.h"


SliderBarWidget::SliderBarWidget(UserWidget* parent, Vector2 position, Vector2 size, int zOrder, LPCTSTR className, WidgetAnchor anchor)
	: WidgetElement(parent, position, size, zOrder, className, anchor) {
	//setInputWigdetEventEnabled(false);
	setInputEventEnabled(false, UserWidget::InputObject::Chlid);
	
	//setDebug(true);
	//setDebugColor(YELLOW);

	Bar = new BarWidget(this, Vector2(0,0), size, 1, _T("Bar"));
	Bar->setTransitionEnabled(false);
	Bar->setSmoothEnabled(false);
	Bar->setCurrentValue(currentValue);
	Bar->setBarColor(RGB(84,174,252));


	Button = new ButtonWidget(this, Vector2(0, size.y /2), Vector2(size.y + 10, size.y + 10), 2, _T("Button"), WidgetAnchor::MiddleLeft);
	Button->setButtonColor(BLUE, ButtonWidget::ButtonState::Default);
	Button->setEllipseRadius(size.y/2 - 5);
	setCurrentValue(currentValue);
};



void SliderBarWidget::draw()
{
	UserWidget::draw();
}

void SliderBarWidget::update(float delta)
{
	UserWidget::update(delta);
}

void SliderBarWidget::onDefault()
{
	isSliding = false;
	Button->setButtonState(ButtonWidget::ButtonState::Default);
}


void SliderBarWidget::onLeave()
{
	onDefault();
}

void SliderBarWidget::onMouseDown(const ExMessage& msg)
{
	isSliding = true;
	updateButtonPosition(msg);
	Button->setButtonState(ButtonWidget::ButtonState::Press);
	setFoucs(true);
	
}

void SliderBarWidget::onMouseUp(const ExMessage& msg)
{
	isSliding = false;
	Button->setButtonState(ButtonWidget::ButtonState::Default);
	setFoucs(false);
	if (onMouseUpCallback)
		onMouseUpCallback();
}


void SliderBarWidget::onMouseMove(const ExMessage& msg)
{
	if (!isSliding)
		return;
	updateButtonPosition(msg);
}


void SliderBarWidget::setCurrentValue(float value)
{
	currentValue = value;
	if (Bar)
		Bar->setCurrentValue(value);
	float buttonPosX = (size.x - Button->getSize().x) * currentValue;
	Button->setPositionX(buttonPosX);
}


void SliderBarWidget::updateButtonPosition(const ExMessage& msg)
{
	float move_x = msg.x - position.x;

	if (move_x <= Button->getSize().x / 2)
	{
		Button->setPositionX(0);
	}
	else if (size.x - move_x <= Button->getSize().x / 2)
	{
		Button->setPositionX(size.x - Button->getSize().x);
	}
	else
	{
		Button->setPositionX(move_x - Button->getSize().x / 2);
	}

	currentValue = (msg.x - (position.x + Button->getSize().x / 2)) / (size.x - Button->getSize().x);
	if(currentValue <= 0)
		currentValue = 0;
	else if(currentValue >= 1)
		currentValue = 1;
	Bar->setCurrentValue(currentValue);
	
	//printf("SliderBarWidget::currentValue :%f\n", currentValue);
	if (onSlideCallback)
		onSlideCallback(currentValue);
}