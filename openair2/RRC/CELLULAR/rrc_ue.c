/***************************************************************************
                            rrc_ue.c
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
#include "rrc_ue.h"
#define SIZEOFINT 32
#define B_SET_VECTOR_MASK(i) ((unsigned int)1 << i)
#define B_RES_VECTOR_MASK(i) (~((unsigned int)1 << i))
#define BIT_SET(b_vector, bit_number) (b_vector)[(bit_number) / SIZEOFINT] |= B_SET_VECTOR_MASK((bit_number) % SIZEOFINT)
#define BIT_RESET(b_vector, bit_number) (b_vector)[(bit_number) / SIZEOFINT] &= ~B_SET_VECTOR_MASK((bit_number) % SIZEOFINT)

#define IS_ON(point) (_On[point / SIZEOFINT] & B_SET_VECTOR_MASK(point % SIZEOFINT))
#define IS_PAUSE_ON(point) (_Pause[point / SIZEOFINT] & B_SET_VECTOR_MASK(point % SIZEOFINT))

#define HALT_POINT_NUM 43
#define HALT_POINT_VECTOR_SIZE ((HALT_POINT_NUM-1)/(int)SIZEOFINT)+1
static unsigned int _On[HALT_POINT_VECTOR_SIZE];
static unsigned int _Pause[HALT_POINT_VECTOR_SIZE];

#define SIGNAL_NUM 55
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
#ifndef SUCCESS
extern integer  SUCCESS;
#endif
#ifndef FAILURE
extern integer  FAILURE;
#endif
#ifndef ALREADY_C
extern integer  ALREADY_C;
#endif
#ifndef CELL_FACH
extern integer  CELL_FACH;
#endif
#ifndef CELL_DCH
extern integer  CELL_DCH;
#endif
#ifndef CELL_PCH
extern integer  CELL_PCH;
#endif
#ifndef RRC_CONN_REQ
extern integer  RRC_CONN_REQ;
#endif
#ifndef RRC_CONN_SETUP
extern integer  RRC_CONN_SETUP;
#endif
#ifndef RRC_CONN_SETUP_COMPLETE
extern integer  RRC_CONN_SETUP_COMPLETE;
#endif
#ifndef RRC_CONN_REL_COMPLETE
extern integer  RRC_CONN_REL_COMPLETE;
#endif
#ifndef RRC_CONN_RELEASE
extern integer  RRC_CONN_RELEASE;
#endif
#ifndef IDLE
extern integer  IDLE;
#endif
#ifndef N300
extern integer  N300;
#endif
#ifndef N308
extern integer  N308;
#endif
static boolean  Var__ThisIsTheEnd__157;
#define __Sig_sc_in_Connection_Management_DOT_Idle_117 0
#define __Sig_sc_in_Connection_Management_DOT_Connected_DOT_CELL_DCH_118 0
#define __Sig_sc_in_Connection_Management_DOT_Connected_DOT_CELL_FACH_119 1
#define __Sig_sc_go_5_CELL_DCH_138 1
static integer  Var_msg_142;
#define __Sig_sc_go_24_ConnReq_sent_141 2
static integer  Var_msg_143;
#define __Sig_sc_go_18_ConnSU_fail2_145 3
#define __Sig_sc_go_14_Timer_started_153 4
static integer  Sig_max_value_151;
#define __Sig_sc_go_14_Timer_started_156 5
static integer  Sig_max_value_154;
#define __Sig_sc_go_41_ConnRel_send_146 6
#define __Sig_sc_go_40_ConnRel_proc_148 7
static integer  Var_msg_147;
static integer  Var_msg_149;
static integer  Var_msg_150;
#define __Sig_Conn_Setup_End_136 8
static int      Sig_V308_135_Pre0 = 0;
static int      Sig_V308_135_Pre1 = 0;
static integer  Sig_V308_135[2];
#define __Sig_start_T308_133 9
static integer  Sig_start_T308_133;
static int      Sig_V300_132_Pre0 = 0;
static int      Sig_V300_132_Pre1 = 0;
static integer  Sig_V300_132[2];
#define __Sig_inc_V300_131 10
#define __Sig_start_T300_130 11
static integer  Sig_start_T300_130;
#define __Sig_Conn_Rel_Compl_Repeat_129 12
#define __Sig_Conn_Rel_Compl_Stop_128 13
#define __Sig_Conn_Request_Repeat_127 14
#define __Sig_Conn_Request_Stop_126 15
#define __Sig_Waiting_Connection_124 16
#define __Sig_Go_state_CELL_FACH_122 17
#define __Sig_Go_state_CELL_DCH_121 18
#define __Sig_Go_Idle_120 19
#define __Out_O_wait_116 20
static integer  Out_O_wait_116;
#define __Out_O_UpdateSI_852_115 21
#define __Out_O_startT308_114 22
#define __Out_O_stopT300_113 23
#define __Out_O_startT300_112 24
#define __Out_O_NAS_CONN_LOSS_IND_111 25
#define __Out_O_NAS_CONN_RELEASE_IND_110 26
#define __Out_O_NAS_CONN_ESTAB_RESP_109 27
static integer  Out_O_NAS_CONN_ESTAB_RESP_109;
#define __Out_O_SEND_DCCH_UM_108 28
static integer  Out_O_SEND_DCCH_UM_108;
#define __Out_O_SEND_DCCH_AM_107 29
static integer  Out_O_SEND_DCCH_AM_107;
#define __Out_O_SEND_CCCH_106 30
static integer  Out_O_SEND_CCCH_106;
#define __Out_O_Setup_FACHRACH_105 31
#define __Out_O_PHY_SYNCH_104 32
#define __In_I_Go_CELL_FACH_103 33
#define __In_I_Go_CELL_DCH_102 34
#define __In_I_WaitTimerExpired_101 35
#define __In_I_T308_TimeOut_100 36
#define __In_I_T300_TimeOut_99 37
#define __In_I_NAS_CONN_RELEASE_REQ_98 38
#define __In_I_NAS_CONN_ESTABLISHMENT_REQ_97 39
#define __In_I_RRC_CONNECTION_RELEASE_96 40
#define __In_I_RRC_CONNECTION_REJECT_95 41
#define __In_I_RRC_CONNECTION_SETUP_94 42
#define __In_I_RLC_Success_93 43
#define __In_I_RLC_Failure_92 44
#define __In_I_CPHY_CONNECTION_LOSS_91 45
#define __In_I_CPHY_SYNCH_IND_90 46
#define __In_I_CPHY_SYNCH_Failure_89 47
#define __In_I_rcved_on_CCCH_88 48
#define __In_I_rcved_on_DCCH_87 49
#define __In_I_Wait_Time_86 50
static integer  In_I_Wait_Time_86;
#define __In_I_IE_Freq_Info_85 51
#define __In_I_IE_RRC_State_84 52
static integer  In_I_IE_RRC_State_84;
#define __In_UE_ID_INIT_83 53
static integer  In_UE_ID_INIT_83;
#define __In_UE_ID_MSG_82 54
static integer  In_UE_ID_MSG_82;
#ifndef encode_message
extern void     encode_message (integer *, integer);
#endif
#ifndef Select_PRACH
extern void     Select_PRACH ();
#endif
#ifndef Select_Secondary_CCPCH
extern void     Select_Secondary_CCPCH ();
#endif
#ifndef Set_State
extern void     Set_State (integer, boolean);
#endif
#ifndef release_radio_resources
extern void     release_radio_resources ();
#endif
#ifndef clear_variables_rel
extern void     clear_variables_rel ();
#endif
#ifndef ue_clear_transaction
extern void     ue_clear_transaction (integer);
#endif
#ifndef INTEGER_COMBINE
extern integer  INTEGER_COMBINE (integer, integer);
#endif

extern void     RRC_UE_O_O_wait (integer);
extern void     RRC_UE_O_O_UpdateSI_852 (void);
extern void     RRC_UE_O_O_startT308 (void);
extern void     RRC_UE_O_O_stopT300 (void);
extern void     RRC_UE_O_O_startT300 (void);
extern void     RRC_UE_O_O_NAS_CONN_LOSS_IND (void);
extern void     RRC_UE_O_O_NAS_CONN_RELEASE_IND (void);
extern void     RRC_UE_O_O_NAS_CONN_ESTAB_RESP (integer);
extern void     RRC_UE_O_O_SEND_DCCH_UM (integer);
extern void     RRC_UE_O_O_SEND_DCCH_AM (integer);
extern void     RRC_UE_O_O_SEND_CCCH (integer);
extern void     RRC_UE_O_O_Setup_FACHRACH (void);
extern void     RRC_UE_O_O_PHY_SYNCH (void);
void
RRC_UE_I_I_Go_CELL_FACH (void)
{
  EMIT (_Sig, __In_I_Go_CELL_FACH_103);
}

void
RRC_UE_I_I_Go_CELL_DCH (void)
{
  EMIT (_Sig, __In_I_Go_CELL_DCH_102);
}

void
RRC_UE_I_I_WaitTimerExpired (void)
{
  EMIT (_Sig, __In_I_WaitTimerExpired_101);
}

void
RRC_UE_I_I_T308_TimeOut (void)
{
  EMIT (_Sig, __In_I_T308_TimeOut_100);
}

void
RRC_UE_I_I_T300_TimeOut (void)
{
  EMIT (_Sig, __In_I_T300_TimeOut_99);
}

void
RRC_UE_I_I_NAS_CONN_RELEASE_REQ (void)
{
  EMIT (_Sig, __In_I_NAS_CONN_RELEASE_REQ_98);
}

void
RRC_UE_I_I_NAS_CONN_ESTABLISHMENT_REQ (void)
{
  EMIT (_Sig, __In_I_NAS_CONN_ESTABLISHMENT_REQ_97);
}

void
RRC_UE_I_I_RRC_CONNECTION_RELEASE (void)
{
  EMIT (_Sig, __In_I_RRC_CONNECTION_RELEASE_96);
}

void
RRC_UE_I_I_RRC_CONNECTION_REJECT (void)
{
  EMIT (_Sig, __In_I_RRC_CONNECTION_REJECT_95);
}

void
RRC_UE_I_I_RRC_CONNECTION_SETUP (void)
{
  EMIT (_Sig, __In_I_RRC_CONNECTION_SETUP_94);
}

void
RRC_UE_I_I_RLC_Success (void)
{
  EMIT (_Sig, __In_I_RLC_Success_93);
}

void
RRC_UE_I_I_RLC_Failure (void)
{
  EMIT (_Sig, __In_I_RLC_Failure_92);
}

void
RRC_UE_I_I_CPHY_CONNECTION_LOSS (void)
{
  EMIT (_Sig, __In_I_CPHY_CONNECTION_LOSS_91);
}

void
RRC_UE_I_I_CPHY_SYNCH_IND (void)
{
  EMIT (_Sig, __In_I_CPHY_SYNCH_IND_90);
}

void
RRC_UE_I_I_CPHY_SYNCH_Failure (void)
{
  EMIT (_Sig, __In_I_CPHY_SYNCH_Failure_89);
}

void
RRC_UE_I_I_rcved_on_CCCH (void)
{
  EMIT (_Sig, __In_I_rcved_on_CCCH_88);
}

void
RRC_UE_I_I_rcved_on_DCCH (void)
{
  EMIT (_Sig, __In_I_rcved_on_DCCH_87);
}

void
RRC_UE_I_I_Wait_Time (integer value)
{
  EMIT (_Sig, __In_I_Wait_Time_86);
  _integer (&In_I_Wait_Time_86, value);
}

void
RRC_UE_I_I_IE_Freq_Info (void)
{
  EMIT (_Sig, __In_I_IE_Freq_Info_85);
}

void
RRC_UE_I_I_IE_RRC_State (integer value)
{
  EMIT (_Sig, __In_I_IE_RRC_State_84);
  _integer (&In_I_IE_RRC_State_84, value);
}

void
RRC_UE_I_UE_ID_INIT (integer value)
{
  EMIT (_Sig, __In_UE_ID_INIT_83);
  _integer (&In_UE_ID_INIT_83, value);
}

void
RRC_UE_I_UE_ID_MSG (integer value)
{
  EMIT (_Sig, __In_UE_ID_MSG_82);
  _integer (&In_UE_ID_MSG_82, value);
}

static void
Point_0 (void)
{
  /*#0 */
  _boolean (&Var__ThisIsTheEnd__157, 1);
  CLEAR_SIGNAL (_SigPre_0, __Sig_sc_in_Connection_Management_DOT_Connected_DOT_CELL_DCH_118);
  CLEAR_SIGNAL (_SigPre_1, __Sig_sc_in_Connection_Management_DOT_Connected_DOT_CELL_DCH_118);
  CLEAR_SIGNAL (_SigPre_0, __Sig_sc_in_Connection_Management_DOT_Connected_DOT_CELL_FACH_119);
  CLEAR_SIGNAL (_SigPre_1, __Sig_sc_in_Connection_Management_DOT_Connected_DOT_CELL_FACH_119);
  Set_State (IDLE, 0);
  _Pause[0] |= 0x2088011a;
  _Pause[1] |= 0x12;            /* PauseOn: #1 #3 #4 #8 #19 #23 #29 #33 #36 */
}

