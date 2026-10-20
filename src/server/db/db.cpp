#include "db.h"
#include <muduo/base/Logging.h>

//数据库配置消息
static string server="127.0.0.1";
static string user="";
static string password="";
static string dbname="chat";

//初始化数据库连接
MySQL::MySQL(){
    _conn=mysql_init(nullptr);//获取连接mysql数据库的句柄
}

//释放数据库连接
MySQL::~MySQL(){
    if(_conn!=nullptr){
        mysql_close(_conn);
    }
}

//连接数据库
bool MySQL::connect(){
    MYSQL *p=mysql_real_connect(_conn,server.c_str(),user.c_str(),
                                password.c_str(),dbname.c_str(),3306,nullptr,0);//连接数据库
    if(p!=nullptr){
        // C和C++代码默认的编码字符是ASCII，如果不设置，从MySQL上拉下来的中文显示？
        mysql_query(_conn,"set names utf8mb4");

        LOG_INFO<<"connect mysql success!";       
    }
    else{
        LOG_INFO<<"connect mysql fail";
    }
    return p;
}

//更新操作,负责插入删除两种操作
bool MySQL::update(string sql){
   if(mysql_query(_conn,sql.c_str())){
    LOG_INFO << __FILE__ << ":" << __LINE__ << ":"
                 << sql << "更新失败!";
        return false;
   }
   return true;
}

//查询操作
MYSQL_RES *MySQL::query(string sql){
    if(mysql_query(_conn,sql.c_str())){
         LOG_INFO << __FILE__ << ":" << __LINE__ << ":"
                 << sql << "查询失败!";
        return nullptr;
    }
    return mysql_use_result(_conn);
}

//获取连接
MYSQL* MySQL::getConnection(){
    return _conn;
}