#include "RenderManager.h"
#include <iostream>
#include "ImageInfo.h"

RenderItem* RenderManager::createRenderItem(ImageInfo* img_info, const Vector2& position, int layer, bool canDestroyed)
{
    RenderItem* item = new RenderItem(img_info, position, layer, canDestroyed);
    renderList.push_back(item);
    isSort_Object = true;
    return item;
}

RenderItem* RenderManager::createRenderItem(ImageInfo* img_info, int layer, bool canDestroyed)
{
    RenderItem* item = new RenderItem(img_info, {0,0}, layer, canDestroyed);
    renderList.push_back(item);
    isSort_Object = true;
    return item;
}


void RenderManager::destroyRenderItem(RenderItem* item)
{
    renderList.erase(std::remove(renderList.begin(), renderList.end(), item), renderList.end());
    if (item) {
        if(item->canBeDestroyed())
            delete item;
        isSort_Object = true;
    }
}

void RenderManager::render_object(const Camera& camera)
{
    if (isSort_Object)
    {
        // 按照 layer 从大到小排序
        std::sort(renderList.begin(), renderList.end(), [](RenderItem* a, RenderItem* b) {
            return a->layer < b->layer;
            });

        isSort_Object = false;
    }

    // 渲染所有的RenderItem
    for (auto& item : renderList) {
        if (!item)
        {
            destroyRenderItem(item);
            continue;
        }
        if(item->image_info && item->isRender && item->image_info->getImage())
        {
            if (item->isPostProcessed())
            {
                // 后处理
                if (item->brightness < 1.0f)
                {
                    IMAGE dst;
                    helper::adjustImageBrightness(item->image_info->getImage(),&dst, item->brightness);
                    helper::putimage_ex(camera, &dst, &item->rect_dst, &item->rect_src);
                    //printf("Brightness: %f\n", item->getBrightness());
                }
                else
                {
                    helper::putimage_ex(camera, item->image_info->getImage(), &item->rect_dst, &item->rect_src);
                }
            }
            else
            {
                helper::putimage_ex(camera, item->image_info->getImage(), &item->rect_dst, &item->rect_src);
            }
           
        }
       
    }

}

void RenderManager::clearDestroyedItems()
{
    auto it = std::remove_if(renderList.begin(), renderList.end(), [](RenderItem* item) {
        if (item) {
            if (item->canBeDestroyed())
            {
                delete item;
                return true;
            }
            return false;
        }
        return false;
        });
    renderList.erase(it, renderList.end());
}

void RenderManager::setAllItemsBrightness(float brightness)
{
    for (auto& item : renderList) {
        if (!item)
            continue;
        if (item->image_info && item->isRender && item->image_info->getImage())
        {
            item->setBrightness(brightness);
        }

    }
}



