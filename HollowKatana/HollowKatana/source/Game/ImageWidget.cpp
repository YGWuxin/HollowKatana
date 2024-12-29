#include "ImageWidget.h"


ImageWidget::~ImageWidget()
{
	//������ź��ͼƬ
	if (imageInfo.scaledImage)
		delete imageInfo.scaledImage;

	//�����ת���ͼƬ
	if (imageInfo.angleImage)
		delete imageInfo.angleImage;

}

void ImageWidget::draw()
{
	if (imageInfo.getImageValid())				//���ͼƬ��Ч�������ͼƬ
	{
		showImage = imageInfo.image;

		//���ͼƬ�����仯��������������ת���ͼƬ
		if (imageInfo.isFill)
		{
			if (imageInfo.scaledImage == nullptr)
				imageInfo.scaledImage = new IMAGE();
			if (tempImage != imageInfo.image)
				helper::scaleImage(showImage, imageInfo.scaledImage, size.x, size.y);		//����ͼƬ
			showImage = imageInfo.scaledImage;
		}
		else
		{
			//���ͼƬ
			if (imageInfo.scaledImage)
				delete imageInfo.scaledImage;
			imageInfo.scaledImage = nullptr;
		}

		//���ͼƬ�����仯��������������ת���ͼƬ
		if (imageInfo.isAngle)
		{
			if (imageInfo.angleImage == nullptr)
				imageInfo.angleImage = new IMAGE();
			if (tempImage != imageInfo.image || !isAngle)
			{
				helper::rotateImage(showImage, imageInfo.angleImage, imageInfo.angle);
				isAngle = true;
			}
			showImage = imageInfo.angleImage;
		}
		else
		{
			//���ͼƬ
			if (imageInfo.angleImage)
				delete imageInfo.angleImage;
			imageInfo.angleImage = nullptr;
		}

		helper::putimage_alpha(position.x + imageInfo.offsetX, position.y + imageInfo.offsetY, showImage);

		if(tempImage != imageInfo.image)
			tempImage = imageInfo.image;

	}
	
	WidgetElement::draw();
}


void ImageWidget::update(float delta)
{
	WidgetElement::update(delta);
}
