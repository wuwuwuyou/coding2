

//#include "fun.h"
#include <stdio.h>
#include <stdlib.h>
char** LU_4(int **pp1,char **coding2,int k,int r,int p,int tau,int M,int blocksize){
extern void galois_region_xor1(   char *r1,         /* Region 1 */
                                  char *r2,         /* Region 2 */
                                  char *r3,         /* Sum region (r3 = r1 ^ r2) -- can be r1 or r2 */
                                  int nbytes);
extern char** shift_value(int b1, int tau,int p,int M);
extern int finite_mod(int i,int M);
printf("\nLU---r=4-------------------------------\n");
if(r!=4){fprintf(stderr,  "r shoule be equal to 4 \n");
			exit(0);}
int i,j,i1,j1;
char **U1;
char **U2;
char **U3;
char **L1;
char **L2;
char **L3;
U1 = (char **)malloc(sizeof(char*)*r);
for (i = 0; i <r ; i++) {
U1[i] = (char *)malloc(sizeof(char)*r);}
U2 = (char **)malloc(sizeof(char*)*r);
for (i = 0; i <r ; i++) {
U2[i] = (char *)malloc(sizeof(char)*r);}
U3 = (char **)malloc(sizeof(char*)*r);
for (i = 0; i <r ; i++) {
U3[i] = (char *)malloc(sizeof(char)*r);}
L1 = (char **)malloc(sizeof(char*)*r);
for (i = 0; i <r ; i++) {
L1[i] = (char *)malloc(sizeof(char)*2*r);}			
L2 = (char **)malloc(sizeof(char*)*r);
for (i = 0; i <r ; i++) {
L2[i] = (char *)malloc(sizeof(char)*2*r);}	
L3 = (char **)malloc(sizeof(char*)*r);
for (i = 0; i <r ; i++) {
L3[i] = (char *)malloc(sizeof(char)*2*r);}

char *shift1;
shift1 = (char *)malloc(sizeof(char)*M);

printf("LU--begin---\n");	
			


			U1[2][3]=pp1[1][k];
			U2[1][2]=pp1[1][k];
			U2[2][3]=pp1[1][k+1];
			U3[0][1]=pp1[1][k];
			U3[1][2]=pp1[1][k+1];
			U3[2][3]=pp1[1][k+2];
			

			L3[1][2]=pp1[1][k];
			L3[1][3]=pp1[1][k+1];
			L3[2][4]=pp1[1][k];
			L3[2][5]=pp1[1][k+2];	
			L3[3][6]=pp1[1][k];
			L3[3][7]=pp1[1][k+3];

			L2[2][4]=pp1[1][k+1];
			L2[2][5]=pp1[1][k+2];
			L2[3][6]=pp1[1][k+1];
			L2[3][7]=pp1[1][k+3];

			L1[3][6]=pp1[1][k+2];
			L1[3][7]=pp1[1][k+3];

			

printf("\nLU--1-----------------------------------------\n");

	
char **x1;
x1 = (char **)malloc(sizeof(char*)*M);
for(i=0;i<M;i++){
x1[i]=(char*)malloc(sizeof(char)*blocksize);}
for(i=0;i<M;i++){
x1[i]=(char*)malloc(sizeof(char)*blocksize);}
char **x2;
x2 = (char **)malloc(sizeof(char*)*M);
for(i=0;i<M;i++){
x2[i]=(char*)malloc(sizeof(char)*blocksize);}
char **x3;
x3 = (char **)malloc(sizeof(char*)*M);
for(i=0;i<M;i++){
x3[i]=(char*)malloc(sizeof(char)*blocksize);}
char **x4;
x4 = (char **)malloc(sizeof(char*)*M);
for(i=0;i<M;i++){
x4[i]=(char*)malloc(sizeof(char)*blocksize);}
	
			
printf("\nLU--1-1----------\n");
				for(i=0;i<M;i++){
				x1[i]=coding2[i];}

printf("\nLU--1-2-----------\n");
				for(i=0;i<M;i++){
				x2[i]=coding2[i]+blocksize;}
printf("\nLU--1-3-----------\n");
				for(i=0;i<M;i++){
				x3[i]=coding2[i]+2*blocksize;}
			
printf("\nLU--1-4-----------\n");		
				for(i=0;i<M;i++){
				shift1[i]=finite_mod((i-U1[2][3]), M);}
printf(" shift1: \n ");
for(j1=0;j1<M;j1++){
printf(" %d ",shift1[j1]);}  
			
			    	for(i=0;i<M;i++){
			    	galois_region_xor1(x3[shift1[i]],(coding2[i]+3*blocksize),x4[i],blocksize);}

printf("\noriginal \n");	
for(j1=0;j1<M;j1++){
printf(" %d ",x3[j1][0]);} 
printf("\nshift \n");
for(j1=0;j1<M;j1++){
printf(" %d ",x3[shift1[j1]][0]);} 
printf("\nv3 \n");
for(j1=0;j1<M;j1++){
printf(" %d ",coding2[j1][3*blocksize]);} 
printf("\nXOR-x4 \n");
for(j1=0;j1<M;j1++){
printf(" %d ",x4[j1][0]);} 
printf("-------\n");

printf("\nx1=========================== \n");	
for(j1=0;j1<M;j1++){
printf(" %d ",x1[j1][0]);} 
printf("\nx2================================ \n");	
for(j1=0;j1<M;j1++){
printf(" %d ",x2[j1][0]);} 
printf("\nx3========================== \n");	
for(j1=0;j1<M;j1++){
printf(" %d ",x3[j1][0]);}
printf("\nx4========================== \n");	
for(j1=0;j1<M;j1++){
printf(" %d ",x4[j1][0]);}
printf("\nLU--2---------------------------------------\n");				
char **y1;
y1 = (char **)malloc(sizeof(char*)*M);
for(i=0;i<M;i++){
y1[i]=(char*)malloc(sizeof(char)*blocksize);}
char **y2;
y2 = (char **)malloc(sizeof(char*)*M);
for(i=0;i<M;i++){
y2[i]=(char*)malloc(sizeof(char)*blocksize);}
char **y3;
y3 = (char **)malloc(sizeof(char*)*M);
for(i=0;i<M;i++){
y3[i]=(char*)malloc(sizeof(char)*blocksize);}
char **y4;
y4 = (char **)malloc(sizeof(char*)*M);
for(i=0;i<M;i++){
y4[i]=(char*)malloc(sizeof(char)*blocksize);}
printf("\nLU--2-1--------------\n");
			    	for(i=0;i<M;i++){
			    	y1[i]=x1[i];}
printf("\nLU--2-2--------------\n");
			    	for(i=0;i<M;i++){
			    	y2[i]=x2[i];}
printf("\nLU--2-3---------------\n");

				for(i=0;i<M;i++){
				shift1[i]=finite_mod((i-U2[1][2]), M);}
printf(" shift1: \n ");
for(j1=0;j1<M;j1++){
printf(" %d ",shift1[j1]);}


			    	for(i=0;i<M;i++){
			    	galois_region_xor1(y2[shift1[i]],x3[i],y3[i],blocksize);}
 			 
printf("\noriginal-y2 \n");	
for(j1=0;j1<M;j1++){
printf(" %d ",y2[j1][0]);} 
printf("\nshift \n");
for(j1=0;j1<M;j1++){
printf(" %d ",y2[shift1[j1]][0]);} 
printf("\nx3 \n");
for(j1=0;j1<M;j1++){
printf(" %d ",x3[j1][0]);} 
printf("\nXOR-y3 \n");
for(j1=0;j1<M;j1++){
printf(" %d ",y3[j1][0]);}			    
printf("\nLU--2-4---------------\n");		


				for(i=0;i<M;i++){
				shift1[i]=finite_mod((i-U2[2][3]), M);}	
printf(" shift1: \n ");
for(j1=0;j1<M;j1++){
printf(" %d ",shift1[j1]);}


     
			    	for(i=0;i<M;i++){
			   	galois_region_xor1(y3[shift1[i]],x4[i],y4[i],blocksize);}
 
printf("\noriginal-y3 \n");	
for(j1=0;j1<M;j1++){
printf(" %d ",y3[j1][0]);} 
printf("\nshift \n");
for(j1=0;j1<M;j1++){
printf(" %d ",y3[shift1[j1]][0]);} 
printf("\nx4 \n");
for(j1=0;j1<M;j1++){
printf(" %d ",x4[j1][0]);} 
printf("\nXOR-y4 \n");
for(j1=0;j1<M;j1++){
printf(" %d ",y4[j1][0]);}

printf("\ny1======================================== \n");	
for(j1=0;j1<M;j1++){
printf(" %d ",y1[j1][0]);} 
printf("\ny2======================================== \n");
for(j1=0;j1<M;j1++){
printf(" %d ",y2[j1][0]);}
printf("\ny3======================================== \n");
for(j1=0;j1<M;j1++){
printf(" %d ",y3[j1][0]);}
printf("\ny4======================================== \n");
for(j1=0;j1<M;j1++){
printf(" %d ",y4[j1][0]);}		

printf("\nLU--2 after---------------------------------------\n");				
char **yy1;
yy1 = (char **)malloc(sizeof(char*)*M);
for(i=0;i<M;i++){
yy1[i]=(char*)malloc(sizeof(char)*blocksize);}
char **yy2;
yy2 = (char **)malloc(sizeof(char*)*M);
for(i=0;i<M;i++){
yy2[i]=(char*)malloc(sizeof(char)*blocksize);}
char **yy3;
yy3 = (char **)malloc(sizeof(char*)*M);
for(i=0;i<M;i++){
yy3[i]=(char*)malloc(sizeof(char)*blocksize);}
char **yy4;
yy4 = (char **)malloc(sizeof(char*)*M);
for(i=0;i<M;i++){
yy4[i]=(char*)malloc(sizeof(char)*blocksize);}
printf("\nLU--2-1- after-------------\n");
			    	for(i=0;i<M;i++){
			    	yy1[i]=y1[i];}
printf("\nLU--2-2-- after------------\n");
			    	for(i=0;i<M;i++){
				shift1[i]=finite_mod((i-U3[0][1]), M);}
printf(" shift1: \n ");
for(j1=0;j1<M;j1++){
printf(" %d ",shift1[j1]);}


			    	for(i=0;i<M;i++){
			    	galois_region_xor1(yy1[shift1[i]],y2[i],yy2[i],blocksize);}
printf("\noriginal-yy1 \n");	
for(j1=0;j1<M;j1++){
printf(" %d ",yy1[j1][0]);} 
printf("\nshift \n");
for(j1=0;j1<M;j1++){
printf(" %d ",yy1[shift1[j1]][0]);} 
printf("\ny2 \n");
for(j1=0;j1<M;j1++){
printf(" %d ",y2[j1][0]);} 
printf("\nXOR-yy2 \n");
for(j1=0;j1<M;j1++){
printf(" %d ",yy2[j1][0]);}
 			 
printf("\nLU--2-3-- after-------------\n");

				for(i=0;i<M;i++){
				shift1[i]=finite_mod((i-U3[1][2]), M);}
printf(" shift1: \n ");
for(j1=0;j1<M;j1++){
printf(" %d ",shift1[j1]);}


			    	for(i=0;i<M;i++){
			    	galois_region_xor1(yy2[shift1[i]],y3[i],yy3[i],blocksize);}
printf("\noriginal-yy2 \n");	
for(j1=0;j1<M;j1++){
printf(" %d ",yy2[j1][0]);} 
printf("\nshift \n");
for(j1=0;j1<M;j1++){
printf(" %d ",yy2[shift1[j1]][0]);} 
printf("\ny3 \n");
for(j1=0;j1<M;j1++){
printf(" %d ",y3[j1][0]);} 
printf("\nXOR-yy3 \n");
for(j1=0;j1<M;j1++){
printf(" %d ",yy3[j1][0]);} 			 
			    
printf("\nLU--2-4-- after-------------\n");		


 			        for(i=0;i<M;i++){
				shift1[i]=finite_mod((i-U3[2][3]), M);}	
printf(" shift1: \n ");
for(j1=0;j1<M;j1++){
printf(" %d ",shift1[j1]);}


     
			    	for(i=0;i<M;i++){
			   	galois_region_xor1(yy3[shift1[i]],y4[i],yy4[i],blocksize);}
 
printf("\noriginal-yy3 \n");	
for(j1=0;j1<M;j1++){
printf(" %d ",yy3[j1][0]);} 
printf("\nshift \n");
for(j1=0;j1<M;j1++){
printf(" %d ",yy3[shift1[j1]][0]);} 
printf("\ny4 \n");
for(j1=0;j1<M;j1++){
printf(" %d ",y4[j1][0]);} 
printf("\nXOR-yy4 \n");
for(j1=0;j1<M;j1++){
printf(" %d ",yy4[j1][0]);}

printf("\nyy1======================================== \n");	
for(j1=0;j1<M;j1++){
printf(" %d ",yy1[j1][0]);} 
printf("\nyy2======================================== \n");
for(j1=0;j1<M;j1++){
printf(" %d ",yy2[j1][0]);}
printf("\nyy3======================================== \n");
for(j1=0;j1<M;j1++){
printf(" %d ",yy3[j1][0]);}
printf("\nyy4======================================== \n");
for(j1=0;j1<M;j1++){
printf(" %d ",yy4[j1][0]);}	



printf("\nLU--3-----------------------------------------------------------------------------------------------------------\n");			
char **z1;
z1 = (char **)malloc(sizeof(char*)*M);
for(i=0;i<M;i++){
z1[i]=(char*)malloc(sizeof(char)*blocksize);}

char **z2_1;
z2_1 = (char **)malloc(sizeof(char*)*M);
for(i=0;i<M;i++){
z2_1[i]=(char*)malloc(sizeof(char)*blocksize);}
char **z2_2;
z2_2 = (char **)malloc(sizeof(char*)*M);
for(i=0;i<M;i++){
z2_2[i]=(char*)malloc(sizeof(char)*blocksize);}

char **z3_1;
z3_1 = (char **)malloc(sizeof(char*)*M);
for(i=0;i<M;i++){
z3_1[i]=(char*)malloc(sizeof(char)*blocksize);}
char **z3_2;
z3_2 = (char **)malloc(sizeof(char*)*M);
for(i=0;i<M;i++){
z3_2[i]=(char*)malloc(sizeof(char)*blocksize);}
		
char **z4_1;
z4_1 = (char **)malloc(sizeof(char*)*M);
for(i=0;i<M;i++){
z4_1[i]=(char*)malloc(sizeof(char)*blocksize);}


int b1;
char **shift;
shift = (char **)malloc(sizeof(char*)*((p-1)/2));
for(i=0;i<((p-1)/2);i++){
shift[i] = (char *)malloc(sizeof(char)*M);}

char **zz4;
zz4 = (char **)malloc(sizeof(char*)*((p-1)/2));
for(i=0;i<((p-1)/2);i++){
zz4[i]=(char*)malloc(sizeof(char)*M*blocksize);}
char **zz3;
zz3 = (char **)malloc(sizeof(char*)*((p-1)/2));
for(i=0;i<((p-1)/2);i++){
zz3[i]=(char*)malloc(sizeof(char)*M*blocksize);}////
char **zz2;
zz2 = (char **)malloc(sizeof(char*)*((p-1)/2));
for(i=0;i<((p-1)/2);i++){
zz2[i]=(char*)malloc(sizeof(char)*M*blocksize);}////
printf("\nLU--3-1---------------\n");			
				for(i=0;i<M;i++){
				shift1[i]=finite_mod((i-(M-L3[3][6])),M);}
printf(" \nL3[3][6] \n ");
printf(" %d ",L3[3][6]);
printf(" \nshift1: \n ");
for(j1=0;j1<M;j1++){
printf(" %d ",shift1[j1]);}
printf(" \n ");

 				for(i=0;i<M;i++){
			        z4_1[i]=yy4[shift1[i]];}
printf("\nz4_1 \n");
for(j1=0;j1<M;j1++){
printf(" %d ",z4_1[j1][0]);}
				b1=L3[3][7]-L3[3][6];// b=2
			        printf(" \nb1:\n ");
				printf(" %d ",b1);
				
			
			        shift=shift_value(b1,tau,p,M); 
printf("\nshift \n");				
for(i=0;i<((p-1)/2);i++){
for(j1=0;j1<M;j1++){
printf(" %d ",shift[i][j1]);}
printf("\n");}
				
				for(i=0;i<((p-1)/2);i++){
				for(j=0;j<M;j++){
				for(i1=0;i1<blocksize;i1++){
				zz4[i][j*blocksize+i1]=*(z4_1[shift[i][j]]+i1);}}}

printf("\nzz4 \n");
for(i=0;i<((p-1)/2);i++){
for(j1=0;j1<M;j1++){
printf(" %d ",zz4[i][j1*blocksize]);}
printf("\n");}



				
				//!!!!!!!!!!!!!!galois_region_xor1 li zhiyunxu you yige bianliang 
				for(i=0;i<((p-1)/2-1);i++){
				//for(j=0;j<M;j++){			
		                galois_region_xor1((zz4[i]),(zz4[i+1]),(zz4[i+1]),M*blocksize);}//}
				
printf("\nzz4-XOR \n");	
for(i=0;i<((p-1)/2);i++){			
for(j1=0;j1<M;j1++){
printf(" %d ",zz4[i][j1*blocksize]);}
printf("\n");}
				
				

printf("\nLU--3-2-------------\n");
				
				

				
				for(i=0;i<M;i++){
			        galois_region_xor1(yy3[i],(zz4[((p-1)/2)-1]+i*blocksize),z3_1[i],blocksize);}
printf("\nyy3 \n");
for(j1=0;j1<M;j1++){
printf(" %d ",yy3[j1][0]);}

printf("\nXOR-z3_1 \n");
for(j1=0;j1<M;j1++){
printf(" %d ",z3_1[j1][0]);}	
				for(i=0;i<M;i++){
				shift1[i]=finite_mod((i-(M-L3[2][4])),M);}
printf(" \nshift1: \n ");
for(j1=0;j1<M;j1++){
printf(" %d ",shift1[j1]);}				

				for(i=0;i<M;i++){
			        z3_2[i]=z3_1[shift1[i]];}
				
printf("\nz3_2 \n");
for(j1=0;j1<M;j1++){
printf(" %d ",z3_2[j1][0]);}

			        b1=L3[2][5]-L3[2][4]; //b=1
				printf(" \nb1:\n ");
				printf(" %d ",b1);

	
				shift=shift_value(b1,tau,p,M);
printf("\nshift \n");				
for(i=0;i<((p-1)/2);i++){
for(j1=0;j1<M;j1++){
printf(" %d ",shift[i][j1]);}
printf("\n");}
				for(i=0;i<((p-1)/2);i++){
				for(j=0;j<M;j++){
				for(i1=0;i1<blocksize;i1++){
				zz3[i][j*blocksize+i1]=*(z3_2[shift[i][j]]+i1);}}}
printf("\nzz3 \n");
for(i=0;i<((p-1)/2);i++){
for(j1=0;j1<M;j1++){
printf(" %d ",zz3[i][j1*blocksize]);}
printf("\n");}				

				for(i=0;i<((p-1)/2-1);i++){			
		                galois_region_xor1((zz3[i]),(zz3[i+1]),(zz3[i+1]),M*blocksize);}

printf("\nzz3-XOR \n");	
for(i=0;i<((p-1)/2);i++){			
for(j1=0;j1<M;j1++){
printf(" %d ",zz3[i][j1*blocksize]);}
printf("\n");}
printf("\nLU--3-3-------------\n");
				
				

				
				for(i=0;i<M;i++){
			        galois_region_xor1(yy2[i],(zz3[((p-1)/2)-1]+i*blocksize),z2_1[i],blocksize);}
printf("\nyy2 \n");
for(j1=0;j1<M;j1++){
printf(" %d ",yy2[j1][0]);}

printf("\nXOR-z2_1 \n");
for(j1=0;j1<M;j1++){
printf(" %d ",z2_1[j1][0]);}	
				for(i=0;i<M;i++){
				shift1[i]=finite_mod((i-(M-L3[1][2])),M);}
printf(" \nshift1: \n ");
for(j1=0;j1<M;j1++){
printf(" %d ",shift1[j1]);}				

				for(i=0;i<M;i++){
			        z2_2[i]=z2_1[shift1[i]];}
printf("\nz2_2 \n");
for(j1=0;j1<M;j1++){
printf(" %d ",z2_2[j1][0]);}				
 

			        b1=L3[1][3]-L3[1][2]; //b=1
				printf(" \nb1:\n ");
				printf(" %d ",b1);

	
				shift=shift_value(b1,tau,p,M);
printf("\nshift \n");				
for(i=0;i<((p-1)/2);i++){
for(j1=0;j1<M;j1++){
printf(" %d ",shift[i][j1]);}
printf("\n");}
				for(i=0;i<((p-1)/2);i++){
				for(j=0;j<M;j++){
				for(i1=0;i1<blocksize;i1++){
				zz2[i][j*blocksize+i1]=*(z2_2[shift[i][j]]+i1);}}}
printf("\nzz2 \n");	
for(i=0;i<((p-1)/2);i++){			
for(j1=0;j1<M;j1++){
printf(" %d ",zz2[i][j1*blocksize]);}
printf("\n");}				

				for(i=0;i<((p-1)/2-1);i++){			
		                galois_region_xor1((zz2[i]),(zz2[i+1]),(zz2[i+1]),M*blocksize);}

printf("\nzz2-XOR \n");	
for(i=0;i<((p-1)/2);i++){			
for(j1=0;j1<M;j1++){
printf(" %d ",zz2[i][j1*blocksize]);}
printf("\n");}				





printf("\nLU--3-4---------------\n");	
				

			      for(i=0;i<M;i++){
			      galois_region_xor1(yy1[i],(zz2[((p-1)/2)-1]+i*blocksize),z1[i],blocksize); }
printf("\nyy1 \n");
for(j1=0;j1<M;j1++){
printf(" %d ",yy1[j1][0]);}
printf("\nXOR- z1 \n");
for(j1=0;j1<M;j1++){
printf(" %d ",z1[j1][0]);}

printf("\nz1======================================== \n");
for(j1=0;j1<M;j1++){
printf(" %d ",z1[j1][0]);}
printf("\nzz2======================================== \n");
for(j1=0;j1<M;j1++){
printf(" %d ",zz2[((p-1)/2)-1][j1*blocksize]);}
printf("\nzz3======================================== \n");
for(j1=0;j1<M;j1++){
printf(" %d ",zz3[((p-1)/2)-1][j1*blocksize]);}
printf("\nzz4======================================== \n");
for(j1=0;j1<M;j1++){
printf(" %d ",zz4[((p-1)/2)-1][j1*blocksize]);}
printf("\nLU--3---after------------------------------------------------------------------------------------------------------------------------------\n");
char **t1;
t1 = (char **)malloc(sizeof(char*)*M);
for(i=0;i<M;i++){
t1[i]=(char*)malloc(sizeof(char)*blocksize);}

char **t2;
t2 = (char **)malloc(sizeof(char*)*M);
for(i=0;i<M;i++){
t2[i]=(char*)malloc(sizeof(char)*blocksize);}


char **t3_1;
t3_1 = (char **)malloc(sizeof(char*)*M);
for(i=0;i<M;i++){
t3_1[i]=(char*)malloc(sizeof(char)*blocksize);}
char **t3_2;
t3_2 = (char **)malloc(sizeof(char*)*M);
for(i=0;i<M;i++){
t3_2[i]=(char*)malloc(sizeof(char)*blocksize);}
		
char **t4_1;
t4_1 = (char **)malloc(sizeof(char*)*M);
for(i=0;i<M;i++){
t4_1[i]=(char*)malloc(sizeof(char)*blocksize);}



char **tt4;
tt4 = (char **)malloc(sizeof(char*)*((p-1)/2));
for(i=0;i<((p-1)/2);i++){
tt4[i]=(char*)malloc(sizeof(char)*M*blocksize);}
char **tt3;
tt3 = (char **)malloc(sizeof(char*)*((p-1)/2));
for(i=0;i<((p-1)/2);i++){
tt3[i]=(char*)malloc(sizeof(char)*M*blocksize);}
printf("\nLU--3-1---after-------------\n");	
				for(i=0;i<M;i++){
				shift1[i]=finite_mod((i-(M-L2[3][6])),M);}
printf(" \nshift1: \n ");
for(j1=0;j1<M;j1++){
printf(" %d ",shift1[j1]);}
 				for(i=0;i<M;i++){
				t4_1[i]=zz4[((p-1)/2)-1]+shift1[i]*blocksize;}
			        
printf("\nt4_1 \n");
for(j1=0;j1<M;j1++){
printf(" %d ",t4_1[j1][0]);}
				b1=L2[3][7]-L2[3][6];// b=2
			        printf(" \nb1:\n ");
				printf(" %d ",b1);
				
			
			        shift=shift_value(b1,tau,p,M); 

printf("\nshift \n");				
for(i=0;i<((p-1)/2);i++){
for(j1=0;j1<M;j1++){
printf(" %d ",shift[i][j1]);}
printf("\n");}				
				for(i=0;i<((p-1)/2);i++){
				for(j=0;j<M;j++){
				for(i1=0;i1<blocksize;i1++){
				tt4[i][j*blocksize+i1]=*(t4_1[shift[i][j]]+i1);}}}


printf("\ntt4-XOR \n");	
for(i=0;i<((p-1)/2);i++){			
for(j1=0;j1<M;j1++){
printf(" %d ",tt4[i][j1*blocksize]);}
printf("\n");}


				
				//!!!!!!!!!!!!!!galois_region_xor1 li zhiyunxu you yige bianliang 
				for(i=0;i<((p-1)/2-1);i++){
							
		                galois_region_xor1((tt4[i]),(tt4[i+1]),(tt4[i+1]),M*blocksize);}//}
				
printf("\ntt4-XOR \n");	
for(i=0;i<((p-1)/2);i++){			
for(j1=0;j1<M;j1++){
printf(" %d ",tt4[i][j1*blocksize]);}
printf("\n");}
 
printf("\n");
printf("\nLU--3-2--after----------------\n");
				
				

				
				for(i=0;i<M;i++){
			        galois_region_xor1(zz3[((p-1)/2)-1]+i*blocksize,(tt4[((p-1)/2)-1]+i*blocksize),t3_1[i],blocksize);}
printf("\nzz3 \n");
for(j1=0;j1<M;j1++){
printf(" %d ",zz3[((p-1)/2)-1][j1*blocksize]);}
printf("\ntt4 \n");
for(j1=0;j1<M;j1++){
printf(" %d ",tt4[((p-1)/2)-1][j1*blocksize]);}	
printf("\nXOR t3_1 \n");
for(j1=0;j1<M;j1++){
printf(" %d ",t3_1[j1][0]);}
				for(i=0;i<M;i++){
				shift1[i]=finite_mod((i-(M-L2[2][4])),M);}
printf(" \nshift1: \n ");
for(j1=0;j1<M;j1++){
printf(" %d ",shift1[j1]);}				

				for(i=0;i<M;i++){
			        t3_2[i]=t3_1[shift1[i]];}
printf("\nt3_2 \n");
for(j1=0;j1<M;j1++){
printf(" %d ",t3_2[j1][0]);}				


			        b1=L2[2][5]-L2[2][4]; //b=1
				printf(" \nb1:\n ");
				printf(" %d ",b1);

	
				shift=shift_value(b1,tau,p,M);
printf("\nshift \n");				
for(i=0;i<((p-1)/2);i++){
for(j1=0;j1<M;j1++){
printf(" %d ",shift[i][j1]);}
printf("\n");}
				for(i=0;i<((p-1)/2);i++){
				for(j=0;j<M;j++){
				for(i1=0;i1<blocksize;i1++){
				tt3[i][j*blocksize+i1]=*(t3_2[shift[i][j]]+i1);}}}
printf("\ntt3 \n");	
for(i=0;i<((p-1)/2);i++){			
for(j1=0;j1<M;j1++){
printf(" %d ",tt3[i][j1*blocksize]);}
printf("\n");}				

				for(i=0;i<((p-1)/2-1);i++){			
		                galois_region_xor1((tt3[i]),(tt3[i+1]),(tt3[i+1]),M*blocksize);}

printf("\ntt3-XOR \n");	
for(i=0;i<((p-1)/2);i++){			
for(j1=0;j1<M;j1++){
printf(" %d ",tt3[i][j1*blocksize]);}
printf("\n");}
printf("\nLU--3-3---after----------\n");
				
				

				
				for(i=0;i<M;i++){
			        galois_region_xor1((zz2[((p-1)/2)-1]+i*blocksize),(tt3[((p-1)/2)-1]+i*blocksize),t2[i],blocksize);}

printf("\nzz2 \n");
for(j1=0;j1<M;j1++){
printf(" %d ",zz2[((p-1)/2)-1][j1*blocksize]);}
printf("\ntt3 \n");
for(j1=0;j1<M;j1++){
printf(" %d ",tt3[((p-1)/2)-1][j1*blocksize]);}	
printf("\nXOR t2 \n");
for(j1=0;j1<M;j1++){
printf(" %d ",t2[j1][0]);}

printf("\nLU--3-4--after-------------\n");	
				

			      for(i=0;i<M;i++){
			      t1[i]=z1[i]; }

printf("\nz1 \n");
for(j1=0;j1<M;j1++){
printf(" %d ",z1[j1][0]);}
printf("\nt1======================================== \n");
for(j1=0;j1<M;j1++){
printf(" %d ",t1[j1][0]);}
printf("\nt2======================================== \n");
for(j1=0;j1<M;j1++){
printf(" %d ",t2[j1][0]);}
printf("\ntt3======================================== \n");
for(j1=0;j1<M;j1++){
printf(" %d ",tt3[((p-1)/2)-1][j1*blocksize]);}
printf("\ntt4======================================== \n");
for(j1=0;j1<M;j1++){
printf(" %d ",tt4[((p-1)/2)-1][j1*blocksize]);}
printf("\nLU--4---------------------------------------------------------------------------------------------------------------------------------------\n");		

char **s4_1;
s4_1 = (char **)malloc(sizeof(char*)*M);
for(i=0;i<M;i++){
s4_1[i]=(char*)malloc(sizeof(char)*blocksize);}

char **s3;
s3 = (char **)malloc(sizeof(char*)*M);
for(i=0;i<M;i++){
s3[i]=(char*)malloc(sizeof(char)*blocksize);}
char **s2;
s2 = (char **)malloc(sizeof(char*)*M);
for(i=0;i<M;i++){
s2[i]=(char*)malloc(sizeof(char)*blocksize);}
char **s1;
s1 = (char **)malloc(sizeof(char*)*M);
for(i=0;i<M;i++){
s1[i]=(char*)malloc(sizeof(char)*blocksize);}

char **ss4;
ss4 = (char **)malloc(sizeof(char*)*((p-1)/2));
for(i=0;i<((p-1)/2);i++){
ss4[i]=(char*)malloc(sizeof(char)*M*blocksize);}
printf("\nLU--4-1---------------\n");
			



			for(i=0;i<M;i++){
			shift1[i]=finite_mod((i-(M-L1[3][6])),M);}
printf(" \nshift1: \n ");
for(j1=0;j1<M;j1++){
printf(" %d ",shift1[j1]);}
			for(i=0;i<M;i++){
			s4_1[i]=tt4[((p-1)/2)-1]+shift1[i]*blocksize;}

printf("\ns4_1 \n");
for(j1=0;j1<M;j1++){
printf(" %d ",s4_1[j1][0]);}




			b1=L1[3][7]-L1[3][6];
			printf(" \nb1:\n ");
			printf(" %d ",b1);

			shift=shift_value(b1,tau,p,M);
printf("\nshift \n");				
for(i=0;i<((p-1)/2);i++){
for(j1=0;j1<M;j1++){
printf(" %d ",shift[i][j1]);}
printf("\n");}
				for(i=0;i<((p-1)/2);i++){
				for(j=0;j<M;j++){
				for(i1=0;i1<blocksize;i1++){
				ss4[i][j*blocksize+i1]=*(s4_1[shift[i][j]]+i1);}}}
printf("\nss4-XOR \n");	
for(i=0;i<((p-1)/2);i++){			
for(j1=0;j1<M;j1++){
printf(" %d ",ss4[i][j1*blocksize]);}
printf("\n");}			

				for(i=0;i<((p-1)/2-1);i++){			
		                galois_region_xor1((ss4[i]),(ss4[i+1]),(ss4[i+1]),M*blocksize);}

printf("\nss4-XOR \n");	
for(i=0;i<((p-1)/2);i++){			
for(j1=0;j1<M;j1++){
printf(" %d ",ss4[i][j1*blocksize]);}
printf("\n");}


printf("LU--4-2--------------\n");

			
			for(i=0;i<M;i++){
			galois_region_xor1((tt3[((p-1)/2)-1]+i*blocksize),(ss4[((p-1)/2)-1]+i*blocksize),(s3[i]),blocksize);}

printf("\ntt3 \n");
for(j1=0;j1<M;j1++){
printf(" %d ",tt3[((p-1)/2)-1][j1*blocksize]);}
printf("\nss4 \n");
for(j1=0;j1<M;j1++){
printf(" %d ",ss4[((p-1)/2)-1][j1*blocksize]);}	
printf("\nXOR s3 \n");
for(j1=0;j1<M;j1++){
printf(" %d ",s3[j1][0]);}


printf("LU--4-3--------------\n");		
			
			for(i=0;i<M;i++){
			s2[i]=t2[i];}
			
printf("\nt2 \n");
for(j1=0;j1<M;j1++){
printf(" %d ",t2[j1][0]);}
printf("LU--4-4--------------\n");		
			
			for(i=0;i<M;i++){
			s1[i]=t1[i];}
			
printf("\nt1 \n");
for(j1=0;j1<M;j1++){
printf(" %d ",t1[j1][0]);}
 
printf("\ns1======================================== \n");
for(j1=0;j1<M;j1++){
printf(" %d ",s1[j1][0]);}
printf("\ns2======================================== \n");
for(j1=0;j1<M;j1++){
printf(" %d ",s2[j1][0]);}
printf("\ns3======================================== \n");
for(j1=0;j1<M;j1++){
printf(" %d ",s3[j1][0]);}
printf("\nss4======================================== \n");
for(j1=0;j1<M;j1++){
printf(" %d ",ss4[((p-1)/2)-1][j1*blocksize]);}


char **fdata;
fdata=(char **)malloc(sizeof(char*)*M);
for(i=0;i<M;i++){
fdata[i]=(char *)malloc(sizeof(char)*r*blocksize);}

for(i=0;i<M;i++){ 

memcpy(fdata[i],s1[i],blocksize);
memcpy((fdata[i]+blocksize),s2[i],blocksize);
memcpy((fdata[i]+2*blocksize),s3[i],blocksize);
memcpy((fdata[i]+3*blocksize),(ss4[((p-1)/2)-1]+i*blocksize),blocksize);}

return fdata;

}//hanshu

