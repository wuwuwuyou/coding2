

//#include "fun.h"
#include <stdio.h>
#include <stdlib.h>
char** LU_5(int **pp1,char **coding2,int k,int r,int p,int tau,int M,int blocksize){
extern void galois_region_xor1(   char *r1,         /* Region 1 */
                                  char *r2,         /* Region 2 */
                                  char *r3,         /* Sum region (r3 = r1 ^ r2) -- can be r1 or r2 */
                                  int nbytes);
extern char** shift_value(int b1, int tau,int p,int M);
extern int finite_mod(int i,int M);
printf("\nLU---r=5-------------------------------\n");
if(r!=5){fprintf(stderr,  "r shoule be equal to 5 \n");
			exit(0);}
int i,j,i1,j1;
char **U1;
char **U2;
char **U3;
char **U4;
char **L1;
char **L2;
char **L3;
char **L4;
U1 = (char **)malloc(sizeof(char*)*r);
for (i = 0; i <r ; i++) {
U1[i] = (char *)malloc(sizeof(char)*r);}
U2 = (char **)malloc(sizeof(char*)*r);
for (i = 0; i <r ; i++) {
U2[i] = (char *)malloc(sizeof(char)*r);}
U3 = (char **)malloc(sizeof(char*)*r);
for (i = 0; i <r ; i++) {
U3[i] = (char *)malloc(sizeof(char)*r);}
U4 = (char **)malloc(sizeof(char*)*r);
for (i = 0; i <r ; i++) {
U4[i] = (char *)malloc(sizeof(char)*r);}
L1 = (char **)malloc(sizeof(char*)*r);
for (i = 0; i <r ; i++) {
L1[i] = (char *)malloc(sizeof(char)*2*r);}			
L2 = (char **)malloc(sizeof(char*)*r);
for (i = 0; i <r ; i++) {
L2[i] = (char *)malloc(sizeof(char)*2*r);}	
L3 = (char **)malloc(sizeof(char*)*r);
for (i = 0; i <r ; i++) {
L3[i] = (char *)malloc(sizeof(char)*2*r);}
L4 = (char **)malloc(sizeof(char*)*r);
for (i = 0; i <r ; i++) {
L4[i] = (char *)malloc(sizeof(char)*2*r);}

char *shift1;
shift1 = (char *)malloc(sizeof(char)*M);

printf("LU--begin---\n");	
			


			U1[3][4]=pp1[1][k];
			U2[2][3]=pp1[1][k];
			U2[3][4]=pp1[1][k+1];
			U3[1][2]=pp1[1][k];
			U3[2][3]=pp1[1][k+1];
			U3[3][4]=pp1[1][k+2];
			U4[0][1]=pp1[1][k];
			U4[1][2]=pp1[1][k+1];
			U4[2][3]=pp1[1][k+2];
			U4[3][4]=pp1[1][k+3];
			
			
			L4[1][2]=pp1[1][k];
			L4[1][3]=pp1[1][k+1];
			L4[2][4]=pp1[1][k];
			L4[2][5]=pp1[1][k+2];	
			L4[3][6]=pp1[1][k];
			L4[3][7]=pp1[1][k+3];
			L4[4][8]=pp1[1][k];
			L4[4][9]=pp1[1][k+4];

			L3[2][4]=pp1[1][k+1];
			L3[2][5]=pp1[1][k+2];	
			L3[3][6]=pp1[1][k+1];
			L3[3][7]=pp1[1][k+3];
			L3[4][8]=pp1[1][k+1];
			L3[4][9]=pp1[1][k+4];

			L2[3][6]=pp1[1][k+2];
			L2[3][7]=pp1[1][k+3];
			L2[4][8]=pp1[1][k+2];
			L2[4][9]=pp1[1][k+4];

			L1[4][8]=pp1[1][k+3];
			L1[4][9]=pp1[1][k+4];

			
printf("\nparametre:\n");
printf(" %d ",pp1[1][k]);
printf(" %d ",pp1[1][k+1]);
printf(" %d ",pp1[1][k+2]);
printf(" %d ",pp1[1][k+3]);
printf(" %d ",pp1[1][k+4]);
printf("\nU--1-----------------------------------------\n");

	
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
char **x5;
x5 = (char **)malloc(sizeof(char*)*M);
for(i=0;i<M;i++){
x5[i]=(char*)malloc(sizeof(char)*blocksize);}	
			
printf("\nU--1-1----------\n");
				for(i=0;i<M;i++){
				x1[i]=coding2[i];}

printf("\nU--1-2-----------\n");
				for(i=0;i<M;i++){
				x2[i]=coding2[i]+blocksize;}
printf("\nU--1-3-----------\n");
				for(i=0;i<M;i++){
				x3[i]=coding2[i]+2*blocksize;}
printf("\nU--1-4-----------\n");
				for(i=0;i<M;i++){
				x4[i]=coding2[i]+3*blocksize;}			
printf("\nU--1-5-----------\n");		
				for(i=0;i<M;i++){
				shift1[i]=finite_mod((i-U1[3][4]), M);}
printf(" shift1: \n ");
for(j1=0;j1<M;j1++){
printf(" %d ",shift1[j1]);}  
			
			    	for(i=0;i<M;i++){
			    	galois_region_xor1(x4[shift1[i]],(coding2[i]+4*blocksize),x5[i],blocksize);}



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
printf("\nx5========================== \n");	
for(j1=0;j1<M;j1++){
printf(" %d ",x5[j1][0]);}
printf("\nU--2---------------------------------------\n");				
char **xx1;
xx1 = (char **)malloc(sizeof(char*)*M);
for(i=0;i<M;i++){
xx1[i]=(char*)malloc(sizeof(char)*blocksize);}
char **xx2;
xx2 = (char **)malloc(sizeof(char*)*M);
for(i=0;i<M;i++){
xx2[i]=(char*)malloc(sizeof(char)*blocksize);}
char **xx3;
xx3 = (char **)malloc(sizeof(char*)*M);
for(i=0;i<M;i++){
xx3[i]=(char*)malloc(sizeof(char)*blocksize);}
char **xx4;
xx4 = (char **)malloc(sizeof(char*)*M);
for(i=0;i<M;i++){
xx4[i]=(char*)malloc(sizeof(char)*blocksize);}
char **xx5;
xx5 = (char **)malloc(sizeof(char*)*M);
for(i=0;i<M;i++){
xx5[i]=(char*)malloc(sizeof(char)*blocksize);}
printf("\nU--2-1--------------\n");
			    	for(i=0;i<M;i++){
			    	xx1[i]=x1[i];}
printf("\nU--2-2--------------\n");
			    	for(i=0;i<M;i++){
			    	xx2[i]=x2[i];}
printf("\nU--2-3--------------\n");
			    	for(i=0;i<M;i++){
			    	xx3[i]=x3[i];}
printf("\nU--2-4---------------\n");

				for(i=0;i<M;i++){
				shift1[i]=finite_mod((i-U2[2][3]), M);}



			    	for(i=0;i<M;i++){
			    	galois_region_xor1(xx3[shift1[i]],x4[i],xx4[i],blocksize);}
 			 
			    
printf("\nLU--2-5---------------\n");		


				for(i=0;i<M;i++){
				shift1[i]=finite_mod((i-U2[3][4]), M);}	



     
			    	for(i=0;i<M;i++){
			   	galois_region_xor1(xx4[shift1[i]],x5[i],xx5[i],blocksize);}
 


printf("\nxx1======================================== \n");	
for(j1=0;j1<M;j1++){
printf(" %d ",xx1[j1][0]);} 
printf("\nxx2======================================== \n");
for(j1=0;j1<M;j1++){
printf(" %d ",xx2[j1][0]);}
printf("\nxx3======================================== \n");
for(j1=0;j1<M;j1++){
printf(" %d ",xx3[j1][0]);}
printf("\nxx4======================================== \n");
for(j1=0;j1<M;j1++){
printf(" %d ",xx4[j1][0]);}
printf("\nxx5======================================== \n");
for(j1=0;j1<M;j1++){
printf(" %d ",xx5[j1][0]);}		
printf("\nU--3---------------------------------------\n");				
char **y1;
y1 = (char **)malloc(sizeof(char*)*M);
for(i=0;i<M;i++){
y1[i]=(char*)malloc(sizeof(char)*blocksize);}
char **y2;
char **y3;
y2 = (char **)malloc(sizeof(char*)*M);
for(i=0;i<M;i++){
y2[i]=(char*)malloc(sizeof(char)*blocksize);}

y3 = (char **)malloc(sizeof(char*)*M);
for(i=0;i<M;i++){
y3[i]=(char*)malloc(sizeof(char)*blocksize);}
char **y4;
y4 = (char **)malloc(sizeof(char*)*M);
for(i=0;i<M;i++){
y4[i]=(char*)malloc(sizeof(char)*blocksize);}
char **y5;
y5 = (char **)malloc(sizeof(char*)*M);
for(i=0;i<M;i++){
y5[i]=(char*)malloc(sizeof(char)*blocksize);}
printf("\nU--3-1--------------\n");
			    	for(i=0;i<M;i++){
			    	y1[i]=xx1[i];}
printf("\nU--3-2--------------\n");
			    	for(i=0;i<M;i++){
			    	y2[i]=xx2[i];}
printf("\nU--3-3---------------\n");

				for(i=0;i<M;i++){
				shift1[i]=finite_mod((i-U3[1][2]), M);}



			    	for(i=0;i<M;i++){
			    	galois_region_xor1(y2[shift1[i]],xx3[i],y3[i],blocksize);}
 			 
			    
printf("\nU--3-4---------------\n");		


				for(i=0;i<M;i++){
				shift1[i]=finite_mod((i-U3[2][3]), M);}	



     
			    	for(i=0;i<M;i++){
			   	galois_region_xor1(y3[shift1[i]],xx4[i],y4[i],blocksize);}
printf("\nU--3-5---------------\n");		


				for(i=0;i<M;i++){
				shift1[i]=finite_mod((i-U3[3][4]), M);}	



     
			    	for(i=0;i<M;i++){
			   	galois_region_xor1(y4[shift1[i]],xx5[i],y5[i],blocksize);}


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
printf("\ny5======================================== \n");
for(j1=0;j1<M;j1++){
printf(" %d ",y5[j1][0]);}
printf("\nU--4---------------------------------------\n");				
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
char **yy5;
yy5 = (char **)malloc(sizeof(char*)*M);
for(i=0;i<M;i++){
yy5[i]=(char*)malloc(sizeof(char)*blocksize);}
printf("\nU--4----1 -------------\n");
			    	for(i=0;i<M;i++){
			    	yy1[i]=y1[i];}
printf("\nU--4----2 ------------\n");
			    	for(i=0;i<M;i++){
				shift1[i]=finite_mod((i-U4[0][1]), M);}



			    	for(i=0;i<M;i++){
			    	galois_region_xor1(yy1[shift1[i]],y2[i],yy2[i],blocksize);}

 			 
printf("\nU--4----3-------------\n");

				for(i=0;i<M;i++){
				shift1[i]=finite_mod((i-U4[1][2]), M);}



			    	for(i=0;i<M;i++){
			    	galois_region_xor1(yy2[shift1[i]],y3[i],yy3[i],blocksize);}
 			 
			    
printf("\nU--4----4------------\n");		


 			        for(i=0;i<M;i++){
				shift1[i]=finite_mod((i-U4[2][3]), M);}	



     
			    	for(i=0;i<M;i++){
			   	galois_region_xor1(yy3[shift1[i]],y4[i],yy4[i],blocksize);}
printf("\nU--4----5------------\n");		


 			        for(i=0;i<M;i++){
				shift1[i]=finite_mod((i-U4[3][4]), M);}	



     
			    	for(i=0;i<M;i++){
			   	galois_region_xor1(yy4[shift1[i]],y5[i],yy5[i],blocksize);}


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
printf("\nyy5======================================== \n");
for(j1=0;j1<M;j1++){
printf(" %d ",yy5[j1][0]);}


printf("\nL----4-----------------------------------------------------------------------------------------------------------\n");			
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
char **z4_2;
z4_2 = (char **)malloc(sizeof(char*)*M);
for(i=0;i<M;i++){
z4_2[i]=(char*)malloc(sizeof(char)*blocksize);}
		
char **z5_1;
z5_1 = (char **)malloc(sizeof(char*)*M);
for(i=0;i<M;i++){
z5_1[i]=(char*)malloc(sizeof(char)*blocksize);}


int b1;
char **shift;
shift = (char **)malloc(sizeof(char*)*((p-1)/2));
for(i=0;i<((p-1)/2);i++){
shift[i] = (char *)malloc(sizeof(char)*M);}

char **zz5;
zz5 = (char **)malloc(sizeof(char*)*((p-1)/2));
for(i=0;i<((p-1)/2);i++){
zz5[i]=(char*)malloc(sizeof(char)*M*blocksize);}
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
printf("\nL---4---1---------------\n");			
				for(i=0;i<M;i++){
				shift1[i]=finite_mod((i-(M-L4[4][8])),M);}


 				for(i=0;i<M;i++){
			        z5_1[i]=yy5[shift1[i]];}

				b1=L4[4][9]-L4[4][8];
			 
			        shift=shift_value(b1,tau,p,M); 

				
				for(i=0;i<((p-1)/2);i++){
				for(j=0;j<M;j++){
				for(i1=0;i1<blocksize;i1++){
				zz5[i][j*blocksize+i1]=*(z5_1[shift[i][j]]+i1);}}}

 
				for(i=0;i<((p-1)/2-1);i++){			
		                galois_region_xor1((zz5[i]),(zz5[i+1]),(zz5[i+1]),M*blocksize);}
				

printf("\nL---4---2-------------\n");
				
				

				
				for(i=0;i<M;i++){
			        galois_region_xor1(yy4[i],(zz5[((p-1)/2)-1]+i*blocksize),z4_1[i],blocksize);}
	
				for(i=0;i<M;i++){
				shift1[i]=finite_mod((i-(M-L4[3][6])),M);}
				

				for(i=0;i<M;i++){
			        z4_2[i]=z4_1[shift1[i]];}
				


			        b1=L4[3][7]-L4[3][6]; //b=1
				printf(" \nb1:\n ");
				printf(" %d ",b1);

	
				shift=shift_value(b1,tau,p,M);

				for(i=0;i<((p-1)/2);i++){
				for(j=0;j<M;j++){
				for(i1=0;i1<blocksize;i1++){
				zz4[i][j*blocksize+i1]=*(z4_2[shift[i][j]]+i1);}}}
			

				for(i=0;i<((p-1)/2-1);i++){			
		                galois_region_xor1((zz4[i]),(zz4[i+1]),(zz4[i+1]),M*blocksize);}


printf("\nL---4---3------------\n");
				
				

				
				for(i=0;i<M;i++){
			        galois_region_xor1(yy3[i],(zz4[((p-1)/2)-1]+i*blocksize),z3_1[i],blocksize);}
	
				for(i=0;i<M;i++){
				shift1[i]=finite_mod((i-(M-L4[2][4])),M);}
				

				for(i=0;i<M;i++){
			        z3_2[i]=z3_1[shift1[i]];}
				
 

			        b1=L4[2][5]-L4[2][4]; //b=1
				printf(" \nb1:\n ");
				printf(" %d ",b1);

	
				shift=shift_value(b1,tau,p,M);

				for(i=0;i<((p-1)/2);i++){
				for(j=0;j<M;j++){
				for(i1=0;i1<blocksize;i1++){
				zz3[i][j*blocksize+i1]=*(z3_2[shift[i][j]]+i1);}}}
			

				for(i=0;i<((p-1)/2-1);i++){			
		                galois_region_xor1((zz3[i]),(zz3[i+1]),(zz3[i+1]),M*blocksize);}

printf("\nL---4---4------------\n");
				
				

				
				for(i=0;i<M;i++){
			        galois_region_xor1(yy2[i],(zz3[((p-1)/2)-1]+i*blocksize),z2_1[i],blocksize);}
	
				for(i=0;i<M;i++){
				shift1[i]=finite_mod((i-(M-L4[1][2])),M);}
				

				for(i=0;i<M;i++){
			        z2_2[i]=z2_1[shift1[i]];}
				
 

			        b1=L4[1][3]-L4[1][2]; //b=1
				printf(" \nb1:\n ");
				printf(" %d ",b1);

	
				shift=shift_value(b1,tau,p,M);

				for(i=0;i<((p-1)/2);i++){
				for(j=0;j<M;j++){
				for(i1=0;i1<blocksize;i1++){
				zz2[i][j*blocksize+i1]=*(z2_2[shift[i][j]]+i1);}}}
			

				for(i=0;i<((p-1)/2-1);i++){			
		                galois_region_xor1((zz2[i]),(zz2[i+1]),(zz2[i+1]),M*blocksize);}




printf("\nL---4---5---------------\n");	
				

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
printf("\nzz5======================================== \n");
for(j1=0;j1<M;j1++){
printf(" %d ",zz5[((p-1)/2)-1][j1*blocksize]);}
printf("\nL--3----------------------------------------------------------------------------------------------------------------------------\n");
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
char **t4_2;
t4_2 = (char **)malloc(sizeof(char*)*M);
for(i=0;i<M;i++){
t4_2[i]=(char*)malloc(sizeof(char)*blocksize);}
		
char **t5_1;
t5_1 = (char **)malloc(sizeof(char*)*M);
for(i=0;i<M;i++){
t5_1[i]=(char*)malloc(sizeof(char)*blocksize);}


char **tt5;
tt5 = (char **)malloc(sizeof(char*)*((p-1)/2));
for(i=0;i<((p-1)/2);i++){
tt5[i]=(char*)malloc(sizeof(char)*M*blocksize);}
char **tt4;
tt4 = (char **)malloc(sizeof(char*)*((p-1)/2));
for(i=0;i<((p-1)/2);i++){
tt4[i]=(char*)malloc(sizeof(char)*M*blocksize);}
char **tt3;
tt3 = (char **)malloc(sizeof(char*)*((p-1)/2));
for(i=0;i<((p-1)/2);i++){
tt3[i]=(char*)malloc(sizeof(char)*M*blocksize);}
printf("\nL--3--1---------------\n");	
				for(i=0;i<M;i++){
				shift1[i]=finite_mod((i-(M-L3[4][8])),M);}

 				for(i=0;i<M;i++){
				t5_1[i]=zz5[((p-1)/2)-1]+shift1[i]*blocksize;}
			        

				b1=L3[4][9]-L3[4][8];// b=2
			        printf(" \nb1:\n ");
				printf(" %d ",b1);
				
			
			        shift=shift_value(b1,tau,p,M); 

			
				for(i=0;i<((p-1)/2);i++){
				for(j=0;j<M;j++){
				for(i1=0;i1<blocksize;i1++){
				tt5[i][j*blocksize+i1]=*(t5_1[shift[i][j]]+i1);}}}


				
				for(i=0;i<((p-1)/2-1);i++){
							
		                galois_region_xor1((tt5[i]),(tt5[i+1]),(tt5[i+1]),M*blocksize);}
				

printf("\nL--3--2------------------\n");
				
				

				
				for(i=0;i<M;i++){
			        galois_region_xor1(zz4[((p-1)/2)-1]+i*blocksize,(tt5[((p-1)/2)-1]+i*blocksize),t4_1[i],blocksize);}

				for(i=0;i<M;i++){
				shift1[i]=finite_mod((i-(M-L3[3][6])),M);}
				

				for(i=0;i<M;i++){
			        t4_2[i]=t4_1[shift1[i]];}
			


			        b1=L3[3][7]-L3[3][6]; //b=1
				printf(" \nb1:\n ");
				printf(" %d ",b1);

	
				shift=shift_value(b1,tau,p,M);

				for(i=0;i<((p-1)/2);i++){
				for(j=0;j<M;j++){
				for(i1=0;i1<blocksize;i1++){
				tt4[i][j*blocksize+i1]=*(t4_2[shift[i][j]]+i1);}}}
			

				for(i=0;i<((p-1)/2-1);i++){			
		                galois_region_xor1((tt4[i]),(tt4[i+1]),(tt4[i+1]),M*blocksize);}

printf("\nL--3--3------------------\n");
				
				
				for(i=0;i<M;i++){
			        galois_region_xor1(zz3[((p-1)/2)-1]+i*blocksize,(tt4[((p-1)/2)-1]+i*blocksize),t3_1[i],blocksize);}

				for(i=0;i<M;i++){
				shift1[i]=finite_mod((i-(M-L3[2][4])),M);}
				

				for(i=0;i<M;i++){
			        t3_2[i]=t3_1[shift1[i]];}
			


			        b1=L3[2][5]-L3[2][4]; //b=1
				printf(" \nb1:\n ");
				printf(" %d ",b1);

	
				shift=shift_value(b1,tau,p,M);

				for(i=0;i<((p-1)/2);i++){
				for(j=0;j<M;j++){
				for(i1=0;i1<blocksize;i1++){
				tt3[i][j*blocksize+i1]=*(t3_2[shift[i][j]]+i1);}}}
			

				for(i=0;i<((p-1)/2-1);i++){			
		                galois_region_xor1((tt3[i]),(tt3[i+1]),(tt3[i+1]),M*blocksize);}
printf("\nL--3--4------------\n");
				
				

				
				for(i=0;i<M;i++){
			        galois_region_xor1((zz2[((p-1)/2)-1]+i*blocksize),(tt3[((p-1)/2)-1]+i*blocksize),t2[i],blocksize);}



printf("\nL--3--5---------------\n");	
				

			      for(i=0;i<M;i++){
			      t1[i]=z1[i]; }


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
printf("\ntt5======================================== \n");
for(j1=0;j1<M;j1++){
printf(" %d ",tt5[((p-1)/2)-1][j1*blocksize]);}
printf("\nL----2---------------------------------------------------------------------------------------------------------------------------------------\n");		

char **s5_1;
s5_1 = (char **)malloc(sizeof(char*)*M);
for(i=0;i<M;i++){
s5_1[i]=(char*)malloc(sizeof(char)*blocksize);}

char **s4_1;
char **s4_2;
s4_1 = (char **)malloc(sizeof(char*)*M);
for(i=0;i<M;i++){
s4_1[i]=(char*)malloc(sizeof(char)*blocksize);}

s4_2 = (char **)malloc(sizeof(char*)*M);
for(i=0;i<M;i++){
s4_2[i]=(char*)malloc(sizeof(char)*blocksize);}

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
char **ss5;
ss5 = (char **)malloc(sizeof(char*)*((p-1)/2));
for(i=0;i<((p-1)/2);i++){
ss5[i]=(char*)malloc(sizeof(char)*M*blocksize);}
printf("\nL--2--1---------------\n");
			



			for(i=0;i<M;i++){
			shift1[i]=finite_mod((i-(M-L2[4][8])),M);}

			for(i=0;i<M;i++){
			s5_1[i]=tt5[((p-1)/2)-1]+shift1[i]*blocksize;}


			b1=L2[4][9]-L2[4][8];
			printf(" \nb1:\n ");
			printf(" %d ",b1);

			shift=shift_value(b1,tau,p,M);

				for(i=0;i<((p-1)/2);i++){
				for(j=0;j<M;j++){
				for(i1=0;i1<blocksize;i1++){
				ss5[i][j*blocksize+i1]=*(s5_1[shift[i][j]]+i1);}}}
			

				for(i=0;i<((p-1)/2-1);i++){			
		                galois_region_xor1((ss5[i]),(ss5[i+1]),(ss5[i+1]),M*blocksize);}

printf("\nL--2--2------------------\n");
				
				

				
				for(i=0;i<M;i++){
			        galois_region_xor1(tt4[((p-1)/2)-1]+i*blocksize,(ss5[((p-1)/2)-1]+i*blocksize),s4_1[i],blocksize);}

				for(i=0;i<M;i++){
				shift1[i]=finite_mod((i-(M-L2[3][6])),M);}
				

				for(i=0;i<M;i++){
			        s4_2[i]=s4_1[shift1[i]];}
			


			        b1=L2[3][7]-L2[3][6]; //b=1
				printf(" \nb1:\n ");
				printf(" %d ",b1);

	
				shift=shift_value(b1,tau,p,M);

				for(i=0;i<((p-1)/2);i++){
				for(j=0;j<M;j++){
				for(i1=0;i1<blocksize;i1++){
				ss4[i][j*blocksize+i1]=*(s4_2[shift[i][j]]+i1);}}}
			

				for(i=0;i<((p-1)/2-1);i++){			
		                galois_region_xor1((ss4[i]),(ss4[i+1]),(ss4[i+1]),M*blocksize);}

printf("L--2--3----------------\n");

			
			for(i=0;i<M;i++){
			galois_region_xor1((tt3[((p-1)/2)-1]+i*blocksize),(ss4[((p-1)/2)-1]+i*blocksize),(s3[i]),blocksize);}




printf("L--2--4----------------\n");		
			
			for(i=0;i<M;i++){
			s2[i]=t2[i];}
			

printf("L--2--5----------------\n");		
			
			for(i=0;i<M;i++){
			s1[i]=t1[i];}
			

 
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
printf("\nss5======================================== \n");
for(j1=0;j1<M;j1++){
printf(" %d ",ss5[((p-1)/2)-1][j1*blocksize]);}

printf("\nL----1---------------------------------------------------------------------------------------------------------------------------------------\n");		

char **g5_1;
g5_1 = (char **)malloc(sizeof(char*)*M);
for(i=0;i<M;i++){
g5_1[i]=(char*)malloc(sizeof(char)*blocksize);}


char **g4;
g4 = (char **)malloc(sizeof(char*)*M);
for(i=0;i<M;i++){
g4[i]=(char*)malloc(sizeof(char)*blocksize);}
char **g3;
g3 = (char **)malloc(sizeof(char*)*M);
for(i=0;i<M;i++){
g3[i]=(char*)malloc(sizeof(char)*blocksize);}
char **g2;
g2 = (char **)malloc(sizeof(char*)*M);
for(i=0;i<M;i++){
g2[i]=(char*)malloc(sizeof(char)*blocksize);}
char **g1;
g1 = (char **)malloc(sizeof(char*)*M);
for(i=0;i<M;i++){
g1[i]=(char*)malloc(sizeof(char)*blocksize);}

char **gg5;
gg5 = (char **)malloc(sizeof(char*)*((p-1)/2));
for(i=0;i<((p-1)/2);i++){
gg5[i]=(char*)malloc(sizeof(char)*M*blocksize);}

printf("\nL--2--1---------------\n");
			



			for(i=0;i<M;i++){
			shift1[i]=finite_mod((i-(M-L1[4][8])),M);}

			for(i=0;i<M;i++){
			g5_1[i]=ss5[((p-1)/2)-1]+shift1[i]*blocksize;}


			b1=L1[4][9]-L1[4][8];
			printf(" \nb1:\n ");
			printf(" %d ",b1);

			shift=shift_value(b1,tau,p,M);

				for(i=0;i<((p-1)/2);i++){
				for(j=0;j<M;j++){
				for(i1=0;i1<blocksize;i1++){
				gg5[i][j*blocksize+i1]=*(g5_1[shift[i][j]]+i1);}}}
			

				for(i=0;i<((p-1)/2-1);i++){			
		                galois_region_xor1((gg5[i]),(gg5[i+1]),(gg5[i+1]),M*blocksize);}

printf("\nL--2--2------------------\n");
				
				

				
			for(i=0;i<M;i++){
			galois_region_xor1((ss4[((p-1)/2)-1]+i*blocksize),(gg5[((p-1)/2)-1]+i*blocksize),(g4[i]),blocksize);}


printf("L--2--3----------------\n");

			
			for(i=0;i<M;i++){
			g3[i]=s3[i];}




printf("L--2--4----------------\n");		
			
			for(i=0;i<M;i++){
			g2[i]=s2[i];}
			

printf("L--2--5----------------\n");		
			
			for(i=0;i<M;i++){
			g1[i]=s1[i];}
			

 
printf("\ng1======================================== \n");
for(j1=0;j1<M;j1++){
printf(" %d ",g1[j1][0]);}
printf("\ng2======================================== \n");
for(j1=0;j1<M;j1++){
printf(" %d ",g2[j1][0]);}
printf("\ng3======================================== \n");
for(j1=0;j1<M;j1++){
printf(" %d ",g3[j1][0]);}
printf("\ng4======================================== \n");
for(j1=0;j1<M;j1++){
printf(" %d ",g4[j1][0]);}
printf("\ngg5======================================== \n");
for(j1=0;j1<M;j1++){
printf(" %d ",gg5[((p-1)/2)-1][j1*blocksize]);}

char **fdata;
fdata=(char **)malloc(sizeof(char*)*M);
for(i=0;i<M;i++){
fdata[i]=(char *)malloc(sizeof(char)*r*blocksize);}

for(i=0;i<M;i++){ 

memcpy(fdata[i],g1[i],blocksize);
memcpy((fdata[i]+blocksize),g2[i],blocksize);
memcpy((fdata[i]+2*blocksize),g3[i],blocksize);
memcpy((fdata[i]+3*blocksize),g4[i],blocksize);
memcpy((fdata[i]+4*blocksize),(gg5[((p-1)/2)-1]+i*blocksize),blocksize);}

return fdata;

}//hanshu

