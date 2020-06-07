/* *
 * Copyright (c) 2014, James S. Plank and Kevin Greenan
 * All rights reserved.
 *
 * Jerasure - A C/C++ Library for a Variety of Reed-Solomon and RAID-6 Erasure
 * Coding Techniques
 *
 * Revision 2.0: Galois Field backend now links to GF-Complete
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 *
 *  - Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 *
 *  - Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in
 *    the documentation and/or other materials provided with the
 *    distribution.
 *
 *  - Neither the name of the University of Tennessee nor the names of its
 *    contributors may be used to endorse or promote products derived
 *    from this software without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
 * "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
 * LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
 * A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT
 * HOLDER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT,
 * INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING,
 * BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS
 * OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED
 * AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT
 * LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY
 * WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
 * POSSIBILITY OF SUCH DAMAGE.
 */

/* Jerasure's authors:

   Revision 2.x - 2014: James S. Plank and Kevin M. Greenan.
   Revision 1.2 - 2008: James S. Plank, Scott Simmerman and Catherine D. Schuman.
   Revision 1.0 - 2007: James S. Plank.
 */

/* 
This program takes as input an inputfile, k, m, a coding
technique, w, and packetsize.  It is the companion program
of encoder.c, which creates k+m files.  This program assumes 
that up to m erasures have occurred in the k+m files.  It
reads in the k+m files or marks the file as erased. It then
recreates the original file and creates a new file with the
suffix "decoded" with the decoded contents of the file.

This program does not error check command line arguments because 
it is assumed that encoder.c has been called previously with the
same arguments, and encoder.c does error check.
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <assert.h>
#include <unistd.h>
#include <sys/time.h>
#include <sys/stat.h>

#include <unistd.h>

#include "timing.h"

//#include "fun.h"
#include "LU3.h"
#include "LU4.h"
#include "LU5.h"
#define N 10


enum Coding_Technique {GEBR};

char *Methods[N] = {"GEBR"};

/* Global variables for signal handler */
enum Coding_Technique method;
int readins, n;

/* Function prototype */


