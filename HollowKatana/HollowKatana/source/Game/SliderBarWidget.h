#pragma once
#include "WidgetElement.h"

class BarWidget;
class ButtonWidget;

class SliderBarWidget : public WidgetElement
{
public:
	SliderBarWidget(UserWidget* parent, Vector2 position, Vector2 size, int zOrder, LPCTSTR className, WidgetAnchor anchor = WidgetAnchor::TopLeft);
	~SliderBarWidget() = default;

	void draw() override;                                        // 绘制

	void update(float delta) override;

	float getCurrentValue() const {return currentValue;};                                // 获取当前值

	void setCurrentValue(float value);                           // 设置当前值

	void setOnSlideCallback(std::function<void(float)> callback) { onSlideCallback = callback; };

	void setOnMouseUpCallback(std::function<void(void)> callback) { onMouseUpCallback = callback; };

protected:
	void onDefault() override;
	//void onEnter() override;
	void onLeave()override;
	void onMouseDown(const ExMessage& msg) override;
	void onMouseUp(const ExMessage& msg) override;
	void onMouseMove(const ExMessage& msg) override;


private:
	void updateButtonPosition(const ExMessage& msg);                                // 更新按钮位置


private:
	BarWidget* Bar = nullptr;
	ButtonWidget* Button = nullptr;

	//当前值
	float currentValue = 0.0f;

	//是否正在滑动
	bool isSliding = false;

	//滑动时回调函数
	std::function<void(float)> onSlideCallback;
	std::function<void(void)> onMouseUpCallback;


};

