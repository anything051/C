#pragma once
#define _CRT_SECURE_NO_WARNINGS
#include <stdint.h>
#include <stdbool.h>
#include <stddef.h>
#include <stdarg.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>
#include <ctype.h>
#include <assert.h>
#include <errno.h>
#include <fcntl.h>
#include <limits.h>
#include <locale.h>
#include <signal.h>
#include <stdarg.h>
#include <stddef.h>
#include <stdint.h>
#include<stdio.h>
#include<fstream>
//�궨����

//�û��˺궨����



const int max_storey = 20;//����ÿһ���������

struct p_code {//ȡ����ṹ��
	//����id������ȡ���룬ʵ��ȡ�����Ψһ��
	int id_1;
	int id_2;
	int id_3;
	struct p_code* next; // ����ָ��
};

struct package {
	//int id;

	p_code np_code;//����ȡ����
	int id;//������� ��Χ��1*10^7��99999999  ///8λ��
	char receiver[20];
	long long r_phone;
	char sender[20];
	long long s_phone;
	char nane[10];//��������Ʒ����
	float weight;//��λ��kg
	float volume;//�����dm^
	int state;//������ǰ״̬  0���ڻ��ܣ�1�������䣬2��������
	int error;//�Ƿ����쳣״̬
	int distance;//��λ��km
	int traffic;//0:½�ˣ�1�����ˣ�2������
	int speed;//�Ƿ��Ǽ�������
	char starting_point[10];
	char ending_point[10];
	int electron;//���Ӳ�Ʒ
	int is_liquid;//�ǲ���Һ̬
	int fragile;//�ǲ�������Ʒ
	//

	package* pre;
	package* next;

};

struct shelf {//����
	int id;
	struct package* storey[6];//����ÿһ��
	int num[6];//����ÿһ�㵱ǰ������
	int capacity[6];//����ÿ����������
};

#define HASH_SIZE 1000

struct user_node {
	struct user* user;
	struct user_node* next;
};

struct user_hash_table {
	struct user_node* buckets[HASH_SIZE];
};



struct user {
	char name[20];
	int sex;//0��Ů��1����
	long long phone_num;//11λ
	int age;//60��������������
	int id;//4λ
	int status;//0����ͨ�û���1����ʦ��2�����ˣ�3��ѧ����4��SVIP


	struct p_code* p_code_list; // ��ȡ��������ͷָ��
	int package_quantity; // p_code_list�İ�����������//�û���ȡ����������
	struct user* next;
	struct user* pre;
};