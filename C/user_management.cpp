#include "user_management.h"

// 哈希函数实现
unsigned int hash_string(const char* str) {
    unsigned int hash = 0;
    while (*str) {
        hash = hash * 31 + (*str++);
    }
    return hash % HASH_SIZE;
}

unsigned int hash_phone(long long phone) {
    // 使用简单的除留余数法
    return (unsigned int)(phone % HASH_SIZE);
}

// 哈希表操作实现
user_hash_table* init_hash_table() {
    user_hash_table* table = (user_hash_table*)malloc(sizeof(user_hash_table));
    if (table == NULL) {
        return NULL;
    }

    // 初始化所有桶为NULL
    for (int i = 0; i < HASH_SIZE; i++) {
        table->buckets[i] = NULL;
    }

    return table;
}

void insert_user_to_hash(user_hash_table* table, user* user_info) {
    if (table == NULL || user_info == NULL) {
        return;
    }

    // 使用姓名哈希作为主键
    unsigned int index = hash_string(user_info->name);

    // 创建新节点
    user_node* new_node = (user_node*)malloc(sizeof(user_node));
    if (new_node == NULL) {
        return;
    }

    new_node->user = user_info;
    new_node->next = table->buckets[index];
    table->buckets[index] = new_node;
}

user* find_user_by_name_hash(user_hash_table* table, const char* name) {
    if (table == NULL || name == NULL) {
        return NULL;
    }

    unsigned int index = hash_string(name);
    user_node* current = table->buckets[index];

    while (current != NULL) {
        if (strcmp(current->user->name, name) == 0) {
            return current->user;
        }
        current = current->next;
    }

    return NULL;
}

user* find_user_by_id_hash(user_hash_table* table, int id) {
    if (table == NULL) {
        return NULL;
    }

    // 遍历所有桶
    for (int i = 0; i < HASH_SIZE; i++) {
        user_node* current = table->buckets[i];
        while (current != NULL) {
            if (current->user->id == id) {
                return current->user;
            }
            current = current->next;
        }
    }

    return NULL;
}

user* find_user_by_phone_hash(user_hash_table* table, long long phone) {
    if (table == NULL) {
        return NULL;
    }

    unsigned int index = hash_phone(phone);
    user_node* current = table->buckets[index];

    while (current != NULL) {
        if (current->user->phone_num == phone) {
            return current->user;
        }
        current = current->next;
    }

    return NULL;
}

void display_user_hash(user_hash_table* table) {
    if (table == NULL) {
        printf("哈希表为空\n");
        return;
    }

    printf("用户信息列表:\n");
    printf("%-10s %-6s %-15s %-6s %-6s %-15s\n", "姓名", "性别", "电话", "年龄", "ID", "状态");

    for (int i = 0; i < HASH_SIZE; i++) {
        user_node* current = table->buckets[i];
        while (current != NULL) {
            user* user_info = current->user;
            printf("%-10s %-6s %-15lld %-6d %-6d %-15s\n",
                user_info->name,
                user_info->sex ? "男" : "女",
                user_info->phone_num,
                user_info->age,
                user_info->id,
                get_status_name(user_info->status));
            current = current->next;
        }
    }
}

void remove_user_from_hash(user_hash_table* table, user* user_info) {
    if (table == NULL || user_info == NULL) {
        return;
    }

    unsigned int index = hash_string(user_info->name);
    user_node* current = table->buckets[index];
    user_node* prev = NULL;

    while (current != NULL) {
        if (current->user == user_info) {
            if (prev == NULL) {
                // 如果是链表的第一个节点
                table->buckets[index] = current->next;
            }
            else {
                prev->next = current->next;
            }
            free(current);
            return;
        }
        prev = current;
        current = current->next;
    }
}

void free_hash_table(user_hash_table* table) {
    if (table == NULL) {
        return;
    }

    for (int i = 0; i < HASH_SIZE; i++) {
        user_node* current = table->buckets[i];
        while (current != NULL) {
            user_node* temp = current;
            current = current->next;
            free(temp);
        }
        table->buckets[i] = NULL;
    }

    free(table);
}

