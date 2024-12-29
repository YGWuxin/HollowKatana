#pragma once
#include <graphics.h>	


class ImageInfo
{
public:
	ImageInfo(IMAGE* image, int frame_num)
	{
		this->image = image;
		this->frame_num = frame_num;
	}

	ImageInfo() = default;


	~ImageInfo()
	{
		destroy();
	}

	//销毁图像
	void destroy()
	{
		if (image)
		{
			//printf("Freeing image\n");
			delete image;
			image = nullptr;
		}
	}

	//设置图像
	void setImage(IMAGE* image,bool is_destroy = true)
	{ 
		if (is_destroy)
			destroy();
		this->image = image; 
	}

	//获取图像
	IMAGE* getImage() { return image; }

	//设置帧数
	void setFrameNumber(int frame_num) { this->frame_num = frame_num; }

	//获取帧数
	int getFrameNumber() { return frame_num; }

	//设置亮度
	void setBrightness(float brightness) { this->brightness = brightness; }

	//获取亮度
	float getBrightness() { return brightness; }


private:
	IMAGE* image = nullptr;
	int frame_num = 0;
	//亮度
	float brightness = 1.0f;

};




