#include "user_management.h"

// �������ȡ����
p_code* generate_random_code() {
    p_code* code = (p_code*)malloc(sizeof(p_code));
    if (code == NULL) {
        return NULL;
    }

    code->id_1 = 100 + rand() % 900; // ��λ��
    code->id_2 = 100 + rand() % 900; // ��λ��
    code->id_3 = 100 + rand() % 900; // ��λ��
    code->next = NULL;

    return code;
}

// ��ʾ�˵�
void display_menu() {
    printf("\n===== �û�����ϵͳ =====\n");
    printf("1. ������û�\n");
    printf("2. ��ѯ�û���Ϣ\n");
    printf("3. �޸��û���Ϣ\n");
    printf("4. ɾ���û���Ϣ\n");
    printf("5. ��ʾ�����û�\n");
    printf("6. �û�ȡ�������\n");
    printf("7. �����û�����\n");
    printf("8. �����û�����\n");
    printf("9. �����û�����\n");
    printf("0. �˳�ϵͳ\n");
    printf("��ѡ�����: ");
}

// ������û��Ӳ˵�
void add_user_menu(user* user_head, user_hash_table* hash_table) {
    char name[20];
    int sex;
    long long phone_num;
    int age;
    int status;

    printf("\n===== ������û� =====\n");

    printf("�������û�����: ");
    scanf("%s", name);

    printf("�������û��Ա�(0:Ů, 1:��): ");
    scanf("%d", &sex);

    printf("�������û��ֻ���(11λ): ");
    scanf("%lld", &phone_num);

    printf("�������û�����: ");
    scanf("%d", &age);

    printf("�������û�״̬(0:��ͨ�û�, 1:��ʦ, 2:����, 3:ѧ��, 4:SVIP): ");
    scanf("%d", &status);

    user* new_user = create_user(name, sex, phone_num, age, status);
    if (new_user != NULL) {
        add_user(user_head, new_user);
        insert_user_to_hash(hash_table, new_user);
        printf("�û���ӳɹ�! �û�ID: %d\n", new_user->id);
    }
    else {
        printf("�û����ʧ��!\n");
    }
}

// ��ѯ�û���Ϣ�Ӳ˵�
void query_user_menu(user_hash_table* hash_table) {
    int choice;
    user* found_user = NULL;

    printf("\n===== ��ѯ�û���Ϣ =====\n");
    printf("1. ��������ѯ\n");
    printf("2. ��ID��ѯ\n");
    printf("3. ���ֻ��Ų�ѯ\n");
    printf("��ѡ���ѯ��ʽ: ");
    scanf("%d", &choice);

    switch (choice) {
    case 1: {
        char name[20];
        printf("�������û�����: ");
        scanf("%s", name);
        found_user = find_user_by_name_hash(hash_table, name);
        break;
    }
    case 2: {
        int id;
        printf("�������û�ID: ");
        scanf("%d", &id);
        found_user = find_user_by_id_hash(hash_table, id);
        break;
    }
    case 3: {
        long long phone;
        printf("�������û��ֻ���: ");
        scanf("%lld", &phone);
        found_user = find_user_by_phone_hash(hash_table, phone);
        break;
    }
    default:
        printf("��Ч��ѡ��!\n");
        return;
    }

    if (found_user != NULL) {
        printf("\n�ҵ��û���Ϣ:\n");
        printf("����: %s\n", found_user->name);
        printf("�Ա�: %s\n", found_user->sex ? "��" : "Ů");
        printf("�ֻ���: %lld\n", found_user->phone_num);
        printf("����: %d\n", found_user->age);
        printf("ID: %d\n", found_user->id);
        printf("״̬: %s\n", get_status_name(found_user->status));
        printf("��ȡ��������: %d\n", found_user->package_quantity);
    }
    else {
        printf("δ�ҵ��û�!\n");
    }
}

