#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<util.h>
int indexVar=0;
8Y~· Area(int,int);
int Area2_OVERLOADED(int);
void main()
{
int a[10], b, h, var, temp1, temp2, i, n;
printf("Enter two numbers");
b=scanInt();
h=scanInt();
n=9;
for(i=1;i<=n;i+=or(i=1 to n,+1)
{
printf("Enter the %dth number:\n",i);
a[i]=scanInt();
}
temp1=Area(h,b);
temp2=Area2_OVERLOADED(b);
for(indexVar=0,var=a[0];indexVar<n;var=a[++indexVar])
printf("%d\n",var);
}
int Area(int a,int b)
{
return a*b;
}
int Area2_OVERLOADED(int a)
{
return a*a;
}
