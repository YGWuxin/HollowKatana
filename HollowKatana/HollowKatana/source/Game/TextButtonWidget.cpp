#include "TextButtonWidget.h"
#include "ButtonWidget.h"
#include "TextWidget.h"
#include "WidgetElement.h"
#include "UserWidget.h"

TextButtonWidget::TextButtonWidget(UserWidget* parent, Vector2 position, Vector2 size, int zOrder, LPCTSTR className, WidgetAnchor anchor)
	: ButtonWidget(parent, position, size, zOrder, className, anchor)
{
	Text = new TextWidget(this, Vector2(0, 0), size, 1, className);

	//�����ı��ؼ���Ĭ����ɫ
	Text->setTextColor(RGB(255, 255, 255));
	
	//�����ı��ؼ��������С
	setFontSize(14);

	//�����ı��ؼ���λ�þ���
	setTextHorizontalCenter(true);
	setTextVerticalCenter(true);

	//�Ƿ����õ���ģʽ
	setDebugText(false);

	//����״̬
	Text->setVisible(true);
}

void TextButtonWidget::onDefault()
{
	ButtonWidget::onDefault();
	setTextInfo(defaultTextInfo);
}

void TextButtonWidget::onEnter()
{
	ButtonWidget::onEnter();
	setTextInfo(hoverTextInfo);
}

void TextButtonWidget::onLeave()
{
	ButtonWidget::onLeave();
	setTextInfo(defaultTextInfo);
}


void TextButtonWidget::onMouseDown(const ExMessage& msg)
{
	ButtonWidget::onMouseDown(msg);
	setTextInfo(pressedTextInfo);
}


void TextButtonWidget::onMouseUp(const ExMessage& msg)
{
	ButtonWidget::onMouseUp(msg);
	if(getIsHover())
	{
		setTextInfo(hoverTextInfo);
	}
	else
	{
		setTextInfo(defaultTextInfo);
	}
}


void TextButtonWidget::setFontSize(int size)
{
	defaultTextInfo.fontSize = size;
	hoverTextInfo.fontSize = size;
	pressedTextInfo.fontSize = size;
	Text->setFontSize(size);
}

void TextButtonWidget::setFontSize(int size, ButtonState state)
{
	switch (state)
	{
	case ButtonWidget::ButtonState::Default:
		defaultTextInfo.fontSize = size;
		break;
	case ButtonWidget::ButtonState::Hover:
		hoverTextInfo.fontSize = size;
		break;
	case ButtonWidget::ButtonState::Press:
		pressedTextInfo.fontSize = size;
		break;
	default:
		break;
	}
	updataTextInfo();
}


void TextButtonWidget::setFont(LPCTSTR name)
{
	defaultTextInfo.fontName = name;
	hoverTextInfo.fontName = name;
	pressedTextInfo.fontName = name;
	Text->setFont(name);
}

void TextButtonWidget::setFont(LPCTSTR name, ButtonState state)
{
	switch (state)
	{
	case ButtonWidget::ButtonState::Default:
		defaultTextInfo.fontName = name;
		break;
	case ButtonWidget::ButtonState::Hover:
		hoverTextInfo.fontName = name;
		break;
	case ButtonWidget::ButtonState::Press:
		pressedTextInfo.fontName = name;
		break;
	default:
		break;
	}
	updataTextInfo();
}

//�Ƿ������ı��ؼ�����
void TextButtonWidget::setDebugText(bool debug)
{
	defaultTextInfo.debug = debug;
	hoverTextInfo.debug = debug;
	pressedTextInfo.debug = debug;
	Text->setDebug(debug);
}

//�Ƿ������ı��ؼ�ˮƽ����
void TextButtonWidget::setTextHorizontalCenter(bool center)
{
	defaultTextInfo.horizontalCenter = center;
	hoverTextInfo.horizontalCenter = center;
	pressedTextInfo.horizontalCenter = center;
	Text->setCenterHorizontal(center);
}

//�Ƿ������ı��ؼ���ֱ����
void TextButtonWidget::setTextVerticalCenter(bool center)
{
	defaultTextInfo.verticalCenter = center;
	hoverTextInfo.verticalCenter = center;
	pressedTextInfo.verticalCenter = center;
	Text->setCenterVertical(center);
}


void TextButtonWidget::setText(LPCTSTR text)
{
	defaultTextInfo.text = text;
	hoverTextInfo.text = text;
	pressedTextInfo.text = text;
	Text->setText(text);
}

void TextButtonWidget::setText(LPCTSTR text, ButtonState state)
{
	switch (state)
	{
	case ButtonWidget::ButtonState::Default:
		defaultTextInfo.text = text;
		break;
	case ButtonWidget::ButtonState::Hover:
		hoverTextInfo.text = text;
		break;
	case ButtonWidget::ButtonState::Press:
		pressedTextInfo.text = text;
		break;
	default:
		break;
	}
	updataTextInfo();
}



void TextButtonWidget::setTextColor(COLORREF color)
{
	defaultTextInfo.color = color;
	hoverTextInfo.color = color;
	pressedTextInfo.color = color;
	Text->setTextColor(color);
}

void TextButtonWidget::setTextColor(COLORREF color, ButtonState state)
{
	switch (state)
	{
	case ButtonWidget::ButtonState::Default:
		defaultTextInfo.color = color;
		break;
	case ButtonWidget::ButtonState::Hover:
		hoverTextInfo.color = color;
		break;
	case ButtonWidget::ButtonState::Press:
		pressedTextInfo.color = color;
		break;
	default:
		break;
	}
	updataTextInfo();
}



void TextButtonWidget::setTextInfo(TextInfo& info)
{
	Text->setText(info.text);
	Text->setTextColor(info.color);
	Text->setFontSize(info.fontSize);
	Text->setFont(info.fontName);
	Text->setCenterHorizontal(info.horizontalCenter);
	Text->setCenterVertical(info.verticalCenter);
	Text->setDebug(info.debug);
}


void TextButtonWidget::updataTextInfo()
{
	switch (buttonState)
	{
	case ButtonWidget::ButtonState::Default:
		setTextInfo(defaultTextInfo);
		break;
	case ButtonWidget::ButtonState::Hover:
		setTextInfo(hoverTextInfo);
		break;
	case ButtonWidget::ButtonState::Press:
		setTextInfo(pressedTextInfo);
		break;
	default:
		break;
	}
}
