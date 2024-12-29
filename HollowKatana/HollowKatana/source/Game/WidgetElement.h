#pragma once
#include <graphics.h>  // EasyX 库
#include <functional>  // 处理回调
#include "Vector2.h"
#include "../Parameter/GlobeGameParameters.h"
#include <conio.h>
#include <windows.h>
#include "../Utils/helper.h""
#include "UserWidget.h"
#include "WidgetManager.h"

class WidgetElement : public UserWidget
{


public:
    WidgetElement(UserWidget* parent, Vector2 position, Vector2 size, int zOrder, LPCTSTR className, WidgetAnchor anchor = WidgetAnchor::TopLeft)
        : UserWidget(parent, zOrder)
    {
        this->size = size;
        this->zOrder = zOrder;
        this->className = className;
        this->anchor = anchor;
        setPosition(position);
        isElementWidget = true;
    }

    ~WidgetElement() = default;

    void draw() override
    {
        UserWidget::draw();
    }

    void update(float delta) override
    {
        UserWidget::update(delta);
    }
    bool handleInputEvent(const ExMessage& msg, bool isFocus) override                  // 处理输入事件
    {  
        if (!isInputEventEnabled)
            return isFocus;

        //更新上一次鼠标位置,因为当鼠标没有移动时，获取不到鼠标的位置
        if (msg.message == WM_MOUSEMOVE)
        {
            lastMouseX = msg.x;
            lastMouseY = msg.y;
        }

        if (position.x <= lastMouseX && lastMouseX <= position.x + size.x && position.y <= lastMouseY && lastMouseY <= position.y + size.y && !isFocus || isWidgetFocus)
        {
            if(isChildInputEnabled)
                UserWidget::handleInputEvent(msg, false);
            if(!isSelfInputEnabled)
                return true;

            if (msg.message == WM_MOUSEMOVE)
            {
                if (!isEnter)
                {
                    status = WidgetStatus::Enter;
                    isEnter = true;
                    if (onEventEnter)
                        onEventEnter();
                    onEnter();
                }
                else
                {
                    status = WidgetStatus::MouseMove;
                    if (onEventMouseMove)
                        onEventMouseMove();
                    onMouseMove(msg);
                }
            }
            else if(msg.message == WM_LBUTTONUP || msg.message == WM_RBUTTONUP)     // 鼠标抬起
            {
                status = WidgetStatus::MouseUp;
                onMouseUp(msg);
            }
            else if(msg.message == WM_LBUTTONDOWN || msg.message == WM_RBUTTONDOWN)   // 鼠标按下
            {
                status = WidgetStatus::MouseDown;
                onMouseDown(msg);
            }
            else if(msg.message == WM_KEYDOWN)   // 键盘按下
            {
                status = WidgetStatus::KeyDown;
                onKeyDown(msg);
            }
            else if(msg.message == WM_KEYUP)     // 键盘抬起
            {
                status = WidgetStatus::KeyUp;
                onKeyUp(msg);
            }
            return true;
        }

        if (!isChildInputEnabled)
            UserWidget::handleInputEvent(msg, true);

        //将控件设置为默认状态
        if (status == WidgetStatus::Leave && !isEnter)
        {
            status = WidgetStatus::Default;
            onDefault();
        }

        //控件失去焦点
        if (isEnter)
        {
            status = WidgetStatus::Leave;
            isEnter = false;
            if(onEventLeave)
                onEventLeave();
            onLeave();
        }

        return isFocus;
    };        

  
    //设置是否可见
    void setVisible(bool visible) override
    {
       UserWidget::setVisible(visible);
        //控件失去焦点
       status = WidgetStatus::Default;
       lastMouseX = -1;
       lastMouseY = -1;
       isEnter = false;
       onDefault();
      // printf("onDefault\n");
    }
    
    //设置是否可用
    void setEnabled(bool enabled) { this->enabled = enabled; }
    //设置层级
    void setZOrder(int zOrder) { this->zOrder = zOrder; }
    //设置锚点
    void setAnchor(WidgetAnchor anchor) { this->anchor = anchor; }

    /*
        设置事件回调函数
    */
    //设置鼠标进入事件回调函数
    void setOnEventEnter(const std::function<void()>& func) { onEventEnter = func; }
    //设置鼠标离开事件回调函数
    void setOnEventLeave(const std::function<void()>& func) { onEventLeave = func; }
    //设置鼠标移动事件回调函数
    void setOnMouseMove(const std::function<void()>& func) { onEventMouseMove = func; }

    //获取显示的位置
    const Vector2& getPosition() const 
    {  
        switch (anchor)
        {
        case WidgetAnchor::TopLeft:
            return position;
        case WidgetAnchor::TopCenter:
            return Vector2(position.x + size.x / 2, position.y);
        case WidgetAnchor::TopRight:
            return Vector2(position.x + size.x, position.y);
        case WidgetAnchor::MiddleLeft:
            return Vector2(position.x, position.y + size.y / 2);
        case WidgetAnchor::MiddleCenter:
            return Vector2(position.x + size.x / 2, position.y + size.y / 2);
        case WidgetAnchor::MiddleRight:
            return Vector2(position.x + size.x, position.y + size.y / 2);
        case WidgetAnchor::BottomLeft:
            return Vector2(position.x, position.y + size.y);
        case WidgetAnchor::BottomCenter:
            return Vector2(position.x + size.x / 2, position.y + size.y);
        case WidgetAnchor::BottomRight:
            return Vector2(position.x + size.x, position.y + size.y);
        }
    }
    //获取显示的大小
    const Vector2& getSize() const { return size; }
    //获取是否可见
    bool isVisible() const { return visible; }
    //获取是否可用
    bool isEnabled() const { return enabled; }
    //获取层级
    int getZOrder() const { return zOrder; }
    //获取锚点,默认锚点为左上角
    WidgetAnchor getAnchor() const { return anchor; }
    //获取父控件
    UserWidget* getParent() const { return parent; }

    //获取状态
    WidgetStatus getStatus() const { return status; }
     
    //设置调试模式
    void setDebug(bool debug) { isDebug = debug; }

    //获取是否调试模式
    bool isDebugMode() const { return isDebug; }

    //设置调试颜色
    void setDebugColor(COLORREF color) { debugColor = color; }

   


protected:
    //绘制调试矩形
    void drawDebugRect() override
    {
        if (isDebug)
        {
            //绘制矩形 
            setlinecolor(debugColor);
            roundrect(position.x, position.y, position.x + size.x, position.y + size.y, 0,0);
        }
    }

    virtual void onDefault() {};
    virtual void onEnter() {};
    virtual void onLeave() {};
    virtual void onMouseMove(const ExMessage& msg) {};
    virtual void onMouseDown(const ExMessage& msg) {};
    virtual void onMouseUp(const ExMessage& msg) {};
    virtual void onKeyDown(const ExMessage& msg) {};
    virtual void onKeyUp(const ExMessage& msg) {};

protected:
    bool isEnter = false;                            // 是否获得焦点

    

private:
    int lastMouseX = -1, lastMouseY = -1;

    std::function<void()> onEventEnter = nullptr;       // 鼠标进入事件回调函数
    std::function<void()> onEventLeave = nullptr;       // 鼠标离开事件回调函数
    std::function<void()> onEventMouseMove = nullptr;        // 鼠标移动事件回调函数

    bool isDebug = false;                               // 是否调试模式
    COLORREF debugColor = RGB(255, 0, 0);               // 调试颜色

};

