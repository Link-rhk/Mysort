#ifndef _MYSORT_H_
#define _MYSORT_H_

#include <stdio.h>
#define DEBUG_PRINTF(fmt,...) printf("%s:%d: "fmt, __FUNCTION__, __LINE__, ##__VA_ARGS__)
typedef struct list_elem_type{
    int data;
    struct list_elem_type* prt;
}list_elem;

void list_free(list_elem *list_head);
void list_printf(list_elem *list_head);
void list_printf_dubug(list_elem *list_head,const char *funcname, int line);
list_elem *list_find_end(list_elem *list_head);

unsigned char list_append(list_elem *list_head, int elem[], int len);
unsigned char list_insert_by_index(list_elem *list_head, int elem[], int len, int index);

//list_elem *list_insert_by_sort(list_elem *list_head,int data, unsigned order);
list_elem *insertion_sort_array(int array[],int len,unsigned char order);

//void build_the_heap_rule(int ary[], int len, unsigned char order);
int *heap_sort(int ary[], int len, unsigned char order);

/// @brief tansform array to list .
/// @param array [input] the array wait to be transform.
/// @param len [input] the len of array.
/// @return the target list. will return NULL if failed.
list_elem *array_to_list(int array[],int len);

typedef struct tree_elem_type{
    int data;
    struct list_elem_type* left;
    struct list_elem_type* right;
}tree_elem;

#endif//_MYSORT_H_