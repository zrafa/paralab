/*  ./callback-template.c  */

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
#include "/usr/lib64/openmpi/1.3.2-gcc/include/mpi.h"
#include <dlfcn.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>



void tor_MPI_Init_pre(){

//       printf("tor_MPI_Init_pre\n");
       return;
 }


void tor_MPI_Init_pos ()
{

//       printf("tor_MPI_Init_pos\n");
       return;
}

void tor_MPI_Finalize_pre()
{

//     printf("tor_MPI_Finalize_pre\n");
     return;
}

void tor_MPI_Finalize_pos()
{
//     printf("tor_MPI_Finalize_pos\n");
     return;
}


void tor_MPI_Bcast_pre(void *buffer, int *count, MPI_Fint *datatype, int *root, MPI_Fint *comm)
{
//     printf("tor_MPI_Bcast_pre\n");
	return;
}

void tor_MPI_Bcast_pos(void *buffer, int *count, MPI_Fint *datatype, int *root, MPI_Fint *comm)
{
//     printf("tor_MPI_Bcast_pos\n");
	return;
}

void tor_MPI_Send_pre (char *buf, int *count, MPI_Fint  *f_type ,int *dest, int *tag, MPI_Fint * f_comm)
{

/*         MPI_Datatype datatype;
         MPI_Comm comm;
      
         datatype = MPI_Type_f2c( *f_type);
         comm = MPI_Comm_f2c( *f_comm);
*/
//          printf("tor_MPI_Send_pre Buf=%s count=%d  dest=%d tag=%d \n", buf, *count, *dest, *tag );

        return;
}



void tor_MPI_Send_pos (char *buf, int *count, MPI_Fint * f_type ,int *dest, int *tag, MPI_Fint * f_comm)
{
/*
         MPI_Datatype datatype;
         MPI_Comm comm;

         datatype = MPI_Type_f2c(* f_type);
           comm = MPI_Comm_f2c(* f_comm);
*/
//          printf("tor_MPI_Send_pos Buf=%s count=%d  dest=%d tag=%d \n", buf, *count, *dest, *tag );

        return;
}

void tor_MPI_Recv_pre (char *buf, int *count, MPI_Fint * f_type, int *source, int *tag, MPI_Fint * f_comm, MPI_Fint *f_status)
{

/*
int MPI_Status_c2f(MPI_Status *c_status, MPI_Fint *f_status)
int MPI_Status_f2c(MPI_Fint *f_status, MPI_Status *c_status)
*/
/*
         MPI_Datatype datatype;
         MPI_Comm comm;
//         MPI_Status c_status;

         datatype = MPI_Type_f2c(* f_type);
         comm = MPI_Comm_f2c(* f_comm);
//         MPI_Status_f2c(*f_status,&c_status);
*/
//        printf("tor_MPI_Recv_pre  count=%d  source=%d tag=%d \n",   *count, *source, *tag );

        return;
}


void tor_MPI_Recv_pos (char *buf, int *count, MPI_Fint * f_type, int *source, int *tag, MPI_Fint * f_comm, MPI_Fint *f_status)
{

/*
int MPI_Status_c2f(MPI_Status *c_status, MPI_Fint *f_status)
int MPI_Status_f2c(MPI_Fint *f_status, MPI_Status *c_status)
*/
/*
         MPI_Datatype datatype;
         MPI_Comm comm;
//         MPI_Status c_status;

         datatype = MPI_Type_f2c(* f_type);
         comm = MPI_Comm_f2c(* f_comm);
//        MPI_Status_f2c(*f_status,&c_status);

//        printf("tor_MPI_Recv_pos Buf=%s count=%d dest=%d tag=%d  \n", buf,  *count, *source, *tag);
*/
        return;
}

void  tor_MPI_Isend_pre(void *buf, int *count, MPI_Fint *f_type, int *dest, int *tag, MPI_Fint *f_comm, MPI_Fint *f_request)
{
//        Datatype MPI_Type_f2c(*f_type)
//        MPI_Fint MPI_Request_c2f ( MPI_Request *request );
//        MPI_Request MPI_Request_f2c ( MPI_Fint *request );

//         printf("tor_MPI_Send_pre\n");
        return;
}


void  tor_MPI_Isend_pos(void *buf, int *count, MPI_Fint *f_type, int *dest, int *tag, MPI_Fint *f_comm, MPI_Fint *f_request)
{
//        printf("tor_MPI_Send_pos\n");
        return ;
}

void  tor_MPI_Irecv_pre(void *buf, int *count, MPI_Fint * f_type, int *source, int *tag, MPI_Fint *f_comm, MPI_Fint *f_request)
{
//        Datatype MPI_Type_f2c(*f_type)
//        MPI_Fint MPI_Request_c2f ( MPI_Request *request );
//        MPI_Request MPI_Request_f2c ( MPI_Fint *request );

//         printf("tor_MPI_Irecv_pre\n");
        return;
}


void  tor_MPI_Irecv_pos(void *buf, int *count, MPI_Fint * f_type, int *source, int *tag, MPI_Fint *f_comm, MPI_Fint *f_request)
{

//        printf("tor_MPI_Irecv_pos\n");
        return;
}



void  tor_MPI_Reduce_pre(void *sendbuf, void *recvbuf, int *count, MPI_Fint *f_type, MPI_Fint *f_op, int *root, MPI_Fint * f_comm)
{
 //       printf("tor_MPI_Reduce_pre\n");
        return ;
}

void  tor_MPI_Reduce_pos(void *sendbuf, void *recvbuf, int *count, MPI_Fint *f_type, MPI_Fint *f_op, int *root, MPI_Fint * f_comm)
{
  //      printf("tor_MPI_Reduce_pos\n");
        return ;
}


void tor_MPI_Allreduce_pre(void *sendbuf, void *recvbuf, int *count, MPI_Fint * f_type, MPI_Fint *f_op, MPI_Fint *f_comm)
{
   //    printf("tor_MPI_Allreduce_pre\n");
        return ;
}


void tor_MPI_Allreduce_pos(void *sendbuf, void *recvbuf, int *count, MPI_Fint * f_type, MPI_Fint *f_op, MPI_Fint *f_comm)
{
    //   printf("tor_MPI_Allreduce_pos\n");
        return ;
}


void tor_MPI_Alltoall_pre(void *sendbuf, int *sendcount, MPI_Fint * sendtype, void *recvbuf, int *recvcount, MPI_Fint * f_recvtype, MPI_Fint *f_comm)
{
      //  printf("tor_MPI_Alltoall_pre\n");
        return ;
}


void tor_MPI_Alltoall_pos(void *sendbuf, int *sendcount, MPI_Fint * sendtype, void *recvbuf, int *recvcount, MPI_Fint * f_recvtype, MPI_Fint *f_comm)
{
     //   printf("tor_MPI_Alltoall_pos\n");
        return ;
}


void tor_MPI_Alltoallv_pre(void *sendbuf, int *sendcounts, int *sdispls, MPI_Fint *f_sendtype, void *recvbuf, int *recvcounts, int *rdispls, MPI_Fint * f_recvtype, MPI_Fint *f_comm)
{
       // printf("tor_MPI_Alltoallv_pre\n");
        return;
}

void tor_MPI_Alltoallv_pos(void *sendbuf, int *sendcounts, int *sdispls, MPI_Fint *f_sendtype, void *recvbuf, int *recvcounts, int *rdispls, MPI_Fint * f_recvtype, MPI_Fint *f_comm)
{
        //printf("tor_MPI_Alltoallv_pos\n");
        return;
}



