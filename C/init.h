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
//�궨����

//�û��˺궨����



const int max_storey = 20;//����ÿһ���������



struct package {
	//int id;
	struct p_code {
		int id_1;
		int id_2;
		int id_3;
	};
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