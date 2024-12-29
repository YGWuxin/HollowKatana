#pragma once

#include "../Utils/helper.h"
#include <vector>
#include <algorithm>
#include "Vector2.h"
#include "../Parameter/GlobeGameParameters.h"
#include "ImageInfo.h"

class RenderItem {
public:
    // 设置图像
    void setImageInfo(ImageInfo* img_info)
    { 
        image_info = img_info;
        if (img_info && img_info->getImage())
        {
            rect_dst.w = img_info->getImage()->getwidth();
            rect_dst.h = img_info->getImage()->getheight();
        }
    }

    // 设置图像
    void setImageInfo(ImageInfo* img_info, const Rect& src)
    { 
        image_info = img_info;
        setRectSrc(src);
    }

    // 获取图像
    ImageInfo* getImageInfo() const { return image_info; }

    // 获取目标矩形
    Rect getRectDst() const { return rect_dst; }

    // 设置源矩形
    void setRectSrc(const Rect& src) 
    { 
        rect_src = src; 
        rect_dst.w = rect_src.w;
        rect_dst.h = rect_src.h;
    }

    //设置渲染的位置
    void setPositionX(int x)
    {
        rect_dst.x = x;
    }

    void setPositionY(int y)
    {
        rect_dst.y = y;
    }

    void setImageSize(int w, int h)
    {
        rect_src.w = w;
        rect_src.h = h;
        rect_dst.w = w;
        rect_dst.h = h;
    }

    void setRenderX(int x)
    {
        rect_src.x = x;
    }

    void setRenderY(int y)
    {
        rect_src.y = y;
    }

    // 设置层级
    void setLayer(int l) { layer = l; }

    // 获取层级
    int getLayer() const { return layer; }

    void setCanRender(bool isRender) { this->isRender = isRender; };

    bool getCanRender() { return isRender; }

    //获取是否能被销毁
    bool canBeDestroyed() const { return beDestroyed; }

    // 设置是否可以销毁
    void setCanBeDestroyed(bool canDestroy) {
        beDestroyed = canDestroy;
    }

    // 设置亮度
    void setBrightness(float b) { brightness = b;}

    // 获取亮度
    float getBrightness() const { return brightness; }

    // 设置是否受到后期处理
    void setPostProcessed(bool isPostProcessed) { postProcessed = isPostProcessed; }

    // 获取是否受到后期处理
    bool isPostProcessed() const { return postProcessed; }

    void setAnchorMode(AnchorMode mode) { this->mode = mode; }
    AnchorMode getAnchorMode() { return mode; }

    void setPosition(Vector2 position)
    {
        rect_dst.x = (int)position.x - rect_src.w / 2;
        switch (mode)
        {
        case AnchorMode::Centered:
            rect_dst.y = (int)position.y - rect_src.h / 2;
            break;
        case AnchorMode::BottomCrented:
            rect_dst.y = (int)position.y - rect_src.h;
            break;
        default:
            break;
        }
        rect_dst.w = rect_src.w;
        rect_dst.h = rect_src.h;
    }

    void setPosition(Vector2 position,int offsetX,int offsetY)
    {
        rect_dst.x = (int)position.x - rect_src.w / 2 + offsetX;
        switch (mode)
        {
        case AnchorMode::Centered:
            rect_dst.y = (int)position.y - rect_src.h / 2 + offsetY;
            break;
        case AnchorMode::BottomCrented:
            rect_dst.y = (int)position.y - rect_src.h + offsetY;
            break;
        default:
            break;
        }
        rect_dst.w = rect_src.w;
        rect_dst.h = rect_src.h;
    }


    Vector2 getPostion()
    {
        float x = (int)rect_dst.x + rect_src.w / 2;
        float y = 0;
        switch (mode)
        {
        case AnchorMode::Centered:
            y = (int)rect_dst.y + rect_src.h / 2;
            break;
        case AnchorMode::BottomCrented:
            y = (int)rect_dst.y + rect_src.h;
            break;
        default:
            break;
        }
        return Vector2(x,y);
    }

private:
    ImageInfo* image_info;
    Rect rect_dst;
    Rect rect_src;
    int layer;
    bool beDestroyed;                           // 表示是否可以被销毁
    AnchorMode mode = AnchorMode::Centered;
    bool isRender = true;
   
    float brightness = 1.0f;                     //亮度
    //是否受到后期处理
    bool postProcessed = true;



private:
    // 构造函数私有化，避免外部直接实例化
    RenderItem(ImageInfo* img_info,Vector2 position ,int lyr,bool beDestroyed)
        : image_info(img_info), layer(lyr), beDestroyed(beDestroyed) {

        if (image_info && image_info->getImage())
        {
            this->rect_src.x = 0;
            this->rect_src.y = 0;
            this->rect_src.w = img_info->getImage()->getwidth();
            this->rect_src.h = image_info->getImage()->getheight();

            this->rect_dst.w = image_info->getImage()->getwidth();
            this->rect_dst.h = image_info->getImage()->getheight();
        }
        else
        {
            this->rect_src = { 0,0,0,0 };
            this->rect_dst = this->rect_src;
        }
        setPosition(position);
    }

    // 友元类
    friend class RenderManager;
};



