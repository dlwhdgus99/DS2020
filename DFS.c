#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define TRUE 1
#define FALSE 0

#define STACKLEN 100

typedef int DATATYPE;

typedef struct{
    DATATYPE StackArr[STACKLEN];
    int Top;
} ArrayStack;

enum {A, B, C, D, E, F, G, H, I, J};

typedef struct Node{
    DATATYPE Data;;
    struct Node* next;
} Node;

typedef struct LinkedList{
    Node* Head;
    Node* Curr;
    Node* Prev;
    int NumOfData;
} LinkedList;

typedef struct{
    int NumOfVertex;
    int NumOfEdge;
    struct LinkedList* AdjList;
    int* VisitInfo;
} Graph;

void InitStack(ArrayStack* stack);
int IsEmpty(ArrayStack* stack);
void Push(ArrayStack* stack, DATATYPE data);
DATATYPE Pop(ArrayStack* stack);
DATATYPE Peek(ArrayStack* stack);

void InitList(LinkedList* list);
void Insert(LinkedList* list, DATATYPE Data);

void HeadInsert(LinkedList* list, DATATYPE Data);
void SortInsert(LinkedList* list, DATATYPE Data);

int PosHead(LinkedList* list, DATATYPE* Data);
int PosNext(LinkedList* list, DATATYPE* Data);

DATATYPE Remove(LinkedList* list);
int RetCount(LinkedList* list);

void InitGraph(Graph* G, int NumOfVertex);
void ReleaseGraph(Graph* G);

void AddEdge(Graph* G, int From, int To);
void PrintGraph(Graph* G);

int VisitVertex(Graph* G, int Visit);
void PrintDFS(Graph* G, int Start);

int main() {

    Graph graph;
    InitGraph(&graph, 10);

    AddEdge(&graph, A, B);
    AddEdge(&graph, A, D);
    AddEdge(&graph, B, C);
    AddEdge(&graph, B, G);
    AddEdge(&graph, G, H);
    AddEdge(&graph, D, E);
    AddEdge(&graph, D, I);
    AddEdge(&graph, E, F);
    AddEdge(&graph, E, J);

    PrintGraph(&graph);
    printf("\n");

    PrintDFS(&graph, A);
    printf("\n");
    PrintDFS(&graph, H);
    printf("\n");
    PrintDFS(&graph, F);
    printf("\n");

    ReleaseGraph(&graph);

    return 0;
}

void InitStack(ArrayStack* stack){
    stack->Top = -1;
}

int IsEmpty(ArrayStack* stack){
    if(stack->Top == -1){
        return TRUE;
    }
    else{
        return FALSE;
    }
}

void Push(ArrayStack* stack, DATATYPE data){
    stack->Top += 1;
    stack->StackArr[stack->Top] = data;
}

DATATYPE Pop(ArrayStack* stack){
    int tempIdx;

    if(IsEmpty(stack)){
        printf("Stack is empty\n");
        exit(1);
    }

    tempIdx = stack ->Top;
    stack ->Top -= 1;

    return stack->StackArr[tempIdx];
}

DATATYPE Peek(ArrayStack* stack){
    if(IsEmpty(stack)){
        printf("Stack is empty\n");
        exit(1);
    }

    return stack->StackArr[stack->Top];
}

void InitList(LinkedList* list){

    list->Head = (Node*)malloc(sizeof(Node));
    list->Head->next = NULL;
    list->NumOfData = 0;
}

void Insert(LinkedList* list, DATATYPE Data){

    if(list->Head->next == NULL){
        HeadInsert(list, Data);
    }
    else{
        SortInsert(list, Data);
    }
}

void HeadInsert(LinkedList* list, DATATYPE Data){

    Node* temp = (Node*)malloc(sizeof(Node));
    temp->Data = Data;

    temp->next = list->Head->next;
    list->Head->next = temp;

    list->NumOfData++;
}

void SortInsert(LinkedList* list, DATATYPE Data){

    Node* new = (Node*)malloc(sizeof(Node));
    Node* pred = list->Head;
    new->Data = Data;

    while((pred->next != NULL) && (Data > pred->next->Data)){
        pred = pred->next;
    }

    new->next = pred->next;
    pred->next = new;

    list->NumOfData++;
}

int PosHead(LinkedList* list, DATATYPE* Data){

    if(list->Head->next == NULL){
        return FALSE;
    }

    list->Prev = list->Head;
    list->Curr = list->Head->next;

    *Data = list->Curr->Data;
    return TRUE;
}

int PosNext(LinkedList* list, DATATYPE* Data){

    if(list->Curr->next == NULL){
        return FALSE;
    }

    list->Prev = list->Curr;
    list->Curr = list->Curr->next;

    *Data = list->Curr->Data;
    return TRUE;
}

DATATYPE Remove(LinkedList* list){
    Node* temp = list->Curr;
    DATATYPE tData = temp->Data;

    list->Prev->next = list->Curr->next;
    list->Curr = list->Prev;

    free(temp);
    list->NumOfData--;
    return tData;
}

int RetCount(LinkedList* list){
    return list->NumOfData;
}

void InitGraph(Graph* G, int NumOfVertex){
    G->AdjList = (LinkedList*)malloc(sizeof(LinkedList) * NumOfVertex);
    G->NumOfVertex = NumOfVertex;
    G->NumOfEdge = 0;

    for(int i = 0; i < NumOfVertex; i++){
        InitList(&G->AdjList[i]);
    }

    G->VisitInfo = (int*)malloc(sizeof(int) * NumOfVertex);
    for(int i = 0; i < NumOfVertex; i++){
        G->VisitInfo[i] = 0;
    }
}

void ReleaseGraph(Graph* G){
    if(G->AdjList != NULL){
        free(G->AdjList);
    }

    if(G->VisitInfo != NULL){
        free(G->VisitInfo);
    }
}

void AddEdge(Graph* G, int From, int To){
    Insert(&G->AdjList[From], To);
    Insert(&G->AdjList[To], From);
    G->NumOfEdge++;
}

void PrintGraph(Graph* G){
    int Vertex;

    for(int i = 0; i < G->NumOfVertex; i++){
        printf("Vertex connected with %c : ", i + 65);
        if(PosHead(&G->AdjList[i], &Vertex)){
            printf("%c ", Vertex + 65);

            while(PosNext(&G->AdjList[i], &Vertex)){
                printf("%c ", Vertex + 65);
            }
        }
        printf("\n");
    }
}

int VisitVertex(Graph* G, int Visit){
    if(G->VisitInfo[Visit] == 0){
        G->VisitInfo[Visit] = 1;
        printf("%c ", Visit + 65);
        return TRUE;
    }
    return FALSE;
}

void PrintDFS(Graph* G, int Start){
    ArrayStack stack;
    int Visit = Start;
    int Next;

    InitStack(&stack);
    VisitVertex(G, Visit);
    Push(&stack, Visit);

    while(PosHead(&G->AdjList[Visit], &Next)){

        int Flag = FALSE;

        if(VisitVertex(G, Next)){
            Push(&stack, Visit);
            Visit = Next;
            Flag = TRUE;
        }
        else{
            while(PosNext(&G->AdjList[Visit], &Next)){
                if(VisitVertex(G, Next)){
                    Push(&stack, Visit);
                    Visit = Next;
                    Flag = TRUE;
                    break;
                }
            }
        }
        if(Flag == FALSE){
            if(IsEmpty(&stack)){
                break;
            }
            else{
                Visit = Pop(&stack);
            }
        }
    }

    for(int i = 0; i < G->NumOfVertex; i++){
        G->VisitInfo[i] = 0;
    }
}