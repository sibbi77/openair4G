/***************************************************************************
                            rrc_rb_ue.c
                           -------------------
    begin                : Nov 10, 2001
    copyright            : (C) 2001, 2010 by Eurecom
    author               : Michelle.Wetterwald@eurecom.fr
 **************************************************************************
  This file contains the code generated by the Esterel engine

  IT MUST NOT BE MODIFIED MANUALLY
 ***************************************************************************/
/********************
//OpenAir definitions
 ********************/
#include "LAYER2/MAC/extern.h"
#include "UTIL/MEM/mem_block.h"
//-----------------------------------------------------------------------------
#include "rrc_ue_vars.h"
//-----------------------------------------------------------------------------
/* "SAXORT STRL Compiler version 3.1.6n compiled on Fri_Oct_18_15:50:53_CEST_2002" */

/* automaton kernel code*/
//#include <stdlib.h>
//#include <stdio.h>
//#include <string.h>
#include "rrc_rb_ue.h"
#define SIZEOFINT 32
#define B_SET_VECTOR_MASK(i) ((unsigned int)1 << i)
#define B_RES_VECTOR_MASK(i) (~((unsigned int)1 << i))
#define BIT_SET(b_vector, bit_number) (b_vector)[(bit_number) / SIZEOFINT] |= B_SET_VECTOR_MASK((bit_number) % SIZEOFINT)
#define BIT_RESET(b_vector, bit_number) (b_vector)[(bit_number) / SIZEOFINT] &= ~B_SET_VECTOR_MASK((bit_number) % SIZEOFINT)

#define IS_ON(point) (_On[point / SIZEOFINT] & B_SET_VECTOR_MASK(point % SIZEOFINT))
#define IS_PAUSE_ON(point) (_Pause[point / SIZEOFINT] & B_SET_VECTOR_MASK(point % SIZEOFINT))

#define HALT_POINT_NUM 22
#define HALT_POINT_VECTOR_SIZE ((HALT_POINT_NUM-1)/(int)SIZEOFINT)+1
static unsigned int _On[HALT_POINT_VECTOR_SIZE];
static unsigned int _Pause[HALT_POINT_VECTOR_SIZE];

#define SIGNAL_NUM 33
#define SIGNAL_VECTOR_SIZE 2
#define SIGNAL_WITH_PRE_VECTOR_SIZE 1
#define GLOBALMAXPRELEVEL 2
static unsigned int _Sig[SIGNAL_VECTOR_SIZE];
static unsigned int _SigPreTab[GLOBALMAXPRELEVEL][SIGNAL_WITH_PRE_VECTOR_SIZE];
static unsigned int *_SigPre_0 = _SigPreTab[0];
static unsigned int *_SigPre_1 = _SigPreTab[1];
#define EMIT(vector, signal) (vector)[signal / SIZEOFINT] |= B_SET_VECTOR_MASK(signal % SIZEOFINT)
#define CLEAR_SIGNAL(vector, signal) (vector)[signal / SIZEOFINT] &= B_RES_VECTOR_MASK(signal % SIZEOFINT)
#define IS_SIGNAL(vector, signal) ((vector)[signal / SIZEOFINT] & B_SET_VECTOR_MASK(signal % SIZEOFINT))

#define GUARD_NUM 13
#define GUARD_VECTOR_SIZE ((GUARD_NUM-1)/(int)SIZEOFINT)+1
static unsigned int _Guard[GUARD_VECTOR_SIZE];
#define IS_GUARD(guard) (_Guard[guard / SIZEOFINT] & B_SET_VECTOR_MASK(guard % SIZEOFINT))
#define SET_GUARD(guard) _Guard[guard / SIZEOFINT] |= B_SET_VECTOR_MASK(guard % SIZEOFINT)
#define RESET_GUARD(guard) _Guard[guard / SIZEOFINT] &= B_RES_VECTOR_MASK(guard % SIZEOFINT)

