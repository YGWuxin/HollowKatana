#include "helper.h"
#include "../Game/atlas.h"
#include <graphics.h>	
#include "../Game/Camera.h"
#include "../Game/Vector2.h"
#include <math.h>

#pragma comment (lib,"winmm.lib") 
#pragma comment (lib,"Msimg32.lib") 

void helper::flip_image(IMAGE* src, IMAGE* dst) {
	//获取原图片的宽度和长度
	int w = src->getwidth();
	int h = src->getheight();

	Resize(dst, w, h);	//将原图片宽度和长度设置给目标图片

	//获取图片缓冲
	DWORD* src_buf = GetImageBuffer(src);
	DWORD* dst_buf = GetImageBuffer(dst);

	//进行翻转赋值
	for (int y = 0; y < h; y++)
	{
		for (int x = 0; x < w; x++)
		{
			int idx_src = y * w + x;
			int idx_dst = y * w + (w - x - 1);
			dst_buf[idx_dst] = src_buf[idx_src];
		}
	}

};


//进行图片翻转
void helper::flip_image(IMAGE* src, IMAGE* dst, int num_h) {
	//获取原图片的宽度和长度
	int w = src->getwidth();
	int h = src->getheight();
	int w_frame = w / num_h;

	Resize(dst, w, h);	//将原图片宽度和长度设置给目标图片

	//获取图片缓冲
	DWORD* src_buf = GetImageBuffer(src);
	DWORD* dst_buf = GetImageBuffer(dst);
	
	//进行翻转赋值
	for(int i = 0; i < num_h; i++)
	{
		int x_left = i * w_frame;
		int x_right = (i + 1) * w_frame;
		for (int y = 0; y < h; y++)
		{
			for (int x = x_left; x < x_right; x++)
			{
				int idx_src = y * w + x;
				int idx_dst = y * w + x_right - (x - x_left);
				dst_buf[idx_dst] = src_buf[idx_src];
			}
		}
	}
};


//翻转操作
void helper::flip_atlas(Atlas& src, Atlas& dst) {
	dst.clear();
	for (int i = 0; i < src.get_size(); i++)
	{
		IMAGE* img_flpipped = new IMAGE();
		flip_image(src.get_image(i), img_flpipped);
		dst.add_image(img_flpipped);
	}
};

bool helper::check_image_valid(IMAGE* image)
{
	if (image == nullptr)
		return false;
	return GetImageBuffer(image);
}


void helper::putimage_alpha(int dst_x, int dst_y, IMAGE* img)
{
	int w = img->getwidth();
	int h = img->getheight();

	static BLENDFUNCTION belen_func = { AC_SRC_OVER,0,255,AC_SRC_ALPHA };

	AlphaBlend(GetImageHDC(GetWorkingImage()), dst_x, dst_y, w, h,
		GetImageHDC(img), 0, 0, w, h, belen_func);
}

void helper::putimage_alpha(const Camera& camera, int dst_x, int dst_y, IMAGE* img)
{
	int w = img->getwidth();
	int h = img->getheight();


	Vector2 camera_position = camera.get_position();

	AlphaBlend(GetImageHDC(GetWorkingImage()), dst_x + camera_position.x, dst_y + camera_position.y, w, h,
		GetImageHDC(img), 0, 0, w, h, { AC_SRC_OVER,0,255,AC_SRC_ALPHA });
}


void helper::putimage_ex(IMAGE* img, const Rect* rect_dst, const Rect* rect_src)
{
	static BLENDFUNCTION belen_func = { AC_SRC_OVER,0,255,AC_SRC_ALPHA };

	AlphaBlend(GetImageHDC(GetWorkingImage()), rect_dst->x, rect_dst->y, rect_dst->w, rect_dst->h,
		GetImageHDC(img), rect_src ? rect_src->x : 0, rect_src ? rect_src->y : 0, rect_src ? rect_src->w : img->getwidth(),
		rect_src ? rect_src->h : img->getheight(), belen_func);
}

void helper::putimage_ex(const Camera& camera,IMAGE* img, const Rect* rect_dst, const Rect* rect_src)
{
	static BLENDFUNCTION belen_func = { AC_SRC_OVER,0,255,AC_SRC_ALPHA };
	
	Vector2 camera_position = camera.get_position();

	AlphaBlend(GetImageHDC(GetWorkingImage()), rect_dst->x + camera_position.x, rect_dst->y + camera_position.y, rect_dst->w, rect_dst->h,
		GetImageHDC(img), rect_src ? rect_src->x : 0 , rect_src ? rect_src->y  : 0 ,
		(rect_src || rect_src->w > 0) ? rect_src->w : img->getwidth(), (rect_src || rect_src->h > 0) ? rect_src->h : img->getheight(), belen_func);
}


