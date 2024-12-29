#include "WidgetManager.h"
#include <algorithm>            // for sort
#include "UserWidget.h"
#include "Controller.h"

void WidgetManager::clearAllWidgets()
{
    for (UserWidget* widget : widget_list)
    {
        if (widget)
            widget->canDestroy();
    }
}

bool WidgetManager::removeWidget(UserWidget* widget)
{
    if (!widget)
        return false;
    if (widget->getIsElementWidget())
        return false;
    widget_list.erase(std::remove(widget_list.begin(), widget_list.end(), widget), widget_list.end());
    delete widget;  // ɾ���ؼ�
    isSortWidgets = false;
    return true;
}


bool WidgetManager::addToView(UserWidget* widget, Controller* controller)
{
    if(!widget)
        return false;
    if (widget->getIsElementWidget())
        return false;
    widget->setAddedToView(true);
    widget->setOwnerController(controller);
    return true;
}


bool WidgetManager::removeFromView(UserWidget* widget)
{
    if (!widget)
        return false;
    if (widget->getIsElementWidget())
        return false;
    widget->setAddedToView(false);
    widget->setOwnerController(nullptr);
}


void WidgetManager::on_draw()
{
    // �������пؼ�
    for (auto widget : widget_list)
    {
        if (widget && widget->isVisible() && widget->getIsAddedToView() && !widget->getParent())
            widget->draw();
    }
}

void WidgetManager::on_update(float delta)
{
    // �Ƚ� actors_list_temp �е�Ԫ����ӵ� actors_list ��
    for (auto it = widget_list_temp.begin(); it != widget_list_temp.end(); ++it)
    {
        UserWidget* actor_ptr = *it;
        widget_list.push_back(actor_ptr);
    }
    widget_list_temp.clear();


    if (!isSortWidgets)
    {
        // ���� layer �Ӵ�С����
        std::sort(widget_list.begin(), widget_list.end(), [](UserWidget* a, UserWidget* b) {
            return a->getZOrder() < b->getZOrder();
            });
        isSortWidgets = true;                              // ����������
    }

    // �������пؼ�������
    for (auto widget : widget_list)
    {
        if(!widget)
            continue;
        if (widget->isEnabled() && widget->isVisible() && widget->getIsAddedToView() && !widget->getParent())
            widget->update(delta);
        if(widget->getIsDestroy())
            clear_list.push_back(widget);
    }

    for (auto widget : clear_list)
    {
        removeWidget(widget);
    }
    clear_list.clear();
}


void WidgetManager::handleInputEvent(const ExMessage& msg)
{
    bool isFocused = false;        // �Ƿ��ȡ����
    for (auto it = widget_list.rbegin(); it != widget_list.rend(); ++it) {
        // �����õ������õ� WidgetElement ָ��
        UserWidget* widget = *it; // ��ȡָ��

        if(widget && widget->isEnabled() && widget->isVisible() && widget->getIsAddedToView() 
            && widget->getOwnerController() && !widget->getParent() && widget->getInputWigdetEventEnabled())
        {
            if (!widget->getOwnerController()->get_can_input())
                continue;
            isFocused = widget->handleInputEvent(msg, isFocused);
        }
    }
}