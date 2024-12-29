#include "TextWidget.h"


void TextWidget::draw()
{
    // 设置字体
    setbkmode(TRANSPARENT);
    setfont(fontSize, fontWeight, fontName.c_str());
    // 绘制文字
    if (autoWrap) {
        drawWrappedText();
    }
    else {
        drawSingleLineText();
    }

    UserWidget::draw();
}



void TextWidget::drawWrappedText()
{
    std::wstring currentLine;
    int lineHeight = textheight(L"A");
    int yOffset = 0;

    for (const wchar_t& ch : text) {
        currentLine += ch;

        if (textwidth(currentLine.c_str()) > size.x) {
            drawLine(currentLine.substr(0, currentLine.size() - 1), yOffset);
            yOffset += lineHeight;
            currentLine = ch;
        }
    }

    if (!currentLine.empty()) {
        drawLine(currentLine, yOffset);
    }
}


void TextWidget::drawLine(const std::wstring& line, int yOffset)
{
    int lineWidth = textwidth(line.c_str());
    int lineHeight = textheight(line.c_str());
    int centeredX = centerHorizontal ? position.x + (size.x - lineWidth) / 2 : position.x;
    int centeredY = centerVertical ? position.y  + (size.y  - lineHeight) / 2 : position.y;

    if (hasShadow) {
        // 绘制阴影
        setcolor(shadowColor);
        outtextxy(centeredX + 2, centeredY + yOffset + 2, line.c_str());
    }
    setcolor(textColor);
    outtextxy(centeredX, centeredY + yOffset, line.c_str());
}


void TextWidget::onEnter()
{
    printf("TextWidget onEnter\n");
}
void TextWidget::onLeave()
{
    printf("TextWidget onLeave\n");
}
void TextWidget::onMouseMove(const ExMessage& msg)
{
    printf("TextWidget onMouseMove\n");
}
