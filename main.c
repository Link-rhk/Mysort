#include <stdio.h>
#include <time.h>
#include <stdlib.h>

#include "Mysort.h"

void insertion_sort_test(int ary[],int len, unsigned char order){
    list_elem *list=array_to_list(ary,10);
    if(list==NULL){

    }
    list_printf(list);
    list_printf(list_find_end(list)); 
    list_append(list,&ary[10],10);
    list_printf(list);
    list_insert_by_index(list,&ary[0],3,40);
    list_printf(list);
    list_free(list);

    list_elem *sort_list=insertion_sort_array(ary,10,order);
    list_printf(sort_list);
    list_free(sort_list);
}

int main(){
    int ary[20];
    int i=0;
    srand(time(0));
    for(i=0;i<20;++i){
        ary[i]=rand()%100;
        printf(" %d",ary[i]);
    }
    printf("\n");

    //insertion_sort_test(ary,20,0);

{   
    //int ary[20]={12,7,86,85,95,95,42,15,52,48,5,64,78,88,5,69,90,93,64,30};
    int len=20;
    int *tmp=heap_sort(ary,len,0);
    for(i=0;i<len;++i){
        printf(" %d",ary[i]);
    }
    printf("\n");}

    printf("main.c end\n");
    return 0;
}