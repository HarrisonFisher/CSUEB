//
// Your code here
//

#include "ChunkList.h"

template<class T>
ChunkList<T>::ChunkList(): numChunks(0),arrPos(-1),listLen(0)  {
    head = nullptr;
    tail = nullptr;
    iterNode = nullptr;
}

template<class T>
ChunkList<T>::ChunkList(T *arr, int arrLen): numChunks(1),arrPos(0),listLen(0) {
    if (arrLen <= 0) {throw InvalidArrayLength();}
    head = nullptr;
    tail = nullptr;

    for (int i = 0;i<arrLen;i++){
        Append(arr[i]);
    }
    ResetIterator();
}

template<class T>
ChunkList<T>::~ChunkList() {
    Node*ptr = head;
    while (true){
        if (ptr != nullptr){
            Node*temp = ptr;
            ptr = ptr->next;
            delete temp;
        }else{
            break;
        }
    }
}

template<class T>
void ChunkList<T>::Append(T value) {
    if (head == nullptr){
        head = new Node;
        head->next = nullptr;
        head->len = 0;
        tail = head;
        numChunks++;
    }
    if (tail->len == ARRAY_SIZE){
        tail->next = new Node;
        tail = tail->next;
        tail->next = nullptr;
        tail->len = 0;
        numChunks++;
    }
    tail->len++;
    listLen++;
    tail->values[tail->len-1] = value;
}


template<class T>
void ChunkList<T>::Remove(T value) {
    if (IsEmpty()) throw EmptyList();
    Node * ptr = head;
    Node * last_ptr = nullptr;
    while(ptr != nullptr){
        for (int i = 0; i < ptr->len; i++){
            if (ptr->values[i] == value){
                {
                    int n = ptr->len;
                    int x = value;
                    int i;
                    for (i=0; i<n; i++){
                        if (ptr->values[i] == x){
                            break;
                        }
                    }
                    if (i < n){
                        n = n - 1;
                        for (int j=i; j<n; j++)
                            ptr->values[j] = ptr->values[j+1];
                    }
                }

                ptr->len--;
                listLen--;
                if (ptr->len == 0){
                    numChunks--;
                    if (last_ptr != nullptr){
                        last_ptr->next == ptr->next;
                    }
                    if (ptr == head){
                        head = ptr->next;
                    }
                    delete ptr;
                }
                return;
            }
        }
        last_ptr = ptr;
        ptr = ptr->next;
    }
}

template<class T>
int ChunkList<T>::GetLength() {
    return listLen;
}

template<class T>
double ChunkList<T>::LoadFactor() {
    return static_cast<double>(listLen)/(numChunks*ARRAY_SIZE);
}

template<class T>
bool ChunkList<T>::Contains(T value) {
    Node * ptr = head;
    while(ptr != nullptr){
        for (int i = 0; i < ARRAY_SIZE; i++){
            if (ptr->values[i] == value){
                return true;
            }
        }
        ptr = ptr->next;
    }
    return false;
}

template<class T>
T ChunkList<T>::GetIndex(int i) {
    if (i < 0) throw IndexOutOfBounds();
    if (i > listLen) throw IndexOutOfBounds();
    Node * ptr = head;
    if (ptr == nullptr) throw EmptyList();



    int var = 0;
    if (i < ptr->len){
        return ptr->values[i];
    }
    var += ptr->len;
    ptr = ptr->next;

    while(ptr != nullptr){
        if (var+ptr->len > i) {
            return ptr->values[i-var];
        }else{
            var += ptr->len;
            ptr = ptr->next;
        }

    }
}

template<class T>
void ChunkList<T>::ResetIterator() {
    iterNode = head;
    arrPos = 0;
}

template<class T>
T ChunkList<T>::GetNextItem() {
    int val = iterNode->values[arrPos];

    if (arrPos+1 != iterNode->len){
        arrPos++;
    }else{
        iterNode = iterNode->next;
        arrPos = 0;
    }
    return val;
}

template<class T>
bool ChunkList<T>::IsEmpty() {
    return listLen == 0;
}

