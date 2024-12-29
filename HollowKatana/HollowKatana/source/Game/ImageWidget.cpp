#include "ImageWidget.h"


ImageWidget::~ImageWidget()
{
	//清除缩放后的图片
	if (imageInfo.scaledImage)
		delete imageInfo.scaledImage;

	//清除旋转后的图片
	if (imageInfo.angleImage)
		delete imageInfo.angleImage;

}

void ImageWidget::draw()
{
	if (imageInfo.getImageValid())				//如果图片有效，则绘制图片
	{
		showImage = imageInfo.image;

		//如果图片发生变化，则重新生成旋转后的图片
		if (imageInfo.isFill)
		{
			if (imageInfo.scaledImage == nullptr)
				imageInfo.scaledImage = new IMAGE();
			if (tempImage != imageInfo.image)
				helper::scaleImage(showImage, imageInfo.scaledImage, size.x, size.y);		//缩放图片
			showImage = imageInfo.scaledImage;
		}
		else
		{
			//清除图片
			if (imageInfo.scaledImage)
				delete imageInfo.scaledImage;
			imageInfo.scaledImage = nullptr;
		}

		//如果图片发生变化，则重新生成旋转后的图片
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
			//清除图片
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
