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

	//����ͼ��
	void destroy()
	{
		if (image)
		{
			//printf("Freeing image\n");
			delete image;
			image = nullptr;
		}
	}

	//����ͼ��
	void setImage(IMAGE* image,bool is_destroy = true)
	{ 
		if (is_destroy)
			destroy();
		this->image = image; 
	}

	//��ȡͼ��
	IMAGE* getImage() { return image; }

	//����֡��
	void setFrameNumber(int frame_num) { this->frame_num = frame_num; }

	//��ȡ֡��
	int getFrameNumber() { return frame_num; }

	//��������
	void setBrightness(float brightness) { this->brightness = brightness; }

	//��ȡ����
	float getBrightness() { return brightness; }


private:
	IMAGE* image = nullptr;
	int frame_num = 0;
	//����
	float brightness = 1.0f;

};




