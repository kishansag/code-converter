#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<ctype.h>

#define getchar_unlocked getchar
#define MAX 1000

int getDataType(char*);
void printFunc(int,FILE*);
void directConvFunc(int,FILE*);
void directConvFunc2(int,FILE*);
void funcFunc(int,FILE*);
void declarationFunc(int,FILE*);
int initialAdditionsFunc(FILE*);
char* getTypeList(int);
void addFuncDeclarations(FILE*);
char*getStr(int);
void forLoopFunc(int,FILE*);
int superStringCheck(char[], char[]);
int funcNumCheck(char[] );
void takeCareOfLine(int, FILE*);
void removeExtraSpaces(char*);

int listOfLocalVarsSize=0,endindex=0,listOfGlobalVarsSize=0,funcListSize=0,noLines=0,globalVarFlag=1; 

char str[1000][1000];

struct FUNC_LIST
{
  int count;
  int flag;
  int suffix;
  int returnType;
  char name[100];
  int paramTypeList[1000];
  int size;
}funcList[100];

struct DATA_TYPE_INFO
{
 char varName[1000];
 int dataType;
}listOfLocalVars[1000],listOfGlobalVars[1000];

int main()
{ 
 int i,j,k;
 FILE *fp=fopen("output.c","w"),*fp1=fopen("input.txt","r");
 
 //COPIES THE INPUT FILE TO THE array str[][]
 for(i=0;fgets(str[i],1000,fp1)!=NULL;i++){
          for(j=strlen(str[i])-1;str[i][j]=='\n' || str[i][j]=='\r';j--)
             str[i][j]='\0';
          removeExtraSpaces(str[i]);       
 }
 noLines=i;

 i=initialAdditionsFunc(fp);
 for(;i<noLines;i++)
   takeCareOfLine(i,fp);
   
 fclose(fp);
 fclose(fp1);
// getch();
 return 0;
}

void printFunc(int ln,FILE *fp)
{
 char tempStr[1000]={},varList[1000]={},str2[1000]={};
 int l=strlen(str[ln]),dataType,i,j;
 strcat(str2,"printf(\"");
 for(i=6;i<l;i++)
 {
  for(j=0;str[ln][i]!=',' && str[ln][i]!=')';i++)
     tempStr[j++]=str[ln][i];
  tempStr[j]='\0';
  if(tempStr[0]=='"'){
     tempStr[j-1]='\0';
     strcat(str2,tempStr+1);
  }
  else
  {
   dataType=getDataType(tempStr);
   if(dataType==1)
     strcat(str2,"%c");
   else if(dataType==2)
     strcat(str2,"%d");
   else if(dataType==3)
     strcat(str2,"%f");
   else if(dataType==4)
     strcat(str2,"%s");
   else if(dataType==5 || dataType==6)
     strcat(str2,"%p");
   strcat(varList,",");
   strcat(varList,tempStr);
  }   
}   
 strcat(str2,"\"");
 strcat(str2,varList);
 strcat(str2,");");
 fprintf(fp,"%s\n",str2);
 //fprintf(stdout,"%s\n",str2);
 return ;
}


int getDataType(char *str)
{
 int i;
 for(i=0;i<listOfLocalVarsSize;i++)
 {
  if(!strcmp(listOfLocalVars[i].varName,str))
    return listOfLocalVars[i].dataType;
 }
 for(i=0;i<listOfGlobalVarsSize;i++)
 {
  if(!strcmp(listOfGlobalVars[i].varName,str))
    return listOfGlobalVars[i].dataType;
 }
 return 1;
}  
  

void directConvFunc(int ln,FILE *fp)
{
 fprintf(fp,"%s\n",str[ln]);
 return ;
}

void directConvFunc2(int ln,FILE *fp)
{
 fprintf(fp,"%s;\n",str[ln]);
 return ;
}

