#include <iostream>
#include <string>
#include <cstring>
#include <memory.h>
#include <thread>
#include <winsock2.h>
#include <windows.h>
// ; (2+main) thread running while object in RAM ;

class client{
    protected:
        WSAData wsa;
        SOCKET client_socket=INVALID_SOCKET;
        sockaddr_in server_path;
        std::string server_ip;
        int port;
    public:
        client(std::string ip,int port);
        bool wsa_setup();
        void send_msg(std::string msg);   
        ~client(){
            t->join();
            t2->join();
            WSACleanup();
        }
        void recv_msg();
        void passer();
        std::thread* t,*t2;     
};