#include<stdlib.h>
#include<unistd.h>
#include<stdio.h>

int main(int argc, char** argv)
{
  char buffer;
  while((buffer=getchar())!=EOF){
    putchar((char)buffer);
  }
  return 0;
}
