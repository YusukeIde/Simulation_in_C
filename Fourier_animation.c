#include<stdio.h>
#include<stdlib.h>
#include<math.h>
#include<string.h>
#include <unistd.h>//For usleep

int main(int argc, char *argv[]){
    
    //start gnuplot initial settings
    FILE *gp;
    gp = popen("gnuplot -persist","w");
    //end gnuplot initial settings

	FILE   *fp_out;
	double s_freq;
	double duration;
	double t;
	double st;
	int    i;
	int    k;
	int    Kmax;
    int    K;
    int    dt;
	
	if(strcmp(argv[1],"--help")==0){
		printf("******引数は以下の通り******\n");
		printf("1.サンプリング周波数[Hz]\n");
		printf("2.出力する時間[sec]\n");
		printf("3.高調波の最大打ち切り次数\n");
		printf("4.出力ファイル名[.dat]\n");
        printf("5.描画間隔[micro sec]\n");
		exit(EXIT_SUCCESS);
	}
		
	if(argc!=6){
        printf("引数を確認して下さい．\n");
        exit(EXIT_FAILURE);
	}
    
	s_freq   =atof(argv[1]);
	duration =atof(argv[2]);
	Kmax     =atoi(argv[3]);
    dt       =atoi(argv[5]);
    
    //start gnuplot settings
    fprintf(gp, "set xlabel 't(s)'\n");
    fprintf(gp, "set ylabel 'Amplitude of the signal(V)'\n");
    fprintf(gp, "set xrange [%lf:%lf]\n",0.0,duration);
    fprintf(gp, "set yrange [%lf:%lf]\n",-0.2,1.2);
    //end gnuplot settings
    
    for(K=1; K<=Kmax; K++){
        
        //start gnuplot settings
        fprintf(gp, "set title 'The shape of square waves with K=%d'\n",K);
        //end gnuplot settings
        
        if((fp_out=fopen(argv[4],"w"))==NULL)
        {
            printf("error!:ファイル%sが開けません\n",argv[4]);
            return 0;
        }
        
        t=0.0;
        for(i=0; i<duration*s_freq; i++)
        {
            t=(double)i/s_freq;
            st=1./2.;
            for(k=1; k<=K; k++)
            {
                if(k%2==1)
                {
                    st+=(2./(k*M_PI))*sin(k*t);
                }
            }
            fprintf(fp_out,"%lf %lf\n",t,st);
        }
        fclose(fp_out);
    
        //start gnuplot plot
        fprintf(gp, "plot '%s' w l\n",argv[4]);
        fflush(gp);
        //end gnuplot plot
    
        usleep(dt);//sleep in micro second
    }

    //start gnuplot final settings
	fprintf(gp, "exit\n");
	fflush(gp);
    pclose(gp);
    //end gnuplot final settings
    
	return 0;
}