void declarationFunc(int linenum, FILE* fp)
{ int i;
  char* token;
  char split[100][200],temp[100];
  int Count,type,k;
  char result[200];
  //printf("%s\n",str[linenum-1]);
   linenum++; 
//DEVIDE THE STRING INTO TOKENS
        token = strtok(str[linenum-1]," ");
        for(i=0; token != NULL;i++ ) 
        {
        strcpy(split[i], token );
        //printf("%s%d\n", split[i],i);
        token = strtok(NULL, ",;");
  
        }
  Count=i;
    

//FOR BIGINT  
  if(strcmp(split[0],"bigInt")==0)
    {
      strcpy(split[0],"int");
      for(i=1;i<Count;i++)
      strcat(split[i],"[1000000]");
    }

//FOR CHARACTER

  if(strcmp(split[0],"char")==0);

//FOR INTEGER
  
  if(strcmp(split[0],"int")==0);
    

//RESULTANT LINE

    strcpy(result, split[0]);
    strcat(result," ");
    for(i=1;i<Count;i++)
    {
        strcat(result,split[i]);
        if(i==(Count-1))
          strcat(result,";");
        else
          strcat(result,", ");      
    }
    //strcat(result,"\n");
    //printf("%s", result);

    i=0;
    k=0;
    while(result[i]!=' ')
    temp[k++]=result[i++];
    
  temp[k]='\0';
  
  if(!strcmp(temp,"char"))
        type=1;
      else if(!strcmp(temp,"int"))
        type=2;
      else if(!strcmp(temp,"double"))
        type=3;
      else if(!strcmp(temp,"void"))
        type=7;   
  
  while(result[i]!=';')
  {
    k=0;
    i++;
    if(result[i]=='*')
    {
      i++;
      type+=3;
    }
    while(result[i]!=',' && result[i]!=';' && result[i]!=' ')
    {
      temp[k++]=result[i++];
    }
    temp[k]='\0';
    if(strcmp(temp,"\0"))
    {
      if(globalVarFlag==1){
                strcpy(listOfGlobalVars[listOfGlobalVarsSize].varName,temp);
                listOfGlobalVars[listOfGlobalVarsSize++].dataType=type;
      }
      strcpy(listOfLocalVars[listOfLocalVarsSize].varName,temp);
      listOfLocalVars[listOfLocalVarsSize++].dataType=type;
      }
  }
    fprintf(fp,"%s\n",result);
    return;
}


void forLoopFunc(int n,FILE *fp)
{
  int i=0,j=0,k=0;
  char var[100]={},init[100]={},last[100]={},op[2]={},change[100]={},temp[100]={},array[100]={},range[100]={};
  
  while(str[n][i]!='(')
    i++;
  i++;
  
  while(str[n][i]!='=' && str[n][i]!=':')
    var[k++]=str[n][i++];
    
  var[k]='\0';
  
  if(str[n][i]=='=')
  {
    j=i++;
    k=0;
    while(str[n][j]!=' ' && str[n][j]!=';')
      j++;
      
    if(str[n][j]==' ')
    {
      for(i=i;i<j;i++)
        init[k++]=str[n][i];
        
      init[k]='\0';
      i+=4;
      k=0;
      
      while(str[n][i]!=',')
        last[k++]=str[n][i++];
      
      last[k]='\0';
        
      op[0]=str[n][++i];
      op[2]='\0';
      i++;
      k=0;
      
      while(str[n][i]!=')')
        change[k++]=str[n][i++];
        
      change[k]='\0';
      
      strcpy(temp,"for(");
      strcat(temp,var);
      strcat(temp,"=");
      strcat(temp,init);
      strcat(temp,";");
      strcat(temp,var);
      strcat(temp,"<=");
      strcat(temp,last);
      strcat(temp,";");
      strcat(temp,var);
      strcat(temp,op);
      strcat(temp,"=");
      strcat(temp,change);
      strcat(temp,")\0");
      
      //printf("%s ",temp);
    }
    else
    {
      strcpy(temp,str[n]);
    }
    
  }
  else
  {
    i++;
    k=0;
    for(j=i;str[n][j]!=':';j++)
      array[k++]=str[n][j];
      
    array[k]='\0';
    
    j++;
    k=0;
    for(i=j;str[n][i]!=')';i++)
      range[k++]=str[n][i];
      
    range[k]='\0';
    
    strcpy(temp,"for(indexVar=0,");
    strcat(temp,var);
    strcat(temp,"=");
    strcat(temp,array);
    strcat(temp,"[0]");
    strcat(temp,";");
    strcat(temp,"indexVar");
    strcat(temp,"<");
    strcat(temp,range);
    strcat(temp,";");
    strcat(temp,var);
    strcat(temp,"=");
    strcat(temp,array);
    strcat(temp,"[++indexVar]");
    strcat(temp,")\0");
    //printf("%s ",temp);
  }
  fprintf(fp,"%s\n",temp);
}

