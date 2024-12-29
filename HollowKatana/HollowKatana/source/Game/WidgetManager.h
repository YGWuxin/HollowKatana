#pragma once
#include <vector>
#include <type_traits>
#include <graphics.h>
#include "UserWidget.h"

class Controller;

class WidgetManager
{
public:
    // 单例模式获取实例
    static WidgetManager& GetInstance()
    {
        static WidgetManager instance;
        return instance;
    }

    // 模板函数，用于创建 UserWidget 的子类控件
    template<typename T, typename... Args>
    T* createUserWidgetInstance(Args&&... args)
    {
        static_assert(std::is_base_of<UserWidget, T>::value, "T must be a subclass of UserWidget");
        T* widget = new T(std::forward<Args>(args)...);  // 创建控件实例
        
        if (!widget->getParent() && !widget->getIsElementWidget())
        {
            // 将控件添加到列表中进行管理
            widget_list_temp.push_back(widget);
            isSortWidgets = false;
          //  printf("addWidgetInstance\n");
        }
       // printf("addWidgetInstance1\n");
        return widget;
    }

    // 清理所有控件
    void clearAllWidgets();

    // 移除指定的控件
    bool removeWidget(UserWidget* widget);

    //添加控件到视图中
    bool addToView(UserWidget* widget, Controller* controller);

    // 移除控件从视图中
    bool removeFromView(UserWidget* widget);


    // 获取所有控件
    const std::vector<UserWidget*>& getAllWidgets() const
    {
        return widget_list;
    }

    void on_draw();                                             // 绘制
    void on_update(float delta);                                // 更新
    void handleInputEvent(const ExMessage& msg);             // 处理输入事件


private:
    WidgetManager() = default;
    ~WidgetManager() { clearAllWidgets(); }  // 确保在析构时清理控件

    std::vector<UserWidget*> widget_list;  // 控件列表，用来存储所有创建的 UserWidget 实例
    std::vector<UserWidget*> widget_list_temp;  // 控件列表，用来存储所有创建的 UserWidget 实例
    std::vector<UserWidget*> clear_list;  // 控件列表，用来存储所有创建的 UserWidget 实例


    bool isSortWidgets = false;             // 是否需要对控件进行排序


};
