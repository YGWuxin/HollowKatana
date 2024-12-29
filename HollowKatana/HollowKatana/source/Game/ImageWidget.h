#pragma once
#include "WidgetElement.h"
#include <functional>

class UserWidget;
class WidgetManager;

class ImageWidget :public WidgetElement
{
	friend class WidgetManager;
	friend class UserWidget;

private:
	struct ImageInfo
	{
		IMAGE* image = nullptr;				// 图片
		IMAGE* scaledImage = nullptr;		// 缩放后的图片
		IMAGE* angleImage = nullptr;		// 旋转后的图片
		int offsetX = 0;					// 图片偏移X
		int offsetY = 0;					// 图片偏移Y
		bool isFill = false;				// 是否填充整个按钮图片
		bool isAngle = false;				// 是否旋转图片
		float angle = 0.0f;					// 图片旋转角度
		bool getImageValid() { return image != nullptr; }
	};

public:
	ImageWidget(UserWidget* parent, Vector2 position, Vector2 size, int zOrder, LPCTSTR className, WidgetAnchor anchor = WidgetAnchor::TopLeft) 
		: WidgetElement(parent, position, size, zOrder, className, anchor) {}
	~ImageWidget();

public:
	void draw() override;                                                                // 绘制
	void update(float delta) override;													 // 更新

	// 设置图片
	void setImage(IMAGE* image)
	{
		imageInfo.image = image;
	}

	// 设置图片偏移
	void setOffset(int x, int y)
	{
		imageInfo.offsetX = x;
		imageInfo.offsetY = y;
	}

	// 设置是否填充整个按钮图片
	void setFill(bool fill)
	{
		imageInfo.isFill = fill;
	}

	// 设置是否旋转图片
	void setCanAngle(bool angle)
	{
		imageInfo.isAngle = angle;
	}

	// 设置图片旋转角度
	void setAngle(float angle)
	{
		imageInfo.angle = angle;
		isAngle = false;				//需要重新旋转图片
		imageInfo.isAngle = true;
	}




private:
	ImageInfo imageInfo;															 // 图片信息
	bool isAngle = false;															 // 是否旋转图片
	IMAGE* tempImage = nullptr;														//临时图片
	IMAGE* showImage = nullptr;														// 显示图片

};

