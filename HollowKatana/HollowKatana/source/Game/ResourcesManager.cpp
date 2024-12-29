#include "ResourcesManager.h"
#include <iostream>
#include <string>
#include <sstream>
#include "../Utils/helper.h"
#include <tchar.h>    // For TCHAR
#include "../Utils/helper.h"

using namespace std;

//�����زı��
void ResourcesManager::loadAndValidate(const string& filename)
{
    ifstream file(filename);

    if (!file.is_open())
    {
        file.close();
        throw runtime_error("�޷����ļ�: " + filename);
    }

    string line;
    // ��ȡ����������У�����еĻ���
    if (!getline(file, line))
    {
        file.close();
        throw runtime_error("�޷���ȡ������: " + filename);
    }

    // ��֤�������Ƿ���ȷ
    if (!validateHeader(line))
    {
        file.close();
        throw runtime_error("�����в���ȷ: " + filename);
    }

    while (getline(file, line))
    {
        stringstream ss(line);
        string token;

        // ��ȡÿ�е�����
        vector<string> columns;
        while (getline(ss, token, ','))
        {
            columns.push_back(token);
        }

        if (columns.size() < 6)
        {
            throw runtime_error("�����и�ʽ����: " + filename);
        }

        string id = columns[0];
        string path = columns[1];
        string type = columns[2];
        bool needFlip = stoi(columns[3]);
        int FrameNum = stoi(columns[4]);
        float Scale = stof(columns[5]);

        if (type == "atlas")
        {
            Atlas* src_atlas = new Atlas();
            

            // ת��Ϊ std::wstring
            std::wstring wpath = helper::stringToWstring(path);
            src_atlas->load_from_file(wpath.c_str(), FrameNum, Scale);
            for (int i = 0; i < src_atlas->get_size(); i++)
            {
                IMAGE* image = src_atlas->get_image(i);
                if (!helper::check_image_valid(image))
                {
                    delete src_atlas; // �����ѷ������Դ
                    file.close();
                    throw runtime_error("ͼ����֤ʧ��: " + path);
                }
            }
            if (!needFlip)
            {
                atlas_pool[id] = src_atlas;
            }
            else
            {
                Atlas* dst_atlas = new Atlas();
                helper::flip_atlas(*src_atlas, *dst_atlas);
                delete src_atlas;
                atlas_pool[id] = dst_atlas;
               // printf("flip atlas:%s\n", id.c_str());
            }
        }
        else if (type == "image")
        {
            IMAGE* src_image = new IMAGE();
            IMAGE* dst_image = src_image;
            std::wstring wpath = helper::stringToWstring(path);
            loadimage(src_image, wpath.c_str());
            if (!helper::check_image_valid(src_image))
            {
                delete src_image; // �����ѷ������Դ
                file.close();
                throw runtime_error("ͼ����֤ʧ��: " + path);
            }
            
            if (Scale != 1.0)
            {
                //printf("Scale:%.2f", Scale);
                dst_image = new IMAGE();
                helper::scaleImage(src_image, dst_image, Scale);
                delete src_image; // �����ѷ������Դ
            }

            if (!needFlip)
            {
                ImageInfo* image_imfo = new ImageInfo(dst_image, FrameNum);
                image_info_pool[id] = image_imfo;
            }
            else
            {
                IMAGE* flip_image = new IMAGE();
                helper::flip_image(dst_image, flip_image, FrameNum);
                delete dst_image;
                ImageInfo* image_imfo = new ImageInfo(flip_image, FrameNum);
                image_info_pool[id] = image_imfo;
            }
        }
        else
        {
            throw runtime_error("��֧�ֵ�����: " + type);
        }
    }
    file.close();
}



bool ResourcesManager::validateHeader(const std::string& header) const
{
    vector<string> expectedHeader = { "id", "path", "type","needFlip","FrameNum","Scale","Notes"};
    stringstream ss(header);
    string token;
    vector<string> headerColumns;

    while (getline(ss, token, ','))
    {
        headerColumns.push_back(token);
    }

    if (headerColumns.size() != expectedHeader.size())
    {
        return false;
    }

    for (size_t i = 0; i < expectedHeader.size(); ++i)
    {
        if (headerColumns[i] != expectedHeader[i])
        {
            return false;
        }
    }

    return true;
}



Atlas* ResourcesManager::find_atlas(const string& id) const
{
    const auto& itor = atlas_pool.find(id);
    if (itor == atlas_pool.end())
        return nullptr;

	return itor->second;
}


ImageInfo* ResourcesManager::find_image(const string& id) const
{
    const auto& itor = image_info_pool.find(id);
    if (itor == image_info_pool.end())
        return nullptr;

    return itor->second;
}

