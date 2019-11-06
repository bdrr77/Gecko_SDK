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

/* coap_list.c -- CoAP list structures
 *
 * Copyright (C) 2010,2011,2015 Olaf Bergmann <bergmann@tzi.org>
 *
 * This file is part of the CoAP library libcoap. Please see README for terms of
 * use.
 */

/* #include "coap_config.h" */

#include <stdio.h>
#include <string.h>

#include "debug.h"
#include "mem.h"
#include "coap_list.h"


int
coap_insert(coap_list_t **head, coap_list_t *node) {
  if (!node) {
    coap_log(LOG_WARNING, "cannot create option Proxy-Uri\n");
  } else {
    /* must append at the list end to avoid re-ordering of
     * options during sort */
    LL_APPEND((*head), node);
  }

  return node != NULL;
}

int
coap_delete(coap_list_t *node) {
  if (node) {
    coap_free(node);
  }
  return 1;
}

void
coap_delete_list(coap_list_t *queue) {
  coap_list_t *elt, *tmp;

  if (!queue)
    return;

  LL_FOREACH_SAFE(queue, elt, tmp) {
    coap_delete(elt);
  }
}