void funcFunc(int ln,FILE *fp)
{
  int i=0,k=0,j=0,l=0,n1,type,typeList[100],typeListSize=0;
    char str2[MAX]={},temp[10]={},temp2[10]={},funcName[100]={},part1[100]={},part2[100]={},part3[100]={};
  
    listOfLocalVarsSize=0;
    /*
     part1 : int 
             char 
     part2 : func
     part3 : (int a,int b)
     */
    for(i=0;str[ln][i]!=' ';i++){part1[i]=str[ln][i];}
    part1[i]=' ';

    for(++i,j=0;str[ln][i]!='(';i++){funcName[j++]=str[ln][i];}
    funcName[j]='\0';
    i++;

    str2[0]='(';
    j=1; 
  while(str[ln][i]!=')')
  {
      k=0;  
      while(str[ln][i]!=' ')
      {
        temp[k]=str[ln][i];
        i++;
        k++;
      }
      temp[k]=' ';
      temp[++k]='\0';
    
      if(!strcmp(temp,"char "))
        type=1;
      else if(!strcmp(temp,"int "))
        type=2;
      else if(!strcmp(temp,"double "))
        type=3;
      else if(!strcmp(temp,"char* "))
        type=4;
      else if(!strcmp(temp,"int* "))
        type=5;
      else if(!strcmp(temp,"double* "))
        type=6;
      else if(!strcmp(temp,"void "))
        type=7;
    
      ++i;
      while(str[ln][i]!=':' && str[ln][i]!=')')
      {
        for(l=0;str[ln][i]!=',' && str[ln][i]!=':' && str[ln][i]!=')';i++){temp2[l++]=str[ln][i];}
          temp2[l]='\0';
        strcat(str2,temp);
        strcat(str2,temp2);
     
        //list of local variables
        strcpy(listOfLocalVars[listOfLocalVarsSize].varName,temp2);
        listOfLocalVars[listOfLocalVarsSize++].dataType=type;
        typeList[typeListSize++]=type;
        strcat(str2,",");
        if(str[ln][i]==','){++i;}
      } 
      if(str[ln][i]==':'){i++;}
      for(;str[ln][i]==' ';i++);
   
  }
  if(strlen(str2)==1)  //if str2 : (
    str2[1]=')';
 else
  str2[strlen(str2)-1]=')';
  
  strcpy(part2,funcName); //necessary for main function,as it is not present in the funcList
  ///code to change the name of the function(in case of overloading)
  for(j=0;j<funcListSize;j++)
  {
   if(!strcmp(funcList[j].name,funcName) && typeListSize==funcList[j].size)
   {
    for(k=0;k<typeListSize;k++)
    {
     if(funcList[j].paramTypeList[k]!=typeList[k])
       break;
    }
    if(k==typeListSize){
     if(funcList[j].flag==1)
       sprintf(part2,"%s%d_OVERLOADED",funcName,funcList[j].suffix);
    else
      sprintf(part2,"%s",funcName);
    }
    break;
   }
  }
  fprintf(fp,"%s%s%s\n",part1,part2,str2);
  return;
}

