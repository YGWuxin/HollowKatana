#pragma once
#include "UserWidget.h"
#include <unordered_map>
#include <string>

using namespace std;

class MainMenuWidget;
class TestWidget;

class MenuWidget : public UserWidget
{
public:
	MenuWidget(UserWidget* parent, int zOrder);
	~MenuWidget() = default;

	void draw() override;

	void update(float delta) override;

private:
	void setCurrentWidget(UserWidget* widget);

	void switchToNextWidget(string name);

	void addWidget(string name,UserWidget* widget)
	{
		widgets_map.insert(make_pair(name, widget));
	}

	UserWidget* findWidget(string name)
	{
		const auto& itor = widgets_map.find(name);
		if (itor == widgets_map.end())
			return nullptr;

		return itor->second;
	}


private:
	UserWidget* current_widget = nullptr;
	UserWidget* temp_widget = nullptr;
	
	//当前亮度
	float current_brightness = 1.0f;
	//目标亮度
	float target_brightness = 1.0f;

	bool is_fading = false;					//是否正在淡出
	float fade_speed = 30;					//淡出速度

	unordered_map<string, UserWidget*>   widgets_map;


};

