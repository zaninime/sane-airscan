/* AirScan (a.k.a. eSCL) backend for SANE
 *
 * Copyright (C) 2019 and up by Alexander Pevzner (pzz@apevzner.com)
 * See LICENSE for license terms and conditions
 *
 * Routines for SANE options handling
 */

#include "airscan.h"

#include <glib.h>
#include <string.h>

/* Name/value mapping entry
 */
typedef struct {
    SANE_String_Const name;
    SANE_Word         value;
} opt_name_map;

/* Decode SANE name string to numeric value
 */
static SANE_Word
opt_name_decode (const opt_name_map map[], size_t map_size,
        SANE_String_Const name)
{
    size_t i;
    for (i = 0; i < map_size; i ++) {
        if (!strcmp(map[i].name, name)) {
            return (SANE_Word) i;
        }
    }

    return -1;
}

/* Encode numeric value into SANE name string
 */
static SANE_String_Const
opt_name_encode (const opt_name_map map[], size_t map_size, SANE_Word value)
{
    size_t i;
    for (i = 0; i < map_size; i ++) {
        if (map[i].value == value) {
            return map[i].name;
        }
    }

    g_assert(!"internal error");

    return NULL;
}

/* Name map for OPT_SOURCE
 */
static opt_name_map
opt_source_name_map[] =
{
    { OPTVAL_SOURCE_PLATEN,      OPT_SOURCE_PLATEN },
    { OPTVAL_SOURCE_ADF_SIMPLEX, OPT_SOURCE_ADF_SIMPLEX },
    { OPTVAL_SOURCE_ADF_DUPLEX,  OPT_SOURCE_ADF_DUPLEX }
};

/* Decode OPT_SOURCE from SANE name
 */
OPT_SOURCE
opt_source_from_sane (SANE_String_Const name)
{
    return (OPT_SOURCE) opt_name_decode(
        opt_source_name_map, G_N_ELEMENTS(opt_source_name_map), name);
}

/* Get SANE name of OPT_SOURCE
 */
SANE_String_Const
opt_source_to_sane (OPT_SOURCE source)
{
    return opt_name_encode(opt_source_name_map,
        G_N_ELEMENTS(opt_source_name_map), (SANE_Word) source);
}

/* Name map for OPT_MODE
 */
static opt_name_map
opt_mode_name_map[] =
{
    { SANE_VALUE_SCAN_MODE_LINEART, OPT_MODE_LINEART },
    { SANE_VALUE_SCAN_MODE_GRAY,    OPT_MODE_GRAYSCALE },
    { SANE_VALUE_SCAN_MODE_COLOR,   OPT_MODE_COLOR }
};

/* Decode OPT_MODE from SANE name
 */
OPT_MODE
opt_mode_from_sane (SANE_String_Const name)
{
    return (OPT_MODE) opt_name_decode(
        opt_mode_name_map, G_N_ELEMENTS(opt_mode_name_map), name);
}

/* Get SANE name of OPT_MODE
 */
SANE_String_Const
opt_mode_to_sane (OPT_MODE mode)
{
    return opt_name_encode(opt_mode_name_map,
        G_N_ELEMENTS(opt_mode_name_map), (SANE_Word) mode);
}

/* vim:ts=8:sw=4:et
 */
