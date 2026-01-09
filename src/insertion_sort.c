#include "Mysort.h"

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
list_elem* list_insert_by_sort(list_elem *list_head,int data, unsigned char order){
    if(list_head==NULL){
        list_head=(list_elem*)malloc(sizeof(list_elem));
        if(list_head==NULL){
            DEBUG_PRINTF("malloc failed!!\n");
            return NULL;
        }
        list_head->prt=NULL;
        list_head->data=data;
    }else{
        list_elem *list_prt=list_head;
        list_elem *list_Pprt=NULL;//record the front of the list_prt.
        list_elem *tmp_prt=(list_elem*)malloc(sizeof(list_elem));
        if(tmp_prt==NULL){
            DEBUG_PRINTF("malloc failed!!\n");
            return NULL;
        }
        tmp_prt->prt=NULL;
        tmp_prt->data=data;

        int deta=0;
        while(1){
            //usleep(500*1000);
            //DEBUG_PRINTF("%d|%d\n",data,list_prt->data);
            deta=data-list_prt->data;
            if(deta>0) deta=1;
            else if(deta<0) deta=-1;
            else{
                tmp_prt->prt=list_prt->prt;
                list_prt->prt=tmp_prt;
                return list_head;
            }

            if(order){//Ascend order
                if(deta>0){
                    if(list_prt->prt!=NULL){
                        list_Pprt=list_prt;
                        list_prt=list_prt->prt;
                    }else{//the end of the list.
                        list_prt->prt=tmp_prt;
                        //list_printf_dubug(list_head,__FUNCTION__,__LINE__);
                        return list_head;
                    }
                }else{
                    if(list_Pprt==NULL){
                        tmp_prt->prt=list_prt;
                        list_head=tmp_prt;
                        //list_printf_dubug(list_head,__FUNCTION__,__LINE__);
                        return list_head;
                    }else{
                        list_Pprt->prt=tmp_prt;
                        tmp_prt->prt=list_prt;
                        list_prt=tmp_prt->prt;
                        //list_printf_dubug(list_head,__FUNCTION__,__LINE__);
                        return list_head;
                    }
                }
            }else{//Descend order
                if(deta>0){
                    if(list_Pprt==NULL){
                        tmp_prt->prt=list_prt;
                        list_head=tmp_prt;
                        //list_printf_dubug(list_head,__FUNCTION__,__LINE__);
                        return list_head;
                    }else{
                        list_Pprt->prt=tmp_prt;
                        tmp_prt->prt=list_prt;
                        list_prt=tmp_prt->prt;
                        //list_printf_dubug(list_head,__FUNCTION__,__LINE__);
                        return list_head;
                    }
                }else{
                    if(list_prt->prt!=NULL){
                        list_Pprt=list_prt;
                        list_prt=list_prt->prt;
                        //list_printf_dubug(list_head,__FUNCTION__,__LINE__);
                    }else{//the end of the list.
                        list_prt->prt=tmp_prt;
                        //list_printf_dubug(list_head,__FUNCTION__,__LINE__);
                        return list_head;
                    }
                }
            }
        }
    }

    return NULL;
}

list_elem *insertion_sort_array(int array[],int len,unsigned char order){
    list_elem *list_head=NULL;
    list_head=(list_elem*)malloc(sizeof(list_elem));
    if(list_head==NULL){
        DEBUG_PRINTF("malloc error\n");
        return NULL;
    }
    list_head->prt=NULL;
    list_head->data=*array;

    list_elem *tmp=NULL;
    int i=0;
    for(i=1;i<len;++i){
        tmp=list_insert_by_sort(list_head,array[i],order);
        if(NULL==tmp){
            DEBUG_PRINTF("error\n");
            list_free(list_head);
            list_head=NULL;
            break;
        }
        list_head=tmp;
    }

    return list_head;
}