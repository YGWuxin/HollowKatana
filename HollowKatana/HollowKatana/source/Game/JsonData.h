#pragma once
#include <iostream>
#include <fstream>
#include <sstream>
#include <map>
#include <string>

class JsonData {
public:
    // ���캯��
    JsonData()
        : m_filename("") {}

    // ��������
    ~JsonData() {}

    // ���Զ�ȡָ�����ļ����������Ƿ�ɹ�
    bool ReadFile(const std::string& filename) {
        m_filename = filename;
        return load(); // �������Լ����ļ������ؽ��
    }

    // �����µ�JSON�ļ�
    bool CreateNewFile(const std::string& filename) {
        return CreateNewFile(filename, {});
    }

    // �����µ�JSON�ļ�����ӳ�ʼ����
    bool CreateNewFile(const std::string& filename, const std::map<std::string, std::string>& initialData) {
        m_filename = filename;
        // ��ӳ�ʼ����
        for (const auto& pair : initialData) {
            m_data[pair.first] = pair.second;
        }
        // �������ݵ����ļ�
        save();
        return true;
    }

    // �����ļ�����
    bool load() {
        // ����ļ����Ƿ�Ϊ��
        if (m_filename.empty()) {
            std::cerr << "�ļ���Ϊ�գ��޷������ļ���" << std::endl;
            return false;
        }

        // ���Դ��ļ�������JSON����
        std::ifstream file(m_filename);
        if (file.is_open()) {
            std::stringstream buffer;
            buffer << file.rdbuf();
            file.close();
            std::string str = buffer.str();
            try {
                // �����ַ���Ϊmap
                parseJson(str);
                return true; // �ɹ������ļ�
            }
            catch (const std::exception& e) {
                std::cerr << "����JSON�ļ�ʧ��: " << e.what() << std::endl;
                m_data.clear(); // ���JSON����
                return false; // �����ļ�ʧ��
            }
        }
        else {
            std::cout << "�ļ�δ�ҵ��������µ�JSON����" << std::endl;
            m_data.clear(); // ���JSON����
            return false; // ���ļ�ʧ��
        }
    }

    // ���浱ǰ��JSON����
    void save() const {
        // ����ļ����Ƿ�Ϊ��
        if (m_filename.empty()) {
            std::cerr << "�ļ���Ϊ�գ��޷������ļ���" << std::endl;
            return;
        }

        // ȷ���ļ�����������������򴴽�
        std::ofstream file(m_filename);
        if (!file.is_open()) {
            std::cerr << "�޷�����/���ļ�: " << m_filename << std::endl;
            return;
        }
        // ���л�mapΪ�ַ���
        std::string str = serializeJson();
        file << str << std::endl; // ���JSON
        file.close();
    }

    // ����JSON�е�ĳ������ֵ�����Զ�����
    template<typename T>
    void UpdateData(const std::string& key, const T& value) {
        // ����ļ����Ƿ�Ϊ��
        if (m_filename.empty()) {
            std::cerr << "�ļ���Ϊ�գ��޷��������ݡ�" << std::endl;
            return;
        }

        // ʹ��stringstream��ת����������Ϊ�ַ���
        std::stringstream ss;
        ss << value;
        m_data[key] = ss.str();
        save(); // ���º��Զ�����
    }

    // ɾ��JSON�е�ĳ����
    bool RemoveKey(const std::string& key) {
        // ����ļ����Ƿ�Ϊ��
        if (m_filename.empty()) {
            std::cerr << "�ļ���Ϊ�գ��޷�ɾ�����ݡ�" << std::endl;
            return false;
        }

        auto it = m_data.find(key);
        if (it != m_data.end()) {
            m_data.erase(it);
            save(); // ɾ�����Զ�����
            return true;
        }
        return false; // ����������ڣ��򷵻�false
    }

    // ��ȡJSON�е�ĳ������ֵ�������������д�����ñ�����������true�����򷵻�false
    template<typename T>
    bool Read(const std::string& key, T& value) const {
        // ����ļ����Ƿ�Ϊ��
        if (m_filename.empty()) {
            std::cerr << "�ļ���Ϊ�գ��޷���ȡ���ݡ�" << std::endl;
            return false;
        }

        auto it = m_data.find(key);
        if (it != m_data.end()) {
            try {
                std::istringstream iss(it->second);
                iss >> value;
                if (iss.fail()) {
                    throw std::runtime_error("ת��ʧ��");
                }
                return true; // ��������ڣ��򷵻�true
            }
            catch (const std::exception& e) {
                std::cerr << "ת��ʧ��: " << e.what() << std::endl;
            }
        }
        return false; // ����������ڣ��򷵻�false
    }

private:
    // ����JSON�ַ�����map
    void parseJson(const std::string& str) {
        // ����JSON�ַ����Ǽ�ֵ�Ե���ʽ������ {"key": "value"}
        std::istringstream iss(str);
        char ch;
        iss >> ch; // ���� '{'

        while (iss) {
            iss >> ch; // ��ȡ��һ���ַ�
            if (ch == '}') break; // ����ѭ������

            if (ch != '"') {
                throw std::runtime_error("JSON�ַ�����ȱ��\"�ַ�");
            }
            
            // ��ȡ��
            std::string key;
            readQuotedString(iss, key);

            iss >> ch; // ��ȡ��һ���ַ�
           
            if (ch != ':') {
                throw std::runtime_error("JSON�ַ�����ȱ��':'�ַ�");
            }

            iss >> ch; // ��ȡ��һ���ַ�
            if (ch != '"') {
                throw std::runtime_error("JSON�ַ�����ȱ��\"�ַ�");
            }

            // ��ȡֵ
            std::string value;
            readQuotedString(iss, value);

            iss >> ch; // ��ȡ��һ���ַ�
            if (ch != ',' && ch != '}') {
                throw std::runtime_error("JSON�ַ�����ȱ��','��'}'�ַ�");
            }

            m_data[key] = value;
        }

        // ȷ��JSON�ַ�����'}'����
        iss >> ch;
        if (ch != '}') {
            throw std::runtime_error("JSON�ַ���δ��'}'�ַ�����");
        }
    }

    // ��ȡ�����ŵ��ַ���
    void readQuotedString(std::istream& iss, std::string& str) {
        str.clear();
        char ch;

        while (iss) {
            iss >> ch;
            if (ch == '\\') { // ����ת���ַ�
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
                default: throw std::runtime_error("δ֪��ת���ַ�");
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


    // ���л�mapΪJSON�ַ���
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

    std::map<std::string, std::string> m_data; // �洢JSON����
    std::string m_filename; // ��ǰ�������ļ���
};