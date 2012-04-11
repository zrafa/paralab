/*  ./callback-classic.c  */

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
	tor_INFORME();
}

/*============================== BCAST ======================================= */

void tor_MPI_Bcast_pre(void *buffer, int count, MPI_Datatype datatype, int root, MPI_Comm comm,
			__SHIM__CALLER caller)
{
	int rankto;

//printf("tor_MPI_Bcast_pre\n");

	int datasize, rank, size;

	MPI_Type_size(datatype, &datasize); //printf("DATASIZE %d\n",datasize);
	MPI_Comm_rank(comm, &rank); //printf("RANK %d\n",rank);
	MPI_Comm_size(comm, &size); //printf("SIZE %d\n",size);

	printf("tor_MPI_Bcast_pre caller %u rank %d count %d datasize %d\n",caller,rank,count,datasize);
	if(rank == root) {
		for(rankto=0; rankto < size; rankto++)
			if(rank != rankto)
				sendbytes[rank][rankto][Bcast] += count * datasize;
	} else // does root also receive its own buffer? 
		recvbytes[rank][root][Bcast] += count * datasize;
	return;
}


void tor_MPI_Bcast_pos(void *buffer, int count, MPI_Datatype datatype, int root, MPI_Comm comm,
			__SHIM__CALLER caller,int err)
{
//printf("tor_MPI_Bcast_pos\n");
	return;
}


/*============================== SEND ======================================= */

void tor_MPI_Send_pre (char *buf, int count, MPI_Datatype datatype ,int dest, int tag, MPI_Comm comm,
			__SHIM__CALLER caller)
{
//printf("tor_MPI_Send_pre Buf=%s count=%d  dest=%d tag=%d \n", buf, *count, *dest, *tag );
	int rank, size; 
	int datasize;

        MPI_Type_size(datatype, &datasize); 
	MPI_Comm_rank(comm, &rank); 
	MPI_Comm_size(comm, &size); 

        sendbytes[rank][dest][Send] += count * datasize;
        return;
}



void tor_MPI_Send_pos (char *buf, int count, MPI_Datatype datatype ,int dest, int tag, MPI_Comm comm,
			__SHIM__CALLER caller, int err)
{
//printf("tor_MPI_Send_pos Buf=%s count=%d  dest=%d tag=%d \n", buf, *count, *dest, *tag );
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

        MPI_Type_size(datatype, &datasize); 
	MPI_Comm_rank(comm, &rank); 
	MPI_Comm_size(comm, &size); 

        recvbytes[rank][source][Recv] += count * datasize;
        return;
}


void tor_MPI_Recv_pos (char *buf, int count, MPI_Datatype datatype, int source, int tag, MPI_Comm comm, MPI_Status *status, 
			__SHIM__CALLER caller, int err)
{
//printf("tor_MPI_Recv_pos Buf=%s count=%d dest=%d tag=%d  \n", buf,  *count, *source, *tag);
        return;
}



/*============================== ISEND ======================================= */

void  tor_MPI_Isend_pre(void *buf, int count, MPI_Datatype datatype, int dest, int tag, MPI_Comm comm, MPI_Request *request,
			__SHIM__CALLER caller)
{
	int rank, size; 
	int datasize;

//printf("tor_MPI_Isend_pre\n");
        MPI_Type_size(datatype, &datasize); 
	MPI_Comm_rank(comm, &rank); 
	MPI_Comm_size(comm, &size); 

        sendbytes[rank][dest][Send] += count * datasize;
        return;
}


void  tor_MPI_Isend_pos(void *buf, int count, MPI_Datatype datatype, int dest, int tag, MPI_Comm comm, MPI_Request *request,
			__SHIM__CALLER caller, int err)
{
//printf("tor_MPI_Irecv_pos\n");
        return;
}


/*============================== IRECV ======================================= */

void  tor_MPI_Irecv_pre(void *buf, int count, MPI_Datatype datatype, int source, int tag, MPI_Comm comm, MPI_Request *request,
			__SHIM__CALLER caller)
{
	int rank, size; 
	int datasize;

//printf("tor_MPI_Irecv_pre\n");
        MPI_Type_size(datatype, &datasize); 
	MPI_Comm_rank(comm, &rank); 
	MPI_Comm_size(comm, &size); 
        recvbytes[rank][source][Irecv] += count * datasize;
        return;
}


void  tor_MPI_Irecv_pos(void *buf, int count, MPI_Datatype datatype, int source, int tag, MPI_Comm comm, MPI_Request *request,
			__SHIM__CALLER caller, int err)
{
//printf("tor_MPI_Irecv_pos\n");
        return;
}



/*============================== REDUCE ======================================= */


