/*
  \author R. Knopp, F. Kaltenberger
  \company EURECOM
  \email knopp@eurecom.fr
*/

#ifndef __openair_SCHED_H__
#define __openair_SCHED_H__

#include "PHY/defs.h"
#ifdef EMOS
#include "phy_procedures_emos.h"
#endif //EMOS

enum THREAD_INDEX { OPENAIR_THREAD_INDEX = 0,
		    TOP_LEVEL_SCHEDULER_THREAD_INDEX,
                    DLC_SCHED_THREAD_INDEX,
                    openair_SCHED_NB_THREADS}; // do not modify this line


#define OPENAIR_THREAD_PRIORITY        255


#define OPENAIR_THREAD_STACK_SIZE    8192 //4096 //RTL_PTHREAD_STACK_MIN*6
//#define DLC_THREAD_STACK_SIZE        4096 //DLC stack size




enum openair_SCHED_STATUS {
      openair_SCHED_STOPPED=1,
      openair_SCHED_STARTING,
      openair_SCHED_STARTED,
      openair_SCHED_STOPPING};

enum openair_ERROR {
  // HARDWARE CAUSES
  openair_ERROR_HARDWARE_CLOCK_STOPPED= 1,

  // SCHEDULER CAUSE
  openair_ERROR_OPENAIR_RUNNING_LATE,
  openair_ERROR_OPENAIR_SCHEDULING_FAILED,

  // OTHERS
  openair_ERROR_OPENAIR_TIMING_OFFSET_OUT_OF_BOUNDS,
};

enum openair_SYNCH_STATUS {
      openair_NOT_SYNCHED=1,
#ifdef OPENAIR_LTE
      openair_SYNCHED,
#else
      openair_SYNCHED_TO_CHSCH,
      openair_SYNCHED_TO_MRSCH,
#endif
      openair_SCHED_EXIT};


#define DAQ_AGC_ON 1
#define DAQ_AGC_OFF 0


typedef struct {
  u8 mode;
  u8 synch_source;
  u32  slot_count;
  u32  sched_cnt;
  u32  synch_wait_cnt;
  u32  sync_state;
  u32  scheduler_interval_ns;
  u32  last_adac_cnt;
  u8 first_sync_call;
  u32  instance_cnt;
  u8 one_shot_get_frame;
  u8 node_configured;  // &1..basic config, &3..ue config &5..eNb config
  u8 node_running;
  u8 tx_test;
  u8 mac_registered;
  u8 freq;
  u32  freq_info;
  u32  rx_gain_val;
  u32  rx_gain_mode;
  u32  tcxo_dac;
  u32  freq_offset;
  u32  tx_rx_switch_point;
  u32  manual_timing_advance;  /// 1 to override automatic timing advance
  u32  timing_advance;
  u32  dual_tx;                /// 1 for dual-antenna TX, 0 for single-antenna TX
  u32  tdd;                    /// 1 for TDD mode, 0 for FDD mode
  u32  rx_rf_mode;
  u32  node_id;
  u32  rach_detection_count;
  u32  channel_vacant[4];  
  u32  target_ue_dl_mcs;
  u32  target_ue_ul_mcs;
  u32  ue_ul_nb_rb;
  u32  dlsch_rate_adaptation;
  u32  dlsch_transmission_mode;
  u32  ulsch_allocation_mode;
  u32  rx_total_gain_dB;
} OPENAIR_DAQ_VARS;

#ifndef USER_MODE
u32 openair_sched_init(void);
void openair_sched_cleanup(void);
void openair_sched_exit(char *);
void openair1_restart(void);
#endif //USER_MODE

#ifdef OPENAIR_LTE
/** @addtogroup _PHY_PROCEDURES_
 * @{
 */


typedef enum {SF_DL, SF_UL, SF_S} lte_subframe_t;

/*!
  \brief Top-level entry routine for eNB procedures.  Called every slot by process scheduler. In even slots, it performs RX functions from previous subframe (if required).  On odd slots, it generate TX waveform for the following subframe.
  @param last_slot Index of last slot (0-19)
  @param next_slot Index of next_slot (0-19)
  @param phy_vars_eNB Pointer to eNB variables on which to act
  @param abstraction_flag Indicator of PHY abstraction
*/
void phy_procedures_eNb_lte(u8 last_slot, u8 next_slot,PHY_VARS_eNB *phy_vars_eNB,u8 abstraction_flag);
/*!
  \brief Top-level entry routine for UE procedures.  Called every slot by process scheduler. In even slots, it performs RX functions from previous subframe (if required).  On odd slots, it generate TX waveform for the following subframe.
  @param last_slot Index of last slot (0-19)
  @param next_slot Index of next_slot (0-19)
  @param phy_vars_ue Pointer to UE variables on which to act
  @param eNB_id ID of eNB on which to act
  @param abstraction_flag Indicator of PHY abstraction
*/
void phy_procedures_ue_lte(u8 last_slot, u8 next_slot,PHY_VARS_UE *phy_vars_ue,u8 eNB_id,u8 abstraction_flag);