void funcCallFunc(int ln,FILE *fp)
{
 int typeList[100],off=0,j,i,typeListSize=0,k,offset=0;
 char *start,tempStr[100]={},part1[100]={},ch,part2[100]={},part3[100]={},*startParanth,funcName[100],initialStr[1000]={};
 strcpy(initialStr,str[ln]);

 while(1)
 {
 typeListSize=0;
 for(i=0;i<funcListSize;i++)
 { 
  if((start=strstr(initialStr+offset,funcList[i].name))!=NULL && start[strlen(funcList[i].name)]=='(')
  {
   ch=initialStr[start-initialStr];
   initialStr[start-initialStr]='\0';
   strcpy(part1,initialStr);
   initialStr[start-initialStr]=ch;

   startParanth=strstr(start,"(");
   
   ch=start[startParanth-start];
   start[startParanth-start]='\0';
   strcpy(funcName,start);
   start[startParanth-start]=ch;

   off=0;
   for(j=1;startParanth[j]!=')';j++)
   {
      if(startParanth[j]==','){tempStr[off]='\0';}
      else{
        tempStr[off]=startParanth[j];
        off++;
        if(startParanth[j+1]==')'){tempStr[off]='\0';typeList[typeListSize++]=getDataType(tempStr);} ///for last variable in parameter list
        continue;
      }
      typeList[typeListSize++]=getDataType(tempStr);
      off=0; 
   }
   break;
  }
 }

 if(i==funcListSize){break;}   //when there doesnt exist anyomore function calls in the line


 for(j=i;j<funcListSize;j++)
 {
  if(!strcmp(funcList[j].name,funcName) && typeListSize==funcList[j].size)
  {
   for(k=0;k<typeListSize;k++)
   {
    if(funcList[j].paramTypeList[k]!=typeList[k])
       break;
   }
   if(k==typeListSize){
    if(funcList[j].flag==1)
      sprintf(part2,"%s%d_OVERLOADED",funcName,funcList[j].suffix);
    else
      sprintf(part2,"%s",funcName);
    }
    break;
   }
  }
 strcpy(part3,startParanth);
 sprintf(initialStr,"%s%s%s",part1,part2,part3);
 offset=startParanth-initialStr;
 }
 fprintf(fp,"%s;\n",initialStr);
 return ;
}

int initialAdditionsFunc(FILE* fp)
{
 int i;
 fprintf(fp,"#include<stdio.h>\n");
 fprintf(fp,"#include<stdlib.h>\n");
 fprintf(fp,"#include<string.h>\n");
 fprintf(fp,"#include<util.h>\n");
 fprintf(fp,"int indexVar=0;\n");
 
 for(i=0;strstr(str[i],"(")==NULL;i++)
   declarationFunc(i,fp);              //for the global declarations
 
 globalVarFlag=0;
 addFuncDeclarations(fp);
 return i;      //i will be where normal conversion of lines starts from
 }

