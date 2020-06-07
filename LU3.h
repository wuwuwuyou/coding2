

#include "fun.h"
#include <stdio.h>
#include <stdlib.h>
char** LU_3(int **pp1,char **coding2,int k,int r,int p,int tau,int M,int blocksize){
printf("\nLU---r=3-------------------------------\n");
if(r!=3){fprintf(stderr,  "r shoule be equal to 3 \n");
			exit(0);}
int i,j,i1,j1;
char **U1;
char **U2;
char **L1;
char **L2;
U1 = (char **)malloc(sizeof(char*)*r);
for (i = 0; i <r ; i++) {
U1[i] = (char *)malloc(sizeof(char)*r);}
U2 = (char **)malloc(sizeof(char*)*r);
for (i = 0; i <r ; i++) {
U2[i] = (char *)malloc(sizeof(char)*r);}

L1 = (char **)malloc(sizeof(char*)*r);
for (i = 0; i <r ; i++) {
L1[i] = (char *)malloc(sizeof(char)*2*r);}			
L2 = (char **)malloc(sizeof(char*)*r);
for (i = 0; i <r ; i++) {
L2[i] = (char *)malloc(sizeof(char)*2*r);}	

char *shift1;
shift1 = (char *)malloc(sizeof(char)*M);

printf("LU--begin---\n");	
			for(i=0;i<r;i++){
			U1[i][i]=1;
			U2[i][i]=1;}


			U1[1][2]=pp1[1][k];
			U2[0][1]=pp1[1][k];
			U2[1][2]=pp1[1][k+1];
				

			L2[0][0]=1;
			L2[1][0]=1;
			L2[2][2]=1;
			L2[1][2]=pp1[1][k];
			L2[1][3]=pp1[1][k+1];
			L2[2][4]=pp1[1][k];
			L2[2][5]=pp1[1][k+2];

			L1[0][0]=1;
			L1[1][2]=1;
			L1[2][2]=1;
			L1[2][4]=pp1[1][k+1];
			L1[2][5]=pp1[1][k+2];

			

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
	
			
printf("\nLU--1-1----------\n");
			for(i=0;i<M;i++){
			x1[i]=coding2[i];}

printf("\nLU--1-2-----------\n");
			for(i=0;i<M;i++){
			x2[i]=coding2[i]+blocksize;}

			
printf("\nLU--1-3-----------\n");		
				 for(i=0;i<M;i++){
				shift1[i]=finite_mod((i-U1[1][2]), M);}
				
			        printf(" shift1: \n ");
				for(j1=0;j1<M;j1++){
				printf(" %d ",shift1[j1]);}  
			  
			    
		     
			    for(i=0;i<M;i++){
			    galois_region_xor1(x2[shift1[i]],(coding2[i]+2*blocksize),x3[i],blocksize);}

printf("\noriginal \n");	
for(j1=0;j1<M;j1++){
printf(" %d ",x2[j1][0]);} 
printf("\nshift \n");
for(j1=0;j1<M;j1++){
printf(" %d ",x2[shift1[j1]][0]);} 
printf("\nv3 \n");
for(j1=0;j1<M;j1++){
printf(" %d ",coding2[j1][2*blocksize]);} 
printf("\nXOR-x3 \n");
for(j1=0;j1<M;j1++){
printf(" %d ",x3[j1][0]);} 
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
printf("\nLU--2-1--------------\n");
			    for(i=0;i<M;i++){
			    y1[i]=x1[i];}

printf("\nLU--2-2---------------\n");

				for(i=0;i<M;i++){
				shift1[i]=finite_mod((i-U2[0][1]), M);}
 				printf(" shift1: \n ");
				for(j1=0;j1<M;j1++){
				printf(" %d ",shift1[j1]);}


			    for(i=0;i<M;i++){
			    galois_region_xor1(y1[shift1[i]],x2[i],y2[i],blocksize);}
 
printf("\noriginal-y1 \n");	
for(j1=0;j1<M;j1++){
printf(" %d ",y1[j1][0]);} 
printf("\nshift \n");
for(j1=0;j1<M;j1++){
printf(" %d ",y1[shift1[j1]][0]);} 
printf("\nx2 \n");
for(j1=0;j1<M;j1++){
printf(" %d ",x2[j1][0]);} 
printf("\nXOR-y2 \n");
for(j1=0;j1<M;j1++){
printf(" %d ",y2[j1][0]);}			 
			    
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

printf("\ny1======================================== \n");	
for(j1=0;j1<M;j1++){
printf(" %d ",y1[j1][0]);} 
printf("\ny2======================================== \n");
for(j1=0;j1<M;j1++){
printf(" %d ",y2[j1][0]);}
printf("\ny3======================================== \n");
for(j1=0;j1<M;j1++){
printf(" %d ",y3[j1][0]);}
			

printf("\nLU--3------------------------------------------------\n");			
char **z1;
z1 = (char **)malloc(sizeof(char*)*M);
for(i=0;i<M;i++){
z1[i]=(char*)malloc(sizeof(char)*blocksize);}

char **z2_3;
z2_3 = (char **)malloc(sizeof(char*)*M);
for(i=0;i<M;i++){
z2_3[i]=(char*)malloc(sizeof(char)*blocksize);}
char **z2_4;
z2_4 = (char **)malloc(sizeof(char*)*M);
for(i=0;i<M;i++){
z2_4[i]=(char*)malloc(sizeof(char)*blocksize);}
		
char **z3_1;
z3_1 = (char **)malloc(sizeof(char*)*M);
for(i=0;i<M;i++){
z3_1[i]=(char*)malloc(sizeof(char)*blocksize);}


int b1;
char **shift;
shift = (char **)malloc(sizeof(char*)*((p-1)/2));
for(i=0;i<((p-1)/2);i++){
shift[i] = (char *)malloc(sizeof(char)*M);}

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
				shift1[i]=finite_mod((i-(M-L2[2][4])),M);}
