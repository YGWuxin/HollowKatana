#pragma once
#include <graphics.h>  // EasyX ��
#include <functional>  // ����ص�
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
    bool handleInputEvent(const ExMessage& msg, bool isFocus) override                  // ���������¼�
    {  
        if (!isInputEventEnabled)
            return isFocus;

        //������һ�����λ��,��Ϊ�����û���ƶ�ʱ����ȡ��������λ��
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
            else if(msg.message == WM_LBUTTONUP || msg.message == WM_RBUTTONUP)     // ���̧��
            {
                status = WidgetStatus::MouseUp;
                onMouseUp(msg);
            }
            else if(msg.message == WM_LBUTTONDOWN || msg.message == WM_RBUTTONDOWN)   // ��갴��
            {
                status = WidgetStatus::MouseDown;
                onMouseDown(msg);
            }
            else if(msg.message == WM_KEYDOWN)   // ���̰���
            {
                status = WidgetStatus::KeyDown;
                onKeyDown(msg);
            }
            else if(msg.message == WM_KEYUP)     // ����̧��
            {
                status = WidgetStatus::KeyUp;
                onKeyUp(msg);
            }
            return true;
        }

        if (!isChildInputEnabled)
            UserWidget::handleInputEvent(msg, true);

        //���ؼ�����ΪĬ��״̬
        if (status == WidgetStatus::Leave && !isEnter)
        {
            status = WidgetStatus::Default;
            onDefault();
        }

        //�ؼ�ʧȥ����
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

  
    //�����Ƿ�ɼ�
    void setVisible(bool visible) override
    {
       UserWidget::setVisible(visible);
        //�ؼ�ʧȥ����
       status = WidgetStatus::Default;
       lastMouseX = -1;
       lastMouseY = -1;
       isEnter = false;
       onDefault();
      // printf("onDefault\n");
    }
    
    //�����Ƿ����
    void setEnabled(bool enabled) { this->enabled = enabled; }
    //���ò㼶
    void setZOrder(int zOrder) { this->zOrder = zOrder; }
    //����ê��
    void setAnchor(WidgetAnchor anchor) { this->anchor = anchor; }

    /*
        �����¼��ص�����
    */
    //�����������¼��ص�����
    void setOnEventEnter(const std::function<void()>& func) { onEventEnter = func; }
    //��������뿪�¼��ص�����
    void setOnEventLeave(const std::function<void()>& func) { onEventLeave = func; }
    //��������ƶ��¼��ص�����
    void setOnMouseMove(const std::function<void()>& func) { onEventMouseMove = func; }

    //��ȡ��ʾ��λ��
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
    //��ȡ��ʾ�Ĵ�С
    const Vector2& getSize() const { return size; }
    //��ȡ�Ƿ�ɼ�
    bool isVisible() const { return visible; }
    //��ȡ�Ƿ����
    bool isEnabled() const { return enabled; }
    //��ȡ�㼶
    int getZOrder() const { return zOrder; }
    //��ȡê��,Ĭ��ê��Ϊ���Ͻ�
    WidgetAnchor getAnchor() const { return anchor; }
    //��ȡ���ؼ�
    UserWidget* getParent() const { return parent; }

    //��ȡ״̬
    WidgetStatus getStatus() const { return status; }
     
    //���õ���ģʽ
    void setDebug(bool debug) { isDebug = debug; }

    //��ȡ�Ƿ����ģʽ
    bool isDebugMode() const { return isDebug; }

    //���õ�����ɫ
    void setDebugColor(COLORREF color) { debugColor = color; }

   


protected:
    //���Ƶ��Ծ���
    void drawDebugRect() override
    {
        if (isDebug)
        {
            //���ƾ��� 
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
    bool isEnter = false;                            // �Ƿ��ý���

    

private:
    int lastMouseX = -1, lastMouseY = -1;

    std::function<void()> onEventEnter = nullptr;       // �������¼��ص�����
    std::function<void()> onEventLeave = nullptr;       // ����뿪�¼��ص�����
    std::function<void()> onEventMouseMove = nullptr;        // ����ƶ��¼��ص�����

    bool isDebug = false;                               // �Ƿ����ģʽ
    COLORREF debugColor = RGB(255, 0, 0);               // ������ɫ

};

