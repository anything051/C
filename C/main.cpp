#include "user_management.h"

// 生成随机取件码
p_code* generate_random_code() {
    p_code* code = (p_code*)malloc(sizeof(p_code));
    if (code == NULL) {
        return NULL;
    }

    code->id_1 = 100 + rand() % 900; // 三位数
    code->id_2 = 100 + rand() % 900; // 三位数
    code->id_3 = 100 + rand() % 900; // 三位数
    code->next = NULL;

    return code;
}

// 显示菜单
void display_menu() {
    printf("\n===== 用户管理系统 =====\n");
    printf("1. 添加新用户\n");
    printf("2. 查询用户信息\n");
    printf("3. 修改用户信息\n");
    printf("4. 删除用户信息\n");
    printf("5. 显示所有用户\n");
    printf("6. 用户取件码管理\n");
    printf("7. 计算用户费用\n");
    printf("8. 保存用户数据\n");
    printf("9. 加载用户数据\n");
    printf("0. 退出系统\n");
    printf("请选择操作: ");
}

// 添加新用户子菜单
void add_user_menu(user* user_head, user_hash_table* hash_table) {
    char name[20];
    int sex;
    long long phone_num;
    int age;
    int status;

    printf("\n===== 添加新用户 =====\n");

    printf("请输入用户姓名: ");
    scanf("%s", name);

    printf("请输入用户性别(0:女, 1:男): ");
    scanf("%d", &sex);

    printf("请输入用户手机号(11位): ");
    scanf("%lld", &phone_num);

    printf("请输入用户年龄: ");
    scanf("%d", &age);

    printf("请输入用户状态(0:普通用户, 1:教师, 2:老人, 3:学生, 4:SVIP): ");
    scanf("%d", &status);

    user* new_user = create_user(name, sex, phone_num, age, status);
    if (new_user != NULL) {
        add_user(user_head, new_user);
        insert_user_to_hash(hash_table, new_user);
        printf("用户添加成功! 用户ID: %d\n", new_user->id);
    }
    else {
        printf("用户添加失败!\n");
    }
}

// 查询用户信息子菜单
void query_user_menu(user_hash_table* hash_table) {
    int choice;
    user* found_user = NULL;

    printf("\n===== 查询用户信息 =====\n");
    printf("1. 按姓名查询\n");
    printf("2. 按ID查询\n");
    printf("3. 按手机号查询\n");
    printf("请选择查询方式: ");
    scanf("%d", &choice);

    switch (choice) {
    case 1: {
        char name[20];
        printf("请输入用户姓名: ");
        scanf("%s", name);
        found_user = find_user_by_name_hash(hash_table, name);
        break;
    }
    case 2: {
        int id;
        printf("请输入用户ID: ");
        scanf("%d", &id);
        found_user = find_user_by_id_hash(hash_table, id);
        break;
    }
    case 3: {
        long long phone;
        printf("请输入用户手机号: ");
        scanf("%lld", &phone);
        found_user = find_user_by_phone_hash(hash_table, phone);
        break;
    }
    default:
        printf("无效的选择!\n");
        return;
    }

    if (found_user != NULL) {
        printf("\n找到用户信息:\n");
        printf("姓名: %s\n", found_user->name);
        printf("性别: %s\n", found_user->sex ? "男" : "女");
        printf("手机号: %lld\n", found_user->phone_num);
        printf("年龄: %d\n", found_user->age);
        printf("ID: %d\n", found_user->id);
        printf("状态: %s\n", get_status_name(found_user->status));
        printf("待取包裹数量: %d\n", found_user->package_quantity);
    }
    else {
        printf("未找到用户!\n");
    }
}

