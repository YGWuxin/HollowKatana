#pragma once
#include "UserWidget.h"

class TextButtonWidget;
class TextWidget;
class SliderBarWidget;

class MainMenuWidget :public UserWidget
{
public:
	MainMenuWidget(UserWidget* parent, int zOrder);
	~MainMenuWidget() = default;


public:
	TextButtonWidget* PlayButton = nullptr;
	TextButtonWidget* OptionsButton = nullptr;
	TextButtonWidget* KeyButton = nullptr;
	TextButtonWidget* ExitButton = nullptr;

};

class SelectBossMenuWidget :public UserWidget
{
public:
	SelectBossMenuWidget(UserWidget* parent, int zOrder);
	~SelectBossMenuWidget() = default;


public:
	TextButtonWidget* ChallengeButton = nullptr;
	TextButtonWidget* BackButton = nullptr;

};

class OptionsMenuWidget :public UserWidget
{
public:
	OptionsMenuWidget(UserWidget* parent, int zOrder);
	~OptionsMenuWidget() = default;


public:
	//应用按钮
	TextButtonWidget* ApplyButton = nullptr;
	//音效设置按钮
	TextButtonWidget* BackButton = nullptr;

	//音乐滑动条
	SliderBarWidget* MusicSlider = nullptr;

	//音效滑动条
	SliderBarWidget *SoundSlider = nullptr;

	TextWidget* MusicText = nullptr;
	TextWidget* SoundText = nullptr;

	int MusicVolume = 0;
	int SoundVolume = 0;

};


class KeyMenuWidget :public UserWidget
{
public:
	KeyMenuWidget(UserWidget* parent, int zOrder);
	~KeyMenuWidget() = default;


public:
	TextButtonWidget* BackButton = nullptr;

};


