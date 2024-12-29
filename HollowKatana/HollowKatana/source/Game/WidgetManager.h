#pragma once
#include <vector>
#include <type_traits>
#include <graphics.h>
#include "UserWidget.h"

class Controller;

class WidgetManager
{
public:
    // ����ģʽ��ȡʵ��
    static WidgetManager& GetInstance()
    {
        static WidgetManager instance;
        return instance;
    }

    // ģ�庯�������ڴ��� UserWidget ������ؼ�
    template<typename T, typename... Args>
    T* createUserWidgetInstance(Args&&... args)
    {
        static_assert(std::is_base_of<UserWidget, T>::value, "T must be a subclass of UserWidget");
        T* widget = new T(std::forward<Args>(args)...);  // �����ؼ�ʵ��
        
        if (!widget->getParent() && !widget->getIsElementWidget())
        {
            // ���ؼ���ӵ��б��н��й���
            widget_list_temp.push_back(widget);
            isSortWidgets = false;
          //  printf("addWidgetInstance\n");
        }
       // printf("addWidgetInstance1\n");
        return widget;
    }

    // �������пؼ�
    void clearAllWidgets();

    // �Ƴ�ָ���Ŀؼ�
    bool removeWidget(UserWidget* widget);

    //��ӿؼ�����ͼ��
    bool addToView(UserWidget* widget, Controller* controller);

    // �Ƴ��ؼ�����ͼ��
    bool removeFromView(UserWidget* widget);


    // ��ȡ���пؼ�
    const std::vector<UserWidget*>& getAllWidgets() const
    {
        return widget_list;
    }

    void on_draw();                                             // ����
    void on_update(float delta);                                // ����
    void handleInputEvent(const ExMessage& msg);             // ���������¼�


private:
    WidgetManager() = default;
    ~WidgetManager() { clearAllWidgets(); }  // ȷ��������ʱ����ؼ�

    std::vector<UserWidget*> widget_list;  // �ؼ��б������洢���д����� UserWidget ʵ��
    std::vector<UserWidget*> widget_list_temp;  // �ؼ��б������洢���д����� UserWidget ʵ��
    std::vector<UserWidget*> clear_list;  // �ؼ��б������洢���д����� UserWidget ʵ��


    bool isSortWidgets = false;             // �Ƿ���Ҫ�Կؼ���������


};
