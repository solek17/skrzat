/*
 * File:        response.c
 * Author:      solek17
 * Copyright:   2018 Copyright solek17
 * License:     GNU GENERAL PUBLIC LICENSE  Version 3
 *
 * Description:
 * Functions responsible for HTTP responses preparation.
 */

/* Includes *******************************************************************/
#include <stdio.h>    // sprintf
#include <string.h>   // strlen
#include "skrzat.h"
#include "response.h"

/* Predefinitions *************************************************************/
void resp_200_ok(char *resp_buff, char *time_str, char *fdata_buff);
void resp_400_bad_request(char *resp_buff, char *time_str);

/* Defines ********************************************************************/

/* Type declarations **********************************************************/

/* Constants ******************************************************************/

/* Variables ******************************************************************/

/* Functions ******************************************************************/
void resp_200_ok(char *resp_buff, char *time_str, char *fdata_buff){
  sprintf(resp_buff,  "%s\n"\
                      "Date: %s"\
                      "Server: %s/%s\n"\
                      "Last-Modified: %s"\
                      "Content-Length: %d\n"\
                      "Content-Type: %s\n"\
                      "Connection: %s\n"\
                      "\n%s",
                      RESP_HTTP_200_OK,
                      time_str,
                      SKRZAT_NAME, SKRZAT_VERSION,
                      time_str,
                      (int)strlen(fdata_buff),
                      RESP_CONTENT_TYPE_TEXT_PLAIN,
                      RESP_CONNECTION_CLOSED,
                      fdata_buff);
  return;
}

void resp_400_bad_request(char *resp_buff, char *time_str){
  sprintf(resp_buff,  "%s\n"\
                      "Date: %s"\
                      "Server: %s/%s\n"\
                      "Last-Modified: %s"\
                      "Content-Length: %d\n"\
                      "Content-Type: %s\n"\
                      "Connection: %s\n"\
                      "\n%s",
                      RESP_HTTP_400_BAD_REQUEST,
                      time_str,
                      SKRZAT_NAME, SKRZAT_VERSION,
                      time_str,
                      (int)strlen(RESP_HTTP_400_BAD_REQUEST_MSG),
                      RESP_CONTENT_TYPE_TEXT_PLAIN,
                      RESP_CONNECTION_CLOSED,
                      RESP_HTTP_400_BAD_REQUEST_MSG);
  return; 
}
