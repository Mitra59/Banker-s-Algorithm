#include<stdio.h>
#include<pthread.h>
int allo[10];
int max[10];
int need[10];
int flag;
int fl;
int i,j,k,p,b,n,r,g,cnt=0,id,newr;
int avail[10],seq[10];
void *thread1();
void *thread2();
pthread_mutex_t l,ll;
int main(){
	pthread_t t1;
	pthread_mutex_init(&l,NULL);
	pthread_mutex_init(&ll,NULL);	
	printf("Enter number of processes");
	scanf("%d",&n);
	printf("Enter number of resources");
	scanf("%d",&r);
	for(i=0;i<n;i++){
		printf("Enter details of p%d",i);
		printf("\nenter allocation\t");
		for(j=0;j<r;j++)
		scanf("%d",&allo[j]);
		printf("\nEnter max\t\t");
		for(j=0;j<r;j++)
			scanf("%d",&max[j]);
		flag=0;
	}
	printf("\nEnter Available resources\t");
	for(i=0;i<r;i++)
		scanf("%d",&avail[i]);
	pthread_create(&t1,NULL,thread1,NULL);
	pthread_join(t1,NULL);
	printf("\nSystem is in safe state");
	printf("\nThe safe seq is -(");
	for(i=0;i<fl;i++)
		printf("p%d",seq[i]);
	printf(")");
}
void *thread1(){
	pthread_mutex_lock(&l);
	pthread_t t2;
	printf("\nEnter new Request details");
	printf("\nENter pid\t");
	scanf("%d",&id);
	printf("\nEnter request for resource\t");
	for(i=0;i<r;i++){
		scanf("%d",&newr);
		allo[i]+=newr;
		avail[i]=avail[i]-newr;
	}
	for(i=0;i<n;i++){
		for(j=0;j<r;j++){
				need[j]=max[i]-allo[j];
				if(need[j]<n)
					need[j]=0;
			}
		}
	cnt=0;
	fl=0;
	while(cnt!=n){
		g=0;
		for(j=0;j<n;j++){
			if(flag=0){
				b=0;
				for(p=0;p<r;p++){
					if(avail[p]>=need[p])
						b=b+1;
					else
						b=b-1;
					if(b==r){
						printf("\np%d is visited");
						seq[fl++]=j;
						flag=1;
						for(k=0;k<r;k++)
							avail[k]=avail[k]+allo[k];
						cnt=cnt+1;
						printf("(");
						for(k=0;k<r;k++)
							printf("%3d",avail[k]);
						printf(")");
						g=1;
					}
				}
			}
		}
		if(g==0){
			printf("\request not granted-Deadlock occured");
			printf("\nSysten is in unsafe state");
			pthread_create(&t2,NULL,thread2,NULL);
			pthread_join(t2,NULL);
			pthread_mutex_lock(&ll);
		}
	}

}
void *thread2(){
	pthread_mutex_lock(&ll);
	printf("\nProcess\t\tAllocation\t\tMax\t\tNeed\n");
	for(i=0;i<n;i++){
		printf("p%d\t",i);
		for(j=0;j<r;j++)
			printf("%6d",allo[j]);
		for(j=0;j<r;j++)
			printf("%6d",max[j]);
		for(j=0;j<r;j++)
			printf("%6d",need[j]);
		printf("\n");
		}
			pthread_mutex_unlock(&ll);
				pthread_mutex_lock(&l);

}
