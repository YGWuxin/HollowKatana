#pragma once
#include <iostream>
#include <fstream>
#include <sstream>
#include <map>
#include <string>

class JsonData {
public:
    // 构造函数
    JsonData()
        : m_filename("") {}

    // 析构函数
    ~JsonData() {}

    // 尝试读取指定的文件，并返回是否成功
    bool ReadFile(const std::string& filename) {
        m_filename = filename;
        return load(); // 立即尝试加载文件并返回结果
    }

    // 创建新的JSON文件
    bool CreateNewFile(const std::string& filename) {
        return CreateNewFile(filename, {});
    }

    // 创建新的JSON文件并添加初始数据
    bool CreateNewFile(const std::string& filename, const std::map<std::string, std::string>& initialData) {
        m_filename = filename;
        // 添加初始数据
        for (const auto& pair : initialData) {
            m_data[pair.first] = pair.second;
        }
        // 保存数据到新文件
        save();
        return true;
    }

    // 加载文件内容
    bool load() {
        // 检查文件名是否为空
        if (m_filename.empty()) {
            std::cerr << "文件名为空，无法加载文件。" << std::endl;
            return false;
        }

        // 尝试打开文件并解析JSON内容
        std::ifstream file(m_filename);
        if (file.is_open()) {
            std::stringstream buffer;
            buffer << file.rdbuf();
            file.close();
            std::string str = buffer.str();
            try {
                // 解析字符串为map
                parseJson(str);
                return true; // 成功加载文件
            }
            catch (const std::exception& e) {
                std::cerr << "解析JSON文件失败: " << e.what() << std::endl;
                m_data.clear(); // 清空JSON对象
                return false; // 解析文件失败
            }
        }
        else {
            std::cout << "文件未找到，创建新的JSON对象。" << std::endl;
            m_data.clear(); // 清空JSON对象
            return false; // 打开文件失败
        }
    }

    // 保存当前的JSON数据
    void save() const {
        // 检查文件名是否为空
        if (m_filename.empty()) {
            std::cerr << "文件名为空，无法保存文件。" << std::endl;
            return;
        }

        // 确保文件创建，如果不存在则创建
        std::ofstream file(m_filename);
        if (!file.is_open()) {
            std::cerr << "无法创建/打开文件: " << m_filename << std::endl;
            return;
        }
        // 序列化map为字符串
        std::string str = serializeJson();
        file << str << std::endl; // 输出JSON
        file.close();
    }

    // 更新JSON中的某个键的值，并自动保存
    template<typename T>
    void UpdateData(const std::string& key, const T& value) {
        // 检查文件名是否为空
        if (m_filename.empty()) {
            std::cerr << "文件名为空，无法更新数据。" << std::endl;
            return;
        }

        // 使用stringstream来转换数据类型为字符串
        std::stringstream ss;
        ss << value;
        m_data[key] = ss.str();
        save(); // 更新后自动保存
    }

    // 删除JSON中的某个键
    bool RemoveKey(const std::string& key) {
        // 检查文件名是否为空
        if (m_filename.empty()) {
            std::cerr << "文件名为空，无法删除数据。" << std::endl;
            return false;
        }

        auto it = m_data.find(key);
        if (it != m_data.end()) {
            m_data.erase(it);
            save(); // 删除后自动保存
            return true;
        }
        return false; // 如果键不存在，则返回false
    }

    // 读取JSON中的某个键的值，如果键存在则写入引用变量，并返回true；否则返回false
    template<typename T>
    bool Read(const std::string& key, T& value) const {
        // 检查文件名是否为空
        if (m_filename.empty()) {
            std::cerr << "文件名为空，无法读取数据。" << std::endl;
            return false;
        }

        auto it = m_data.find(key);
        if (it != m_data.end()) {
            try {
                std::istringstream iss(it->second);
                iss >> value;
                if (iss.fail()) {
                    throw std::runtime_error("转换失败");
                }
                return true; // 如果键存在，则返回true
            }
            catch (const std::exception& e) {
                std::cerr << "转换失败: " << e.what() << std::endl;
            }
        }
        return false; // 如果键不存在，则返回false
    }

private:
    // 解析JSON字符串到map
    void parseJson(const std::string& str) {
        // 假设JSON字符串是键值对的形式，例如 {"key": "value"}
        std::istringstream iss(str);
        char ch;
        iss >> ch; // 忽略 '{'

        while (iss) {
            iss >> ch; // 获取下一个字符
            if (ch == '}') break; // 结束循环条件

            if (ch != '"') {
                throw std::runtime_error("JSON字符串中缺少\"字符");
            }
            
            // 读取键
            std::string key;
            readQuotedString(iss, key);

            iss >> ch; // 获取下一个字符
           
            if (ch != ':') {
                throw std::runtime_error("JSON字符串中缺少':'字符");
            }

            iss >> ch; // 获取下一个字符
            if (ch != '"') {
                throw std::runtime_error("JSON字符串中缺少\"字符");
            }

            // 读取值
            std::string value;
            readQuotedString(iss, value);

            iss >> ch; // 获取下一个字符
            if (ch != ',' && ch != '}') {
                throw std::runtime_error("JSON字符串中缺少','或'}'字符");
            }

            m_data[key] = value;
        }

        // 确保JSON字符串以'}'结束
        iss >> ch;
        if (ch != '}') {
            throw std::runtime_error("JSON字符串未以'}'字符结束");
        }
    }

    // 读取带引号的字符串
    void readQuotedString(std::istream& iss, std::string& str) {
        str.clear();
        char ch;

        while (iss) {
            iss >> ch;
            if (ch == '\\') { // 处理转义字符
                iss >> ch;
                switch (ch) {
                case '"': str += '"'; break;
                case '\\': str += '\\'; break;
                case '/': str += '/'; break;
                case 'b': str += '\b'; break;
                case 'f': str += '\f'; break;
                case 'n': str += '\n'; break;
                case 'r': str += '\r'; break;
                case 't': str += '\t'; break;
                default: throw std::runtime_error("未知的转义字符");
                }
            }
            else if (ch == '"') {
                break;
            }
            else {
                str += ch;
            }
        }
    }


    // 序列化map为JSON字符串
    std::string serializeJson() const {
        std::ostringstream oss;
        oss << "{";
        for (auto it = m_data.begin(); it != m_data.end(); ++it) {
            if (it != m_data.begin()) {
                oss << ",";
            }
            oss << "\"" << it->first << "\":\"" << it->second << "\"";
        }
        oss << "}";
        return oss.str();
    }

    std::map<std::string, std::string> m_data; // 存储JSON数据
    std::string m_filename; // 当前操作的文件名
};