printf(" shift1: \n ");
for(j1=0;j1<M;j1++){
printf(" %d ",shift1[j1]);}
printf(" \n ");	

 				for(i=0;i<M;i++){
			        z3_1[i]=y3[shift1[i]];}
printf("\nz3_1 \n");
for(j1=0;j1<M;j1++){
printf(" %d ",z3_1[j1][0]);}
				b1=L2[2][5]-L2[2][4];// b=2
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
				zz3[i][j*blocksize+i1]=*(z3_1[shift[i][j]]+i1);}}}

printf("\nzz3 \n");
for(i=0;i<((p-1)/2);i++){
for(j1=0;j1<M;j1++){
printf(" %d ",zz3[i][j1*blocksize]);}
printf("\n");}



				
				//!!!!!!!!!!!!!!galois_region_xor1 li zhiyunxu you yige bianliang 
				for(i=0;i<((p-1)/2-1);i++){
				//for(j=0;j<M;j++){			
		                galois_region_xor1((zz3[i]),(zz3[i+1]),(zz3[i+1]),M*blocksize);}//}
				

				
				
printf("\nzz3-XOR \n");	
for(i=0;i<((p-1)/2);i++){			
for(j1=0;j1<M;j1++){
printf(" %d ",zz3[i][j1*blocksize]);}
printf("\n");}			  





 
printf("\n");
printf("\nLU--3-2-------------\n");
				
				//for(i=0;i<M;i++){
			        //z3[i]=zz3[((p-1)/2)-1]+i*blocksize;}

				
				for(i=0;i<M;i++){
			        galois_region_xor1(y2[i],(zz3[((p-1)/2)-1]+i*blocksize),z2_4[i],blocksize);}
printf("\ny2 \n");
for(j1=0;j1<M;j1++){
printf(" %d ",y2[j1][0]);}

printf("\nXOR-z2_4 \n");
for(j1=0;j1<M;j1++){
printf(" %d ",z2_4[j1][0]);}	
				for(i=0;i<M;i++){
				shift1[i]=finite_mod((i-(M-L2[1][2])),M);}
				
printf(" \nshift1: \n ");
for(j1=0;j1<M;j1++){
printf(" %d ",shift1[j1]);}
				for(i=0;i<M;i++){
			        z2_3[i]=z2_4[shift1[i]];}
				
printf("\nz2_3 \n");
for(j1=0;j1<M;j1++){
printf(" %d ",z2_3[j1][0]);} 

			        b1=L2[1][3]-L2[1][2]; //b=1
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
				zz2[i][j*blocksize+i1]=*(z2_3[shift[i][j]]+i1);}}}
				
printf("\nzz2 \n");
for(i=0;i<((p-1)/2);i++){
for(j1=0;j1<M;j1++){
printf(" %d ",zz2[i][j1*blocksize]);}
printf("\n");}
				for(i=0;i<((p-1)/2-1);i++){			
		                galois_region_xor1((zz2[i]),(zz2[i+1]),(zz2[i+1]),M*blocksize);}

printf("\nXOR--zz2 \n");
for(i=0;i<((p-1)/2);i++){
for(j1=0;j1<M;j1++){
printf(" %d ",zz2[i][j1*blocksize]);}
printf("\n");}
				





