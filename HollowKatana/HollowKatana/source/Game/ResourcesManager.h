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
        static ResourcesManager instance; // 静态局部变量，确保唯一性
        return instance;
    }

    // 删除拷贝构造函数和赋值运算符
    ResourcesManager(const ResourcesManager&) = delete;
    ResourcesManager& operator=(const ResourcesManager&) = delete;


    //加载和验证csv文件的内容
    void loadAndValidate(const string& filename);


    Atlas* find_atlas(const string& id) const;
    ImageInfo* find_image(const string& id) const;


private:
    unordered_map<string, Atlas*>  atlas_pool;
    unordered_map<string, ImageInfo*>  image_info_pool;
    

    ResourcesManager() = default;    // 私有构造函数，防止外部创建实例
    ~ResourcesManager() = default;
    bool validateHeader(const string& header) const;       // 验证标题行是否符合预期

};

