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
		IMAGE* image = nullptr;				// ͼƬ
		IMAGE* scaledImage = nullptr;		// ���ź��ͼƬ
		IMAGE* angleImage = nullptr;		// ��ת���ͼƬ
		int offsetX = 0;					// ͼƬƫ��X
		int offsetY = 0;					// ͼƬƫ��Y
		bool isFill = false;				// �Ƿ����������ťͼƬ
		bool isAngle = false;				// �Ƿ���תͼƬ
		float angle = 0.0f;					// ͼƬ��ת�Ƕ�
		bool getImageValid() { return image != nullptr; }
	};

public:
	ImageWidget(UserWidget* parent, Vector2 position, Vector2 size, int zOrder, LPCTSTR className, WidgetAnchor anchor = WidgetAnchor::TopLeft) 
		: WidgetElement(parent, position, size, zOrder, className, anchor) {}
	~ImageWidget();

public:
	void draw() override;                                                                // ����
	void update(float delta) override;													 // ����

	// ����ͼƬ
	void setImage(IMAGE* image)
	{
		imageInfo.image = image;
	}

	// ����ͼƬƫ��
	void setOffset(int x, int y)
	{
		imageInfo.offsetX = x;
		imageInfo.offsetY = y;
	}

	// �����Ƿ����������ťͼƬ
	void setFill(bool fill)
	{
		imageInfo.isFill = fill;
	}

	// �����Ƿ���תͼƬ
	void setCanAngle(bool angle)
	{
		imageInfo.isAngle = angle;
	}

	// ����ͼƬ��ת�Ƕ�
	void setAngle(float angle)
	{
		imageInfo.angle = angle;
		isAngle = false;				//��Ҫ������תͼƬ
		imageInfo.isAngle = true;
	}




private:
	ImageInfo imageInfo;															 // ͼƬ��Ϣ
	bool isAngle = false;															 // �Ƿ���תͼƬ
	IMAGE* tempImage = nullptr;														//��ʱͼƬ
	IMAGE* showImage = nullptr;														// ��ʾͼƬ

};

