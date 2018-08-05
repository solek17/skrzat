/*
 * File:        skrzat.c
 * Author:      solek17
 * Copyright:   2018 Copyright solek17
 * License:     GNU GENERAL PUBLIC LICENSE  Version 3
 *
 * Description:
 * 'skrzat' main file. 'skrzat' is simple web server.
 */


/* Includes *******************************************************************/
#include <arpa/inet.h>
#include <errno.h>
#include <netinet/in.h>
#include <stdio.h>      // perror()
#include <stdlib.h>     // exit()
#include <string.h>     // memset()
#include <sys/socket.h>
#include <sys/types.h>
#include <time.h>
#include <unistd.h>
#include "auxiliary.h"
#include "response.h"
#include "skrzat.h"

/* Predefinitions *************************************************************/

/* Defines ********************************************************************/

/* Type declarations **********************************************************/

/* Constants ******************************************************************/

/* Variables ******************************************************************/

/* Functions ******************************************************************/
/*
 * Initialize Skrzat server and run it.
 */
int init_and_run(){
  printf("Initializing server on port %d\n", SKRZAT_PORT);
  int client_fd;
  int socket_fd;
  struct sockaddr_in client_addr; // Client address information
  struct sockaddr_in skrzat_addr; // Server address information
  time_t t = time(NULL);
  socklen_t sin_size = sizeof client_addr;
  
  /* Configure structure with socket data */
  skrzat_addr.sin_family      = AF_INET;
  skrzat_addr.sin_port        = htons(SKRZAT_PORT);
  if( SKRZAT_ADDR == INADDR_ANY ){
    skrzat_addr.sin_addr.s_addr = htonl(SKRZAT_ADDR);
  } else {
    skrzat_addr.sin_addr.s_addr = inet_addr(SKRZAT_ADDR);
  }
  memset(skrzat_addr.sin_zero, '\0', sizeof(skrzat_addr.sin_zero));
  
  /* Create a file descriptor for socket */
  if( (socket_fd = socket(PF_INET, SOCK_STREAM, SKRZAT_PROTOCOL)) == -1) {
    printf("Error, socket file descriptor. Error code: %d\n", errno);
    exit(errno);
  }
  
  /* Bind socket descriptor with configured structure */
  if( ( bind(socket_fd, 
            (struct sockaddr *)&skrzat_addr, 
            sizeof(skrzat_addr))) == -1 ){
    printf("Error, socket binding. Error code: %d\n", errno);
  }

  if( (listen(socket_fd, SKRZAT_BACKLOG)) == -1){
    printf("Error, socket listen setup. Error code: %d\n", errno);
  }

  while(1){
    /* Awaiting for connection... */
    client_fd = accept(socket_fd, (struct sockaddr *)&client_addr, &sin_size);
    
    /* Get REQUEST data */
    char * recv_buff = (char *) calloc( SKRZAT_RECV_BUFF_SIZE, sizeof(char) );
    int data_size = recv(client_fd, recv_buff, SKRZAT_RESP_BUFF_SIZE, 0);

    /* Handle REQUEST data */ 
    if( data_size > 0 && memcmp(recv_buff, "GET", 3) == 0){
      char *fname       = NULL;
      char *fdata_buff  = NULL;
      char *resp_buff   = (char *) calloc( SKRZAT_RESP_BUFF_SIZE, sizeof(char));
      char *time_str    = asctime(gmtime(&t));

      if( get_file_name(recv_buff, &fname) != 0 ){
        printf("[!] Error while looking for file name...");
        exit(1);
      }
      
      if( access(fname, R_OK) == 0){
        /* File exists and is readable. Read the content and return it. */
        if( get_file_content(fname, &fdata_buff) != 0){
          printf("[!] ERROR: while reading a file %s\n", fname);
          exit(1);
        }
        resp_200_ok(resp_buff, time_str, fdata_buff);
        data_size = send(client_fd, (void *) resp_buff, strlen(resp_buff), 0);
      } else { 
        resp_400_bad_request(resp_buff, time_str);
        data_size = send(client_fd, (void *) resp_buff, strlen(resp_buff), 0);
      }
      // Free allocated memory, it want be needed anymore
      free(fname);
      free(fdata_buff);
      free(resp_buff);
      fname       = NULL;
      fdata_buff  = NULL;
      resp_buff   = NULL;
      close(client_fd);
    } else {
      /* Receives something else than GET request */
      printf("[!] ERROR: Help, not sure what to do!\n");
    }
    free(recv_buff);
    recv_buff = NULL;
  }
  close(socket_fd);
  return 0;
}
