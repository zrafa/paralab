/*  ./shim.c  */

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


/*      Shim para instrumentacion mixta
        Permite instrumentar en caja negra
        Implementa algunas de las funciones MPI llamadas por NPB3.3:

                 U MPI_Allreduce        X
                 U MPI_Alltoall         X
                 U MPI_Alltoallv        X
                 U MPI_Barrier		X
                 U MPI_Comm_rank
                 U MPI_Comm_size
                 U MPI_Finalize         X
                 U MPI_Init             X
                 U MPI_Irecv            X
                 U MPI_Reduce           X
                 U MPI_Send             X
                 U MPI_Wait	  	X con deficit
                 U MPI_Waitall		X con mayor deficit
                 U MPI_Wtime
*/

// static char *LIBMPI = "/usr/lib64/openmpi/1.3.2-gcc/lib/libmpi.so";
// static char *LIBMPI = "/usr/lib/openmpi/1.4-gcc/lib/libmpi.so";
//static char *LIBMPI = "/usr/lib/libmpi.so"; // debe leerse de conf
static char *LIBMPI = "/usr/lib64/openmpi/1.4-gcc/lib/libmpi.so"; // debe leerse de conf

int (*__SHIM__FUNCTable[100])();

char *FUNCName[] = {
	"Init",
	"Barrier",
	"Bcast",
	"Allreduce",
	"Alltoall",
	"Alltoallv",
	"Comm_rank",
	"Comm_size",
	"Finalize",
	"Irecv",
	"Isend",
	"Reduce",
	"Send",
	"Recv",
	"Wait",
	"Waitll",
	"Wtime"
};