#ifndef _PREDEFINED_TYPES
#    define _PREDEFINED_TYPES
typedef int     boolean;
typedef int     integer;
#    ifndef STRLEN
#        define STRLEN 81
#    endif
typedef char   *string;
#    define _integer(x, y) (*x) = (y)
#    define _boolean(x, y) (*x) = (y)
#    define _float(x, y) (*x) = (y)
#    define _double(x, y) (*x) = (y)
#    define _string(x, y) strcpy((*x), (y))
#    define _eq_integer(x, y) ((x) == (y))
#    define _eq_boolean(x, y) ((x) == (y))
#    define _eq_float(x, y) ((x) == (y))
#    define _eq_double(x, y) ((x) == (y))
#    define _eq_string(x, y) (!strcmp((x), (y)))
#    define _ne_integer(x, y) ((x) != (y))
#    define _ne_boolean(x, y) ((x) != (y))
#    define _ne_float(x, y) ((x) != (y))
#    define _ne_double(x, y) ((x) != (y))
#    define _ne_string(x, y) (strcmp((x), (y)))
#    define _cond_integer(x, y, z) ((x)?(y):(z))
#    define _cond_boolean(x, y, z) ((x)?(y):(z))
#    define _cond_float(x, y, z) ((x)?(y):(z))
#    define _cond_double(x, y, z) ((x)?(y):(z))
#    define _cond_string(x, y, z) ((x)?(y):(z))
#    define _string_to_text(x) (x)
#    define _text_to_string(x, y) (strcpy((*x), (y)))
#    define _plus_(x, y) (x) + (y)
#    define _minus_(x, y) (x) - (y)
#    define _times_(x, y) (x) * (y)
#    define _div_(x, y) (x) / (y)
#    define _mod_(x, y) (x) % (y)
#    define _not_(x) !(x)
#    define _or_(x, y) (x) || (y)
#    define _and_(x, y) (x) && (y)
#    define _equal_(x, y) (x) == (y)
#    define _diff_(x, y) (x) != (y)
#    define _sup_(x, y) (x) > (y)
#    define _supequal_(x, y) (x) >= (y)
#    define _inf_(x, y) (x) < (y)
#    define _infequal_(x, y) (x) <= (y)
#endif
#ifndef RB_SETUP
extern integer  RB_SETUP;
#endif
#ifndef RB_RELEASE
extern integer  RB_RELEASE;
#endif
#ifndef RB_SETUP_COMPLETE
extern integer  RB_SETUP_COMPLETE;
#endif
#ifndef RB_SETUP_FAILURE
extern integer  RB_SETUP_FAILURE;
#endif
#ifndef RB_RELEASE_COMPLETE
extern integer  RB_RELEASE_COMPLETE;
#endif
#ifndef RB_RELEASE_FAILURE
extern integer  RB_RELEASE_FAILURE;
#endif
#ifndef CELL_UPDATE
extern integer  CELL_UPDATE;
#endif
#ifndef CELL_FACH
extern integer  CELL_FACH;
#endif
static boolean  Var__ThisIsTheEnd__114;
#define __Sig_sc_in_RB_Management_DOT_CELL_DCH_97 0
static integer  Var_msg_113;
#define __Sig_sc_go_45_RBSU_Failure_112 0
static integer  Var_msg_111;
#define __Sig_sc_go_36_CELL_DCH_109 1
#define __Sig_sc_go_42_CELL_PCH_110 2
static integer  Var_next_state_108;
static integer  Var_msg_107;
#define __Sig_Go_CELL_FACH_105 3
#define __Sig_Go_CELL_DCH_104 4
static boolean  Sig_INVALID_CONFIGURATION_103;
static boolean  Sig_ORDERED_RECONFIGURATION_102;
#define __Sig_RB_Establish_Success_98 5
#define __Out_O_CELL_Update_Proc_96 6
#define __Out_O_New_State_CELL_FACH_95 7
#define __Out_O_New_State_CELL_DCH_94 8
#define __Out_O_startT305_93 9
#define __Out_O_SEND_CCCH_92 10
static integer  Out_O_SEND_CCCH_92;
#define __Out_O_SEND_DCCH_AM_91 11
static integer  Out_O_SEND_DCCH_AM_91;
#define __Out_O_CRLC_CONFIG_Req_90 12
#define __Out_O_CMAC_CONFIG_Req_89 13
#define __Out_O_CPHY_RL_RELEASE_Req_88 14
#define __Out_O_CPHY_RL_SETUP_Req_87 15
#define __Out_O_NAS_RB_RELEASE_Ind_86 16
static integer  Out_O_NAS_RB_RELEASE_Ind_86;
#define __Out_O_NAS_RB_ESTABLISH_Ind_85 17
static integer  Out_O_NAS_RB_ESTABLISH_Ind_85;
#define __In_I_Go_CELL_PCH_84 18
#define __In_I_Go_CELL_FACH_83 19
#define __In_I_Go_CELL_DCH_82 20
#define __In_I_Go_Idle_81 21
#define __In_I_IE_RRC_State_80 22
static integer  In_I_IE_RRC_State_80;
#define __In_I_Radio_Bearer_ID_79 23
static integer  In_I_Radio_Bearer_ID_79;
#define __In_I_RLC_Success_78 24
#define __In_I_CRLC_STATUS_77 25
#define __In_I_CPHY_OUT_OF_SYNCH_76 26
#define __In_I_CPHY_SYNCH_Failure_75 27
#define __In_I_CPHY_SYNCH_IND_74 28
#define __In_I_Prot_Error_73 29
static boolean  In_I_Prot_Error_73;
#define __In_I_CELL_UPDATE_CONFIRM_72 30
#define __In_I_RADIO_BEARER_RELEASE_71 31
#define __In_I_RADIO_BEARER_SETUP_70 32
#ifndef proc_IE_activ_Time
extern void     proc_IE_activ_Time ();
#endif
#ifndef proc_IE_RNTIs
extern void     proc_IE_RNTIs ();
#endif
#ifndef proc_IE_transaction
extern void     proc_IE_transaction ();
#endif
#ifndef proc_IE_configuration
extern void     proc_IE_configuration ();
#endif
#ifndef clear_C_RNTI
extern void     clear_C_RNTI ();
#endif
#ifndef set_RRC_Transaction_ID
extern void     set_RRC_Transaction_ID ();
#endif
#ifndef Select_Secondary_CCPCH
extern void     Select_Secondary_CCPCH ();
#endif
#ifndef Select_PRACH
extern void     Select_PRACH ();
#endif
#ifndef ue_clear_transaction
extern void     ue_clear_transaction (integer);
#endif
#ifndef encode_message
extern void     encode_message (integer *, integer);
#endif
#ifndef INTEGER_COMBINE
extern integer  INTEGER_COMBINE (integer, integer);
#endif
#ifndef BOOLEAN_COMBINE
extern boolean  BOOLEAN_COMBINE (boolean, boolean);
#endif