static void
Point_1 (void)
{
  /*#1 AutoPauseOn */
  if (IS_SIGNAL (_Sig, __In_I_NAS_CONN_RELEASE_REQ_98)) {
    if ((IS_SIGNAL (_SigPre_1, __Sig_sc_in_Connection_Management_DOT_Connected_DOT_CELL_FACH_119) || IS_SIGNAL (_SigPre_1, __Sig_sc_in_Connection_Management_DOT_Connected_DOT_CELL_DCH_118))) {
      encode_message (&Var_msg_150, RRC_CONN_RELEASE);
      EMIT (_Sig, __Out_O_SEND_DCCH_AM_107);

      if (!(IS_GUARD (9)))
        _integer (&Out_O_SEND_DCCH_AM_107, Var_msg_150);
      else
        _integer (&Out_O_SEND_DCCH_AM_107, INTEGER_COMBINE (Out_O_SEND_DCCH_AM_107, Var_msg_150));

      SET_GUARD (9);
      _On[0] |= 0x100000;       /* On: #20 */
      _On[0] &= ~0x2;           /* Off: #1 */
      _Pause[0] |= 0x4;         /* PauseOn: #2 */
    }
  }
}

static void
Point_2 (void)
{
  /*#2 AutoPauseOn */
  if ((IS_SIGNAL (_Sig, __In_I_RLC_Success_93) || IS_SIGNAL (_Sig, __In_I_RLC_Failure_92))) {
    release_radio_resources ();
    clear_variables_rel ();
    EMIT (_Sig, __Sig_Go_Idle_120);
    EMIT (_Sig, __Out_O_UpdateSI_852_115);

    if (!(IS_GUARD (1))) {
      RRC_UE_O_O_UpdateSI_852 ();
      SET_GUARD (1);
    }

    EMIT (_Sig, __Sig_Conn_Setup_End_136);
    _On[0] |= 0x1000000;        /* On: #24 */
    _On[0] &= ~0x4;             /* Off: #2 */
  }
}

