-- ============================================================
-- 集群聊天服务器 数据库初始化脚本
-- 数据库名: chat (与 db.cpp 中的 dbname 一致)
-- 用法:     mysql -u fx -p312sdsb < init.sql
-- 说明:     本脚本会先删旧表再重建,可反复执行用于重置数据
-- ============================================================

-- 建库(如果不存在)
CREATE DATABASE IF NOT EXISTS chat DEFAULT CHARACTER SET utf8mb4;
USE chat;

-- 删除旧表(按依赖顺序,保证脚本可重复执行)
DROP TABLE IF EXISTS offlinemessage;
DROP TABLE IF EXISTS groupuser;
DROP TABLE IF EXISTS allgroup;
DROP TABLE IF EXISTS friend;
DROP TABLE IF EXISTS `user`;

-- 1. 用户表 (来自 usermodel.cpp)
--    insert into user(name,password,state) ...   => name, password, state
--    select * from user                          => id, name, password, state
CREATE TABLE `user` (
    `id`       INT PRIMARY KEY AUTO_INCREMENT COMMENT '用户id,自增主键',
    `name`     VARCHAR(50) NOT NULL UNIQUE       COMMENT '用户名',
    `password` VARCHAR(50) NOT NULL              COMMENT '密码',
    `state`    VARCHAR(10) NOT NULL DEFAULT 'offline' COMMENT '在线状态: online/offline'
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4 COMMENT='用户表';

-- 2. 好友关系表 (来自 friendmodel.cpp)
--    insert into friend values(userid, friendid) => userid, friendid
CREATE TABLE `friend` (
    `userid`   INT NOT NULL COMMENT '用户id',
    `friendid` INT NOT NULL COMMENT '好友id'
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4 COMMENT='好友关系表';

-- 3. 群组表 (来自 groupmodel.cpp)
--    insert into allgroup(groupname, groupdesc) ... => groupname, groupdesc
CREATE TABLE `allgroup` (
    `id`        INT PRIMARY KEY AUTO_INCREMENT COMMENT '群id,自增主键',
    `groupname` VARCHAR(50) NOT NULL             COMMENT '群名称',
    `groupdesc` VARCHAR(200) DEFAULT ''          COMMENT '群描述'
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4 COMMENT='群组表';

-- 4. 群成员表 (来自 groupmodel.cpp)
--    insert into groupuser values(groupid, userid, role) => groupid, userid, grouprole
CREATE TABLE `groupuser` (
    `groupid`   INT NOT NULL COMMENT '群id',
    `userid`    INT NOT NULL COMMENT '用户id',
    `grouprole` VARCHAR(10) NOT NULL DEFAULT 'normal' COMMENT '角色: creator/normal'
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4 COMMENT='群成员表';

-- 5. 离线消息表 (来自 offlinemessagemodel.cpp)
--    insert into offlinemessage values(userid, message) => userid, message
CREATE TABLE `offlinemessage` (
    `userid`  INT NOT NULL COMMENT '用户id',
    `message` VARCHAR(500) NOT NULL COMMENT '消息内容(JSON字符串)'
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4 COMMENT='离线消息表';