void addFuncDeclarations(FILE *fp)
{
 char ch,tempStr[100],funcName[100],temp2[100],*temp1;
 int i,j,off,type,k,m;
 
 for(i=0;i<noLines;i++)
 {
  for(j=0;str[i][j]!=' ' && str[i][j]!='\0';j++){tempStr[j]=str[i][j];}
  tempStr[j]='\0';
  
  if(!strcmp(tempStr,"char")){type=1;}
  else if(!strcmp(tempStr,"int")){type=2;}
  else if(!strcmp(tempStr,"double")){type=3;}
  else if(!strcmp(tempStr,"char*")){type=4;}
  else if(!strcmp(tempStr,"int*")){type=5;}
  else if(!strcmp(tempStr,"double*")){type=6;}
  else if(!strcmp(tempStr,"void")){type=7;}  //for void
  else{continue;}
  
  if(str[i][strlen(str[i])-1]==')')
  { 
    for(k=j+1,off=0;str[i][k]!='(';k++){funcName[off++]=str[i][k];}
    funcName[off]='\0';
    if(!strcmp(funcName,"main")){continue;}
    funcList[funcListSize].returnType=type;
    for(k=0;k<funcListSize;k++)
    {
     if(!strcmp(funcName,funcList[k].name))
     {
      funcList[k].count++;
      strcpy(funcList[funcListSize].name,funcName);
      funcList[funcListSize].flag=1;
      funcList[funcListSize].suffix=funcList[k].count;
      
      temp1=getTypeList(i);
      if(strlen(temp1)==0){break;}        //if the variable list is empty
      j=0;
      while(1)
      {
      for(ch=temp1[j],m=0;ch!=' ';m++,j++,ch=temp1[j]){temp2[m]=temp1[j];}
      temp2[m]='\0';
      if(!strcmp(temp2,"char")){funcList[funcListSize].paramTypeList[funcList[funcListSize].size]=1;}
      else if(!strcmp(temp2,"int")){funcList[funcListSize].paramTypeList[funcList[funcListSize].size]=2;}      
      else if(!strcmp(temp2,"double")){funcList[funcListSize].paramTypeList[funcList[funcListSize].size]=3;}
      else if(!strcmp(temp2,"char*")){funcList[funcListSize].paramTypeList[funcList[funcListSize].size]=4;}
      else if(!strcmp(temp2,"int*")){funcList[funcListSize].paramTypeList[funcList[funcListSize].size]=5;}
      else if(!strcmp(temp2,"double*")){funcList[funcListSize].paramTypeList[funcList[funcListSize].size]=6;}
      funcList[funcListSize].size++;
      for(;temp1[j]!=',' && temp1[j]!='\0';j++);
      if(temp1[j]=='\0')
        break;
      else
        j++;
      }
      break;
     }
    } 
     
    if(k==funcListSize)
    {  
        funcList[funcListSize].count++;
        strcpy(funcList[funcListSize].name,funcName);
        funcList[funcListSize].flag=0;
        funcList[funcListSize].suffix=0;
        
        temp1=getTypeList(i);
        if(strlen(temp1)==0){break;}        //if the variable list is empty
        j=0;
        while(1)
        {
        for(ch=temp1[j],m=0;ch!=' ';j++,m++,ch=temp1[j]){temp2[m]=temp1[j];}
        temp2[m]='\0';
        if(!strcmp(temp2,"char")){funcList[funcListSize].paramTypeList[funcList[funcListSize].size]=1;}
        else if(!strcmp(temp2,"int")){funcList[funcListSize].paramTypeList[funcList[funcListSize].size]=2;}      
        else if(!strcmp(temp2,"double")){funcList[funcListSize].paramTypeList[funcList[funcListSize].size]=3;}
        else if(!strcmp(temp2,"char*")){funcList[funcListSize].paramTypeList[funcList[funcListSize].size]=4;}
        else if(!strcmp(temp2,"int*")){funcList[funcListSize].paramTypeList[funcList[funcListSize].size]=5;}
        else if(!strcmp(temp2,"double*")){funcList[funcListSize].paramTypeList[funcList[funcListSize].size]=6;}
        funcList[funcListSize].size++;
        for(;temp1[j]!=',' && temp1[j]!='\0';j++);
        if(temp1[j]=='\0')
          break;
        else
         j++; 
        }
    }
     funcListSize++;
  } 
 }
 for(i=0;i<funcListSize;i++)
 {
  if(funcList[i].flag==0)
  {
   fprintf(fp,"%s %s(",getStr(funcList[i].returnType),funcList[i].name);
   for(j=0;j<(funcList[i].size)-1;j++)
    fprintf(fp,"%s,",getStr(funcList[i].paramTypeList[j]));
   fprintf(fp,"%s);\n",getStr(funcList[i].paramTypeList[j]));
   }
   else
   {
   fprintf(fp,"%s %s%d_OVERLOADED(",getStr(funcList[i].returnType),funcList[i].name,funcList[i].suffix);
   for(j=0;j<(funcList[i].size)-1;j++)
     fprintf(fp,"%s,",getStr(funcList[i].paramTypeList[j]));
   fprintf(fp,"%s);\n",getStr(funcList[i].paramTypeList[j]));
   }
  }
  
 return;
}

