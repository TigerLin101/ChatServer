#ifndef USERMODEL_H
#define USERMODEL_H
#include "user.h"
/*usr表的数据操作类,专门用于处理user表对象
当业务层需要对表进行增删改查时就调用这个类  
*/
class UserModel{
    public:
    //user表的增加方法
    bool insert(User &user);
    User query(int id);
    //更新用户的状态信息
    bool update(User user);
    //重置用户的状态信息
    void resetState();
};
#endif