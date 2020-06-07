

#include <assert.h>
#include <time.h>
#include <sys/time.h>// struct stat headfile
#include <sys/stat.h>// struct stat headfile
#include <unistd.h>// struct stat headfile
#include <string.h>
#include <stdio.h>
#include <stdlib.h>// macllo headerfile
#include <errno.h>
#include <unistd.h>
#include "timing.h"
//#include "fun.h"//LU3.h zhong yibaohan zhelibuneng include----wrong
#include "LU3.h"
#include "LU4.h"
#include "LU5.h"
#include "cstring"// memset headfile


#define N 10

//enum　枚举名　{枚举元素1,枚举元素2,……};
enum Coding_Technique {GEBR};

char *Methods[N] = {"GEBR"};

/* Global variables for signal handler */
int readins, n;
enum Coding_Technique method;// dingyi meijubianliang wei method

/* Function prototypes */


//total += jfread(block, sizeof(char), buffersize, fp);
int jfread(void *ptr, int size, int nmembers, FILE *stream)
{
  if (stream != NULL) return fread(ptr, size, nmembers, stream);

 
  return size;
}




int main (int argc, char **argv) {
	FILE *fp, *fp2;				// file pointers
	char *block;				// padding file
	int size, newsize;			// size of file and temp size 
	struct stat status;//定义局部的结构体类型变量status // finding file size   
			   //_stat函数用来获取指定路径的文件或者文件夹的信息
	
	enum Coding_Technique tech;//定义枚举型变量 tech		// coding technique (parameter)
	int k, r, w,p,tau, packetsize,M,miu,l;		// parameters
	int buffersize;					// paramter
	int i,i1,j,i2,j1;						// loop control variables
	int blocksize,stripe_size;					// size of k+m files
	int total;
	int extra;
	int flag=0;
	
	/* Jerasure Arguments */
	char **data;				
	
	
	
	/* Creation of file name variables */
	char temp[5];
	char *s1s, *s2s, *extension;
	char *fname;
	int md;
	char *curdir;
	
	/* Timing variables */
	struct timing q1,q2,q3,q4,q5,q6;//定义局部的结构体类型变量 t1...
	
	double extra_bit_time;
	double first_matrix_mul_time;
	double LU_time;
	double sum_time;
	//struct timing start;

	/* Find buffersize */
	int up, down;

	/* Start timing */
	
	/* Error check Arguments*/
	if (argc != 10) {			//stderr（标准错误），是不带缓冲的，这使得出错信息可以直接尽快地显示出来。
		fprintf(stderr,  "usage: inputfile k m coding_technique w packetsize buffersize\n");
		fprintf(stderr,  "\nChoose one of the following coding techniques: \nreed_sol_van, \nreed_sol_r6_op, \ncauchy_orig, \ncauchy_good, \nliberation, \nblaum_roth, \nliber8tion");
		fprintf(stderr,  "\n\nPacketsize is ignored for the reed_sol's");
		fprintf(stderr,  "\nBuffersize of 0 means the buffersize is chosen automatically.\n");
		fprintf(stderr,  "\nIf you just want to test speed, use an inputfile of \"-number\" where number is the size of the fake file you want to test.\n\n");
		exit(0);
	}
	/* Conversion of parameters and error checking */	//sscanf /scanf   shuru    //printf sprintf  shuchu
	if (sscanf(argv[2], "%d", &k) == 0 || k <= 0) {
		fprintf(stderr,  "Invalid value for k\n"); //格式化输出到一个流文件中；int fprintf( FILE *stream, const char *format, [ argument ]...)，
								//fprintf()函数根据指定的格式(format)，向输出流(stream)写入数据(argument)。
		exit(0);
	}
	if (sscanf(argv[3], "%d", &r) == 0 || r < 0) {
		fprintf(stderr,  "Invalid value for m\n");
		exit(0);
	}
	if (sscanf(argv[7],"%d", &w) == 0 || w <= 0) {
		fprintf(stderr,  "Invalid value for w.\n");
		exit(0);
	}
	if (sscanf(argv[4],"%d", &p) == 0 || p <= 0) {
		fprintf(stderr,  "Invalid value for p.\n");
		exit(0);
	}
	if (sscanf(argv[5],"%d", &tau) == 0 || tau <= 0) {
		fprintf(stderr,  "Invalid value for tau.\n");
		exit(0);
	}
	if(p!=k+r){fprintf(stderr,  "p should equal to k+r \n");
			exit(0);}
	if(tau!=1){fprintf(stderr,  "tau should equal to 1 \n");
			exit(0);}	
	if (argc == 6) {
		packetsize = 0;
	}
	else {
		if (sscanf(argv[8], "%d", &packetsize) == 0 || packetsize < 0) {
			fprintf(stderr,  "Invalid value for packetsize.\n");
			exit(0);
		}
	}
	if (argc != 8) {
		buffersize = 0;
	}
	
	else {
		if (sscanf(argv[9], "%d", &buffersize) == 0 || buffersize < 0) {
			fprintf(stderr, "Invalid value for buffersize\n");
			exit(0);
		}
		
	}

	/* Determine proper buffersize by finding the closest valid buffersize to the input value  */
	if (buffersize != 0) {
		if (packetsize != 0 && buffersize%(sizeof(long)*w*k*packetsize) != 0) { 
			up = buffersize;
			down = buffersize;
			while (up%(sizeof(long)*w*k*packetsize) != 0 && (down%(sizeof(long)*w*k*packetsize) != 0)) {
				up++;
				if (down == 0) {
					down--;
				}
			}
			if (up%(sizeof(long)*w*k*packetsize) == 0) {
				buffersize = up;
			}
			else {
				if (down != 0) {
					buffersize = down;
				}
			}
		}
		else if (packetsize == 0 && buffersize%(sizeof(long)*w*k) != 0) {
			up = buffersize;
			down = buffersize;
			while (up%(sizeof(long)*w*k) != 0 && down%(sizeof(long)*w*k) != 0) {
				up++;
				down--;
			}
			if (up%(sizeof(long)*w*k) == 0) {
				buffersize = up;
			}
			else {
				buffersize = down;
			}
		}
	}

	/* Setting of coding technique and error checking */
	
	if (strcmp(argv[6], "GEBR") == 0) {
		
		
		if (p%2==0) {
			fprintf(stderr,  "p must be a prime\n");
			exit(0);
		}
		tech = GEBR;
	}
	
	else {
		fprintf(stderr,  "Not a valid coding technique. Choose one of the following: reed_sol_van, reed_sol_r6_op, cauchy_orig, cauchy_good, liberation, blaum_roth, liber8tion, no_coding\n");
		exit(0);
	}

	/* Set global variable method for signal handler */
	method = tech;

	/* Get current working directory for construction of file names */
	curdir = (char*)malloc(sizeof(char)*1000);	
	assert(curdir == getcwd(curdir, 1000));
					//char *getcwd( char *buffer, int maxlen );
					//getcwd()会将当前工作目录的绝对路径复制到参数buffer所指的内存空间中,参数maxlen为buffer的空间大小。
					//assert后面的表达式为假就结束程序
        if (argv[1][0] != '-') {

		/* Open file and error check */
		fp = fopen(argv[1], "rb");  //FILE *fp；   fp=fopen("***","r");//"rb"=打开一个二进制文件，文件必须存在，只允许读
		if (fp == NULL) {
			fprintf(stderr,  "Unable to open file.\n");
			exit(0);
		}
	
		/* Create Coding directory *///---------mark
		i = mkdir("Coding", S_IRWXU);  
		if (i == -1 && errno != EEXIST) {
			fprintf(stderr, "Unable to create Coding directory.\n");
			exit(0);
		}
	
		/* Determine original size of file *///---------mark
		stat(argv[1], &status);	//   status为之前定义的结构体变量   struct stat status;
		size = status.st_size;  //	int stat(const char * file_name, struct stat *buf);  stat()用来将参数file_name 所指的文件状态, 复制到参数buf 所指的结构中
        } else {
        	if (sscanf(argv[1]+1, "%d", &size) != 1 || size <= 0) {
                	fprintf(stderr, "Files starting with '-' should be sizes for randomly created input\n");
			exit(1);
		}
        	fp = NULL;
		
        }

	newsize = size;
	
	/* Find new size by determining next closest multiple */
	if (packetsize != 0) {
		if (size%(k*w*packetsize*sizeof(long)) != 0) {
			while (newsize%(k*w*packetsize*sizeof(long)) != 0) 
				newsize++;
		}
	}
	else {
		if (size%(k*w*sizeof(long)) != 0) {
			while (newsize%(k*w*sizeof(long)) != 0) 
				newsize++;
		}
	}
	
	if (buffersize != 0) {
		while (newsize%buffersize != 0) {
			newsize++;
		}
	}


	/* Determine size of k+m files */
	//blocksize = newsize/k;

        stripe_size=newsize/((p-1)*tau);
	blocksize = stripe_size/k;
	M=p*tau;
	n=k+r;
	/* Allow for buffersize and determine number of read-ins */
	if (size > buffersize && buffersize != 0) {
		if (newsize%buffersize != 0) {
			readins = newsize/buffersize;
		}
		else {
			readins = newsize/buffersize;
		}
		block = (char *)malloc(sizeof(char)*buffersize);
		blocksize = buffersize/k;
	}
	else {
		readins = 1;
		buffersize = size;
		block = (char *)malloc(sizeof(char)*newsize);
	}
	printf("buffersize:%d\n", buffersize);
	printf("size:%d\n", size);
        printf("newsize:%d\n",newsize);
	printf("stripe_size:%d\n",stripe_size);	
	printf("blocksize:%d\n", blocksize);
	printf("p:%d\n", p);
	printf("r:%d\n", r);
	printf("tau:%d\n", tau);
	printf("M:%d\n", M);
	printf("k:%d\n", k);
	printf("n:%d\n", n);
	/* Break inputfile name into the filename and extension */	
	s1s = (char*)malloc(sizeof(char)*(strlen(argv[1])+20));
	s2s = strrchr(argv[1], '/');  //strrchr() 函数 查找字符在指定字符串中从右面开始的第一次出现的位置，如果成功，返回该字符以及其后面的字符，如果失败，则返回 NULL。
					//与之相对应的是strchr()函数，它查找字符串中首次出现指定字符以及其后面的字符。
	if (s2s != NULL) {
		s2s++;
		strcpy(s1s, s2s);
	}
	else {
		strcpy(s1s, argv[1]);
	}
	s2s = strchr(s1s, '.');
	if (s2s != NULL) {
          extension = strdup(s2s);  //c语言中常用的一种字符串拷贝库函数，一般和free（）函数成对出现
          *s2s = '\0';
	} else {
          extension = strdup("");
        }
	
	/* Allocate for full file name */
	fname = (char*)malloc(sizeof(char)*(strlen(argv[1])+strlen(curdir)+20));
	sprintf(temp, "%d", k);   //将k的内容存储到temp数组 sprintf为输出函数 把结果输出到指定的字符串(*buffer)中   int sprintf( char *buffer, const char *format [, argument,...] );
	md = strlen(temp);         //char temp[5];
	
	/* Allocate data and coding */
	data = (char **)malloc(sizeof(char*)*p*tau);
	for (i = 0; i < M; i++) {
		data[i] = (char *)malloc(sizeof(char)*k*blocksize);
                if (data[i] == NULL) { perror("malloc"); exit(1); }
	}	
	
	/* Create coding matrix or bitmatrix and schedule */
	
	switch(tech) {
		
		case GEBR:
			break;
		
			assert(0);
	}
	//timing_set(&start);

	/* Read in data until finished */
	n = 1;
	total = 0;

	while (n <= readins) {
		/* Check if padding is needed, if so, add appropriate 
		   number of zeros */
		if (total < size && total+buffersize <= size) {
			total += jfread(block, sizeof(char), buffersize, fp);
		}
		else if (total < size && total+buffersize > size) {
			extra = jfread(block, sizeof(char), buffersize, fp);
			for (i = extra; i < buffersize; i++) {
				block[i] = '0';
			}
		}
		else if (total == size) {
			for (i = 0; i < buffersize; i++) {
				block[i] = '0';
			}
		}
	 		 
	
		/* Encode according to coding method */
		switch(tech) {	
			
			case GEBR:flag=1;
				break;
			
				assert(0);
			
		}


if (flag==1){	

/* Set pointers to point to file data */ 
		for(j = 0; j < (p-1)*tau; j++){
	       	 for (i = 0; i < k; i++) {
	          for(i1=0;i1<blocksize;i1++){
		   data[j][i*blocksize+i1] = *(block+((j*k+i)*blocksize)+i1);}}}
printf("extra bit---------------------\n");	
	
char **mark;
mark = (char **)malloc(sizeof(char*)*(p-1));//2
for (i = 0; i < p-1; i++) {
mark[i] = (char *)malloc(sizeof(char)*blocksize);}
 timing_set(&q1); 
	
       
		
				for(j=0;j<k;j++){
				for(miu=0;miu<tau;miu++){

				for(l=0;l<p-1;l++){//l=0 1 
				for(i1=0;i1<blocksize;i1++){
				mark[l][i1]=*(data[l*tau+miu]+j*blocksize+i1);}}


				
				for(l=0;l<p-2;l++){  // p=5 l=0 1 2
				galois_region_xor1(mark[l],mark[l+1],mark[l+1],blocksize);}

				for(i1=0;i1<blocksize;i1++){
				*(data[(p-1)*tau+miu]+j*blocksize+i1)=*(mark[p-2]+i1);}

				}
				}
timing_set(&q2);

printf("\ncheck2==============================:\n");


printf("\ndata-----------:\n");
for(i=0;i<M;i++){
for(j=0;j<k;j++){
printf(" %d ",data[i][j*blocksize]);}
printf("\n");}

printf("\n4-vandemonde----\n");

timing_set(&q3);
int **pp1;  
pp1 = (int **)malloc(sizeof(int*)*r);
for(i=0;i<r;i++){
pp1[i]=(int*)malloc(sizeof(int)*(k+r));}

			 for(j=0;j<k+r;j++){pp1[0][j]=0;}
			 for(j=0;j<k+r;j++){pp1[1][j]=j;}
			 for(i=2;i<r;i++){
			 for(j=0;j<k+r;j++){
			 pp1[i][j]=pp1[1][j]*i;}}
		        

				
	
printf("\npp1-----\n");
for(j=0;j<r;j++){
for(i=0;i<(k+r);i++){
printf(" %d ",pp1[j][i]);}
printf(" \n ");}
printf("\n");
	
char *shift5;
char **group;
group = (char **)malloc(sizeof(char*)*k);
for(i=0;i<k;i++){
group[i]=(char*)malloc(sizeof(char)*blocksize);}			
shift5 = (char *)malloc(sizeof(char)*k);
char **coding2;
coding2 = (char **)malloc(sizeof(char*)*p*tau);
for(j = 0; j < M; j++) {
coding2[j] = (char *)malloc(sizeof(char)*r*blocksize);}


printf("coding0---------------------------\n");	
printf("\ncoding1--2------------------------------\n");	
		
				
			for(i2=0;i2<r;i2++){ 
			for(i=0;i<M;i++){

			
			for(j1=0;j1<k;j1++){
			shift5[j1]=finite_mod((i-pp1[i2][j1]) , M);}


printf(" shift5: i2= %d\n ",i2);
for(j1=0;j1<k;j1++){
printf(" %d ",shift5[j1]);}
printf("\n");


			for(j=0;j<k;j++){
			for(i1=0;i1<blocksize;i1++){
			group[j][i1]=*(data[shift5[j]]+j*blocksize+i1);}}

			for(j=0;j<(k-1);j++){
			galois_region_xor1((group[j]),(group[j+1]),group[j+1],blocksize);}

			for(i1=0;i1<blocksize;i1++){
			coding2[i][i2*blocksize+i1]=group[k-1][i1];}


			}}

		

timing_set(&q4);
printf("\ncoding-----------:\n");
for(i=0;i<M;i++){
for(j=0;j<r;j++){
printf(" %d ",coding2[i][j*blocksize]);}
printf("\n");}


printf("\nshift complete-------------------------\n");


timing_set(&q5);
char **fdataa;
fdataa=(char **)malloc(sizeof(char*)*M);
for(i=0;i<M;i++){
fdataa[i]=(char *)malloc(sizeof(char)*r*blocksize);}

if(r==3){
fdataa=LU_3(pp1,coding2, k, r,p,tau, M,blocksize);}

if(r==4){
fdataa=LU_4(pp1,coding2, k, r,p,tau, M,blocksize);}

if(r==5){
fdataa=LU_5(pp1,coding2, k, r,p,tau, M,blocksize);}
timing_set(&q6);

		


/*char *test1;
test1 = (char *)malloc(sizeof(char)*8);
test1[0]=-49;test1[1]=-97;test1[2]=77;test1[3]=95;test1[4]=-113;test1[5]=100;test1[6]=116;test1[7]=-72;
char *test2;
test2 = (char *)malloc(sizeof(char)*8);
test2[0]=-85;test2[1]=95;test2[2]=117;test2[3]=56;test2[4]=-6;test2[5]=-113;test2[6]=-21;test2[7]=-125;
char *test3;
test3 = (char *)malloc(sizeof(char)*8);

galois_region_xor1(test1,test2,test3,8);
printf("-------\n");
for(i=0;i<8;i++){
printf(" %d ",test3[i]);}*/


		
	
/* Write data and encoded data to k+m files */
		for	(i = 0; i < k; i++) {
		 
			if (fp == NULL) {
				bzero(data[i], blocksize);}
 			else {									//char *fname;
				sprintf(fname, "%s/Coding/%s_k%0*d%s", curdir, s1s, md, i, extension);//  int sprintf( char *buffer, const char *format [, argument] … );
				if (n == 1) {
					fp2 = fopen(fname, "wb");  //FILE *fp；   fp=fopen("***","r");//wb：以二进制写模式打开 (参见 w )
													//ab：以二进制追加模式打开 (参见 a )
				}
				else {
				
				fp2 = fopen(fname, "ab");
				}
				for(j=0;j<M;j++){
				fwrite(&data[j][(i)*blocksize], sizeof(char), blocksize, fp2);}  //size_t fwrite(const void *ptr, size_t size, size_t nmemb, FILE *stream)
						//buffer：是一个指针，对fwrite来说，是要获取数据的地址  //把ptr所指向的数组中的数据写入到给定流stream中
												//该函数以二进制形式对文件进行操作，不局限于文本文件
				fclose(fp2);
			}
			
		}
          
		for	(i = 0; i < r; i++) {
			if (fp == NULL) {
				bzero(fdataa[i], blocksize);}
 			 else {
				sprintf(fname, "%s/Coding/%s_m%0*d%s", curdir, s1s, md, i, extension);
				if (n == 1) {
					fp2 = fopen(fname, "wb");
				}
				else {
					fp2 = fopen(fname, "ab");
				}
				for(j=0;j<M;j++){
				fwrite(&fdataa[j][(i)*blocksize], sizeof(char), blocksize, fp2);}
				fclose(fp2);
			}
		}
			/*for	(i = 0; i < 1; i++) {
			if (fp == NULL) {
				bzero(s11[i], blocksize);}
 			 else {
				sprintf(fname, "%s/Coding/%s_m%0*d%s", curdir, s1s, md, i, extension);
				if (n == 1) {
					fp2 = fopen(fname, "wb");
				}
				else {
					fp2 = fopen(fname, "ab");
				}
				for(j=0;j<M;j++){
				fwrite(s11[j], sizeof(char), blocksize, fp2);}
				fclose(fp2);
			}
		        }
			for	(i = 1; i < 2; i++) {
			if (fp == NULL) {
				bzero(s22[i], blocksize);}
 			 else {
				sprintf(fname, "%s/Coding/%s_m%0*d%s", curdir, s1s, md, i, extension);
				if (n == 1) {
					fp2 = fopen(fname, "wb");
				}
				else {
					fp2 = fopen(fname, "ab");
				}
				for(j=0;j<M;j++){
				fwrite(s22[j], sizeof(char), blocksize, fp2);}
				fclose(fp2);
			}
		        }
			for	(i = 2; i < 3; i++) {
			if (fp == NULL) {
				bzero(s33[i], blocksize);}
 			 else {
				sprintf(fname, "%s/Coding/%s_m%0*d%s", curdir, s1s, md, i, extension);
				if (n == 1) {
					fp2 = fopen(fname, "wb");
				}
				else {
					fp2 = fopen(fname, "ab");
				}
				for(j=0;j<M;j++){
				fwrite(s33[j], sizeof(char), blocksize, fp2);}
				fclose(fp2);
			}
		        }*/



	
		n++;
		
		/* Calculate encoding time */
		
		extra_bit_time=timing_delta(&q1,&q2);
		first_matrix_mul_time=timing_delta(&q3,&q4);
		LU_time=timing_delta(&q5,&q6);
		sum_time=extra_bit_time+first_matrix_mul_time+LU_time;


	free(coding2);
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
	free(s3_1);
	free(ss3);
	
	free(U1);
	free(U2);
	free(L1);
	free(L2);
	free(shift);*/
	
	free(pp1);
	free(group);
	free(shift5);
	
	//free(test1);
	//free(test2);
	//free(test3);

	}//flag
	}//while

	/* Create metadata file */
        if (fp != NULL) {
		sprintf(fname, "%s/Coding/%s_meta.txt", curdir, s1s);
		fp2 = fopen(fname, "wb");
		fprintf(fp2, "%s\n", argv[1]);
		fprintf(fp2, "%d\n", size);
		fprintf(fp2, "%d %d %d %d %d %d %d\n", k, r,p,tau, w, packetsize, buffersize);
		fprintf(fp2, "%s\n", argv[6]);
		fprintf(fp2, "%d\n", tech);
		fprintf(fp2, "%d\n", readins);
		fclose(fp2);
	}


	/* Free allocated memory */
	free(s1s);
	free(fname);
	free(block);
	free(curdir);
	free(data);
	
	
	
	
	/* Calculate rate in MB/sec and print */
	printf("Encoding (MB/sec): %0.10f\n", (((double) size)/1024.0/1024.0)/sum_time);
	printf("extra_bit_time: %0.10f\n", extra_bit_time);
	printf("first_matrix_mul_time: %0.10f\n", first_matrix_mul_time);
	printf("LU_time: %0.10f\n", LU_time);
	printf("sum_time: %0.10f\n", sum_time);
	
	return 0;
}//main


















