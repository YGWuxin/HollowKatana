#pragma once
#include <vector>
#include <graphics.h>
#include "Vector2.h"
#include "../Parameter/GlobeGameParameters.h"


class WidgetElement;
class WidgetManager;
class Controller;

class UserWidget
{
	friend class WidgetManager;

public:
	enum class WidgetStatus
	{
		//未获得焦点
		Default,
		//事件进入
		Enter,
		//事件离开
		Leave,
		//鼠标按下
		MouseDown,
		//鼠标抬起
		MouseUp,
		//鼠标移动
		MouseMove,
		//键盘按下
		KeyDown,
		//键盘抬起
		KeyUp,
	};

	enum class InputObject
	{
		Self,
		Chlid,
		Parent,
		Root,
	};

public:
	UserWidget(UserWidget* parent, int zOrder);
	virtual ~UserWidget();

	void addWidget(UserWidget* widget);	// 添加控件元素

	void removeWidget(UserWidget* widget);	// 移除控件元素

	virtual void draw();														            // 绘制
	virtual void update(float delta);														// 更新
	virtual bool handleInputEvent(const ExMessage& msg, bool isFocus);						// 处理输入事件


	void setZOrder(int zOrder);				 // 设置层级
	int getZOrder() const {return zOrder;};									// 获取层级

	virtual void setVisible(bool visible) 
	{
		this->visible = visible; 
		for (auto child : childList)
		{
			child->setVisible(visible);
		}
	};			// 设置可见性


	bool isVisible() const {return visible;};							// 是否可见

	void setEnabled(bool enabled) {this->enabled = enabled;};			// 设置可用性
	bool isEnabled() const {return enabled;};							// 是否可用

	bool getIsAddedToView() const {return isAddedToView;};				// 是否已添加到视图中

	void setOwnerController(Controller* controller)
	{ 
		owner_controller = controller; 
		for (auto child : childList)
		{
			child->setOwnerController(controller);
		}
	};	// 设置所属控制器

	Controller* getOwnerController() const { return owner_controller; };	// 获取所属控制器

	void setParent(UserWidget* parent);	// 设置父控件

	UserWidget* getParent() const { return parent; };				// 获取父控件

	void canDestroy() { isDestroy = true; };					// 销毁

	bool getIsDestroy() { return isDestroy; };					// 是否销毁

	//获取名字
	LPCTSTR getClassName() const { return className; }

	//获取是否为控件元素，包括子控件
	bool getIsElementWidget() const { return isElementWidget; }

	//设置是否允许输入事件，包括子控件
	void setInputWigdetEventEnabled(bool enabled) { isInputEventEnabled = enabled; }

	//获取是否允许输入事件
	bool getInputWigdetEventEnabled() const { return isInputEventEnabled; }

	//设置是否禁止触发输入事件
	void setInputEventEnabled(bool enabled, InputObject object = InputObject::Self)
	{
		switch (object)
		{
		case UserWidget::InputObject::Self:
			isSelfInputEnabled = enabled;
			break;
		case UserWidget::InputObject::Chlid:
			isChildInputEnabled = enabled;
			break;
		case UserWidget::InputObject::Parent:
			if (parent)
				isSelfInputEnabled = enabled;
			break;
		case UserWidget::InputObject::Root:
			if(parent)
				parent->setInputEventEnabled(enabled, InputObject::Root);
			else
				isSelfInputEnabled = enabled;
			break;
		default:
			break;
		}
	}

	void setFoucs(bool focus) { isWidgetFocus = focus; }

	bool getIsFocus() const { return isWidgetFocus; }

	void setPositionX(float x);

	void setPositionY(float y);

	//设置显示的位置
	void setPosition(const Vector2& pos);

	//获取显示位置
	Vector2 getShowPosition() const { return position; }

	//设置位置的偏移量
	void addPositionOffset(const Vector2& offset) { position += offset; }
	//设置位置的偏移量X
	void addPositionOffsetX(int offset_x) { position.x += offset_x; }
	//设置位置的偏移量Y
	void addPositionOffsetY(int offset_y) { position.y += offset_y; }

	//设置显示的大小
	void setSize(const Vector2& size) { this->size = size; }

protected:
	void setAddedToView(bool addedToView) 
	{ 
		isAddedToView = addedToView;
	};	// 设置是否已添加到视图中

	virtual void drawDebugRect() {};									// 绘制调试矩形

protected:
	UserWidget* parent = nullptr;							// 父控件
	LPCTSTR className = _T("Widget");						// 类名
	WidgetStatus status = WidgetStatus::Default;			// 状态
	bool isSortElement = false;								// 是否需要排序
	bool visible = true;									// 是否可见
	bool enabled = true;									// 是否可用
	bool isAddedToView = false;								// 是否已添加到视图中	
	int zOrder = 0;											// 层级
	Controller* owner_controller = nullptr;						// 所属控制器
	bool isDestroy = false;									// 是否销毁
	bool isElementWidget = false;							// 是否为控件元素
	bool isInputEventEnabled = true;						// 是否允许输入事件，包括子控件
	//子类触发输入
	bool isChildInputEnabled = true;
	//自己触发输入
	bool isSelfInputEnabled = true;

	bool isWidgetFocus = false;									// 是否获得焦点

	Vector2 position = Vector2(0, 0);						// 位置
	Vector2 size = Vector2(0, 0);							// 大小
	WidgetAnchor anchor = WidgetAnchor::TopLeft;			// 锚点,默认锚点为左上角

private:
	std::vector<UserWidget*> clearWidgetList;					// 控件元素集合
	std::vector<UserWidget*> childList;							// 子控件集合

};




