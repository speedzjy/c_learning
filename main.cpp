#include<iostream>
#include <vector>
#include <time.h>
#include "hello.h"
using namespace std;

int countPrimes(int n);

int main(){
    system("chcp 65001");
    //printhello();
    int count=0;
    clock_t start,finish; //
    double Times=0;
    start=clock();
    count=countPrimes(100000000);
    finish=clock();
    Times=(double)(finish-start)/CLOCKS_PER_SEC;
    cout<<"素数个数: "<<count<<endl;
    cout<<"运行时间(秒): "<<Times<<"s"<<endl;
    return 0;
}

int countPrimes(int n){
    vector<int> nums(n,1);
    int count=0;
    for(int i=2;i*i<n;i++) {
        if(nums[i]!=0) {
            for(int j = 2; i*j<n;j++) {
                nums[i*j]=0;
            }
        }
    }
    for(int i=2;i<n;i++){
        if(nums[i]!=0){
            count++;
            //cout<<i<<" ";
        }
    }
    return count;
}