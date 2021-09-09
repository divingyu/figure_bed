#include <stdio.h>
#include <stdlib.h>

#define MAXNUM 10
typedef int seqType;

typedef struct {
    seqType *elem; //存储空间基地址
    int length; //当前长度
    int listSize; //当前分配的存储容量
}sqList;

/*
 * 创建顺序表
 */
sqList createSequenceList(){
    sqList* list = (sqList*)malloc(sizeof(sqList));
    return *list;
}

/*
 * 初始化顺序表
 * 0代表失败
 * 1代表成功
 */
int initSequenceList(sqList &L){
    L.elem = (seqType*)malloc(sizeof(seqType)*MAXNUM);
    if(!L.elem)
        return 0;
    L.length = 0;
    L.listSize = MAXNUM;
    return 1;
}

/*
 * 插入元素
 * 下表是负数就插入到结尾
 */
int insertElemFromList(sqList &L,int index,seqType val){
    if(index > L.length){
        printf("插入下标已经超过顺序表的实际长度\n");
        return 0;
    }
    if(index < 0)
        index = L.length;
    if(L.length == L.listSize){
        printf("顺序表的存储单元已经存满,继续分配存储单元\n");
        seqType* newList = (seqType*)malloc((L.listSize+MAXNUM)*sizeof(seqType));
        if(!newList){
            printf("内存分配失败\n");
            return 0;
        }
        for(int i = 0;i < L.length;i++){
            newList[i] = L.elem[i];
        }
        L.elem = newList;
        L.listSize += MAXNUM;
    }
    for(int i = L.length;i > index;i--){
        L.elem[i] = L.elem[i-1];
    }
    L.elem[index] = val;
    L.length++;
    return 1;
}

/*
 * 删除指定元素
 * 0代表找不到指定元素,删除失败
 * 1代表找到指定元素,删除成功
 */
int deleteElemFromList(sqList &L,seqType val){
    int index = 0; //记录匹配的下标
    for(int i = 0;i < L.length;i++){
        if(L.elem[i] == val){
            index = i;
            break;
        }
        return 0;
    }
    for(;index < L.length;index++){
        L.elem[index] = L.elem[index+1];
    }
    L.length--;
    return 1;
}

/*
 * 打印顺序表
 */
void printSequenceList(sqList &L){
    for(int i = 0;i < L.length;i++){
        printf("%d ",L.elem[i]);
    }
    printf("\n");
}

/*
 * 销毁顺序表
 */
void destoryList(sqList &L){
    free(L.elem);
    L.length = 0;
    L.listSize = 0;
}

int main(void){
    sqList L = createSequenceList();
    if(!initSequenceList(L)){
        printf("初始化失败\n");
        return 0;
    }
    for (int i = 0;i < 20; i++){
        insertElemFromList(L,i,(rand()%31));
    }
    printSequenceList(L);
    destoryList(L);
    return 0;
}
