#pragma once

#include <string>
#include <map>

class Value {
    friend std::ostream &operator<<(std::ostream &out, const Value &value);

public:
    Value();

    Value(bool value);

    Value(int value);

    Value(double value);

    Value(const char *value);

    Value(const std::string &value);

    Value(const Value &value);

    ~Value();

    Value &operator=(bool value);

    Value &operator=(int value);

    Value &operator=(double value);

    Value &operator=(const char *value);

    Value &operator=(const std::string &value);

    Value &operator=(const Value &value);

    bool operator==(const Value &other);

    bool operator!=(const Value &other);

    operator bool();

    operator int();

    operator double();

    operator std::string();

private:
    std::string m_value;
};

typedef std::map<std::string, Value> Section;

class IniFile {
public:
    IniFile();

    IniFile(const std::string &filename);

    ~IniFile();

    bool load(const std::string &filename);

    bool save(const std::string &filename);

    Value &get(const std::string &section, const std::string &key);

    void set(const std::string &section, const std::string &key, const Value &value);

    void show();

    void clear();

    bool has(const std::string &section);

    bool has(const std::string &section, const std::string &key);

    void remove(const std::string &section);

    void remove(const std::string &section, const std::string &key);

    Section &operator[](const std::string &section);

    std::string str();

private:
    std::string filename;
    std::map<std::string, Section> sections;

    std::string trim(std::string s);
};