int main (int argc, char **argv) {
	FILE *fp;				// File pointer

	/* Jerasure arguments */
	
	
	int *erasures;
	int *erased;
	
	
	char **fdata;
	char **fcoding;
	char **tempcoding;
	char **tempdata;
	char **ffdata;
	
	/* Parameters */
	int k, r,p,tau,M, w, packetsize, buffersize;
	int tech;
	char *c_tech;
	int jj=0;
	int i, j,i1,j1,i2,i4=0,i5=0;				// loop control variable, s
	int blocksize = 0;			// size of individual files
	int origsize;			// size of file before padding
	int total;				// used to write data, not padding to file
	struct stat status;		// used to find size of individual files
	int numerased;			// number of erased files
	int flag=0;	
	/* Used to recreate file names */
	char *temp;
	char *cs1, *cs2, *extension;
	char *fname;
	char *fname1;
	int md;
	char *curdir;

	/* Used to time decoding */
	struct timing q1,q2,q3,q4;
	
	double first_matrix_mul_time;
	double LU_time;
	double sum_time;

	
	/* Start timing */
	

	/* Error checking parameters */
	if (argc != 2) {
		fprintf(stderr, "usage: inputfile\n");
		exit(0);
	}
	curdir = (char *)malloc(sizeof(char)*1000);
	assert(curdir == getcwd(curdir, 1000));
	
	/* Begin recreation of file names */
	cs1 = (char*)malloc(sizeof(char)*strlen(argv[1]));
	cs2 = strrchr(argv[1], '/');
	if (cs2 != NULL) {
		cs2++;
		strcpy(cs1, cs2);
	}
	else {
		strcpy(cs1, argv[1]);
	}
	cs2 = strchr(cs1, '.');
	if (cs2 != NULL) {
                extension = strdup(cs2);
		*cs2 = '\0';
	} else {
           extension = strdup("");
        }	
	fname = (char *)malloc(sizeof(char*)*(100+strlen(argv[1])+20));

	/* Read in parameters from metadata file */
	sprintf(fname, "%s/Coding/%s_meta.txt", curdir, cs1);

	fp = fopen(fname, "rb");
        if (fp == NULL) {
          fprintf(stderr, "Error: no metadata file %s\n", fname);
          exit(1);
        }
	temp = (char *)malloc(sizeof(char)*(strlen(argv[1])+20));
	if (fscanf(fp, "%s", temp) != 1) {//int fscanf(FILE * stream, const char * format, [argument...]); 其功能为根据数据格式(format)，从输入流(stream)中读入数据，存储到argument中，遇到空格和换行时结束
		fprintf(stderr, "Metadata file - bad format\n");
		exit(0);
	}
	
	if (fscanf(fp, "%d", &origsize) != 1) {
		fprintf(stderr, "Original size is not valid\n");
		exit(0);
	}
	if (fscanf(fp, "%d %d %d %d %d %d %d", &k, &r, &p, &tau, &w, &packetsize, &buffersize) != 7) {
		fprintf(stderr, "Parameters are not correct\n");
		exit(0);
	}
	c_tech = (char *)malloc(sizeof(char)*(strlen(argv[1])+20));
	if (fscanf(fp, "%s", c_tech) != 1) {
		fprintf(stderr, "Metadata file - bad format\n");
		exit(0);
	}
	if (fscanf(fp, "%d", &tech) != 1) {
		fprintf(stderr, "Metadata file - bad format\n");
		exit(0);
	}
	method = tech;
	if (fscanf(fp, "%d", &readins) != 1) {
		fprintf(stderr, "Metadata file - bad format\n");
		exit(0);
	}
	fclose(fp);	
	M=p*tau;
	/* Allocate memory */
	erased = (int *)malloc(sizeof(int)*(k+r));
	for (i = 0; i < k+r; i++)
		erased[i] = 0;
	erasures = (int *)malloc(sizeof(int)*(k+r));

	
	tempdata = (char **)malloc(sizeof(char *)*k);
	tempcoding = (char **)malloc(sizeof(char *)*r);



		
	if (buffersize != origsize) {
		for (i = 0; i < k; i++) {
			//data[i] = (char *)malloc(sizeof(char)*(buffersize/k));
			tempdata[i] = (char *)malloc(sizeof(char *)*(buffersize/k));
		}
		for (i = 0; i < r; i++) {
			//coding[i] = (char *)malloc(sizeof(char)*(buffersize/k));
			tempcoding[i] = (char *)malloc(sizeof(char)*(buffersize/k));
		}
		blocksize = buffersize/k;
	}

	sprintf(temp, "%d", k);
	md = strlen(temp);
	
	printf("\nk:%d", k);
	printf("\nr:%d", r);
	printf("\np:%d", p);
	printf("\ntau:%d", tau);
	printf("\nM:%d", M);


        printf("\nbuffersize:%d\n", buffersize);
   
	
	/* Allow for buffersize and determine 
	/* Create coding matrix or bitmatrix */
	
	switch(tech) {
		
		case GEBR:
			flag=1;
			break;
	}
	
	//printf("matrix: \n");
	//jerasure_print_matrix(matrix,k+r,k,w);

//print_data_and_coding(k, r, w, sizeof(long), data, coding);
printf( " 0\n");
	

	/* Begin decoding process */
	total = 0;
	n = 1;	
	while (n <= readins) {
		numerased = 0;
		/* Open files, check for erasures, read in data/coding */	
			
		for (i = 0; i < k; i++) {
			sprintf(fname, "%s/Coding/%s_k%0*d%s", curdir, cs1, md, i, extension);
			fp = fopen(fname, "rb");
			if (fp == NULL) {
				erased[i] = 1;
				erasures[numerased] = i;
				numerased++;}
				
			else {
				if (buffersize == origsize) {
					stat(fname, &status);
					blocksize = status.st_size/M;
					
					//data[i] = (char *)malloc(sizeof(char)*blocksize);
					tempdata[i] = (char *)malloc(sizeof(char)*M*blocksize);
					assert(M*blocksize == fread(tempdata[i], sizeof(char), M*blocksize, fp));
				}
				
				fclose(fp);
			}
		}
				
					
		for (i = 0; i < r; i++) {
			sprintf(fname, "%s/Coding/%s_m%0*d%s", curdir, cs1, md, i, extension);
				fp = fopen(fname, "rb");
				if (fp == NULL) {
				erased[k+i] = 1;
				erasures[numerased] = k+i;
				numerased++;}	
			else{
				if (buffersize == origsize) {
					stat(fname, &status);
					blocksize = status.st_size/M;
					
					//coding[i] = (char *)malloc(sizeof(char)*blocksize);
					tempcoding[i] = (char *)malloc(sizeof(char)*M*blocksize);
					assert(M*blocksize == fread(tempcoding[i], sizeof(char), M*blocksize, fp));
				}
					
				fclose(fp);
			}
		}

printf("\n");
printf("blocksize:%d", blocksize);
printf("\n");
	/* Finish allocating data/coding if needed */
		if (n == 1) {
			for (i = 0; i < numerased; i++) {
				if (erasures[i] < k) {
					
					tempdata[erasures[i]] = (char *)malloc(sizeof(char)*M*blocksize);
				}
				else {
					
					tempcoding[erasures[i]-k] = (char *)malloc(sizeof(char)*M*blocksize);
				}
			}
		}
		erasures[numerased] = -1;

////??? malloc 
fdata = (char **)malloc(sizeof(char*)*M);
fcoding = (char **)malloc(sizeof(char*)*M);
ffdata = (char **)malloc(sizeof(char*)*M);
for(j = 0; j < M; j++) {
fdata[j] = (char *)malloc(sizeof(char)*k*blocksize);
fcoding[j] = (char *)malloc(sizeof(char)*r*blocksize);
ffdata[j] = (char *)malloc(sizeof(char)*(k+r)*blocksize);}

for(i=0;i<M;i++){
for(j=0;j<r*blocksize;j++){
fcoding[i][j]=0;}}



                 	for(i=0;i<M;i++){
                 	for(j1=0;j1<k;j1++){
                 	for(j=0;j<blocksize;j++){           
                	fdata[i][j+j1*blocksize]=*(tempdata[j1]+j+i*blocksize);}}}
                  	
   		


     			 for(i=0;i<M;i++){
    			 for(j1=0;j1<r;j1++){
      			 for(j=0;j<blocksize;j++){
      			 fcoding[i][j+j1*blocksize]=*(tempcoding[j1]+i*blocksize+j);}}}


printf("\n fdata 6*4: char \n ");
for(i1=0;i1<M;i1++){
for(j=0;j<k;j++){
printf(" %d ",fdata[i1][j*blocksize]);}
printf("\n");	}

printf("\n fcoding 6*3: char \n ");
for(i1=0;i1<M;i1++){
for(j=0;j<r;j++){
printf(" %d ",fcoding[i1][j*blocksize]);}
printf("\n");	}



			for(i=0;i<M;i++){
			for(j=0;j<k;j++){
			for(i1=0;i1<blocksize;i1++){
			ffdata[i][j*blocksize+i1]=fdata[i][j*blocksize+i1];}}}
			for(i=0;i<M;i++){
			for(j=0;j<r;j++){
			for(i1=0;i1<blocksize;i1++){
			ffdata[i][(j+k)*blocksize+i1]=fcoding[i][j*blocksize+i1];}}}


printf("\n ffdata 6*7: char \n ");
for(i1=0;i1<M;i1++){
for(j=0;j<(k+r);j++){
printf(" %d ",ffdata[i1][j*blocksize]);}
printf("\n");	}




if(flag==1){


char *mark1;
mark1 = (char *)malloc(sizeof(char)*r);
//memset(mark1,0,r);

char **markk;
markk = (char **)malloc(sizeof(char*)*r);
for(i=0;i<r;i++){
markk[i]=(char*)malloc(sizeof(char)*k);}


char **group;
group = (char **)malloc(sizeof(char*)*k);
for(i=0;i<k;i++){
group[i]=(char*)malloc(sizeof(char)*blocksize);}
char *shift5;			
shift5 = (char *)malloc(sizeof(char)*k);
int *p2group;
p2group = (int *)malloc(sizeof(int)*k);



printf( "\nerased:\n");
for(j1=0;j1<k+r;j1++)
{printf("%d ",erased[j1]);}
printf( " \n");
printf( "\nerasures:\n");
for(j1=0;j1<k+r;j1++)
{printf("%d ",erasures[j1]);}
printf( " \n");

for(i=0;i<k;i++){markk[0][i]=0;}


			for(i=0;i<k+r;i++){

   			if(erased[i]==0){
      			markk[1][i4]=i;
     			 i4++;}
			}
			
			for(i=0;i<r;i++){
			mark1[i]=erasures[i];}

			if(erasures[0]==-1){
			for(i=0;i<k;i++){
			markk[1][i]=i;}

			for(i=0;i<r;i++){
			mark1[i]=k+i;}
			}
			


printf("\nmark1-failed \n");
for(i=0;i<r;i++){
printf(" %d ",mark1[i]);}

printf("\nmark-survive \n");
for(i=0;i<k;i++){
printf(" %d ",markk[1][i]);}



for(i=2;i<r;i++){
for(j=0;j<k;j++){
markk[i][j]=markk[1][j]*i;}}
printf("\nmarkk \n");
for(i=0;i<r;i++){
for(j=0;j<k;j++){	
printf(" %d ",markk[i][j]);}
printf("\n");}



char **syndrome;
syndrome = (char **)malloc(sizeof(char*)*M);
for(j = 0; j < M; j++) {
syndrome[j] = (char *)malloc(sizeof(char)*r*blocksize);}


timing_set(&q1);

		for(i2=0;i2<r;i2++){
		for(i=0;i<M;i++){

			for(j1=0;j1<k;j1++){
			shift5[j1]=finite_mod((i-markk[i2][j1]),M);}
				printf(" shift5: i2= %d\n ",i2);
				for(j1=0;j1<k;j1++){
				printf(" %d ",shift5[j1]);}
				printf("\n");

			

			
			for(j=0;j<k;j++){
			for(i1=0;i1<blocksize;i1++){
			group[j][i1]=*(ffdata[shift5[j]]+markk[1][j]*blocksize+i1);}}

			for(j=0;j<(k-1);j++){
			galois_region_xor1((group[j]),(group[j+1]),group[j+1],blocksize);}

			for(i1=0;i1<blocksize;i1++){
			syndrome[i][i2*blocksize+i1]=group[k-1][i1];}
			
		}}
			



			
timing_set(&q2);
printf("\n syndrome 6*3: char \n ");
for(i1=0;i1<M;i1++){
for(j=0;j<r;j++){
printf(" %d ",syndrome[i1][j*blocksize]);}
printf("\n");	}




printf("\nLU----------------------------------\n");
	

timing_set(&q3);
printf("LU--begin---\n");	
			
char **fdataa;
fdataa=(char **)malloc(sizeof(char*)*M);
for(i=0;i<M;i++){
fdataa[i]=(char *)malloc(sizeof(char)*r*blocksize);}
int **pp1;  
pp1 = (int **)malloc(sizeof(int*)*r);
for(i=0;i<r;i++){
pp1[i]=(int*)malloc(sizeof(int)*(k+r));}

if(r==3&&erasures[0]!=k){
pp1[1][k]=mark1[0];pp1[1][k+1]=mark1[1];pp1[1][k+2]=mark1[2];
fdataa=LU_3(pp1,syndrome, k, r,p,tau, M,blocksize);}

if(r==4&&erasures[0]!=k){
pp1[1][k]=mark1[0];pp1[1][k+1]=mark1[1];pp1[1][k+2]=mark1[2];pp1[1][k+3]=mark1[3];
fdataa=LU_4(pp1,syndrome, k, r,p,tau, M,blocksize);}

if(r==5){
pp1[1][k]=mark1[0];pp1[1][k+1]=mark1[1];pp1[1][k+2]=mark1[2];pp1[1][k+3]=mark1[3];pp1[1][k+4]=mark1[4];
fdataa=LU_5(pp1,syndrome, k, r,p,tau, M,blocksize);}


timing_set(&q4);
/*for(i=0;i<M;i++){

if(mark1[0]<k && mark1[1]<k &&mark1[2]<k){// 0 1 2 3 
memcpy(fdata[i]+mark1[0]*blocksize,s11[i],blocksize);
memcpy(fdata[i]+mark1[1]*blocksize,s22[i],blocksize);
memcpy(fdata[i]+mark1[2]*blocksize,ss3[((p-1)/2)-1]+i*blocksize,blocksize);}

else if(mark1[0]<k && mark1[1]<k &&mark1[2]==k){//2 3 4
memcpy(fdata[i]+mark1[0]*blocksize,s11[i],blocksize);
memcpy(fdata[i]+mark1[1]*blocksize,s22[i],blocksize);}

else if(mark1[0]<k && mark1[1]==k &&mark1[2]>k){// 3 4 5
memcpy(fdata[i]+mark1[0]*blocksize,s11[i],blocksize);}

}	*/
//no need to full all solved data 
if(r==3&&erasures[0]!=k){
for(i=0;i<M;i++){

if(mark1[0]<k && mark1[1]<k &&mark1[2]<k){// 0 1 2 3 
for(j=0;j<r;j++){
memcpy(fdata[i]+mark1[j]*blocksize,fdataa[i]+j*blocksize,blocksize);}}


else if(mark1[0]<k && mark1[1]<k &&mark1[2]==k){//2 3 4
for(j=0;j<r-1;j++){
memcpy(fdata[i]+mark1[j]*blocksize,fdataa[i]+j*blocksize,blocksize);}}


else if(mark1[0]<k && mark1[1]==k &&mark1[2]>k){// 3 4 5
for(j=0;j<r-2;j++){
memcpy(fdata[i]+mark1[j]*blocksize,fdataa[i]+j*blocksize,blocksize);}}

}}
if(r==4&&erasures[0]!=k){
for(i=0;i<M;i++){

if( mark1[3]<k){// 0 1 2 3 
for(j=0;j<r;j++){
memcpy(fdata[i]+mark1[j]*blocksize,fdataa[i]+j*blocksize,blocksize);}}
else if(mark1[3]==k){//2 3 4
for(j=0;j<r-1;j++){
memcpy(fdata[i]+mark1[j]*blocksize,fdataa[i]+j*blocksize,blocksize);}}
else if(mark1[2]==k){// 3 4 5
for(j=0;j<r-2;j++){
memcpy(fdata[i]+mark1[j]*blocksize,fdataa[i]+j*blocksize,blocksize);}}
else if( mark1[1]==k ){// 3 4 5
for(j=0;j<r-3;j++){
memcpy(fdata[i]+mark1[j]*blocksize,fdataa[i]+j*blocksize,blocksize);}}
}}

if(r==5){
for(i=0;i<M;i++){

if( mark1[4]<k){
for(j=0;j<r;j++){
memcpy(fdata[i]+mark1[j]*blocksize,fdataa[i]+j*blocksize,blocksize);}}
else if(mark1[4]==k){
for(j=0;j<r-1;j++){
memcpy(fdata[i]+mark1[j]*blocksize,fdataa[i]+j*blocksize,blocksize);}}
else if(mark1[3]==k){
for(j=0;j<r-2;j++){
memcpy(fdata[i]+mark1[j]*blocksize,fdataa[i]+j*blocksize,blocksize);}}
else if(mark1[2]==k){
for(j=0;j<r-3;j++){
memcpy(fdata[i]+mark1[j]*blocksize,fdataa[i]+j*blocksize,blocksize);}}
else if( mark1[1]==k ){
for(j=0;j<r-4;j++){
memcpy(fdata[i]+mark1[j]*blocksize,fdataa[i]+j*blocksize,blocksize);}}
}}
	
		/* Create decoded file */
		sprintf(fname, "%s/Coding/%s_decoded%s", curdir, cs1, extension);
		if (n == 1) {
			fp = fopen(fname, "wb");
		}
		else {
			fp = fopen(fname, "ab");
		}
		



		for (i4 = 0; i4 < M; i4++) {
		

			if (total+k*blocksize <= origsize) {
			   
				fwrite(fdata[i4], sizeof(char), k*blocksize, fp);
			        total+= k*blocksize;}
			   
			else {
				
				for (i5 = 0; i5 < k*blocksize; i5++) {
					if (total < origsize) {
						
						fprintf(fp, "%c", fdata[i4][i5]);
						total++;
					}
					else {
						break;
					}
					
				}
			}//else
		}

char *test1;
test1 = (char *)malloc(sizeof(char)*5);
test1[0]=-1;test1[1]=33;test1[2]=10;test1[3]=-72;test1[4]=-11;
char *test2;
test2 = (char *)malloc(sizeof(char)*5);
test2[0]=105;test2[1]=105;test2[2]=24;test2[3]=-26;test2[4]=105;
char *test3;
test3 = (char *)malloc(sizeof(char)*5);
test3[0]=-7;test3[1]=83;test3[2]=56;test3[3]=83;test3[4]=-63;
/*char *test4;
test4 = (char **)malloc(sizeof(char*)*5);
test4[0]=-101;test4[1]=-112;test4[2]=-107;test4[3]=-38;test4[4]=-98;
char *test5;
test5 = (char **)malloc(sizeof(char*)*5);
test5[0]=-23;test5[1]=-81;test5[2]=73;test5[3]=-81;test5[4]=-98;
char *test6;
test6 = (char **)malloc(sizeof(char*)*5);
test6[0]=73;test6[1]=-66;test6[2]=42;test6[3]=-12;test6[4]=-98;
char *test7;
test7 = (char **)malloc(sizeof(char*)*5);
test7[0]=-112;test7[1]=55;test7[2]=-38;test7[3]=-82;test7[4]=-98;*/


galois_region_xor1(test1,test2,test2,5);
galois_region_xor1(test2,test3,test3,5);
/*galois_region_xor1(test3,test4,test4,5);
galois_region_xor1(test4,test5,test5,5);
galois_region_xor1(test5,test6,test6,5);
galois_region_xor1(test6,test7,test7,5);*/

printf("-------\n");
for(i=0;i<5;i++){
printf(" %d ",test3[i]);}




		n++;
		fclose(fp);

	free(syndrome);
	/*free(x1);
	free(x2);
	free(x3);
	free(y1);
	free(y2);
	free(y3);
	free(z1);
	

	free(zz2);
	free(z2_3);
	free(z2_4);

	free(z3_1);
	free(zz3);
	
	free(s11);
	free(s22);
	free(ss3);
	free(s3_1);
	
	free(U1);
	free(U2);
	free(L1);
	free(L2);*/
	free(markk);
	free(mark1);
	free(group);
	free(shift5);
	//free(shift);
	free(test1);
	free(test2);
	free(test3);

	}//if

	


	}//while
	/* Free allocated memory */
	free(cs1);
	free(extension);
	free(fname);
	//free(data);
	//free(coding);
	free(erasures);
	free(erased);
	free(fdata);
	free(fcoding);
	free(ffdata);
	free(tempdata);
	free(tempcoding);
	
	/* Stop timing and print time */
	
	first_matrix_mul_time = timing_delta(&q1, &q2);
	LU_time = timing_delta(&q3, &q4);
	sum_time = first_matrix_mul_time+LU_time;

	printf("Decoding (MB/sec): %0.10f\n", (((double) origsize)/1024.0/1024.0)/sum_time);
	
	printf("first_matrix_mul_time (sec): %0.10f\n\n", first_matrix_mul_time);
	printf("LU_time (sec): %0.10f\n\n", LU_time);
	printf("sum_time (sec): %0.10f\n\n", sum_time);
	return 0;
}	


