#include <stdio.h>
#include <stdlib.h>
#define TRUE 1
#define FALSE 0

typedef struct{
    int ID;
    char* Name;
} Student;

typedef Student DATATYPE;

typedef struct Node{
    DATATYPE data;
    struct Node* next;
} Node;

typedef struct{
    Node* Head;
    Node* Cur;
    Node* Tail;
    int NumofData;
    int (*Comp)(int data1, int data2);
} LinkedList;

void InitList(LinkedList* list);
void Insert(LinkedList* list, int ID, char* Name);
void HeadInsert(LinkedList* list, int ID, char* Name);
void SortInsert(LinkedList* list, int ID, char* Name);

int PosHead(LinkedList* list, DATATYPE* data);
int PosNext(LinkedList* list, DATATYPE* data);

DATATYPE Remove(LinkedList* list);
int RetCount(LinkedList* list);

void SetSortRule(LinkedList* list, int (*Comp)(int ID1, int ID2));

int ComparePrecede(int ID1, int ID2);

void print(DATATYPE data);

int main(int argc, char* argv[]) {
    LinkedList list;
    DATATYPE data;

    InitList(&list);

    SetSortRule(&list, ComparePrecede);

    Insert(&list, 2020200001, "test person1");
    Insert(&list, 2020200765, "test person2");
    Insert(&list, 2020300004, "test person3");
    Insert(&list, 2020200628, "test person4");
    Insert(&list, 2020200218, "test person5");

    printf("Num of data: %d\n", RetCount(&list));

    if(PosHead(&list, &data)){
        print(data);

        while(PosNext(&list, &data)){
            print(data);
        }
    }
    printf("\n");

    int target = 2020200628;
    printf("Delete student node ID = %d\n\n", target);
    if(PosHead(&list, &data)){
        if(data.ID == target){
            Remove(&list);
        }
        while(PosNext(&list, &data)){
            if(data.ID == target){
                Remove(&list);
            }
        }
    }

    printf("Num of data: %d\n", RetCount(&list));

    if(PosHead(&list, &data)){
        print(data);

        while(PosNext(&list, &data)){
            print(data);
        }
        printf("\n");
    }
    return 0;
}

void InitList(LinkedList* list){
    list->Head = (Node*)malloc(sizeof(Node));
    list->Head->next = NULL;
    list->Comp = NULL;
    list->NumofData = 0;
}

void Insert(LinkedList* list, int ID, char* Name){
    if(list -> Comp == NULL){
        HeadInsert(list, ID, Name);
    }
    else{
        SortInsert(list, ID, Name);
    }
}

void HeadInsert(LinkedList* list, int ID, char* Name){
    Node* temp = (Node*)malloc(sizeof(Node));
    temp->data.ID = ID;
    temp->data.Name = Name;

    temp->next = list->Head->next;
    list->Head->next = temp;
    list->NumofData++;
}

void SortInsert(LinkedList* list, int ID, char* Name){
    Node* new = (Node*)malloc(sizeof(Node));
    Node* pred = list->Head;
    new->data.ID = ID;
    new->data.Name = Name;

    while(pred->next != NULL && list->Comp(ID, pred->next->data.ID) != 0){
        pred = pred->next;
    }
    new->next = pred->next;
    pred->next = new;

    list->NumofData++;
}

int PosHead(LinkedList* list, DATATYPE* data){
    if(list->Head->next == NULL){
        return FALSE;
    }
    list->Tail = list->Head;
    list->Cur = list->Head->next;
    *data = list->Cur->data;
    return TRUE;
}

int PosNext(LinkedList* list, DATATYPE* data){
    if(list->Cur->next == NULL){
        return FALSE;
    }
    list->Tail = list->Cur;
    list->Cur = list->Cur->next;

    *data = list->Cur->data;
    return TRUE;
}

DATATYPE Remove(LinkedList* list){
    Node* temp = list->Cur;
    DATATYPE tdata = temp->data;

    list->Tail->next = list->Cur->next;
    list->Cur = list->Tail;
    free(temp);
    list->NumofData--;
    return tdata;
}
int RetCount(LinkedList* list){
    return list->NumofData;
}

void SetSortRule(LinkedList* list, int (*Comp)(int ID1, int ID2)){
    list->Comp = Comp;
}

int ComparePrecede(int ID1, int ID2){
    if(ID1 < ID2){
        return 0;
    }
    else{
        return 1;
    }
}

void print(DATATYPE data){
    printf("ID : %d, Name : %s\n", data.ID, data.Name);
}