static void
Point_3 (void)
{
  /*#3 AutoPauseOn */
  EMIT (_Sig, __Sig_sc_in_Connection_Management_DOT_Idle_117);
}

static void
Point_4 (void)
{
  /*#4 AutoPauseOn */
  if (IS_SIGNAL (_Sig, __In_I_NAS_CONN_ESTABLISHMENT_REQ_97)) {
    _On[0] |= 0x10000000;       /* On: #28 */
    _On[0] &= ~0x10;            /* Off: #4 */
  }
}

static void
Point_5 (void)
{
  /*#5 AutoPauseOn */
  if (IS_SIGNAL (_Sig, __In_I_WaitTimerExpired_101)) {
    EMIT (_Sig, __Sig_inc_V300_131);
    _On[0] |= 0x10000;          /* On: #16 */
    _On[0] &= ~0x20;            /* Off: #5 */
  }
}

static void
Point_6 (void)
{
  /*#6 */
  if (IS_SIGNAL (_Sig, __In_I_RRC_CONNECTION_REJECT_95)) {
    EMIT (_Sig, __Out_O_stopT300_113);

    if (!(IS_GUARD (3))) {
      RRC_UE_O_O_stopT300 ();
      SET_GUARD (3);
    }

    if (((In_I_Wait_Time_86 > 0) && (Sig_V300_132[Sig_V300_132_Pre1] <= N300))) {
      if (IS_SIGNAL (_Sig, __In_I_IE_Freq_Info_85)) {
        EMIT (_Sig, __Sig_sc_go_18_ConnSU_fail2_145);
        _On[0] |= 0x10000;      /* On: #16 */
      } else {
        EMIT (_Sig, __Out_O_wait_116);
        _integer (&Out_O_wait_116, In_I_Wait_Time_86);
        RRC_UE_O_O_wait (Out_O_wait_116);
        _Pause[0] |= 0x20;      /* PauseOn: #5 */
      }
    } else {
      EMIT (_Sig, __Sig_sc_go_18_ConnSU_fail2_145);
      _On[0] |= 0x10000;        /* On: #16 */
    }
  } else {
    if (IS_SIGNAL (_Sig, __In_I_RRC_CONNECTION_SETUP_94)) {
      EMIT (_Sig, __Out_O_stopT300_113);

      if (!(IS_GUARD (3))) {
        RRC_UE_O_O_stopT300 ();
        SET_GUARD (3);
      }

      _Pause[0] |= 0x80;        /* PauseOn: #7 */

      if (_eq_integer (In_I_IE_RRC_State_84, CELL_FACH)) {
        Select_PRACH ();
        Select_Secondary_CCPCH ();
      }

      EMIT (_Sig, __Out_O_PHY_SYNCH_104);

      if (!(IS_GUARD (12))) {
        RRC_UE_O_O_PHY_SYNCH ();
        SET_GUARD (12);
      }
    } else {
      _On[1] |= 0x80;           /* On: #39 */
    }
  }
}

