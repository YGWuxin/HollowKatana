#pragma once
#include "WidgetElement.h"
#include <functional>

class UserWidget;
class WidgetManager;

class ButtonWidget :public WidgetElement
{
	friend class WidgetManager;
	friend class UserWidget;

public:
	enum class ButtonState
	{
		Invalid,
		Default,
		Hover,
		Press
	};

private:
	struct ImageInfo
	{
		IMAGE* image = nullptr;			// ͼƬ
		IMAGE* scaledImage = nullptr;	// ���ź��ͼƬ
		int offsetX = 0;					// ͼƬƫ��X
		int offsetY = 0;					// ͼƬƫ��Y
		bool isFill = false;			// �Ƿ����������ťͼƬ
		bool getImageValid() { return image != nullptr; }
	};

	struct ButtonBGInfo
	{
		ButtonState state = ButtonState::Invalid;
		ImageInfo image_info;
		COLORREF color = RGB(0, 0, 0);
		COLORREF lineColor = RGB(0, 0, 0);
		int ellipsewidth = 0;				// ��ť������Բ���
		int ellipseheight = 0;				// ��ť������Բ�߶�
		bool isDrawLine = false;			// �Ƿ���ư�ť�߿�
		bool isShowBackground = true;		// �Ƿ���ʾ����
		std::string SoundPath;				// ��ť��Ч·��
		ButtonBGInfo(COLORREF color, COLORREF lineColor, ButtonState state) : color(color), lineColor(lineColor), state(state) {}
	};


public:
	ButtonWidget(UserWidget* parent, Vector2 position, Vector2 size,int zOrder, LPCTSTR className, WidgetAnchor anchor = WidgetAnchor::TopLeft);
	~ButtonWidget();

public:
	void draw() override;                                                                // ����
	void update(float delta) override;													 // ����

	//���ð�������¼��Ļص�����
	void setOnClickFunc(std::function<void()> func) { onClick = func; }
	//���ð����¼��Ļص�����
	void setOnPressFunc(std::function<void()> func) { onPress = func; }
	//�����ͷ��¼��Ļص�����
	void setOnReleaseFunc(std::function<void()> func) { onRelease = func; }
	//���������ͣ�¼��Ļص�����
	void setOnHoverFunc(std::function<void()> func) { onHover = func; }

	//��ȡ�Ƿ������ͣ
	bool getIsHover() { return isHover; }

	//���ð�ť��ɫ
	void setButtonColor(COLORREF color, ButtonState state)
	{
		switch (state)
		{
		case ButtonState::Default:
			defaultBGInfo.color = color;
			break;
		case ButtonState::Hover:
			hoverBGInfo.color = color;
			break;
		case ButtonState::Press:
			pressBGInfo.color = color;
			break;
		default:
			break;
		}
		updateCurrentButtonInfo();
	}

	//���ð�ť�߿���ɫ
	void setLineColor(COLORREF color, ButtonState state)
	{
		switch (state)
		{
		case ButtonState::Default:
			defaultBGInfo.lineColor = color;
			break;
		case ButtonState::Hover:
			hoverBGInfo.lineColor = color;
			break;
		case ButtonState::Press:
			pressBGInfo.lineColor = color;
			break;
		default:
			break;
		}
		updateCurrentButtonInfo();
	}

	//���ð�ť�߿���ɫ
	void setLineColor(COLORREF color) { defaultBGInfo.lineColor = color; hoverBGInfo.lineColor = color;
	pressBGInfo.lineColor = color; updateCurrentButtonInfo();};

	//�����Ƿ�水ť�߿�
	void setIsDrawLine(bool isDraw, ButtonState state)
	{
		switch (state)
		{
		case ButtonState::Default:
			defaultBGInfo.isDrawLine = isDraw;
			break;
		case ButtonState::Hover:
			hoverBGInfo.isDrawLine = isDraw;
			break;
		case ButtonState::Press:
			pressBGInfo.isDrawLine = isDraw;
			break;
		default:
			break;
		}
		updateCurrentButtonInfo();
	}
	//�����Ƿ����û��ư�ť�߿�
	void setIsDrawLine(bool isDraw) { defaultBGInfo.isDrawLine = isDraw; hoverBGInfo.isDrawLine = isDraw; 
	pressBGInfo.isDrawLine = isDraw; updateCurrentButtonInfo(); };

	//����Բ�ǰ뾶
	void setEllipseRadius(int radius) { defaultBGInfo.ellipsewidth = radius; defaultBGInfo.ellipseheight = radius; 
	hoverBGInfo.ellipsewidth = radius; hoverBGInfo.ellipseheight = radius; 
	pressBGInfo.ellipsewidth = radius; pressBGInfo.ellipseheight = radius; updateCurrentButtonInfo(); };

	//���ð�ť����ͼƬ
	void setBGImage(IMAGE* image, ButtonState state, bool isFill = false)
	{
		switch (state)
		{
		case ButtonState::Default:
			defaultBGInfo.image_info.image = image;
			defaultBGInfo.image_info.isFill = isFill;
			break;
		case ButtonState::Hover:
			hoverBGInfo.image_info.image = image;
			hoverBGInfo.image_info.isFill = isFill;
			break;
		case ButtonState::Press:
			pressBGInfo.image_info.image = image;
			pressBGInfo.image_info.isFill = isFill;
			break;
		default:
			break;
		}
		updateCurrentButtonInfo();
	}

