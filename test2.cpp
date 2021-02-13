#include <math.h>
#include <iostream>
#include <stack>

using namespace std;

int precede(char a,char b) {
    if((a=='*'||a=='/')&&(b=='+'|| b=='-')){
        return 1;
    }
    else{
        return 0;
    }
}

stack<int> calcu(stack<int> cal,char theta){
    int a=cal.top();
    cal.pop();
    int b=cal.top();
    cal.pop();
    if (theta == '+') {
        cal.push(b+a);
        return cal;
    } 
     else if(theta == '-'){
        cal.push(b - a);
        return cal;
    }   
    else if(theta == '*'){
        cal.push(b * a);
        return cal;
    } 
    else{
        cal.push(b / a);
        return cal;
    }
}

int main(){
    stack<char> ope;
    stack<int> cal;
    char *arr=(char *)malloc(sizeof(char));
    char *back=(char *)malloc(sizeof(char));
    arr[0]='0';
    int length=0;
    for(int i=0;;i++){
        scanf("%c",&arr[i]);
        //printf("%c",arr[i]);
        if(arr[i]=='\n'){
            break;
        }
        length ++;
    }
    int count=0;
    for(int j=0;j<length;j++){
        if(arr[j]>='0' && arr[j]<='9'){
            back[count++]=arr[j];
        }
        else{
            if(ope.size()==0 || precede(arr[j],ope.top())==1){
                ope.push(arr[j]);
            }
            else{
                while(precede(arr[j],ope.top())==0){
                    back[count++]=ope.top();
                    ope.pop();
                    if(ope.size()==0){
                        ope.push(arr[j]);
                        break;
                    }
                }                
            }
        }
    }
    while(ope.size()!=0){
        back[count++]=ope.top();
        ope.pop();
    }
    for(int j=0;j<length;j++){
        printf("%c",back[j]);
    }
    for(int m=0;m<length;m++){
        if(back[m]>='0' && back[m]<='9'){
            cal.push(back[m]-'0');
        }
        else{
            cal=calcu(cal,back[m]);
        }
    }
    printf("\n");
    printf("%d",cal.top());
    return 0;
}