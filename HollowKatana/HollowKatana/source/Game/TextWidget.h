#pragma once
#include "WidgetElement.h"
#include <string>

class TextWidget :public WidgetElement
{
public:
	TextWidget(UserWidget* parent, Vector2 position, Vector2 size, int zOrder, LPCTSTR className, WidgetAnchor anchor = WidgetAnchor::TopLeft)
		: WidgetElement(parent, position, size, zOrder, className, anchor) {
        setInputWigdetEventEnabled(false);
       // setInputEventEnabled(false,UserWidget::InputObject::Self);
    };
	~TextWidget() = default;

    void draw() override;                                        // 绘制

    // 设置文本内容
    void setText(const std::wstring& newText) {
        text = newText;
    }

    // 获取文本内容
    const std::wstring& getText() const {
        return text;
    }

    // 设置字体
    void setFont(const std::wstring& newFont) {
        fontName = newFont;
    }

    // 设置字体大小
    void setFontSize(int size) {
        fontSize = size;
    }

    // 设置阴影效果
    void setShadow(bool shadow) {
        hasShadow = shadow;
    }

    // 设置文本颜色
    void setTextColor(COLORREF color) {
        textColor = color;
    }

    // 设置阴影颜色
    void setShadowColor(COLORREF color) {
        shadowColor = color;
    }

    // 设置是否自动换行
    void setWrap(bool wrap) {
        autoWrap = wrap;
    }

    // 设置字体粗度
    void setFontWeight(int weight) {
        fontWeight = weight;
    }

    // 设置是否水平居中
    void setCenterHorizontal(bool center) {
        centerHorizontal = center;
    }

    // 设置是否垂直居中
    void setCenterVertical(bool center) {
        centerVertical = center;
    }


protected:
    void onEnter() override;                                    // 进入
    void onLeave() override;                                    // 离开
    void onMouseMove(const ExMessage& msg) override;

private:
    // 绘制自动换行的文本
    void drawWrappedText();

    // 绘制一行文本
    void drawLine(const std::wstring& line, int yOffset);

    // 绘制单行文本
    void drawSingleLineText() {
        drawLine(text, 0);
    }

  

private:
    std::wstring text = L"";                                // 文本内容（宽字符）
    std::wstring fontName = L"黑体";                          // 字体名称（宽字符）
    int fontSize = 30;                                      // 字体大小
    bool hasShadow = false;                                  // 是否有阴影
    COLORREF textColor = RGB(255, 255, 255);                 // 文本颜色
    COLORREF shadowColor = RGB(0, 0, 0);                     // 阴影颜色
    bool autoWrap = false;                                  //是否自动换行
    int fontWeight = 0;                                         // 字体粗度
    bool centerHorizontal = false;                                  // 是否水平居中
    bool centerVertical = false;                                    // 是否垂直居中
};

