/*  ./callback.c  */

/*
 * Copyright (c) 2011-2012 by
 *   Claudio Zanellato <cipotano at gmail.com>
 *   Eduardo Grosclaude <eduardo.grosclaude at gmail.com>
 *
 *   This program is free software; you can redistribute it and/or modify
 *   it under the terms of the GNU General Public License as published by
 *   the Free Software Foundation; either version 2 of the License, or
 *   (at your option) any later version.
 *
 */

#include "shim.h"


#define MAXRANK 64
#define MAXFUNCTS 64
static long sendbytes[MAXRANK][MAXRANK][MAXFUNCTS];
static long recvbytes[MAXRANK][MAXRANK][MAXFUNCTS];
/*============================== INFORME FINAL ================================== */
void tor_INFORME() 
{
	int rank,rankto,funct;
	for(rank=0; rank < MAXRANK; rank++) 
		for(funct=0; funct < MAXFUNCTS; funct++) 
			for(rankto=0; rankto < MAXRANK; rankto++) {
				if(sendbytes[rank][rankto][funct])
					printf("TOR send %d to %d mpi %s bytes %ld\n",
						rank, rankto,
						FUNCName[funct],
						sendbytes[rank][rankto][funct]);
 				//if(recvbytes[rank][rankto][funct])
				//	printf("TOR recv %d fr %d mpi %s bytes %ld\n",
				//		rank, rankto,
				//		FUNCName[funct],
				//		recvbytes[rank][rankto][funct]);
			}


	return;
}

/*============================== INIT ======================================= */

void tor_MPI_Init_pre()
{
//printf("tor_MPI_Init_pre\n");
	return;
}


void tor_MPI_Init_pos()
{
//printf("tor_MPI_Init_pos\n");
	tor_setclock();
	return;
}


/*============================== FINALIZE ======================================= */


void tor_MPI_Finalize_pre()
{
//printf("tor_MPI_Finalize_pre\n");
	return;
}

void tor_MPI_Finalize_pos()
{
//printf("tor_MPI_Finalize_pos\n");
//	tor_INFORME();
}

/*============================== BCAST ======================================= */

void tor_MPI_Bcast_pre(void *buffer, int count, MPI_Datatype datatype, int root, MPI_Comm comm,
			__SHIM__CALLER caller)
{
	int dest;
	int datasize, rank, size;

	MPI_Type_size(datatype, &datasize); //printf("DATASIZE %d\n",datasize);
	MPI_Comm_rank(comm, &rank); //printf("RANK %d\n",rank);
	MPI_Comm_size(comm, &size); //printf("SIZE %d\n",size);

	if(rank == root) {
		for(dest=0; dest < size; dest++)
			if(rank != dest)
				sendbytes[rank][dest][Bcast] += count * datasize;
	} else // does root also receive its own buffer? 
		recvbytes[rank][root][Bcast] += count * datasize;
//	for(dest=0; dest < size; dest++)
		dest  = -1;
		printf("%lu tor_MPI_Bcast_pre caller=%u rank=%d dest=%d count=%d size=%d\n",tor_getelapsed(),caller,rank,dest,count,datasize);
	return;
}


void tor_MPI_Bcast_pos(void *buffer, int count, MPI_Datatype datatype, int root, MPI_Comm comm,
			__SHIM__CALLER caller,int err)
{
	int dest;
	int datasize, rank, size;

	MPI_Type_size(datatype, &datasize); //printf("DATASIZE %d\n",datasize);
	MPI_Comm_rank(comm, &rank); //printf("RANK %d\n",rank);
	MPI_Comm_size(comm, &size); //printf("SIZE %d\n",size);

//	for(dest=0; dest < size; dest++)
		dest  = -1;
		printf("%lu tor_MPI_Bcast_pos caller=%u rank=%d dest=%d count=%d size=%d\n",tor_getelapsed(),caller,rank,dest,count,datasize);
	return;
}


/*============================== BARRIER ==================================== */

