/*
 * File:        skrzat.h
 * Author:      solek17
 * Copyright:   2018 Copyright solek17
 * License:     GNU GENERAL PUBLIC LICENSE  Version 3
 *
 * Description:
 * This file contains 'skrzat' all exposed interfaces.
 */

/* Include guards *************************************************************/
#ifndef __HEADER__SKRZAT_H__
#define __HEADER__SKRZAT_H__

/* Includes *******************************************************************/

/* Predefinitions *************************************************************/

/* Defines ********************************************************************/
#define SKRZAT_ADDR                   (INADDR_ANY)  // Use my IP address
#define SKRZAT_BACKLOG                (10)          // Size of incoming connections queue
#define SKRZAT_PORT                   (5050)        // Range 1025 - 65535
#define SKRZAT_PROTOCOL               (0)
#define SKRZAT_NAME                   "SKRZAT"
#define SKRZAT_VERSION                "1.0.0"
#define SKRZAT_RECV_BUFF_SIZE         (2048)
#define SKRZAT_RESP_BUFF_SIZE         (4096)
#define SKRZAT_DEFAULT_DIR            "./www/"
#define SKRZAT_DEFAULT_FILENAME       "index.md"
/* Type declarations **********************************************************/

/* Constants ******************************************************************/

/* Variables ******************************************************************/

/* Functions ******************************************************************/
int init_and_run();

#endif /* __HEADER__SKRZAT_H__ include guard */