#define __SHIM__REGISTER( FUNCT ) \
                void *handle; \
                char *error; \
		int err; \
		__SHIM__CALLER caller; \
                int (*__SHIM__FUNC)() = NULL; \
                if (!__SHIM__FUNCTable[FUNCT]) { \
                        handle = dlopen(LIBMPI,RTLD_LAZY); \
                        if (!handle) { \
                                fputs(dlerror(), stderr); \
                                exit(1); \
                        } \
                        __SHIM__FUNCTable[FUNCT]= dlsym(handle,"MPI_" #FUNCT); \
                        if ((error = dlerror()) != NULL) { \
                                fprintf(stderr, "%s\n", error); \
                                exit(1); \
                        } \
                } \
                __SHIM__FUNC = __SHIM__FUNCTable[FUNCT];
		

__SHIM__CALLER CALLER0;

__SHIM__CALLER __SHIM__get_caller()
{
	unw_cursor_t cursor;
	unw_word_t sp;
	unw_word_t ip;
	unw_context_t uc;

	unw_getcontext(&uc);
	unw_init_local(&cursor, &uc);
	if((unw_step(&cursor) > 0) && (unw_step(&cursor) > 0)) {
		unw_get_reg(&cursor, UNW_REG_IP, &ip);
		return ip - CALLER0;
	} else {
		perror("caller");
		exit(1);
	}
}


int MPI_Init(int *argc, char ***argv)
{
	__SHIM__REGISTER(Init);

	CALLER0 = __SHIM__get_caller();

	tor_MPI_Init_pre();
	err =  __SHIM__FUNC(argc,argv);
	tor_MPI_Init_pos();
	return err;
}

int MPI_Finalize()
{
        __SHIM__REGISTER(Finalize);

        tor_MPI_Finalize_pre();
        err = __SHIM__FUNC();
        tor_MPI_Finalize_pos();
        return err;
}

int MPI_Barrier(MPI_Comm comm)
{
        __SHIM__REGISTER(Barrier);
	caller =  __SHIM__get_caller();
        tor_MPI_Barrier_pre(comm,caller);
        err = __SHIM__FUNC(comm);
        tor_MPI_Barrier_pos(comm,caller,err);
        return err;
}


int MPI_Bcast(void *buffer, int count, MPI_Datatype datatype, int root, MPI_Comm comm)
{
	__SHIM__REGISTER(Bcast);
	caller =  __SHIM__get_caller();
	tor_MPI_Bcast_pre(buffer, count, datatype, root, comm, caller);
	err =  __SHIM__FUNC(buffer, count, datatype, root, comm);
	tor_MPI_Bcast_pos(buffer, count, datatype, root, comm, caller, err);
	return err;
}


int MPI_Send(void *buf, int count, MPI_Datatype datatype, int dest, int tag, MPI_Comm comm)
{
	__SHIM__REGISTER(Send);
	caller =  __SHIM__get_caller();
	tor_MPI_Send_pre(buf,count,datatype,dest,tag,comm,caller);
	err =  __SHIM__FUNC(buf,count,datatype,dest,tag,comm);
	tor_MPI_Send_pos(buf,count,datatype,dest,tag,comm,caller,err);
	return err;
}


int MPI_Recv(void *buf, int count, MPI_Datatype datatype, int source, int tag, MPI_Comm comm, MPI_Status *status)
{
	__SHIM__REGISTER(Recv);
	caller =  __SHIM__get_caller();
	tor_MPI_Recv_pre(buf,count,datatype,source,tag,comm,status,caller);
	err =  __SHIM__FUNC(buf,count,datatype,source,tag,comm,status);
	tor_MPI_Recv_pos(buf,count,datatype,source,tag,comm,status,caller,err);
	return err;
}



int MPI_Isend(void *buf, int count, MPI_Datatype datatype, int dest, int tag, MPI_Comm comm, MPI_Request *request)
{
        __SHIM__REGISTER(Isend);
	caller =  __SHIM__get_caller();
        tor_MPI_Isend_pre(buf,count,datatype,dest,tag,comm,request,caller);
        err = __SHIM__FUNC(buf,count,datatype,dest,tag,comm,request);
        tor_MPI_Isend_pos(buf,count,datatype,dest,tag,comm,request,caller,err);
        return err;
}

int MPI_Wait(MPI_Request *request, MPI_Status *status)
{
        __SHIM__REGISTER(Wait);
	caller =  __SHIM__get_caller();
        tor_MPI_Wait_pre(request,status,caller);
        err = __SHIM__FUNC(request,status);
        tor_MPI_Wait_pos(request,status,caller,err);
        return err;
}
//       int MPI_Waitall(int count, MPI_Request *array_of_requests,
//            MPI_Status *array_of_statuses)
int MPI_Waitall(int count, MPI_Request *requests, MPI_Status *statuses)
{
        __SHIM__REGISTER(Waitall);
	caller =  __SHIM__get_caller();
        tor_MPI_Waitall_pre(count,(void *)requests,(void *)statuses,caller);
        err = __SHIM__FUNC(count,requests,statuses);
        tor_MPI_Waitall_pos(count,(void *)requests,(void *)statuses,caller,err);
        return err;
}


int MPI_Irecv(void *buf, int count, MPI_Datatype datatype, int source, int tag, MPI_Comm comm, MPI_Request *request)
{
        __SHIM__REGISTER(Irecv);
	caller =  __SHIM__get_caller();
        tor_MPI_Irecv_pre(buf,count,datatype,source,tag,comm,request,caller);
        err = __SHIM__FUNC(buf,count,datatype,source,tag,comm,request);
        tor_MPI_Irecv_pos(buf,count,datatype,source,tag,comm,request,caller,err);
        return err;
}
int MPI_Reduce(void *sendbuf, void *recvbuf, int count, MPI_Datatype datatype, MPI_Op op, int root, MPI_Comm comm)
{
        __SHIM__REGISTER(Reduce);
	caller =  __SHIM__get_caller();
        tor_MPI_Reduce_pre(sendbuf,recvbuf,count,datatype,op,root,comm,caller);
        err = __SHIM__FUNC(sendbuf,recvbuf,count,datatype,op,root,comm);
        tor_MPI_Reduce_pos(sendbuf,recvbuf,count,datatype,op,root,comm,caller,err);
        return err;
}

int MPI_Allreduce(void *sendbuf, void *recvbuf, int count, MPI_Datatype datatype, MPI_Op op, MPI_Comm comm)
{
        __SHIM__REGISTER(Allreduce);
	caller =  __SHIM__get_caller();
        tor_MPI_Allreduce_pre(sendbuf,recvbuf,count,datatype,op,comm,caller);
        err = __SHIM__FUNC(sendbuf,recvbuf,count,datatype,op,comm);
        tor_MPI_Allreduce_pos(sendbuf,recvbuf,count,datatype,op,comm,caller,err);
        return err;
}



int MPI_Alltoall(void *sendbuf, int sendcount, MPI_Datatype sendtype, void *recvbuf, int recvcount, MPI_Datatype recvtype, MPI_Comm comm)
{
        __SHIM__REGISTER(Alltoall);
	caller =  __SHIM__get_caller();
        tor_MPI_Alltoall_pre(sendbuf,sendcount,sendtype,recvbuf,recvcount,recvtype,comm,caller);
        err = __SHIM__FUNC(sendbuf,sendcount,sendtype,recvbuf,recvcount,recvtype,comm);
        tor_MPI_Alltoall_pos(sendbuf,sendcount,sendtype,recvbuf,recvcount,recvtype,comm,caller,err);
        return err;
}

int MPI_Alltoallv(void *sendbuf, int *sendcounts, int *sdispls, MPI_Datatype sendtype, void *recvbuf, int *recvcounts, int *rdispls, MPI_Datatype recvtype, MPI_Comm comm)
{
        __SHIM__REGISTER(Alltoallv);
	caller =  __SHIM__get_caller();
        tor_MPI_Alltoallv_pre(sendbuf,sendcounts,sdispls,sendtype,recvbuf,recvcounts,rdispls,recvtype,comm,caller);
        err = __SHIM__FUNC(sendbuf, sendcounts, sdispls, sendtype, recvbuf, recvcounts,rdispls, recvtype, comm);
        tor_MPI_Alltoallv_pos(sendbuf,sendcounts,sdispls,sendtype,recvbuf,recvcounts,rdispls,recvtype,comm,caller,err);
        return err;
}




/************************************************************
*************************************************************

   Las siguientes funciones implementan
   shim para aplicaciones en fortran

**************************************************************/

//static char *LIBFMPI = "/usr/lib64/openmpi/1.3.2-gcc/lib/libmpi_f77.so";
//static char *LIBFMPI = "/usr/lib/openmpi/1.4-gcc/lib/libmpi_f90.so";
static char *LIBFMPI = "/usr/lib/libmpi_f90.so";

int (*__SHIM__FUNCTableF[100])();

enum { 
        init,
        bcast,
	barrier,
        allreduce,
        alltoall,
        alltoallv,
        comm_rank,
        comm_size,
        finalize,
        irecv,
        isend,
        reduce,
        send,
        recv,
        wait,
	waitall,
        wtime

}; 



#define __SHIM__REGISTER_F( FUNCT ) \
                void *handle; \
                char *error; \
                int (*__SHIM__FUNC_F)() = NULL; \
				__SHIM__CALLER caller; \
                if (!__SHIM__FUNCTableF[FUNCT]) { \
                        handle = dlopen(LIBFMPI,RTLD_LAZY); \
                        if (!handle) { \
                                fputs(dlerror(), stderr); \
                                exit(1); \
                        } \
                        __SHIM__FUNCTableF[FUNCT]= dlsym(handle,"mpi_" #FUNCT); \
                        if ((error = dlerror()) != NULL) { \
                                fprintf(stderr, "%s\n", error); \
                                exit(1); \
                        } \
                } \
                __SHIM__FUNC_F = __SHIM__FUNCTableF[FUNCT] \


void mpi_init (int *ierr)
{
       __SHIM__REGISTER_F(init);
	CALLER0 = __SHIM__get_caller();
       tor_MPI_Init_pre();
       __SHIM__FUNC_F(ierr);
       tor_MPI_Init_pos(); 
       return;
}


void mpi_finalize (int *ierr)
{
       __SHIM__REGISTER_F(finalize);
       tor_MPI_Finalize_pre();
       __SHIM__FUNC_F(ierr);
       tor_MPI_Finalize_pos();
       return;
}

void mpi_barrier (MPI_Fint *comm, int *ierr)
{
	__SHIM__REGISTER_F(barrier);
	caller = __SHIM__get_caller();
	MPI_Comm cb_comm;
	cb_comm = MPI_Comm_f2c(*comm);
	tor_MPI_Barrier_pre(cb_comm,caller);
	__SHIM__FUNC_F(comm,ierr);
	tor_MPI_Barrier_pos(cb_comm,caller,*ierr);
	return;
}



void mpi_bcast(void *buffer, int *count, MPI_Fint *datatype, int *root, MPI_Fint *comm, int *ierr)
{
	__SHIM__REGISTER_F(bcast);
	caller = __SHIM__get_caller();

	MPI_Datatype cb_datatype;
	MPI_Comm cb_comm;

	cb_datatype = MPI_Type_f2c(*datatype);
	cb_comm = MPI_Comm_f2c(*comm);
	
	tor_MPI_Bcast_pre(buffer, *count, cb_datatype, *root, cb_comm, caller);
	__SHIM__FUNC_F(buffer, count, datatype, root, comm, ierr);
	tor_MPI_Bcast_pos(buffer, *count, cb_datatype, *root, cb_comm, caller, *ierr);
	return ;
}

void mpi_send(char *buf, int *count, MPI_Fint *datatype ,int *dest, int *tag, MPI_Fint *comm, int *ierr)
{
	__SHIM__REGISTER_F(send);

	MPI_Datatype cb_datatype;
	MPI_Comm cb_comm;

	caller = __SHIM__get_caller();

	cb_datatype = MPI_Type_f2c(*datatype);
	cb_comm = MPI_Comm_f2c(*comm);
	
	tor_MPI_Send_pre(buf, *count, cb_datatype, *dest, *tag, cb_comm, caller); 
	__SHIM__FUNC_F(buf, count, datatype, dest, tag, comm, ierr);
	tor_MPI_Send_pos(buf, *count, cb_datatype, *dest, *tag, cb_comm, caller, *ierr); 
	return;
}


void mpi_recv (void *buf, int *count, MPI_Fint *datatype, int *source, int *tag, MPI_Fint *comm, MPI_Fint *status, int *ierr)
{
	__SHIM__REGISTER_F(recv);
	caller = __SHIM__get_caller();

	MPI_Datatype cb_datatype;
	MPI_Comm cb_comm;
	MPI_Status cb_status;

	cb_datatype = MPI_Type_f2c(*datatype);
	cb_comm = MPI_Comm_f2c(*comm);
	MPI_Status_f2c(status, &cb_status);
	
	tor_MPI_Recv_pre(buf, *count, cb_datatype, *source, *tag, cb_comm, &cb_status, caller);
	__SHIM__FUNC_F(buf,count, datatype,source,tag, comm, status, ierr);
	tor_MPI_Recv_pos(buf, *count, cb_datatype, *source, *tag, cb_comm, &cb_status, caller, *ierr);
	return;
}



void mpi_irecv(void *buf, int *count, MPI_Fint *datatype, int *source, int *tag, MPI_Fint *comm, MPI_Fint *request, int *ierr)
{
        __SHIM__REGISTER_F(irecv);
	caller = __SHIM__get_caller();

        MPI_Datatype cb_datatype;
        MPI_Comm cb_comm;
	MPI_Request cb_request;

        cb_datatype = MPI_Type_f2c(*datatype);
        cb_comm = MPI_Comm_f2c(*comm);
        cb_request = MPI_Request_f2c(*request);
	
        tor_MPI_Irecv_pre(buf, *count, cb_datatype, *source, *tag, cb_comm, &cb_request,caller);
        __SHIM__FUNC_F(buf,count,datatype,source,tag,comm,request,ierr);
        tor_MPI_Irecv_pos(buf, *count, cb_datatype, *source, *tag, cb_comm, &cb_request,caller,*ierr);
        return;
}

void mpi_isend(void *buf, int *count, MPI_Fint *datatype, int *dest, int *tag, MPI_Fint *comm, MPI_Fint *request,int *ierr)
{
        __SHIM__REGISTER_F(isend);
	caller = __SHIM__get_caller();

        MPI_Datatype cb_datatype;
        MPI_Comm cb_comm;
	MPI_Request cb_request;

        cb_datatype = MPI_Type_f2c(*datatype);
        cb_comm = MPI_Comm_f2c(*comm);
        cb_request = MPI_Request_f2c(*request);
	
        tor_MPI_Isend_pre(buf, *count, cb_datatype, *dest, *tag, cb_comm, &cb_request,caller);
        __SHIM__FUNC_F(buf,count,datatype,dest,tag,comm,request,ierr);
        tor_MPI_Isend_pos(buf, *count, cb_datatype, *dest, *tag, cb_comm, &cb_request,caller,*ierr);
        return;
}

//       MPI_WAIT(REQUEST, STATUS, IERROR)
//            INTEGER   REQUEST, STATUS(MPI_STATUS_SIZE), IERROR
//       MPI_Request MPI_Request_f2c(MPI_Fint request)
 //      MPI_Fint MPI_Request_c2f(MPI_Request request)
void mpi_wait(MPI_Fint *request, MPI_Fint *status, int *ierr)
{
        __SHIM__REGISTER_F(wait);
	caller = __SHIM__get_caller();

	MPI_Request cb_request;
        cb_request = MPI_Request_f2c(*request);
	MPI_Status cb_status;
	MPI_Status_f2c(status, &cb_status);

        tor_MPI_Wait_pre(&cb_request,&cb_status,caller);
        __SHIM__FUNC_F(request,status,ierr);
        tor_MPI_Wait_pos(&cb_request,&cb_status,caller,*ierr);
        return;
}
//       MPI_WAITALL(COUNT, ARRAY_OF_REQUESTS, ARRAY_OF_STATUSES, IERROR)
//            INTEGER   COUNT, ARRAY_OF_REQUESTS(*)
//            INTEGER   ARRAY_OF_STATUSES(MPI_STATUS_SIZE,*), IERROR
void mpi_waitall(int *count,void *requests, void *statuses, int *ierr)
{
        __SHIM__REGISTER_F(waitall);
	caller = __SHIM__get_caller();

        tor_MPI_Waitall_pre(count,requests,statuses,caller);
        __SHIM__FUNC_F(count,requests,statuses,ierr);
        tor_MPI_Waitall_pos(count,requests,statuses,caller,*ierr);
        return;
}

void mpi_reduce(void *sendbuf, void *recvbuf, int *count, MPI_Fint *datatype, MPI_Fint *op, int *root, MPI_Fint *comm, int *ierr)
{
        __SHIM__REGISTER_F(reduce);

        MPI_Datatype cb_datatype;
        MPI_Comm cb_comm;
	MPI_Op cb_op;

	caller = __SHIM__get_caller();

        cb_datatype = MPI_Type_f2c(*datatype);
        cb_comm = MPI_Comm_f2c(*comm);
        cb_op = MPI_Op_f2c(*op);
	
        tor_MPI_Reduce_pre(sendbuf,recvbuf,*count,cb_datatype,cb_op,*root,cb_comm,caller);
         __SHIM__FUNC_F(sendbuf,recvbuf,count,datatype,op,root,comm,ierr);
        tor_MPI_Reduce_pos(sendbuf,recvbuf,*count,cb_datatype,cb_op,*root,cb_comm,caller,*ierr);
	return;
}

void mpi_allreduce(void *sendbuf, void *recvbuf, int *count, MPI_Fint *datatype, MPI_Fint *op, MPI_Fint *comm, int *ierr)
{
        __SHIM__REGISTER_F(allreduce);
	caller = __SHIM__get_caller();

        MPI_Datatype cb_datatype;
        MPI_Comm cb_comm;
	MPI_Op cb_op;

        cb_datatype = MPI_Type_f2c(*datatype);
        cb_comm = MPI_Comm_f2c(*comm);
        cb_op = MPI_Op_f2c(*op);

        tor_MPI_Allreduce_pre(sendbuf,recvbuf, *count, cb_datatype, cb_op, cb_comm,caller);
         __SHIM__FUNC_F(sendbuf,recvbuf,count,datatype,op,comm,ierr);
        tor_MPI_Allreduce_pos(sendbuf,recvbuf, *count, cb_datatype, cb_op, cb_comm,caller,*ierr);
        return;
}



void  mpi_alltoall(void *sendbuf, int *sendcount, MPI_Fint *sendtype, void *recvbuf, int *recvcount, MPI_Fint *recvtype, MPI_Fint *comm,int *ierr)
{
        __SHIM__REGISTER_F(alltoall);

        MPI_Datatype cb_sendtype, cb_recvtype;
        MPI_Comm cb_comm;

	caller = __SHIM__get_caller();

        cb_sendtype = MPI_Type_f2c(*sendtype);
        cb_recvtype = MPI_Type_f2c(*recvtype);
        cb_comm = MPI_Comm_f2c(*comm);
	
        tor_MPI_Alltoall_pre(sendbuf,*sendcount,cb_sendtype,recvbuf,*recvcount,cb_recvtype,cb_comm,caller);
        __SHIM__FUNC_F(sendbuf,sendcount,sendtype,recvbuf,recvcount,recvtype,comm,ierr);
        tor_MPI_Alltoall_pos(sendbuf,*sendcount,cb_sendtype,recvbuf,*recvcount,cb_recvtype,cb_comm,caller,*ierr);
        return;
}

void mpi_alltoallv (void *sendbuf, int *sendcounts, int *sdispls, MPI_Fint *sendtype, void *recvbuf, int *recvcounts, int *rdispls, MPI_Fint *recvtype, MPI_Fint *comm,int *ierr)
{
        __SHIM__REGISTER_F(Alltoallv);
	caller = __SHIM__get_caller();

        MPI_Datatype cb_sendtype, cb_recvtype;
        MPI_Comm cb_comm;

        cb_sendtype = MPI_Type_f2c(*sendtype);
        cb_recvtype = MPI_Type_f2c(*recvtype);
        cb_comm = MPI_Comm_f2c(*comm);
	
        tor_MPI_Alltoallv_pre(sendbuf, sendcounts, sdispls, cb_sendtype, recvbuf, recvcounts, rdispls, cb_recvtype, cb_comm,caller);
        __SHIM__FUNC_F(sendbuf, sendcounts,sdispls, sendtype, recvbuf, recvcounts, rdispls, recvtype, comm, ierr);
        tor_MPI_Alltoallv_pos(sendbuf, sendcounts, sdispls, cb_sendtype, recvbuf, recvcounts, rdispls, cb_recvtype, cb_comm,caller,*ierr);
        return;
}
