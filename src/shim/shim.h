/*  ./shim.h  */

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
#define UNW_LOCAL_ONLY
#include <libunwind.h>
#define __SHIM__CALLER unw_word_t
#include <dlfcn.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
//#include "/usr/lib64/openmpi/1.4-gcc/include/mpi.h"
#include <mpi.h>
#include <sys/types.h>

#include <sys/time.h>
void tor_setclock();
suseconds_t tor_getclock();
suseconds_t tor_getelapsed();




extern char *FUNCName[] ;
enum { 
	Init,
	Bcast,
	Barrier,
	Allreduce,
	Alltoall,
	Alltoallv,
	Comm_rank,
	Comm_size,
	Finalize,
	Irecv,
	Isend,
	Reduce,
	Send,
	Recv,
	Wait,
	Waitall,
	Wtime
}; 


void tor_MPI_Init_pre();
void tor_MPI_Init_pos();

void tor_MPI_Finalize_pre();
void tor_MPI_Finalize_pos();

void tor_MPI_Barrier_pre(MPI_Comm comm,__SHIM__CALLER caller);
void tor_MPI_Barrier_pos(MPI_Comm comm, __SHIM__CALLER caller, int err);

void tor_MPI_Bcast_pre(void *buffer, int count, MPI_Datatype datatype, int root, MPI_Comm comm,__SHIM__CALLER caller);
void tor_MPI_Bcast_pos(void *buffer, int count, MPI_Datatype datatype, int root, MPI_Comm comm,__SHIM__CALLER caller, int err);

void tor_MPI_Send_pre(char *buf, int count, MPI_Datatype datatype, int dest, int tag, MPI_Comm comm, __SHIM__CALLER caller);
void tor_MPI_Send_pos(char *buf, int count, MPI_Datatype datatype, int dest, int tag, MPI_Comm comm, __SHIM__CALLER caller, int err);

void tor_MPI_Recv_pre(char *buf, int count, MPI_Datatype datatype, int source, int tag, MPI_Comm comm, MPI_Status *status, __SHIM__CALLER caller);
void tor_MPI_Recv_pos(char *buf, int count, MPI_Datatype datatype, int source, int tag, MPI_Comm comm, MPI_Status *status, __SHIM__CALLER caller, int err);

void  tor_MPI_Isend_pre(void *buf, int count, MPI_Datatype datatype, int dest, int tag, MPI_Comm comm, MPI_Request *request, __SHIM__CALLER caller);
void  tor_MPI_Isend_pos(void *buf, int count, MPI_Datatype datatype, int dest, int tag, MPI_Comm comm, MPI_Request *request,__SHIM__CALLER caller, int err);

void  tor_MPI_Wait_pre(MPI_Request *request, MPI_Status *status, __SHIM__CALLER caller);
void  tor_MPI_Wait_pos(MPI_Request *request, MPI_Status *status, __SHIM__CALLER caller, int err);

void  tor_MPI_Waitall_pre(int count, void *requests, void *status, __SHIM__CALLER caller);
void  tor_MPI_Waitall_pos(int count, void *requests, void *status, __SHIM__CALLER caller, int err);

void  tor_MPI_Irecv_pre(void *buf, int count, MPI_Datatype datatype, int source, int tag, MPI_Comm comm, MPI_Request *request, __SHIM__CALLER caller);
void  tor_MPI_Irecv_pos(void *buf, int count, MPI_Datatype datatype, int source, int tag, MPI_Comm comm, MPI_Request *request,__SHIM__CALLER caller, int err);

void  tor_MPI_Reduce_pre(void *sendbuf, void *recvbuf, int count, MPI_Datatype datatype, MPI_Op op, int root, MPI_Comm comm,__SHIM__CALLER caller);
void  tor_MPI_Reduce_pos(void *sendbuf, void *recvbuf, int count, MPI_Datatype datatype, MPI_Op op, int root, MPI_Comm comm,__SHIM__CALLER caller,int err);

void tor_MPI_Allreduce_pre(void *sendbuf, void *recvbuf, int count, MPI_Datatype datatype, MPI_Op op, MPI_Comm comm, __SHIM__CALLER caller);
void tor_MPI_Allreduce_pos(void *sendbuf, void *recvbuf, int count, MPI_Datatype datatype, MPI_Op op, MPI_Comm comm,__SHIM__CALLER caller, int err);

void tor_MPI_Alltoall_pre(void *sendbuf, int sendcount, MPI_Datatype sendtype, void *recvbuf, int recvcount, MPI_Datatype recvtype, MPI_Comm comm,__SHIM__CALLER caller);
void tor_MPI_Alltoall_pos(void *sendbuf, int sendcount, MPI_Datatype sendtype, void *recvbuf, int recvcount, MPI_Datatype recvtype, MPI_Comm comm,__SHIM__CALLER caller, int err);

void tor_MPI_Alltoallv_pre(void *sendbuf, int *sendcounts, int *sdispls, MPI_Datatype sendtype, void *recvbuf, int *recvcounts, int *rdispls, MPI_Datatype recvtype, MPI_Comm comm, __SHIM__CALLER caller);
void tor_MPI_Alltoallv_pos(void *sendbuf, int *sendcounts, int *sdispls, MPI_Datatype sendtype, void *recvbuf, int *recvcounts, int *rdispls, MPI_Datatype recvtype, MPI_Comm comm,__SHIM__CALLER caller, int err);