static void
Point_7 (void)
{
  /*#7 AutoPauseOn */
  if (IS_SIGNAL (_Sig, __In_I_CPHY_SYNCH_Failure_89)) {
    _On[0] &= ~0x80;            /* Off: #7 */

    if ((Sig_V300_132[Sig_V300_132_Pre1] <= N300)) {
      EMIT (_Sig, __Sig_inc_V300_131);
      _On[0] |= 0x10000;        /* On: #16 */
    } else {
      EMIT (_Sig, __Sig_sc_go_18_ConnSU_fail2_145);
      _On[0] |= 0x10000;        /* On: #16 */
    }
  } else {
    if (IS_SIGNAL (_Sig, __In_I_CPHY_SYNCH_IND_90)) {
      _On[0] &= ~0x80;          /* Off: #7 */
      _Pause[0] |= 0x8000;      /* PauseOn: #15 */

      if (_eq_integer (In_I_IE_RRC_State_84, CELL_FACH)) {
        EMIT (_Sig, __Sig_Go_state_CELL_FACH_122);
      }

      if (_eq_integer (In_I_IE_RRC_State_84, CELL_DCH)) {
        EMIT (_Sig, __Sig_Go_state_CELL_DCH_121);
      }

      encode_message (&Var_msg_143, RRC_CONN_SETUP_COMPLETE);
      EMIT (_Sig, __Out_O_SEND_DCCH_AM_107);

      if (!(IS_GUARD (9)))
        _integer (&Out_O_SEND_DCCH_AM_107, Var_msg_143);
      else
        _integer (&Out_O_SEND_DCCH_AM_107, INTEGER_COMBINE (Out_O_SEND_DCCH_AM_107, Var_msg_143));

      SET_GUARD (9);
      _On[0] |= 0x100000;       /* On: #20 */
    }
  }
}

static void
Point_8 (void)
{
  /*#8 AutoPauseOn */
  if ((IS_SIGNAL (_Sig, __Sig_Go_state_CELL_DCH_121) || IS_SIGNAL (_Sig, __Sig_Go_state_CELL_FACH_122))) {
    CLEAR_SIGNAL (_Sig, __Sig_sc_go_5_CELL_DCH_138);
    _On[0] |= 0x200;            /* On: #9 */
    _On[0] &= ~0x100;           /* Off: #8 */
    _Pause[0] |= 0x8000000;     /* PauseOn: #27 */
    _Pause[0] &= ~0x8;
    _On[0] &= ~0x8;             /* PauseOff: #3 */
  }
}

static void
Point_9 (void)
{
  /*#9 AutoPauseOn */
  if (IS_SIGNAL (_Sig, __Sig_Go_state_CELL_FACH_122)) {
    SET_GUARD (0);
    _On[0] &= ~0x200;           /* Off: #9 */
  } else {
    if (IS_SIGNAL (_Sig, __Sig_Go_state_CELL_DCH_121)) {
      SET_GUARD (0);
      EMIT (_Sig, __Sig_sc_go_5_CELL_DCH_138);
      _On[0] &= ~0x200;         /* Off: #9 */
    }
  }

  if (IS_GUARD (0)) {
    if (IS_SIGNAL (_Sig, __Sig_sc_go_5_CELL_DCH_138)) {
      EMIT (_SigPre_0, __Sig_sc_in_Connection_Management_DOT_Connected_DOT_CELL_DCH_118);
      _Pause[0] |= 0xc00;       /* PauseOn: #10 #11 */

      if (IS_SIGNAL (_Sig, __In_I_Go_CELL_DCH_102)) {
        Set_State (CELL_DCH, 1);
      } else {
        Set_State (CELL_DCH, 0);
      }
    } else {
      EMIT (_SigPre_0, __Sig_sc_in_Connection_Management_DOT_Connected_DOT_CELL_FACH_119);
      _Pause[0] |= 0x3000;      /* PauseOn: #12 #13 */

      if (IS_SIGNAL (_Sig, __In_I_Go_CELL_FACH_103)) {
        Set_State (CELL_FACH, 1);
      } else {
        Set_State (CELL_FACH, 0);
      }
    }
  }
}

static void
Point_10 (void)
{
  /*#10 AutoPauseOn */
  EMIT (_SigPre_0, __Sig_sc_in_Connection_Management_DOT_Connected_DOT_CELL_DCH_118);
}

static void
Point_11 (void)
{
  /*#11 AutoPauseOn */
  if ((IS_SIGNAL (_Sig, __Sig_Go_state_CELL_FACH_122) || IS_SIGNAL (_Sig, __In_I_Go_CELL_FACH_103))) {
    _On[0] |= 0x4000;           /* On: #14 */
    _On[0] &= ~0x800;           /* Off: #11 */
    _Pause[0] &= ~0x400;
    _On[0] &= ~0x400;           /* PauseOff: #10 */
  }
}

static void
Point_12 (void)
{
  /*#12 AutoPauseOn */
  EMIT (_SigPre_0, __Sig_sc_in_Connection_Management_DOT_Connected_DOT_CELL_FACH_119);
}

static void
Point_13 (void)
{
  /*#13 AutoPauseOn */
  if ((IS_SIGNAL (_Sig, __Sig_Go_state_CELL_DCH_121) || IS_SIGNAL (_Sig, __In_I_Go_CELL_DCH_102))) {
    EMIT (_Sig, __Sig_sc_go_5_CELL_DCH_138);
    _On[0] |= 0x4000;           /* On: #14 */
    _On[0] &= ~0x2000;          /* Off: #13 */
    _Pause[0] &= ~0x1000;
    _On[0] &= ~0x1000;          /* PauseOff: #12 */
  }
}