extern void     RRC_RB_UE_O_O_CELL_Update_Proc (void);
extern void     RRC_RB_UE_O_O_New_State_CELL_FACH (void);
extern void     RRC_RB_UE_O_O_New_State_CELL_DCH (void);
extern void     RRC_RB_UE_O_O_startT305 (void);
extern void     RRC_RB_UE_O_O_SEND_CCCH (integer);
extern void     RRC_RB_UE_O_O_SEND_DCCH_AM (integer);
extern void     RRC_RB_UE_O_O_CRLC_CONFIG_Req (void);
extern void     RRC_RB_UE_O_O_CMAC_CONFIG_Req (void);
extern void     RRC_RB_UE_O_O_CPHY_RL_RELEASE_Req (void);
extern void     RRC_RB_UE_O_O_CPHY_RL_SETUP_Req (void);
extern void     RRC_RB_UE_O_O_NAS_RB_RELEASE_Ind (integer);
extern void     RRC_RB_UE_O_O_NAS_RB_ESTABLISH_Ind (integer);
void
RRC_RB_UE_I_I_Go_CELL_PCH (void)
{
  EMIT (_Sig, __In_I_Go_CELL_PCH_84);
}

void
RRC_RB_UE_I_I_Go_CELL_FACH (void)
{
  EMIT (_Sig, __In_I_Go_CELL_FACH_83);
}

void
RRC_RB_UE_I_I_Go_CELL_DCH (void)
{
  EMIT (_Sig, __In_I_Go_CELL_DCH_82);
}

void
RRC_RB_UE_I_I_Go_Idle (void)
{
  EMIT (_Sig, __In_I_Go_Idle_81);
}

void
RRC_RB_UE_I_I_IE_RRC_State (integer value)
{
  EMIT (_Sig, __In_I_IE_RRC_State_80);
  _integer (&In_I_IE_RRC_State_80, value);
}

void
RRC_RB_UE_I_I_Radio_Bearer_ID (integer value)
{
  EMIT (_Sig, __In_I_Radio_Bearer_ID_79);
  _integer (&In_I_Radio_Bearer_ID_79, value);
}

void
RRC_RB_UE_I_I_RLC_Success (void)
{
  EMIT (_Sig, __In_I_RLC_Success_78);
}

void
RRC_RB_UE_I_I_CRLC_STATUS (void)
{
  EMIT (_Sig, __In_I_CRLC_STATUS_77);
}

void
RRC_RB_UE_I_I_CPHY_OUT_OF_SYNCH (void)
{
  EMIT (_Sig, __In_I_CPHY_OUT_OF_SYNCH_76);
}

void
RRC_RB_UE_I_I_CPHY_SYNCH_Failure (void)
{
  EMIT (_Sig, __In_I_CPHY_SYNCH_Failure_75);
}

void
RRC_RB_UE_I_I_CPHY_SYNCH_IND (void)
{
  EMIT (_Sig, __In_I_CPHY_SYNCH_IND_74);
}

void
RRC_RB_UE_I_I_Prot_Error (boolean value)
{
  EMIT (_Sig, __In_I_Prot_Error_73);
  _boolean (&In_I_Prot_Error_73, value);
}

void
RRC_RB_UE_I_I_CELL_UPDATE_CONFIRM (void)
{
  EMIT (_Sig, __In_I_CELL_UPDATE_CONFIRM_72);
}

void
RRC_RB_UE_I_I_RADIO_BEARER_RELEASE (void)
{
  EMIT (_Sig, __In_I_RADIO_BEARER_RELEASE_71);
}

void
RRC_RB_UE_I_I_RADIO_BEARER_SETUP (void)
{
  printf("\n Inside Esterel FSM  RRC_RB_UE_I_I_RADIO_BEARER_SETUP \n\n");
  EMIT (_Sig, __In_I_RADIO_BEARER_SETUP_70);
}

static void
Point_0 (void)
{
  /*#0 */
  printf("\n Inside Esterel FSM  Point_0 \n\n");
  _boolean (&Var__ThisIsTheEnd__114, 1);
  CLEAR_SIGNAL (_SigPre_0, __Sig_sc_in_RB_Management_DOT_CELL_DCH_97);
  CLEAR_SIGNAL (_SigPre_1, __Sig_sc_in_RB_Management_DOT_CELL_DCH_97);
  _boolean (&Sig_ORDERED_RECONFIGURATION_102, 0);
  _boolean (&Sig_INVALID_CONFIGURATION_103, 0);
  _On[0] |= 0x8;                /* On: #3 */
}

static void
Point_1 (void)
{
  /*#1 AutoPauseOn */
  printf("\n Inside Esterel FSM  Point_1 \n\n");

  if ((IS_SIGNAL (_Sig, __In_I_CPHY_OUT_OF_SYNCH_76) || IS_SIGNAL (_Sig, __In_I_CRLC_STATUS_77))) {
    encode_message (&Var_msg_113, CELL_UPDATE);
    EMIT (_Sig, __Out_O_SEND_CCCH_92);

    if (!(IS_GUARD (7)))
      _integer (&Out_O_SEND_CCCH_92, Var_msg_113);
    else
      _integer (&Out_O_SEND_CCCH_92, INTEGER_COMBINE (Out_O_SEND_CCCH_92, Var_msg_113));

    SET_GUARD (7);
    RRC_RB_UE_O_O_SEND_CCCH (Out_O_SEND_CCCH_92);
    _On[0] &= ~0x2;             /* Off: #1 */
    _Pause[0] |= 0x4;           /* PauseOn: #2 */
  }
}

