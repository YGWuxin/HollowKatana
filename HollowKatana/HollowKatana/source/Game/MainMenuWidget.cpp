#include "MainMenuWidget.h"
#include "TextButtonWidget.h"
#include "ImageWidget.h"
#include "../Parameter/GlobeGameParameters.h"
#include "ResourcesManager.h"
#include "SceneManager.h"
#include "WidgetManager.h"
#include "AudioManager.h"
#include "SliderBarWidget.h"
#include "TextWidget.h"
#include <string>
#include "SceneManager.h"
#include "JsonData.h"

MainMenuWidget::MainMenuWidget(UserWidget* parent, int zOrder): UserWidget(parent, zOrder)
{
	//TextButtonWidget* main_widget = WidgetManager::GetInstance().createUserWidgetInstance<TextButtonWidget>(this, { WIN_WIDTH / 2,WIN_HEIGHT / 2 + 50 }, { 200,50 }, 2, _T("PlayButton"), WidgetAnchor::MiddleCenter);

	//����ͼƬ
	IMAGE* img_bg = ResourcesManager::GetInstance().find_image("img_menu_bg")->getImage();
	IMAGE* img_bg_hover= ResourcesManager::GetInstance().find_image("img_btn_bg_1")->getImage();
	IMAGE* img_bg_pressed = ResourcesManager::GetInstance().find_image("img_btn_bg_2")->getImage();

	//���ñ���
	ImageWidget *bg = new ImageWidget(this, { WIN_WIDTH / 2,WIN_HEIGHT / 2 }, { WIN_WIDTH,WIN_HEIGHT }, 0,_T("bg"),WidgetAnchor::MiddleCenter);
	bg->setImage(img_bg);


	//��ʼ��ť
	PlayButton = new TextButtonWidget(this, { WIN_WIDTH / 2,WIN_HEIGHT / 2 + 50 }, { 200,50 }, 2, _T("PlayButton"), WidgetAnchor::MiddleCenter);
	PlayButton->setText(_T("��ʼ��Ϸ"));
	PlayButton->setFontSize(30);
	PlayButton->setFont(_T("����"));
	PlayButton->setIsShowBackground(false, ButtonWidget::ButtonState::Default);
	PlayButton->setTextColor(RGB(0, 0, 0), ButtonWidget::ButtonState::Hover);
	PlayButton->setTextColor(RGB(49, 49, 49), ButtonWidget::ButtonState::Press);
	PlayButton->setBGImage(img_bg_hover, ButtonWidget::ButtonState::Hover);
	PlayButton->setBGImage(img_bg_pressed, ButtonWidget::ButtonState::Press);
	PlayButton->setImageOffset(-75, -4);
	PlayButton->setSoundPath("res/audio/ui/Hovered.mp3", ButtonWidget::ButtonState::Hover);
	PlayButton->setSoundPath("res/audio/ui/Click.mp3", ButtonWidget::ButtonState::Press);

	//Options��ť
	OptionsButton = new TextButtonWidget(this, { WIN_WIDTH / 2,WIN_HEIGHT / 2 + 120 }, { 200,50 }, 2, _T("OptionsButton"), WidgetAnchor::MiddleCenter);
	OptionsButton->setText(_T("����"));
	OptionsButton->setFontSize(30);
	OptionsButton->setFont(_T("����"));
	OptionsButton->setIsShowBackground(false, ButtonWidget::ButtonState::Default);
	OptionsButton->setTextColor(RGB(0, 0, 0), ButtonWidget::ButtonState::Hover);
	OptionsButton->setTextColor(RGB(49, 49, 49), ButtonWidget::ButtonState::Press);
	OptionsButton->setBGImage(img_bg_hover, ButtonWidget::ButtonState::Hover);
	OptionsButton->setBGImage(img_bg_pressed, ButtonWidget::ButtonState::Press);
	OptionsButton->setImageOffset(-75, -4);
	OptionsButton->setSoundPath("res/audio/ui/Hovered.mp3", ButtonWidget::ButtonState::Hover);
	OptionsButton->setSoundPath("res/audio/ui/Click.mp3", ButtonWidget::ButtonState::Press);

	//Key��ť
	KeyButton = new TextButtonWidget(this, { WIN_WIDTH / 2,WIN_HEIGHT / 2 + 190 }, { 200,50 }, 2, _T("KeyButton"), WidgetAnchor::MiddleCenter);
	KeyButton->setText(_T("��λ˵��"));
	KeyButton->setFontSize(30);
	KeyButton->setFont(_T("����"));
	KeyButton->setIsShowBackground(false, ButtonWidget::ButtonState::Default);
	KeyButton->setTextColor(RGB(0, 0, 0), ButtonWidget::ButtonState::Hover);
	KeyButton->setTextColor(RGB(49, 49, 49), ButtonWidget::ButtonState::Press);
	KeyButton->setBGImage(img_bg_hover, ButtonWidget::ButtonState::Hover);
	KeyButton->setBGImage(img_bg_pressed, ButtonWidget::ButtonState::Press);
	KeyButton->setImageOffset(-75, -4);
	KeyButton->setSoundPath("res/audio/ui/Hovered.mp3", ButtonWidget::ButtonState::Hover);
	KeyButton->setSoundPath("res/audio/ui/Click.mp3", ButtonWidget::ButtonState::Press);

	//Exit��ť
	ExitButton = new TextButtonWidget(this, { WIN_WIDTH / 2,WIN_HEIGHT / 2 + 260 }, { 200,50 }, 2, _T("ExitButton"), WidgetAnchor::MiddleCenter);
	ExitButton->setText(_T("�˳�"));
	ExitButton->setFontSize(30);
	ExitButton->setFont(_T("����"));
	ExitButton->setIsShowBackground(false, ButtonWidget::ButtonState::Default);
	ExitButton->setTextColor(RGB(0, 0, 0), ButtonWidget::ButtonState::Hover);
	ExitButton->setTextColor(RGB(49, 49, 49), ButtonWidget::ButtonState::Press);
	ExitButton->setBGImage(img_bg_hover, ButtonWidget::ButtonState::Hover);
	ExitButton->setBGImage(img_bg_pressed, ButtonWidget::ButtonState::Press);
	ExitButton->setImageOffset(-75, -4);
	ExitButton->setOnClickFunc([&] {
		SceneManager::GetInstance().QuitGame();
		});
	ExitButton->setSoundPath("res/audio/ui/Hovered.mp3", ButtonWidget::ButtonState::Hover);
	ExitButton->setSoundPath("res/audio/ui/Click.mp3", ButtonWidget::ButtonState::Press);

}