static void
Point_14 (void)
{
  /*#14 */
  if (IS_SIGNAL (_Sig, __Sig_sc_go_5_CELL_DCH_138)) {
    EMIT (_SigPre_0, __Sig_sc_in_Connection_Management_DOT_Connected_DOT_CELL_DCH_118);
    _Pause[0] |= 0xc00;         /* PauseOn: #10 #11 */

    if (IS_SIGNAL (_Sig, __In_I_Go_CELL_DCH_102)) {
      Set_State (CELL_DCH, 1);
    } else {
      Set_State (CELL_DCH, 0);
    }
  } else {
    EMIT (_SigPre_0, __Sig_sc_in_Connection_Management_DOT_Connected_DOT_CELL_FACH_119);
    _Pause[0] |= 0x3000;        /* PauseOn: #12 #13 */

    if (IS_SIGNAL (_Sig, __In_I_Go_CELL_FACH_103)) {
      Set_State (CELL_FACH, 1);
    } else {
      Set_State (CELL_FACH, 0);
    }
  }
}

static void
Point_15 (void)
{
  /*#15 AutoPauseOn */
  if (IS_SIGNAL (_Sig, __In_I_RLC_Failure_92)) {
    EMIT (_Sig, __Sig_Go_Idle_120);
    EMIT (_Sig, __Sig_sc_go_18_ConnSU_fail2_145);
    _On[0] |= 0x10000;          /* On: #16 */
    _On[0] &= ~0x8000;          /* Off: #15 */
  } else {
    if (IS_SIGNAL (_Sig, __In_I_RLC_Success_93)) {
      EMIT (_Sig, __Out_O_NAS_CONN_ESTAB_RESP_109);

      if (!(IS_GUARD (7)))
        _integer (&Out_O_NAS_CONN_ESTAB_RESP_109, SUCCESS);
      else
        _integer (&Out_O_NAS_CONN_ESTAB_RESP_109, INTEGER_COMBINE (Out_O_NAS_CONN_ESTAB_RESP_109, SUCCESS));

      SET_GUARD (7);
      ue_clear_transaction (RRC_CONN_SETUP);
      EMIT (_Sig, __Sig_Conn_Setup_End_136);
      _On[1] |= 0x200;          /* On: #41 */
      _On[0] &= ~0x8000;        /* Off: #15 */
    }
  }
}

static void
Point_16 (void)
{
  /*#16 */
  if (IS_SIGNAL (_Sig, __Sig_sc_go_18_ConnSU_fail2_145)) {
    EMIT (_Sig, __Sig_Conn_Setup_End_136);
    EMIT (_Sig, __Out_O_UpdateSI_852_115);

    if (!(IS_GUARD (1))) {
      RRC_UE_O_O_UpdateSI_852 ();
      SET_GUARD (1);
    }

    EMIT (_Sig, __Out_O_NAS_CONN_ESTAB_RESP_109);

    if (!(IS_GUARD (7)))
      _integer (&Out_O_NAS_CONN_ESTAB_RESP_109, FAILURE);
    else
      _integer (&Out_O_NAS_CONN_ESTAB_RESP_109, INTEGER_COMBINE (Out_O_NAS_CONN_ESTAB_RESP_109, FAILURE));

    SET_GUARD (7);
    _On[1] |= 0x200;            /* On: #41 */
  } else {
    _Pause[0] |= 0x40;          /* PauseOn: #6 */
  }
}

static void
Point_17 (void)
{
  /*#17 */
  if (IS_SIGNAL (_Sig, __In_I_T308_TimeOut_100)) {
    if ((Sig_V308_135[Sig_V308_135_Pre1] > Sig_max_value_154)) {
      EMIT (_Sig, __Sig_Conn_Rel_Compl_Stop_128);
      _On[1] |= 0x4;            /* On: #34 */
    } else {
      EMIT (_Sig, __Sig_Conn_Rel_Compl_Repeat_129);
      _On[1] |= 0x1;            /* On: #32 */
    }
  } else {
    _On[0] |= 0x80000000;       /* On: #31 */
  }
}

static void
Point_18 (void)
{
  /*#18 AutoPauseOn */
  if (IS_SIGNAL (_Sig, __Sig_Conn_Rel_Compl_Repeat_129)) {
    EMIT (_Sig, __Sig_sc_go_41_ConnRel_send_146);
    _On[0] |= 0x400000;         /* On: #22 */
    _On[0] &= ~0x40000;         /* Off: #18 */
  } else {
    if (IS_SIGNAL (_Sig, __Sig_Conn_Rel_Compl_Stop_128)) {
      EMIT (_Sig, __Sig_sc_go_40_ConnRel_proc_148);
      _On[0] |= 0x400000;       /* On: #22 */
      _On[0] &= ~0x40000;       /* Off: #18 */
    }
  }
}

static void
Point_19 (void)
{
  /*#19 AutoPauseOn */
  if (IS_SIGNAL (_Sig, __In_I_RRC_CONNECTION_RELEASE_96)) {
    _On[0] &= ~0x80000;         /* Off: #19 */

    if (IS_SIGNAL (_SigPre_1, __Sig_sc_in_Connection_Management_DOT_Connected_DOT_CELL_FACH_119)) {
      if (IS_SIGNAL (_Sig, __In_I_rcved_on_CCCH_88)) {
        EMIT (_Sig, __Sig_sc_go_40_ConnRel_proc_148);
        _On[0] |= 0x400000;     /* On: #22 */
      } else {
        if (IS_SIGNAL (_Sig, __In_I_rcved_on_DCCH_87)) {
          encode_message (&Var_msg_147, RRC_CONN_REL_COMPLETE);
          EMIT (_Sig, __Out_O_SEND_DCCH_AM_107);

          if (!(IS_GUARD (9)))
            _integer (&Out_O_SEND_DCCH_AM_107, Var_msg_147);
          else
            _integer (&Out_O_SEND_DCCH_AM_107, INTEGER_COMBINE (Out_O_SEND_DCCH_AM_107, Var_msg_147));

          SET_GUARD (9);
          _On[0] |= 0x100000;   /* On: #20 */
          _Pause[0] |= 0x200000;        /* PauseOn: #21 */
        } else {
          _On[0] |= 0x400000;   /* On: #22 */
        }
      }
    } else {
      if (IS_SIGNAL (_SigPre_1, __Sig_sc_in_Connection_Management_DOT_Connected_DOT_CELL_DCH_118)) {
        encode_message (&Var_msg_147, RRC_CONN_REL_COMPLETE);
        EMIT (_Sig, __Sig_start_T308_133);
        _integer (&Sig_start_T308_133, N308);
        EMIT (_Sig, __Sig_sc_go_41_ConnRel_send_146);
        _On[0] |= 0x400000;     /* On: #22 */
      } else {
        _On[0] |= 0x400000;     /* On: #22 */
      }
    }
  }
}

