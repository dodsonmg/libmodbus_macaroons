#ifndef _MODBUS_MACAROONS_H_
#define _MODBUS_MACAROONS_H_

#include <stdio.h>
#include <string.h>

/* for Modbus */
#include <modbus/modbus.h>
#include <modbus/modbus-helpers.h>

/* Macaroons */
#include "macaroons/macaroons.h"

#if defined(__freertos__)
/* FreeRTOS */
#include "FreeRTOS.h"
#include "queue.h"
#endif

/*************
 * DEFINITIONS
 ************/

#if defined(__freertos__)
/* structure to hold queue messages (requests and responses) */
typedef struct _macaroons_queue_msg_t
{
  int msg_length;
  uint8_t *msg;
} macaroons_queue_msg_t;

/* define the length of the queue used to pass macaroons */
#define MACAROONS_QUEUE_LENGTH 1
#endif

/******************
 * SERVER FUNCTIONS
 *****************/
int initialise_server_macaroon(modbus_t *ctx, const char *location, const char *key, const char *id);
int modbus_receive_macaroons(modbus_t *ctx, uint8_t *req);

#if defined(__freertos__)
int queue_server_macaroon(modbus_t *ctx);
int modbus_preprocess_request_macaroons(modbus_t *ctx, uint8_t *req);
#else
int modbus_preprocess_request_macaroons(modbus_t *ctx, uint8_t *req, modbus_mapping_t *mb_mapping);
#endif

/******************
 * CLIENT FUNCTIONS
 *****************/

#if defined(__freertos__)
int initialise_client_macaroon(modbus_t *ctx);
#else
int initialise_client_macaroon(modbus_t *ctx, char *serialised_macaroon, int serialised_macaroon_length);
#endif
/**
 * no function required for read/write token
 * since no additional macaroon is sent with that request
 * */
int modbus_read_bits_macaroons(modbus_t *ctx, int addr, int nb, uint8_t *dest);
int modbus_read_input_bits_macaroons(modbus_t *ctx, int addr, int nb, uint8_t *dest);
int modbus_read_registers_macaroons(modbus_t *ctx, int addr, int nb, uint16_t *dest);
int modbus_read_input_registers_macaroons(modbus_t *ctx, int addr, int nb, uint16_t *dest);
int modbus_write_bit_macaroons(modbus_t *ctx, int addr, int status);
int modbus_write_register_macaroons(modbus_t *ctx, int addr, const uint16_t value);
int modbus_write_bits_macaroons(modbus_t *ctx, int addr, int nb, const uint8_t *src);
int modbus_write_registers_macaroons(modbus_t *ctx, int addr, int nb, const uint16_t *data);
int modbus_mask_write_register_macaroons(modbus_t *ctx, int addr, uint16_t and_mask, uint16_t or_mask);
int modbus_write_and_read_registers_macaroons(modbus_t *ctx, int write_addr, int write_nb,
                                               const uint16_t *src, int read_addr, int read_nb,
                                               uint16_t *dest);
int modbus_report_slave_id_macaroons(modbus_t *ctx, int max_dest, uint8_t *dest);

#endif /* _MODBUS_MACAROONS_H_ */
