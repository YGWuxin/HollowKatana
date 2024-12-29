#pragma once
#include "UserWidget.h"

class TextButtonWidget;
class BarWidget;


class WD_Hornet : public UserWidget
{
public:
	WD_Hornet(UserWidget* parent, int zOrder);
	~WD_Hornet() = default;

	void setHP(float value) const;

	void testFunction();

	void testFunction1();

private:

	BarWidget* bar_hp = nullptr;


};

