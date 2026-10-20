#include "ChatServer.h"
#include "ChatService.h"
#include <iostream>
#include <signal.h>
#include <cstdlib>
using namespace std;
//处理服务器ctrl+c结束后,重置user的状态信息
void resetHandler(int){
  ChatService::instance()->reset();
  exit(0);
}

int main(int argc,const char** argv){
    if(argc<3){
      cerr << "command invalid! example: ./ChatServer 127.0.0.1 6000" << endl;
        exit(-1);
    }
    //解析通过命令行参数传递的IP和port
    const char *ip=argv[1];
    uint16_t port=atoi(argv[2]);
    signal(SIGINT,resetHandler);
    EventLoop loop;
    InetAddress addr(ip,port);
    ChatServer server(&loop,addr,"ChatServer");
    server.start();
    loop.loop();
    return 0;
}