// 用户信息录入实现
int id_cnt = 0;
user* create_user(char* name, int sex, long long phone_num, int age, int status) {
    if (!validate_user_info(name, sex, phone_num, age, status)) {
        return NULL;
    }

    user* new_user = (user*)malloc(sizeof(user));
    if (new_user == NULL) {
        return NULL;
    }

    strcpy(new_user->name, name);
    new_user->sex = sex;
    new_user->phone_num = phone_num;
    new_user->age = age;
    new_user->status = status;

    // 生成一个随机的4位ID
    new_user->id =id_cnt++;

    // 初始化取件码链表
    new_user->p_code_list = NULL;
    new_user->package_quantity = 0;
    new_user->next = NULL;
    new_user->pre = NULL;

    return new_user;
}

void add_user(user* head, user* new_user) {
    if (head == NULL || new_user == NULL) {
        return;
    }

    // 将新用户添加到链表末尾
    user* current = head;
    while (current->next != NULL) {
        current = current->next;
    }

    current->next = new_user;
    new_user->pre = current;
    new_user->next = NULL;
}

bool validate_user_info(char* name, int sex, long long phone_num, int age, int status) {
    // 验证姓名
    if (name == NULL || strlen(name) == 0 || strlen(name) > 19) {
        printf("姓名不合法\n");
        return false;
    }

    // 验证性别
    if (sex != 0 && sex != 1) {
        printf("性别不合法，0表示女性，1表示男性\n");
        return false;
    }

    // 验证手机号
    if (phone_num < 10000000000LL || phone_num > 19999999999LL) {
        printf("手机号不合法，应为11位数字\n");
        return false;
    }

    // 验证年龄
    if (age < 0 || age > 120) {
        printf("年龄不合法\n");
        return false;
    }

    // 验证状态
    if (status < 0 || status > 4) {
        printf("用户状态不合法，0-4之间\n");
        return false;
    }

    return true;
}

// 用户信息修改实现
bool update_user_name(user* user_info, char* new_name) {
    if (user_info == NULL || new_name == NULL || strlen(new_name) == 0 || strlen(new_name) > 19) {
        return false;
    }

    strcpy(user_info->name, new_name);
    return true;
}

bool update_user_phone(user* user_info, long long new_phone) {
    if (user_info == NULL || new_phone < 10000000000LL || new_phone > 19999999999LL) {
        return false;
    }

    user_info->phone_num = new_phone;
    return true;
}

bool update_user_status(user* user_info, int new_status) {
    if (user_info == NULL || new_status < 0 || new_status > 4) {
        return false;
    }

    user_info->status = new_status;
    return true;
}

// 用户信息删除实现
bool delete_user_by_id(user* head, int id) {
    if (head == NULL) {
        return false;
    }

    user* current = head->next; // 跳过头节点

    while (current != NULL) {
        if (current->id == id) {
            // 从链表中删除
            if (current->pre != NULL) {
                current->pre->next = current->next;
            }
            if (current->next != NULL) {
                current->next->pre = current->pre;
            }

            // 释放取件码链表
            p_code* code = current->p_code_list;
            while (code != NULL) {
                p_code* temp = code;
                code = code->next;
                free(temp);
            }

            free(current);
            return true;
        }
        current = current->next;
    }

    return false;
}

bool delete_user_by_name(user* head, char* name) {
    if (head == NULL || name == NULL) {
        return false;
    }

    user* current = head->next; // 跳过头节点

    while (current != NULL) {
        if (strcmp(current->name, name) == 0) {
            // 从链表中删除
            if (current->pre != NULL) {
                current->pre->next = current->next;
            }
            if (current->next != NULL) {
                current->next->pre = current->pre;
            }

            // 释放取件码链表
            p_code* code = current->p_code_list;
            while (code != NULL) {
                p_code* temp = code;
                code = code->next;
                free(temp);
            }

            free(current);
            return true;
        }
        current = current->next;
    }

    return false;
}

