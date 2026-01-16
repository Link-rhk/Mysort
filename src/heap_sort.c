#include "Mysort.h"
#include <unistd.h>

#define _CHANG_VALUE_(tmp, value0, value1,index) {tmp=value0;value0=value1;value1=tmp;tmp=index;}

void build_the_heap_rule(int ary[], int len, unsigned char order){
    int over_note=0;
    int Lsub_note=0;
    int Rsub_note=0;

    int sub_len=len;
    int i=0,j=0;
    int deta=0,tmp=0;
    while(1){
/*         usleep(300*1000);
        printf("%d\t:ary:",i);
        for(j=0;j<len;++j){
            printf(" %d",ary[j]);
        }
        printf("\n"); */

        tmp=i;
        if((i+1)*2<=sub_len-1){//have two sub-note.
            deta=ary[(i+1)*2]-ary[(i+1)*2-1];
            if(order){//while order=1, is ascend sort. the larger elem will be the over_note.
                if(deta>=0 && ary[(i+1)*2]>ary[i]) _CHANG_VALUE_(tmp, ary[(i+1)*2], ary[i],(i+1)*2)
                else if(deta<=0 && ary[(i+1)*2-1]>ary[i]) _CHANG_VALUE_(tmp, ary[(i+1)*2-1], ary[i],(i+1)*2-1)
            }else{//while order=0, is descend sort. the smaller elem will be the over_note.
                if(deta<=0 && ary[(i+1)*2]<ary[i]) _CHANG_VALUE_(tmp, ary[(i+1)*2], ary[i],(i+1)*2)
                else if(deta>0 && ary[(i+1)*2-1]<ary[i]) _CHANG_VALUE_(tmp, ary[(i+1)*2-1], ary[i],(i+1)*2-1)
            }
        }else if((i+1)*2-1<=sub_len-1){//have one sub-note
            deta=ary[(i+1)*2-1]-ary[i];
            if(order==1 && deta>=0)//while order=1, is ascend sort. the larger elem will be the over_note.
                _CHANG_VALUE_(tmp, ary[(i+1)*2-1], ary[i],(i+1)*2-1)
            else if(order==0 && deta<=0)
                _CHANG_VALUE_(tmp, ary[(i+1)*2-1], ary[i],(i+1)*2-1)
        }else{//there is not a sub-note
            if(sub_len==1){
                return;
            }
        }

        if(i==tmp){//the rule the of heap is completed.
            _CHANG_VALUE_(tmp, ary[0], ary[sub_len-1],0)
            --sub_len;
        }
        i=tmp;
    }
}

int *heap_sort(int ary[], int len, unsigned char order){
    if(len==0){
        DEBUG_PRINTF("error input");
        return ary;
    }else if(len==1){
        return ary;
    }

    unsigned char Tflag=(len-1)%2;//-1 for match the subscript number.
    int last_label=len-1;

    int deta=0;
    int tmp=0;

    int i=len-1,j=0;
    unsigned char chang_flag=0;
    for(;;){
/*         usleep(300*1000);
        printf("heap_sort|%d\t:ary:",i);
        for(j=0;j<len;++j){
            printf(" %d",ary[j]);
        }
        printf("\n"); */

        deta=ary[(i-2)/2]-ary[i-1];
        if((order==1 && deta<0)//while order=1, is ascend sort. the larger elem will be the over_note.
        ||(order==0 && deta>0)){//while order=0, is descend sort. the smaller elem will be the over_note.
            _CHANG_VALUE_(tmp,ary[(i-2)/2],ary[i-1],i-1)
            chang_flag=1;
        }

        if(chang_flag==0 && i==2) break;
        else if(chang_flag==1){
            chang_flag=0;
            if(tmp*2<len-1){
                i=tmp*2;
            }else{
                --i;
            }
        }
        else if(i<=0){
            i=len-1-Tflag;
            chang_flag=0;
        }else{
            --i;
        }
    }

/*     if(Tflag){
        deta=ary[(len-2)/2]-ary[len-1];
        if((order==1 && deta<=0)//while order=1, is ascend sort. the larger elem will be the over_note.
        ||(order==0 && deta>=0)){//while order=0, is descend sort. the smaller elem will be the over_note.
            _CHANG_VALUE_(tmp,ary[(len-2)/2],ary[len-1],0)
        }
    }
    int i=len-1-Tflag;//after this i will be an even number.

    for(;;){
        //DEBUG_PRINTF("%d-%d\t:%d\t|%d\t|%d\t\n",(int)order,i,ary[(i-2)/2],ary[i-1],ary[i]);
        deta=ary[i]-ary[i-1];
        if(order){//while order=1, is ascend sort. the larger elem will be the over_note.
            if(deta>=0 && ary[i]>ary[(i-2)/2]){ _CHANG_VALUE_(tmp,ary[i],ary[(i-2)/2],i) chang_flag=1;}
            else if(deta<=0 && ary[i-1]>ary[(i-2)/2]){ _CHANG_VALUE_(tmp,ary[i-1],ary[(i-2)/2],i-1) chang_flag=1;}
        }else{//while order=0, is descend sort. the smaller elem will be the over_note.
            if(deta<=0 && ary[i]<ary[(i-2)/2]){ _CHANG_VALUE_(tmp,ary[i],ary[(i-2)/2],i) chang_flag=1;}
            else if(deta>=0 && ary[i-1]<ary[(i-2)/2]){ _CHANG_VALUE_(tmp,ary[i-1],ary[(i-2)/2],i-1) chang_flag=1;}
        }
        //DEBUG_PRINTF("%d-%d\t:%d\t|%d\t|%d\t\n",(int)order,i,ary[(i-2)/2],ary[i-1],ary[i]);

        if(chang_flag==0 && i==2) break;
        else if(i<=0){
            i=len-1-Tflag;
            chang_flag=0;
        }else{
            i-=2;
        }
    } */
/*     printf("heap_sort:ary:");
    for(i=0;i<len;++i){
        printf(" %d",ary[i]);
    }
    printf("\n");  */
    _CHANG_VALUE_(tmp,ary[0],ary[len-1],0);//the last elem is completed the compare.

    build_the_heap_rule(ary,len-1,order);

    return ary;
}