% file: struct_template.m
% author: florian.kaltenberger@eurecom.fr
% date: 13.3.2010
% purpose: this file reconstructs the structures fifo_dump_emos_struct_UE
%          and fifo_dump_emos_struct_UE which are defined in
%          SCHED/phy_procedures_emos.h


NUMBER_OF_OFDM_CARRIERS_EMOS = 512; 
NUMBER_OF_USEFUL_CARRIERS_EMOS = 300;

N_RB_UL_EMOS = 25;
N_PILOTS_DL_EMOS = 2;  % ofdm symbols with pilots per slot
N_PILOTS_UL_EMOS = 2;  % ofdm symbols with pilots per subframe
N_SLOTS_DL_EMOS = 2;     % we take slots 10,11
N_SUBFRAMES_UL_EMOS = 1;     % we take subframes 3
NB_ANTENNAS_TX_EMOS = 2;
NB_ANTENNAS_RX_EMOS = 2;


MAX_DCI_PER_FRAME = 20;
MAX_UCI_PER_FRAME = 20;

PBCH_PDU_SIZE = 6;

NUMBER_OF_eNB_MAX = 3;
NUMBER_OF_UE_MAX = 2;
NUMBER_OF_SUBBANDS = 13;

NB_ANTENNAS_RX = 2;
NB_ANTENNAS_TX = 2;

MAX_CQI_BITS = 40;
MAX_DCI_SIZE_BITS = 45;

%EMOS_CHANNEL = 0;

% enable this line to enable error checking
if isunix
  get_dump_size
else
  warning('Error checking of sizes only possible in Linux');
end

phy_measurements_struct = struct(...
    'rssi',                 uint32(0),...
    'n_adj_cells',          int32(0),...
    'n_adj_cells_id',       uint32(zeros(1,6)),...
    'rsrq',                 uint32(zeros(1,7)),...
    'rsrp',                 uint32(zeros(1,7)),...
    'rsrp_filtered',        single(zeros(1,7)),...
    'rsrq_filtered',        single(zeros(1,7)),...
    'n0_power',             uint32(zeros(1,NB_ANTENNAS_RX)),...
    'n0_power_dB',          uint16(zeros(1,NB_ANTENNAS_RX)),...
    'n0_power_tot',         uint32(0),...
    'n0_power_tot_dB',      uint16(0),...
    'n0_power_avg',         uint32(0),...
    'n0_power_avg_dB',      uint16(0),...
    'n0_power_tot_dBm',     int16(0),...
    'rx_spatial_power',     int32(zeros(2,2,NUMBER_OF_eNB_MAX)),...
    'rx_spatial_power_dB',  uint16(zeros(2,2,NUMBER_OF_eNB_MAX)),...
    'rx_power',             int32(zeros(NB_ANTENNAS_RX,NUMBER_OF_eNB_MAX)),...
    'rx_power_dB',          uint16(zeros(NB_ANTENNAS_RX,NUMBER_OF_eNB_MAX)),...
    'rx_power_tot',         int32(zeros(1,NUMBER_OF_eNB_MAX)),...
    'rx_power_tot_dB',      uint16(zeros(1,NUMBER_OF_eNB_MAX)),...
    'rx_power_avg',         int32(zeros(1,NUMBER_OF_eNB_MAX)),...
    'rx_power_avg_dB',      uint16(zeros(1,NUMBER_OF_eNB_MAX)),...
    'wideband_cqi_tot',     int32(zeros(1,NUMBER_OF_eNB_MAX)),...
    'wideband_cqi_avg',     int32(zeros(1,NUMBER_OF_eNB_MAX)),...
    'rx_rssi_dBm',          int16(zeros(1,NUMBER_OF_eNB_MAX)),...
    'rx_correlation',       int32(zeros(2,NUMBER_OF_eNB_MAX)),...
    'rx_correlation_dB',    int32(zeros(2,NUMBER_OF_eNB_MAX)),...
    'precoded_cqi_dB',      int32(zeros(4,NUMBER_OF_eNB_MAX+1)),...
    'subband_cqi',          int32(zeros(NUMBER_OF_SUBBANDS,NB_ANTENNAS_RX,NUMBER_OF_eNB_MAX)),...
    'subband_cqi_tot',      int32(zeros(NUMBER_OF_SUBBANDS,NUMBER_OF_eNB_MAX)),...
    'subband_cqi_dB',       int32(zeros(NUMBER_OF_SUBBANDS,NB_ANTENNAS_RX,NUMBER_OF_eNB_MAX)),...
    'subband_cqi_tot_dB',   int32(zeros(NUMBER_OF_SUBBANDS,NUMBER_OF_eNB_MAX)),...
    'wideband_pmi_re',      int32(zeros(NB_ANTENNAS_RX,NUMBER_OF_eNB_MAX)),...
    'wideband_pmi_im',      int32(zeros(NB_ANTENNAS_RX,NUMBER_OF_eNB_MAX)),...
    'subband_pmi_re',       int32(zeros(NB_ANTENNAS_RX,NUMBER_OF_SUBBANDS,NUMBER_OF_eNB_MAX)),...
    'subband_pmi_im',       int32(zeros(NB_ANTENNAS_RX,NUMBER_OF_SUBBANDS,NUMBER_OF_eNB_MAX)),...
    'selected_rx_antennas', int8(zeros(NUMBER_OF_SUBBANDS,NUMBER_OF_eNB_MAX)),...
    'rank',                 uint8(zeros(1,NUMBER_OF_eNB_MAX)),...
    'nb_antennas_rx',       uint8(0));


