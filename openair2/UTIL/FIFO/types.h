/*******************************************************************************

  Eurecom OpenAirInterface
  Copyright(c) 1999 - 2014 Eurecom

  This program is free software; you can redistribute it and/or modify it
  under the terms and conditions of the GNU General Public License,
  version 2, as published by the Free Software Foundation.

  This program is distributed in the hope it will be useful, but WITHOUT
  ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or
  FITNESS FOR A PARTICULAR PURPOSE.  See the GNU General Public License for
  more details.

  You should have received a copy of the GNU General Public License along with
  this program; if not, write to the Free Software Foundation, Inc.,
  51 Franklin St - Fifth Floor, Boston, MA 02110-1301 USA.

  The full GNU General Public License is included in this distribution in
  the file called "COPYING".

  Contact Information
  Openair Admin: openair_admin@eurecom.fr
  Openair Tech : openair_tech@eurecom.fr
  Forums       : http://forums.eurecom.fsr/openairinterface
  Address      : Eurecom, 2229, route des crêtes, 06560 Valbonne Sophia Antipolis, France

*******************************************************************************/

#ifndef __FIFO_TYPES_H__
#define __FIFO_TYPES_H__
#include "platform_types.h"

/* Types regrouping both user-defined and regular events */
typedef enum  {
  MIN_ET=0,
  OAI_ET=MIN_ET, // config events 
  SYS_ET,
  TOPO_ET,
  APP_ET,
  EMU_ET,
  DL_ET, // frame events
  UL_ET, 
  S_ET, 
  PHY_ET, // protocol events 
  MAC_ET,
  RLC_ET,
  PDCP_ET,
  RRC_ET,
  MAX_ET
} Event_Type_t;

/* decomposition of node functions into jobs for a given event */
typedef enum Job_type_e { JT_OTG, JT_PDCP, JT_PHY_MAC, JT_INIT_SYNC, JT_DL, JT_UL, RN_DL, RN_UL, JT_END} Job_Type_t;

typedef struct Job_s {
    enum Job_type_e type;
    int             exe_time; /* execution time at the worker*/
    int             nid; /* node id*/
    eNB_flag_t      eNB_flag;
    frame_t         frame;
    int             last_slot;
    int             next_slot;
    int             ctime;
} Job_t;

typedef struct Signal_buffers_s { // (s = transmit, r,r0 = receive)
  double **s_re;
  double **s_im;
  double **r_re;
  double **r_im;
  double **r_re0;
  double **r_im0;
} Signal_buffers_t;

/*!\brief  sybframe type : DL, UL, SF, */

typedef struct Packet_otg_s {
  unsigned int              sdu_buffer_size;
  unsigned char            *sdu_buffer;
  module_id_t               module_id;
  rb_id_t                   rb_id;
  module_id_t               dst_id;
  boolean_t                 is_ue;
  pdcp_transmission_mode_t  mode;
} Packet_otg_t;

typedef struct {
    Event_Type_t type;
    char             *key;
    void             *value;
    frame_t           frame;
} Event_t;

/*typedef struct Global_Time {
  uint32_t frame;
  int32_t slot;
  int32_t last_slot;
  int32_t next_slot;
  double time_s;
  double time_ms;
};*/

typedef struct Packet_otg_elt_s {
    struct Packet_otg_elt_s *next;
    struct Packet_otg_elt_s *previous;
    Packet_otg_t             otg_pkt;
} Packet_otg_elt_t;

typedef struct Job_element_s {
  struct Job_element_s *next;
  Job_t                 job;
} Job_elt_t;

typedef struct Event_element_s {
  struct Event_element *next;
  struct Event_element *previous;
  Event_t               event;
} Event_elt_t;
#endif
