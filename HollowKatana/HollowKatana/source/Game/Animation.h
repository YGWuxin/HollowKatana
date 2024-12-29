#pragma once

#include "../Utils/Timer.h"
#include "../Utils/helper.h"
#include "../Game/Vector2.h"
#include <vector>
#include <functional>
#include "atlas.h"
#include <cstdio>
#include "Camera.h"
#include "../Parameter/GlobeGameParameters.h"
#include "ImageInfo.h"
#include <unordered_map>

using namespace std;

class Animation
{
public:
	Animation() 
	{
		timer.set_one_shot(false);
		timer.set_callback([&]() 
			{
				idx_frame++;
				if (is_crop_loop && is_loop)
				{
					if (idx_frame >= crop_end_frame)
						idx_frame = crop_start_frame;
				}
				else
				{
					if (idx_frame >= frame_list.size())
					{
						idx_frame = is_loop ? 0 : frame_list.size() - 1;
						if (!is_loop && on_finished)
							on_finished();
						//printf(" 执行完一次动画\r\n");
						if(crop_start_frame != 0 && crop_end_frame!= 0)
							is_crop_loop = true;
					}
				}
				if (frame_event[idx_frame])
				{
					frame_event[idx_frame]();		//执行帧事件
				}
			});
	};

	~Animation() = default;


	inline void reset()
	{
		timer.restart();
		idx_frame = 0;
		resume_animation();
		is_crop_loop = false;
	}

	inline int get_frame_index() const
	{
		return idx_frame;
	}

	inline void set_frame_index(int idx)
	{
		if (idx >= 0 && idx < frame_list.size())
			idx_frame = idx;
	}

	inline void set_anchor_mode(AnchorMode mode)
	{
		anchor_mode = mode;
	}

	inline void set_loop(bool val)
	{
		this->is_loop = val;
	}

	inline void set_interval(float interval)
	{
		timer.set_wait_time(interval);
	}

	inline void set_on_finished_callback(function<void()> on_finished)
	{
		this->on_finished = on_finished;
	}

	inline ImageInfo* get_current_frame_image_info()
	{
		if (frame_list.empty())
			return nullptr;
		const Frame& frame = frame_list[idx_frame];
		return frame.image_info;
	}


	inline Rect get_current_frame_rect_src()
	{
		if (frame_list.empty())
			return { 0,0,0,0 };
		const Frame& frame = frame_list[idx_frame];
		return frame.rect_src;
	}


	inline void add_animation(ImageInfo* image_info)
	{
		if (!frame_list.empty())
			return;
		if (image_info == nullptr)
			return;
		IMAGE* image = image_info->getImage();
		int num_h = image_info->getFrameNumber();
		if (image == nullptr || num_h == 0)
			return;
		int w = image->getwidth();
		int h = image->getheight();
		int w_frame = w / num_h;
		for (int i = 0; i < num_h; i++)
		{
			Rect rect_src;
			rect_src.x = i * w_frame;
			rect_src.y = 0;
			rect_src.w = w_frame;
			rect_src.h = h;

			frame_list.emplace_back(image_info, rect_src);
		}
		animation_type = AnimationType::SequenceImage;
		//printf("添加完毕:%d\r\n", frame_list[0].rect_src.h);
	}

	inline void add_animation(Atlas* atlas)
	{
		if (!frame_list.empty())
			return;
		if (atlas == nullptr)
		{
			printf("atlas为空指针\r\n");
			return;
		}
		int w = 0;
		int h = 0;
		for (int i = 0; i < atlas->get_size(); i++)
		{
			IMAGE* image = atlas->get_image(i);
			if(image == nullptr)
				continue;
			w = image->getwidth();
			h = image->getheight();
			Rect rect_src;
			rect_src.w = w, rect_src.h = h;
			rect_src.x = 0; rect_src.y = 0;
			frame_list.emplace_back(atlas->get_image_info(i), rect_src);
		}
		animation_type = AnimationType::Atlas;
	}

	inline void clear_animation()
	{
		if (frame_list.empty())
			return;
		frame_list.clear();
		animation_type = AnimationType::None;
	}

	inline void on_update(float delta)
	{
		if (paused)
			return;
		timer.on_update(delta);
		//printf(" 执行中\r\n");
	}


	inline void pause_animation()
	{
		paused = true;
	}

	inline void resume_animation()
	{
		paused = false;
	}

	inline void add_frame_event(int frame_index, function<void()> func)
	{
		frame_event[frame_index] = func;
	}

	inline void remove_frame_event(int frame_index)
	{
		frame_event.erase(frame_index);
	}


	inline void set_crop_loop(int start_frame, int end_frame)
	{
		if (start_frame >= end_frame || start_frame < 0 || end_frame >= frame_list.size())
			return;
		crop_start_frame = start_frame;
		crop_end_frame = end_frame;
	}


private:
	struct Frame
	{
		Rect rect_src;  
		ImageInfo* image_info = nullptr;
		Frame() = default;
		Frame(ImageInfo* image_info, const Rect& rect_src)
			: image_info(image_info), rect_src(rect_src){}

		~Frame() = default;
	};


private:
	Timer timer;
	bool is_loop = true;
	size_t idx_frame = 0;
	vector<Frame> frame_list;
	function<void()> on_finished;
	AnchorMode anchor_mode = AnchorMode::Centered;
	bool paused = false;			//是否暂停

	AnimationType animation_type = AnimationType::None;

	unordered_map<int, function<void()>> frame_event;			//帧事件

	//是否裁剪循环
	bool is_crop_loop = false;
	//裁剪起始帧
	int crop_start_frame = 0;
	//裁剪结束帧
	int crop_end_frame = 0;

};



