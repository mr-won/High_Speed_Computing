#include <stdio.h>
#include "mpi.h"

main(int argc, char* argv[])
{
   int pid, np, i, n, prod=1, tag=0;
   MPI_Status status;

   MPI_Init(&argc, &argv);

   MPI_Comm_size(MPI_COMM_WORLD, &np);
   MPI_Comm_rank(MPI_COMM_WORLD, &pid);
    
   pid += 1;
   MPI_Reduce(&pid, &prod, 1, MPI_INT, MPI_PROD, 0, MPI_COMM_WORLD);
   
   if(pid-1==0) 
      printf("%d\n", prod);

   MPI_Finalize();
}
