#include "BarWidget.h"
#include "WidgetElement.h"
#include "TimerManager.h"



void BarWidget::draw()
{
	//绘制阴影
	if (shadowEnabled)
	{
		setfillcolor(shadowColor);
		solidroundrect(position.x + shadowOffset, position.y + shadowOffset, position.x + size.x + shadowOffset, position.y + size.y + shadowOffset, ellipseRadius, ellipseRadius);
	}

	// 绘制背景
	setfillcolor(backgroundColor);
	solidroundrect(position.x, position.y, position.x + size.x, position.y + size.y, ellipseRadius, ellipseRadius);

	//绘制减少效果进度条
	if ((targetValue - tempValue) < 0.0f)
	{
		if ((TransitionValue - targetValue) != 0.0f && isTransitionEnabled)
		{
			setfillcolor(TransitionColor);
			switch (direction)
			{
			case BarWidget::BarDirection::Left:
				solidroundrect(position.x, position.y, position.x + size.x * TransitionValue, position.y + size.y, ellipseRadius, ellipseRadius);
				break;
			case BarWidget::BarDirection::Right:
				solidroundrect(position.x + size.x * TransitionValue, position.y, position.x + size.x, position.y + size.y, ellipseRadius, ellipseRadius);
				break;
			case BarWidget::BarDirection::Center:
				solidroundrect(position.x + size.x / 2 - (size.x * TransitionValue / 2), position.y, position.x + size.x / 2 + (size.x * TransitionValue / 2), position.y + size.y, ellipseRadius, ellipseRadius);
				break;
			default:
				break;
			}
		}
	}
	else if ((targetValue - tempValue) > 0.0f)
	{
		if ((value - targetValue) != 0.0f && isTransitionEnabled)
		{
			setfillcolor(TransitionColor);
			switch (direction)
			{
			case BarWidget::BarDirection::Left:
				solidroundrect(position.x, position.y, position.x + size.x * TransitionValue, position.y + size.y, ellipseRadius, ellipseRadius);
				break;
			case BarWidget::BarDirection::Right:
				solidroundrect(position.x + size.x * TransitionValue, position.y, position.x + size.x, position.y + size.y, ellipseRadius, ellipseRadius);
				break;
			case BarWidget::BarDirection::Center:
				solidroundrect(position.x + size.x / 2 - (size.x * TransitionValue / 2), position.y, position.x + size.x / 2 + (size.x * TransitionValue / 2), position.y + size.y, ellipseRadius, ellipseRadius);
				break;
			default:
				break;
			}

			//printf("targetValue: %f\r\n", targetValue);
		}
		
	}


	//绘制进度条
	if (value != 0.0f)
	{
		setfillcolor(barColor);
		switch (direction)
		{
		case BarWidget::BarDirection::Left:
			solidroundrect(position.x, position.y, position.x + size.x * value, position.y + size.y, ellipseRadius, ellipseRadius);
			break;
		case BarWidget::BarDirection::Right:
			solidroundrect(position.x + size.x * value, position.y, position.x + size.x, position.y + size.y, ellipseRadius, ellipseRadius);
			break;
		case BarWidget::BarDirection::Center:
			solidroundrect(position.x + size.x / 2 - (size.x * value / 2), position.y, position.x + size.x / 2 + (size.x * value / 2), position.y + size.y, ellipseRadius, ellipseRadius);
			break;
		default:
			break;
		}
	}

	//绘制边框
	if (borderEnabled)
	{
		setfillcolor(borderColor);
		roundrect(position.x, position.y, position.x + size.x, position.y + size.y, ellipseRadius, ellipseRadius);
	}

	WidgetElement::draw();
}


void BarWidget::update(float delta)
{
	WidgetElement::update(delta);

	
	if (isTransitionEnabled)
	{
		if ((targetValue - tempValue) > 0.0f)
		{
			TimerManager::GetInstance().lerp_float(value, targetValue, speed, delta);
			TransitionValue = targetValue;
		}
		else if ((targetValue - tempValue) < 0.0f)
		{
			TimerManager::GetInstance().lerp_float(TransitionValue, targetValue, speed, delta);
			value = targetValue;
		}
	}
	else
	{
		if (isSmoothEnabled)
		{
			TimerManager::GetInstance().lerp_float(value, targetValue, speed, delta);
			//printf("targetValue: %f\r\n", value);
		}
		else
		{
			value = targetValue;
		}
	}


}

void BarWidget::setDefaultValue(float value)
{
	if (value < 0.0f)
		this->value = 0.0f;
	if (value > 1.0f)
		this->value = 1.0f;
	else
		this->value = value;
	targetValue = this->value;
	TransitionValue = this->value;
	tempValue = this->value;
}


void BarWidget::setCurrentValue(float value)
{
	if(targetValue == value) return;
	if (value < 0.0f)
		targetValue = 0.0f;
	if (value > 1.0f)
		targetValue = 1.0f;
	else
		targetValue = value;
	tempValue = this->value;
}


void BarWidget::addCurrentValue(float value)
{
	targetValue += value;
	if (targetValue < 0.0f)
		targetValue = 0.0f;
	if (targetValue > 1.0f)
		targetValue = 1.0f;
	tempValue = this->value;
}




