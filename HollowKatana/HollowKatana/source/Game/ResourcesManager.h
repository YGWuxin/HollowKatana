#pragma once

#include "atlas.h"
#include "ImageInfo.h"
#include <fstream>
#include <unordered_map>
#include <graphics.h>	

using namespace std;

class ResourcesManager
{
public:
    static ResourcesManager& GetInstance()
    {
        static ResourcesManager instance; // ��̬�ֲ�������ȷ��Ψһ��
        return instance;
    }

    // ɾ���������캯���͸�ֵ�����
    ResourcesManager(const ResourcesManager&) = delete;
    ResourcesManager& operator=(const ResourcesManager&) = delete;


    //���غ���֤csv�ļ�������
    void loadAndValidate(const string& filename);


    Atlas* find_atlas(const string& id) const;
    ImageInfo* find_image(const string& id) const;


private:
    unordered_map<string, Atlas*>  atlas_pool;
    unordered_map<string, ImageInfo*>  image_info_pool;
    

    ResourcesManager() = default;    // ˽�й��캯������ֹ�ⲿ����ʵ��
    ~ResourcesManager() = default;
    bool validateHeader(const string& header) const;       // ��֤�������Ƿ����Ԥ��

};

