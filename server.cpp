#include "server.h"

int server::wsa_setup(){
    int code=WSAStartup(MAKEWORD(2,2),&wsa);
    return code;
}

server::server(std::string ip,int port):ip(ip),port(port){
    int code=this->wsa_setup();
    if(code!=0){
        std::cerr<<"WSAStartup failed with error: "<<code<<std::endl;
        exit(1);
    }
    server_socket=socket(AF_INET,SOCK_STREAM,0);
    if(server_socket==INVALID_SOCKET){
        std::cerr<<"socket failed with error: "<<WSAGetLastError()<<std::endl;
        exit(1);
    }
    server_path.sin_family=AF_INET;
    server_path.sin_port=htons(port);
    server_path.sin_addr.s_addr=inet_addr(ip.c_str());

    bind(server_socket,(sockaddr*)&server_path,sizeof(server_path));

    t1=new std::thread(&server::lissen,this);
    t2=new std::thread(&server::recv_msg,this);

    std::cout<<"Waiting for a connection...\n";

}

void server::send_msg(std::string msg){
    for(std::shared_ptr<SOCKET> c:clint_sockets){
        send(*c,msg.c_str(),msg.size(),0);
    }
}

void server::recv_msg(){
    
    while (1){
        for(std::shared_ptr<SOCKET> sock:clint_sockets){// lot of bug there :( fix me ;
                // std::cout<<"lisening...\n";
                // Sleep(1000);
                char msg[1024]={0};
                recv(*sock,msg,1024,0);
                
                std::string m(msg);
                std::string m2("@pass#;");
                filter obj(m,m2);
                obj.run();
                std::string data=obj.get_filterd_word();
                if(data==""|| data==" "){
                    continue;
                }
                bool x=false;
                for(int i=0;i<data.size();i++){
                    if(data[i]!=' '){
                        x=true;
                    }
                }
                if(x){std::cout<<"messege: "<<data<<std::endl;}

            // ? if user left form client app, when this code line mush be run 
            //      ;  clint_sockets.erase(clint_sockets.begin()+c,clint_sockets.begin()+c+1);
            //      ;  continue;
            // fix me :(
        }
    }
}

void server::lissen(){
    while(true){

        listen(server_socket,10);

        int LEN=sizeof(clint_path);
        
        SOCKET clint_socket=accept(server_socket,(sockaddr*)&clint_path,&LEN);
        
        if(clint_socket==INVALID_SOCKET){
            std::cerr<<"accept failed with error: "<<WSAGetLastError()<<std::endl;
            exit(1);
        }

        std::shared_ptr<SOCKET> sock =std::make_shared<SOCKET>(clint_socket);

        clint_sockets.push_back(sock);
        std::cout<<"user:"<<clint_sockets.size()<<std::endl;
        std::cout<<"new user loging..."<<std::endl;
    }
}
