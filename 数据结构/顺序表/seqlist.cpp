//顺序表 数组实现 链表实现
//功能：增删查改

#include <iostream>
#include <cstdlib>

using namespace std;

class seq_list_arr{
private:
    int* arr;
    int size;

public:
    seq_list_arr(int size){
        this->size = size;
        arr = (int*)malloc(size * sizeof(int));
        for(int i = 0; i < size; ++i) arr[i] = -1;
        printf("顺序表初始化成功\n");
    }

    ~seq_list_arr(){
        delete[] arr;
        printf("顺序表释放成功\n");
    }

    void modify_seq_list_arr(int key, int val){//数组实现 修改复杂度为O(1)
        arr[key] = val;  
        printf("成功将%d位置修改成%d\n",key,val);
    }

    int search_seq_list_arr(int val){//数组实现 查找复杂度O(n)
        for(int i = 0; i < size; ++i){
            if(arr[i] == val) {
                printf("%d位置存在%d\n",i,val);
                return i;
            }
        }
        printf("不存在%d\n",val);
        return -1;
    }

    void insert_seq_list_arr(int key, int val){//数组实现 插入复杂度为O(n)
        if(key < 0 || key >= size){
            printf("key超出范围\n");
            return ;
        }
        for(int i = size-1; i > key; --i){//i从后往前遍历，把key后面的元素依次后移一位
            arr[i] = arr[i-1];
        }
        arr[key] = val;
        this->size++;
        printf("成功将%d位置插入%d\n",key,val);
    }

    void delete_seq_list_arr(int key){//数组实现 删除复杂度为O(n)
        if(key < 0 || key >= size){
            printf("key超出范围\n");
            return ;
        }
        for(int i = key; i < size-1; ++i){//i从前往后遍历，把key后面的元素依次前移一位
            arr[i] = arr[i+1];
        }
        this->size--;
        printf("成功将%d位置删除\n",key);
    }
};
class seq_list_link{
private:
    struct link_list_Node{
        int val;
        link_list_Node* next;
    };
    int size;
    link_list_Node* head_node;

public:
    seq_list_link(int size){
        head_node = (link_list_Node*)malloc(sizeof(link_list_Node));//分配头节点    
        head_node->val = -1;
        head_node->next = NULL;
        link_list_Node *p = head_node;
        for(int i = 0; i < size; ++i){
            p->next = (link_list_Node*)malloc(sizeof(link_list_Node));
            p->val = -1;
            p = p->next;
        }
        p->next = NULL;
        this->size = size;
        printf("链表初始化成功\n");
    }

    ~seq_list_link(){
        link_list_Node* p = head_node;
        while(p){//逐个释放节点
            link_list_Node* tmp = p;
            p = p->next;
            free(tmp);
        }
        printf("链表释放成功\n");
    }

    void modify_seq_list_link(int key, int val){//链表实现 修改复杂度为O(n)
        if(key < 0 || key >= size){
            printf("key超出范围\n");
            return;
        }
        int step_cnt = 0;
        link_list_Node* p = head_node;
        while(p && step_cnt < key){
            p = p->next;
            ++step_cnt;
        }
        p->val = val;
        printf("成功将%d位置修改成%d\n",key,val);
    }

    void insert_seq_list_link(int key, int val){//链表实现 插入复杂度为O(n)
        if(key < 0 || key >= size){
            printf("key超出范围\n");
            return;
        }
        int step_cnt = 0;
        link_list_Node* p = head_node;
        while(p && step_cnt < key-1){//遍历到key-1节点
            p = p->next;
            ++step_cnt;
        }
        link_list_Node* tmp = (link_list_Node*)malloc(sizeof(link_list_Node));
        tmp->val = val;
        tmp->next = p->next;
        p->next = tmp;//先把新节点尾节点指向p的下一个节点，再把p的下一个节点指向新节点
        this->size++;
        printf("成功将%d位置插入%d\n",key,val);
    }

    void delete_seq_list_link(int key){//链表实现 删除复杂度为O(n)
        if(key < 0 || key >= size){
            printf("key超出范围\n");
            return;
        }
        int step_cnt = 0;
        link_list_Node* p = head_node;
        while(p && step_cnt < key-1){//遍历到key-1节点
            p = p->next;
            ++step_cnt;
        }
        if(p->next->next == NULL){//是最后一个节点 直接删除
            free(p->next);
        }
        else{//不是最后一个节点，把p的下一个节点指向下下个节点，再释放下个节点
            link_list_Node* tmp = p->next;
            p->next = p->next->next;
            free(tmp);
        }
        this->size--;
        printf("成功将%d位置删除\n",key);
    }

    int search_seq_list_link(int val){//链表实现 查找复杂度O(n)
        int step_cnt = 0;
        link_list_Node* p = head_node;
        while(p){
            if(p->val == val) {
                printf("%d位置存在%d\n",step_cnt,val);
                return step_cnt;
            }
            p = p->next;
            ++step_cnt;
        }
        printf("不存在%d\n",val);
        return -1;
    }
};

int main() {
    printf("测试开始\n");
    int test_num = 5;  // 减少测试数据量便于调试
    seq_list_arr test_arr(10);
    seq_list_link test_link(10);

    //测试插入
    for(int i = 0; i < test_num; ++i){
        test_arr.insert_seq_list_arr(i,i);
        test_link.insert_seq_list_link(i,i);
    }

    //测试查找 
    for(int i = 0; i < test_num; ++i){
        test_arr.search_seq_list_arr(i);
        test_link.search_seq_list_link(i);
    }

    //测试删除
    for(int i = 0; i < test_num; ++i){
        test_arr.delete_seq_list_arr(i);
        test_link.delete_seq_list_link(i);
    }

    //测试修改
    for(int i = 0; i < test_num; ++i){
        test_arr.modify_seq_list_arr(i,i*2);
        test_link.modify_seq_list_link(i,i*2);
    }

    printf("测试结束\n");
    return 0;
}