static void
Point_2 (void)
{
  /*#2 AutoPauseOn */
  printf("\n Inside Esterel FSM  Point_2 \n\n");

  if (IS_SIGNAL (_Sig, __In_I_CELL_UPDATE_CONFIRM_72)) {
    EMIT (_Sig, __Out_O_CELL_Update_Proc_96);

    if (!(IS_GUARD (3))) {
      RRC_RB_UE_O_O_CELL_Update_Proc ();
      SET_GUARD (3);
    }

    _On[0] &= ~0x4;             /* Off: #2 */
    _Pause[0] |= 0x2;           /* PauseOn: #1 */
  }
}

static void
Point_3 (void)
{
  /*#3 AutoPauseOn */
  printf("\n Inside Esterel FSM  Point_3 \n\n");

  if ((IS_SIGNAL (_Sig, __In_I_Go_CELL_DCH_82) || IS_SIGNAL (_Sig, __In_I_Go_CELL_FACH_83))) {
    _integer (&Var_next_state_108, 1);
    CLEAR_SIGNAL (_Sig, __Sig_sc_go_36_CELL_DCH_109);
    _On[0] &= ~0x8;             /* Off: #3 */
    _Pause[0] |= 0x200812;      /* PauseOn: #1 #4 #11 #21 */

    if (IS_SIGNAL (_Sig, __In_I_Go_CELL_FACH_83)) {
      SET_GUARD (0);
    } else {
      if (IS_SIGNAL (_Sig, __In_I_Go_CELL_DCH_82)) {
        SET_GUARD (0);
        EMIT (_Sig, __Sig_sc_go_36_CELL_DCH_109);
      } else {
        _Pause[0] |= 0x100000;  /* PauseOn: #20 */
      }
    }

    if (IS_GUARD (0)) {
      if (IS_SIGNAL (_Sig, __Sig_sc_go_36_CELL_DCH_109)) {
        EMIT (_SigPre_0, __Sig_sc_in_RB_Management_DOT_CELL_DCH_97);
        _Pause[0] |= 0x60000;   /* PauseOn: #17 #18 */
      } else {
        _Pause[0] |= 0x10000;   /* PauseOn: #16 */
      }
    }
  }
}

static void
Point_4 (void)
{
  /*#4 AutoPauseOn */
  printf("\n Inside Esterel FSM  Point_4 \n\n");

  if (IS_SIGNAL (_Sig, __In_I_RADIO_BEARER_SETUP_70)) {
    printf ("\n\n Inside ESTEREL 1 \n");

    if (!(IS_GUARD (0)))
      _boolean (&Sig_ORDERED_RECONFIGURATION_102, 1);
    else
      _boolean (&Sig_ORDERED_RECONFIGURATION_102, BOOLEAN_COMBINE (Sig_ORDERED_RECONFIGURATION_102, 1));

    SET_GUARD (0);
    _On[0] &= ~0x10;            /* Off: #4 */

    if (_eq_boolean (In_I_Prot_Error_73, 0)) {
      printf ("\n\n Inside ESTEREL 2 \n");
      proc_IE_activ_Time ();
      proc_IE_RNTIs ();
      proc_IE_transaction ();
      proc_IE_configuration ();
      EMIT (_Sig, __Out_O_CPHY_RL_SETUP_Req_87);

      if (!(IS_GUARD (12))) {
        RRC_RB_UE_O_O_CPHY_RL_SETUP_Req ();
        SET_GUARD (12);
      }

      EMIT (_Sig, __Out_O_CMAC_CONFIG_Req_89);

      if (!(IS_GUARD (10))) {
        RRC_RB_UE_O_O_CMAC_CONFIG_Req ();
        SET_GUARD (10);
      }

      _Pause[0] |= 0x20;        /* PauseOn: #5 */
    } else {
      if (!(IS_GUARD (0)))
        _boolean (&Sig_INVALID_CONFIGURATION_103, 1);
      else
        _boolean (&Sig_INVALID_CONFIGURATION_103, BOOLEAN_COMBINE (Sig_INVALID_CONFIGURATION_103, 1));

      SET_GUARD (0);
      EMIT (_Sig, __Sig_sc_go_45_RBSU_Failure_112);
      _On[0] |= 0x100;          /* On: #8 */
    }
  }
}

static void
Point_5 (void)
{
  printf("\n Inside Esterel FSM  Point_5 \n\n");

  /*#5 AutoPauseOn */
  if (IS_SIGNAL (_Sig, __In_I_CPHY_SYNCH_IND_74)) {
    _On[0] &= ~0x20;            /* Off: #5 */

    if (IS_SIGNAL (_SigPre_1, __Sig_sc_in_RB_Management_DOT_CELL_DCH_97)) {
      _Pause[0] |= 0x40;        /* PauseOn: #6 */
    } else {
      EMIT (_Sig, __Sig_Go_CELL_DCH_104);
      clear_C_RNTI ();
      _Pause[0] |= 0x40;        /* PauseOn: #6 */
    }

    EMIT (_Sig, __Out_O_CRLC_CONFIG_Req_90);

    if (!(IS_GUARD (9))) {
      RRC_RB_UE_O_O_CRLC_CONFIG_Req ();
      SET_GUARD (9);
    }

    set_RRC_Transaction_ID ();
    encode_message (&Var_msg_111, RB_SETUP_COMPLETE);
    EMIT (_Sig, __Out_O_SEND_DCCH_AM_91);

    if (!(IS_GUARD (8)))
      _integer (&Out_O_SEND_DCCH_AM_91, Var_msg_111);
    else
      _integer (&Out_O_SEND_DCCH_AM_91, INTEGER_COMBINE (Out_O_SEND_DCCH_AM_91, Var_msg_111));

    SET_GUARD (8);
    _On[0] |= 0x4000;           /* On: #14 */
  } else {
    if (IS_SIGNAL (_Sig, __In_I_CPHY_SYNCH_Failure_75)) {
      EMIT (_Sig, __Sig_sc_go_45_RBSU_Failure_112);
      _On[0] |= 0x100;          /* On: #8 */
      _On[0] &= ~0x20;          /* Off: #5 */
    }
  }
}

