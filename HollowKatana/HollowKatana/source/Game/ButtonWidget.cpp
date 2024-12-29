#include "ButtonWidget.h"
#include "WidgetElement.h"
#include "UserWidget.h"
#include "AudioManager.h"

ButtonWidget::ButtonWidget(UserWidget* parent, Vector2 position, Vector2 size, int zOrder, LPCTSTR className, WidgetAnchor anchor):
	WidgetElement(parent, position, size, zOrder, className, anchor)
{
	
}


ButtonWidget::~ButtonWidget()
{
	if (defaultBGInfo.image_info.scaledImage)
		delete defaultBGInfo.image_info.scaledImage;
	if (hoverBGInfo.image_info.scaledImage)
		delete hoverBGInfo.image_info.scaledImage;
	if (pressBGInfo.image_info.scaledImage)
		delete pressBGInfo.image_info.scaledImage;
}


void ButtonWidget::draw()
{
	if (currentBGInfo.isShowBackground)
	{
		if (currentBGInfo.image_info.getImageValid())				//如果图片有效，则绘制图片
		{
			if (currentBGInfo.image_info.isFill)
			{
				if (currentBGInfo.image_info.scaledImage == nullptr)
				{
					currentBGInfo.image_info.scaledImage = new IMAGE();
					helper::scaleImage(currentBGInfo.image_info.image, currentBGInfo.image_info.scaledImage, size.x, size.y);		//缩放图片

				}
				helper::putimage_alpha(position.x + currentBGInfo.image_info.offsetX, position.y + currentBGInfo.image_info.offsetY, currentBGInfo.image_info.scaledImage);
			}
			else
			{
				helper::putimage_alpha(position.x + currentBGInfo.image_info.offsetX, position.y + currentBGInfo.image_info.offsetY, currentBGInfo.image_info.image);
			}
		}
		else                                                        //如果图片无效，则绘制矩形
		{
			setfillcolor(currentBGInfo.color);
			solidroundrect(position.x, position.y, position.x + size.x, position.y + size.y, currentBGInfo.ellipsewidth, currentBGInfo.ellipseheight);
			if (currentBGInfo.isDrawLine)							//如果需要绘制边框，则绘制边框
			{
				setlinecolor(currentBGInfo.lineColor);
				roundrect(position.x, position.y, position.x + size.x, position.y + size.y, currentBGInfo.ellipsewidth, currentBGInfo.ellipseheight);
			}
			if (currentBGInfo.image_info.scaledImage)
			{
				delete currentBGInfo.image_info.scaledImage;
				currentBGInfo.image_info.scaledImage = nullptr;
			}
		}
	}

	UserWidget::draw();
}
void ButtonWidget::update(float delta)
{
	WidgetElement::update(delta);
}

void ButtonWidget::onDefault()
{
	setButtonInfo(defaultBGInfo);
	isHover = false;
	
}

void ButtonWidget::onEnter()
{
	//wprintf(L"name:%ls,Enter\n", className);
	if (onHover)
		onHover();
	isHover = true;
	setButtonInfo(hoverBGInfo);
	playSound();
}

void ButtonWidget::onLeave()
{
	//wprintf(L"name:%ls,Leave\n", className);
	onDefault();
	playSound();
}

void ButtonWidget::onMouseDown(const ExMessage& msg)
{
	//wprintf(L"name:%ls,MouseDown\n", className);
	if (onClick)
		onClick();
	if (onPress)
		onPress();

	setButtonInfo(pressBGInfo);
	playSound();
}

void ButtonWidget::onMouseUp(const ExMessage& msg)
{
	//wprintf(L"name:%ls,MouseUp\n", className);
	if (isHover)
		setButtonInfo(hoverBGInfo);
	else
		setButtonInfo(defaultBGInfo);
	if(onRelease)
		onRelease();
	//playSound();
}


void ButtonWidget::onMouseMove(const ExMessage& msg)
{
	isHover = true;
}

void ButtonWidget::playSound()
{
	if(currentBGInfo.SoundPath.empty())
		return;
	AudioManager::GetInstance().PlaySoundAudio(currentBGInfo.SoundPath.c_str(), AudioManager::AudioType::Effect, false);
	//printf("play sound:%s\n", currentBGInfo.SoundPath.c_str());
}