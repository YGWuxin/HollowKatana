#pragma once
#include "UserWidget.h"
#include "TextWidget.h"

class TextButtonWidget;
class BarWidget;


class WD_Player : public UserWidget
{
public:
	WD_Player(UserWidget* parent, int zOrder);
	~WD_Player() = default;

	void setHP(float value) const;

	void setMP(float value) const;

	void setStamina(float value) const;

	void testFunction();

	void testFunction1();

	void setTips(const std::wstring& newText) const;


private:
	
	BarWidget* bar_hp = nullptr;

	BarWidget* bar_mp = nullptr;

	BarWidget* bar_stamina = nullptr;

	TextWidget* text_tips= nullptr;


};