// 修改用户信息子菜单
void update_user_menu(user_hash_table* hash_table) {
    int id;
    user* found_user = NULL;

    printf("\n===== 修改用户信息 =====\n");
    printf("请输入要修改的用户ID: ");
    scanf("%d", &id);

    found_user = find_user_by_id_hash(hash_table, id);
    if (found_user == NULL) {
        printf("未找到用户!\n");
        return;
    }

    int choice;
    printf("\n当前用户信息:\n");
    printf("姓名: %s\n", found_user->name);
    printf("手机号: %lld\n", found_user->phone_num);
    printf("状态: %s\n", get_status_name(found_user->status));

    printf("\n请选择要修改的信息:\n");
    printf("1. 修改姓名\n");
    printf("2. 修改手机号\n");
    printf("3. 修改用户状态\n");
    printf("请选择: ");
    scanf("%d", &choice);

    switch (choice) {
    case 1: {
        char new_name[20];
        printf("请输入新姓名: ");
        scanf("%s", new_name);
        if (update_user_name(found_user, new_name)) {
            printf("姓名修改成功!\n");
        }
        else {
            printf("姓名修改失败!\n");
        }
        break;
    }
    case 2: {
        long long new_phone;
        printf("请输入新手机号: ");
        scanf("%lld", &new_phone);
        if (update_user_phone(found_user, new_phone)) {
            printf("手机号修改成功!\n");
        }
        else {
            printf("手机号修改失败!\n");
        }
        break;
    }
    case 3: {
        int new_status;
        printf("请输入新状态(0:普通用户, 1:教师, 2:老人, 3:学生, 4:SVIP): ");
        scanf("%d", &new_status);
        if (update_user_status(found_user, new_status)) {
            printf("用户状态修改成功!\n");
        }
        else {
            printf("用户状态修改失败!\n");
        }
        break;
    }
    default:
        printf("无效的选择!\n");
    }
}

// 删除用户信息子菜单
void delete_user_menu(user* user_head, user_hash_table* hash_table) {
    int choice;
    user* found_user = NULL;

    printf("\n===== 删除用户信息 =====\n");
    printf("1. 按ID删除\n");
    printf("2. 按姓名删除\n");
    printf("3. 按手机号删除\n");
    printf("请选择删除方式: ");
    scanf("%d", &choice);

    switch (choice) {
    case 1: {
        int id;
        printf("请输入用户ID: ");
        scanf("%d", &id);
        found_user = find_user_by_id_hash(hash_table, id);
        if (found_user != NULL) {
            remove_user_from_hash(hash_table, found_user);
            if (delete_user_by_id(user_head, id)) {
                printf("用户删除成功!\n");
            }
            else {
                printf("用户删除失败!\n");
            }
        }
        else {
            printf("未找到用户!\n");
        }
        break;
    }
    case 2: {
        char name[20];
        printf("请输入用户姓名: ");
        scanf("%s", name);
        found_user = find_user_by_name_hash(hash_table, name);
        if (found_user != NULL) {
            remove_user_from_hash(hash_table, found_user);
            if (delete_user_by_name(user_head, name)) {
                printf("用户删除成功!\n");
            }
            else {
                printf("用户删除失败!\n");
            }
        }
        else {
            printf("未找到用户!\n");
        }
        break;
    }
    case 3: {
        long long phone;
        printf("请输入用户手机号: ");
        scanf("%lld", &phone);
        found_user = find_user_by_phone_hash(hash_table, phone);
        if (found_user != NULL) {
            remove_user_from_hash(hash_table, found_user);
            if (delete_user_by_phone(user_head, phone)) {
                printf("用户删除成功!\n");
            }
            else {
                printf("用户删除失败!\n");
            }
        }
        else {
            printf("未找到用户!\n");
        }
        break;
    }
    default:
        printf("无效的选择!\n");
    }
}

