#include"user_management.h"

// �û�ID�������������Զ������û�ID
static int user_id_counter = 1000;

// �û���Ϣ¼����غ���

// �������û�
user* create_user(char* name, int sex, long long phone_num, int age, int status) {
    // ��֤�û���Ϣ
    if (!validate_user_info(name, sex, phone_num, age, status)) {
        return NULL;
    }

    // �����ڴ�
    user* new_user = (user*)malloc(sizeof(user));
    if (new_user == NULL) {
        printf("�ڴ����ʧ�ܣ�\n");
        return NULL;
    }

    // ��ʼ���û���Ϣ
    strcpy(new_user->name, name);
    new_user->sex = sex;
    new_user->phone_num = phone_num;
    new_user->age = age;
    new_user->id = user_id_counter++;
    new_user->count = 0; // ��ʼ������Ϊ0
    new_user->status = status;
    new_user->next = NULL;
    new_user->pre = NULL;

    return new_user;
}

// ����û�������
void add_user(user* head, user* new_user) {
    if (head == NULL || new_user == NULL) {
        return;
    }

    // �ҵ�����β��
    user* current = head;
    while (current->next != NULL) {
        current = current->next;
    }

    // ������û�������β��
    current->next = new_user;
    new_user->pre = current;
    new_user->next = NULL;
}

// ��֤�û���Ϣ
bool validate_user_info(char* name, int sex, long long phone_num, int age, int status) {
    // ��֤����
    if (name == NULL || strlen(name) == 0 || strlen(name) > 19) {
        printf("��������Ϊ���ҳ��Ȳ��ܳ���19���ַ���\n");
        return false;
    }

    // ��֤�Ա�0ΪŮ�ԣ�1Ϊ���ԣ�
    if (sex != 0 && sex != 1) {
        printf("�Ա��������������0��Ů����1���У���\n");
        return false;
    }

    // ��֤�绰���루����֤11λ��
    if (phone_num < 10000000000LL || phone_num > 99999999999LL) {
        printf("�绰�������Ϊ11λ��\n");
        return false;
    }

    // ��֤����
    if (age < 0 || age > 150) {
        printf("���������0-150֮�䣡\n");
        return false;
    }

    // ��֤�û�״̬
    if (status < 0 || status > 4) {
        printf("�û�״̬������0-4֮�䣡\n");
        return false;
    }

    return true;
}

// �û���Ϣ��ѯ��غ���

// ����ID�����û�
user* find_user_by_id(user* head, int id) {
    if (head == NULL) {
        return NULL;
    }

    user* current = head->next; // ����ͷ�ڵ�
    while (current != NULL) {
        if (current->id == id) {
            return current;
        }
        current = current->next;
    }

    return NULL; // δ�ҵ�
}

// �������������û�
user* find_user_by_name(user* head, char* name) {
    if (head == NULL || name == NULL) {
        return NULL;
    }

    user* current = head->next; // ����ͷ�ڵ�
    while (current != NULL) {
        if (strcmp(current->name, name) == 0) {
            return current;
        }
        current = current->next;
    }

    return NULL; // δ�ҵ�
}

// ���ݵ绰��������û�
user* find_user_by_phone(user* head, long long phone_num) {
    if (head == NULL) {
        return NULL;
    }

    user* current = head->next; // ����ͷ�ڵ�
    while (current != NULL) {
        if (current->phone_num == phone_num) {
            return current;
        }
        current = current->next;
    }

    return NULL; // δ�ҵ�
}

// ��ʾ�û���Ϣ
void display_user(user* user_info) {
    if (user_info == NULL) {
        printf("�û������ڣ�\n");
        return;
    }

    printf("\n�û���Ϣ��\n");
    printf("ID: %d\n", user_info->id);
    printf("����: %s\n", user_info->name);
    printf("�Ա�: %s\n", user_info->sex == 0 ? "Ů" : "��");
    printf("�绰: %lld\n", user_info->phone_num);
    printf("����: %d\n", user_info->age);
    printf("ʹ�ô���: %d\n", user_info->count);
    printf("�û�����: %s\n", get_status_name(user_info->status));
}

// �û���Ϣ�޸���غ���

// �޸��û�����
bool update_user_name(user* user_info, char* new_name) {
    if (user_info == NULL || new_name == NULL || strlen(new_name) == 0 || strlen(new_name) > 19) {
        printf("�û������ڻ�������ʽ����\n");
        return false;
    }

    strcpy(user_info->name, new_name);
    printf("�û������Ѹ���Ϊ��%s\n", new_name);
    return true;
}

