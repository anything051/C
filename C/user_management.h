#pragma once

#include"init.h"

// 用户管理
//功能函数

// 哈希函数
unsigned int hash_string(const char* str);
unsigned int hash_phone(long long phone);

user_hash_table* init_hash_table();//初始化哈希表
void insert_user_to_hash(user_hash_table* table, user* user_info);//将用户信息添加到哈希表中
// 通过哈希表管理增删改查用户信息

//用户信息查询：支持根据用户ID、姓名等条件查询到用户。
user* find_user_by_name_hash(user_hash_table* table, const char* name);//通过姓名查找用户
user* find_user_by_id_hash(user_hash_table* table, int id);//通过ID查找用户
user* find_user_by_phone_hash(user_hash_table* table, long long phone);//通过手机号查找用户
void display_user_hash(user_hash_table* table);//显示哈希表中的所有用户信息
void remove_user_from_hash(user_hash_table* table, user* user_info);//从哈希表中删除用户信息
void free_hash_table(user_hash_table* table);//释放哈希表

//用户信息录入：实现新用户信息的录入功能，包括输入验证。
user* create_user(char* name, int sex, long long phone_num, int age, int status);//创建新用户
void add_user(user* head, user* new_user);//将新用户添加到用户链表中
bool validate_user_info(char* name, int sex, long long phone_num, int age, int status);//验证用户信息是否合法

//用户信息修改：允许修改用户的部分信息，如联系方式等。
bool update_user_name(user* user_info, char* new_name);
bool update_user_phone(user* user_info, long long new_phone);
bool update_user_status(user* user_info, int new_status);

//用户信息删除：删除不再使用的用户信息。
bool delete_user_by_id(user* head, int id);//删除用户信息
bool delete_user_by_name(user* head, char* name);//删除用户信息
bool delete_user_by_phone(user* head, long long phone_num);//删除用户信息

//用户级别管理：管理不同级别的用户，设置对应的计费方式、结算方式等。
float calculate_fee(user* user_info, float base_fee);//计算用户的费用，基础费用*折扣
const char* get_status_name(int status);//获取用户的状态名称
float get_discount_rate(int status);//获取用户的折扣率

// 用户链表管理
user* init_user_list();//初始化用户链表
void free_user_list(user* head);//释放用户链表
void save_users_to_file(user* head, const char* filename);//将用户信息保存到文件中
user* load_users_from_file(const char* filename);//从文件中加载用户信息

//用户的取件码管理
void add_pick_up_code(user* user_info, p_code* code);//将取件码放入用户的取件码链表中
void remove_pick_up_code(user* user_info, p_code* code);//从用户的取件码链表中删除取件码
void display_user_pick_up_codes(user* user_info);//显示某个用户的取件码




