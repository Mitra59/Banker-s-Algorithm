#include<stdio.h>
int main()
{
int a[10]={86,1470,913,1774,948,1509,1022,1750,130};
int p=143,seek=0,i,n=9,t[9],j,temp;
float avg;
printf("Queue is 86,1470,913,1774,948,1509,1022,1750,130\n");
printf("Initial position of Head is=143\n");
 for(i=0;i<n;i++)
   t[i]=abs(p-a[i]);
  for(i=0;i<n;i++)
     {
 for(j=i+1;j<n;j++)
   {
     if(t[i]>t[j])
   {
        temp=t[i];
     t[i]=t[j];
      t[j]=temp;
      temp=a[i];
      a[i]=a[j];
       a[j]=temp;
     }
    }
    }
     for(i=0;i<n-1;i++)
    {
  seek=seek+abs(p-a[i]);
    p=a[i];
   }
  printf("\nTotal Seek Time is=%d\t",seek);
  avg=seek/(float)n;
   printf("\nAverage Seek Time is=%f\t",avg);
 getch();
}

