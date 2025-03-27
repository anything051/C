#pragma once

#include"init.h"


// 用户管理
//功能函数

//用户信息录入：实现新用户信息的录入功能，包括输入验证。

//用户信息查询：支持根据用户ID、姓名等条件查询用户信息。

//用户信息修改：允许修改用户的部分信息，如联系方式等。

//用户信息删除：删除不再使用的用户信息。

//用户级别管理：管理不同级别的用户，设置对应的计费方式、结算方式等。

/*会员信息系统层级函数区*/
int user_account(char account[20]);/*个人账户信息*/
void member_log_up();/*会员注册函数*/
int member_log_in(char account[20]);/*会员登录函数*/
void ADMIN_watch_member();/*查看会员信息函数*/
void display_memberbook();/*查看所有图书借阅信息函数*/
int check_repeat_ID(char id_account[20]);/*检查账户重复性函数*/
void find_account();/*账户找回函数*/