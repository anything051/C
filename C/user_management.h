#pragma once

#define _CRT_SECURE_NO_WARNINGS
#include"init.h"

// ����״̬��������
static const char* status_names[] = {
    "��ͨ�û�", // status = 0
    "��ʦ",     // status = 1
    "����",     // status = 2
    "ѧ��",     // status = 3
    "SVIP"      // status = 4
};

// �û�����
//���ܺ���

//�û���Ϣ¼�룺ʵ�����û���Ϣ��¼�빦�ܣ�����������֤��
user* create_user(char* name, int sex, long long phone_num, int age, int status);
void add_user(user* head, user* new_user);
bool validate_user_info(char* name, int sex, long long phone_num, int age, int status);

//�û���Ϣ��ѯ��֧�ָ����û�ID��������������ѯ�û���Ϣ��
user* find_user_by_id(user* head, int id);
user* find_user_by_name(user* head, char* name);
user* find_user_by_phone(user* head, long long phone_num);
void display_user(user* user_info);

//�û���Ϣ�޸ģ������޸��û��Ĳ�����Ϣ������ϵ��ʽ�ȡ�
bool update_user_name(user* user_info, char* new_name);
bool update_user_phone(user* user_info, long long new_phone);
bool update_user_status(user* user_info, int new_status);

//�û���Ϣɾ����ɾ������ʹ�õ��û���Ϣ��
bool delete_user(user* head, int id);

//�û������������ͬ������û������ö�Ӧ�ļƷѷ�ʽ�����㷽ʽ�ȡ�
float calculate_fee(user* user_info, float base_fee);
const char* get_status_name(int status);
float get_discount_rate(int status);

// �û��������
user* init_user_list();
void free_user_list(user* head);
void save_users_to_file(user* head, const char* filename);
user* load_users_from_file(const char* filename);





