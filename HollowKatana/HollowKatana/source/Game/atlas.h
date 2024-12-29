#pragma once

#include <vector>
#include <graphics.h>	
#include "../Utils/helper.h"
#include "ImageInfo.h"

using namespace std;

class Atlas
{
public:
	Atlas() = default;
	~Atlas() { clear();  }

	void load_from_file(LPCTSTR path, int num) {

		clear();
		resize(num);

		TCHAR path_file[256];
		for (int i = 0; i < num; i++)
		{
			_stprintf_s(path_file, path, i + 1);
			//loadimage(&image_list[i], path_file);
			IMAGE* src_image = new IMAGE;
			loadimage(src_image, path_file);
			image_list[i]->setImage(src_image);
		}
	};


	void load_from_file(LPCTSTR path, int num, float scale) {

		clear();
		resize(num);

		TCHAR path_file[256];
		for (int i = 0; i < num; i++)
		{
			_stprintf_s(path_file, path, i + 1);
			IMAGE* src_image = new IMAGE;
			loadimage(src_image, path_file);

			if (scale == 1.0)
			{
				image_list[i]->setImage(src_image);
			}
			else
			{
				IMAGE* dst_image = new IMAGE;
				helper::scaleImage(src_image, dst_image, scale);
				delete src_image;
				image_list[i]->setImage(dst_image);
			}
		}
	};


	void clear() {
		for (int i = 0; i < image_list.size(); i++)
		{
			if (image_list[i]->getImage())
				delete image_list[i];
		}
		image_list.clear();
	};


	void resize(int num){
		image_list.resize(num);
		for (int i = 0; i < num; i++)
		{
			ImageInfo* info = new ImageInfo();
			image_list[i] = info;
		}
	}

	int get_size() {
		return image_list.size();
	};

	IMAGE* get_image(int idx) {
		if (idx < 0 || idx >= image_list.size())
			return nullptr;
		return image_list[idx]->getImage();
	};

	ImageInfo* get_image_info(int idx) {
		if (idx < 0 || idx >= image_list.size())
			return nullptr;
		return image_list[idx];
	};

	void add_image(IMAGE* img) {
		ImageInfo* info = new ImageInfo(img,0);
		image_list.push_back(info);
	};


private:
	//vector<IMAGE>	image_list;		//图片列表
	vector<ImageInfo*>	image_list;		//图片列表
};



