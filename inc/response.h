/*
 * File:        response.h
 * Author:      solek17
 * Copyright:   2018 Copyright solek17
 * License:     GNU GENERAL PUBLIC LICENSE  Version 3
 *
 * Description:
 * HTTP responses data preparation items.
 */

/* Include guards *************************************************************/
#ifndef __HEADER__RESPONSE_H__
#define __HEADER__RESPONSE_H__

/* Includes *******************************************************************/

/* Predefinitions *************************************************************/

/* Defines ********************************************************************/
#define RESP_HTTP_200_OK              "HTTP/1.1 200 OK"
#define RESP_HTTP_400_BAD_REQUEST     "HTTP/1.1 400 Bad Request"
#define RESP_HTTP_400_BAD_REQUEST_MSG "Mystery file you are looking for!"
#define RESP_CONTENT_TYPE_TEXT_PLAIN  "text/plain"
#define RESP_CONNECTION_CLOSED        "Closed"

/* Type declarations **********************************************************/

/* Constants ******************************************************************/

/* Variables ******************************************************************/

/* Functions ******************************************************************/
void resp_200_ok(char *resp_buff, char *time_str, char *fdata_buff);
void resp_400_bad_request(char *resp_buff, char *time_str);

#endif /* __SKRZAT_H__ include guard */
