#pragma once
#include "UserWidget.h"
#include "TextWidget.h"

class TextButtonWidget;
class BarWidget;

class TestWidget : public UserWidget
{
public:
	TestWidget(UserWidget* parent, int zOrder);
	~TestWidget() = default;

	void testFunction();

	void testFunction1();

	void testButton(Vector2 position, LPCWSTR text);

	TextButtonWidget* button = nullptr;
	BarWidget* bar = nullptr;
};

