#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include "smemory.h"
//client.c
main(int argc, char*argv[])
{
   int shm_id;
   void *shm_addr;
   SHM *shm;
   int key;

   int data;

   if (argc != 3) {
      printf("usage: %s key data\n", argv[0]);
      exit(1);
   }

   key = atoi(argv[1]);
   data = atoi(argv[2]);

   shm_id = shmget(key, sizeof(int), IPC_CREAT|0666);
   shm_addr = (void *)shmat(shm_id, 0, 0);

   shm = (SHM *) shm_addr;

   if(data >= 0)
   {
      shm->sum = data;
      shm->s = 1;
   }
   else
      shm->s = data;

   exit(0);
}
//-------------------------------------------------------------
//server.c
main(int argc, char*argv[])
{
   int shm_id;
   void *shm_addr;
   SHM *shm;
   int key;

   int sum = 0;

   if (argc != 2) {
      printf("usage: %s key\n", argv[0]);
      exit(1);
   }

   key = atoi(argv[1]);

   shm_id = shmget(key, sizeof(int), IPC_CREAT|0666);
   shm_addr = (void *)shmat(shm_id, 0, 0);
   shm = (SHM *) shm_addr;

   shm->s = 0;
   while(1)
   {
      while(!shm->s){}

      if(shm->s<0)
         break;

      shm->s=0;
      sum += shm->sum;
      printf("sum = %d\n", sum);
   }

   shmdt((void *)shm_addr);
   shmctl(shm_id, IPC_RMID, 0);

   exit(0);
}