/*!
  \brief Scheduling for UE TX procedures in normal subframes.  
  @param next_slot Index of next slot (0-19)
  @param phy_vars_ue Pointer to UE variables on which to act
  @param eNB_id Local id of eNB on which to act
  @param abstraction_flag Indicator of PHY abstraction
*/
void phy_procedures_UE_TX(u8 next_slot,PHY_VARS_UE *phy_vars_ue,u8 eNB_id,u8 abstraction_flag);
/*!
  \brief Scheduling for UE RX procedures in normal subframes.  
  @param last_slot Index of last slot (0-19)
  @param phy_vars_ue Pointer to UE variables on which to act
  @param eNB_id Local id of eNB on which to act
  @param abstraction_flag Indicator of PHY abstraction
*/
int phy_procedures_UE_RX(u8 last_slot,PHY_VARS_UE *phy_vars_ue,u8 eNB_id,u8 abstraction_flag);

/*!
  \brief Scheduling for UE TX procedures in TDD S-subframes.  
  @param next_slot Index of next slot (0-19)
  @param phy_vars_ue Pointer to UE variables on which to act
  @param eNB_id Local id of eNB on which to act
  @param abstraction_flag Indicator of PHY abstraction
*/
void phy_procedures_UE_S_TX(u8 next_slot,PHY_VARS_UE *phy_vars_ue,u8 eNB_id,u8 abstraction_flag);

/*!
  \brief Scheduling for UE RX procedures in TDD S-subframes.  
  @param last_slot Index of last slot (0-19)
  @param phy_vars_ue Pointer to UE variables on which to act
  @param eNB_id Local id of eNB on which to act
  @param abstraction_flag Indicator of PHY abstraction
*/
void phy_procedures_UE_S_RX(u8 last_slot,PHY_VARS_UE *phy_vars_ue,u8 eNB_id,u8 abstraction_flag);

/*!
  \brief Scheduling for eNB TX procedures in normal subframes.  
  @param next_slot Index of next slot (0-19)
  @param phy_vars_eNB Pointer to eNB variables on which to act
  @param abstraction_flag Indicator of PHY abstraction
*/
void phy_procedures_eNB_TX(u8 next_slot,PHY_VARS_eNB *phy_vars_eNB,u8 abstraction_flag);

/*!
  \brief Scheduling for eNB RX procedures in normal subframes.  
  @param last_slot Index of last slot (0-19)
  @param phy_vars_eNB Pointer to eNB variables on which to act
  @param abstraction_flag Indicator of PHY abstraction
*/
void phy_procedures_eNB_RX(u8 last_slot,PHY_VARS_eNB *phy_vars_eNB,u8 abstraction_flag);

/*!
  \brief Scheduling for eNB TX procedures in TDD S-subframes.  
  @param next_slot Index of next slot (0-19)
  @param phy_vars_eNB Pointer to eNB variables on which to act
  @param abstraction_flag Indicator of PHY abstraction
*/
void phy_procedures_eNB_S_TX(u8 next_slot,PHY_VARS_eNB *phy_vars_eNB,u8 abstraction_flag);

/*!
  \brief Scheduling for eNB RX procedures in TDD S-subframes.  
  @param last_slot Index of next slot (0-19)
  @param phy_vars_eNB Pointer to eNB variables on which to act
  @param abstraction_flag Indicator of PHY abstraction
*/
void phy_procedures_eNB_S_RX(u8 last_slot,PHY_VARS_eNB *phy_vars_eNB,u8 abstraction_flag);

/*!
  \brief Function to compute subframe type as a function of Frame type and TDD Configuration (implements Table 4.2.2 from 36.211, p.11 from version 8.6) and subframe index.
  @param frame_parms Pointer to DL frame parameter descriptor
  @param subframe Subframe index
  @returns Subframe type (DL,UL,S) 
*/
lte_subframe_t subframe_select(LTE_DL_FRAME_PARMS *frame_parms,u8 subframe);


/*!
  \brief Function to indicate PHICH transmission subframes.  Implements Table 9.1.2-1 for TDD.
  @param frame_parms Pointer to DL frame parameter descriptor
  @param subframe Subframe index
  @returns 1 if PHICH can be transmitted in subframe (always 1 for FDD)
*/
u32 is_phich_subframe(LTE_DL_FRAME_PARMS *frame_parms,u8 subframe);

