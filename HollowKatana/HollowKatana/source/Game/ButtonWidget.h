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
		IMAGE* image = nullptr;			// 图片
		IMAGE* scaledImage = nullptr;	// 缩放后的图片
		int offsetX = 0;					// 图片偏移X
		int offsetY = 0;					// 图片偏移Y
		bool isFill = false;			// 是否填充整个按钮图片
		bool getImageValid() { return image != nullptr; }
	};

	struct ButtonBGInfo
	{
		ButtonState state = ButtonState::Invalid;
		ImageInfo image_info;
		COLORREF color = RGB(0, 0, 0);
		COLORREF lineColor = RGB(0, 0, 0);
		int ellipsewidth = 0;				// 按钮背景椭圆宽度
		int ellipseheight = 0;				// 按钮背景椭圆高度
		bool isDrawLine = false;			// 是否绘制按钮边框
		bool isShowBackground = true;		// 是否显示背景
		std::string SoundPath;				// 按钮音效路径
		ButtonBGInfo(COLORREF color, COLORREF lineColor, ButtonState state) : color(color), lineColor(lineColor), state(state) {}
	};


public:
	ButtonWidget(UserWidget* parent, Vector2 position, Vector2 size,int zOrder, LPCTSTR className, WidgetAnchor anchor = WidgetAnchor::TopLeft);
	~ButtonWidget();

public:
	void draw() override;                                                                // 绘制
	void update(float delta) override;													 // 更新

	//设置按键点击事件的回调函数
	void setOnClickFunc(std::function<void()> func) { onClick = func; }
	//设置按下事件的回调函数
	void setOnPressFunc(std::function<void()> func) { onPress = func; }
	//设置释放事件的回调函数
	void setOnReleaseFunc(std::function<void()> func) { onRelease = func; }
	//设置鼠标悬停事件的回调函数
	void setOnHoverFunc(std::function<void()> func) { onHover = func; }

	//获取是否鼠标悬停
	bool getIsHover() { return isHover; }

	//设置按钮颜色
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

	//设置按钮边框颜色
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

	//设置按钮边框颜色
	void setLineColor(COLORREF color) { defaultBGInfo.lineColor = color; hoverBGInfo.lineColor = color;
	pressBGInfo.lineColor = color; updateCurrentButtonInfo();};

	//设置是否绘按钮边框
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
	//设置是否启用绘制按钮边框
	void setIsDrawLine(bool isDraw) { defaultBGInfo.isDrawLine = isDraw; hoverBGInfo.isDrawLine = isDraw; 
	pressBGInfo.isDrawLine = isDraw; updateCurrentButtonInfo(); };

	//设置圆角半径
	void setEllipseRadius(int radius) { defaultBGInfo.ellipsewidth = radius; defaultBGInfo.ellipseheight = radius; 
	hoverBGInfo.ellipsewidth = radius; hoverBGInfo.ellipseheight = radius; 
	pressBGInfo.ellipsewidth = radius; pressBGInfo.ellipseheight = radius; updateCurrentButtonInfo(); };

	//设置按钮背景图片
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

	//设置按钮背景音效
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

	//设置是否显示背景
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

	//设置图片偏移
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


	//设置是否填充整个按钮图片
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
	//设置按钮的颜色
	void setColor(COLORREF color) { currentBGInfo.color = color; };

	//设置按钮信息
	void setButtonInfo(const ButtonBGInfo& info) { currentBGInfo = info; buttonState = info.state; };

	void playSound();									// 播放按钮音效

	void updateCurrentButtonInfo()	// 更新按钮信息
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
	std::function<void()> onClick = nullptr;    // 按钮点击事件的回调函数
	std::function<void()> onPress = nullptr;	// 按钮按下事件的回调函数
	std::function<void()> onRelease = nullptr;  // 按钮释放事件的回调函数
	std::function<void()> onHover = nullptr;	// 鼠标悬停事件的回调函数
	bool isHover = false;						// 是否鼠标悬停
	
	/* 按钮背景相关 */
	ButtonBGInfo defaultBGInfo = ButtonBGInfo(RGB(0, 120, 215), RGB(0, 0, 0), ButtonState::Default);					// 默认背景信息
	ButtonBGInfo hoverBGInfo = ButtonBGInfo(RGB(173, 216, 230), RGB(0, 0, 0), ButtonState::Hover);					// 鼠标悬停背景信息
	ButtonBGInfo pressBGInfo = ButtonBGInfo(RGB(192, 192, 192), RGB(0, 0, 0), ButtonState::Press);					// 按下背景信息
	ButtonBGInfo currentBGInfo = defaultBGInfo;													// 当前背景信息


protected:
	ButtonState buttonState = ButtonState::Default;												// 按钮状态

};

