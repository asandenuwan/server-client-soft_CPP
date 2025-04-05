#include "msg_filter.h"

filter::filter(std::string msg, std::string cut_word) : msg(msg), cut_word(cut_word) {}

void filter::run(){
    int t = 0;
    for (int m = 0; m < msg.size(); m++){
        if (msg[m] == cut_word[0]){
            std::string tmp_list = "";

            for (int i = m; i < m + cut_word.size(); i++){
                tmp_list.push_back(msg[i]);
            }
            if (tmp_list == cut_word){
                this->cutter(m, m + cut_word.size(), t);
                t = m + cut_word.size();
            }
        }
    }
    if (t < msg.size()){
        for (int i = t; i < msg.size(); i++){
            filtered_word.push_back(msg[i]);
        }
    }
}

void filter::cutter(int s, int e, int t){
    for (int i = t; i < e; i++){
        if (i >= s && i <= e){
            continue;
        }
        filtered_word.push_back(msg[i]);
    }
}

std::string filter::get_filterd_word(){
    return filtered_word;
}


// int main(){
//     filter f("ass@pa@ss#;ss@asssa@pass#;sss@pass#;@pass#;zsafsdfs@pass#;;","@pass#;");
//     f.run();
//     std::cout<<f.get_filterd_word();
// }