#include"user_management.h"

// 用户ID计数器，用于自动分配用户ID
static int user_id_counter = 1000;

// 用户信息录入相关函数

// 创建新用户
user* create_user(char* name, int sex, long long phone_num, int age, int status) {
    // 验证用户信息
    if (!validate_user_info(name, sex, phone_num, age, status)) {
        return NULL;
    }

    // 分配内存
    user* new_user = (user*)malloc(sizeof(user));
    if (new_user == NULL) {
        printf("内存分配失败！\n");
        return NULL;
    }

    // 初始化用户信息
    strcpy(new_user->name, name);
    new_user->sex = sex;
    new_user->phone_num = phone_num;
    new_user->age = age;
    new_user->id = user_id_counter++;
    new_user->count = 0; // 初始化计数为0
    new_user->status = status;
    new_user->next = NULL;
    new_user->pre = NULL;

    return new_user;
}

// 添加用户到链表
void add_user(user* head, user* new_user) {
    if (head == NULL || new_user == NULL) {
        return;
    }

    // 找到链表尾部
    user* current = head;
    while (current->next != NULL) {
        current = current->next;
    }

    // 添加新用户到链表尾部
    current->next = new_user;
    new_user->pre = current;
    new_user->next = NULL;
}

// 验证用户信息
bool validate_user_info(char* name, int sex, long long phone_num, int age, int status) {
    // 验证姓名
    if (name == NULL || strlen(name) == 0 || strlen(name) > 19) {
        printf("姓名不能为空且长度不能超过19个字符！\n");
        return false;
    }

    // 验证性别（0为女性，1为男性）
    if (sex != 0 && sex != 1) {
        printf("性别输入错误，请输入0（女）或1（男）！\n");
        return false;
    }

    // 验证电话号码（简单验证11位）
    if (phone_num < 10000000000LL || phone_num > 99999999999LL) {
        printf("电话号码必须为11位！\n");
        return false;
    }

    // 验证年龄
    if (age < 0 || age > 150) {
        printf("年龄必须在0-150之间！\n");
        return false;
    }

    // 验证用户状态
    if (status < 0 || status > 4) {
        printf("用户状态必须在0-4之间！\n");
        return false;
    }

    return true;
}

// 用户信息查询相关函数

// 根据ID查找用户
user* find_user_by_id(user* head, int id) {
    if (head == NULL) {
        return NULL;
    }

    user* current = head->next; // 跳过头节点
    while (current != NULL) {
        if (current->id == id) {
            return current;
        }
        current = current->next;
    }

    return NULL; // 未找到
}

// 根据姓名查找用户
user* find_user_by_name(user* head, char* name) {
    if (head == NULL || name == NULL) {
        return NULL;
    }

    user* current = head->next; // 跳过头节点
    while (current != NULL) {
        if (strcmp(current->name, name) == 0) {
            return current;
        }
        current = current->next;
    }

    return NULL; // 未找到
}

// 根据电话号码查找用户
user* find_user_by_phone(user* head, long long phone_num) {
    if (head == NULL) {
        return NULL;
    }

    user* current = head->next; // 跳过头节点
    while (current != NULL) {
        if (current->phone_num == phone_num) {
            return current;
        }
        current = current->next;
    }

    return NULL; // 未找到
}

// 显示用户信息
void display_user(user* user_info) {
    if (user_info == NULL) {
        printf("用户不存在！\n");
        return;
    }

    printf("\n用户信息：\n");
    printf("ID: %d\n", user_info->id);
    printf("姓名: %s\n", user_info->name);
    printf("性别: %s\n", user_info->sex == 0 ? "女" : "男");
    printf("电话: %lld\n", user_info->phone_num);
    printf("年龄: %d\n", user_info->age);
    printf("使用次数: %d\n", user_info->count);
    printf("用户级别: %s\n", get_status_name(user_info->status));
}

// 用户信息修改相关函数

// 修改用户姓名
bool update_user_name(user* user_info, char* new_name) {
    if (user_info == NULL || new_name == NULL || strlen(new_name) == 0 || strlen(new_name) > 19) {
        printf("用户不存在或姓名格式错误！\n");
        return false;
    }

    strcpy(user_info->name, new_name);
    printf("用户姓名已更新为：%s\n", new_name);
    return true;
}

// 修改用户电话
bool update_user_phone(user* user_info, long long new_phone) {
    if (user_info == NULL || new_phone < 10000000000LL || new_phone > 99999999999LL) {
        printf("用户不存在或电话号码格式错误！\n");
        return false;
    }

    user_info->phone_num = new_phone;
    printf("用户电话已更新为：%lld\n", new_phone);
    return true;
}

