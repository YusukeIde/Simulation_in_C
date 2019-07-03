#include<stdio.h>

int main(void){
    
    FILE *fp;
    int i;
    char filename[100];
    
    for(i=1;i<=5;i++){
        sprintf(filename,"test%d.dat",i);
        fp=fopen(filename,"w");
        fprintf(fp,"%d\n",i);
        fclose(fp);
    }
    
    return 0;
    
}