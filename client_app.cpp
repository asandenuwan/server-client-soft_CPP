#include "client.h"

using namespace std;
int main(){
    string ip="127.0.0.1";
    client c=client(ip,5555);
    string msg="";
    while (1){
        cout<<"Enter a message: ";
        getline(cin,msg);
        c.send_msg(msg);
        msg="";
    }
    return 0;
}