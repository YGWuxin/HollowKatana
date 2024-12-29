#pragma once
#include "WidgetElement.h"

class BarWidget;
class ButtonWidget;

class SliderBarWidget : public WidgetElement
{
public:
	SliderBarWidget(UserWidget* parent, Vector2 position, Vector2 size, int zOrder, LPCTSTR className, WidgetAnchor anchor = WidgetAnchor::TopLeft);
	~SliderBarWidget() = default;

	void draw() override;                                        // ����

	void update(float delta) override;

	float getCurrentValue() const {return currentValue;};                                // ��ȡ��ǰֵ

	void setCurrentValue(float value);                           // ���õ�ǰֵ

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
	void updateButtonPosition(const ExMessage& msg);                                // ���°�ťλ��


private:
	BarWidget* Bar = nullptr;
	ButtonWidget* Button = nullptr;

	//��ǰֵ
	float currentValue = 0.0f;

	//�Ƿ����ڻ���
	bool isSliding = false;

	//����ʱ�ص�����
	std::function<void(float)> onSlideCallback;
	std::function<void(void)> onMouseUpCallback;


};

