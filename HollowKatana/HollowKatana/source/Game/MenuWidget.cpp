#include "MenuWidget.h"
#include "WidgetManager.h"
#include "MainMenuWidget.h"
#include "TestWidget.h"
#include "TextButtonWidget.h"
#include "TimerManager.h"
#include "../Utils/helper.h"
#include "SceneManager.h"


MenuWidget::MenuWidget(UserWidget* parent, int zOrder): UserWidget(parent, zOrder)
{
	MainMenuWidget* main_widget = WidgetManager::GetInstance().createUserWidgetInstance<MainMenuWidget>(this, 1);
	addWidget("MainMenu", main_widget);

	SelectBossMenuWidget* select_boss_widget = WidgetManager::GetInstance().createUserWidgetInstance<SelectBossMenuWidget>(this, 2);
	addWidget("SelectBossMenu", select_boss_widget);
	select_boss_widget->BackButton->setOnReleaseFunc([&] {
		switchToNextWidget("MainMenu");
		});



	KeyMenuWidget* key_widget = WidgetManager::GetInstance().createUserWidgetInstance<KeyMenuWidget>(this, 2);
	addWidget("KeyMenuMenu", key_widget);
	key_widget->BackButton->setOnReleaseFunc([&] {
		switchToNextWidget("MainMenu");
		});

	OptionsMenuWidget* options_widget = WidgetManager::GetInstance().createUserWidgetInstance<OptionsMenuWidget>(this, 2);
	addWidget("OptionsMenu", options_widget);
	options_widget->BackButton->setOnReleaseFunc([&] {
		switchToNextWidget("MainMenu");
		});


	main_widget->KeyButton->setOnReleaseFunc([&] {
		switchToNextWidget("KeyMenuMenu");
		});
	main_widget->OptionsButton->setOnReleaseFunc([&] {
		switchToNextWidget("OptionsMenu");
		});
	main_widget->PlayButton->setOnReleaseFunc([&] {
		//switchToNextWidget("SelectBossMenu");
		SceneManager::GetInstance().switch_to(SceneManager::SceneType::Level1);

		});

	setCurrentWidget(main_widget);

}


void MenuWidget::draw()
{
	UserWidget::draw();
	if (is_fading)
		helper::post_process_full_screen(current_brightness);
}

void MenuWidget::update(float delta)
{
	UserWidget::update(delta);
	TimerManager::GetInstance().lerp_float(current_brightness,target_brightness, fade_speed,delta);
	if (current_brightness == 0.0f)
	{
		target_brightness = 1.0f;
		current_widget->setVisible(false);

		current_widget = temp_widget;
		current_widget->setVisible(true);
		current_widget->setEnabled(true);
	}
	if(current_brightness == 1.0f)
		is_fading = false;
}


void MenuWidget::setCurrentWidget(UserWidget* widget)
{
	for (auto it = widgets_map.begin(); it != widgets_map.end(); ++it) 
	{
		UserWidget* w = it->second;
		w->setVisible(false);
		w->setEnabled(false);
	}
	current_widget = widget;
	temp_widget = widget;
	current_widget->setVisible(true);
	current_widget->setEnabled(true);
}


void MenuWidget::switchToNextWidget(string name)
{
	UserWidget* widget = findWidget(name);
	if(widget == nullptr)
		return;
	current_widget->setEnabled(false);
	target_brightness = 0.0f;
	is_fading = true;
	temp_widget = widget;
}