phy_measurements_struct_a = cstruct(phy_measurements_struct,[],align);
if (exist('PHY_measurements_size','var') && (phy_measurements_struct_a.size ~= PHY_measurements_size))
    warning('PHY_measurements_size does not match');
end

phy_measurements_eNb_struct = struct(...
    'n0_power',             uint32(zeros(1,NB_ANTENNAS_RX)),...
    'n0_power_dB',          uint16(zeros(1,NB_ANTENNAS_RX)),...
    'n0_power_tot',         uint32(0),...
    'n0_power_tot_dB',      uint16(0),...
    'n0_power_tot_dBm',     int16(0),...
    'n0_subband_power',     uint16(zeros(N_RB_UL_EMOS,NB_ANTENNAS_RX)),...
    'n0_subband_power_dB',  uint16(zeros(N_RB_UL_EMOS,NB_ANTENNAS_RX)),...
    'n0_subband_power_tot_dB', int16(zeros(1,N_RB_UL_EMOS)),...
    'n0_subband_power_tot_dBm', int16(zeros(1,N_RB_UL_EMOS)),...
    'rx_spatial_power',     uint32(zeros(2,2,NUMBER_OF_UE_MAX)),...
    'rx_spatial_power_dB',  uint16(zeros(2,2,NUMBER_OF_UE_MAX)),...
    'rx_rssi_dBm',          int16(zeros(1,NUMBER_OF_UE_MAX)),...
    'rx_correlation',       int32(zeros(2,NUMBER_OF_UE_MAX)),...
    'rx_correlation_dB',    int32(zeros(2,NUMBER_OF_UE_MAX)),...
    'wideband_cqi',         int32(zeros(NB_ANTENNAS_RX,NUMBER_OF_UE_MAX)),...
    'wideband_cqi_dB',      int32(zeros(NB_ANTENNAS_RX,NUMBER_OF_UE_MAX)),...
    'wideband_cqi_tot',     int8(zeros(1,NUMBER_OF_UE_MAX)),...
    'subband_cqi',          int32(zeros(N_RB_UL_EMOS,NB_ANTENNAS_RX,NUMBER_OF_UE_MAX)),...
    'subband_cqi_tot',      int32(zeros(N_RB_UL_EMOS,NUMBER_OF_UE_MAX)),...
    'subband_cqi_dB',       int32(zeros(N_RB_UL_EMOS,NB_ANTENNAS_RX,NUMBER_OF_UE_MAX)),...
    'subband_cqi_tot_dB',   int32(zeros(N_RB_UL_EMOS,NUMBER_OF_UE_MAX)));

phy_measurements_eNb_struct_a = cstruct(phy_measurements_eNb_struct,[],align);
if (exist('PHY_measurements_eNb_size','var') && (phy_measurements_eNb_struct_a.size ~= PHY_measurements_eNb_size))
    warning('PHY_measurements_eNb_size does not match');
end

uci_data_struct = struct(...
    'o',uint8(zeros(1,MAX_CQI_BITS)),...
    'O',uint8(0),...
    'o_RI',uint8(zeros(1,2)),...
    'O_RI',uint8(0),...
    'o_ACK',uint8(zeros(1,4)),...
    'O_ACK',uint8(0));

