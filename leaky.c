#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>


void main(){
	int bucketSize,outflowRate;
	int a[10],n;
	printf("Enter bucket size: ");
	scanf("%d",&bucketSize);
	
	printf("Enter the outflow rate: ");
	scanf("%d",&outflowRate);
	
	printf("Enter the no of packets: ");
	scanf("%d",&n);
	
	for(int i=0;i<n;i++){
		printf("Enter size of packet %d: ",i);
		scanf("%d",&a[i]);
	}
	
	printf("\n============================\n");
	printf("======BUCKET SIZE :%d======\n======OUTFLOW RATE :%d======\n",bucketSize,outflowRate);
	printf("\n============================\n");
	
	int currSize=0;
	for(int i=0;i<n;i++){
		if(a[i]>bucketSize){
			printf("Large size than that of bucket. Packet %d is lost\n",i);
		}else{
			if(a[i]+currSize>bucketSize){
				printf("Bucket overflow\n");
			}else{
				currSize+=a[i];
				printf("Packet %d added to bucket\n",i);
			}
		}
		
		if(currSize>0){
			currSize-=outflowRate;
			if(currSize<0){
				currSize=0;
			}printf("Leaking the bucket....\nBucket has size now: %d\n",currSize);
		}sleep(1);
	}
}