void helper::sketch_image(IMAGE* src, IMAGE* dst , S_RGB rgb)
{
	int w = src->getwidth();
	int h = src->getheight();
	Resize(dst,w,h);
	DWORD* src_buffer = GetImageBuffer(src);
	DWORD* dst_buffer = GetImageBuffer(dst);
	for (int y = 0; y < h; y++)
	{
		for (int x = 0; x < w; x++)
		{
			int idx = y * w + x;
			dst_buffer[idx] = BGR(RGB(rgb.Red, rgb.Green, rgb.Blue) | (src_buffer[idx] & 0xFF000000));
		}
	}
}


void helper::rotateImage(IMAGE* srcImg, IMAGE* dstImg, double angle)
{
	int srcWidth = srcImg->getwidth();
	int srcHeight = srcImg->getheight();

	//printf("srcWidth = %d, srcHeight = %d\n", srcWidth, srcHeight);

	// 获取源图像中心点
	int centerX = srcWidth / 2;
	int centerY = srcHeight / 2;

	// 标准化角度到 0 到 360 度之间
	angle = fmod(angle, 360.0);
	if (angle < 0) {
		angle += 360.0; // 如果是负值，则加360
	}

	// 角度转换为弧度
	double radian = angle * PI / 180.0;

	// 调整目标图像大小与源图像相同
	Resize(dstImg, srcWidth, srcHeight);
		

	// 获取源和目标图像的缓冲区
	DWORD* src_buf = GetImageBuffer(srcImg);
	DWORD* dst_buf = GetImageBuffer(dstImg);

	// 遍历目标图像的每个像素点
	for (int x = 0; x < srcWidth; x++) {
		for (int y = 0; y < srcHeight; y++) {
			// 计算目标图像的像素相对于中心的偏移
			int offsetX = x - centerX;
			int offsetY = y - centerY;

			// 使用旋转矩阵计算原始图像中的位置
			int srcX = static_cast<int>(offsetX * cos(radian) + offsetY * sin(radian)) + centerX;
			int srcY = static_cast<int>(-offsetX * sin(radian) + offsetY * cos(radian)) + centerY;

			// 确保源图像中的坐标在合法范围内
			if (srcX >= 0 && srcX < srcWidth && srcY >= 0 && srcY < srcHeight) {
				// 将源图像的颜色值赋给目标图像的对应像素
				dst_buf[y * srcWidth + x] = src_buf[srcY * srcWidth + srcX];
			}
			else {
				// 超出边界的部分设为黑色
				dst_buf[y * srcWidth + x] = RGB(0, 0, 0);
			}
		}
	}
}


void helper::scaleImage(IMAGE* srcImg, IMAGE* dstImg, float scale)
{
	int srcWidth = srcImg->getwidth();
	int srcHeight = srcImg->getheight();

	// 计算目标图像的宽高
	int dstWidth = static_cast<int>(srcWidth * scale);
	int dstHeight = static_cast<int>(srcHeight * scale);

	// 调整目标图像大小
	Resize(dstImg, dstWidth, dstHeight);

	// 获取源和目标图像的缓冲区
	DWORD* src_buf = GetImageBuffer(srcImg);
	DWORD* dst_buf = GetImageBuffer(dstImg);

	// 遍历目标图像的每个像素点
	for (int x = 0; x < dstWidth; x++) {
		for (int y = 0; y < dstHeight; y++) {
			// 计算对应源图像中的位置
			int srcX = static_cast<int>(x / scale);
			int srcY = static_cast<int>(y / scale);

			// 确保源图像中的坐标在合法范围内
			if (srcX >= 0 && srcX < srcWidth && srcY >= 0 && srcY < srcHeight) {
				// 将源图像的颜色值赋给目标图像的对应像素
				dst_buf[y * dstWidth + x] = src_buf[srcY * srcWidth + srcX];
			}
			else {
				// 超出边界的部分设为黑色
				dst_buf[y * dstWidth + x] = RGB(0, 0, 0);
			}
		}
	}
}

