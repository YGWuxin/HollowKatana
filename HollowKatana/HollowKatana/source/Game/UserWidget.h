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
		//δ��ý���
		Default,
		//�¼�����
		Enter,
		//�¼��뿪
		Leave,
		//��갴��
		MouseDown,
		//���̧��
		MouseUp,
		//����ƶ�
		MouseMove,
		//���̰���
		KeyDown,
		//����̧��
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

	void addWidget(UserWidget* widget);	// ��ӿؼ�Ԫ��

	void removeWidget(UserWidget* widget);	// �Ƴ��ؼ�Ԫ��

	virtual void draw();														            // ����
	virtual void update(float delta);														// ����
	virtual bool handleInputEvent(const ExMessage& msg, bool isFocus);						// ���������¼�


	void setZOrder(int zOrder);				 // ���ò㼶
	int getZOrder() const {return zOrder;};									// ��ȡ�㼶

	virtual void setVisible(bool visible) 
	{
		this->visible = visible; 
		for (auto child : childList)
		{
			child->setVisible(visible);
		}
	};			// ���ÿɼ���


	bool isVisible() const {return visible;};							// �Ƿ�ɼ�

	void setEnabled(bool enabled) {this->enabled = enabled;};			// ���ÿ�����
	bool isEnabled() const {return enabled;};							// �Ƿ����

	bool getIsAddedToView() const {return isAddedToView;};				// �Ƿ�����ӵ���ͼ��

	void setOwnerController(Controller* controller)
	{ 
		owner_controller = controller; 
		for (auto child : childList)
		{
			child->setOwnerController(controller);
		}
	};	// ��������������

	Controller* getOwnerController() const { return owner_controller; };	// ��ȡ����������

	void setParent(UserWidget* parent);	// ���ø��ؼ�

	UserWidget* getParent() const { return parent; };				// ��ȡ���ؼ�

	void canDestroy() { isDestroy = true; };					// ����

	bool getIsDestroy() { return isDestroy; };					// �Ƿ�����

	//��ȡ����
	LPCTSTR getClassName() const { return className; }

	//��ȡ�Ƿ�Ϊ�ؼ�Ԫ�أ������ӿؼ�
	bool getIsElementWidget() const { return isElementWidget; }

	//�����Ƿ����������¼��������ӿؼ�
	void setInputWigdetEventEnabled(bool enabled) { isInputEventEnabled = enabled; }

	//��ȡ�Ƿ����������¼�
	bool getInputWigdetEventEnabled() const { return isInputEventEnabled; }

	//�����Ƿ��ֹ���������¼�
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

	//������ʾ��λ��
	void setPosition(const Vector2& pos);

	//��ȡ��ʾλ��
	Vector2 getShowPosition() const { return position; }

	//����λ�õ�ƫ����
	void addPositionOffset(const Vector2& offset) { position += offset; }
	//����λ�õ�ƫ����X
	void addPositionOffsetX(int offset_x) { position.x += offset_x; }
	//����λ�õ�ƫ����Y
	void addPositionOffsetY(int offset_y) { position.y += offset_y; }

	//������ʾ�Ĵ�С
	void setSize(const Vector2& size) { this->size = size; }

protected:
	void setAddedToView(bool addedToView) 
	{ 
		isAddedToView = addedToView;
	};	// �����Ƿ�����ӵ���ͼ��

	virtual void drawDebugRect() {};									// ���Ƶ��Ծ���

protected:
	UserWidget* parent = nullptr;							// ���ؼ�
	LPCTSTR className = _T("Widget");						// ����
	WidgetStatus status = WidgetStatus::Default;			// ״̬
	bool isSortElement = false;								// �Ƿ���Ҫ����
	bool visible = true;									// �Ƿ�ɼ�
	bool enabled = true;									// �Ƿ����
	bool isAddedToView = false;								// �Ƿ�����ӵ���ͼ��	
	int zOrder = 0;											// �㼶
	Controller* owner_controller = nullptr;						// ����������
	bool isDestroy = false;									// �Ƿ�����
	bool isElementWidget = false;							// �Ƿ�Ϊ�ؼ�Ԫ��
	bool isInputEventEnabled = true;						// �Ƿ����������¼��������ӿؼ�
	//���ഥ������
	bool isChildInputEnabled = true;
	//�Լ���������
	bool isSelfInputEnabled = true;

	bool isWidgetFocus = false;									// �Ƿ��ý���

	Vector2 position = Vector2(0, 0);						// λ��
	Vector2 size = Vector2(0, 0);							// ��С
	WidgetAnchor anchor = WidgetAnchor::TopLeft;			// ê��,Ĭ��ê��Ϊ���Ͻ�

private:
	std::vector<UserWidget*> clearWidgetList;					// �ؼ�Ԫ�ؼ���
	std::vector<UserWidget*> childList;							// �ӿؼ�����

};