static void
Point_20 (void)
{
  /*#20 */
  RRC_UE_O_O_SEND_DCCH_AM (Out_O_SEND_DCCH_AM_107);
}

static void
Point_21 (void)
{
  /*#21 AutoPauseOn */
  if ((IS_SIGNAL (_Sig, __In_I_RLC_Success_93) || IS_SIGNAL (_Sig, __In_I_RLC_Failure_92))) {
    EMIT (_Sig, __Sig_sc_go_40_ConnRel_proc_148);
    _On[0] |= 0x400000;         /* On: #22 */
    _On[0] &= ~0x200000;        /* Off: #21 */
  }
}

static void
Point_22 (void)
{
  /*#22 */
  if (IS_SIGNAL (_Sig, __Sig_sc_go_40_ConnRel_proc_148)) {
    release_radio_resources ();
    EMIT (_Sig, __Out_O_NAS_CONN_RELEASE_IND_110);

    if (!(IS_GUARD (6))) {
      RRC_UE_O_O_NAS_CONN_RELEASE_IND ();
      SET_GUARD (6);
    }

    clear_variables_rel ();
    EMIT (_Sig, __Sig_Go_Idle_120);
    EMIT (_Sig, __Out_O_UpdateSI_852_115);

    if (!(IS_GUARD (1))) {
      RRC_UE_O_O_UpdateSI_852 ();
      SET_GUARD (1);
    }

    EMIT (_Sig, __Sig_Conn_Setup_End_136);
    _On[0] |= 0x4000000;        /* On: #26 */
  } else {
    _On[0] |= 0x40000000;       /* On: #30 */
  }
}

static void
Point_23 (void)
{
  /*#23 AutoPauseOn */
  if (IS_SIGNAL (_Sig, __In_I_CPHY_CONNECTION_LOSS_91)) {
    release_radio_resources ();
    EMIT (_Sig, __Out_O_NAS_CONN_LOSS_IND_111);

    if (!(IS_GUARD (5))) {
      RRC_UE_O_O_NAS_CONN_LOSS_IND ();
      SET_GUARD (5);
    }

    clear_variables_rel ();
    EMIT (_Sig, __Out_O_UpdateSI_852_115);

    if (!(IS_GUARD (1))) {
      RRC_UE_O_O_UpdateSI_852 ();
      SET_GUARD (1);
    }

    EMIT (_Sig, __Sig_Conn_Setup_End_136);
    EMIT (_Sig, __Sig_Go_Idle_120);
    _On[0] |= 0x2000000;        /* On: #25 */
    _On[0] &= ~0x800000;        /* Off: #23 */
  }
}

static void
Point_24 (void)
{
  /*#24 AutoPauseOn */
  if (IS_SIGNAL (_Sig, __Sig_Conn_Setup_End_136)) {
    _On[0] &= ~0x1000000;       /* Off: #24 */
    _Pause[0] |= 0x2;           /* PauseOn: #1 */
  }
}

static void
Point_25 (void)
{
  /*#25 AutoPauseOn */
  if (IS_SIGNAL (_Sig, __Sig_Conn_Setup_End_136)) {
    _On[0] &= ~0x2000000;       /* Off: #25 */
    _Pause[0] |= 0x800000;      /* PauseOn: #23 */
  }
}

static void
Point_26 (void)
{
  /*#26 AutoPauseOn */
  if (IS_SIGNAL (_Sig, __Sig_Conn_Setup_End_136)) {
    _On[0] |= 0x40000000;       /* On: #30 */
    _On[0] &= ~0x4000000;       /* Off: #26 */
  }
}

static void
Point_27 (void)
{
  /*#27 AutoPauseOn */
  if (IS_SIGNAL (_Sig, __Sig_Go_Idle_120)) {
    Set_State (IDLE, 0);
    EMIT (_Sig, __Sig_sc_in_Connection_Management_DOT_Idle_117);
    _On[0] &= ~0x8000000;       /* Off: #27 */
    _Pause[0] |= 0x108;         /* PauseOn: #3 #8 */
    _Pause[0] &= ~0x3e00;
    _On[0] &= ~0x3e00;          /* PauseOff: #9 #10 #11 #12 #13 */
  }
}

static void
Point_28 (void)
{
  /*#28 AutoPauseOn */
  if (IS_SIGNAL (_Sig, __Sig_sc_in_Connection_Management_DOT_Idle_117)) {
    EMIT (_Sig, __Out_O_Setup_FACHRACH_105);

    if (!(IS_GUARD (11))) {
      RRC_UE_O_O_Setup_FACHRACH ();
      SET_GUARD (11);
    }

    encode_message (&Var_msg_142, RRC_CONN_REQ);
    EMIT (_Sig, __Sig_Waiting_Connection_124);
    EMIT (_Sig, __Sig_start_T300_130);
    _integer (&Sig_start_T300_130, N300);
    EMIT (_Sig, __Sig_sc_go_24_ConnReq_sent_141);
    _On[1] |= 0x400;            /* On: #42 */
    _On[0] &= ~0x10000000;      /* Off: #28 */
  } else {
    if ((!IS_SIGNAL (_Sig, __Sig_sc_in_Connection_Management_DOT_Idle_117))) {
      EMIT (_Sig, __Out_O_NAS_CONN_ESTAB_RESP_109);

      if (!(IS_GUARD (7)))
        _integer (&Out_O_NAS_CONN_ESTAB_RESP_109, ALREADY_C);
      else
        _integer (&Out_O_NAS_CONN_ESTAB_RESP_109, INTEGER_COMBINE (Out_O_NAS_CONN_ESTAB_RESP_109, ALREADY_C));

      SET_GUARD (7);
      _On[1] |= 0x600;          /* On: #41 #42 */
      _On[0] &= ~0x10000000;    /* Off: #28 */
    }
  }
}

