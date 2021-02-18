#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <iostream>
#include <stack>
#include <ctype.h>
using namespace std;

typedef struct Node{
    char data;
    struct Node *lchild,*rchild;
}Node;

Node *gshell(char str[]);
void Destory(Node *T);
Node *Find(Node *T,char x);
void Delete(Node *T,char x);
void output(Node *Tree);

Node* init(char data) {
    Node *node =(Node *)malloc(sizeof(Node));
    node->data = data;
    node->lchild = NULL;
    node->rchild = NULL;
    return node;
}

void preorder(Node *node) {
    printf("%c ", node->data);
    if (node->lchild != NULL) {
        preorder(node->lchild);
    }
    if (node->rchild != NULL) {
        preorder(node->rchild);
    }
}


int main(){
    char pstr[100];
    long long k;
    scanf("%s",pstr);
    getchar();
    char m;
    scanf("%c",&m);
    //printf("%d",strlen(m));
    //printf("m:%d\n",m-' ');
   // printf("1\n");
    if(m-'0'==-48)
        return 0;
    Node *tree=gshell(pstr);
    preorder(tree);
    Node *p=Find(tree,m);
    if(p==NULL){
        output(tree);
        return 0;
    }
    else{
        if(p==tree){
            Destory(p);
            return 0;
        }
        Destory(p);
    }
    output(tree);
    return 0;
}

void output(Node *tree){
    printf("%c",tree->data);
    if(tree->lchild!=NULL){
        printf("(");
        output(tree->lchild);
        if(tree->rchild==NULL)
            printf(")");
    }
    if(tree->rchild!=NULL){
        if(tree->lchild==NULL)
            printf("(");
        printf(",");
        output(tree->rchild);
        printf(")");
    }
}

void Destory(Node *T)
{
    if(T!=NULL)
    {
        Destory(T->lchild);
        Destory(T->rchild);
        free(T);
    }
}

Node *Find(Node *T,char x)
{
    Node *p;
    if(T==NULL)
        return NULL;
    else if(T->data==x)
        return T;
    else if(T->lchild!=NULL&&T->lchild->data==x)
    {
        p=T->lchild;
        T->lchild=NULL;
        return p;
    }
    else if(T->rchild!=NULL&&T->rchild->data==x)
    {
        p=T->rchild;
        T->rchild=NULL;
        return p;
    }
    else
    {
        p=Find(T->lchild,x);
        if(p!=NULL)
            return p;
        else
            return Find(T->rchild,x);
    }
}
 

Node *gshell(char str[]){
    stack<Node *> tree;
    int k=-1;
    Node *root;
    Node *p=init('0');
    for(int i=0;i<strlen(str);i++){
        //printf("k= %d   %c \n",k,str[i]);
        if(str[i]=='('){
            k=0;
            tree.push(p);
        }
        else if(str[i]==','){
            k=1;
        }
        else if(str[i]==')'){
            tree.pop();
        }
        else{
            
            Node *temp=init(str[i]);
            if(k==-1){
                //printf("else k==-1\n");
                root=temp;
                tree.push(temp);
            }
            if(k==0){
                if(tree.top()==p)
                    tree.pop();
                Node *top=tree.top();
                top->lchild=temp;
                tree.push(temp);
            }
            if(k==1){
                tree.pop();
                Node *top=tree.top();
                top->rchild=temp;
                tree.push(temp);
            }
        }
    }
    return root;
}
