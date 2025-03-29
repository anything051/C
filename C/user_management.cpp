#include "user_management.h"

// ��ϣ����ʵ��
unsigned int hash_string(const char* str) {
    unsigned int hash = 0;
    while (*str) {
        hash = hash * 31 + (*str++);
    }
    return hash % HASH_SIZE;
}

unsigned int hash_phone(long long phone) {
    // ʹ�ü򵥵ĳ���������
    return (unsigned int)(phone % HASH_SIZE);
}

// ��ϣ�����ʵ��
user_hash_table* init_hash_table() {
    user_hash_table* table = (user_hash_table*)malloc(sizeof(user_hash_table));
    if (table == NULL) {
        return NULL;
    }

    // ��ʼ������ͰΪNULL
    for (int i = 0; i < HASH_SIZE; i++) {
        table->buckets[i] = NULL;
    }

    return table;
}

void insert_user_to_hash(user_hash_table* table, user* user_info) {
    if (table == NULL || user_info == NULL) {
        return;
    }

    // ʹ��������ϣ��Ϊ����
    unsigned int index = hash_string(user_info->name);

    // �����½ڵ�
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

    // ��������Ͱ
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
        printf("��ϣ��Ϊ��\n");
        return;
    }

    printf("�û���Ϣ�б�:\n");
    printf("%-10s %-6s %-15s %-6s %-6s %-15s\n", "����", "�Ա�", "�绰", "����", "ID", "״̬");

    for (int i = 0; i < HASH_SIZE; i++) {
        user_node* current = table->buckets[i];
        while (current != NULL) {
            user* user_info = current->user;
            printf("%-10s %-6s %-15lld %-6d %-6d %-15s\n",
                user_info->name,
                user_info->sex ? "��" : "Ů",
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
                // ���������ĵ�һ���ڵ�
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

// �û���Ϣ¼��ʵ��
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

    // ����һ�������4λID
    new_user->id =id_cnt++;

    // ��ʼ��ȡ��������
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

    // �����û���ӵ�����ĩβ
    user* current = head;
    while (current->next != NULL) {
        current = current->next;
    }

    current->next = new_user;
    new_user->pre = current;
    new_user->next = NULL;
}

bool validate_user_info(char* name, int sex, long long phone_num, int age, int status) {
    // ��֤����
    if (name == NULL || strlen(name) == 0 || strlen(name) > 19) {
        printf("�������Ϸ�\n");
        return false;
    }

    // ��֤�Ա�
    if (sex != 0 && sex != 1) {
        printf("�Ա𲻺Ϸ���0��ʾŮ�ԣ�1��ʾ����\n");
        return false;
    }

    // ��֤�ֻ���
    if (phone_num < 10000000000LL || phone_num > 19999999999LL) {
        printf("�ֻ��Ų��Ϸ���ӦΪ11λ����\n");
        return false;
    }

    // ��֤����
    if (age < 0 || age > 120) {
        printf("���䲻�Ϸ�\n");
        return false;
    }

    // ��֤״̬
    if (status < 0 || status > 4) {
        printf("�û�״̬���Ϸ���0-4֮��\n");
        return false;
    }

    return true;
}

// �û���Ϣ�޸�ʵ��
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

// �û���Ϣɾ��ʵ��
bool delete_user_by_id(user* head, int id) {
    if (head == NULL) {
        return false;
    }

    user* current = head->next; // ����ͷ�ڵ�

    while (current != NULL) {
        if (current->id == id) {
            // ��������ɾ��
            if (current->pre != NULL) {
                current->pre->next = current->next;
            }
            if (current->next != NULL) {
                current->next->pre = current->pre;
            }

            // �ͷ�ȡ��������
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

    user* current = head->next; // ����ͷ�ڵ�

    while (current != NULL) {
        if (strcmp(current->name, name) == 0) {
            // ��������ɾ��
            if (current->pre != NULL) {
                current->pre->next = current->next;
            }
            if (current->next != NULL) {
                current->next->pre = current->pre;
            }

            // �ͷ�ȡ��������
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

    user* current = head->next; // ����ͷ�ڵ�

    while (current != NULL) {
        if (current->phone_num == phone_num) {
            // ��������ɾ��
            if (current->pre != NULL) {
                current->pre->next = current->next;
            }
            if (current->next != NULL) {
                current->next->pre = current->pre;
            }

            // �ͷ�ȡ��������
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

// �û��������ʵ��
float calculate_fee(user* user_info, float base_fee) {
    if (user_info == NULL || base_fee < 0) {
        return base_fee;
    }

    float discount = get_discount_rate(user_info->status);
    return base_fee * discount;
}

const char* get_status_name(int status) {
    switch (status) {
    case 0: return "��ͨ�û�";
    case 1: return "��ʦ";
    case 2: return "����";
    case 3: return "ѧ��";
    case 4: return "SVIP";
    default: return "δ֪״̬";
    }
}

float get_discount_rate(int status) {
    switch (status) {
    case 0: return 1.0f;      // ��ͨ�û����ۿ�
    case 1: return 0.9f;      // ��ʦ9��
    case 2: return 0.8f;      // ����8��
    case 3: return 0.85f;     // ѧ��8.5��
    case 4: return 0.75f;     // SVIP 7.5��
    default: return 1.0f;
    }
}

// �û��������ʵ��
user* init_user_list() {
    user* head = (user*)malloc(sizeof(user));
    if (head == NULL) {
        return NULL;
    }

    // ����һ���յ�ͷ�ڵ�
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

        // �ͷ�ȡ��������
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

    // �����û��ļ���ȡ�����ļ���·��
    char user_file[256] = "user.txt";
    char pcode_file[256] = "p_code.txt";

    // �����û���Ϣ
    FILE* user_fp = fopen(user_file, "wb");
    if (user_fp == NULL) {
        printf("�޷����ļ� %s ����д��\n", user_file);
        return;
    }

    // ����ȡ������Ϣ
    FILE* pcode_fp = fopen(pcode_file, "wb");
    if (pcode_fp == NULL) {
        printf("�޷����ļ� %s ����д��\n", pcode_file);
        fclose(user_fp);
        return;
    }

    user* current = head->next; // ����ͷ�ڵ�
    while (current != NULL) {
        // �����û�������Ϣ
        fwrite(current, sizeof(user), 1, user_fp);

        // ����ȡ������Ϣ
        fprintf(pcode_fp, "%d ", current->id); // д���û�ID

        // ͳ�Ʋ�����ȡ��������
        int code_count = 0;
        p_code* code = current->p_code_list;
        while (code != NULL) {
            code_count++;
            code = code->next;
        }
        fprintf(pcode_fp, "%d ", code_count);

        // ����ȡ����
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
    // �����û��ļ���ȡ�����ļ���·��
    char user_file[256] = "user.txt";
    char pcode_file[256] = "p_code.txt";

    // ���û���Ϣ�ļ�
    FILE* user_fp = fopen(user_file, "rb");
    if (user_fp == NULL) {
        printf("�޷����ļ� %s ���ж�ȡ�����������ļ�\n", user_file);
        // ����ļ������ڣ���ʼ��һ���յ��û�����
        return init_user_list();
    }

    // ��ʼ���û�����
    user* head = init_user_list();
    if (head == NULL) {
        fclose(user_fp);
        return NULL;
    }

    user* current = head;
    user temp;

    // ��ȡ�û�������Ϣ
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

    // ��ȡ�����ļ�
    FILE* pcode_fp = fopen(pcode_file, "rb");
    if (pcode_fp == NULL) {
        printf("�޷����ļ� %s ���ж�ȡ\n", pcode_file);
        return head; // ����ֻ���û���Ϣ������
    }

    // ��ȡȡ������Ϣ
    int user_id, code_count;
    while (fscanf(pcode_fp, "%d %d", &user_id, &code_count) == 2) {
        // ���Ҷ�Ӧ���û�
        user* current_user = head->next;
        while (current_user != NULL) {
            if (current_user->id == user_id) {
                // ��ȡ���û�������ȡ����
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
        fscanf(pcode_fp, " "); // ��ȡ���з�
    }

    fclose(pcode_fp);
    return head;
}

// �û���ȡ�������ʵ��
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
                // ���������ĵ�һ���ڵ�
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

    printf("%s ��ȡ�����б�:\n", user_info->name);

    if (user_info->p_code_list == NULL) {
        printf("����ȡ����\n");
        return;
    }

    p_code* current = user_info->p_code_list;
    int count = 1;

    while (current != NULL) {
        printf("ȡ���� %d: %d-%d-%d\n", count, current->id_1, current->id_2, current->id_3);
        current = current->next;
        count++;
    }

    printf("���� %d ��ȡ����\n", user_info->package_quantity);
}