bool delete_user_by_phone(user* head, long long phone_num) {
    if (head == NULL) {
        return false;
    }

    user* current = head->next; // 跳过头节点

    while (current != NULL) {
        if (current->phone_num == phone_num) {
            // 从链表中删除
            if (current->pre != NULL) {
                current->pre->next = current->next;
            }
            if (current->next != NULL) {
                current->next->pre = current->pre;
            }

            // 释放取件码链表
            p_code* code = current->p_code_list;
            while (code != NULL) {
                p_code* temp = code;
                code = code->next;
                free(temp);
            }

            free(current);
            return true;
        }
        current = current->next;
    }

    return false;
}

// 用户级别管理实现
float calculate_fee(user* user_info, float base_fee) {
    if (user_info == NULL || base_fee < 0) {
        return base_fee;
    }

    float discount = get_discount_rate(user_info->status);
    return base_fee * discount;
}

const char* get_status_name(int status) {
    switch (status) {
    case 0: return "普通用户";
    case 1: return "教师";
    case 2: return "老人";
    case 3: return "学生";
    case 4: return "SVIP";
    default: return "未知状态";
    }
}

float get_discount_rate(int status) {
    switch (status) {
    case 0: return 1.0f;      // 普通用户无折扣
    case 1: return 0.9f;      // 教师9折
    case 2: return 0.8f;      // 老人8折
    case 3: return 0.85f;     // 学生8.5折
    case 4: return 0.75f;     // SVIP 7.5折
    default: return 1.0f;
    }
}

// 用户链表管理实现
user* init_user_list() {
    user* head = (user*)malloc(sizeof(user));
    if (head == NULL) {
        return NULL;
    }

    // 创建一个空的头节点
    memset(head, 0, sizeof(user));
    head->next = NULL;
    head->pre = NULL;

    return head;
}

void free_user_list(user* head) {
    if (head == NULL) {
        return;
    }

    user* current = head;
    while (current != NULL) {
        user* temp = current;
        current = current->next;

        // 释放取件码链表
        p_code* code = temp->p_code_list;
        while (code != NULL) {
            p_code* code_temp = code;
            code = code->next;
            free(code_temp);
        }

        free(temp);
    }
}

void save_users_to_file(user* head, const char* filename) {
    if (head == NULL || filename == NULL) {
        return;
    }

    // 构造用户文件和取件码文件的路径
    char user_file[256] = "user.txt";
    char pcode_file[256] = "p_code.txt";

    // 保存用户信息
    FILE* user_fp = fopen(user_file, "wb");
    if (user_fp == NULL) {
        printf("无法打开文件 %s 进行写入\n", user_file);
        return;
    }

    // 保存取件码信息
    FILE* pcode_fp = fopen(pcode_file, "wb");
    if (pcode_fp == NULL) {
        printf("无法打开文件 %s 进行写入\n", pcode_file);
        fclose(user_fp);
        return;
    }

    user* current = head->next; // 跳过头节点
    while (current != NULL) {
        // 保存用户基本信息
        fwrite(current, sizeof(user), 1, user_fp);

        // 保存取件码信息
        fprintf(pcode_fp, "%d ", current->id); // 写入用户ID

        // 统计并保存取件码数量
        int code_count = 0;
        p_code* code = current->p_code_list;
        while (code != NULL) {
            code_count++;
            code = code->next;
        }
        fprintf(pcode_fp, "%d ", code_count);

        // 保存取件码
        code = current->p_code_list;
        while (code != NULL) {
            fprintf(pcode_fp, "%d %d %d ", code->id_1, code->id_2, code->id_3);
            code = code->next;
        }
        fprintf(pcode_fp, "\n");

        current = current->next;
    }

    fclose(user_fp);
    fclose(pcode_fp);
}