SelectBossMenuWidget::SelectBossMenuWidget(UserWidget* parent, int zOrder): UserWidget(parent, zOrder)
{
	//����ͼƬ
	IMAGE* img_bg_pressed = ResourcesManager::GetInstance().find_image("img_btn_bg_2")->getImage();
	IMAGE* img_bg_hover = ResourcesManager::GetInstance().find_image("img_btn_bg_1")->getImage();
	IMAGE* img_bg = ResourcesManager::GetInstance().find_image("img_menu_bg_select")->getImage();

	//���ñ���
	ImageWidget* bg = new ImageWidget(this, { WIN_WIDTH / 2,WIN_HEIGHT / 2 }, { WIN_WIDTH,WIN_HEIGHT }, 0, _T("bg"), WidgetAnchor::MiddleCenter);
	bg->setImage(img_bg);

	//���ذ�ť
	ChallengeButton = new TextButtonWidget(this, { WIN_WIDTH / 2 + 300 ,WIN_HEIGHT / 2 + 260 }, { 200,50 }, 2, _T("BackButton"), WidgetAnchor::MiddleCenter);
	ChallengeButton->setText(_T("��ս"));
	ChallengeButton->setFontSize(30);
	ChallengeButton->setFont(_T("����"));
	ChallengeButton->setSoundPath("res/audio/ui/Hovered.mp3", ButtonWidget::ButtonState::Hover);
	ChallengeButton->setSoundPath("res/audio/ui/Click.mp3", ButtonWidget::ButtonState::Press);
	ChallengeButton->setIsShowBackground(false, ButtonWidget::ButtonState::Default);
	ChallengeButton->setTextColor(RGB(0, 0, 0), ButtonWidget::ButtonState::Hover);
	ChallengeButton->setTextColor(RGB(49, 49, 49), ButtonWidget::ButtonState::Press);
	ChallengeButton->setBGImage(img_bg_hover, ButtonWidget::ButtonState::Hover);
	ChallengeButton->setBGImage(img_bg_pressed, ButtonWidget::ButtonState::Press);
	ChallengeButton->setImageOffset(-75, -4);


	//���ذ�ť
	BackButton = new TextButtonWidget(this, { WIN_WIDTH / 2 - 300 ,WIN_HEIGHT / 2 + 260 }, { 200,50 }, 2, _T("BackButton"), WidgetAnchor::MiddleCenter);
	BackButton->setText(_T("����"));
	BackButton->setFontSize(30);
	BackButton->setFont(_T("����"));
	BackButton->setSoundPath("res/audio/ui/Hovered.mp3", ButtonWidget::ButtonState::Hover);
	BackButton->setSoundPath("res/audio/ui/Click.mp3", ButtonWidget::ButtonState::Press);
	BackButton->setIsShowBackground(false, ButtonWidget::ButtonState::Default);
	BackButton->setTextColor(RGB(0, 0, 0), ButtonWidget::ButtonState::Hover);
	BackButton->setTextColor(RGB(49, 49, 49), ButtonWidget::ButtonState::Press);
	BackButton->setBGImage(img_bg_hover, ButtonWidget::ButtonState::Hover);
	BackButton->setBGImage(img_bg_pressed, ButtonWidget::ButtonState::Press);
	BackButton->setImageOffset(-75, -4);
}