void tor_MPI_Barrier_pre(MPI_Comm comm, __SHIM__CALLER caller)
{
	int rank, size; 

	MPI_Comm_rank(comm, &rank); 

	printf("%lu tor_MPI_Barrier_pre caller=%u rank=%d\n", tor_getelapsed(), caller, rank);
        return;
}

void tor_MPI_Barrier_pos(MPI_Comm comm, __SHIM__CALLER caller, int err)
{
	int rank, size; 

	MPI_Comm_rank(comm, &rank); 

	printf("%lu tor_MPI_Barrier_pos caller=%u rank=%d\n", tor_getelapsed(), caller, rank);
        return;
}


/*============================== SEND ======================================= */

void tor_MPI_Send_pre (char *buf, int count, MPI_Datatype datatype ,int dest, int tag, MPI_Comm comm,
			__SHIM__CALLER caller)
{
	int rank, size; 
	int datasize;

        MPI_Type_size(datatype, &datasize); 
	MPI_Comm_rank(comm, &rank); 
	MPI_Comm_size(comm, &size); 

        sendbytes[rank][dest][Send] += count * datasize;
	printf("%lu tor_MPI_Send_pre caller=%u rank=%d dest=%d count=%d size=%d\n", tor_getelapsed(), caller, rank, dest, count, datasize);
        return;
}



void tor_MPI_Send_pos (char *buf, int count, MPI_Datatype datatype ,int dest, int tag, MPI_Comm comm,
			__SHIM__CALLER caller, int err)
{
	int rank, size; 
	int datasize;

        MPI_Type_size(datatype, &datasize); 
	MPI_Comm_rank(comm, &rank); 
	MPI_Comm_size(comm, &size); 

	printf("%lu tor_MPI_Send_pos caller=%u rank=%d dest=%d count=%d size=%d\n", tor_getelapsed(), caller, rank, dest, count, datasize);
        return;
}


/*============================== RECV ======================================= */

void tor_MPI_Recv_pre (char *buf, int count, MPI_Datatype datatype, int source, int tag, MPI_Comm comm, MPI_Status *status, 
			__SHIM__CALLER caller)
{
/*
int MPI_Status_c2f(MPI_Status *c_status, MPI_Fint *f_status)
int MPI_Status_f2c(MPI_Fint *f_status, MPI_Status *c_status)
 	MPI_Status c_status;
*/
//printf("tor_MPI_Recv_pre  count=%d  source=%d tag=%d \n",   *count, *source, *tag );
	int rank, size; 
	int datasize;
	int dest;

	dest = source;

        MPI_Type_size(datatype, &datasize); 
	MPI_Comm_rank(comm, &rank); 
	MPI_Comm_size(comm, &size); 

        recvbytes[rank][source][Recv] += count * datasize;
	printf("%lu tor_MPI_Recv_pre caller=%u rank=%d dest=%d count=%d size=%d\n", tor_getelapsed(), caller, rank, dest, count, datasize);
        return;
}


void tor_MPI_Recv_pos (char *buf, int count, MPI_Datatype datatype, int source, int tag, MPI_Comm comm, MPI_Status *status, 
			__SHIM__CALLER caller, int err)
{
//printf("tor_MPI_Recv_pos Buf=%s count=%d dest=%d tag=%d  \n", buf,  *count, *source, *tag);
	int rank, size; 
	int datasize;
	int dest;

	dest = source;
        MPI_Type_size(datatype, &datasize); 
	MPI_Comm_rank(comm, &rank); 
	MPI_Comm_size(comm, &size); 
	printf("%lu tor_MPI_Recv_pos caller=%u rank=%d dest=%d count=%d size=%d\n", tor_getelapsed(), caller, rank, dest, count, datasize);
        return;
}



/*============================== ISEND ======================================= */

void  tor_MPI_Isend_pre(void *buf, int count, MPI_Datatype datatype, int dest, int tag, MPI_Comm comm, MPI_Request *request,
			__SHIM__CALLER caller)
{
	int rank, size; 
	int datasize;

        MPI_Type_size(datatype, &datasize); 
	MPI_Comm_rank(comm, &rank); 
	MPI_Comm_size(comm, &size); 

        sendbytes[rank][dest][Send] += count * datasize;
	printf("%lu tor_MPI_Isend_pre caller=%u rank=%d dest=%d count=%d size=%d\n", tor_getelapsed(),caller, rank, dest, count, datasize);
        return;
}