// �޸��û���Ϣ�Ӳ˵�
void update_user_menu(user_hash_table* hash_table) {
    int id;
    user* found_user = NULL;

    printf("\n===== �޸��û���Ϣ =====\n");
    printf("������Ҫ�޸ĵ��û�ID: ");
    scanf("%d", &id);

    found_user = find_user_by_id_hash(hash_table, id);
    if (found_user == NULL) {
        printf("δ�ҵ��û�!\n");
        return;
    }

    int choice;
    printf("\n��ǰ�û���Ϣ:\n");
    printf("����: %s\n", found_user->name);
    printf("�ֻ���: %lld\n", found_user->phone_num);
    printf("״̬: %s\n", get_status_name(found_user->status));

    printf("\n��ѡ��Ҫ�޸ĵ���Ϣ:\n");
    printf("1. �޸�����\n");
    printf("2. �޸��ֻ���\n");
    printf("3. �޸��û�״̬\n");
    printf("��ѡ��: ");
    scanf("%d", &choice);

    switch (choice) {
    case 1: {
        char new_name[20];
        printf("������������: ");
        scanf("%s", new_name);
        if (update_user_name(found_user, new_name)) {
            printf("�����޸ĳɹ�!\n");
        }
        else {
            printf("�����޸�ʧ��!\n");
        }
        break;
    }
    case 2: {
        long long new_phone;
        printf("���������ֻ���: ");
        scanf("%lld", &new_phone);
        if (update_user_phone(found_user, new_phone)) {
            printf("�ֻ����޸ĳɹ�!\n");
        }
        else {
            printf("�ֻ����޸�ʧ��!\n");
        }
        break;
    }
    case 3: {
        int new_status;
        printf("��������״̬(0:��ͨ�û�, 1:��ʦ, 2:����, 3:ѧ��, 4:SVIP): ");
        scanf("%d", &new_status);
        if (update_user_status(found_user, new_status)) {
            printf("�û�״̬�޸ĳɹ�!\n");
        }
        else {
            printf("�û�״̬�޸�ʧ��!\n");
        }
        break;
    }
    default:
        printf("��Ч��ѡ��!\n");
    }
}

// ɾ���û���Ϣ�Ӳ˵�
void delete_user_menu(user* user_head, user_hash_table* hash_table) {
    int choice;
    user* found_user = NULL;

    printf("\n===== ɾ���û���Ϣ =====\n");
    printf("1. ��IDɾ��\n");
    printf("2. ������ɾ��\n");
    printf("3. ���ֻ���ɾ��\n");
    printf("��ѡ��ɾ����ʽ: ");
    scanf("%d", &choice);

    switch (choice) {
    case 1: {
        int id;
        printf("�������û�ID: ");
        scanf("%d", &id);
        found_user = find_user_by_id_hash(hash_table, id);
        if (found_user != NULL) {
            remove_user_from_hash(hash_table, found_user);
            if (delete_user_by_id(user_head, id)) {
                printf("�û�ɾ���ɹ�!\n");
            }
            else {
                printf("�û�ɾ��ʧ��!\n");
            }
        }
        else {
            printf("δ�ҵ��û�!\n");
        }
        break;
    }
    case 2: {
        char name[20];
        printf("�������û�����: ");
        scanf("%s", name);
        found_user = find_user_by_name_hash(hash_table, name);
        if (found_user != NULL) {
            remove_user_from_hash(hash_table, found_user);
            if (delete_user_by_name(user_head, name)) {
                printf("�û�ɾ���ɹ�!\n");
            }
            else {
                printf("�û�ɾ��ʧ��!\n");
            }
        }
        else {
            printf("δ�ҵ��û�!\n");
        }
        break;
    }
    case 3: {
        long long phone;
        printf("�������û��ֻ���: ");
        scanf("%lld", &phone);
        found_user = find_user_by_phone_hash(hash_table, phone);
        if (found_user != NULL) {
            remove_user_from_hash(hash_table, found_user);
            if (delete_user_by_phone(user_head, phone)) {
                printf("�û�ɾ���ɹ�!\n");
            }
            else {
                printf("�û�ɾ��ʧ��!\n");
            }
        }
        else {
            printf("δ�ҵ��û�!\n");
        }
        break;
    }
    default:
        printf("��Ч��ѡ��!\n");
    }
}

