#include "ChatServer.h"
#include <functional>
#include "json.hpp"
#include <string>
#include "ChatService.h"
using namespace std;
using namespace std::placeholders;
using json=nlohmann::json;
ChatServer::ChatServer(
    EventLoop *loop,
    const InetAddress& ListAddr,
    const string& nameArg)
    :_server(loop,ListAddr,nameArg),_loop(loop)
    {
    //注册连接回调
    _server.setConnectionCallback(std::bind(&ChatServer::onConnection,this,_1));
/*连接或者断开连接后就调用ChatServer中的onConnection函数
  这个bind表示将一个函数和它的一些参数打包成一个新的可调用的对象
  bind在这里是onConnection和别的参数绑定在一起,具体是指this和_1占位符表示的函数
  _1是占位符的一种,_1表示把传入的第一个参数给_1所占的位置
*/
//注册消息回调
    _server.setMessageCallback(std::bind(&ChatServer::onMessage,this,_1,_2,_3));

    //设置线程数量
    _server.setThreadNum(4);
}

//启动服务
void ChatServer::start(){
    _server.start();
}

//上报链接相关信息的回调函数
void ChatServer::onConnection(const TcpConnectionPtr& conn){
     if(!conn->connected()){
        ChatService::instance()->clientCloseException(conn);
        
        conn->shutdown();
     }
}

//上报读写事件相关信息的回调函数
void ChatServer::onMessage(const TcpConnectionPtr& conn,
                           Buffer *buffer,
                           Timestamp time
                          ){
   string buf=buffer->retrieveAllAsString();//将网络上读取到的字符串读取到buf字符串中
   json js=json::parse(buf);//数据的反序列化
   //达到的目的:完全解耦网络模块的代码和业务模块的代码
   //通过js["msgid"]获取=>业务handler=> conn js time
   auto MsgHandler=ChatService::instance()->getHandler(js["msgid"].get<int>());
   //回调消息绑定好的事件处理器,来执行相应的业务处理
   MsgHandler(conn,js,time);//将解析外来信息的工作交给业务层ChatService
}
