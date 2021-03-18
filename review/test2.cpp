#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <algorithm>
#include <iostream>

using namespace std;

typedef struct Node {
    int data;
    int num;
}Node;

bool cmp(Node *a,Node *b) {
    if (a->data >= b->data)
        return 1;
    else
        return 0;
}

void quick_sort(Node **arr, int left, int right) {
    if (left > right) return ;
    Node *pivot = arr[left];
    int low = left, high = right;
    while (low < high) {
        while (low < high && arr[high]->data >= pivot->data) --high;
        arr[low] = arr[high];
        while (low < high && arr[low]->data < pivot->data) ++low;
        arr[high] = arr[low];
    }
    arr[low] = pivot;
    quick_sort(arr, left, low - 1);
    quick_sort(arr, low + 1, right);
}

int search(Node **arr, int length, int value) {
    int left = 0, right = length - 1;
    while (left <= right) {
        int mid = (left + right) / 2;
        if (arr[mid]->data == value) {
            return arr[mid]->num;
        }
        else if (arr[mid]->data < value) {
            left = mid + 1;
        }
        else {
            right = mid - 1;
        }
    }
    return -1;
}
int main(){
    int n;
    scanf("%d", &n);
    Node **arr = (Node **)malloc(sizeof(Node*) * n);
    for (int i = 0; i < n; i++) {
        arr[i] = (Node *)malloc(sizeof(Node));
        arr[i]->num = i;
        scanf("%d", &(arr[i]->data));
    }
    int target; scanf("%d", &target);
    //quick_sort(arr,0,n-1);
    sort(arr,arr + n,cmp);

    for (int i = 0; i < n; i++) {
        printf("%d ",arr[i]->data);
    }
    for (int i = 0; i < n; i++) {
        if (arr[i]->data > target) {
            continue;
        }
        int ans = search(arr,n,target - arr[i]->data);
        if (ans != -1) {
            if (arr[i]->num < ans)
                printf("%d %d",arr[i]->num + 1, ans + 1);
            else 
                printf("%d %d", ans + 1, arr[i]->num + 1);
            break;
        }
    }
    return 0;
}