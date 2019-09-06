#include <iostream>
#include <unordered_map>
using namespace std;

struct LRUNode{
    int key;
    int value;
    LRUNode* pre;
    LRUNode* next;
    LRUNode(int k, int v):key(k), value(v), pre(NULL), next(NULL){}
};
void printMap(unordered_map<int, LRUNode*> myMap){
    unordered_map<int, LRUNode*>::iterator it = myMap.begin();
    while (it != myMap.end()){
        cout<<"key:"<<it->first<<" val:"<<it->second->value<<endl;
        ++it;
    }
}
class LRUCache {
private:
    int capacity;
    LRUNode* head;
    LRUNode* tail;
    unordered_map<int, LRUNode*> myMap;

public:
    LRUCache(int capacity) {
        this->capacity = capacity;
        this->head = NULL;
        this->tail = NULL;
    }

    int get(int key) {
        unordered_map<int, LRUNode*>::iterator it = myMap.find(key);
        if(it != myMap.end()){
            LRUNode* temp = it->second;
            remove(temp);
            addFirst(temp);
        }
        return -1;
    }

    void put(int key, int value) {
        unordered_map<int, LRUNode*>::iterator it = myMap.find(key);
        if(it != myMap.end()){
            LRUNode* temp = it->second;
            remove(temp);
            addFirst(temp);
        }else{
            LRUNode* node = new LRUNode(key, value);
            if(myMap.size() >= capacity){
                unordered_map<int, LRUNode*>::iterator iter = myMap.find(tail->key);
                remove(tail);
                myMap.erase(iter);
            }
            addFirst(node);
            myMap.insert(make_pair(key, node));
        }
    }
    void remove(LRUNode* x){
        if(x == head){
            head = x->next;
        }else{
            x->pre->next = x->next;
        }
        if(x == tail){
            tail = x->pre;
        }else{
            x->next->pre = x->pre;
        }
    }
    void addFirst(LRUNode* x){
        if(head == NULL){
            head = x;
            tail = x;
        }else{
            x->next = head;
            head->pre = x;
            head = x;
        }
    }
};
int main() {
    LRUCache* cache = new LRUCache( 2 /* 缓存容量 */ );
    cache->put(1, 1);
    cache->put(2, 2);
    cache->get(1);       // 返回  1
    cache->put(3, 3);    // 该操作会使得密钥 2 作废
    cache->get(2);       // 返回 -1 (未找到)
    cache->put(4, 4);    // 该操作会使得密钥 1 作废
    cache->get(1);       // 返回 -1 (未找到)
    cache->get(3);       // 返回  3
    cache->get(4);       // 返回  4

    return 0;
}