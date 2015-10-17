int scanInt()
{
int n = 0;
char c;
for( c = getchar(); c==' ' || c=='\n' || c == '\t'; c = getchar());
for( ; c > 0x2f && c < 0x3a; c = getchar())
n = (n * 10) + (c & 0x0f);
return n;
}

double scanDouble()
{
 int n=0,n2=0,i=1;
 char c;
 double ans;
 for( c = getchar(); c==' ' || c=='\n' || c == '\t'; c = getchar());
 for( ; c > 0x2f && c < 0x3a; c = getchar())
 n = (n * 10) + (c & 0x0f);
 for( c=getchar(); c > 0x2f && c < 0x3a; c = getchar(),i++)
 n2 = (n2 * 10) + (c & 0x0f);
 ans=n2;
 while(i--)
   ans/=10;
 return ans+(double)n;
}

void getStrng(char *str)
{
 char ch;
 int i=0;
 for(ch=getchar();ch!='\n' || ch!='\r';ch=getchar())
    str[i++]=ch;
 str[i]='\0';
 return ;
}