void  tor_MPI_Isend_pos(void *buf, int count, MPI_Datatype datatype, int dest, int tag, MPI_Comm comm, MPI_Request *request,
			__SHIM__CALLER caller, int err)
{
        int rank, size;
        int datasize;

        MPI_Type_size(datatype, &datasize);
        MPI_Comm_rank(comm, &rank);
        MPI_Comm_size(comm, &size);

        printf("%lu tor_MPI_Isend_pos caller=%u rank=%d dest=%d count=%d size=%d\n", tor_getelapsed(),caller, rank, dest, count, datasize);

        return;
}


/*============================== WAIT ======================================= */
// Falta deducir rank, dest, etc. a partir de status (donde han sido puestos por una primitiva asincronica)
void  tor_MPI_Wait_pre(MPI_Request *request, MPI_Status *status,
			__SHIM__CALLER caller)
{
	int rank; 
//        MPI_Comm_rank(comm, &rank);

	printf("%lu tor_MPI_Wait_pre caller=%u rank=%d dest=%d count=%d size=%d\n", tor_getelapsed(),caller, -1, -1, -1, -1);
        return;
}


void  tor_MPI_Wait_pos(MPI_Request *request, MPI_Status *status,
			__SHIM__CALLER caller, int err)
{
        int rank;
 //       MPI_Comm_rank(comm, &rank);

	printf("%lu tor_MPI_Wait_pos caller=%u rank=%d dest=%d count=%d size=%d\n", tor_getelapsed(),caller, -1, -1, -1, -1);
        return;
}

/*============================== WAITALL ======================================= */
// Falta deducir rank, dest, etc. a partir de status (donde han sido puestos por una primitiva asincronica)
void  tor_MPI_Waitall_pre(int count,void *request, void *status,
			__SHIM__CALLER caller)
{
	int rank; 
//        MPI_Comm_rank(comm, &rank);

	printf("%lu tor_MPI_Waitall_pre caller=%u rank=%d dest=%d count=%d size=%d\n", tor_getelapsed(),caller, -1, -1, -1, -1);
        return;
}


void  tor_MPI_Waitall_pos(int count, void *request, void *status,
			__SHIM__CALLER caller, int err)
{
        int rank;
 //       MPI_Comm_rank(comm, &rank);

	printf("%lu tor_MPI_Waitall_pos caller=%u rank=%d dest=%d count=%d size=%d\n", tor_getelapsed(),caller, -1, -1, -1, -1);
        return;
}

/*============================== IRECV ======================================= */

void  tor_MPI_Irecv_pre(void *buf, int count, MPI_Datatype datatype, int source, int tag, MPI_Comm comm, MPI_Request *request,
			__SHIM__CALLER caller)
{
	int rank, size; 
	int datasize;
	int dest;

	dest = source;

//printf("tor_MPI_Irecv_pre\n");
        MPI_Type_size(datatype, &datasize); 
	MPI_Comm_rank(comm, &rank); 
	MPI_Comm_size(comm, &size); 
        recvbytes[rank][source][Irecv] += count * datasize;
        printf("%lu tor_MPI_Irecv_pre caller=%u rank=%d dest=%d count=%d size=%d\n", tor_getelapsed(),caller, rank, dest, count, datasize);
        return;
}


void  tor_MPI_Irecv_pos(void *buf, int count, MPI_Datatype datatype, int source, int tag, MPI_Comm comm, MPI_Request *request,
			__SHIM__CALLER caller, int err)
{
//printf("tor_MPI_Irecv_pos\n");
	int rank, size; 
	int datasize;
	int dest;

	dest = source;

        MPI_Type_size(datatype, &datasize); 
	MPI_Comm_rank(comm, &rank); 
	MPI_Comm_size(comm, &size); 
        printf("%lu tor_MPI_Irecv_pos caller=%u rank=%d dest=%d count=%d size=%d\n", tor_getelapsed(),caller, rank, dest, count, datasize);
        return;
}



