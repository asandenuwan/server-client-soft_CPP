#include <string>
#include <cstring>
#include <iostream>

class filter
{
protected:
    std::string filtered_word = "";
    std::string msg;
    std::string cut_word;

public:
    filter(std::string msg, std::string cut_word);
    void run();
    void cutter(int s, int e, int t);
    std::string get_filterd_word();
};