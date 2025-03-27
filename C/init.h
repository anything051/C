#pragma once
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
//宏定义区

//用户端宏定义区



const int max_storey = 20;//货架每一层最大容量



struct package {
	//int id;
	struct p_code {
		int id_1;
		int id_2;
		int id_3;
	};
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

struct user {

	char name[20];
	int sex;
	long long phone_num;
	int age;
	int id;
	int count;
	int status;
	/*EVERYONE = 0,
	TEACHER = 1,
	OLDER = 2,
	STUDENT = 3,
	SVIP = 4*/

	struct user* next;
	struct user* pre;
};