// 修改用户状态
bool update_user_status(user* user_info, int new_status) {
    if (user_info == NULL || new_status < 0 || new_status > 4) {
        printf("用户不存在或状态码错误！\n");
        return false;
    }

    user_info->status = new_status;
    printf("用户级别已更新为：%s\n", get_status_name(new_status));
    return true;
}

// 用户信息删除相关函数

// 删除用户
bool delete_user(user* head, int id) {
    if (head == NULL) {
        return false;
    }

    user* current = head->next;
    while (current != NULL) {
        if (current->id == id) {
            // 找到要删除的节点，调整前后节点的指针
            current->pre->next = current->next;
            if (current->next != NULL) {
                current->next->pre = current->pre;
            }

            // 释放内存
            free(current);
            printf("用户(ID: %d)已成功删除！\n", id);
            return true;
        }
        current = current->next;
    }

    printf("未找到ID为%d的用户！\n", id);
    return false;
}

// 用户级别管理相关函数

// 计算费用（根据用户级别应用不同折扣）
float calculate_fee(user* user_info, float base_fee) {
    if (user_info == NULL || base_fee < 0) {
        return base_fee;
    }

    float discount = get_discount_rate(user_info->status);
    return base_fee * discount;
}

// 获取用户状态名称
const char* get_status_name(int status) {
    switch (status) {
    case 0:
        return "普通用户";  // 直接返回，无需转换
    case 1:
        return "教师";
    case 2:
        return "老人";
    case 3:
        return "学生";
    case 4:
        return "SVIP";
    default:
        return "未知状态";
    }
}


// 获取用户折扣率
float get_discount_rate(int status) {
    switch (status) {
    case 0: // 普通用户
        return 1.0f;
    case 1: // 教师
        return 0.9f;
    case 2: // 老人
        return 0.8f;
    case 3: // 学生
        return 0.7f;
    case 4: // SVIP
        return 0.6f;
    default:
        return 1.0f;
    }
}

// 用户链表管理相关函数

// 初始化用户链表
user* init_user_list() {
    user* head = (user*)malloc(sizeof(user));
    if (head == NULL) {
        printf("内存分配失败！\n");
        return NULL;
    }

    // 初始化头节点
    memset(head, 0, sizeof(user));
    head->next = NULL;
    head->pre = NULL;

    return head;
}

// 释放用户链表
void free_user_list(user* head) {
    if (head == NULL) {
        return;
    }

    user* current = head;
    user* next;

    while (current != NULL) {
        next = current->next;
        free(current);
        current = next;
    }
}

// 保存用户数据到文件
void save_users_to_file(user* head, const char* filename) {
    if (head == NULL || filename == NULL) {
        return;
    }

    FILE* file = fopen(filename, "wb");
    if (file == NULL) {
        printf("无法打开文件 %s 进行写入！\n", filename);
        return;
    }

    user* current = head->next; // 跳过头节点
    while (current != NULL) {
        fwrite(current, sizeof(user), 1, file);
        current = current->next;
    }

    fclose(file);
    printf("用户数据已保存到文件 %s\n", filename);
}

// 从文件加载用户数据
user* load_users_from_file(const char* filename) {
    if (filename == NULL) {
        return NULL;
    }

    FILE* file = fopen(filename, "rb");
    if (file == NULL) {
        printf("无法打开文件 %s 进行读取！\n", filename);
        return NULL;
    }

    // 初始化用户链表
    user* head = init_user_list();
    if (head == NULL) {
        fclose(file);
        return NULL;
    }

    user temp;
    user* current = head;

    // 读取文件中的用户数据
    while (fread(&temp, sizeof(user), 1, file) == 1) {
        user* new_user = (user*)malloc(sizeof(user));
        if (new_user == NULL) {
            printf("内存分配失败！\n");
            free_user_list(head);
            fclose(file);
            return NULL;
        }

        // 复制用户数据
        memcpy(new_user, &temp, sizeof(user));
        new_user->next = NULL;

        // 添加到链表
        current->next = new_user;
        new_user->pre = current;
        current = new_user;

        // 更新ID计数器
        if (new_user->id >= user_id_counter) {
            user_id_counter = new_user->id + 1;
        }
    }

    fclose(file);
    printf("已从文件 %s 加载用户数据\n", filename);
    return head;
}