/*============================== REDUCE ======================================= */


void  tor_MPI_Reduce_pre(void *sendbuf, void *recvbuf, int count, MPI_Datatype datatype, MPI_Op op, int root, MPI_Comm comm, 
				__SHIM__CALLER caller)
{
	int rank, size, rankfrom; 
	int datasize;

        MPI_Type_size(datatype, &datasize); 
	MPI_Comm_rank(comm, &rank); 
	MPI_Comm_size(comm, &size); 
	if(rank == root) {
		for(rankfrom=0; rankfrom < size; rankfrom++)
			if(rank != rankfrom)
				recvbytes[rank][rankfrom][Reduce] += count * datasize;
	} else {
		sendbytes[rank][root][Reduce] += count * datasize;
	}
	printf("%lu tor_MPI_Reduce_pre caller=%u rank=%d dest=%d count=%d size=%d\n",tor_getelapsed(), caller,rank,root,count,datasize);
        return;
}

void  tor_MPI_Reduce_pos(void *sendbuf, void *recvbuf, int count, MPI_Datatype datatype, MPI_Op op, int root, MPI_Comm comm,
			__SHIM__CALLER caller, int err)
{
        int rank, size, rankfrom;
        int datasize;

        MPI_Type_size(datatype, &datasize);
        MPI_Comm_rank(comm, &rank);
        MPI_Comm_size(comm, &size);
        printf("%lu tor_MPI_Reduce_pos caller=%u rank=%d dest=%d count=%d size=%d\n",tor_getelapsed(), caller,rank,root,count,datasize);
 
        return;
}



/*============================== ALLREDUCE ======================================= */

void tor_MPI_Allreduce_pre(void *sendbuf, void *recvbuf, int count, MPI_Datatype datatype, MPI_Op op, MPI_Comm comm,
			__SHIM__CALLER caller)
{
      	int datasize; 
	int rank, dest, size;
	
        MPI_Type_size(datatype, &datasize); 

	MPI_Comm_rank(comm, &rank); 
	MPI_Comm_size(comm, &size); 
	for(dest=0; dest < size; dest++) 
		if(rank != dest) {
			recvbytes[rank][dest][Allreduce] += count * datasize;
			sendbytes[rank][dest][Allreduce] += count * datasize;
			// FALTA CONSIDERAR LA VUELTA
		}
//	for(dest=0; dest < size; dest++) 
		dest  = -1;
		printf("%lu tor_MPI_Allreduce_pre caller=%u rank=%d dest=%d count=%d size=%d\n", tor_getelapsed(), caller, rank, dest, count, datasize);
        return ;
}


void tor_MPI_Allreduce_pos(void *sendbuf, void *recvbuf, int count, MPI_Datatype datatype, MPI_Op op, MPI_Comm comm,
			__SHIM__CALLER caller, int err)
{
        int datasize;
        int rank, dest, size;

        MPI_Type_size(datatype, &datasize);

        MPI_Comm_rank(comm, &rank);
        MPI_Comm_size(comm, &size);
 //       for(dest=0; dest < size; dest++)
		dest  = -1;
                printf("%lu tor_MPI_Allreduce_pos caller=%u rank=%d dest=%d count=%d size=%d\n", tor_getelapsed(), caller, rank, dest, count, datasize);
 
        return;
}



/*============================== ALLTOALL ======================================= */

