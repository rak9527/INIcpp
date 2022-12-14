#include "ini.h"
#include <fstream>
#include <iostream>
#include <sstream>

Value::Value() {
}

Value::Value(bool value) {
    m_value = value ? "true" : "false";
}

Value::Value(int value) {
    m_value = std::to_string(value);
}

Value::Value(double value) {
    m_value = std::to_string(value);
}

Value::Value(const char *value) {
    m_value = value;
}

Value::Value(const std::string &value) {
    m_value = value;
}

Value::Value(const Value &value) {
    m_value = value.m_value;
}

Value::~Value() {}

Value &Value::operator=(bool value) {
    m_value = value ? "true" : "false";
    return *this;
}

Value &Value::operator=(int value) {
    m_value = std::to_string(value);
    return *this;
}

Value &Value::operator=(double value) {
    m_value = std::to_string(value);
    return *this;
}

Value &Value::operator=(const char *value) {
    m_value = value;
    return *this;
}

Value &Value::operator=(const std::string &value) {
    m_value = value;
    return *this;
}

Value &Value::operator=(const Value &value) {
    m_value = value.m_value;
    return *this;
}

bool Value::operator==(const Value &other) {
    return m_value == other.m_value;
}

bool Value::operator!=(const Value &other) {
    return m_value != other.m_value;
}

Value::operator bool() {
    return m_value == "true";
}

Value::operator int() {
    return std::atoi(m_value.c_str());
}

Value::operator double() {
    return std::atof(m_value.c_str());
}

Value::operator std::string() {
    return m_value;
}

std::ostream& operator<<(std::ostream &out, const Value& value) {
    out << value.m_value;
    return out;
}
std::string IniFile::trim(std::string s) {
    if (s.empty()) return s;
    s.erase(0, s.find_first_not_of(" "));
    s.erase(s.find_last_not_of(" ") + 1);
    return s;
}

IniFile::IniFile() {}

IniFile::IniFile(const std::string &filename) {
    load(filename);
}

IniFile::~IniFile() {}

bool IniFile::load(const std::string &filename) {
    std::ifstream fin(filename.c_str());
    if (fin.fail()) {
        printf("loading file failed. %s is not found.\n", filename.c_str());
        return false;
    }
    this->filename = filename;
    sections.clear();
    std::string line;
    std::string cursection;
    int linenum = 1;
    while (getline(fin, line)) {
        line = trim(line);
        if (line == "") continue;
        if (line[0] == ';') continue;
        if (line[0] == '#') continue;
        if (line[0] == '[') {
            int pos = line.find_first_of(']');
            if (pos < 0) {
                printf("missing ] at line %d.\n", linenum);
                return false;
            }
            cursection = line.substr(1, pos - 1);
            if (sections.count(cursection)) sections[cursection] = Section();
        } else {
            int pos = line.find_first_of('=');
            if (pos < 0) {
                printf("missing = at line %d.\n", linenum);
                return false;
            }
            std::string key = trim(line.substr(0, pos));
            std::string value = trim(line.substr(pos + 1));
            sections[cursection][key] = value;
        }
        linenum++;
    }
    return true;
}

bool IniFile::save(const std::string &filename) {
    std::ofstream out(filename.c_str());
    if (out.fail()) {
        printf("opening file %s failed.\n", filename.c_str());
        return false;
    }
    out << str();
    return true;
}

void IniFile::show() {
    std::cout << str();
}

void IniFile::clear() {
    sections.clear();
}

std::string IniFile::str() {
    std::stringstream ss;
    for (const auto &pair: sections) {
        std::string sectionname = pair.first;
        Section section = pair.second;
        ss << "[" << sectionname << "]" << std::endl;
        for (const auto &item: section) {
            ss << item.first << " = " << item.second << std::endl;
        }
        ss << std::endl;
    }
    return ss.str();
}

Value &IniFile::get(const std::string &section, const std::string &key) {
    return sections[section][key];
}

void IniFile::set(const std::string &section, const std::string &key, const Value &value) {
    sections[section][key] = value;
}

bool IniFile::has(const std::string &section) {
    return sections.find(section) != sections.end();
}

bool IniFile::has(const std::string &section, const std::string &key) {
    return sections.find(section) != sections.end() && sections[section].find(key) != sections[section].end();
}

void IniFile::remove(const std::string &section) {
    sections.erase(section);
}

void IniFile::remove(const std::string &section, const std::string &key) {
    if (sections.find(section) != sections.end()) {
        sections[section].erase(key);
    }
}

Section &IniFile::operator[](const std::string &section) {
    return sections[section];
}