static void
Point_6 (void)
{
  printf("\n Inside Esterel FSM  Point_6 \n\n");

  /*#6 AutoPauseOn */
  if (IS_SIGNAL (_Sig, __In_I_RLC_Success_78)) {
    ue_clear_transaction (RB_SETUP);
    EMIT (_Sig, __Sig_RB_Establish_Success_98);
    _On[0] |= 0x80;             /* On: #7 */
    _On[0] &= ~0x40;            /* Off: #6 */
  }
}

static void
Point_7 (void)
{
  printf("\n Inside Esterel FSM  Point_7 \n\n");

  /*#7 AutoPauseOn */
  if (IS_SIGNAL (_Sig, __Sig_RB_Establish_Success_98)) {
    if (!(IS_GUARD (0)))
      _boolean (&Sig_ORDERED_RECONFIGURATION_102, 0);
    else
      _boolean (&Sig_ORDERED_RECONFIGURATION_102, BOOLEAN_COMBINE (Sig_ORDERED_RECONFIGURATION_102, 0));

    SET_GUARD (0);
    EMIT (_Sig, __Out_O_NAS_RB_ESTABLISH_Ind_85);
    _integer (&Out_O_NAS_RB_ESTABLISH_Ind_85, In_I_Radio_Bearer_ID_79);
    RRC_RB_UE_O_O_NAS_RB_ESTABLISH_Ind (Out_O_NAS_RB_ESTABLISH_Ind_85);
    _On[0] |= 0x100;            /* On: #8 */
    _On[0] &= ~0x80;            /* Off: #7 */
  }
}

static void
Point_8 (void)
{
  printf("\n Inside Esterel FSM  Point_8 \n\n");

  /*#8 */
  if (IS_SIGNAL (_Sig, __Sig_sc_go_45_RBSU_Failure_112)) {
    set_RRC_Transaction_ID ();
    encode_message (&Var_msg_111, RB_SETUP_FAILURE);
    EMIT (_Sig, __Out_O_SEND_DCCH_AM_91);

    if (!(IS_GUARD (8)))
      _integer (&Out_O_SEND_DCCH_AM_91, Var_msg_111);
    else
      _integer (&Out_O_SEND_DCCH_AM_91, INTEGER_COMBINE (Out_O_SEND_DCCH_AM_91, Var_msg_111));

    SET_GUARD (8);
    _On[0] |= 0x4000;           /* On: #14 */
    _Pause[0] |= 0x200;         /* PauseOn: #9 */
  } else {
    _Pause[0] |= 0x10;          /* PauseOn: #4 */
  }
}

static void
Point_9 (void)
{
  printf("\n Inside Esterel FSM  Point_9 \n\n");

  /*#9 AutoPauseOn */
  if (IS_SIGNAL (_Sig, __In_I_RLC_Success_78)) {
    if (!(IS_GUARD (0)))
      _boolean (&Sig_INVALID_CONFIGURATION_103, 0);
    else
      _boolean (&Sig_INVALID_CONFIGURATION_103, BOOLEAN_COMBINE (Sig_INVALID_CONFIGURATION_103, 0));

    SET_GUARD (0);

    if (!(IS_GUARD (0)))
      _boolean (&Sig_ORDERED_RECONFIGURATION_102, 0);
    else
      _boolean (&Sig_ORDERED_RECONFIGURATION_102, BOOLEAN_COMBINE (Sig_ORDERED_RECONFIGURATION_102, 0));

    SET_GUARD (0);
    _On[0] &= ~0x200;           /* Off: #9 */
    _Pause[0] |= 0x10;          /* PauseOn: #4 */
  }
}

static void
Point_10 (void)
{
  printf("\n Inside Esterel FSM  Point_10 \n\n");

  /*#10 AutoPauseOn */
  if (IS_SIGNAL (_Sig, __In_I_RLC_Success_78)) {
    if (!(IS_GUARD (0)))
      _boolean (&Sig_ORDERED_RECONFIGURATION_102, 0);
    else
      _boolean (&Sig_ORDERED_RECONFIGURATION_102, BOOLEAN_COMBINE (Sig_ORDERED_RECONFIGURATION_102, 0));

    SET_GUARD (0);
    ue_clear_transaction (RB_RELEASE);
    _On[0] &= ~0x400;           /* Off: #10 */
    _Pause[0] |= 0x800;         /* PauseOn: #11 */
  }
}