/*!
  \brief Function to compute timing of RRCConnRequest transmission on UL-SCH (first UE transmission in RA procedure). This implements the timing in paragraph a) from Section 6.1.1 in 36.213 (p. 17 in version 8.6).  Used by eNB upon transmission of random-access response (RA_RNTI) to program corresponding ULSCH reception procedure.  Used by UE upon reception of random-access response (RA_RNTI) to program corresponding ULSCH transmission procedure.  This does not support the UL_delay field in RAR (always assumed to be 0).
  @param frame_parms Pointer to DL frame parameter descriptor
  @param current_subframe Index of subframe where RA_RNTI was received 
  @param current_frame Index of frame where RA_RNTI was received
  @param frame Frame index where RRCConnectionRequest is to be transmitted (n+6 mod 10 for FDD, different for TDD)
  @param subframe subframe index where RRCConnectionRequest is to be transmitted (n, n+1 or n+2)
*/
void get_RRCConnReq_alloc(LTE_DL_FRAME_PARMS *frame_parms,
			  u8 current_subframe, 
			  u32 current_frame,
			  u32 *frame,
			  u8 *subframe);
u8 get_RRCConnReq_harq_pid(LTE_DL_FRAME_PARMS *frame_parms,u8 current_subframe);




//
/*!
  \brief Compute ACK/NACK information for PUSCH/PUCCH for UE transmission in subframe n. This function implements table 10.1-1 of 36.213, p. 69.
  @param frame_parms Pointer to DL frame parameter descriptor
  @param harq_ack Pointer to dlsch_ue harq_ack status descriptor
  @param subframe Subframe for UE transmission (n in 36.213)
  @param o_ACK Pointer to ACK/NAK payload for PUCCH/PUSCH
  @returns status indicator for PUCCH/PUSCH transmission
*/
u8 get_ack(LTE_DL_FRAME_PARMS *frame_parms,harq_status_t *harq_ack,u8 subframe,u8 *o_ACK);

/*!
  \brief Compute UL ACK subframe from DL subframe. This is used to retrieve corresponding DLSCH HARQ pid at eNB upon reception of ACK/NAK information on PUCCH/PUSCH.  Derived from Table 10.1-1 in 36.213 (p. 69 in version 8.6)
  @param frame_parms Pointer to DL frame parameter descriptor
  @param subframe Subframe for UE transmission (n in 36.213)
  @param ACK_index TTI bundling index (0,1)
  @returns Subframe index for corresponding DL transmission
*/
u8 ul_ACK_subframe2_dl_subframe(LTE_DL_FRAME_PARMS *frame_parms,u8 subframe,u8 ACK_index);


s8 find_ue(u16 rnti, PHY_VARS_eNB *phy_vars_eNB);
s32 add_ue(s16 rnti, PHY_VARS_eNB *phy_vars_eNB);
s32 remove_ue(u16 rnti, PHY_VARS_eNB *phy_vars_eNB);

void process_timing_advance(u8 timing_advance);
void process_timing_advance_rar(PHY_VARS_UE *phy_vars_ue,u16 timing_advance);



/*!
  \brief This function retrieves the harq_pid of the corresponding DLSCH process and updates the error statistics of the DLSCH based on the received ACK info from UE along with the round index.  It also performs the fine-grain rate-adaptation based on the error statistics derived from the ACK/NAK process.
  @param UE_id Local UE index on which to act
  @param subframe Index of subframe
  @param phy_vars_eNB Pointer to eNB variables on which to act
*/
void process_HARQ_feedback(u8 UE_id, u8 subframe, PHY_VARS_eNB *phy_vars_eNB);

LTE_eNB_UE_stats* get_eNB_UE_stats(u8 Mod_id, u16 rnti);
int get_ue_active_harq_pid(u8 Mod_id,u16 rnti,u8 subframe,u8 *harq_pid,u8 *round,u8 ul_flag);


void dump_dlsch(PHY_VARS_UE *phy_vars_ue,u8 eNB_id,u8 subframe);
void dump_dlsch_SI(PHY_VARS_UE *phy_vars_ue,u8 eNB_id,u8 subframe);
void dump_dlsch_ra(PHY_VARS_UE *phy_vars_ue,u8 eNB_id,u8 subframe);


#else
#ifdef EMOS
void phy_procedures_emos(u8 last_slot);
#else
void phy_procedures(u8 last_slot,u8 abstraction_flag);
#endif //EMOS
/**@}*/
#endif //OPENAIR_LTE

#ifndef OPENAIR_LTE
u32 find_chbch(void);
u32 find_mrbch(void);
#endif

#endif

/*@}*/