uci_data_struct_a = cstruct(uci_data_struct,[],align);
if (exist('UCI_data_t_size','var') && (uci_data_struct_a.size ~= UCI_data_t_size))
    warning('UCI_data_t_size does not match');
end


dci_alloc_struct = struct(...
    'dci_length',uint8(0),...
    'L',uint8(0),...
    'rnti',uint16(0),...
    'format',uint32(0),...
    'dci_pdu',uint16(zeros(1,1+floor(MAX_DCI_SIZE_BITS/16))));

% this one does not work unfortunately
% dci_alloc_struct = struct(...
%     'dci_length',uint8(0),...
%     'L',uint8(0),...
%     'rnti',uint16(0),...
%     'format',uint32(0),...
%     'rah',logical(0),...
%     'rballoc',logical(zeros(1,13)),...
%     'TPC',logical(zeros(1,2)),... %16
%     
%     'dai',logical(zeros(1,2)),... 1:2
%     'harq_pid',logical(zeros(1,4)),... 3:6
%     'tb_swap',logical(0),... 7
%     'mcs1',logical(zeros(1,5)),... 8:12 
%     'ndi1',logical(0),... 13
%     'rv1',logical(zeros(1,2)),... 14:15
%     'tpmi',logical(zeros(1,3)),... 16:17:...
%     'mcs2',logical(zeros(1,5)),...
%     'ndi2',logical(0),...
%     'rv2',logical(zeros(1,2)),...
%     'padding',logical(zeros(1,6)));

dci_alloc_struct_a = cstruct(dci_alloc_struct,[],align);
if (exist('DCI_alloc_t_size','var') && (dci_alloc_struct_a.size ~= DCI_alloc_t_size))
    warning('DCI_alloc_t_size does not match');
end


eNb_UE_stats_struct = struct(...
    'UL_rssi',int32(zeros(1,NB_ANTENNAS_RX)),...
    'DL_cqi',uint8(zeros(1,2)),...
    'DL_subband_cqi',uint8(zeros(13,2)),...
    'DL_pmi_single',uint16(0),...
    'DL_pmi_dual',uint16(0),...
    'rank',uint8(0),...
    'crnti',uint16(0),...
    'UE_timing_offset',int32(0),...
    'timing_advance_update',int32(0),...
    'UE_mode',uint32(0),...
    'sector',uint8(0),...

  'dlsch_l2_errors', uint32(zeros(1,8)),...
  'dlsch_trials', uint32(zeros(8,8)),...
  'dlsch_ACK', uint32(zeros(8,8)),...
  'dlsch_NAK', uint32(zeros(8,8)),...

  'ulsch_errors', uint32(zeros(1,8)),...
  'ulsch_consecutive_errors', uint32(0),...
  'ulsch_decoding_attempts', uint32(zeros(8,8)),...
  'ulsch_round_errors', uint32(zeros(8,8)),...
  'ulsch_decoding_attempts_last', uint32(zeros(8,8)),...
  'ulsch_round_errors_last', uint32(zeros(8,8)),...
  'ulsch_round_fer', uint32(zeros(8,8)),...
  'sr_received', uint32(0), ...
  'sr_total', uint32(0), ...

  'dlsch_sliding_cnt', uint32(0),...
  'dlsch_NAK_round0', uint32(0),...
  'dlsch_mcs_offset', int8(0),...

  'dlsch_mcs1', uint8(0),...
  'dlsch_mcs2', uint8(0),...
  'total_TBS_MAC', int32(0),...
  'total_TBS', int32(0),...
  'total_TBS_last', int32(0),...
  'dlsch_bitrate', uint32(0)
  %'total_transmitted_bits', uint32(0)
);


eNb_UE_stats_struct_a = cstruct(eNb_UE_stats_struct,[],align);
if (exist('eNb_UE_stats_size','var') && (eNb_UE_stats_struct_a.size ~= eNb_UE_stats_size))
    warning('eNb_UE_stats_size does not match');
end

complex_struct = struct('real',int16(0),'imag',int16(0));

