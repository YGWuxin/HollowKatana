#pragma once
#include "ButtonWidget.h"
#include "../Parameter/GlobeGameParameters.h"

class TextWidget;

class TextButtonWidget : public ButtonWidget
{
public:
	struct TextInfo
	{
		LPCTSTR text = _T("");
		COLORREF color = RGB(255, 255, 255);
		int fontSize = 14;
		LPCTSTR fontName = _T("����");
		bool debug = false;
		bool horizontalCenter = false;
		bool verticalCenter = false;

	};
public:
	TextButtonWidget(UserWidget* parent, Vector2 position, Vector2 size, int zOrder, LPCTSTR className, WidgetAnchor anchor = WidgetAnchor::TopLeft);
	~TextButtonWidget() = default;

	//�����ı�����
	void setText(LPCTSTR text);

	void setText(LPCTSTR text,ButtonState state);

	//�����ı���ɫ
	void setTextColor(COLORREF color);

	void setTextColor(COLORREF color, ButtonState state);

	//���������С
	void setFontSize(int size);

	void setFontSize(int size, ButtonState state);

	//������������
	void setFont(LPCTSTR name);

	void setFont(LPCTSTR name, ButtonState state);

	//�Ƿ������ı��ؼ�����
	void setDebugText(bool debug);

	//�Ƿ������ı��ؼ�ˮƽ����
	void setTextHorizontalCenter(bool center);

	//�Ƿ������ı��ؼ���ֱ����
	void setTextVerticalCenter(bool center);

	//��ȡĬ���ı���Ϣ
	TextInfo* getDefaultTextInfo() {return &defaultTextInfo;};

	//��ȡ��ͣ�ı���Ϣ
	TextInfo* getHoverTextInfo() {return &hoverTextInfo;};

	//��ȡ�����ı���Ϣ
	TextInfo* getPressedTextInfo() {return &pressedTextInfo;};

	void updataTextInfo();

private:
	void setTextInfo(TextInfo& info);

protected:
	void onDefault() override;
	void onEnter()	override;
	void onLeave()	override;
	void onMouseDown(const ExMessage& msg)	override;
	void onMouseUp(const ExMessage& msg)	override;

private:
	TextWidget* Text = nullptr;
	
	TextInfo defaultTextInfo; //Ĭ���ı���Ϣ
	TextInfo hoverTextInfo; //��ͣ�ı���Ϣ
	TextInfo pressedTextInfo; //�����ı���Ϣ

	WidgetAnchor textAnchor = WidgetAnchor::TopLeft;

};