static void
Point_29 (void)
{
  /*#29 AutoPauseOn */
  if (IS_SIGNAL (_Sig, __Sig_Waiting_Connection_124)) {
    _On[1] |= 0x100;            /* On: #40 */
    _On[0] &= ~0x20000000;      /* Off: #29 */
    _Pause[0] |= 0x40;          /* PauseOn: #6 */
  }
}

static void
Point_30 (void)
{
  /*#30 */
  if (IS_SIGNAL (_Sig, __Sig_sc_go_41_ConnRel_send_146)) {
    EMIT (_Sig, __Out_O_SEND_DCCH_UM_108);

    if (!(IS_GUARD (8)))
      _integer (&Out_O_SEND_DCCH_UM_108, Var_msg_147);
    else
      _integer (&Out_O_SEND_DCCH_UM_108, INTEGER_COMBINE (Out_O_SEND_DCCH_UM_108, Var_msg_147));

    SET_GUARD (8);
    EMIT (_Sig, __Out_O_startT308_114);

    if (!(IS_GUARD (2))) {
      RRC_UE_O_O_startT308 ();
      SET_GUARD (2);
    }

    RRC_UE_O_O_SEND_DCCH_UM (Out_O_SEND_DCCH_UM_108);
    _Pause[0] |= 0x40000;       /* PauseOn: #18 */
  } else {
    _Pause[0] |= 0x80000;       /* PauseOn: #19 */
  }
}

static void
Point_31 (void)
{
  /*#31 */
  if (IS_SIGNAL (_Sig, __Sig_Conn_Setup_End_136)) {
    _On[1] |= 0x4;              /* On: #34 */
  } else {
    _Pause[0] |= 0x20000;       /* PauseOn: #17 */
  }
}

static void
Point_32 (void)
{
  /*#32 */
  Sig_V308_135_Pre0 = Sig_V308_135_Pre1 ^ 1;
  _integer (&Sig_V308_135[Sig_V308_135_Pre0], (Sig_V308_135[Sig_V308_135_Pre1] + 1));
  EMIT (_Sig, __Sig_sc_go_14_Timer_started_156);
  _On[1] |= 0x4;                /* On: #34 */
}

static void
Point_33 (void)
{
  /*#33 AutoPauseOn */
  if (IS_SIGNAL (_Sig, __Sig_start_T308_133)) {
    Sig_V308_135_Pre0 = Sig_V308_135_Pre1 ^ 1;
    _integer (&Sig_V308_135[Sig_V308_135_Pre0], 1);
    _integer (&Sig_max_value_154, Sig_start_T308_133);
    EMIT (_Sig, __Sig_sc_go_14_Timer_started_156);
    _On[1] |= 0x4;              /* On: #34 */
    _On[1] &= ~0x2;             /* Off: #33 */
  }
}

static void
Point_34 (void)
{
  /*#34 */
  if (IS_SIGNAL (_Sig, __Sig_sc_go_14_Timer_started_156)) {
    _Pause[0] |= 0x20000;       /* PauseOn: #17 */
  } else {
    _Pause[1] |= 0x2;           /* PauseOn: #33 */
  }
}

static void
Point_35 (void)
{
  /*#35 AutoPauseOn */
  if ((IS_SIGNAL (_Sig, __In_I_T300_TimeOut_99) || IS_SIGNAL (_Sig, __Sig_inc_V300_131))) {
    _On[1] &= ~0x8;             /* Off: #35 */

    if ((Sig_V300_132[Sig_V300_132_Pre1] > Sig_max_value_151)) {
      EMIT (_Sig, __Sig_Conn_Request_Stop_126);
      _On[1] |= 0x20;           /* On: #37 */
    } else {
      EMIT (_Sig, __Sig_Conn_Request_Repeat_127);
      Sig_V300_132_Pre0 = Sig_V300_132_Pre1 ^ 1;
      _integer (&Sig_V300_132[Sig_V300_132_Pre0], (Sig_V300_132[Sig_V300_132_Pre1] + 1));
      EMIT (_Sig, __Sig_sc_go_14_Timer_started_153);
      _On[1] |= 0x20;           /* On: #37 */
    }
  } else {
    if (IS_SIGNAL (_Sig, __Sig_Conn_Setup_End_136)) {
      _On[1] |= 0x20;           /* On: #37 */
      _On[1] &= ~0x8;           /* Off: #35 */
    }
  }
}

static void
Point_36 (void)
{
  /*#36 AutoPauseOn */
  if (IS_SIGNAL (_Sig, __Sig_start_T300_130)) {
    Sig_V300_132_Pre0 = Sig_V300_132_Pre1 ^ 1;
    _integer (&Sig_V300_132[Sig_V300_132_Pre0], 1);
    _integer (&Sig_max_value_151, Sig_start_T300_130);
    EMIT (_Sig, __Sig_sc_go_14_Timer_started_153);
    _On[1] |= 0x20;             /* On: #37 */
    _On[1] &= ~0x10;            /* Off: #36 */
  }
}

static void
Point_37 (void)
{
  /*#37 */
  if (IS_SIGNAL (_Sig, __Sig_sc_go_14_Timer_started_153)) {
    _Pause[1] |= 0x8;           /* PauseOn: #35 */
  } else {
    _Pause[1] |= 0x10;          /* PauseOn: #36 */
  }
}

static void
Point_38 (void)
{
  /*#38 AutoPauseOn */
  if (IS_SIGNAL (_Sig, __Sig_Conn_Request_Repeat_127)) {
    EMIT (_Sig, __Sig_sc_go_24_ConnReq_sent_141);
    _On[1] |= 0x400;            /* On: #42 */
    _On[1] &= ~0x40;            /* Off: #38 */
  } else {
    if (IS_SIGNAL (_Sig, __Sig_Conn_Request_Stop_126)) {
      _On[1] |= 0x400;          /* On: #42 */
      _On[1] &= ~0x40;          /* Off: #38 */
    } else {
      if (IS_SIGNAL (_Sig, __Sig_Conn_Setup_End_136)) {
        _On[1] |= 0x400;        /* On: #42 */
        _On[1] &= ~0x40;        /* Off: #38 */
      }
    }
  }
}

