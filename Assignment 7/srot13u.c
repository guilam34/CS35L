#include <stdio.h>
#include<stdbool.h>
#include<sys/types.h>
#include <sys/stat.h>
#include<unistd.h>
#include <stdlib.h>
#include <ctype.h>
int cmpCt=0;
int rot13cmp(void const* aa, void const* bb){
  int i=0;
  cmpCt=cmpCt+1;
  int cmp=0;
  char const* a=*(char const **)aa;
  char const* b=*(char const **)bb;
  if(a[0]=='\n' && b[0]=='\n')
    {
      return 0;
    }
  do{
    if(a[i]=='\n' && b[i]=='\n')
      {cmp= 0;
	break;}
    else if(a[i]=='\n')
      {cmp= -1;
	break;}
    else if(b[i]=='\n')
      {cmp= 1;
	break;}
	
    else if(isupper(a[i]) && islower(b[i]))
      {cmp= -1;
	break;}
    else if(islower(a[i]) && isupper(b[i]))
      {cmp= 1;
	break;}

    else if(a[i]=='\0' &&b[i]!='\0')
      {cmp= -1;
	break;}
    else if(a[i]!='\0' &&b[i]=='\0')
      {cmp= 1;
	break;}

    else if(a[i]>='a' && a[i]<='m' && b[i]>='m' && b[i] <='z')
      {cmp= 1;
	break;}
    else if(a[i]>='m' && a[i]<='z' && b[i]>='a' && b[i]<='m')
      {cmp= -1;
	break;}
    else if(a[i]>='a' && a[i]<='m' && b[i] >='a' && b[i] <='m')
      {
	if(a[i]>b[i])
	  {
	    cmp=1;
	    break;
	  }
	else{
	  cmp=-1;
	  break;
	}
      }
    else if(a[i]>='m' && a[i]<='z' && b[i] >='m' && b[i] <='z')
      {
	if(a[i]>b[i])
	  {
	    cmp=1;
	    break;
	  }
	else{
	  cmp=-1;
	  break;
	}
      }

    else if(a[i]>='A' && a[i]<='M' && b[i]>='M' && b[i] <='Z')
      {cmp= 1;
	break;}
    else if(a[i]>='M' && a[i]<='Z' && b[i]>='A' && b[i]<='M')
      {cmp= -1;
	break;}
    else if(a[i]>='A' && a[i]<='M' && b[i] >='A' && b[i] <='M')
      {
	if(a[i]>b[i])
	  {
	    cmp=1;
	    break;
	  }
	else{
	  cmp=-1;
	  break;
	}
      }
    else if(a[i]>='M' && a[i]<='Z' && b[i] >='M' && b[i] <='Z')
      {
	if(a[i]>b[i])
	  {
	    cmp=1;
	    break;
	  }
	else{
	  cmp=-1;
	  break;
	}
      }

    else{
      i=i+1;
    }
  }while(a[i]!='\n'&&b[i]!='\n');
  return cmp;
}

int main(void){
  int maxSize=1000;
  int wMax=maxSize;
  int cMax=maxSize;
  char *cArray;
  int cIndex=0;
  char **wArray;
  int wIndex=0;
  char buffer;
  bool change=true;
  struct stat fileStat;
  fstat(0,&fileStat);
  if(S_ISREG(fileStat.st_mode))
    {
        cArray=(char*)malloc(fileStat.st_size);
        wArray=(char**)malloc(fileStat.st_size);
	wArray[0] = cArray;
    }
  else{
      cArray=(char*)malloc(sizeof(char)*maxSize);
      wArray=(char**)malloc(sizeof(char*)*maxSize);
      wArray[0] = cArray;
  }
  if(cArray==NULL)
    {
      fprintf(stderr,"malloc failed to allocate memory for char* cArray");
      exit(1);
    }
  if(wArray==NULL)
    {
      fprintf(stderr,"malloc failed to allocate memory for char* wArray");
      exit(1);
    }
  
  while(read(0,&buffer,1)>0)
    {
      cArray[cIndex]=(char)buffer;
      cIndex=cIndex+1;
      if(cIndex>=cMax)
	{
	  cArray=(char*)realloc(cArray,(cMax+1)*sizeof(char));
	  cMax=cMax+1;
	  if(cArray==NULL)
	    {
	      fprintf(stderr,"realloc failed to reallocate memory for char* cArray");
	      exit(1);
	    }
	}
      if(cArray[cIndex-1]=='\n')
	{
	  wIndex=wIndex+1;
	  wArray[wIndex]=cArray+cIndex;
	  if(wIndex>=wMax)
	    {
	      wArray=(char**)realloc(wArray, (wMax+1)*sizeof(char));
	      wMax=wMax+1;
	      if(wArray==NULL)
		{
		  fprintf(stderr,"realloc failed to reallocate memory for char* wArray");
		  exit(1);
		  
		}
	    }
	}
    }
  wIndex=wIndex+1;
  if(cArray[cIndex-1]!='\n')
    {
      if(cIndex-1==cMax)
	{
	  cArray=(char*)realloc(cArray,(cMax+1)*sizeof(char));
	  cMax=cMax+1;
	}
      cArray[cIndex]='\n';
    }
  qsort(wArray,wIndex,sizeof(char*),rot13cmp);
  int x;
  for(x=0;x<wIndex;x++)
    {
      buffer=*(wArray[x]);
      while(buffer!=EOF&&buffer!='\n')
	{
	  write(1,&buffer,1);
	  buffer=*(++wArray[x]);
	}
      buffer='\n';
      write(1,&buffer,1);
    }
  fprintf(stderr,"Number of comparisons: %d\n",cmpCt);
  free(wArray);
  free(cArray);
  return 0;
}