printf("\nLU--3-3---------------\n");	
				//buxuyao lingwai kaibi kongjian cunchu 
				//for(i=0;i<M;i++){
			       // z2[i]=zz2[((p-1)/2)-1]+i*blocksize;}	

			      for(i=0;i<M;i++){
			      galois_region_xor1(y1[i],(zz2[((p-1)/2)-1]+i*blocksize),z1[i],blocksize); }

printf("\ny1 \n");
for(j1=0;j1<M;j1++){
printf(" %d ",y1[j1][0]);}
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
printf("\nLU--4-----------------------------------\n");	
printf("\nLU--4-1--\n");		

char **s3_1;
s3_1 = (char **)malloc(sizeof(char*)*M);
for(i=0;i<M;i++){
s3_1[i]=(char*)malloc(sizeof(char)*blocksize);}

char **s11;
s11 = (char **)malloc(sizeof(char*)*M);
for(i=0;i<M;i++){
s11[i]=(char*)malloc(sizeof(char)*blocksize);}
char **s22;
s22 = (char **)malloc(sizeof(char*)*M);
for(i=0;i<M;i++){
s22[i]=(char*)malloc(sizeof(char)*blocksize);}

char **ss3;
ss3 = (char **)malloc(sizeof(char*)*((p-1)/2));
for(i=0;i<((p-1)/2);i++){
ss3[i]=(char*)malloc(sizeof(char)*M*blocksize);}
printf("\nLU--4-1--\n");
			



			for(i=0;i<M;i++){
			shift1[i]=finite_mod((i-(M-L1[2][4])),M);}
printf(" \nshift1: \n ");
for(j1=0;j1<M;j1++){
printf(" %d ",shift1[j1]);}
			for(i=0;i<M;i++){
			s3_1[i]=zz3[((p-1)/2)-1]+shift1[i]*blocksize;}



printf("\noringinal \n");	
for(j1=0;j1<M;j1++){
printf(" %d ",zz3[((p-1)/2)-1][j1*blocksize]);}
printf("\nshift \n");
for(j1=0;j1<M;j1++){
printf(" %d ",s3_1[j1][0]);}


			b1=L1[2][5]-L1[2][4];
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
				ss3[i][j*blocksize+i1]=*(s3_1[shift[i][j]]+i1);}}}
printf("\nss3 \n");
for(i=0;i<((p-1)/2);i++){
for(j1=0;j1<M;j1++){
printf(" %d ",ss3[i][j1*blocksize]);}
printf("\n");}				

				for(i=0;i<((p-1)/2-1);i++){			
		                galois_region_xor1((ss3[i]),(ss3[i+1]),(ss3[i+1]),M*blocksize);}

printf("\nXOR--ss3 \n");
for(i=0;i<((p-1)/2);i++){
for(j1=0;j1<M;j1++){
printf(" %d ",ss3[i][j1*blocksize]);}
printf("\n");}



printf("LU--4-2--------------\n");

			
			for(i=0;i<M;i++){
			galois_region_xor1((zz2[((p-1)/2)-1]+i*blocksize),(ss3[((p-1)/2)-1]+i*blocksize),(s22[i]),blocksize);}


printf("\nzz2 \n");
for(j1=0;j1<M;j1++){
printf(" %d ",zz2[((p-1)/2)-1][j1*blocksize]);} 

printf("\nXOR s22\n");
for(j1=0;j1<M;j1++){
printf(" %d ",s22[j1][0]);}

			
			
			for(i=0;i<M;i++){
			s11[i]=z1[i];}
			
 printf("\nz1 \n");
for(j1=0;j1<M;j1++){
printf(" %d ",z1[j1][0]);} 


printf("\ns11 \n");
for(j1=0;j1<M;j1++){
printf(" %d ",s11[j1][0]);} 
printf("\ns11======================================== \n");
for(j1=0;j1<M;j1++){
printf(" %d ",s11[j1][0]);}
printf("\ns22======================================== \n");
for(j1=0;j1<M;j1++){
printf(" %d ",s22[j1][0]);}
printf("\nss3======================================== \n");
for(j1=0;j1<M;j1++){
printf(" %d ",ss3[((p-1)/2)-1][j1*blocksize]);}


char **fdata;
fdata=(char **)malloc(sizeof(char*)*M);
for(i=0;i<M;i++){
fdata[i]=(char *)malloc(sizeof(char)*r*blocksize);}

for(i=0;i<M;i++){ 

memcpy(fdata[i],s11[i],blocksize);
memcpy((fdata[i]+blocksize),s22[i],blocksize);
memcpy((fdata[i]+2*blocksize),(ss3[((p-1)/2)-1]+i*blocksize),blocksize);}

return fdata;

}//hanshu

