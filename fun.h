





#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>





void galois_region_xor1(           char *r1,         /* Region 1 */
                                  char *r2,         /* Region 2 */
                                  char *r3,         /* Sum region (r3 = r1 ^ r2) -- can be r1 or r2 */
                                  int nbytes)       /* Number of bytes in region */
{
  long *l1;
  long *l2;
  long *l3;
  long *ltop;
  char *ctop;
  
  ctop = r1 + nbytes;
  ltop = (long *) ctop;
  l1 = (long *) r1;
  l2 = (long *) r2;
  l3 = (long *) r3;
 
  while (l1 < ltop) {
    *l3 = ((*l1)  ^ (*l2));
    l1++;
    l2++;
    l3++;
  }
}



 

 int gcd(int a,int b)
{
    while(a!=b)
    {
       if(a>b)
           a-=b;
       else
           b-=a;
    }
    return a;
}


int finite_mod(int i,int M){
int ans;
ans=i%M;
if(ans<0)
{ans+=M;}
else
ans=ans;

return ans;}


char** shift_value(int b1, int tau,int p,int M){
int a;
int jj=0;
char *inver;
char **shiftt;
int i,j,j1;
inver = (char *)malloc(sizeof(char)*((p-1)/2));
shiftt = (char **)malloc(sizeof(char*)*((p-1)/2));
for(i=0;i<((p-1)/2);i++){
shiftt[i] = (char *)malloc(sizeof(char)*M);}

a=gcd(b1,tau);
for(j=0;j<((p-1)/2);j++){
for(i=(2*j+1)*tau/a;i<=((2*(j+1)*tau)/a-1);i++){
inver[jj]=i*b1;
jj++;}}


for(j=0;j<((p-1)/2);j++){
for(i=0;i<M;i++){
shiftt[j][i]=finite_mod((i-inver[j]),M);}}


				
return shiftt;
}


