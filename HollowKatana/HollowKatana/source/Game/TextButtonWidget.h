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
		LPCTSTR fontName = _T("宋体");
		bool debug = false;
		bool horizontalCenter = false;
		bool verticalCenter = false;

	};
public:
	TextButtonWidget(UserWidget* parent, Vector2 position, Vector2 size, int zOrder, LPCTSTR className, WidgetAnchor anchor = WidgetAnchor::TopLeft);
	~TextButtonWidget() = default;

	//设置文本内容
	void setText(LPCTSTR text);

	void setText(LPCTSTR text,ButtonState state);

	//设置文本颜色
	void setTextColor(COLORREF color);

	void setTextColor(COLORREF color, ButtonState state);

	//设置字体大小
	void setFontSize(int size);

	void setFontSize(int size, ButtonState state);

	//设置字体名称
	void setFont(LPCTSTR name);

	void setFont(LPCTSTR name, ButtonState state);

	//是否启用文本控件调试
	void setDebugText(bool debug);

	//是否设置文本控件水平居中
	void setTextHorizontalCenter(bool center);

	//是否设置文本控件垂直居中
	void setTextVerticalCenter(bool center);

	//获取默认文本信息
	TextInfo* getDefaultTextInfo() {return &defaultTextInfo;};

	//获取悬停文本信息
	TextInfo* getHoverTextInfo() {return &hoverTextInfo;};

	//获取按下文本信息
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
	
	TextInfo defaultTextInfo; //默认文本信息
	TextInfo hoverTextInfo; //悬停文本信息
	TextInfo pressedTextInfo; //按下文本信息

	WidgetAnchor textAnchor = WidgetAnchor::TopLeft;

};

