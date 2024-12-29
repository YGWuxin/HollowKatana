#pragma once
#include "WidgetElement.h"

class BarWidget :public WidgetElement
{
public:
	enum class BarDirection {
		Left,
		Right,
		Center
	};

public:
	BarWidget(UserWidget* parent, Vector2 position, Vector2 size, int zOrder, LPCTSTR className, WidgetAnchor anchor = WidgetAnchor::TopLeft)
		: WidgetElement(parent, position, size, zOrder, className, anchor) {
		setInputWigdetEventEnabled(false);
		// setInputEventEnabled(false,UserWidget::InputObject::Self);
	};
	~BarWidget() = default;

	void draw() override;                                        // 绘制

	void update(float delta) override;

	//设置默认进度条当前值
	void setDefaultValue(float value);

	//设置进度条当前值
	void setCurrentValue(float value);

	//增加进度条当前值
	void addCurrentValue(float value);

	//设置进度条颜色
	void setBarColor(COLORREF color) { barColor= color; }
	//设置进度条背景颜色
	void setBackgroundColor(COLORREF color) { backgroundColor = color; }
	//设置是否开启边框
	void setBorderEnabled(bool enabled) { borderEnabled = enabled; }
	//设置边框颜色
	void setBorderColor(COLORREF color) { borderColor = color; }
	//设置进度条方向
	void setDirection(BarDirection direction) { this->direction = direction; }

	//设置圆角半径
	void setEllipseRadius(int radius) { ellipseRadius = radius; }

	//设置是否绘制阴影
	void setShadowEnabled(bool enabled) { shadowEnabled = enabled; }
	//设置阴影颜色
	void setShadowColor(COLORREF color) { shadowColor = color; }
	//设置阴影偏移量
	void setShadowOffset(int offset) { shadowOffset = offset; }

	//设置是否开启平滑效果
	void setSmoothEnabled(bool enabled) { isSmoothEnabled = enabled; }
	//设置过渡速度
	void setSpeed(float speed) { this->speed = speed; }

	//设置是否开启过渡效果
	void setTransitionEnabled(bool enabled)
	{ 
		isTransitionEnabled = enabled;
		if (enabled) 	
			isSmoothEnabled = false;
		else
			isSmoothEnabled = true;
	}
	//设置缺少效果颜色
	void setTransitionColor(COLORREF color) { TransitionColor = color; }


private:
	//进度条方向
	BarDirection direction = BarDirection::Left;
	//进度条当前值
	float value = 0.0f;

	//进度条颜色
	COLORREF barColor = RGB(0, 122, 255);
	//进度条背景颜色
	COLORREF backgroundColor = RGB(67, 47, 47);

	//是否开启边框
	bool borderEnabled = false;
	//边框颜色
	COLORREF borderColor = RGB(0, 0, 0);

	int ellipseRadius = 0;				//圆角半径

	//是否绘制阴影
	bool shadowEnabled = false;
	//阴影颜色
	COLORREF shadowColor = RGB(5, 5, 5);
	//设置阴影偏移量
	int shadowOffset = 4;

	//是否开启平滑效果
	bool isSmoothEnabled = true;
	float targetValue = 0.0f;
	float speed = 20.0f;
	float tempValue = 0.0f;

	//是否开启过渡效果
	bool isTransitionEnabled = false;
	//过渡效果颜色
	COLORREF TransitionColor = RGB(0, 0, 0);
	//过渡效果值
	float TransitionValue = 0.0f;

};



