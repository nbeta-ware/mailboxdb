/*
 Copyright (c) 2004-2013 NFG Net Facilities Group BV support@nfg.nl
 Copyright (c) 2014-2019 Paul J Stevens, The Netherlands, support@nfg.nl
 Copyright (c) 2020-2024 Alan Hicks, Persistent Objects Ltd support@p-o.co.uk

 This program is free software; you can redistribute it and/or 
 modify it under the terms of the GNU General Public License 
 as published by the Free Software Foundation; either 
 version 2 of the License, or (at your option) any later 
 version.

 This program is distributed in the hope that it will be useful,
 but WITHOUT ANY WARRANTY; without even the implied warranty of
 MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 GNU General Public License for more details.

 You should have received a copy of the GNU General Public License
 along with this program; if not, write to the Free Software
 Foundation, Inc., 675 Mass Ave, Cambridge, MA 02139, USA.
*/

#ifndef DM_CAPA_H
#define DM_CAPA_H

#include <glib.h>
#include "dm_mempool.h"

typedef struct Capa_T *Capa_T;

extern Capa_T          Capa_new(Mempool_T);
extern const gchar *   Capa_as_string(Capa_T);
extern gboolean        Capa_match(Capa_T, const char *); 
extern void            Capa_add(Capa_T, const char *);
extern void            Capa_remove(Capa_T, const char *);
extern void            Capa_free(Capa_T *);

#endif
