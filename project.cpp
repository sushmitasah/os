#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<pthread.h>
#include<sys/types.h>


pthread_mutex_t l,l1;//l is for readers count ,l1 for writer 
int value = 0,reader_count = 0;

void *for_reader(void *arg)
{
  int *s=(int *)arg;
  
  sleep(1);
  pthread_mutex_lock(&l);
  reader_count = reader_count + 1;
  if(reader_count==1)
   pthread_mutex_lock(&l1);
  pthread_mutex_unlock(&l);
  printf("Data read by the reader %d is %d and the number of readers are %d when reader is reading\n",*s,value,reader_count);
  //sleep(1);
  pthread_mutex_lock(&l);
  reader_count = reader_count - 1;
  if(reader_count==0)
   pthread_mutex_unlock(&l1);
  pthread_mutex_unlock(&l);
}

void *for_writer(void *arg)
{
  int *m=(int *)arg;

  //pthread_mutex_lock(&l);
  pthread_mutex_lock(&l1);
 
  value++;
  printf("Data writen by the writer%d is %d\n",*m,value);
  printf("The number of readers are %d when writer is writing\n",reader_count);
  
  pthread_mutex_unlock(&l1);
  //pthread_mutex_unlock(&l);
}

int main()
{
  int i,b; 
  pthread_t reader[5],writer[5];
  pthread_mutex_init(&l,NULL);
  pthread_mutex_init(&l1,NULL);
  for(i=0;i<=4;i++)
  {
    pthread_create(&writer[i],NULL,for_writer,&i);
    pthread_create(&reader[i],NULL,for_reader,&i);
  }
  for(i=0;i<=4;i++)
  {
    pthread_join(writer[i],NULL);
    pthread_join(reader[i],NULL);
  }
  return 0;
}
