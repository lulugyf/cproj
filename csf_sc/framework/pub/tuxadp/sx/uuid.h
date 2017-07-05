/* IBM_PROLOG_BEGIN_TAG                                                   */
/* This is an automatically generated prolog.                             */
/*                                                                        */
/* bos61N src/bos/usr/include/uuid.h 1.2.1.3                              */
/*                                                                        */
/* Licensed Materials - Property of IBM                                   */
/*                                                                        */
/* Restricted Materials of IBM                                            */
/*                                                                        */
/* COPYRIGHT International Business Machines Corp. 2008,2010              */
/* All Rights Reserved                                                    */
/*                                                                        */
/* US Government Users Restricted Rights - Use, duplication or            */
/* disclosure restricted by GSA ADP Schedule Contract with IBM Corp.      */
/*                                                                        */
/* IBM_PROLOG_END_TAG                                                     */
/* @(#)69     1.2.1.3  src/bos/usr/include/uuid.h, incstd, bos61N, 1031A_61N 7/8/10 14:13:10" */
/*
 *   COMPONENT_NAME: kdmf
 *
 *   ORIGINS: 72 27
 *
 *   (C) COPYRIGHT International Business Machines Corp. 1995
 *   All Rights Reserved
 *   Licensed Materials - Property of IBM
 *   US Government Users Restricted Rights - Use, duplication or
 *   disclosure restricted by GSA ADP Schedule Contract with IBM Corp.
 */
/*
 * @OSF_COPYRIGHT@
 * COPYRIGHT NOTICE
 * Copyright (c) 1990, 1991, 1992, 1993, 1996 Open Software Foundation, Inc.
 * ALL RIGHTS RESERVED (DCE).  See the file named COPYRIGHT.DCE in the
 * src directory for the full copyright text.
 */
/*
**  Copyright (c) 1989, 1990 by
**      Hewlett-Packard Company, Palo Alto, Ca. & 
**      Digital Equipment Corporation, Maynard, Mass.
**
*/
#ifndef _UUID_H
#define _UUID_H	1
#include <sys/types.h>
#define __STDC_FORMAT_MACROS 1
#include <sys/inttypes.h>
#include <sys/time.h>

/*
 * Type definitions for specific size integers.
 */
typedef u_int8_t  unsigned8;       /* positive 8 bit integer */
typedef u_int16_t unsigned16;      /* positive 16 bit integer */
typedef u_int32_t unsigned32;      /* positive 32 bit integer */
typedef int8_t	signed8;           /* signed 8 bit integer */
typedef int16_t signed16;          /* signed 16 bit integer */
typedef int32_t signed32;          /* signed 32 bit integer */
typedef char byte, *byte_t;
typedef unsigned32 boolean32;


typedef unsigned int   error_status_t;
#define error_status_ok			0
#define uuid_s_ok			error_status_ok

/*
 * Error status values from uuid APIs.
 */
#define uuid_s_internal_error		1
#define uuid_s_bad_version		2
#define uuid_s_no_memory		3 
#define uuid_s_invalid_string_uuid	4
#define uuid_s_no_address		5

#define UUID_C_UUID_STRING_MAX          37

/*
 * Universal Unique Identifier (UUID) types.
 */
typedef struct _uuid_t
{
    unsigned32          time_low;
    unsigned16          time_mid;
    unsigned16          time_hi_and_version;
    unsigned8           clock_seq_hi_and_reserved;
    unsigned8           clock_seq_low;
    byte               node[6];
} uuid_t, *uuid_p_t;

/** The strlen() of a UUID string (does not include terminating null) */
#define UUID_STRLEN 36
/**
 * Constant value indicating an as-yet undetermined UUID for a thing.  Spells \c
 * "\0\0UUID\x10_\x80UNKNOWN" in ASCII.  Zeroes at the top make it very unlikely
 * to collide with a uuid_create()d value, which puts a timestamp in that spot.
 * The \c "\x10" and \c "\x80" are reserved/version/mask bits that make this
 * conform to the format expected by the uuid.h API.
 */
#define UUID_UNKNOWN (uuid_t){0x00005555, 0x4944, 0x105F, 0x80, 0x55, {0x4E, 0x4B, 0x4E, 0x4F, 0x57, 0x4E}}
#define UUID_UNKNOWN_STR       "00005555-4944-105f-8055-4e4b4e4f574e"

/** Constant value representing a zero UUID. */
#define UUID_NIL     (uuid_t){0, 0, 0, 0, 0, {0, 0, 0, 0, 0, 0}}
#define UUID_NIL_STR           "00000000-0000-0000-0000-000000000000"

extern void uuid_create (uuid_t * uuid, unsigned32 * status);
extern void uuid_create_nil(uuid_t *uuid, unsigned32 *status);
extern void uuid_to_string(uuid_p_t uuid, unsigned char **uuid_string, unsigned32 *status);
void uuid_from_string(unsigned char * uuid_string, uuid_t *uuid, unsigned32 *status);
boolean32 uuid_equal(uuid_p_t uuid1, uuid_p_t uuid2, unsigned32 *status);
boolean32 uuid_is_nil(uuid_p_t uuid, unsigned32 *status);
signed32 uuid_compare(uuid_p_t uuid1, uuid_p_t uuid2, unsigned32 *status);
unsigned16 uuid_hash(uuid_p_t uuid, unsigned32 *status);
/**
 * Copy a UUID from one \c uuid_t to another.
 *
 * \param[in] from Pointer to the source \c uuid_t structure.  Must not be \c
 * NULL.
 *
 * \param[out] to Pointer to the target \c uuid_t structure.  The pointer must
 * not be \c NULL, and the target must have enough space to hold the result.
 *
 * \param[out] status Pointer to a memory location where the result of the
 * operation will be stored.  On success, the value is set to \c uuid_s_ok.  On
 * failure, it is set to one of the other \c uuid_s_*.
 */
extern void uuid_copy(const uuid_p_t from, uuid_p_t to, unsigned32 *status);

#endif /* _UUID_H */