void tor_MPI_Alltoall_pre(void *sendbuf, int sendcount, MPI_Datatype sendtype, void *recvbuf, int recvcount, MPI_Datatype recvtype, MPI_Comm comm,
			__SHIM__CALLER caller)
{
      	int recvsize, sendsize; 
	int rank, dest, size;


        MPI_Type_size(recvtype, &recvsize); 
        MPI_Type_size(sendtype, &sendsize); 

	MPI_Comm_rank(comm, &rank); 
	MPI_Comm_size(comm, &size); 

	for(dest=0; dest < size; dest++) 
		if(rank != dest) {
			recvbytes[rank][dest][Alltoall] += recvcount * recvsize;
			sendbytes[rank][dest][Alltoall] += sendcount * sendsize;
			// FALTA CONSIDERAR LA VUELTA
		}
//	for(dest=0; dest < size; dest++) 
		dest  = -1;
		printf("%lu tor_MPI_Alltoall_pre caller=%u rank=%d dest=%d count=%d size=%d\n",tor_getelapsed(),caller,rank,dest,sendcount,sendsize);
        return ;
}


void tor_MPI_Alltoall_pos(void *sendbuf, int sendcount, MPI_Datatype sendtype, void *recvbuf, int recvcount, MPI_Datatype recvtype, MPI_Comm comm, 
			__SHIM__CALLER caller, int err)
{
//printf("tor_MPI_Alltoall_pos\n");
      	int recvsize, sendsize; 
	int rank, dest, size;


        MPI_Type_size(recvtype, &recvsize); 
        MPI_Type_size(sendtype, &sendsize); 

	MPI_Comm_rank(comm, &rank); 
	MPI_Comm_size(comm, &size); 

//	for(dest=0; dest < size; dest++) 
		dest  = -1;
		printf("%lu tor_MPI_Alltoall_pos caller=%u rank=%d dest=%d count=%d size=%d\n",tor_getelapsed(),caller,rank,dest,sendcount,sendsize);
        return ;
}



/*============================== ALLTOALLV ======================================= */

void tor_MPI_Alltoallv_pre(void *sendbuf, int *sendcounts, int *sdispls, MPI_Datatype sendtype, void *recvbuf, int *recvcounts, 
			int *rdispls, MPI_Datatype recvtype, MPI_Comm comm,
			__SHIM__CALLER caller)
{
      	int recvsize, sendsize; 
      	int recvcount, sendcount; 
	int rank, dest, size;

//printf("tor_MPI_Alltoallv_pre\n");

        MPI_Type_size(recvtype, &recvsize); 
        MPI_Type_size(sendtype, &sendsize); 

	MPI_Comm_rank(comm, &rank); 
	MPI_Comm_size(comm, &size); 

	for(dest=0; dest < size; dest++) 
		if(rank != dest) { // including himself?
			recvbytes[rank][dest][Alltoallv] += recvcounts[dest] * recvsize;
			sendbytes[rank][dest][Alltoallv] += sendcounts[dest] * sendsize;
		}

	sendcount = 0;
	for(dest=0; dest< size; dest++)
		sendcount += sendcounts[dest];
//	for(dest=0; dest < size; dest++) 
		dest  = -1;
		printf("%lu tor_MPI_Alltoallv_pre caller=%u rank=%d dest=%d count=%d size=%d\n",tor_getelapsed(),caller,rank,dest,sendcount,sendsize);
        return;
}

void tor_MPI_Alltoallv_pos(void *sendbuf, int *sendcounts, int *sdispls, MPI_Datatype sendtype, void *recvbuf, int *recvcounts, 
			int *rdispls, MPI_Datatype recvtype, MPI_Comm comm,
			__SHIM__CALLER caller,int err)
{
//printf("tor_MPI_Alltoallv_pos\n");
      	int recvsize, sendsize; 
      	int recvcount, sendcount; 
	int rank, dest, size;

        MPI_Type_size(recvtype, &recvsize); 
        MPI_Type_size(sendtype, &sendsize); 

	MPI_Comm_rank(comm, &rank); 
	MPI_Comm_size(comm, &size); 

	sendcount = 0;
	for(dest=0; dest< size; dest++)
		sendcount += sendcounts[dest];
//	for(dest=0; dest < size; dest++) 
		dest = -1;
		printf("%lu tor_MPI_Alltoallv_pos caller=%u rank=%d dest=%d count=%d size=%d\n",tor_getelapsed(),caller,rank,dest,sendcount,sendsize);
        return;
}



