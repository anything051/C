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
//宏定义区

//用户端宏定义区



const int max_storey = 20;//货架每一层最大容量

struct p_code {//取件码结构体
	//三个id构建出取件码，实现取件码的唯一性
	int id_1;
	int id_2;
	int id_3;
	struct p_code* next; // 链表指针
};

struct package {
	//int id;

	p_code np_code;//包裹取件码
	int id;//包裹编号 范围从1*10^7到99999999  ///8位数
	char receiver[20];
	long long r_phone;
	char sender[20];
	long long s_phone;
	char nane[10];//包裹内物品名称
	float weight;//单位：kg
	float volume;//体积：dm^
	int state;//包裹当前状态  0：在货架，1：在运输，2：待发送
	int error;//是否处于异常状态
	int distance;//单位：km
	int traffic;//0:陆运，1：海运；2：空运
	int speed;//是否是急速运输
	char starting_point[10];
	char ending_point[10];
	int electron;//电子产品
	int is_liquid;//是不是液态
	int fragile;//是不是易碎品
	//

	package* pre;
	package* next;

};

struct shelf {//货架
	int id;
	struct package* storey[6];//货架每一层
	int num[6];//货架每一层当前包裹数
	int capacity[6];//货架每层已用数量
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
	int sex;//0：女，1：男
	long long phone_num;//11位
	int age;//60岁以上属于老人
	int id;//4位
	int status;//0：普通用户，1：教师，2：老人，3：学生，4：SVIP


	struct p_code* p_code_list; // 待取包裹链表头指针
	int package_quantity; // p_code_list的包裹链表数量//用户待取包裹的数量
	struct user* next;
	struct user* pre;
};