void helper::scaleImage(IMAGE* srcImg, IMAGE* dstImg, int newWidth, int newHeight) {
	int srcWidth = srcImg->getwidth();
	int srcHeight = srcImg->getheight();

	// 设置目标图像的大小
	Resize(dstImg, newWidth, newHeight);

	// 获取源图片和目标图片的像素缓冲区
	DWORD* srcBuf = GetImageBuffer(srcImg);
	DWORD* dstBuf = GetImageBuffer(dstImg);

	// 按比例缩放图像
	for (int y = 0; y < newHeight; y++) {
		for (int x = 0; x < newWidth; x++) {
			// 计算缩放后对应的源图像坐标
			int srcX = x * srcWidth / newWidth;
			int srcY = y * srcHeight / newHeight;

			// 获取源图像的像素并赋值给目标图像
			dstBuf[y * newWidth + x] = srcBuf[srcY * srcWidth + srcX];
		}
	}
}


void helper::adjustImageBrightness(IMAGE* img, float brightness)
{
	int w = img->getwidth();
	int h = img->getheight();

	// 获取图像的缓冲区
	DWORD* buf = GetImageBuffer(img);

	float Decrease = 1.0;
	if (brightness <= 1.0)
		Decrease = brightness;

	// 遍历图像的每个像素并调整亮度
	for (int y = 0; y < h; y++) {
		for (int x = 0; x < w; x++) {
			int idx = y * w + x;
			DWORD color = buf[idx];

			// 提取 R, G, B 和 Alpha 通道
			BYTE r = GetRValue(color);
			BYTE g = GetGValue(color);
			BYTE b = GetBValue(color);
			BYTE alpha = (BYTE)((color >> 24) & 0xFF); // 保留 Alpha 通道

			// 调整 R, G, B 的亮度
			r = (BYTE)(r * Decrease);
			g = (BYTE)(g * Decrease);
			b = (BYTE)(b * Decrease);

			// 重新组合 Alpha 和 RGB 并写回缓冲区
			buf[idx] = (alpha << 24) | RGB(r, g, b);

		}
	}
}


void helper::adjustImageBrightness(IMAGE* src, IMAGE* dst, float brightness)
{
	int w = src->getwidth();
	int h = src->getheight();

	// 获取图像的缓冲区
	DWORD* src_buf = GetImageBuffer(src);

	// 调整目标图像大小与源图像相同
	Resize(dst, w, h);
	DWORD* dst_buf = GetImageBuffer(dst);

	float Decrease = 1.0;
	if (brightness <= 1.0)
		Decrease = brightness;

	// 遍历图像的每个像素并调整亮度
	for (int y = 0; y < h; y++) {
		for (int x = 0; x < w; x++) {
			int idx = y * w + x;
			DWORD color = src_buf[idx];

			// 提取 R, G, B 和 Alpha 通道
			BYTE r = GetRValue(color);
			BYTE g = GetGValue(color);
			BYTE b = GetBValue(color);
			BYTE alpha = (BYTE)((color >> 24) & 0xFF); // 保留 Alpha 通道

			// 调整 R, G, B 的亮度
			r = (BYTE)(r * Decrease);
			g = (BYTE)(g * Decrease);
			b = (BYTE)(b * Decrease);

			// 重新组合 Alpha 和 RGB 并写回缓冲区
			dst_buf[idx] = (alpha << 24) | RGB(r, g, b);

		}
	}
}


std::wstring helper::stringToWstring(const std::string& str)
{
	std::wstring_convert<std::codecvt_utf8<wchar_t>> converter;
	return converter.from_bytes(str);
}

//全屏亮度调节后处理
void helper::post_process_full_screen(float brightness)
{
	DWORD* buffer = GetImageBuffer();
	int w = getwidth();
	int h = getheight();

	float Decrease = 1.0;
	if (brightness <= 1.0)
		Decrease = brightness;

	// 遍历图像的每个像素并调整亮度
	for (int y = 0; y < h; y++) {
		for (int x = 0; x < w; x++) {
			int idx = y * w + x;
			DWORD color = buffer[idx];

			// 提取 R, G, B 和 Alpha 通道
			BYTE r = GetRValue(color);
			BYTE g = GetGValue(color);
			BYTE b = GetBValue(color);
			BYTE alpha = (BYTE)((color >> 24) & 0xFF); // 保留 Alpha 通道

			// 调整 R, G, B 的亮度
			r = (BYTE)(r * Decrease);
			g = (BYTE)(g * Decrease);
			b = (BYTE)(b * Decrease);

			// 重新组合 Alpha 和 RGB 并写回缓冲区
			buffer[idx] = (alpha << 24) | RGB(r, g, b);

		}
	}
}