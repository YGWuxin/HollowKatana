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

    void draw() override;                                        // ����

    // �����ı�����
    void setText(const std::wstring& newText) {
        text = newText;
    }

    // ��ȡ�ı�����
    const std::wstring& getText() const {
        return text;
    }

    // ��������
    void setFont(const std::wstring& newFont) {
        fontName = newFont;
    }

    // ���������С
    void setFontSize(int size) {
        fontSize = size;
    }

    // ������ӰЧ��
    void setShadow(bool shadow) {
        hasShadow = shadow;
    }

    // �����ı���ɫ
    void setTextColor(COLORREF color) {
        textColor = color;
    }

    // ������Ӱ��ɫ
    void setShadowColor(COLORREF color) {
        shadowColor = color;
    }

    // �����Ƿ��Զ�����
    void setWrap(bool wrap) {
        autoWrap = wrap;
    }

    // ��������ֶ�
    void setFontWeight(int weight) {
        fontWeight = weight;
    }

    // �����Ƿ�ˮƽ����
    void setCenterHorizontal(bool center) {
        centerHorizontal = center;
    }

    // �����Ƿ�ֱ����
    void setCenterVertical(bool center) {
        centerVertical = center;
    }


protected:
    void onEnter() override;                                    // ����
    void onLeave() override;                                    // �뿪
    void onMouseMove(const ExMessage& msg) override;

private:
    // �����Զ����е��ı�
    void drawWrappedText();

    // ����һ���ı�
    void drawLine(const std::wstring& line, int yOffset);

    // ���Ƶ����ı�
    void drawSingleLineText() {
        drawLine(text, 0);
    }

  

private:
    std::wstring text = L"";                                // �ı����ݣ����ַ���
    std::wstring fontName = L"����";                          // �������ƣ����ַ���
    int fontSize = 30;                                      // �����С
    bool hasShadow = false;                                  // �Ƿ�����Ӱ
    COLORREF textColor = RGB(255, 255, 255);                 // �ı���ɫ
    COLORREF shadowColor = RGB(0, 0, 0);                     // ��Ӱ��ɫ
    bool autoWrap = false;                                  //�Ƿ��Զ�����
    int fontWeight = 0;                                         // ����ֶ�
    bool centerHorizontal = false;                                  // �Ƿ�ˮƽ����
    bool centerVertical = false;                                    // �Ƿ�ֱ����
};

