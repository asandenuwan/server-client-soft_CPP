#include <iostream>
#include <string>
#include <cstring>
#include <memory>
#include <vector>
#include <thread>
#include <winsock2.h>
#include <windows.h>

#include "msg_filter.h"
//  ; (2+main)  thread running while object in RAM ;

class server{
    protected:
        WSAData wsa;
        SOCKET server_socket=INVALID_SOCKET;
        std::vector<std::shared_ptr<SOCKET>> clint_sockets;
        sockaddr_in server_path;
        sockaddr_in clint_path;
        std::string ip;
        int port;
        
    public:
        server(std::string ip,int port);
        int wsa_setup();    
        void send_msg(std::string msg);
        ~server(){
            t1->join();
            t2->join();  
            WSACleanup();
        }
        void recv_msg();
        void lissen();
        std::thread* t1;
        std::thread* t2;
    };