// �û�ȡ��������Ӳ˵�
void pickup_code_menu(user_hash_table* hash_table) {
    int id;
    user* found_user = NULL;

    printf("\n===== �û�ȡ������� =====\n");
    printf("�������û�ID: ");
    scanf("%d", &id);

    found_user = find_user_by_id_hash(hash_table, id);
    if (found_user == NULL) {
        printf("δ�ҵ��û�!\n");
        return;
    }

    int choice;
    printf("\n1. ���ȡ����\n");
    printf("2. ɾ��ȡ����\n");
    printf("3. ��ʾ����ȡ����\n");
    printf("��ѡ�����: ");
    scanf("%d", &choice);

    switch (choice) {
    case 1: {
        p_code* new_code = generate_random_code();
        if (new_code != NULL) {
            add_pick_up_code(found_user, new_code);
            printf("ȡ������ӳɹ�: %d-%d-%d\n", new_code->id_1, new_code->id_2, new_code->id_3);
        }
        else {
            printf("ȡ��������ʧ��!\n");
        }
        break;
    }
    case 2: {
        if (found_user->p_code_list == NULL) {
            printf("���û�û��ȡ����!\n");
            break;
        }

        int id1, id2, id3;
        printf("������Ҫɾ����ȡ����(��ʽ: xxx-xxx-xxx): ");
        scanf("%d-%d-%d", &id1, &id2, &id3);

        p_code temp_code;
        temp_code.id_1 = id1;
        temp_code.id_2 = id2;
        temp_code.id_3 = id3;

        remove_pick_up_code(found_user, &temp_code);
        printf("ȡ����ɾ���������!\n");
        break;
    }
    case 3:
        display_user_pick_up_codes(found_user);
        break;
    default:
        printf("��Ч��ѡ��!\n");
    }
}

// �����û������Ӳ˵�
void calculate_fee_menu(user_hash_table* hash_table) {
    int id;
    float base_fee;
    user* found_user = NULL;

    printf("\n===== �����û����� =====\n");
    printf("�������û�ID: ");
    scanf("%d", &id);

    found_user = find_user_by_id_hash(hash_table, id);
    if (found_user == NULL) {
        printf("δ�ҵ��û�!\n");
        return;
    }

    printf("�������������: ");
    scanf("%f", &base_fee);

    float final_fee = calculate_fee(found_user, base_fee);

    printf("\n�û���Ϣ:\n");
    printf("����: %s\n", found_user->name);
    printf("״̬: %s\n", get_status_name(found_user->status));
    printf("�ۿ���: %.2f\n", get_discount_rate(found_user->status));
    printf("��������: %.2f\n", base_fee);
    printf("���շ���: %.2f\n", final_fee);
}

// ������
int main() {
    // ��ʼ�����������
    srand((unsigned int)time(NULL));

    // ��ʼ���û�����͹�ϣ��
    user* user_head = init_user_list();
    user_hash_table* hash_table = init_hash_table();

    // ���Լ������е��û�����
    FILE* file = fopen("user.txt", "r");
    if (file == NULL) {
        // ����ļ������ڣ�����һ�����ļ�
        file = fopen("user.txt", "w");
        if (file != NULL) {
            fclose(file);
        }
    }
    else {
        fclose(file);
        // ������������
        user_head = load_users_from_file("user.txt");
        if (user_head != NULL) {
            // ���¹�����ϣ��
            user* current = user_head->next;
            while (current != NULL) {
                insert_user_to_hash(hash_table, current);
                current = current->next;
            }
        }
    }

    if (user_head == NULL || hash_table == NULL) {
        printf("��ʼ��ʧ��!\n");
        return 1;
    }

    int choice;
    bool running = true;

    while (running) {
        display_menu();
        scanf("%d", &choice);

        switch (choice) {
        case 1:
            add_user_menu(user_head, hash_table);
            break;
        case 2:
            query_user_menu(hash_table);
            break;
        case 3:
            update_user_menu(hash_table);
            break;
        case 4:
            delete_user_menu(user_head, hash_table);
            break;
        case 5:
            display_user_hash(hash_table);
            break;
        case 6:
            pickup_code_menu(hash_table);
            break;
        case 7:
            calculate_fee_menu(hash_table);
            break;
        case 8: {
            save_users_to_file(user_head, "user.txt");
            printf("�û����ݱ������!\n");
            break;
        }
        case 9: {
            // �ͷŵ�ǰ����
            free_user_list(user_head);
            free_hash_table(hash_table);

            // ����������
            user_head = load_users_from_file("user.txt");
            hash_table = init_hash_table();

            if (user_head == NULL || hash_table == NULL) {
                printf("����ʧ��!\n");
                return 1;
            }

            // ���¹�����ϣ��
            user* current = user_head->next;
            while (current != NULL) {
                insert_user_to_hash(hash_table, current);
                current = current->next;
            }

            printf("�û����ݼ������!\n");
            break;
        }
        case 0:
            running = false;
            printf("��лʹ�ã��ټ�!\n");
            break;
        default:
            printf("��Ч��ѡ������������!\n");
        }
    }

    // �ͷ���Դ
    free_user_list(user_head);
    free_hash_table(hash_table);

    return 0;
}