void  tor_MPI_Reduce_pre(void *sendbuf, void *recvbuf, int count, MPI_Datatype datatype, MPI_Op op, int root, MPI_Comm comm, 
				__SHIM__CALLER caller)
{
	int rank, size, rankfrom; 
	int datasize;

//printf("tor_MPI_Reduce_pre\n");
        MPI_Type_size(datatype, &datasize); 
	MPI_Comm_rank(comm, &rank); 
	MPI_Comm_size(comm, &size); 
	printf("tor_MPI_Reduce_pre caller %u rank %d count %d root %d datasize %d\n",caller,rank,count,root,datasize);
	if(rank == root) {
		for(rankfrom=0; rankfrom < size; rankfrom++)
			if(rank != rankfrom)
				recvbytes[rank][rankfrom][Reduce] += count * datasize;
	} else {
		sendbytes[rank][root][Reduce] += count * datasize;
	}
        return;
}

void  tor_MPI_Reduce_pos(void *sendbuf, void *recvbuf, int count, MPI_Datatype datatype, MPI_Op op, int root, MPI_Comm comm,
			__SHIM__CALLER caller, int err)
{
//printf("tor_MPI_Reduce_pos\n");
        return ;
}



/*============================== ALLREDUCE ======================================= */

void tor_MPI_Allreduce_pre(void *sendbuf, void *recvbuf, int count, MPI_Datatype datatype, MPI_Op op, MPI_Comm comm,
			__SHIM__CALLER caller)
{
      	int datasize; 
	int rank, rankto, size;
	
//printf("tor_MPI_Allreduce_pre\n");
        MPI_Type_size(datatype, &datasize); 

	MPI_Comm_rank(comm, &rank); 
	MPI_Comm_size(comm, &size); 
	for(rankto=0; rankto < size; rankto++) 
		if(rank != rankto) {
			recvbytes[rank][rankto][Allreduce] += count * datasize;
			sendbytes[rank][rankto][Allreduce] += count * datasize;
			// FALTA CONSIDERAR LA VUELTA
		}
        return ;
}


void tor_MPI_Allreduce_pos(void *sendbuf, void *recvbuf, int count, MPI_Datatype datatype, MPI_Op op, MPI_Comm comm,
			__SHIM__CALLER caller, int err)
{
//printf("tor_MPI_Allreduce_pos\n");
        return ;
}



/*============================== ALLTOALL ======================================= */

void tor_MPI_Alltoall_pre(void *sendbuf, int sendcount, MPI_Datatype sendtype, void *recvbuf, int recvcount, MPI_Datatype recvtype, MPI_Comm comm,
			__SHIM__CALLER caller)
{
      	int recvsize, sendsize; 
	int rank, rankto, size;


        MPI_Type_size(recvtype, &recvsize); 
        MPI_Type_size(sendtype, &sendsize); 

	MPI_Comm_rank(comm, &rank); 
	MPI_Comm_size(comm, &size); 

	printf("tor_MPI_Alltoall_pre caller %u rank %d sendcount %d sendsize %d recvcount %d recvsize %d\n",caller,rank,sendcount,sendsize,recvcount,recvsize);
	for(rankto=0; rankto < size; rankto++) 
		if(rank != rankto) {
			recvbytes[rank][rankto][Alltoall] += recvcount * recvsize;
			sendbytes[rank][rankto][Alltoall] += sendcount * sendsize;
			// FALTA CONSIDERAR LA VUELTA
		}
        return ;
}


void tor_MPI_Alltoall_pos(void *sendbuf, int sendcount, MPI_Datatype sendtype, void *recvbuf, int recvcount, MPI_Datatype recvtype, MPI_Comm comm, 
			__SHIM__CALLER caller, int err)
{
//printf("tor_MPI_Alltoall_pos\n");
        return ;
}



/*============================== ALLTOALLV ======================================= */

void tor_MPI_Alltoallv_pre(void *sendbuf, int *sendcounts, int *sdispls, MPI_Datatype sendtype, void *recvbuf, int *recvcounts, 
			int *rdispls, MPI_Datatype recvtype, MPI_Comm comm,
			__SHIM__CALLER caller)
{
      	int recvsize, sendsize; 
	int rank, rankto, size;

//printf("tor_MPI_Alltoallv_pre\n");

        MPI_Type_size(recvtype, &recvsize); 
        MPI_Type_size(sendtype, &sendsize); 

	MPI_Comm_rank(comm, &rank); 
	MPI_Comm_size(comm, &size); 

	for(rankto=0; rankto < size; rankto++) 
		if(rank != rankto) {
			recvbytes[rank][rankto][Alltoallv] += recvcounts[rankto] * recvsize;
			sendbytes[rank][rankto][Alltoallv] += sendcounts[rankto] * sendsize;
		}
        return;
}

void tor_MPI_Alltoallv_pos(void *sendbuf, int *sendcounts, int *sdispls, MPI_Datatype sendtype, void *recvbuf, int *recvcounts, 
			int *rdispls, MPI_Datatype recvtype, MPI_Comm comm,
			__SHIM__CALLER caller,int err)
{
//printf("tor_MPI_Alltoallv_pos\n");
        return;
}



