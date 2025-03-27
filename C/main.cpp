#include "user_management.h"

// 显示菜单
void show_menu() {
    printf("\n=== 用户管理系统 ===\n");
    printf("1. 添加用户\n");
    printf("2. 显示所有用户\n");
    printf("3. 查找用户\n");
    printf("4. 修改用户信息\n");
    printf("5. 删除用户\n");
    printf("6. 保存用户信息\n");
    printf("0. 退出系统\n");
    printf("==================\n");
    printf("请选择操作: ");
}

// 添加用户功能
void add_new_user(user* head) {
    char name[20];
    int sex;
    long long phone_num;
    int age;
    int status;

    printf("\n=== 添加新用户 ===\n");
    printf("请输入姓名: ");
    scanf("%s", name);
    printf("请输入性别(0-女,1-男): ");
    scanf("%d", &sex);
    printf("请输入电话号码: ");
    scanf("%lld", &phone_num);
    while (phone_num < 10000000000LL || phone_num > 99999999999LL) {
        printf("电话号码必须为11位！请重新输入\n");
        scanf("%lld", &phone_num);
    }
    printf("请输入年龄: ");
    scanf("%d", &age);
    printf("请输入用户级别(0-普通用户,1-教师,2-老年人,3-学生,4-SVIP): ");
    scanf("%d", &status);

    user* new_user = create_user(name, sex, phone_num, age, status);
    if (new_user != NULL) {
        add_user(head, new_user);
        printf("用户添加成功！\n");
    }
}

// 显示所有用户功能
void show_all_users(user* head) {
    if (head->next == NULL) {
        printf("\n当前没有用户信息！\n");
        return;
    }

    printf("\n=== 所有用户信息 ===\n");
    user* current = head->next;
    while (current != NULL) {
        display_user(current);
        current = current->next;
    }
}

// 查找用户功能
void search_user(user* head) {
    int choice;
    printf("\n=== 查找用户 ===\n");
    printf("1. 按ID查找\n");
    printf("2. 按姓名查找\n");
    printf("3. 按电话查找\n");
    printf("请选择查找方式: ");
    scanf("%d", &choice);

    user* found_user = NULL;
    switch (choice) {
    case 1: {
        int id;
        printf("请输入用户ID: ");
        scanf("%d", &id);
        found_user = find_user_by_id(head, id);
        break;
    }
    case 2: {
        char name[20];
        printf("请输入用户姓名: ");
        scanf("%s", name);
        found_user = find_user_by_name(head, name);
        break;
    }
    case 3: {
        long long phone;
        printf("请输入电话号码: ");
        scanf("%lld", &phone);
        found_user = find_user_by_phone(head, phone);
        break;
    }
    default:
        printf("无效的选择！\n");
        return;
    }

    if (found_user != NULL) {
        display_user(found_user);
    }
    else {
        printf("未找到用户！\n");
    }
}

// 修改用户信息功能
void modify_user(user* head) {
    int id;
    printf("\n=== 修改用户信息 ===\n");
    printf("请输入要修改的用户ID: ");
    scanf("%d", &id);

    user* user_to_modify = find_user_by_id(head, id);
    if (user_to_modify == NULL) {
        printf("未找到该用户！\n");
        return;
    }

    int choice;
    printf("1. 修改姓名\n");
    printf("2. 修改电话\n");
    printf("3. 修改用户级别\n");
    printf("请选择要修改的信息: ");
    scanf("%d", &choice);

    switch (choice) {
    case 1: {
        char new_name[20];
        printf("请输入新姓名: ");
        scanf("%s", new_name);
        update_user_name(user_to_modify, new_name);
        break;
    }
    case 2: {
        long long new_phone;
        printf("请输入新电话: ");
        scanf("%lld", &new_phone);
        update_user_phone(user_to_modify, new_phone);
        break;
    }
    case 3: {
        int new_status;
        printf("请输入新用户级别(0-普通用户,1-教师,2-老年人,3-学生,4-SVIP): ");
        scanf("%d", &new_status);
        update_user_status(user_to_modify, new_status);
        break;
    }
    default:
        printf("无效的选择！\n");
    }
}

// 删除用户功能
void delete_user_info(user* head) {
    int id;
    printf("\n=== 删除用户 ===\n");
    printf("请输入要删除的用户ID: ");
    scanf("%d", &id);

    if (delete_user(head, id)) {
        printf("用户删除成功！\n");
    }
    else {
        printf("删除失败，用户可能不存在！\n");
    }
}

int main() {
    // 初始化用户链表
    user* head = init_user_list();
    if (head == NULL) {
        printf("系统初始化失败！\n");
        return 1;
    }

    // 尝试从文件加载用户数据
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
            printf("感谢使用，再见！\n");
            // 保存用户数据到文件
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
            printf("用户信息已保存到文件！\n");
            break;
        default:
            printf("无效的选择，请重新输入！\n");
        }

        printf("\n按Enter键继续...");
        getchar(); // 消耗之前的换行符
        getchar(); // 等待用户按Enter
        system("cls"); // 清屏
    }

    return 0;
}