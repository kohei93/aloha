#include<stdio.h>
#include<stdlib.h>
#include "MT.h"
#include<time.h>
#include<math.h>


#ifndef DEFINE_H
#define DEFINE_H
#include "./define.h"
#endif

#ifndef FUNCTION_H
#define FUNCTION_H
#include "./function.h"
#endif

//一様乱数
double Uniform( void ){
    return genrand_real3();
}

//指数分布
double rand_exp( double lambda ){
    return -log(Uniform())/lambda;
}

//最小値出力
void sort(struct info node[NODE], int *num, double *minn){
	double min=10000;
	double max=0;
  	int min_num=0;
   	int max_num=0;
	double array[NODE] = {0};
  	
   	for(int i=0;i<NODE;i++){
   		array[i] = node[i].start;
	}

   	for(int i=0;i<NODE;i++){
   		double a = array[i];
   		if(a<min){
   			min = a;
   			min_num = i;
   			// printf("min%lf\n",a );
   		}
   		if(a>max){
   			max = a;
   			max_num = i;
   		}
	}
	*num=min_num;
	*minn=min;
	// printf("sort %d %lf \n",*num,*minn );
}


// void make_list(double list[NODE]){
// 	for(int i=0; i<NODE; i++){
// 		list[NODE] = 0;
// 	}
// }

// int check_list(double list[NODE]){
// 	int sum=0;
// 	for(int i=0; i<NODE; i++){
// 		sum +=list[i];
// 	}
// 	return sum;
// }




int main(void){
    init_genrand((unsigned)time(NULL)); //ランダム初期化

	for(int i_node=10; i_node<NODE; i_node+=10){
		printf("\n");
	  	struct info node[i_node];

	  	//各ノードのパラメータ
	  	double lambda=0.5;
	    for(int i=0;i<i_node;i++){
	    	node[i].x = X*Uniform();
	    	node[i].y = Y*Uniform();
	   		node[i].start = rand_exp(lambda);
	   		node[i].finish = node[i].start + transtime;
	   		printf("%lf\n",node[i].start );
	   	}

		double time=0;
		int loss=0;
		int success=0;
		int *id_trans = (int*)malloc(sizeof(int)*3);
		double *min = (double*)malloc(sizeof(double)*3);


		while(time<TIME){

	   		//送信時間，ノード
	   		sort(node, id_trans, min);
			node[*id_trans].flag_trans = 1;
	   		time = *min;
	   		// printf("min %d %lf\n",*id_trans,*min);

	   		//flag checker
	   		for(int i=0; i<i_node; i++){
	   			if(time > node[i].finish){
	  				node[i].flag_coll = 0;
	  				node[i].flag_trans = 0;
	  				node[i].finish = node[i].start + transtime;
	  			}
	   		}
	   		//衝突決定
	   		for(int i=0;i<i_node;i++){
				if(i != *id_trans){
	   				double dif = abs(time-node[i].start);
		   			//送信中に他端末がパケット生起
		   			if(dif < transtime){
		   				//collision, 送信中フラグ
		   				node[*id_trans].flag_coll = 1;
		   				// printf("   loss%d and %d dif=%lf\n",*id_trans,i,dif);
		   			//パケット生起時に他端末が送信中
		   			}else if(node[i].flag_trans == 1){
						node[*id_trans].flag_coll = 1;
		   				// printf("   loss%d and %d\n",*id_trans,i);
		   			}
	   			}
	   		}


	   		//loss数，success数のカウント
	   		if(node[*id_trans].flag_coll == 1){
	   			loss++;
	   		}else{
	   			success++;
	   		}


			//送信タイミング更新
	   		node[*id_trans].start += rand_exp(lambda);
			//transmit success
		}
		printf("success= %d loss= %d \n",success,loss);

		free(id_trans);
		free(min);

	}//node
	return 0;

}