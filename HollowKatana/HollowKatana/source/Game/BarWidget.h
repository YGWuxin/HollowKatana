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

	void draw() override;                                        // ����

	void update(float delta) override;

	//����Ĭ�Ͻ�������ǰֵ
	void setDefaultValue(float value);

	//���ý�������ǰֵ
	void setCurrentValue(float value);

	//���ӽ�������ǰֵ
	void addCurrentValue(float value);

	//���ý�������ɫ
	void setBarColor(COLORREF color) { barColor= color; }
	//���ý�����������ɫ
	void setBackgroundColor(COLORREF color) { backgroundColor = color; }
	//�����Ƿ����߿�
	void setBorderEnabled(bool enabled) { borderEnabled = enabled; }
	//���ñ߿���ɫ
	void setBorderColor(COLORREF color) { borderColor = color; }
	//���ý���������
	void setDirection(BarDirection direction) { this->direction = direction; }

	//����Բ�ǰ뾶
	void setEllipseRadius(int radius) { ellipseRadius = radius; }

	//�����Ƿ������Ӱ
	void setShadowEnabled(bool enabled) { shadowEnabled = enabled; }
	//������Ӱ��ɫ
	void setShadowColor(COLORREF color) { shadowColor = color; }
	//������Ӱƫ����
	void setShadowOffset(int offset) { shadowOffset = offset; }

	//�����Ƿ���ƽ��Ч��
	void setSmoothEnabled(bool enabled) { isSmoothEnabled = enabled; }
	//���ù����ٶ�
	void setSpeed(float speed) { this->speed = speed; }

	//�����Ƿ�������Ч��
	void setTransitionEnabled(bool enabled)
	{ 
		isTransitionEnabled = enabled;
		if (enabled) 	
			isSmoothEnabled = false;
		else
			isSmoothEnabled = true;
	}
	//����ȱ��Ч����ɫ
	void setTransitionColor(COLORREF color) { TransitionColor = color; }


private:
	//����������
	BarDirection direction = BarDirection::Left;
	//��������ǰֵ
	float value = 0.0f;

	//��������ɫ
	COLORREF barColor = RGB(0, 122, 255);
	//������������ɫ
	COLORREF backgroundColor = RGB(67, 47, 47);

	//�Ƿ����߿�
	bool borderEnabled = false;
	//�߿���ɫ
	COLORREF borderColor = RGB(0, 0, 0);

	int ellipseRadius = 0;				//Բ�ǰ뾶

	//�Ƿ������Ӱ
	bool shadowEnabled = false;
	//��Ӱ��ɫ
	COLORREF shadowColor = RGB(5, 5, 5);
	//������Ӱƫ����
	int shadowOffset = 4;

	//�Ƿ���ƽ��Ч��
	bool isSmoothEnabled = true;
	float targetValue = 0.0f;
	float speed = 20.0f;
	float tempValue = 0.0f;

	//�Ƿ�������Ч��
	bool isTransitionEnabled = false;
	//����Ч����ɫ
	COLORREF TransitionColor = RGB(0, 0, 0);
	//����Ч��ֵ
	float TransitionValue = 0.0f;

};