// �޸��û��绰
bool update_user_phone(user* user_info, long long new_phone) {
    if (user_info == NULL || new_phone < 10000000000LL || new_phone > 99999999999LL) {
        printf("�û������ڻ�绰�����ʽ����\n");
        return false;
    }

    user_info->phone_num = new_phone;
    printf("�û��绰�Ѹ���Ϊ��%lld\n", new_phone);
    return true;
}

// �޸��û�״̬
bool update_user_status(user* user_info, int new_status) {
    if (user_info == NULL || new_status < 0 || new_status > 4) {
        printf("�û������ڻ�״̬�����\n");
        return false;
    }

    user_info->status = new_status;
    printf("�û������Ѹ���Ϊ��%s\n", get_status_name(new_status));
    return true;
}

// �û���Ϣɾ����غ���

// ɾ���û�
bool delete_user(user* head, int id) {
    if (head == NULL) {
        return false;
    }

    user* current = head->next;
    while (current != NULL) {
        if (current->id == id) {
            // �ҵ�Ҫɾ���Ľڵ㣬����ǰ��ڵ��ָ��
            current->pre->next = current->next;
            if (current->next != NULL) {
                current->next->pre = current->pre;
            }

            // �ͷ��ڴ�
            free(current);
            printf("�û�(ID: %d)�ѳɹ�ɾ����\n", id);
            return true;
        }
        current = current->next;
    }

    printf("δ�ҵ�IDΪ%d���û���\n", id);
    return false;
}

// �û����������غ���

// ������ã������û�����Ӧ�ò�ͬ�ۿۣ�
float calculate_fee(user* user_info, float base_fee) {
    if (user_info == NULL || base_fee < 0) {
        return base_fee;
    }

    float discount = get_discount_rate(user_info->status);
    return base_fee * discount;
}

// ��ȡ�û�״̬����
const char* get_status_name(int status) {
    switch (status) {
    case 0:
        return "��ͨ�û�";  // ֱ�ӷ��أ�����ת��
    case 1:
        return "��ʦ";
    case 2:
        return "����";
    case 3:
        return "ѧ��";
    case 4:
        return "SVIP";
    default:
        return "δ֪״̬";
    }
}


// ��ȡ�û��ۿ���
float get_discount_rate(int status) {
    switch (status) {
    case 0: // ��ͨ�û�
        return 1.0f;
    case 1: // ��ʦ
        return 0.9f;
    case 2: // ����
        return 0.8f;
    case 3: // ѧ��
        return 0.7f;
    case 4: // SVIP
        return 0.6f;
    default:
        return 1.0f;
    }
}

// �û����������غ���

// ��ʼ���û�����
user* init_user_list() {
    user* head = (user*)malloc(sizeof(user));
    if (head == NULL) {
        printf("�ڴ����ʧ�ܣ�\n");
        return NULL;
    }

    // ��ʼ��ͷ�ڵ�
    memset(head, 0, sizeof(user));
    head->next = NULL;
    head->pre = NULL;

    return head;
}

// �ͷ��û�����
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

// �����û����ݵ��ļ�
void save_users_to_file(user* head, const char* filename) {
    if (head == NULL || filename == NULL) {
        return;
    }

    FILE* file = fopen(filename, "wb");
    if (file == NULL) {
        printf("�޷����ļ� %s ����д�룡\n", filename);
        return;
    }

    user* current = head->next; // ����ͷ�ڵ�
    while (current != NULL) {
        fwrite(current, sizeof(user), 1, file);
        current = current->next;
    }

    fclose(file);
    printf("�û������ѱ��浽�ļ� %s\n", filename);
}

// ���ļ������û�����
user* load_users_from_file(const char* filename) {
    if (filename == NULL) {
        return NULL;
    }

    FILE* file = fopen(filename, "rb");
    if (file == NULL) {
        printf("�޷����ļ� %s ���ж�ȡ��\n", filename);
        return NULL;
    }

    // ��ʼ���û�����
    user* head = init_user_list();
    if (head == NULL) {
        fclose(file);
        return NULL;
    }

    user temp;
    user* current = head;

    // ��ȡ�ļ��е��û�����
    while (fread(&temp, sizeof(user), 1, file) == 1) {
        user* new_user = (user*)malloc(sizeof(user));
        if (new_user == NULL) {
            printf("�ڴ����ʧ�ܣ�\n");
            free_user_list(head);
            fclose(file);
            return NULL;
        }

        // �����û�����
        memcpy(new_user, &temp, sizeof(user));
        new_user->next = NULL;

        // ��ӵ�����
        current->next = new_user;
        new_user->pre = current;
        current = new_user;

        // ����ID������
        if (new_user->id >= user_id_counter) {
            user_id_counter = new_user->id + 1;
        }
    }

    fclose(file);
    printf("�Ѵ��ļ� %s �����û�����\n", filename);
    return head;
}