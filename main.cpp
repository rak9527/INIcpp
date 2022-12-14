#include <string>
#include <iostream>
#include "ini.h"

int main() {
    const std::string & filename = "./main.ini";
    IniFile ini(filename);
    ini.show();
    ini["profile"]["age"] = "28";
    ini["profile"]["email"] = "wwxx0718@163.com";
    ini.remove("server");
    ini["prop"]["date"] = "2022-12-22";
    std::cout << "========================" << std::endl;
    ini.show();
    ini.save("./main2.ini");
    return 0;
}
