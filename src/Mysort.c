#include "Mysort.h"
#include <stdlib.h>

void list_free(list_elem *list_head){
    list_elem *list_prt=list_head;
    list_elem *list_free=list_prt;
    while(1){
        if(list_prt==NULL){
            break;
        }else{
            list_prt=list_prt->prt;
            free(list_free);
            list_free=list_prt;
        }
    }
}

void list_printf(list_elem *list_head){
    printf("list_printf:");
    list_elem *list_prt=list_head;
    while(list_prt!=NULL){
        printf(" %d",list_prt->data);
        list_prt=list_prt->prt;
    }
    printf("\n");
}

void list_printf_dubug(list_elem *list_head,const char *funcname, int line){
    printf("%s:%d:list_printf:",funcname,line);
    list_elem *list_prt=list_head;
    while(list_prt!=NULL){
        printf(" %d",list_prt->data);
        list_prt=list_prt->prt;
    }
    printf("\n");
}

list_elem *list_find_end(list_elem *list_head){
    if(list_head==NULL){
        DEBUG_PRINTF("empty Input!!\n");
        return NULL;
    }

    list_elem *list_ret=list_head;
    while(1){
        if(list_ret->prt==NULL) break;
        list_ret=list_ret->prt;
    }
    return list_ret;
}

unsigned char list_append(list_elem *list_head, int elem[], int len){
    if(len<=0 || list_head==NULL){
        DEBUG_PRINTF("error input\n");
        return 1;
    }
    list_elem *list_end=list_find_end(list_head);
    list_end->prt=NULL;//for the saft of 
    list_elem *list_prt=list_find_end(list_head);
    int i=0;
    for(i=0;i<len;++i){
        list_prt->prt=(list_elem*)malloc(sizeof(list_elem));
        if(list_prt->prt==NULL){
            DEBUG_PRINTF("malloc failed!!\n");
            if(list_end->prt!=NULL){
                list_free(list_end->prt);
                return 2;
            }
        }
        list_prt->prt->prt=NULL;
        list_prt->prt->data=elem[i];
        list_prt=list_prt->prt;
    }

    return 0;
}

/// @brief insert elems into the list by index.
/// @param list_head [input/ouput] the head of the list.
/// @param elem the array will be inserted.
/// @param len the len of the array.
/// @param index insert count. if it out of the len of the list, it will insert at the end of the list.
/// @return 0 if successful.
unsigned char list_insert_by_index(list_elem *list_head, int elem[], int len, int index){
    if(len<=0){
        DEBUG_PRINTF("error input\n");
        return 1;
    }
    
    list_elem *list_tail=list_head;//record the tail of the head-list.
    int i=0;
    for(i=0;i<index-1;++i){
        if(list_tail->prt!=NULL)
            list_tail=list_tail->prt;
        else
            break;
    }
    list_elem * list_tmp_head=list_tail->prt;//record the head of the follow-list.
    list_tail->prt=NULL;//cut it by index

    list_elem *list_prt=list_tail;
    i=0;
    for(i=0;i<len;++i){
        list_prt->prt=(list_elem*)malloc(sizeof(list_elem));
        if(list_prt->prt==NULL){
            DEBUG_PRINTF("malloc failed!!\n");
            if(list_tail->prt!=NULL){
                list_free(list_tail->prt);
                list_tail->prt=list_tmp_head;
                return 2;
            }
        }
        list_prt->prt->prt=NULL;
        list_prt->prt->data=elem[i];
        list_prt=list_prt->prt;
    }
    list_prt->prt=list_tmp_head;

    return 0;
}

list_elem *array_to_list(int array[],int len){
    if(array==0 || len<=0){
        DEBUG_PRINTF("error intput!!");
        return NULL;
    }
    int *arr_head=array;
    list_elem *list_head=NULL;
    list_head=(list_elem*)malloc(sizeof(list_elem));
    if(list_head==NULL){
        DEBUG_PRINTF("malloc failed!!\n");
        return NULL;
    }
    list_head->prt=NULL;//must set NULL here for free_list() this will be the confident of the loop end.
    list_head->data=*arr_head;

    list_elem *list_prt=list_head;
    int i=0;
    for(i=1;i<len;++i){
        list_prt->prt=(list_elem*)malloc(sizeof(list_elem));
        if(list_prt->prt==NULL){
            list_free(list_head);
            DEBUG_PRINTF("malloc failed!!\n");
            return NULL;
        }
        list_prt->prt->prt=NULL;//must set NULL here for free_list() this will be the confident of the loop end.
        list_prt->prt->data=*(arr_head+i);
        list_prt=list_prt->prt;
    }

    return list_head;
}