static void
Point_11 (void)
{
  printf("\n Inside Esterel FSM  Point_11 \n\n");

  /*#11 AutoPauseOn */
  if (IS_SIGNAL (_Sig, __In_I_RADIO_BEARER_RELEASE_71)) {
    if (!(IS_GUARD (0)))
      _boolean (&Sig_ORDERED_RECONFIGURATION_102, 1);
    else
      _boolean (&Sig_ORDERED_RECONFIGURATION_102, BOOLEAN_COMBINE (Sig_ORDERED_RECONFIGURATION_102, 1));

    SET_GUARD (0);
    _On[0] &= ~0x800;           /* Off: #11 */

    if (_eq_boolean (In_I_Prot_Error_73, 0)) {
      _On[0] |= 0x1000;         /* On: #12 */
    } else {
      _On[0] |= 0x2000;         /* On: #13 */
    }
  }
}

static void
Point_12 (void)
{
  printf("\n Inside Esterel FSM  Point_12 \n\n");
  /*#12 */
  _integer (&Var_next_state_108, In_I_IE_RRC_State_80);
  proc_IE_activ_Time ();
  proc_IE_RNTIs ();
  proc_IE_transaction ();
  proc_IE_configuration ();
  EMIT (_Sig, __Out_O_CRLC_CONFIG_Req_90);

  if (!(IS_GUARD (9))) {
    RRC_RB_UE_O_O_CRLC_CONFIG_Req ();
    SET_GUARD (9);
  }

  EMIT (_Sig, __Out_O_CMAC_CONFIG_Req_89);

  if (!(IS_GUARD (10))) {
    RRC_RB_UE_O_O_CMAC_CONFIG_Req ();
    SET_GUARD (10);
  }

  EMIT (_Sig, __Out_O_CPHY_RL_RELEASE_Req_88);

  if (!(IS_GUARD (11))) {
    RRC_RB_UE_O_O_CPHY_RL_RELEASE_Req ();
    SET_GUARD (11);
  }

  if (_eq_integer (Var_next_state_108, CELL_FACH)) {
    EMIT (_Sig, __Sig_Go_CELL_FACH_105);
    Select_Secondary_CCPCH ();
    Select_PRACH ();
    EMIT (_Sig, __Out_O_startT305_93);

    if (!(IS_GUARD (6))) {
      RRC_RB_UE_O_O_startT305 ();
      SET_GUARD (6);
    }

    _Pause[0] |= 0x400;         /* PauseOn: #10 */
  } else {
    _Pause[0] |= 0x400;         /* PauseOn: #10 */
  }

  EMIT (_Sig, __Out_O_NAS_RB_RELEASE_Ind_86);
  _integer (&Out_O_NAS_RB_RELEASE_Ind_86, In_I_Radio_Bearer_ID_79);
  set_RRC_Transaction_ID ();
  encode_message (&Var_msg_107, RB_RELEASE_COMPLETE);
  EMIT (_Sig, __Out_O_SEND_DCCH_AM_91);

  if (!(IS_GUARD (8)))
    _integer (&Out_O_SEND_DCCH_AM_91, Var_msg_107);
  else
    _integer (&Out_O_SEND_DCCH_AM_91, INTEGER_COMBINE (Out_O_SEND_DCCH_AM_91, Var_msg_107));

  SET_GUARD (8);
  RRC_RB_UE_O_O_NAS_RB_RELEASE_Ind (Out_O_NAS_RB_RELEASE_Ind_86);
  _On[0] |= 0x4000;             /* On: #14 */
}

static void
Point_13 (void)
{
  printf("\n Inside Esterel FSM  Point_13 \n\n");

  /*#13 */
  if (!(IS_GUARD (0)))
    _boolean (&Sig_INVALID_CONFIGURATION_103, 1);
  else
    _boolean (&Sig_INVALID_CONFIGURATION_103, BOOLEAN_COMBINE (Sig_INVALID_CONFIGURATION_103, 1));

  SET_GUARD (0);
  set_RRC_Transaction_ID ();
  encode_message (&Var_msg_107, RB_RELEASE_FAILURE);
  EMIT (_Sig, __Out_O_SEND_DCCH_AM_91);

  if (!(IS_GUARD (8)))
    _integer (&Out_O_SEND_DCCH_AM_91, Var_msg_107);
  else
    _integer (&Out_O_SEND_DCCH_AM_91, INTEGER_COMBINE (Out_O_SEND_DCCH_AM_91, Var_msg_107));

  SET_GUARD (8);
  _On[0] |= 0x4000;             /* On: #14 */
  _Pause[0] |= 0x8000;          /* PauseOn: #15 */
}

static void
Point_14 (void)
{
  /*#14 */
  RRC_RB_UE_O_O_SEND_DCCH_AM (Out_O_SEND_DCCH_AM_91);
}

static void
Point_15 (void)
{
  printf("\n Inside Esterel FSM  Point_15 \n\n");

  /*#15 AutoPauseOn */
  if (IS_SIGNAL (_Sig, __In_I_RLC_Success_78)) {
    if (!(IS_GUARD (0)))
      _boolean (&Sig_INVALID_CONFIGURATION_103, 0);
    else
      _boolean (&Sig_INVALID_CONFIGURATION_103, BOOLEAN_COMBINE (Sig_INVALID_CONFIGURATION_103, 0));

    SET_GUARD (0);

    if (!(IS_GUARD (0)))
      _boolean (&Sig_ORDERED_RECONFIGURATION_102, 0);
    else
      _boolean (&Sig_ORDERED_RECONFIGURATION_102, BOOLEAN_COMBINE (Sig_ORDERED_RECONFIGURATION_102, 0));

    SET_GUARD (0);
    _On[0] &= ~0x8000;          /* Off: #15 */
    _Pause[0] |= 0x800;         /* PauseOn: #11 */
  }
}

