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
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "skrzat.h"
#include "auxiliary.h"
/* Predefinitions *************************************************************/

/* Defines ********************************************************************/

/* Type declarations **********************************************************/

/* Constants ******************************************************************/

/* Variables ******************************************************************/

/* Functions ******************************************************************/

/* Extract filename from REQUEST header
 * Parameters:
 * [in] request   - Pointer to REQUEST header data
 * [in] fname     - Pointer to NULL buffer to which file name will be stored
 * [out]          - 0 on SUCCESS, or -1 on FAILURE
 *
 *      *fname_start
 *      |
 * GET /index.html HTTP/1.1 
 *      |         |
 *      |         *fname_end
 *      \_________/
 *           |
 *      fname_len
 */
int get_file_name(const char *request, char **fname){
  char *fname_start = strpbrk(request, "/");
  fname_start++;
  char *fname_end = strpbrk(fname_start, " ");
  int fname_len = (int)(fname_end - fname_start);

  /* If there was no file requested return default one */
  if(fname_len == 0){
    fname_len = 10;
    fname_start = SKRZAT_DEFAULT_FILENAME;
  }
  
  *fname = (char*)calloc(fname_len+1, sizeof(char));
  if(*fname == NULL){
    printf("Not enough memory!, Sorry...");
    return -1;
  } else {
    memcpy(*fname, fname_start, fname_len); 
  }
  // Prefix 'fname' with default path
  char * fpath;
  fpath = (char*) calloc( strlen(SKRZAT_DEFAULT_DIR)+strlen(*fname), 
                          sizeof(char));
  sprintf(fpath, "%s%s", SKRZAT_DEFAULT_DIR, *fname);
  printf("%s\n", fpath);
  free(*fname);
  *fname = fpath; 
  return 0;
};

/* 
 * Read data from file 'fname' and store it in 'fdata_buff' buffer 
 * Parameters:
 *   [in] fname     Target file name
 *   [in] fdata_buff     NULL pointer to file data buffer. Size of fdata_buff will be 
 *                  allocated according to file size
 *   [out] 0        On SUCCESS or -1 on FAILURE
 */
int get_file_content(const char *fname, char **fdata_buff){
  FILE *fp;
  size_t f_size;
  fp = fopen(fname, "rb");
  fseek(fp, 0, SEEK_END);
  f_size = ftell(fp);
  fseek(fp, 0, SEEK_SET);
  if( *fdata_buff != NULL ){
    printf("[!] Possible memory leak\n");
  }
  *fdata_buff = (char*) calloc(f_size, sizeof(char));
  if( *fdata_buff == NULL ){
    printf("[!] ERROR: Not enough memory!, Sorry...\n");
    return -1;
  }
  fread(*fdata_buff, 1, f_size, fp);
  return 0;
};
