#pragma once

#include <vector>
#include "RenderItem.h"
#include "../Parameter/GlobeGameParameters.h"


//Item����
#define LAYER_ITEM_PLAYER									10								//�����ʾ�㼶
#define LAYER_ITEM_PARTICLE									9								//������ʾ�㼶
#define LAYER_ITEM_PLATFORM									4								//�ذ���ʾ�㼶
#define LAYER_ITEM_BUFFBOX								    15								//�ذ���ʾ�㼶
#define LAYER_ITEM_BULLET									14								//�ӵ���ʾ�㼶


class Camera;

class RenderManager
{
public:
    // ����ģʽ��ȡʵ��
    static RenderManager& getInstance() {
        static RenderManager instance;
        return instance;
    }

    // ���ø��ƺ͸�ֵ����
    RenderManager(const RenderManager&) = delete;
    RenderManager& operator=(const RenderManager&) = delete;


    // �������������ڴ���RenderItem
    RenderItem* createRenderItem(ImageInfo* img_info, int layer, bool canDestroyed = true);
    RenderItem* createRenderItem(ImageInfo* img_info, const Vector2& position, int layer, bool canDestroyed = true);

    // ����RenderItem
    void destroyRenderItem(RenderItem* item);

    // ��Ⱦ����������layer�����������Ⱦ
    void render_object(const Camera& camera);

    //������Ա����ٵ���Ⱦ����
    void clearDestroyedItems();

    //����������Ⱦ���������
    void setAllItemsBrightness(float brightness);

private:
    bool isSort_Object = false;
    std::vector<RenderItem*> renderList;
    std::vector<RenderItem*> destroyedList;

    // ȷ������ģʽ
    RenderManager() = default;
    ~RenderManager() = default;

};