KeyMenuWidget::KeyMenuWidget(UserWidget* parent, int zOrder): UserWidget(parent, zOrder)
{
	//����ͼƬ
	IMAGE* img_bg = ResourcesManager::GetInstance().find_image("img_menu_key")->getImage();
	IMAGE* img_bg_hover = ResourcesManager::GetInstance().find_image("img_btn_bg_1")->getImage();
	IMAGE* img_bg_pressed = ResourcesManager::GetInstance().find_image("img_btn_bg_2")->getImage();

	//���ñ���
	ImageWidget* bg = new ImageWidget(this, { WIN_WIDTH / 2,WIN_HEIGHT / 2 }, { WIN_WIDTH,WIN_HEIGHT }, 0, _T("bg"), WidgetAnchor::MiddleCenter);
	bg->setImage(img_bg);


	//���ذ�ť
	BackButton = new TextButtonWidget(this, { WIN_WIDTH / 2,WIN_HEIGHT / 2 + 260 }, { 200,50 }, 2, _T("BackButton"), WidgetAnchor::MiddleCenter);
	BackButton->setText(_T("����"));
	BackButton->setFontSize(30);
	BackButton->setFont(_T("����"));
	BackButton->setIsShowBackground(false, ButtonWidget::ButtonState::Default);
	BackButton->setTextColor(RGB(0, 0, 0), ButtonWidget::ButtonState::Hover);
	BackButton->setTextColor(RGB(49, 49, 49), ButtonWidget::ButtonState::Press);
	BackButton->setBGImage(img_bg_hover, ButtonWidget::ButtonState::Hover);
	BackButton->setBGImage(img_bg_pressed, ButtonWidget::ButtonState::Press);
	BackButton->setImageOffset(-75, -4);
	BackButton->setSoundPath("res/audio/ui/Hovered.mp3", ButtonWidget::ButtonState::Hover);
	BackButton->setSoundPath("res/audio/ui/Click.mp3", ButtonWidget::ButtonState::Press);


}



