/***************************************************************************//**
 * # License
 * 
 * The licensor of this software is Silicon Laboratories Inc. Your use of this
 * software is governed by the terms of Silicon Labs Master Software License
 * Agreement (MSLA) available at
 * www.silabs.com/about-us/legal/master-software-license-agreement. This
 * software is Third Party Software licensed by Silicon Labs from a third party
 * and is governed by the sections of the MSLA applicable to Third Party
 * Software and the additional terms set forth below.
 * 
 ******************************************************************************/

/* -*- Mode: C; tab-width: 2; indent-tabs-mode: nil; c-basic-offset: 2 * -*- */

/* coap_list.h -- CoAP list structures
 *
 * Copyright (C) 2010,2011,2015 Olaf Bergmann <bergmann@tzi.org>
 *
 * This file is part of the CoAP library libcoap. Please see README for terms of
 * use.
 */

#ifndef _COAP_LIST_H_
#define _COAP_LIST_H_

#include "utlist.h"

typedef struct coap_list_t {
  struct coap_list_t *next;
  char data[];
} coap_list_t;

/**
 * Adds node to given queue, ordered by specified order function. Returns 1
 * when insert was successful, 0 otherwise.
 */
int coap_insert(coap_list_t **queue, coap_list_t *node);

/* destroys specified node */
int coap_delete(coap_list_t *node);

/* removes all items from given queue and frees the allocated storage */
void coap_delete_list(coap_list_t *queue);

#endif /* _COAP_LIST_H_ */
