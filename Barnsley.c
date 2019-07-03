#include<stdio.h>
#include<stdlib.h>
#include<math.h>
#include<string.h>
#include<time.h>
#include <unistd.h>//For usleep

void calc_next(double *x, double *y);
double rand_uniform(void);

int main(int argc, char *argv[]){
    
    srand((unsigned int)time(NULL));
    
    //start gnuplot initial settings
    FILE *gp;
    gp = popen("gnuplot -persist","w");
    //end gnuplot initial settings

	FILE   *fp_out;
	double x;
	double y;
	int    Kmax;
    int    K;
//    int    dt;
	
	if(strcmp(argv[1],"--help")==0){
		printf("******引数は以下の通り******\n");
		printf("1.初期x座標\n");
		printf("2.初期y座標\n");
		printf("3.繰り返し回数[回]\n");
		printf("4.出力ファイル名[.dat]\n");
//        printf("5.描画間隔[micro sec]\n");
		exit(EXIT_SUCCESS);
	}
		
	if(argc!=5){
        printf("引数を確認して下さい．\n");
        exit(EXIT_FAILURE);
	}
    
	x       =atof(argv[1]);
	y       =atof(argv[2]);
	Kmax    =atoi(argv[3]);
//    dt      =atoi(argv[5]);
    
    //start gnuplot settings
//    fprintf(gp, "set xlabel 't(s)'\n");
//    fprintf(gp, "set ylabel 'Amplitude of the signal(V)'\n");
//    fprintf(gp, "set xrange [%lf:%lf]\n",0.0,duration);
//    fprintf(gp, "set yrange [%lf:%lf]\n",-0.2,1.2);
    //end gnuplot settings
    
    if((fp_out=fopen(argv[4],"w"))==NULL){
        printf("error!:ファイル%sが開けません\n",argv[4]);
        return 0;
    }
    fprintf(fp_out,"%lf %lf\n",x,y);
    fclose(fp_out);

    for(K=0; K<=Kmax; K++){
        if(K%1000 == 0){
            //start gnuplot settings
            fprintf(gp, "set title 'The Barnsley fern with K=%d'\n",K);
            //end gnuplot settings
            
            //start gnuplot plot
            fprintf(gp, "plot '%s'\n",argv[4]);
            fflush(gp);
            //end gnuplot plot
    
//            usleep(dt);//sleep in micro second
        }
        if((fp_out=fopen(argv[4],"a"))==NULL){
            printf("error!:ファイル%sが開けません\n",argv[4]);
            return 0;
        }
        
        calc_next(&x,&y);
        
        fprintf(fp_out,"%lf %lf\n",x,y);
        fclose(fp_out);
    }

    //start gnuplot final settings
	fprintf(gp, "exit\n");
	fflush(gp);
    pclose(gp);
    //end gnuplot final settings
    
	return 0;
}

void calc_next(double *x, double *y){
    double a,b,c,d,e,f;
    double r;
    
    r=rand_uniform();
    
    if(r<=0.01){
        a=0;b=0;c=0;d=0.16;e=0;f=0;
    }else if(r<=0.86){
        a=0.85;b=0.04;c=-0.04;d=0.85;e=0;f=1.6;
    }else if(r<=0.93){
        a=0.20;b=-0.26;c=0.23;d=0.22;e=0;f=1.6;
    }else{
        a=-0.15;b=0.28;c=0.26;d=0.24;e=0;f=0.44;
    }
    
    *x=a*(*x)+b*(*y)+e;
    *y=c*(*x)+d*(*y)+f;
}

double rand_uniform(void){
    return (double)rand()/RAND_MAX;
}