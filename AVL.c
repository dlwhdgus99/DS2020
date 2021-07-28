#include <stdio.h>
#include <stdlib.h>

#define COUNT 12

typedef int DATATYPE;

typedef struct BTNode{
    DATATYPE Data;
    struct BTNode* Left;
    struct BTNode* Right;
} BTNode;

BTNode* MakeBTNode();
DATATYPE RetData(BTNode* Node);
void SaveData(BTNode* Node, DATATYPE Data);

BTNode* RetSubTreeLeft(BTNode* Node);
BTNode* RetSubTreeRight(BTNode* Node);

void MakeSubTreeLeft(BTNode* Parent, BTNode* Child);
void MakeSubTreeRight(BTNode* Parent, BTNode* Child);

BTNode* RemoveSubTreeLeft(BTNode* Node);
BTNode* RemoveSubTreeRight(BTNode* Node);

void ChangeSubTreeLeft(BTNode* Parent, BTNode* Child);
void ChangeSubTreeRight(BTNode* Parent, BTNode* Child);

void PreorderTraversal(BTNode* Node);
void InorderTraversal(BTNode* Node);
void PostorderTraversal(BTNode* Node);

void MakeBST(BTNode** Node);

BTNode* InsertBST(BTNode** Root, DATATYPE Data);
BTNode* SearchBST(BTNode* Node, DATATYPE Target);
BTNode* RemoveBST(BTNode** Root, DATATYPE Target);

void PrintALLBST(BTNode* Node);

BTNode* Rebalance(BTNode** Root);

BTNode* RotateLL(BTNode* Node);
BTNode* RotateRR(BTNode* Node);
BTNode* RotateRL(BTNode* Node);
BTNode* RotateLR(BTNode* Node);

int RetHeight(BTNode* Node);
int RetDiffInHeightOfSubTree(BTNode* Node);

void Print2D(BTNode* root, int space);

int main() {

    BTNode* Root;
    BTNode* TargetNode;
    int Target;

    MakeBST(&Root);

    Target = 5;
    printf("Insert %d\n", Target);
    InsertBST(&Root, Target);
    PrintALLBST(Root);
    printf("\n");

    Target = 4;
    printf("Insert %d\n", Target);
    InsertBST(&Root, Target);
    PrintALLBST(Root);
    printf("\n");

    Target = 3;
    printf("Insert %d\n", Target);
    InsertBST(&Root, Target);
    PrintALLBST(Root);
    printf("\n");

    Target = 1;
    printf("Insert %d\n", Target);
    InsertBST(&Root, Target);
    PrintALLBST(Root);
    printf("\n");

    Target = 2;
    printf("Insert %d\n", Target);
    InsertBST(&Root, Target);
    PrintALLBST(Root);
    printf("\n");

    Target = 6;
    printf("Insert %d\n", Target);
    InsertBST(&Root, Target);
    PrintALLBST(Root);
    printf("\n");

    Target = 7;
    printf("Insert %d\n", Target);
    InsertBST(&Root, Target);
    PrintALLBST(Root);
    printf("\n");

    Target = 9;
    printf("Insert %d\n", Target);
    InsertBST(&Root, Target);
    PrintALLBST(Root);
    printf("\n");

    Target = 8;
    printf("Insert %d\n", Target);
    InsertBST(&Root, Target);
    PrintALLBST(Root);
    printf("\n");

    return 0;
}

BTNode* MakeBTNode(){
    BTNode* Node = (BTNode*)malloc(sizeof(BTNode));
    Node->Left = NULL;
    Node->Right = NULL;
    return Node;
}

DATATYPE RetData(BTNode* Node){
    return Node->Data;
}

void SaveData(BTNode* Node, DATATYPE Data){
    Node->Data = Data;
}

BTNode* RetSubTreeLeft(BTNode* Node){
    return Node->Left;
}

BTNode* RetSubTreeRight(BTNode* Node){
    return Node->Right;
}

void MakeSubTreeLeft(BTNode* Parent, BTNode* Child){
    if(Parent->Left != NULL){
        free(Parent->Left);
    }
    Parent->Left = Child;
}

