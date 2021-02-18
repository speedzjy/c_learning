#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct HashTable {
    char **elem;
    int size;
} HashTable;

void init(HashTable *h);
int hash(HashTable *h, char value[]);
int search(HashTable *h, char value[], int *pos, int *times);
int insert(HashTable *h, char value[]);
void recreate(HashTable *h);

void init(HashTable *h) {
    h->size = 2000;
    h->elem = (char **)malloc(sizeof(char *) * h->size);
    for (int i = 0; i < h->size; i++) {
        h->elem[i] = NULL;
    }
}

int hash(HashTable *h, char value[]) {
    int code = 0;
    for (size_t i = 0; i < strlen(value); i++) {
        code = (code * 256 + value[i] + 128) % h->size;
    }
    return code;
}

int search(HashTable *h, char value[], int *pos, int *times) {
    *pos = hash(h, value);
    *times = 0;
    while (h->elem[*pos] != NULL && strcmp(h->elem[*pos], value) != 0) {
        (*times)++;
        if (*times < h->size) {
            *pos = (*pos + 1) % h->size;
        } else {
            return 0;
        }
    }
    if (h->elem[*pos] != NULL && strcmp(h->elem[*pos], value) == 0) {
        return 1;
    } else {
        return 0;
    }
}

int insert(HashTable *h, char value[]) {
    int pos, times;
    if (search(h, value, &pos, &times)) {
        return 2;
    } else if (times < h->size / 2) {
        h->elem[pos] = (char *)malloc(strlen(value) + 1);
        strcpy(h->elem[pos], value);
        return 1;
    } else {
        recreate(h);
        insert(h, value);
        return 0;
    }
}

// 请在下面实现哈希表重建函数 recreate
void recreate(HashTable *h) {
    char **temp_elem;
    temp_elem = (char **)malloc(sizeof(char *) * h->size);
    for (int i = 0; i < h->size; i++) {
        if (h->elem[i] != NULL) {
            temp_elem[i] = (char *)malloc(strlen(h->elem[i]) + 1);
            strcpy(temp_elem[i], h->elem[i]);
        }
        else {
            temp_elem[i] = NULL;
        }
    }
    for (int i = 0; i < h->size; i++) {
        if (h->elem[i] != NULL) {
            free(h->elem[i]);
        }
    }
    free(h->elem);
    int copy_size = h->size;
    h->size = h->size * 2;
    h->elem = (char **)malloc(sizeof(char *) * h->size);
    for (int i = 0; i < h->size; i++) {
        h->elem[i] = NULL;
    }
    for (int i = 0; i < copy_size; i++) {
        if (temp_elem[i] != NULL) {
            insert(h, temp_elem[i]);
        }
    }
    for (int i = 0; i < copy_size; i++) {
        if (temp_elem[i] != NULL) {
            free(temp_elem[i]);
        }
    }
    free(temp_elem);
}

void clear(HashTable *h) {
    for (int i = 0; i < h->size; ++i) {
        if (h->elem[i] != NULL) {
            free(h->elem[i]);
        }
    }
    free(h->elem);
    free(h);
}

int main() {
    HashTable *hashtable = (HashTable*)malloc(sizeof(HashTable));
    init(hashtable);
    char buffer[1000];
    int n;
    scanf("%d", &n);
    for (int i = 1; i <= n; i++) {
        scanf("%s", buffer);
        int ans = insert(hashtable, buffer);
        if (ans == 0) {
            printf("recreate while insert!\n");
        } else if (ans == 1) {
            printf("insert success!\n");
        } else if (ans == 2) {
            printf("It already exists!\n");
        }
    }
    int temp_pos, temp_times;
    scanf("%s", buffer);
    if (search(hashtable, buffer, &temp_pos, &temp_times)) {
        printf("search success!\n");
    } else {
        printf("search failed!\n");
    }
    clear(hashtable);
    return 0;
}