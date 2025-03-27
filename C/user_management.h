#pragma once

#define _CRT_SECURE_NO_WARNINGS
#include"init.h"

// 定义状态名称数组
static const char* status_names[] = {
    "普通用户", // status = 0
    "教师",     // status = 1
    "老人",     // status = 2
    "学生",     // status = 3
    "SVIP"      // status = 4
};

// 用户管理
//功能函数

//用户信息录入：实现新用户信息的录入功能，包括输入验证。
user* create_user(char* name, int sex, long long phone_num, int age, int status);
void add_user(user* head, user* new_user);
bool validate_user_info(char* name, int sex, long long phone_num, int age, int status);

//用户信息查询：支持根据用户ID、姓名等条件查询用户信息。
user* find_user_by_id(user* head, int id);
user* find_user_by_name(user* head, char* name);
user* find_user_by_phone(user* head, long long phone_num);
void display_user(user* user_info);

//用户信息修改：允许修改用户的部分信息，如联系方式等。
bool update_user_name(user* user_info, char* new_name);
bool update_user_phone(user* user_info, long long new_phone);
bool update_user_status(user* user_info, int new_status);

//用户信息删除：删除不再使用的用户信息。
bool delete_user(user* head, int id);

//用户级别管理：管理不同级别的用户，设置对应的计费方式、结算方式等。
float calculate_fee(user* user_info, float base_fee);
const char* get_status_name(int status);
float get_discount_rate(int status);

// 用户链表管理
user* init_user_list();
void free_user_list(user* head);
void save_users_to_file(user* head, const char* filename);
user* load_users_from_file(const char* filename);