static void
Point_16 (void)
{
  printf("\n Inside Esterel FSM  Point_16 \n\n");

  /*#16 AutoPauseOn */
  if (IS_SIGNAL (_Sig, __Sig_Go_CELL_DCH_104)) {
    EMIT (_Sig, __Out_O_New_State_CELL_DCH_94);

    if (!(IS_GUARD (5))) {
      RRC_RB_UE_O_O_New_State_CELL_DCH ();
      SET_GUARD (5);
    }

    EMIT (_Sig, __Sig_sc_go_36_CELL_DCH_109);
    _On[0] |= 0x80000;          /* On: #19 */
    _On[0] &= ~0x10000;         /* Off: #16 */
  } else {
    if (IS_SIGNAL (_Sig, __In_I_Go_CELL_DCH_82)) {
      EMIT (_Sig, __Sig_sc_go_36_CELL_DCH_109);
      _On[0] |= 0x80000;        /* On: #19 */
      _On[0] &= ~0x10000;       /* Off: #16 */
    } else {
      if (IS_SIGNAL (_Sig, __In_I_Go_CELL_PCH_84)) {
        EMIT (_Sig, __Sig_sc_go_42_CELL_PCH_110);
        _On[0] |= 0x80000;      /* On: #19 */
        _On[0] &= ~0x10000;     /* Off: #16 */
      }
    }
  }
}

static void
Point_17 (void)
{
  printf("\n Inside Esterel FSM  Point_17 \n\n");
  /*#17 AutoPauseOn */
  EMIT (_SigPre_0, __Sig_sc_in_RB_Management_DOT_CELL_DCH_97);
}

static void
Point_18 (void)
{
  printf("\n Inside Esterel FSM  Point_18 \n\n");

  /*#18 AutoPauseOn */
  if (IS_SIGNAL (_Sig, __Sig_Go_CELL_FACH_105)) {
    EMIT (_Sig, __Out_O_New_State_CELL_FACH_95);

    if (!(IS_GUARD (4))) {
      RRC_RB_UE_O_O_New_State_CELL_FACH ();
      SET_GUARD (4);
    }

    _On[0] |= 0x80000;          /* On: #19 */
    _On[0] &= ~0x40000;         /* Off: #18 */
    _Pause[0] &= ~0x20000;
    _On[0] &= ~0x20000;         /* PauseOff: #17 */
  } else {
    if (IS_SIGNAL (_Sig, __In_I_Go_CELL_FACH_83)) {
      _On[0] |= 0x80000;        /* On: #19 */
      _On[0] &= ~0x40000;       /* Off: #18 */
      _Pause[0] &= ~0x20000;
      _On[0] &= ~0x20000;       /* PauseOff: #17 */
    } else {
      if (IS_SIGNAL (_Sig, __In_I_Go_CELL_PCH_84)) {
        EMIT (_Sig, __Sig_sc_go_42_CELL_PCH_110);
        _On[0] |= 0x80000;      /* On: #19 */
        _On[0] &= ~0x40000;     /* Off: #18 */
        _Pause[0] &= ~0x20000;
        _On[0] &= ~0x20000;     /* PauseOff: #17 */
      }
    }
  }
}

static void
Point_19 (void)
{
  printf("\n Inside Esterel FSM  Point_19 \n\n");

  /*#19 */
  if (IS_SIGNAL (_Sig, __Sig_sc_go_42_CELL_PCH_110)) {
  } else {
    if (IS_SIGNAL (_Sig, __Sig_sc_go_36_CELL_DCH_109)) {
      EMIT (_SigPre_0, __Sig_sc_in_RB_Management_DOT_CELL_DCH_97);
      _Pause[0] |= 0x60000;     /* PauseOn: #17 #18 */
    } else {
      _Pause[0] |= 0x10000;     /* PauseOn: #16 */
    }
  }
}

static void
Point_20 (void)
{
  printf("\n Inside Esterel FSM  Point_20 \n\n");

  /*#20 AutoPauseOn */
  if (IS_SIGNAL (_Sig, __In_I_Go_CELL_FACH_83)) {
    SET_GUARD (1);
    _On[0] &= ~0x100000;        /* Off: #20 */
  } else {
    if (IS_SIGNAL (_Sig, __In_I_Go_CELL_DCH_82)) {
      SET_GUARD (1);
      EMIT (_Sig, __Sig_sc_go_36_CELL_DCH_109);
      _On[0] &= ~0x100000;      /* Off: #20 */
    }
  }

  if (IS_GUARD (1)) {
    if (IS_SIGNAL (_Sig, __Sig_sc_go_36_CELL_DCH_109)) {
      EMIT (_SigPre_0, __Sig_sc_in_RB_Management_DOT_CELL_DCH_97);
      _Pause[0] |= 0x60000;     /* PauseOn: #17 #18 */
    } else {
      _Pause[0] |= 0x10000;     /* PauseOn: #16 */
    }
  }
}

