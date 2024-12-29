#include "UserWidget.h"
#include "WidgetElement.h"
#include <iostream>
#include <algorithm>            // for sort

UserWidget::UserWidget(UserWidget* parent, int zOrder)
{
    if (parent)
    {
        parent->addWidget(this);
       // printf("UserWidget::UserWidget\n");
    }
    zOrder = zOrder;
}

UserWidget::~UserWidget()
{
    isDestroy = true;
    for (auto widget: childList)
    {
        if (widget)
            delete widget;
    }
    childList.clear();                  // ��տؼ��б�
   // printf("UserWidget::~UserWidget\n");
}

void UserWidget::setParent(UserWidget* parent)
{
    this->parent = parent;
    if (parent)
    {
       // setPosition(parent->getShowPosition());
      //  printf("UserWidget::setParent111\n");
    }
}

void UserWidget::setZOrder(int zOrder)
{
    this->zOrder = zOrder;
}

void UserWidget::addWidget(UserWidget* widget)
{
    isSortElement = false;                                   // �����Ҫ��������ؼ��б�
    if (widget->getParent() && widget->getParent() != this)
    {
        widget->getParent()->removeWidget(widget);              // �ȴ�ԭ���ؼ����Ƴ��ؼ�
    }
    widget->setParent(this);                                // ���ÿؼ��ĸ��ؼ�
    childList.push_back(widget);                            // ��ӿؼ����б���
}

void UserWidget::removeWidget(UserWidget* widget)
{
    isSortElement = false;
    childList.erase(std::remove(childList.begin(), childList.end(), widget), childList.end());
    if(widget)
        delete widget;
}

void UserWidget::draw()
{
    for (auto widget : childList)
    {
        if (widget && widget->isVisible())
            widget->draw();
    }
    drawDebugRect();

}
void UserWidget::update(float delta)
{
    if (!isSortElement)
    {
        // ���� layer �Ӵ�С����
        std::sort(childList.begin(), childList.end(), [](UserWidget* a, UserWidget* b) {
            return a->getZOrder() < b->getZOrder();
            });
        isSortElement = true;                              // ����������
    }
    
    // �������пؼ�������
    for (auto widget : childList)
    {
        if(widget && widget->isEnabled() && widget->isVisible() && !widget->getIsDestroy())
            widget->update(delta);
        if(widget && widget->getIsDestroy())
            clearWidgetList.push_back(widget);
    }

    // �������������ٵĿؼ�
    for (auto widget : clearWidgetList)
    {
        removeWidget(widget);
    }
    clearWidgetList.clear();

}

bool UserWidget::handleInputEvent(const ExMessage& msg, bool isFocus)
{
    // �����ؼ��б��Ӻ���ǰ��������ֹ�ؼ����ڵ�
    for (auto widget = childList.rbegin(); widget != childList.rend(); ++widget) {
        // �����õ������õ� WidgetElement ָ��
        UserWidget* child_widget = *widget; // ��ȡָ��

        if (child_widget && child_widget->isEnabled() && child_widget->isVisible() && !child_widget->getIsDestroy())
        {
            isFocus = child_widget->handleInputEvent(msg, isFocus);
        }
    }
	return isFocus;
}


void UserWidget::setPosition(const Vector2& pos)
{
    Vector2 parentPos = { 0,0 };
    if (parent)
    {
        parentPos = parent->getShowPosition();
       // printf("parentPos:%f,%f\n", parentPos.x, parentPos.y);
    }
    switch (anchor)
    {
    case WidgetAnchor::TopLeft:
        position = pos + parentPos;
        break;
    case WidgetAnchor::TopCenter:
        position = Vector2(pos.x - size.x / 2 + parentPos.x, pos.y + parentPos.y);
        break;
    case WidgetAnchor::TopRight:
        position = Vector2(pos.x - size.x + parentPos.x, pos.y + parentPos.y);
        break;
    case WidgetAnchor::MiddleLeft:
        position = Vector2(pos.x + parentPos.x, pos.y - size.y / 2 + parentPos.y);
        break;
    case WidgetAnchor::MiddleCenter:
        position = Vector2(pos.x - size.x / 2 + parentPos.x, pos.y - size.y / 2 + parentPos.y);
        break;
    case WidgetAnchor::MiddleRight:
        position = Vector2(pos.x - size.x + parentPos.x, pos.y - size.y / 2 + parentPos.y);
        break;
    case WidgetAnchor::BottomLeft:
        position = Vector2(pos.x + parentPos.x, pos.y - size.y + parentPos.y);
        break;
    case WidgetAnchor::BottomCenter:
        position = Vector2(pos.x - size.x / 2 + parentPos.x, pos.y - size.y + parentPos.y);
        break;
    case WidgetAnchor::BottomRight:
        position = Vector2(pos.x - size.x + parentPos.x, pos.y - size.y + parentPos.y);
        break;
    }
}



void UserWidget::setPositionX(float x)
{
    Vector2 parentPos = { 0,0 };
    if (parent)
        parentPos = parent->getShowPosition();
    switch (anchor)
    {
    case WidgetAnchor::TopLeft:
        position.x = x + parentPos.x;
        break;
    case WidgetAnchor::TopCenter:
        position.x = x - size.x / 2 + parentPos.x;
        break;
    case WidgetAnchor::TopRight:
        position.x = x - size.x + parentPos.x;
        break;
    case WidgetAnchor::MiddleLeft:
        position.x = x + parentPos.x;
        break;
    case WidgetAnchor::MiddleCenter:
        position.x = x - size.x / 2 + parentPos.x;
        break;
    case WidgetAnchor::MiddleRight:
        position.x = x - size.x + parentPos.x;
        break;
    case WidgetAnchor::BottomLeft:
        position.x = x + parentPos.x;
        break;
    case WidgetAnchor::BottomCenter:
        position.x = x - size.x / 2 + parentPos.x;
        break;
    case WidgetAnchor::BottomRight:
        position.x = x - size.x + parentPos.x;
        break;
    default:
        break;
    }
}


void UserWidget::setPositionY(float y)
{
    Vector2 parentPos = {0,0};
    if(parent)
        parentPos = parent->getShowPosition();

    switch (anchor)
    {
    case WidgetAnchor::TopLeft:
        position.y = y + parentPos.y;
        break;
    case WidgetAnchor::TopCenter:
        position.y = y + parentPos.y;
        break;
    case WidgetAnchor::TopRight:
        position.y = y + parentPos.y;
        break;
    case WidgetAnchor::MiddleLeft:
        position.y = y - size.y / 2 + parentPos.y;
        break;
    case WidgetAnchor::MiddleCenter:
        position.y = y - size.y / 2 + parentPos.y;
        break;
    case WidgetAnchor::MiddleRight:
        position.y = y - size.y / 2 + parentPos.y;
        break;
    case WidgetAnchor::BottomLeft:
        position.y = y - size.y + parentPos.y;
        break;
    case WidgetAnchor::BottomCenter:
        position.y = y - size.y + parentPos.y;
        break;
    case WidgetAnchor::BottomRight:
        position.y = y - size.y + parentPos.y;
        break;
    default:
        break;
    }
}