void MakeSubTreeRight(BTNode* Parent, BTNode* Child){
    if(Parent->Right != NULL){
        free(Parent->Right);
    }
    Parent->Right = Child;
}

BTNode* RemoveSubTreeLeft(BTNode* Node){
    BTNode* Temp;
    if(Node != NULL){
        Temp = Node->Left;
        Node->Left = NULL;
    }
    return Temp;
}

BTNode* RemoveSubTreeRight(BTNode* Node){
    BTNode* Temp;
    if(Node != NULL){
        Temp = Node->Right;
        Node->Right = NULL;
    }
    return Temp;
}

void ChangeSubTreeLeft(BTNode* Parent, BTNode* Child){
    Parent->Left = Child;
}

void ChangeSubTreeRight(BTNode* Parent, BTNode* Child){
    Parent->Right = Child;
}

void PreorderTraversal(BTNode* Node){
    if(Node == NULL){
        return;
    }
    printf("%d ", Node->Data);
    PreorderTraversal(Node->Left);
    PreorderTraversal(Node->Right);
}

void InorderTraversal(BTNode* Node){
    if(Node == NULL){
        return;
    }
    InorderTraversal(Node->Left);
    printf("%d ", Node->Data);
    InorderTraversal(Node->Right);
}

void PostorderTraversal(BTNode* Node){
    if(Node == NULL){
        return;
    }
    PostorderTraversal(Node->Left);
    PostorderTraversal(Node->Right);
    printf("%d ", Node->Data);
}

void MakeBST(BTNode** Node){
    *Node = NULL;
}

BTNode* InsertBST(BTNode** Root, DATATYPE Data){
    if(*Root == NULL){
        *Root = MakeBTNode();
        SaveData(*Root, Data);
    }
    else if(Data < RetData(*Root)){
        InsertBST(&((*Root)->Left), Data);
        *Root = Rebalance(Root);
    }
    else if(Data > RetData(*Root)){
        InsertBST(&((*Root)->Right), Data);
        *Root = Rebalance(Root);
    }
    else{
        return NULL;
    }
    return *Root;
}

BTNode* SearchBST(BTNode* Node, DATATYPE Target){
    BTNode* Current = Node;
    DATATYPE Data;

    while(Current != NULL){
        Data = RetData(Current);

        if(Target == Data) return Current;
        else if(Target < Data) Current = RetSubTreeLeft(Current);
        else Current = RetSubTreeRight(Current);
    }
    return NULL;
}

BTNode* RemoveBST(BTNode** Root, DATATYPE Target){
    BTNode* VirtualRoot = MakeBTNode();

    BTNode* Parent = VirtualRoot;
    BTNode* Current = *Root;
    BTNode* TargetNode;

    ChangeSubTreeRight(VirtualRoot, *Root);

    while(Current != NULL && RetData(Current) != Target){
        Parent = Current;
        if(Target < RetData(Current)) Current = RetSubTreeLeft(Current);
        else Current = RetSubTreeRight(Current);
    }

    if(Current == NULL) return NULL;

    TargetNode = Current;

    if(RetSubTreeLeft(TargetNode) == NULL && RetSubTreeRight(TargetNode) == NULL){
        if(RetSubTreeLeft(Parent) == TargetNode) RemoveSubTreeLeft(Parent);
        else RemoveSubTreeRight(Parent);
    }
    else if(RetSubTreeLeft(TargetNode) == NULL || RetSubTreeRight(TargetNode) == NULL){
        BTNode* ChildofTarget;
        if(RetSubTreeLeft(TargetNode) != NULL) ChildofTarget  = RetSubTreeLeft(TargetNode);
        else ChildofTarget = RetSubTreeRight(TargetNode);

        if(RetSubTreeLeft(Parent) == TargetNode) ChangeSubTreeLeft(Parent, ChildofTarget);
        else ChangeSubTreeRight(Parent, ChildofTarget);
    }
    else{
        BTNode* MaximumNode = RetSubTreeLeft(TargetNode);
        BTNode* ParentofMaximum = TargetNode;

        DATATYPE Backup;

        while(RetSubTreeRight(MaximumNode) != NULL){
            ParentofMaximum = MaximumNode;
            MaximumNode = RetSubTreeRight(MaximumNode);
        }

        Backup = RetData(TargetNode);
        SaveData(TargetNode, RetData(MaximumNode));

        if(RetSubTreeRight(ParentofMaximum) == MaximumNode) ChangeSubTreeRight(ParentofMaximum, RetSubTreeLeft(MaximumNode));
        else ChangeSubTreeLeft(ParentofMaximum, RetSubTreeLeft(MaximumNode));

        TargetNode = MaximumNode;
        SaveData(TargetNode, Backup);
    }

    if(RetSubTreeRight(VirtualRoot) != *Root) *Root = RetSubTreeRight(VirtualRoot);

    free(VirtualRoot);
    return TargetNode;
}