static void
Point_21 (void)
{
  printf("\n Inside Esterel FSM  Point_21 \n\n");

  /*#21 AutoPauseOn */
  if (IS_SIGNAL (_Sig, __In_I_Go_Idle_81)) {
    _On[0] &= ~0x200000;        /* Off: #21 */
    _Pause[0] &= ~0x179ef6;
    _On[0] &= ~0x178ef6;        /* PauseOff: #1 #2 #4 #5 #6 #7 #9 #10 #11 #12 #15 #16 #17 #18 #20 */

    if ((IS_SIGNAL (_Sig, __In_I_Go_CELL_DCH_82) || IS_SIGNAL (_Sig, __In_I_Go_CELL_FACH_83))) {
      _integer (&Var_next_state_108, 1);
      CLEAR_SIGNAL (_Sig, __Sig_sc_go_36_CELL_DCH_109);
      _Pause[0] |= 0x200812;    /* PauseOn: #1 #4 #11 #21 */

      if (IS_SIGNAL (_Sig, __In_I_Go_CELL_FACH_83)) {
        SET_GUARD (2);
      } else {
        if (IS_SIGNAL (_Sig, __In_I_Go_CELL_DCH_82)) {
          SET_GUARD (2);
          EMIT (_Sig, __Sig_sc_go_36_CELL_DCH_109);
        } else {
          _Pause[0] |= 0x100000;        /* PauseOn: #20 */
        }
      }

      if (IS_GUARD (2)) {
        if (IS_SIGNAL (_Sig, __Sig_sc_go_36_CELL_DCH_109)) {
          EMIT (_SigPre_0, __Sig_sc_in_RB_Management_DOT_CELL_DCH_97);
          _Pause[0] |= 0x60000; /* PauseOn: #17 #18 */
        } else {
          _Pause[0] |= 0x10000; /* PauseOn: #16 */
        }
      }
    } else {
      _Pause[0] |= 0x8;         /* PauseOn: #3 */
    }
  }
}


int
RRC_RB_UE (void)
{
  unsigned int   *Points;

  Points = _On;

  if (*Points) {
    if (*Points & 0x1) {
      Point_0 ();
    }

    if (*Points & 0x2) {
      Point_1 ();
    }

    if (*Points & 0x4) {
      Point_2 ();
    }

    if (*Points & 0x8) {
      Point_3 ();
    }

    if (*Points & 0x10) {
      Point_4 ();
    }

    if (*Points & 0x20) {
      Point_5 ();
    }

    if (*Points & 0x40) {
      Point_6 ();
    }

    if (*Points & 0x80) {
      Point_7 ();
    }

    if (*Points & 0x100) {
      Point_8 ();
    }

    if (*Points & 0x200) {
      Point_9 ();
    }

    if (*Points & 0x400) {
      Point_10 ();
    }

    if (*Points & 0x800) {
      Point_11 ();
    }

    if (*Points & 0x1000) {
      Point_12 ();
    }

    if (*Points & 0x2000) {
      Point_13 ();
    }

    if (*Points & 0x4000) {
      Point_14 ();
    }

    if (*Points & 0x8000) {
      Point_15 ();
    }

    if (*Points & 0x10000) {
      Point_16 ();
    }

    if (*Points & 0x20000) {
      Point_17 ();
    }

    if (*Points & 0x40000) {
      Point_18 ();
    }

    if (*Points & 0x80000) {
      Point_19 ();
    }

    if (*Points & 0x100000) {
      Point_20 ();
    }

    if (*Points & 0x200000) {
      Point_21 ();
    }
  }

  Points++;
  {
    int             j;
    unsigned int   *_tmp;

    _tmp = _SigPre_1;
    _SigPre_1 = _SigPre_0;
    _SigPre_0 = _tmp;

    for (j = 0; j < SIGNAL_WITH_PRE_VECTOR_SIZE; j++)
      _SigPre_0[j] = 0;

    for (j = 0; j < SIGNAL_VECTOR_SIZE; j++)
      _Sig[j] = 0;

    _On[0] = _Pause[0] | (_On[0] & 0x378efe);

    /* AutoPauseOn: #1 #2 #3 #4 #5 #6 #7 #9 #10 #11 #15 #16 #17 #18 #20 #21 */
    for (j = 0; j < HALT_POINT_VECTOR_SIZE; j++)
      _Pause[j] = 0;

    for (j = 0; j < GUARD_VECTOR_SIZE; j++)
      _Guard[j] = 0;
  }
  return Var__ThisIsTheEnd__114;
}

int
RRC_RB_UE_reset (void)
{
  int             i, j;

  for (j = 0; j < SIGNAL_VECTOR_SIZE; j++)
    _Sig[j] = 0;

  for (i = 0; i < GLOBALMAXPRELEVEL; i++)
    for (j = 0; j < SIGNAL_WITH_PRE_VECTOR_SIZE; j++)
      _SigPreTab[i][j] = 0;

  _boolean (&In_I_Prot_Error_73, 0);

  for (i = 0; i < HALT_POINT_VECTOR_SIZE; i++)
    _On[i] = 0;

  for (i = 0; i < HALT_POINT_VECTOR_SIZE; i++)
    _Pause[i] = 0;

  for (i = 0; i < GUARD_VECTOR_SIZE; i++)
    _Guard[i] = 0;

  BIT_SET (_On, 0);
  return 1;
}

typedef int     (*SimInitFunc_t) ();
int
RRC_RB_UE_init (char **pError, SimInitFunc_t pFunc)
{
  return 1;
}
typedef int     (*SimEndFunc_t) ();
int
RRC_RB_UE_end (SimEndFunc_t pFunc)
{
  return 1;
}

int
RRC_RB_UE_run (void)
{
  return RRC_RB_UE ();
}

int
RRC_RB_UE_getError (void)
{
  return 0;
}

char           *
RRC_RB_UE_getErrorMessage (void)
{
  return (char *) 0;
}