OptionsMenuWidget::OptionsMenuWidget(UserWidget* parent, int zOrder): UserWidget(parent, zOrder)
{
	//����ͼƬ
	IMAGE* img_bg_pressed = ResourcesManager::GetInstance().find_image("img_btn_bg_2")->getImage();
	IMAGE* img_bg_hover = ResourcesManager::GetInstance().find_image("img_btn_bg_1")->getImage();
	IMAGE* img_bg = ResourcesManager::GetInstance().find_image("img_menu_bg_settings")->getImage();

	//���ñ���
	ImageWidget* bg = new ImageWidget(this, { WIN_WIDTH / 2,WIN_HEIGHT / 2 }, { WIN_WIDTH,WIN_HEIGHT }, 0, _T("bg"), WidgetAnchor::MiddleCenter);
	bg->setImage(img_bg);


	MusicVolume = AudioManager::GetInstance().GetMusicVolume();
	SoundVolume = AudioManager::GetInstance().GetSoundVolume();

	MusicSlider = new SliderBarWidget(this, { WIN_WIDTH / 2,WIN_HEIGHT / 2 - 100 }, { 280,20 }, 2, _T("MusicSlider"), WidgetAnchor::MiddleCenter);
	MusicSlider->setCurrentValue(MusicVolume /100.0f);
	MusicSlider->setOnSlideCallback([&](float value) {
		MusicVolume = (int)(value * 100);
		MusicText->setText(std::to_wstring(MusicVolume).c_str());
		AudioManager::GetInstance().SetMusicVolume(MusicVolume);
		});

	MusicSlider->setOnMouseUpCallback([&] {
		//printf("MusicSlider OnMouseUpCallback\n");
		// ����JsonDataʵ��
		JsonData data;
		// ���Դ�ָ���ļ���ȡ����
		bool success = data.ReadFile("res/data/SettingsData.json");
		if (success) {
			data.UpdateData("Music", MusicVolume);
			//printf("MusicVolume:%d\n", MusicVolume);
		}
		});

	TextWidget* MusicTitle = new TextWidget(MusicSlider, {  -80 ,-2 }, { 80,50 }, 2, _T("OptionsTitle"));
	MusicTitle->setText(_T("����"));
	MusicTitle->setFontSize(26);
	MusicTitle->setFont(_T("����"));

	std::wstring music_volume_str = std::to_wstring(MusicVolume);
	MusicText = new TextWidget(MusicSlider, {  300 ,-2 }, { 80,50 }, 2, _T("MusicText"));
	MusicText->setText(music_volume_str.c_str());
	MusicText->setFontSize(26);
	MusicText->setFont(_T("����"));


	SoundSlider = new SliderBarWidget(this, { WIN_WIDTH / 2,WIN_HEIGHT / 2  }, { 280,20 }, 2, _T("SoundSlider"), WidgetAnchor::MiddleCenter);
	SoundSlider->setCurrentValue(SoundVolume / 100.0f);
	SoundSlider->setOnSlideCallback([&](float value) {
		SoundVolume = (int)(value * 100);
		SoundText->setText(std::to_wstring(SoundVolume).c_str());
		AudioManager::GetInstance().SetEffectVolume(SoundVolume);
		});

	SoundSlider->setOnMouseUpCallback([&] {
		JsonData data;
		// ���Դ�ָ���ļ���ȡ����
		bool success = data.ReadFile("res/data/SettingsData.json");
		if (success) {
			data.UpdateData("Effect", SoundVolume);
			//printf("Effect:%d\n", SoundVolume);
		}
		});

	TextWidget* SoundTitle = new TextWidget(SoundSlider, { -80 ,-2 }, { 80,50 }, 2, _T("OptionsTitle"));
	SoundTitle->setText(_T("��Ч"));
	SoundTitle->setFontSize(26);
	SoundTitle->setFont(_T("����"));
	
	std::wstring sound_volume_str = std::to_wstring(SoundVolume);
	SoundText = new TextWidget(SoundSlider, { 300 ,-2 }, { 80,50 }, 2, _T("SoundText"));
	SoundText->setText(sound_volume_str.c_str());
	SoundText->setFontSize(26);
	SoundText->setFont(_T("����"));


	//���ذ�ť
	BackButton = new TextButtonWidget(this, { WIN_WIDTH / 2  ,WIN_HEIGHT / 2 + 260 }, { 200,50 }, 2, _T("BackButton"), WidgetAnchor::MiddleCenter);
	BackButton->setText(_T("����"));
	BackButton->setFontSize(30);
	BackButton->setFont(_T("����"));
	BackButton->setIsShowBackground(false, ButtonWidget::ButtonState::Default);
	BackButton->setTextColor(RGB(0, 0, 0), ButtonWidget::ButtonState::Hover);
	BackButton->setTextColor(RGB(49, 49, 49), ButtonWidget::ButtonState::Press);
	BackButton->setBGImage(img_bg_hover, ButtonWidget::ButtonState::Hover);
	BackButton->setBGImage(img_bg_pressed, ButtonWidget::ButtonState::Press);
	BackButton->setImageOffset(-75, -4);
	BackButton->setSoundPath("res/audio/ui/Hovered.mp3", ButtonWidget::ButtonState::Hover);
	BackButton->setSoundPath("res/audio/ui/Click.mp3", ButtonWidget::ButtonState::Press);

	


}

