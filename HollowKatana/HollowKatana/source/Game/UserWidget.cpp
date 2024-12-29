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
    childList.clear();                  // 清空控件列表
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
    isSortElement = false;                                   // 标记需要重新排序控件列表
    if (widget->getParent() && widget->getParent() != this)
    {
        widget->getParent()->removeWidget(widget);              // 先从原父控件中移除控件
    }
    widget->setParent(this);                                // 设置控件的父控件
    childList.push_back(widget);                            // 添加控件到列表中
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
        // 按照 layer 从大到小排序
        std::sort(childList.begin(), childList.end(), [](UserWidget* a, UserWidget* b) {
            return a->getZOrder() < b->getZOrder();
            });
        isSortElement = true;                              // 标记排序完成
    }
    
    // 更新所有控件的内容
    for (auto widget : childList)
    {
        if(widget && widget->isEnabled() && widget->isVisible() && !widget->getIsDestroy())
            widget->update(delta);
        if(widget && widget->getIsDestroy())
            clearWidgetList.push_back(widget);
    }

    // 销毁所有已销毁的控件
    for (auto widget : clearWidgetList)
    {
        removeWidget(widget);
    }
    clearWidgetList.clear();

}

bool UserWidget::handleInputEvent(const ExMessage& msg, bool isFocus)
{
    // 遍历控件列表，从后往前遍历，防止控件被遮挡
    for (auto widget = childList.rbegin(); widget != childList.rend(); ++widget) {
        // 解引用迭代器得到 WidgetElement 指针
        UserWidget* child_widget = *widget; // 获取指针

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