user* load_users_from_file(const char* filename) {
    // 构造用户文件和取件码文件的路径
    char user_file[256] = "user.txt";
    char pcode_file[256] = "p_code.txt";

    // 打开用户信息文件
    FILE* user_fp = fopen(user_file, "rb");
    if (user_fp == NULL) {
        printf("无法打开文件 %s 进行读取，将创建新文件\n", user_file);
        // 如果文件不存在，初始化一个空的用户链表
        return init_user_list();
    }

    // 初始化用户链表
    user* head = init_user_list();
    if (head == NULL) {
        fclose(user_fp);
        return NULL;
    }

    user* current = head;
    user temp;

    // 读取用户基本信息
    while (fread(&temp, sizeof(user), 1, user_fp) == 1) {
        user* new_user = (user*)malloc(sizeof(user));
        if (new_user == NULL) {
            free_user_list(head);
            fclose(user_fp);
            return NULL;
        }

        *new_user = temp;
        new_user->next = NULL;
        new_user->pre = current;
        new_user->p_code_list = NULL;

        current->next = new_user;
        current = new_user;
    }

    fclose(user_fp);

    // 打开取件码文件
    FILE* pcode_fp = fopen(pcode_file, "rb");
    if (pcode_fp == NULL) {
        printf("无法打开文件 %s 进行读取\n", pcode_file);
        return head; // 返回只有用户信息的链表
    }

    // 读取取件码信息
    int user_id, code_count;
    while (fscanf(pcode_fp, "%d %d", &user_id, &code_count) == 2) {
        // 查找对应的用户
        user* current_user = head->next;
        while (current_user != NULL) {
            if (current_user->id == user_id) {
                // 读取该用户的所有取件码
                p_code* code_current = NULL;
                for (int i = 0; i < code_count; i++) {
                    p_code* new_code = (p_code*)malloc(sizeof(p_code));
                    if (new_code == NULL) continue;

                    fscanf(pcode_fp, "%d %d %d", &new_code->id_1, &new_code->id_2, &new_code->id_3);
                    new_code->next = NULL;

                    if (i == 0) {
                        current_user->p_code_list = new_code;
                        code_current = new_code;
                    }
                    else {
                        code_current->next = new_code;
                        code_current = new_code;
                    }
                }
                break;
            }
            current_user = current_user->next;
        }
        fscanf(pcode_fp, " "); // 读取换行符
    }

    fclose(pcode_fp);
    return head;
}

// 用户的取件码管理实现
void add_pick_up_code(user* user_info, p_code* code) {
    if (user_info == NULL || code == NULL) {
        return;
    }

    code->next = NULL;

    if (user_info->p_code_list == NULL) {
        user_info->p_code_list = code;
    }
    else {
        p_code* current = user_info->p_code_list;
        while (current->next != NULL) {
            current = current->next;
        }
        current->next = code;
    }

    user_info->package_quantity++;
}

void remove_pick_up_code(user* user_info, p_code* code) {
    if (user_info == NULL || code == NULL || user_info->p_code_list == NULL) {
        return;
    }

    p_code* current = user_info->p_code_list;
    p_code* prev = NULL;

    while (current != NULL) {
        if (current->id_1 == code->id_1 && current->id_2 == code->id_2 && current->id_3 == code->id_3) {
            if (prev == NULL) {
                // 如果是链表的第一个节点
                user_info->p_code_list = current->next;
            }
            else {
                prev->next = current->next;
            }

            free(current);
            user_info->package_quantity--;
            return;
        }

        prev = current;
        current = current->next;
    }
}

void display_user_pick_up_codes(user* user_info) {
    if (user_info == NULL) {
        return;
    }

    printf("%s 的取件码列表:\n", user_info->name);

    if (user_info->p_code_list == NULL) {
        printf("暂无取件码\n");
        return;
    }

    p_code* current = user_info->p_code_list;
    int count = 1;

    while (current != NULL) {
        printf("取件码 %d: %d-%d-%d\n", count, current->id_1, current->id_2, current->id_3);
        current = current->next;
        count++;
    }

    printf("共有 %d 个取件码\n", user_info->package_quantity);
}