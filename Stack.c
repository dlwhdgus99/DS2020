#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>

#define DATATYPE char
#define TRUE 1
#define FALSE 0

typedef struct node{
    DATATYPE data;
    struct node* next;
} NODE;

typedef struct{
    NODE* head;
} ListStack;

void InitStack(ListStack* stack);
int IsEmpty(ListStack* stack);
void Push(ListStack* stack, DATATYPE data);
DATATYPE Pop(ListStack* stack);
DATATYPE Peek(ListStack* stack);
void ConvertExp(char exp[]);
int GetOperatorPriority(char op);
int CompareOperatorPriority(char op1, char op2);
int EvalExp(char exp[]);

int main() {

    char exp_1[20] = "3+(4-3)*(1+2)";
    char exp_2[20] = "(1+2)*3";
    char exp_3[20] = "((2*3/2)+5)/3+7";
    char exp_4[20] = "((9-7/2)-4)*3+2";

    printf("Infix notation: %s\n", exp_1);
    ConvertExp(exp_1);
    printf("Postfix notation: %s = %d\n", exp_1, EvalExp(exp_1));

    printf("\n");

    printf("Infix notation: %s\n", exp_2);
    ConvertExp(exp_2);
    printf("Postfix notation: %s = %d\n", exp_2, EvalExp(exp_2));

    printf("\n");

    printf("Infix notation: %s\n", exp_3);
    ConvertExp(exp_3);
    printf("Postfix notation: %s = %d\n", exp_3, EvalExp(exp_3));

    printf("\n");

    printf("Infix notation: %s\n", exp_4);
    ConvertExp(exp_4);
    printf("Postfix notation: %s = %d\n", exp_4, EvalExp(exp_4));

    return 0;
}

void InitStack(ListStack* stack){
    stack->head = NULL;
}

int IsEmpty(ListStack* stack){
    if(stack->head == NULL){
        return TRUE;
    }
    return FALSE;
}

void Push(ListStack* stack, DATATYPE data){
    NODE* temp = (NODE*)malloc(sizeof(NODE));
    temp->data = data;
    temp->next = stack->head;
    stack->head = temp;
}

DATATYPE Pop(ListStack* stack){
    NODE* temp;
    DATATYPE tempData;
    if(IsEmpty(stack)){
        printf("Stack is empty\n");
        exit(1);
    }
    tempData = stack->head->data;
    temp = stack->head;
    stack->head = stack->head->next;
    free(temp);
    return tempData;
}

DATATYPE Peek(ListStack* stack){
    if(IsEmpty(stack)){
        printf("Stack is empty\n");
        exit(1);
    }
    return stack->head->data;
}

void ConvertExp(char exp[]){
    ListStack IntStack;
    ListStack CharStack;
    InitStack(&IntStack);
    InitStack(&CharStack);
    int NumOfParenthesis = 0;
    for (int i = 0; i < (int)strlen(exp); ++i) {
        if(isdigit(exp[i])){
            Push(&IntStack, exp[i]);
        }
        else if(exp[i] == '(') Push(&CharStack,exp[i]);
        else if(exp[i] == ')'){
            while(Peek(&CharStack) != '('){
                Push(&IntStack, Pop(&CharStack));
            }
            Pop(&CharStack);
            NumOfParenthesis++;
        }
        else if(IsEmpty(&CharStack)) Push(&CharStack, exp[i]);
        else if(CompareOperatorPriority(exp[i], Peek(&CharStack))) Push(&CharStack, exp[i]);
        else{
            while(!CompareOperatorPriority(exp[i], Peek(&CharStack))){
                Push(&IntStack, Pop(&CharStack));
                if(IsEmpty(&CharStack)) break;
            }
            Push(&CharStack, exp[i]);
        }
    }
    printf("%d\n", NumOfParenthesis);
    while(!IsEmpty(&CharStack)){
        Push(&IntStack, Pop(&CharStack));
    }
    char tempArr[(int)strlen(exp)];
    int i = (int)strlen(exp) - 2*NumOfParenthesis;
    while(!IsEmpty(&IntStack)){
        tempArr[i-1] = Pop(&IntStack);
        i--;
    }
    strcpy(exp,tempArr);
}

int GetOperatorPriority(char op){
    if(op == '*'||op == '/') return 5;
    else if(op == '+'||op == '-') return 3;
    else if(op == '(') return 1;
    else return -1;
}

int CompareOperatorPriority(char op1, char op2){
    if(GetOperatorPriority(op1) > GetOperatorPriority(op2)) return 1;
    else return 0;
}

int EvalExp(char exp[]){
    ListStack stack;
    InitStack(&stack);
    for (int i = 0; i < (int)strlen(exp); ++i) {
        if(isdigit(exp[i])){
            Push(&stack, exp[i]);
        }
        else if(exp[i] == '*'){
            char arr[10];
            int temp = (Pop(&stack)-'0')*(Pop(&stack)-'0');
            sprintf(arr, "%d", temp);
            Push(&stack, arr[0]);
        }
        else if(exp[i] == '/'){
            char arr[10];
            int tempDiv = Pop(&stack)-'0';
            int temp = (Pop(&stack)-'0')/tempDiv;
            sprintf(arr, "%d", temp);
            Push(&stack, arr[0]);
        }
        else if(exp[i] == '+'){
            char arr[10];
            int temp = (Pop(&stack)-'0')+(Pop(&stack)-'0');
            sprintf(arr, "%d", temp);
            Push(&stack, arr[0]);
        }
        else if(exp[i] == '-'){
            char arr[10];
            int tempSub = (Pop(&stack)-'0');
            int temp = (Pop(&stack)-'0')-tempSub;
            sprintf(arr, "%d", temp);
            Push(&stack, arr[0]);
        }
    }
    return Pop(&stack)-'0';
}