	//���ð�ť������Ч
	void setSoundPath(std::string path, ButtonState state)
	{
		switch (state)
		{
		case ButtonState::Default:
			defaultBGInfo.SoundPath = path;
			break;
		case ButtonState::Hover:
			hoverBGInfo.SoundPath = path;
			break;
		case ButtonState::Press:
			pressBGInfo.SoundPath = path;
			break;
		default:
			break;
		}
	}

	//�����Ƿ���ʾ����
	void setIsShowBackground(bool isShow, ButtonState state)
	{
		switch (state)
		{
		case ButtonState::Default:
			defaultBGInfo.isShowBackground = isShow;
			break;
		case ButtonState::Hover:
			hoverBGInfo.isShowBackground = isShow;
			break;
		case ButtonState::Press:
			pressBGInfo.isShowBackground = isShow;
			break;
		default:
			break;
		}
		updateCurrentButtonInfo();
	}

	//����ͼƬƫ��
	void setImageOffset(int offsetX, int offsetY, ButtonState state)
	{
		switch (state)
		{
		case ButtonState::Default:
			defaultBGInfo.image_info.offsetX = offsetX;
			defaultBGInfo.image_info.offsetY = offsetY;
			break;
		case ButtonState::Hover:
			hoverBGInfo.image_info.offsetX = offsetX;
			hoverBGInfo.image_info.offsetY = offsetY;
			break;
		case ButtonState::Press:
			pressBGInfo.image_info.offsetX = offsetX;
			pressBGInfo.image_info.offsetY = offsetY;
			break;
		default:
			break;
		}
		updateCurrentButtonInfo();
	}
	void setImageOffset(int offsetX, int offsetY) { defaultBGInfo.image_info.offsetX = offsetX; defaultBGInfo.image_info.offsetY = offsetY; hoverBGInfo.image_info.offsetX = offsetX; hoverBGInfo.image_info.offsetY = offsetY; pressBGInfo.image_info.offsetX = offsetX; pressBGInfo.image_info.offsetY = offsetY; updateCurrentButtonInfo(); };


	//�����Ƿ����������ťͼƬ
	void setIsFillImage(bool isFill, ButtonState state)
	{
		switch (state)
		{
		case ButtonState::Default:					
			defaultBGInfo.image_info.isFill = isFill;
			break;
		case ButtonState::Hover:
			hoverBGInfo.image_info.isFill = isFill;
			break;
		case ButtonState::Press:
			pressBGInfo.image_info.isFill = isFill;
			break;
		default:
			break;
		}
		updateCurrentButtonInfo();
	}
	void setIsFillImage(bool isFill) { defaultBGInfo.image_info.isFill = isFill; hoverBGInfo.image_info.isFill = isFill; pressBGInfo.image_info.isFill = isFill; updateCurrentButtonInfo(); };

	void setButtonState(ButtonState state) { buttonState = state; updateCurrentButtonInfo(); };

protected:
	void onDefault() override;
	void onEnter() override;
	void onLeave()override;
	void onMouseDown(const ExMessage& msg) override;
	void onMouseUp(const ExMessage& msg) override;
	void onMouseMove(const ExMessage& msg) override;

private:
	//���ð�ť����ɫ
	void setColor(COLORREF color) { currentBGInfo.color = color; };

	//���ð�ť��Ϣ
	void setButtonInfo(const ButtonBGInfo& info) { currentBGInfo = info; buttonState = info.state; };

	void playSound();									// ���Ű�ť��Ч

	void updateCurrentButtonInfo()	// ���°�ť��Ϣ
	{
		switch (buttonState)
		{
		case ButtonWidget::ButtonState::Default:
			currentBGInfo = defaultBGInfo;
			break;
		case ButtonWidget::ButtonState::Hover:
			currentBGInfo = hoverBGInfo;
			break;
		case ButtonWidget::ButtonState::Press:
			currentBGInfo = pressBGInfo;
			break;
		default:
			break;
		}
	}



private:
	std::function<void()> onClick = nullptr;    // ��ť����¼��Ļص�����
	std::function<void()> onPress = nullptr;	// ��ť�����¼��Ļص�����
	std::function<void()> onRelease = nullptr;  // ��ť�ͷ��¼��Ļص�����
	std::function<void()> onHover = nullptr;	// �����ͣ�¼��Ļص�����
	bool isHover = false;						// �Ƿ������ͣ
	
	/* ��ť������� */
	ButtonBGInfo defaultBGInfo = ButtonBGInfo(RGB(0, 120, 215), RGB(0, 0, 0), ButtonState::Default);					// Ĭ�ϱ�����Ϣ
	ButtonBGInfo hoverBGInfo = ButtonBGInfo(RGB(173, 216, 230), RGB(0, 0, 0), ButtonState::Hover);					// �����ͣ������Ϣ
	ButtonBGInfo pressBGInfo = ButtonBGInfo(RGB(192, 192, 192), RGB(0, 0, 0), ButtonState::Press);					// ���±�����Ϣ
	ButtonBGInfo currentBGInfo = defaultBGInfo;													// ��ǰ������Ϣ


protected:
	ButtonState buttonState = ButtonState::Default;												// ��ť״̬

};