// 用户取件码管理子菜单
void pickup_code_menu(user_hash_table* hash_table) {
    int id;
    user* found_user = NULL;

    printf("\n===== 用户取件码管理 =====\n");
    printf("请输入用户ID: ");
    scanf("%d", &id);

    found_user = find_user_by_id_hash(hash_table, id);
    if (found_user == NULL) {
        printf("未找到用户!\n");
        return;
    }

    int choice;
    printf("\n1. 添加取件码\n");
    printf("2. 删除取件码\n");
    printf("3. 显示所有取件码\n");
    printf("请选择操作: ");
    scanf("%d", &choice);

    switch (choice) {
    case 1: {
        p_code* new_code = generate_random_code();
        if (new_code != NULL) {
            add_pick_up_code(found_user, new_code);
            printf("取件码添加成功: %d-%d-%d\n", new_code->id_1, new_code->id_2, new_code->id_3);
        }
        else {
            printf("取件码生成失败!\n");
        }
        break;
    }
    case 2: {
        if (found_user->p_code_list == NULL) {
            printf("该用户没有取件码!\n");
            break;
        }

        int id1, id2, id3;
        printf("请输入要删除的取件码(格式: xxx-xxx-xxx): ");
        scanf("%d-%d-%d", &id1, &id2, &id3);

        p_code temp_code;
        temp_code.id_1 = id1;
        temp_code.id_2 = id2;
        temp_code.id_3 = id3;

        remove_pick_up_code(found_user, &temp_code);
        printf("取件码删除操作完成!\n");
        break;
    }
    case 3:
        display_user_pick_up_codes(found_user);
        break;
    default:
        printf("无效的选择!\n");
    }
}

// 计算用户费用子菜单
void calculate_fee_menu(user_hash_table* hash_table) {
    int id;
    float base_fee;
    user* found_user = NULL;

    printf("\n===== 计算用户费用 =====\n");
    printf("请输入用户ID: ");
    scanf("%d", &id);

    found_user = find_user_by_id_hash(hash_table, id);
    if (found_user == NULL) {
        printf("未找到用户!\n");
        return;
    }

    printf("请输入基础费用: ");
    scanf("%f", &base_fee);

    float final_fee = calculate_fee(found_user, base_fee);

    printf("\n用户信息:\n");
    printf("姓名: %s\n", found_user->name);
    printf("状态: %s\n", get_status_name(found_user->status));
    printf("折扣率: %.2f\n", get_discount_rate(found_user->status));
    printf("基础费用: %.2f\n", base_fee);
    printf("最终费用: %.2f\n", final_fee);
}

// 主函数
int main() {
    // 初始化随机数种子
    srand((unsigned int)time(NULL));

    // 初始化用户链表和哈希表
    user* user_head = init_user_list();
    user_hash_table* hash_table = init_hash_table();

    // 尝试加载已有的用户数据
    FILE* file = fopen("user.txt", "r");
    if (file == NULL) {
        // 如果文件不存在，创建一个空文件
        file = fopen("user.txt", "w");
        if (file != NULL) {
            fclose(file);
        }
    }
    else {
        fclose(file);
        // 加载已有数据
        user_head = load_users_from_file("user.txt");
        if (user_head != NULL) {
            // 重新构建哈希表
            user* current = user_head->next;
            while (current != NULL) {
                insert_user_to_hash(hash_table, current);
                current = current->next;
            }
        }
    }

    if (user_head == NULL || hash_table == NULL) {
        printf("初始化失败!\n");
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
            printf("用户数据保存完成!\n");
            break;
        }
        case 9: {
            // 释放当前数据
            free_user_list(user_head);
            free_hash_table(hash_table);

            // 加载新数据
            user_head = load_users_from_file("user.txt");
            hash_table = init_hash_table();

            if (user_head == NULL || hash_table == NULL) {
                printf("加载失败!\n");
                return 1;
            }

            // 重新构建哈希表
            user* current = user_head->next;
            while (current != NULL) {
                insert_user_to_hash(hash_table, current);
                current = current->next;
            }

            printf("用户数据加载完成!\n");
            break;
        }
        case 0:
            running = false;
            printf("感谢使用，再见!\n");
            break;
        default:
            printf("无效的选择，请重新输入!\n");
        }
    }

    // 释放资源
    free_user_list(user_head);
    free_hash_table(hash_table);

    return 0;
}