fifo_dump_emos_struct_UE = struct(...
    'timestamp',int64(0),...
    'frame_tx',uint32(0),...
    'frame_rx',uint32(0),...
    'UE_mode',uint32(0),...
    'phy_measurements', phy_measurements_struct,...
    'pbch_errors',uint32(0),...
    'pbch_errors_last',uint32(0),...
    'pbch_errors_conseq',uint32(0),...
    'pbch_fer',uint32(0),...
    'dlsch_errors',uint32(0),...
    'dlsch_errors_last',uint32(0),...
    'dlsch_received',uint32(0),...
    'dlsch_received_last',uint32(0),...
    'dlsch_fer',uint32(0),...
    'dlsch_cntl_errors',uint32(0),...
    'dlsch_ra_errors',uint32(0),...
    'total_TBS',uint32(0),...
    'total_TBS_last',uint32(0),...
    'bitrate',uint32(0),...
    'total_received_bits',uint32(0),...
    'timing_offset',int32(0),...
    'timing_advance',int32(0),...
    'freq_offset',int32(0),...
    'use_ia_receiver',int32(0),...
    'pmi_saved',uint16(0),...
    'mcs',uint16(0),...
    'rx_total_gain_dB',uint32(0),...
    'eNb_id',uint8(0),...
    'mimo_mode',uint8(0));
if (EMOS_CHANNEL)
    fifo_dump_emos_struct_UE.channel=int16(zeros(2*NUMBER_OF_OFDM_CARRIERS_EMOS*N_PILOTS_DL_EMOS*N_SLOTS_DL_EMOS,NB_ANTENNAS_TX_EMOS,NB_ANTENNAS_RX_EMOS));
end

fifo_dump_emos_struct_UE_a = cstruct(fifo_dump_emos_struct_UE,[],align);
if (exist('fifo_dump_emos_UE_size','var') && (fifo_dump_emos_struct_UE_a.size ~= fifo_dump_emos_UE_size))
    warning('fifo_dump_emos_UE_size does not match');
end

fifo_dump_emos_struct_eNb = struct(...
    'timestamp',int64(0),...
    'frame_tx',uint32(0),...
    'mimo_mode',uint8(0),...   
    'phy_measurements_eNb',phy_measurements_eNb_struct,...
    'eNb_UE_stats',repmat(eNb_UE_stats_struct,1,NUMBER_OF_UE_MAX),...
    'rx_total_gain_dB',uint32(0)); 
if (EMOS_CHANNEL)
  fifo_dump_emos_struct_eNb.channel = int16(zeros(2*N_RB_UL_EMOS*12*N_PILOTS_UL_EMOS*N_SUBFRAMES_UL_EMOS,NB_ANTENNAS_RX_EMOS));
end

fifo_dump_emos_struct_eNb_a = cstruct(fifo_dump_emos_struct_eNb,[],align);
if (exist('fifo_dump_emos_eNb_size','var') && (fifo_dump_emos_struct_eNb_a.size ~= fifo_dump_emos_eNb_size))
    warning('fifo_dump_emos_eNb_size does not match');
end


gps_data_struct = struct(...
    'timestamp', double(0),...
    'mode', int32(0),...
    'ept',double(0),...
    'latitude',double(0),...
    'epy',double(0),...
    'longitude',double(0),...
    'epx',double(0),...
    'altitude',double(0),...
    'epv',double(0),...
    'track',double(0),...
    'epd',double(0),...
    'speed',double(0),...
    'eps',double(0),...
    'climb',double(0),...
    'epc',double(0));

gps_data_struct_a = cstruct(gps_data_struct,[],align);
if (exist('gps_fix_t_size','var') && (gps_data_struct_a.size ~= gps_fix_t_size))
    warning('gps_data_struct_size does not match');
end


min_estimates_struct = struct(...
    'mcs',double(0),...
    'tbs',double(0),...
    'rx_rssi_dBm',int16(0),...
    'frame_tx',uint32(0),...
    'frame_rx',uint32(0),...
    'pbch_fer',uint32(0),...
    'timestamp',int64(0),...
    'UE_mode',uint32(0),...
    'phy_measurements', repmat(phy_measurements_struct,1,1),...
    'dlsch_fer',uint32(0),...
    'dlsch_errors',uint32(0),...
    'mimo_mode',uint8(0),...
    'eNb_id',uint8(0));
min_estimates_struct_a = cstruct(min_estimates_struct,[],align);

min_estimates_struct_eNb = struct(...
    'mcs',double(0),...
    'tbs',double(0),...
    'rx_rssi_dBm',int16(0),...
    'frame_tx',uint32(0),...
    'timestamp',int64(0),...
    'UE_mode',uint32(0),...
    'phy_measurements', repmat(phy_measurements_eNb_struct,1,1),...
    'ulsch_errors',uint32(0),...
    'mimo_mode',uint8(0),...
    'eNb_id',uint8(0));
min_estimates_struct_eNb_a = cstruct(min_estimates_struct,[],align);




