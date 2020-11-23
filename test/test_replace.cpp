#include "utils.h"
#include <iostream>
#include <typeinfo>
#include <tuple>
int main(int argc, char **argv)
{
    std::string tplate = "https://www.baidu.com/{x}/{y}/{z}/{test}";
    std::tuple<int,int,int> test(10,3,12);
    std::cout << Utils::replaceTokens(tplate,[test](const std::string &str)->std::string
    {
        if( str == "x")
        {
            return std::to_string(std::get<0>(test));
        }
        else if (str == "y")
        {
            return std::to_string(std::get<1>(test));
        }
        else if (str == "z")
        {
            return std::to_string(std::get<2>(test));
        }
        else if(str == "test")
        {
            return "world";
        }
        else
        {
            ;
        }
    }) << std::endl;

    return 0;
}