char* getStr(int i)
{
 char temp[100]={};
  if(i==1)
    strcpy(temp,"char");
  else if(i==2)
    strcpy(temp,"int");
  else if(i==3)
    strcpy(temp,"double");
  else if(i==4)
    strcpy(temp,"char*");
  else if(i==5)
    strcpy(temp,"int*");
  else if(i==6)
    strcpy(temp,"double*");
  else if(i==0)
    strcpy(temp,"\0");            //necessary while printing function declarations in the beginning
  else if(i==7)
    strcpy(temp,"void");
  return temp;   
}


char* getTypeList(int ln)
{
 int i=0,k=0,j=0,off=0,l=0,n1;
  char str2[MAX]={},temp[10]={},temp2[10]={};
  
  for(j=0,i=0;str[ln][i]!='(';j++,i++){
   str2[j]=str[ln][i];}
   str2[j]='(';
   i++;
   j++;
   off=j;
 while(str[ln][i]!=')')
 {
     k=0;  
     while(str[ln][i]!=' ')
     {
     temp[k]=str[ln][i];
     i++;
     k++;
     }
    temp[k]=' ';
    temp[++k]='\0';
    ++i;
    while(str[ln][i]!=':' && str[ln][i]!=')')
    {
     for(l=0;str[ln][i]!=',' && str[ln][i]!=':' && str[ln][i]!=')';i++){temp2[l++]=str[ln][i];}
     temp2[l]='\0';
     if(temp2[0]=='*'){
     strcat(str2,temp);
     str2[strlen(str2)-1]='*';
     strcat(str2," ");
     strcat(str2,temp2+1);
     strcat(str2,",");
     }
     else
     {
     strcat(str2,temp);
     strcat(str2,temp2);
     strcat(str2,",");     
     }
     if(str[ln][i]==','){++i;}
    }
    if(str[ln][i]==':'){i++;}
    for(;str[ln][i]==' ';i++);
   
 }
str2[strlen(str2)-1]='\0';
return str2+off; 
}

int funcNumCheck(char *tempStr)
{ 
 char *i;
/*
5-->directfunc(one which adds ;)
1-->forFunc
2-->printFunc
3-->funcFunc
4-->declFunc
0-->directFun2(one which doesn't add ;)
8-->functionCallFunc
*/
    if(strstr(tempStr,"for(")){return 1;}
    if(strstr(tempStr,"print(")){return 2;}
    if(strstr(tempStr,"int ") || strstr(tempStr,"char ") || strstr(tempStr,"double ") || strstr(tempStr,"void ") || strstr(tempStr,"bigInt "))
    {
      if(strstr(tempStr,"("))
        return 3;
      else
        return 4;
    }
    if(strstr(tempStr,"if(") || strstr(tempStr,"else(") || strstr(tempStr,"{") || strstr(tempStr,"}")){
      return 0;}
    for(i=strstr(tempStr,"(");i!=NULL && tempStr[i-tempStr-1]!='(' && tempStr[i-tempStr-1]!='=' && tempStr[i-tempStr-1]!='+' && tempStr[i-tempStr-1]!='*'&& tempStr[i-tempStr-1]!='/'&& tempStr[i-tempStr-1]!='-';)
      return 8;
    return 5;

} 
void takeCareOfLine(int i, FILE *f)
{
  int funcnum=funcNumCheck(str[i]);
  //printf("%d %d\n",i+1,funcnum);  
  switch(funcnum)
  {
    case 0: directConvFunc(i,f);
      break;
    case 1: forLoopFunc(i, f);
      break;
    case 2: printFunc(i, f);
      break;
    case 3: funcFunc(i,f);
      break;
    case 4: declarationFunc(i,f);
      break;  
    case 5: directConvFunc2(i,f);
      break;
    case 8: funcCallFunc(i, f);
      break;
  }
}

void removeExtraSpaces(char *strng)
{
 int i,j;
 for(i=strlen(strng)-1;strng[i]==' ';i--)
    strng[i]='\0';
 for(i=0;strng[i]==' ' || strng[i]=='\t';i++);
 for(j=i;strng[j]!='\0';j++)
    strng[j-i]=strng[j];
 strng[j-i]=strng[j];
}
