#include "user_management.h"

// ��ʾ�˵�
void show_menu() {
    printf("\n=== �û�����ϵͳ ===\n");
    printf("1. ����û�\n");
    printf("2. ��ʾ�����û�\n");
    printf("3. �����û�\n");
    printf("4. �޸��û���Ϣ\n");
    printf("5. ɾ���û�\n");
    printf("6. �����û���Ϣ\n");
    printf("0. �˳�ϵͳ\n");
    printf("==================\n");
    printf("��ѡ�����: ");
}

// ����û�����
void add_new_user(user* head) {
    char name[20];
    int sex;
    long long phone_num;
    int age;
    int status;

    printf("\n=== ������û� ===\n");
    printf("����������: ");
    scanf("%s", name);
    printf("�������Ա�(0-Ů,1-��): ");
    scanf("%d", &sex);
    printf("������绰����: ");
    scanf("%lld", &phone_num);
    while (phone_num < 10000000000LL || phone_num > 99999999999LL) {
        printf("�绰�������Ϊ11λ������������\n");
        scanf("%lld", &phone_num);
    }
    printf("����������: ");
    scanf("%d", &age);
    printf("�������û�����(0-��ͨ�û�,1-��ʦ,2-������,3-ѧ��,4-SVIP): ");
    scanf("%d", &status);

    user* new_user = create_user(name, sex, phone_num, age, status);
    if (new_user != NULL) {
        add_user(head, new_user);
        printf("�û���ӳɹ���\n");
    }
}

// ��ʾ�����û�����
void show_all_users(user* head) {
    if (head->next == NULL) {
        printf("\n��ǰû���û���Ϣ��\n");
        return;
    }

    printf("\n=== �����û���Ϣ ===\n");
    user* current = head->next;
    while (current != NULL) {
        display_user(current);
        current = current->next;
    }
}

// �����û�����
void search_user(user* head) {
    int choice;
    printf("\n=== �����û� ===\n");
    printf("1. ��ID����\n");
    printf("2. ����������\n");
    printf("3. ���绰����\n");
    printf("��ѡ����ҷ�ʽ: ");
    scanf("%d", &choice);

    user* found_user = NULL;
    switch (choice) {
    case 1: {
        int id;
        printf("�������û�ID: ");
        scanf("%d", &id);
        found_user = find_user_by_id(head, id);
        break;
    }
    case 2: {
        char name[20];
        printf("�������û�����: ");
        scanf("%s", name);
        found_user = find_user_by_name(head, name);
        break;
    }
    case 3: {
        long long phone;
        printf("������绰����: ");
        scanf("%lld", &phone);
        found_user = find_user_by_phone(head, phone);
        break;
    }
    default:
        printf("��Ч��ѡ��\n");
        return;
    }

    if (found_user != NULL) {
        display_user(found_user);
    }
    else {
        printf("δ�ҵ��û���\n");
    }
}

// �޸��û���Ϣ����
void modify_user(user* head) {
    int id;
    printf("\n=== �޸��û���Ϣ ===\n");
    printf("������Ҫ�޸ĵ��û�ID: ");
    scanf("%d", &id);

    user* user_to_modify = find_user_by_id(head, id);
    if (user_to_modify == NULL) {
        printf("δ�ҵ����û���\n");
        return;
    }

    int choice;
    printf("1. �޸�����\n");
    printf("2. �޸ĵ绰\n");
    printf("3. �޸��û�����\n");
    printf("��ѡ��Ҫ�޸ĵ���Ϣ: ");
    scanf("%d", &choice);

    switch (choice) {
    case 1: {
        char new_name[20];
        printf("������������: ");
        scanf("%s", new_name);
        update_user_name(user_to_modify, new_name);
        break;
    }
    case 2: {
        long long new_phone;
        printf("�������µ绰: ");
        scanf("%lld", &new_phone);
        update_user_phone(user_to_modify, new_phone);
        break;
    }
    case 3: {
        int new_status;
        printf("���������û�����(0-��ͨ�û�,1-��ʦ,2-������,3-ѧ��,4-SVIP): ");
        scanf("%d", &new_status);
        update_user_status(user_to_modify, new_status);
        break;
    }
    default:
        printf("��Ч��ѡ��\n");
    }
}

// ɾ���û�����
void delete_user_info(user* head) {
    int id;
    printf("\n=== ɾ���û� ===\n");
    printf("������Ҫɾ�����û�ID: ");
    scanf("%d", &id);

    if (delete_user(head, id)) {
        printf("�û�ɾ���ɹ���\n");
    }
    else {
        printf("ɾ��ʧ�ܣ��û����ܲ����ڣ�\n");
    }
}

int main() {
    // ��ʼ���û�����
    user* head = init_user_list();
    if (head == NULL) {
        printf("ϵͳ��ʼ��ʧ�ܣ�\n");
        return 1;
    }

    // ���Դ��ļ������û�����
    user* loaded_users = load_users_from_file("users.dat");
    if (loaded_users != NULL) {
        free_user_list(head);
        head = loaded_users;
    }

    int choice;
    while (1) {
        show_menu();
        scanf("%d", &choice);

        switch (choice) {
        case 0:
            printf("��лʹ�ã��ټ���\n");
            // �����û����ݵ��ļ�
            save_users_to_file(head, "users.dat");
            free_user_list(head);
            return 0;
        case 1:
            add_new_user(head);
            break;
        case 2:
            show_all_users(head);
            break;
        case 3:
            search_user(head);
            break;
        case 4:
            modify_user(head);
            break;
        case 5:
            delete_user_info(head);
            break;
        case 6:
            save_users_to_file(head, "users.dat");
            printf("�û���Ϣ�ѱ��浽�ļ���\n");
            break;
        default:
            printf("��Ч��ѡ�����������룡\n");
        }

        printf("\n��Enter������...");
        getchar(); // ����֮ǰ�Ļ��з�
        getchar(); // �ȴ��û���Enter
        system("cls"); // ����
    }

    return 0;
}