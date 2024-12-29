#include "helper.h"
#include "../Game/atlas.h"
#include <graphics.h>	
#include "../Game/Camera.h"
#include "../Game/Vector2.h"
#include <math.h>

#pragma comment (lib,"winmm.lib") 
#pragma comment (lib,"Msimg32.lib") 

void helper::flip_image(IMAGE* src, IMAGE* dst) {
	//��ȡԭͼƬ�Ŀ�Ⱥͳ���
	int w = src->getwidth();
	int h = src->getheight();

	Resize(dst, w, h);	//��ԭͼƬ��Ⱥͳ������ø�Ŀ��ͼƬ

	//��ȡͼƬ����
	DWORD* src_buf = GetImageBuffer(src);
	DWORD* dst_buf = GetImageBuffer(dst);

	//���з�ת��ֵ
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


//����ͼƬ��ת
void helper::flip_image(IMAGE* src, IMAGE* dst, int num_h) {
	//��ȡԭͼƬ�Ŀ�Ⱥͳ���
	int w = src->getwidth();
	int h = src->getheight();
	int w_frame = w / num_h;

	Resize(dst, w, h);	//��ԭͼƬ��Ⱥͳ������ø�Ŀ��ͼƬ

	//��ȡͼƬ����
	DWORD* src_buf = GetImageBuffer(src);
	DWORD* dst_buf = GetImageBuffer(dst);
	
	//���з�ת��ֵ
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


//��ת����
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

	// ��ȡԴͼ�����ĵ�
	int centerX = srcWidth / 2;
	int centerY = srcHeight / 2;

	// ��׼���Ƕȵ� 0 �� 360 ��֮��
	angle = fmod(angle, 360.0);
	if (angle < 0) {
		angle += 360.0; // ����Ǹ�ֵ�����360
	}

	// �Ƕ�ת��Ϊ����
	double radian = angle * PI / 180.0;

	// ����Ŀ��ͼ���С��Դͼ����ͬ
	Resize(dstImg, srcWidth, srcHeight);
		

	// ��ȡԴ��Ŀ��ͼ��Ļ�����
	DWORD* src_buf = GetImageBuffer(srcImg);
	DWORD* dst_buf = GetImageBuffer(dstImg);

	// ����Ŀ��ͼ���ÿ�����ص�
	for (int x = 0; x < srcWidth; x++) {
		for (int y = 0; y < srcHeight; y++) {
			// ����Ŀ��ͼ���������������ĵ�ƫ��
			int offsetX = x - centerX;
			int offsetY = y - centerY;

			// ʹ����ת�������ԭʼͼ���е�λ��
			int srcX = static_cast<int>(offsetX * cos(radian) + offsetY * sin(radian)) + centerX;
			int srcY = static_cast<int>(-offsetX * sin(radian) + offsetY * cos(radian)) + centerY;

			// ȷ��Դͼ���е������ںϷ���Χ��
			if (srcX >= 0 && srcX < srcWidth && srcY >= 0 && srcY < srcHeight) {
				// ��Դͼ�����ɫֵ����Ŀ��ͼ��Ķ�Ӧ����
				dst_buf[y * srcWidth + x] = src_buf[srcY * srcWidth + srcX];
			}
			else {
				// �����߽�Ĳ�����Ϊ��ɫ
				dst_buf[y * srcWidth + x] = RGB(0, 0, 0);
			}
		}
	}
}


void helper::scaleImage(IMAGE* srcImg, IMAGE* dstImg, float scale)
{
	int srcWidth = srcImg->getwidth();
	int srcHeight = srcImg->getheight();

	// ����Ŀ��ͼ��Ŀ��
	int dstWidth = static_cast<int>(srcWidth * scale);
	int dstHeight = static_cast<int>(srcHeight * scale);

	// ����Ŀ��ͼ���С
	Resize(dstImg, dstWidth, dstHeight);

	// ��ȡԴ��Ŀ��ͼ��Ļ�����
	DWORD* src_buf = GetImageBuffer(srcImg);
	DWORD* dst_buf = GetImageBuffer(dstImg);

	// ����Ŀ��ͼ���ÿ�����ص�
	for (int x = 0; x < dstWidth; x++) {
		for (int y = 0; y < dstHeight; y++) {
			// �����ӦԴͼ���е�λ��
			int srcX = static_cast<int>(x / scale);
			int srcY = static_cast<int>(y / scale);

			// ȷ��Դͼ���е������ںϷ���Χ��
			if (srcX >= 0 && srcX < srcWidth && srcY >= 0 && srcY < srcHeight) {
				// ��Դͼ�����ɫֵ����Ŀ��ͼ��Ķ�Ӧ����
				dst_buf[y * dstWidth + x] = src_buf[srcY * srcWidth + srcX];
			}
			else {
				// �����߽�Ĳ�����Ϊ��ɫ
				dst_buf[y * dstWidth + x] = RGB(0, 0, 0);
			}
		}
	}
}

void helper::scaleImage(IMAGE* srcImg, IMAGE* dstImg, int newWidth, int newHeight) {
	int srcWidth = srcImg->getwidth();
	int srcHeight = srcImg->getheight();

	// ����Ŀ��ͼ��Ĵ�С
	Resize(dstImg, newWidth, newHeight);

	// ��ȡԴͼƬ��Ŀ��ͼƬ�����ػ�����
	DWORD* srcBuf = GetImageBuffer(srcImg);
	DWORD* dstBuf = GetImageBuffer(dstImg);

	// ����������ͼ��
	for (int y = 0; y < newHeight; y++) {
		for (int x = 0; x < newWidth; x++) {
			// �������ź��Ӧ��Դͼ������
			int srcX = x * srcWidth / newWidth;
			int srcY = y * srcHeight / newHeight;

			// ��ȡԴͼ������ز���ֵ��Ŀ��ͼ��
			dstBuf[y * newWidth + x] = srcBuf[srcY * srcWidth + srcX];
		}
	}
}


void helper::adjustImageBrightness(IMAGE* img, float brightness)
{
	int w = img->getwidth();
	int h = img->getheight();

	// ��ȡͼ��Ļ�����
	DWORD* buf = GetImageBuffer(img);

	float Decrease = 1.0;
	if (brightness <= 1.0)
		Decrease = brightness;

	// ����ͼ���ÿ�����ز���������
	for (int y = 0; y < h; y++) {
		for (int x = 0; x < w; x++) {
			int idx = y * w + x;
			DWORD color = buf[idx];

			// ��ȡ R, G, B �� Alpha ͨ��
			BYTE r = GetRValue(color);
			BYTE g = GetGValue(color);
			BYTE b = GetBValue(color);
			BYTE alpha = (BYTE)((color >> 24) & 0xFF); // ���� Alpha ͨ��

			// ���� R, G, B ������
			r = (BYTE)(r * Decrease);
			g = (BYTE)(g * Decrease);
			b = (BYTE)(b * Decrease);

			// ������� Alpha �� RGB ��д�ػ�����
			buf[idx] = (alpha << 24) | RGB(r, g, b);

		}
	}
}


void helper::adjustImageBrightness(IMAGE* src, IMAGE* dst, float brightness)
{
	int w = src->getwidth();
	int h = src->getheight();

	// ��ȡͼ��Ļ�����
	DWORD* src_buf = GetImageBuffer(src);

	// ����Ŀ��ͼ���С��Դͼ����ͬ
	Resize(dst, w, h);
	DWORD* dst_buf = GetImageBuffer(dst);

	float Decrease = 1.0;
	if (brightness <= 1.0)
		Decrease = brightness;

	// ����ͼ���ÿ�����ز���������
	for (int y = 0; y < h; y++) {
		for (int x = 0; x < w; x++) {
			int idx = y * w + x;
			DWORD color = src_buf[idx];

			// ��ȡ R, G, B �� Alpha ͨ��
			BYTE r = GetRValue(color);
			BYTE g = GetGValue(color);
			BYTE b = GetBValue(color);
			BYTE alpha = (BYTE)((color >> 24) & 0xFF); // ���� Alpha ͨ��

			// ���� R, G, B ������
			r = (BYTE)(r * Decrease);
			g = (BYTE)(g * Decrease);
			b = (BYTE)(b * Decrease);

			// ������� Alpha �� RGB ��д�ػ�����
			dst_buf[idx] = (alpha << 24) | RGB(r, g, b);

		}
	}
}


std::wstring helper::stringToWstring(const std::string& str)
{
	std::wstring_convert<std::codecvt_utf8<wchar_t>> converter;
	return converter.from_bytes(str);
}

//ȫ�����ȵ��ں���
void helper::post_process_full_screen(float brightness)
{
	DWORD* buffer = GetImageBuffer();
	int w = getwidth();
	int h = getheight();

	float Decrease = 1.0;
	if (brightness <= 1.0)
		Decrease = brightness;

	// ����ͼ���ÿ�����ز���������
	for (int y = 0; y < h; y++) {
		for (int x = 0; x < w; x++) {
			int idx = y * w + x;
			DWORD color = buffer[idx];

			// ��ȡ R, G, B �� Alpha ͨ��
			BYTE r = GetRValue(color);
			BYTE g = GetGValue(color);
			BYTE b = GetBValue(color);
			BYTE alpha = (BYTE)((color >> 24) & 0xFF); // ���� Alpha ͨ��

			// ���� R, G, B ������
			r = (BYTE)(r * Decrease);
			g = (BYTE)(g * Decrease);
			b = (BYTE)(b * Decrease);

			// ������� Alpha �� RGB ��д�ػ�����
			buffer[idx] = (alpha << 24) | RGB(r, g, b);

		}
	}
}