void PrintALLBST(BTNode* Node){
//    PreorderTraversal(Node);
//    InorderTraversal(Node);
//    PostorderTraversal(Node);
    Print2D(Node, 0);
}

BTNode* Rebalance(BTNode** Root){
    int Diff = RetDiffInHeightOfSubTree(*Root);

    if(Diff>1){
        if(RetDiffInHeightOfSubTree(RetSubTreeLeft(*Root)) > 0){
            printf("Rotate LL\n");
            *Root = RotateLL(*Root);
        }
        else{
            printf("Rotate LR\n");
            *Root = RotateLR(*Root);
        }
    }
    if(Diff < -1){
        if(RetDiffInHeightOfSubTree(RetSubTreeRight(*Root)) < 0){
            printf("Rotate RR\n");
            *Root = RotateRR(*Root);
        }
        else{
            printf("Rotate RL\n");
            *Root = RotateRL(*Root);
        }
    }
    return *Root;
}

BTNode* RotateLL(BTNode* Node){
    BTNode* Parent;
    BTNode* Child;

    Parent = Node;
    Child = RetSubTreeLeft(Parent);

    ChangeSubTreeLeft(Parent, RetSubTreeRight(Child));
    ChangeSubTreeRight(Child, Parent);

    return Child;
}

BTNode* RotateRR(BTNode* Node){
    BTNode* Parent;
    BTNode* Child;

    Parent = Node;
    Child = RetSubTreeRight(Parent);

    ChangeSubTreeRight(Parent, RetSubTreeLeft(Child));
    ChangeSubTreeLeft(Child, Parent);

    return Child;
}

BTNode* RotateRL(BTNode* Node){
    BTNode* Parent;
    BTNode* Child;

    Parent = Node;
    Child = RetSubTreeRight(Parent);
    ChangeSubTreeRight(Parent, RotateLL(Child));

    return RotateRR(Parent);
}

BTNode* RotateLR(BTNode* Node){
    BTNode* Parent;
    BTNode* Child;

    Parent = Node;
    Child = RetSubTreeLeft(Parent);
    ChangeSubTreeLeft(Parent, RotateRR(Child));

    return RotateLL(Parent);
}

int RetHeight(BTNode* Node){
    int HeightOfLeft;
    int HeightOFRight;

    if(Node == NULL) return 0;

    HeightOfLeft = RetHeight(RetSubTreeLeft(Node));
    HeightOFRight = RetHeight(RetSubTreeRight(Node));
    if(HeightOfLeft > HeightOFRight) return HeightOfLeft+1;
    else return HeightOFRight + 1;

}

int RetDiffInHeightOfSubTree(BTNode* Node){
    int HeightOfLeft;
    int HeightOfRight;
    if(Node == NULL) return 0;
    HeightOfLeft = RetHeight(RetSubTreeLeft(Node));
    HeightOfRight = RetHeight(RetSubTreeRight(Node));

    return HeightOfLeft - HeightOfRight;
}

void Print2D(BTNode* root, int space){
    if(root == NULL) return;

    space += COUNT;
    Print2D(root->Right, space);
    printf("\n");
    for(int i = COUNT; i < space; i++){
        printf(" ");
    }
    printf("%d\n", root->Data);
    Print2D(root->Left, space);
}