static void
Point_39 (void)
{
  /*#39 */
  if (IS_SIGNAL (_Sig, __Sig_Conn_Request_Stop_126)) {
    EMIT (_Sig, __Out_O_NAS_CONN_ESTAB_RESP_109);

    if (!(IS_GUARD (7)))
      _integer (&Out_O_NAS_CONN_ESTAB_RESP_109, FAILURE);
    else
      _integer (&Out_O_NAS_CONN_ESTAB_RESP_109, INTEGER_COMBINE (Out_O_NAS_CONN_ESTAB_RESP_109, FAILURE));

    SET_GUARD (7);
    _On[1] |= 0x200;            /* On: #41 */
  } else {
    _Pause[0] |= 0x40;          /* PauseOn: #6 */
  }
}

static void
Point_40 (void)
{
  /*#40 AutoPauseOn */
  if ((IS_SIGNAL (_Sig, __Sig_Conn_Setup_End_136) || IS_SIGNAL (_Sig, __Sig_Conn_Request_Stop_126))) {
    _On[1] &= ~0x100;           /* Off: #40 */
    _Pause[0] |= 0x20000000;    /* PauseOn: #29 */
    _Pause[0] &= ~0x80e0;
    _On[0] &= ~0x80a0;          /* PauseOff: #5 #6 #7 #15 */
  }
}

static void
Point_41 (void)
{
  /*#41 */
  RRC_UE_O_O_NAS_CONN_ESTAB_RESP (Out_O_NAS_CONN_ESTAB_RESP_109);
}

static void
Point_42 (void)
{
  /*#42 */
  if (IS_SIGNAL (_Sig, __Sig_sc_go_24_ConnReq_sent_141)) {
    EMIT (_Sig, __Out_O_SEND_CCCH_106);

    if (!(IS_GUARD (10)))
      _integer (&Out_O_SEND_CCCH_106, Var_msg_142);
    else
      _integer (&Out_O_SEND_CCCH_106, INTEGER_COMBINE (Out_O_SEND_CCCH_106, Var_msg_142));

    SET_GUARD (10);
    EMIT (_Sig, __Out_O_startT300_112);

    if (!(IS_GUARD (4))) {
      RRC_UE_O_O_startT300 ();
      SET_GUARD (4);
    }

    RRC_UE_O_O_SEND_CCCH (Out_O_SEND_CCCH_106);
    _Pause[1] |= 0x40;          /* PauseOn: #38 */
  } else {
    _Pause[0] |= 0x10;          /* PauseOn: #4 */
  }
}


int
RRC_UE (void)
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

    if (*Points & 0x400000) {
      Point_22 ();
    }

    if (*Points & 0x800000) {
      Point_23 ();
    }

    if (*Points & 0x1000000) {
      Point_24 ();
    }

    if (*Points & 0x2000000) {
      Point_25 ();
    }

    if (*Points & 0x4000000) {
      Point_26 ();
    }

    if (*Points & 0x8000000) {
      Point_27 ();
    }

    if (*Points & 0x10000000) {
      Point_28 ();
    }

    if (*Points & 0x20000000) {
      Point_29 ();
    }

    if (*Points & 0x40000000) {
      Point_30 ();
    }

    if (*Points & 0x80000000) {
      Point_31 ();
    }
  }

  Points++;

  if (*Points) {
    if (*Points & 0x1) {
      Point_32 ();
    }

    if (*Points & 0x2) {
      Point_33 ();
    }

    if (*Points & 0x4) {
      Point_34 ();
    }

    if (*Points & 0x8) {
      Point_35 ();
    }

    if (*Points & 0x10) {
      Point_36 ();
    }

    if (*Points & 0x20) {
      Point_37 ();
    }

    if (*Points & 0x40) {
      Point_38 ();
    }

    if (*Points & 0x80) {
      Point_39 ();
    }

    if (*Points & 0x100) {
      Point_40 ();
    }

    if (*Points & 0x200) {
      Point_41 ();
    }

    if (*Points & 0x400) {
      Point_42 ();
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

    Sig_V308_135_Pre1 = Sig_V308_135_Pre0;
    Sig_V300_132_Pre1 = Sig_V300_132_Pre0;
    _On[0] = _Pause[0] | (_On[0] & 0x3facbfbe);
    _On[1] = _Pause[1] | (_On[1] & 0x15a);

    /* AutoPauseOn: #1 #2 #3 #4 #5 #7 #8 #9 #10 #11 #12 #13 #15 #18 #19 #21 #23 #24 #25 #26 #27 #28 #29 #33 #35 #36 #38 #40 */
    for (j = 0; j < HALT_POINT_VECTOR_SIZE; j++)
      _Pause[j] = 0;

    for (j = 0; j < GUARD_VECTOR_SIZE; j++)
      _Guard[j] = 0;
  }
  return Var__ThisIsTheEnd__157;
}

int
RRC_UE_reset (void)
{
  int             i, j;

  for (j = 0; j < SIGNAL_VECTOR_SIZE; j++)
    _Sig[j] = 0;

  for (i = 0; i < GLOBALMAXPRELEVEL; i++)
    for (j = 0; j < SIGNAL_WITH_PRE_VECTOR_SIZE; j++)
      _SigPreTab[i][j] = 0;

  _integer (&In_UE_ID_INIT_83, 33);

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
RRC_UE_init (char **pError, SimInitFunc_t pFunc)
{
  return 1;
}
typedef int     (*SimEndFunc_t) ();
int
RRC_UE_end (SimEndFunc_t pFunc)
{
  return 1;
}

int
RRC_UE_run (void)
{
  return RRC_UE ();
}

int
RRC_UE_getError (void)
{
  return 0;
}

char           *
RRC_UE_getErrorMessage (void)
{
  return (char *) 0;
}
