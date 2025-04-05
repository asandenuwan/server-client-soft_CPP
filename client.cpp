#include "client.h"

bool client::wsa_setup(){
    int code=WSAStartup(MAKEWORD(2,2),&wsa);
    return code;
}

client::client(std::string ip,int port):server_ip(ip),port(port){
    int code =this->wsa_setup();
    if(code!=0){
        std::cerr<<"WSAStartup failed with error: "<<code<<std::endl;
        exit(1);
    }

    client_socket=socket(AF_INET,SOCK_STREAM,0);
    server_path.sin_family=AF_INET;
    server_path.sin_port=htons(port);
    server_path.sin_addr.s_addr=inet_addr(server_ip.c_str());

    code=connect(client_socket,(sockaddr*)&server_path,sizeof(server_path));
    if(code==SOCKET_ERROR){
        std::cerr<<"connect failed with error: "<<WSAGetLastError()<<std::endl;
        exit(1);
    }

    std::cout<<"Connected to server\n";

    t=new std::thread(&client::recv_msg,this);
    t2=new std::thread(&client::passer,this);
}

void client::recv_msg(){
    
    while(true){
        bool x=false;
        char msg[1024]={0};
        recv(client_socket,msg,1024,0);
        for(char i:msg){
            if(i!=' '){
                x=true;
            }
        }
        if(x){std::cout<<"message: "<<"{"<<msg<<"}"<<std::endl;}
        
    }
}

void client::send_msg(std::string msg){
    int i=send(client_socket,msg.c_str(),msg.size(),0);   
   
}

void client::passer(){
    while (1){
        std::string data="@pass#;";
        this->send_msg(data);
        Sleep(500);
    }  
}