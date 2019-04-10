#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<pthread.h>
#include<sys/types.h>


pthread_mutex_t l,l1;//l is for readers count ,l1 for writer 
int value = 0,reader_count = 0;
pthread_t reader[5],writer[5];
int i,b,r,w; 

void *for_reader(void *arg)
{
  int *s=(int *)arg;
  
  pthread_mutex_lock(&l);
  reader_count = reader_count + 1;
  if(reader_count==1)
   pthread_mutex_lock(&l1);
  pthread_mutex_unlock(&l);
  
  {
  printf("Data read by the reader %d is %d and the number of readers are %d when reader is reading\n\n",*s,value,reader_count);
//  	if(reader_count==1)
//  	{
//  	printf("The reader_count is %d\n",reader_count);
//  	printf("The reader %d with thread id %d is reading\n",*s,&reader[*s]);
//    }
//  if(reader_count>1)
//  { for(i=0;i<reader_count-1;i++)
//     {
//    printf("The reader_count is %d\n",reader_count);	
//  	printf("The reader %d with thread id is %d is reading\n",*s,&reader[*s]);
//     }
//  }

  } 
  
  pthread_mutex_lock(&l);
  reader_count = reader_count - 1;
  if(reader_count==0)
   pthread_mutex_unlock(&l1);
  pthread_mutex_unlock(&l);
}

void *for_writer(void *arg)
{
  int *m=(int *)arg;

  while(reader_count!=0);
  pthread_mutex_lock(&l1);
 
  value++;
  {
  printf("Data writen by the writer %d is %d\n",*m,value);
  printf("The number of readers are %d when writer is writing\n",reader_count);
  }
  pthread_mutex_unlock(&l1);
  
}

int main()
{
  //int i,b,r,w; 
  //pthread_t reader[5],writer[5];
  pthread_mutex_init(&l,NULL);
  pthread_mutex_init(&l1,NULL);
  printf("************************The Reader-Writer Program***************************\n");
  printf("Enter the number of the reader threads you want to create:\n");
  scanf("%d",&r);
  printf("Enter the number of the writer threads you want to create:\n");
  scanf("%d",&w);
  
  for(i=0;i<r;i++)
  {
    pthread_create(&reader[i],NULL,for_reader,&i);
  }
  
  for(i=0;i<w;i++)
  {
    pthread_create(&writer[i],NULL,for_writer,&i);
  }
  for(i=0;i<r;i++)
  {
    pthread_join(reader[i],NULL);
  }
  for(i=0;i<w;i++)
  {
    pthread_join(writer[i],NULL);
  }
printf("************************Program Ends***************************\n");
printf("************************Made By:Sushmita Sah*******************\n");
printf("************************Roll no:05*****************************\n");
printf("************************Section:K17AP**************************\n");
  return 0;
}

