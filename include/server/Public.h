#ifndef PUBLIC_H
#define PUBLIC_H
/*
server和client的公共文件
*/
/*enum全称enumeration(枚举),作用就是给一组相关的正数常量起上有意义的名字。
枚举里每个名字底层都是一个整数  
*/
enum EnMsgType{
    LOGIN_MSG=1,//登录消息
    LOGIN_MSG_ACK,//登录响应消息
    REG_MSG,//注册消息
    REG_MSG_ACK,//注册响应消息
    ONE_CHAT_MSG,//聊天信息
    ADD_FRIEND_MSG,//添加好友信息
    CREATE_GROUP_MSG,//创建群组
    ADD_GROUP_MSG,//加入群组
    GROUP_CHAT_MSG,//群聊天
    LOGINOUT_MSG,
};
#endif