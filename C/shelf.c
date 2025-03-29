#include"init.h"
#include<stdio.h>
#include <stdlib.h>
#include <string.h>

#define threshold 90
//生成取件码
struct p_code generate_p_code(int shelf_id, int storey_id, int position) {
    struct p_code code;
    code.shelf_id = shelf_id;
    code.storey_id= storey_id;
    code.position = position;
    return code;
}
//输出取件码
void printPackageCode(struct p_code code) {
    printf("%02d-%02d-%02d", code.shelf_id, code.storey_id, code.position);
}
//判断货架位置
int selectShelf(struct package* pkg) {
    int shelf = -1;//初始化货架位置
    if (pkg->electron) {
        shelf = (pkg->volume < VOLUME_THRESHOLD) ? 1 : 2;
    } else if (pkg->fragile) {
        shelf = (pkg->volume < VOLUME_THRESHOLD) ? 3 : 4;
    } else if (pkg->is_liquid) {
        shelf = (pkg->volume < VOLUME_THRESHOLD) ? 5 : 6;
    } else {
        shelf =(pkg->volume >= VOLUME_THRESHOLD) ? (7 + (pkg->id % 2)) : (9 + (pkg->id % 2));
    }
    return shelf;
}
//判断层数
int find_available_storey(int shelf_id) {
    for (int i = 0; i < MAX_STOREY; i++) {
        if (shelfs[shelf_id].num[i] < MAX_CAPACITY) {
            return i;  // 返回第一个未满的层
        }
    }
    return -1;  // 货架满了
}
//判断位置
int find_postion(int shelf_id,int storey){
    return shelfs[shelf_id].capacity[storey]+1;
}
// 统计库存数量
void count_package(struct shelf* s) {
    int total = 0;
    for (int i = 1; i < 6; i++) {
        total += s->num[i];
    }
    printf("当前货架总包裹数量: %d\n", total);
}
// 检测并触发预警
void check_and_warn(struct shelf* s) {
    int total = 0;
    for (int i = 1; i < 6; i++) {
        total += s->num[i];
    }
    if (total >= threshold) {
        printf("⚠️ 库存已达到 %d 件，接近上限！\n", total);
    }
}

