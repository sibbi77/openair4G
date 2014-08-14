/*******************************************************************************
    OpenAirInterface
    Copyright(c) 1999 - 2014 Eurecom

    OpenAirInterface is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.


    OpenAirInterface is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with OpenAirInterface.The full GNU General Public License is
    included in this distribution in the file called "COPYING". If not,
    see <http://www.gnu.org/licenses/>.

  Contact Information
  OpenAirInterface Admin: openair_admin@eurecom.fr
  OpenAirInterface Tech : openair_tech@eurecom.fr
  OpenAirInterface Dev  : openair4g-devel@eurecom.fr

  Address      : Eurecom, Campus SophiaTech, 450 Route des Chappes, CS 50193 - 06904 Biot Sophia Antipolis cedex, FRANCE

*******************************************************************************/

/*
                                enb_config.c
                             -------------------
  AUTHOR  : Lionel GAUTHIER, navid nikaein, Laurent Winckel
  COMPANY : EURECOM
  EMAIL   : Lionel.Gauthier@eurecom.fr, navid.nikaein@eurecom.fr
*/

#include <string.h>
#include <libconfig.h>
#include <inttypes.h>

#include "log.h"
#include "log_extern.h"
#include "assertions.h"
#include "enb_config.h"
#if defined(OAI_EMU)
# include "OCG.h"
# include "OCG_extern.h"
#endif
#if defined(ENABLE_ITTI)
# include "intertask_interface.h"
# if defined(ENABLE_USE_MME)
#   include "s1ap_eNB.h"
#   include "sctp_eNB_task.h"
# endif
#endif

#include "LAYER2/MAC/extern.h"

#define ENB_CONFIG_STRING_ACTIVE_ENBS                   "Active_eNBs"

#define ENB_CONFIG_STRING_ENB_LIST                      "eNBs"
#define ENB_CONFIG_STRING_ENB_ID                        "eNB_ID"
#define ENB_CONFIG_STRING_CELL_TYPE                     "cell_type"
#define ENB_CONFIG_STRING_ENB_NAME                      "eNB_name"

#define ENB_CONFIG_STRING_TRACKING_AREA_CODE            "tracking_area_code"
#define ENB_CONFIG_STRING_MOBILE_COUNTRY_CODE           "mobile_country_code"
#define ENB_CONFIG_STRING_MOBILE_NETWORK_CODE           "mobile_network_code"

#define ENB_CONFIG_STRING_DEFAULT_PAGING_DRX            "default_paging_drx"

#define ENB_CONFIG_STRING_FRAME_TYPE                    "frame_type"
#define ENB_CONFIG_STRING_TDD_CONFIG                    "tdd_config"
#define ENB_CONFIG_STRING_TDD_CONFIG_S                  "tdd_config_s"
#define ENB_CONFIG_STRING_PREFIX_TYPE                   "prefix_type"
#define ENB_CONFIG_STRING_EUTRA_BAND                    "eutra_band"
#define ENB_CONFIG_STRING_DOWNLINK_FREQUENCY            "downlink_frequency"
#define ENB_CONFIG_STRING_UPLINK_FREQUENCY_OFFSET       "uplink_frequency_offset"

#define ENB_CONFIG_STRING_COMPONENT_CARRIERS            "component_carriers"
#define ENB_CONFIG_STRING_CELL_ID                       "cell_id"
#define ENB_CONFIG_STRING_N_RB_DL                       "N_RB_DL"

#define ENB_CONFIG_STRING_MME_IP_ADDRESS                "mme_ip_address"
#define ENB_CONFIG_STRING_MME_IPV4_ADDRESS              "ipv4"
#define ENB_CONFIG_STRING_MME_IPV6_ADDRESS              "ipv6"
#define ENB_CONFIG_STRING_MME_IP_ADDRESS_ACTIVE         "active"
#define ENB_CONFIG_STRING_MME_IP_ADDRESS_PREFERENCE     "preference"

#define ENB_CONFIG_STRING_NETWORK_INTERFACES_CONFIG     "NETWORK_INTERFACES"
#define ENB_CONFIG_STRING_ENB_INTERFACE_NAME_FOR_S1_MME "ENB_INTERFACE_NAME_FOR_S1_MME"
#define ENB_CONFIG_STRING_ENB_IPV4_ADDRESS_FOR_S1_MME   "ENB_IPV4_ADDRESS_FOR_S1_MME"
#define ENB_CONFIG_STRING_ENB_INTERFACE_NAME_FOR_S1U    "ENB_INTERFACE_NAME_FOR_S1U"
#define ENB_CONFIG_STRING_ENB_IPV4_ADDR_FOR_S1U         "ENB_IPV4_ADDRESS_FOR_S1U"


#define ENB_CONFIG_STRING_ASN1_VERBOSITY                      "Asn1_verbosity"
#define ENB_CONFIG_STRING_ASN1_VERBOSITY_NONE                 "none"
#define ENB_CONFIG_STRING_ASN1_VERBOSITY_ANNOYING             "annoying"
#define ENB_CONFIG_STRING_ASN1_VERBOSITY_INFO                 "info"


// per eNB configuration 
#define ENB_CONFIG_STRING_LOG_CONFIG                       "log_config"
#define ENB_CONFIG_STRING_GLOBAL_LOG_LEVEL                 "global_log_level"
#define ENB_CONFIG_STRING_GLOBAL_LOG_VERBOSITY              "global_log_verbosity"
#define ENB_CONFIG_STRING_HW_LOG_LEVEL                    "hw_log_level"
#define ENB_CONFIG_STRING_HW_LOG_VERBOSITY                "hw_log_verbosity"
#define ENB_CONFIG_STRING_PHY_LOG_LEVEL                    "phy_log_level"
#define ENB_CONFIG_STRING_PHY_LOG_VERBOSITY                "phy_log_verbosity"
#define ENB_CONFIG_STRING_MAC_LOG_LEVEL                    "mac_log_level"
#define ENB_CONFIG_STRING_MAC_LOG_VERBOSITY                "mac_log_verbosity"
#define ENB_CONFIG_STRING_RLC_LOG_LEVEL                    "rlc_log_level"
#define ENB_CONFIG_STRING_RLC_LOG_VERBOSITY                "rlc_log_verbosity"
#define ENB_CONFIG_STRING_PDCP_LOG_LEVEL                   "pdcp_log_level"
#define ENB_CONFIG_STRING_PDCP_LOG_VERBOSITY               "pdcp_log_verbosity"
#define ENB_CONFIG_STRING_RRC_LOG_LEVEL                    "rrc_log_level"
#define ENB_CONFIG_STRING_RRC_LOG_VERBOSITY                "rrc_log_verbosity"




#define KHz (1000UL)
#define MHz (1000 * KHz)

typedef struct eutra_band_s
{
    int16_t             band;
    uint32_t            ul_min;
    uint32_t            ul_max;
    uint32_t            dl_min;
    uint32_t            dl_max;
    lte_frame_type_t    frame_type;
} eutra_band_t;

static const eutra_band_t eutra_bands[] =
{
    { 1, 1920    * MHz, 1980    * MHz, 2110    * MHz, 2170    * MHz, FDD},
    { 2, 1850    * MHz, 1910    * MHz, 1930    * MHz, 1990    * MHz, FDD},
    { 3, 1710    * MHz, 1785    * MHz, 1805    * MHz, 1880    * MHz, FDD},
    { 4, 1710    * MHz, 1755    * MHz, 2110    * MHz, 2155    * MHz, FDD},
    { 5,  824    * MHz,  849    * MHz,  869    * MHz,  894    * MHz, FDD},
    { 6,  830    * MHz,  840    * MHz,  875    * MHz,  885    * MHz, FDD},
    { 7, 2500    * MHz, 2570    * MHz, 2620    * MHz, 2690    * MHz, FDD},
    { 8,  880    * MHz,  915    * MHz,  925    * MHz,  960    * MHz, FDD},
    { 9, 1749900 * KHz, 1784900 * KHz, 1844900 * KHz, 1879900 * KHz, FDD},
    {10, 1710    * MHz, 1770    * MHz, 2110    * MHz, 2170    * MHz, FDD},
    {11, 1427900 * KHz, 1452900 * KHz, 1475900 * KHz, 1500900 * KHz, FDD},
    {12,  698    * MHz,  716    * MHz,  728    * MHz,  746    * MHz, FDD},
    {13,  777    * MHz,  787    * MHz,  746    * MHz,  756    * MHz, FDD},
    {14,  788    * MHz,  798    * MHz,  758    * MHz,  768    * MHz, FDD},

    {17,  704    * MHz,  716    * MHz,  734    * MHz,  746    * MHz, FDD},

    {33, 1900    * MHz, 1920    * MHz, 1900    * MHz, 1920    * MHz, TDD},
    {34, 2010    * MHz, 2025    * MHz, 2010    * MHz, 2025    * MHz, TDD},
    {35, 1850    * MHz, 1910    * MHz, 1850    * MHz, 1910    * MHz, TDD},
    {36, 1930    * MHz, 1990    * MHz, 1930    * MHz, 1990    * MHz, TDD},
    {37, 1910    * MHz, 1930    * MHz, 1910    * MHz, 1930    * MHz, TDD},
    {38, 2570    * MHz, 2620    * MHz, 2570    * MHz, 2630    * MHz, TDD},
    {39, 1880    * MHz, 1920    * MHz, 1880    * MHz, 1920    * MHz, TDD},
    {40, 2300    * MHz, 2400    * MHz, 2300    * MHz, 2400    * MHz, TDD},
};

static Enb_properties_array_t enb_properties;

static void enb_config_display(void) {
  int i,j;

    printf( "\n----------------------------------------------------------------------\n");
    printf( " ENB CONFIG FILE CONTENT LOADED (TBC):\n");
    printf( "----------------------------------------------------------------------\n");
    for (i = 0; i < enb_properties.number; i++) {
        printf( "ENB CONFIG for instance %u:\n\n", i);
        printf( "\teNB name:           \t%s:\n",enb_properties.properties[i]->eNB_name);
        printf( "\teNB ID:             \t%u:\n",enb_properties.properties[i]->eNB_id);
        printf( "\tCell type:          \t%s:\n",enb_properties.properties[i]->cell_type == CELL_MACRO_ENB ? "CELL_MACRO_ENB":"CELL_HOME_ENB");
        printf( "\tTAC:                \t%u:\n",enb_properties.properties[i]->tac);
        printf( "\tMCC:                \t%u:\n",enb_properties.properties[i]->mcc);
        printf( "\tMNC:                \t%u:\n",enb_properties.properties[i]->mnc);
	printf( "\teutra band:         \t%d:\n",enb_properties.properties[i]->eutra_band);
        printf( "\tdownlink freq:      \t%u:\n",enb_properties.properties[i]->downlink_frequency);
        printf( "\tuplink freq:        \t%d:\n",enb_properties.properties[i]->uplink_frequency_offset);

	for (j=0; j< enb_properties.properties[i]->nb_cc; j++) {
	  printf( "\n\tCell ID for CC %d:\t%d:\n",j,enb_properties.properties[i]->cell_id[j]);
	  printf( "\tN_RB_DL for CC %d:\t%d:\n",j,enb_properties.properties[i]->N_RB_DL[j]);
	}
	
      	printf( "\n\tGlobal log level:  \t%s\n", map_int_to_str(log_level_names,enb_properties.properties[i]->glog_level));
	printf( "\tHW log level:      \t%s\n", map_int_to_str(log_level_names,enb_properties.properties[i]->hw_log_level));
	printf( "\tPHY log level:     \t%s\n", map_int_to_str(log_level_names,enb_properties.properties[i]->phy_log_level));
	printf( "\tMAC log level:     \t%s\n", map_int_to_str(log_level_names,enb_properties.properties[i]->mac_log_level));
	printf( "\tRLC log level:     \t%s\n", map_int_to_str(log_level_names,enb_properties.properties[i]->rlc_log_level));
	printf( "\tPDCP log level:    \t%s\n", map_int_to_str(log_level_names,enb_properties.properties[i]->pdcp_log_level));
	printf( "\tRRC log level:     \t%s\n", map_int_to_str(log_level_names,enb_properties.properties[i]->rrc_log_level));
	 
	printf( "\n--------------------------------------------------------\n");
    }
}


static int enb_check_band_frequencies(char* lib_config_file_name_pP,
                                      int enb_properties_index,
                                      int16_t band,
                                      uint32_t downlink_frequency,
                                      int32_t uplink_frequency_offset,
                                      lte_frame_type_t frame_type)
{
    int errors = 0;

    if (band > 0)
    {
        int band_index;

        for (band_index = 0; band_index < sizeof (eutra_bands) / sizeof (eutra_bands[0]); band_index++)
        {
            if (band == eutra_bands[band_index].band)
            {
                uint32_t uplink_frequency = downlink_frequency + uplink_frequency_offset;

                AssertError (eutra_bands[band_index].dl_min < downlink_frequency, errors ++,
                             "Failed to parse eNB configuration file %s, enb %d downlink frequency %u too low (%u) for band %d!",
                             lib_config_file_name_pP, enb_properties_index, downlink_frequency, eutra_bands[band_index].dl_min, band);
                AssertError (downlink_frequency < eutra_bands[band_index].dl_max, errors ++,
                             "Failed to parse eNB configuration file %s, enb %d downlink frequency %u too high (%u) for band %d!",
                             lib_config_file_name_pP, enb_properties_index, downlink_frequency, eutra_bands[band_index].dl_max, band);

                AssertError (eutra_bands[band_index].ul_min < uplink_frequency, errors ++,
                             "Failed to parse eNB configuration file %s, enb %d uplink frequency %u too low (%u) for band %d!",
                             lib_config_file_name_pP, enb_properties_index, uplink_frequency, eutra_bands[band_index].ul_min, band);
                AssertError (uplink_frequency < eutra_bands[band_index].ul_max, errors ++,
                             "Failed to parse eNB configuration file %s, enb %d uplink frequency %u too high (%u) for band %d!",
                             lib_config_file_name_pP, enb_properties_index, uplink_frequency, eutra_bands[band_index].ul_max, band);

                AssertError (eutra_bands[band_index].frame_type == frame_type, errors ++,
                             "Failed to parse eNB configuration file %s, enb %d invalid frame type (%d/%d) for band %d!",
                             lib_config_file_name_pP, enb_properties_index, eutra_bands[band_index].frame_type, frame_type, band);
            }
        }
    }
    return errors;
}

#if defined(ENABLE_ITTI) && defined(ENABLE_USE_MME)
extern int asn_debug;
extern int asn1_xer_print;
#endif

const Enb_properties_array_t *enb_config_init(char* lib_config_file_name_pP) {
  config_t          cfg;
  config_setting_t *setting                       = NULL;
  config_setting_t *subsetting                    = NULL;
  config_setting_t *setting_component_carriers    = NULL;
  config_setting_t *component_carrier             = NULL;
  config_setting_t *setting_mme_addresses         = NULL;
  config_setting_t *setting_mme_address           = NULL;
  config_setting_t *setting_enb                   = NULL;
  int               num_enb_properties            = 0;
  int               enb_properties_index          = 0;
  int               num_enbs;
  int               num_mme_address;
  int               num_component_carriers        =0;
  int               i;
  int               j;
  int               parse_errors                  = 0;
  long int          enb_id                        = 0;
  const char*       cell_type                     = NULL;
  const char*       tac                           = 0;
  const char*       enb_name                      = NULL;
  const char*       mcc                           = 0;
  const char*       mnc                           = 0;
  const char*       default_drx                   = NULL;
  const char*       frame_type;
  long int          tdd_config;
  long int          tdd_config_s;
  const char*       prefix_type;
  long int          eutra_band;
  long long int     downlink_frequency;
  long int          uplink_frequency_offset;
  long int          cell_id[MAX_NUM_CCs];
  long int          N_RB_DL[MAX_NUM_CCs];
  char*             ipv4                          = NULL;
  char*             ipv6                          = NULL;
  char*             active                        = NULL;
  char*             preference                    = NULL;
  const char*       active_enb[MAX_ENB];
  char*             enb_interface_name_for_S1U    = NULL;
  char*             enb_ipv4_address_for_S1U      = NULL;
  char*             enb_interface_name_for_S1_MME = NULL;
  char*             enb_ipv4_address_for_S1_MME   = NULL;
  char             *address                       = NULL;
  char             *cidr                          = NULL;
  char             *astring                       = NULL;
  char*          glog_level                   = NULL;
  char*          glog_verbosity               = NULL;
  char*          hw_log_level                = NULL;
  char*          hw_log_verbosity            = NULL;
  char*          phy_log_level                = NULL;
  char*          phy_log_verbosity            = NULL;
  char*          mac_log_level                = NULL;
  char*          mac_log_verbosity            = NULL;
  char*          rlc_log_level                = NULL;
  char*          rlc_log_verbosity            = NULL;
  char*          pdcp_log_level               = NULL;
  char*          pdcp_log_verbosity           = NULL;
  char*          rrc_log_level                = NULL;
  char*          rrc_log_verbosity            = NULL;

  memset((char*) (enb_properties.properties), 0 , MAX_ENB * sizeof(Enb_properties_t *));
  memset((char*)active_enb,     0 , MAX_ENB * sizeof(char*));

  config_init(&cfg);

  if(lib_config_file_name_pP != NULL)
  {
      /* Read the file. If there is an error, report it and exit. */
      if(! config_read_file(&cfg, lib_config_file_name_pP))
      {
          config_destroy(&cfg);
          AssertFatal (0, "Failed to parse eNB configuration file %s!\n", lib_config_file_name_pP);
      }
  }
  else
  {
      config_destroy(&cfg);
      AssertFatal (0, "No eNB configuration file provided!\n");
  }

#if defined(ENABLE_ITTI) && defined(ENABLE_USE_MME)
  if(  (config_lookup_string( &cfg, ENB_CONFIG_STRING_ASN1_VERBOSITY, (const char **)&astring) )) {
      if (strcasecmp(astring , ENB_CONFIG_STRING_ASN1_VERBOSITY_NONE) == 0) {
          asn_debug      = 0;
          asn1_xer_print = 0;
      } else if (strcasecmp(astring , ENB_CONFIG_STRING_ASN1_VERBOSITY_INFO) == 0) {
          asn_debug      = 1;
          asn1_xer_print = 1;
      } else if (strcasecmp(astring , ENB_CONFIG_STRING_ASN1_VERBOSITY_ANNOYING) == 0) {
          asn_debug      = 1;
          asn1_xer_print = 2;
      } else {
          asn_debug      = 0;
          asn1_xer_print = 0;
      }
  }
#endif
  // Get list of active eNBs, (only these will be configured)
  setting = config_lookup(&cfg, ENB_CONFIG_STRING_ACTIVE_ENBS);
  if(setting != NULL)
  {
      num_enbs = config_setting_length(setting);
      for (i = 0; i < num_enbs; i++) {
          setting_enb   = config_setting_get_elem(setting, i);
          active_enb[i] = config_setting_get_string (setting_enb);
          AssertFatal (active_enb[i] != NULL,
                       "Failed to parse config file %s, %uth attribute %s \n",
                       lib_config_file_name_pP, i, ENB_CONFIG_STRING_ACTIVE_ENBS);
          active_enb[i] = strdup(active_enb[i]);
          num_enb_properties += 1;
      }
  }

  /* Output a list of all eNBs. */
  setting = config_lookup(&cfg, ENB_CONFIG_STRING_ENB_LIST);
  if(setting != NULL)
  {
      enb_properties_index = 0;
      parse_errors      = 0;
      num_enbs = config_setting_length(setting);
      for (i = 0; i < num_enbs; i++) {
          setting_enb = config_setting_get_elem(setting, i);

          if(! config_setting_lookup_int(setting_enb, ENB_CONFIG_STRING_ENB_ID, &enb_id)) {
              /* Calculate a default eNB ID */
# if defined(ENABLE_USE_MME)
              uint32_t hash;

              hash = s1ap_generate_eNB_id ();
              enb_id = i + (hash & 0xFFFF8);
# else
              enb_id = i;
# endif
          }

          if(  !(       config_setting_lookup_string(setting_enb, ENB_CONFIG_STRING_CELL_TYPE,           &cell_type)
                     && config_setting_lookup_string(setting_enb, ENB_CONFIG_STRING_ENB_NAME,            &enb_name)
                     && config_setting_lookup_string(setting_enb, ENB_CONFIG_STRING_TRACKING_AREA_CODE,  &tac)
                     && config_setting_lookup_string(setting_enb, ENB_CONFIG_STRING_MOBILE_COUNTRY_CODE, &mcc)
                     && config_setting_lookup_string(setting_enb, ENB_CONFIG_STRING_MOBILE_NETWORK_CODE, &mnc)
                     && config_setting_lookup_string(setting_enb, ENB_CONFIG_STRING_DEFAULT_PAGING_DRX,  &default_drx)
			
                )
            ) {
              AssertError (0, parse_errors ++,
                      "Failed to parse eNB configuration file %s, %u th enb\n",
                      lib_config_file_name_pP, i);
          }
          // search if in active list
          for (j=0; j < num_enb_properties; j++) {
              if (strcmp(active_enb[j], enb_name) == 0) {
                  enb_properties.properties[enb_properties_index] = calloc(1, sizeof(Enb_properties_t));

                  enb_properties.properties[enb_properties_index]->eNB_id   = enb_id;
                  if (strcmp(cell_type, "CELL_MACRO_ENB") == 0) {
                      enb_properties.properties[enb_properties_index]->cell_type = CELL_MACRO_ENB;
                  } else  if (strcmp(cell_type, "CELL_HOME_ENB") == 0) {
                      enb_properties.properties[enb_properties_index]->cell_type = CELL_HOME_ENB;
                  } else {
                      AssertError (0, parse_errors ++,
                              "Failed to parse eNB configuration file %s, enb %d unknown value \"%s\" for cell_type choice: CELL_MACRO_ENB or CELL_HOME_ENB !\n",
                              lib_config_file_name_pP, i, cell_type);
                  }
                  enb_properties.properties[enb_properties_index]->eNB_name         = strdup(enb_name);
                  enb_properties.properties[enb_properties_index]->tac              = (uint16_t)atoi(tac);
                  enb_properties.properties[enb_properties_index]->mcc              = (uint16_t)atoi(mcc);
                  enb_properties.properties[enb_properties_index]->mnc              = (uint16_t)atoi(mnc);
                  enb_properties.properties[enb_properties_index]->mnc_digit_length = strlen(mnc);

                  if (strcmp(default_drx, "PAGING_DRX_32") == 0) {
                      enb_properties.properties[enb_properties_index]->default_drx = PAGING_DRX_32;
                  } else  if (strcmp(default_drx, "PAGING_DRX_64") == 0) {
                      enb_properties.properties[enb_properties_index]->default_drx = PAGING_DRX_64;
                  } else  if (strcmp(default_drx, "PAGING_DRX_128") == 0) {
                      enb_properties.properties[enb_properties_index]->default_drx = PAGING_DRX_128;
                  } else  if (strcmp(default_drx, "PAGING_DRX_256") == 0) {
                      enb_properties.properties[enb_properties_index]->default_drx = PAGING_DRX_256;
                  } else {
                      AssertError (0, parse_errors ++,
                              "Failed to parse eNB configuration file %s, enb %d unknown value \"%s\" for default_drx choice: PAGING_DRX_32..PAGING_DRX_256 !\n",
                              lib_config_file_name_pP, i, default_drx);
                  }

                  // Parse optional physical parameters
                  if(config_setting_lookup_string(setting_enb, ENB_CONFIG_STRING_FRAME_TYPE, &frame_type)) {
                      if (strcmp(frame_type, "FDD") == 0) {
                          enb_properties.properties[enb_properties_index]->frame_type = FDD;
                      } else  if (strcmp(frame_type, "TDD") == 0) {
                          enb_properties.properties[enb_properties_index]->frame_type = TDD;
                      } else {
                          AssertError (0, parse_errors ++,
                                  "Failed to parse eNB configuration file %s, enb %d unknown value \"%s\" for frame_type choice: FDD or TDD !\n",
                                  lib_config_file_name_pP, i, frame_type);
                      }
                  } else {
                      enb_properties.properties[enb_properties_index]->frame_type = FDD; // Default frame type
                  }

                  if(config_setting_lookup_int(setting_enb, ENB_CONFIG_STRING_TDD_CONFIG, &tdd_config)) {
                      enb_properties.properties[enb_properties_index]->tdd_config = tdd_config;
                      AssertError (tdd_config <= TDD_Config__subframeAssignment_sa6, parse_errors ++,
                              "Failed to parse eNB configuration file %s, enb %d illegal tdd_config %ld (should be 0-%d)!",
                              lib_config_file_name_pP, i, tdd_config, TDD_Config__subframeAssignment_sa6);
                  } else {
                      enb_properties.properties[enb_properties_index]->tdd_config = 3; // Default TDD sub-frame configuration
                  }

                  if(config_setting_lookup_int(setting_enb, ENB_CONFIG_STRING_TDD_CONFIG_S, &tdd_config_s)) {
                      enb_properties.properties[enb_properties_index]->tdd_config_s = tdd_config_s;
                      AssertError (tdd_config_s <= TDD_Config__specialSubframePatterns_ssp8, parse_errors ++,
                              "Failed to parse eNB configuration file %s, enb %d illegal tdd_config_s %ld (should be 0-%d)!",
                              lib_config_file_name_pP, i, tdd_config_s, TDD_Config__specialSubframePatterns_ssp8);
                  } else {
                      enb_properties.properties[enb_properties_index]->tdd_config_s = 0; // Default TDD S-sub-frame configuration
                  }

                  if(config_setting_lookup_string(setting_enb, ENB_CONFIG_STRING_PREFIX_TYPE, &prefix_type)) {
                      if (strcmp(prefix_type, "NORMAL") == 0) {
                          enb_properties.properties[enb_properties_index]->prefix_type = NORMAL;
                      } else  if (strcmp(prefix_type, "EXTENDED") == 0) {
                          enb_properties.properties[enb_properties_index]->prefix_type = EXTENDED;
                      } else {
                          AssertError (0, parse_errors ++,
                                  "Failed to parse eNB configuration file %s, enb %d unknown value \"%s\" for prefix_type choice: NORMAL or EXTENDED !\n",
                                  lib_config_file_name_pP, i, prefix_type);
                      }
                  } else {
                      enb_properties.properties[enb_properties_index]->prefix_type = NORMAL; // Default prefix type
                  }

                  if(config_setting_lookup_int(setting_enb, ENB_CONFIG_STRING_EUTRA_BAND, &eutra_band)) {
                      enb_properties.properties[enb_properties_index]->eutra_band = eutra_band;
		      // printf( "\teutra band:\t%d\n",enb_properties.properties[enb_properties_index]->eutra_band);
                  } else {
                      enb_properties.properties[enb_properties_index]->eutra_band = 7; // Default band
                      //printf( "\teutra band:\t%d (default)\n",enb_properties.properties[enb_properties_index]->eutra_band);
                  }

                  if(config_setting_lookup_int64(setting_enb, ENB_CONFIG_STRING_DOWNLINK_FREQUENCY, &downlink_frequency)) {
                      enb_properties.properties[enb_properties_index]->downlink_frequency = (uint32_t) downlink_frequency;
                      //printf( "\tdownlink freq:\t%u\n",enb_properties.properties[enb_properties_index]->downlink_frequency);
                  } else {
                      enb_properties.properties[enb_properties_index]->downlink_frequency = 2680000000UL; // Default downlink frequency
		      // printf( "\tdownlink freq:\t%u (default)\n",enb_properties.properties[enb_properties_index]->downlink_frequency);
                  }
                  if(config_setting_lookup_int(setting_enb, ENB_CONFIG_STRING_UPLINK_FREQUENCY_OFFSET, &uplink_frequency_offset)) {
                      enb_properties.properties[enb_properties_index]->uplink_frequency_offset = (unsigned int) uplink_frequency_offset;
                      //printf( "\tuplink freq offset:\t%ld\n",enb_properties.properties[enb_properties_index]->uplink_frequency_offset);
                  } else {
                      // Default uplink frequency offset
                      if (enb_properties.properties[enb_properties_index]->frame_type == FDD) {
                          enb_properties.properties[enb_properties_index]->uplink_frequency_offset = -120000000;
                      } else {
                          enb_properties.properties[enb_properties_index]->uplink_frequency_offset = 0;
                      }
                      //printf( "\tuplink freq offset:\t%ld (default)\n",enb_properties.properties[enb_properties_index]->uplink_frequency_offset);
                  }

                  parse_errors += enb_check_band_frequencies(lib_config_file_name_pP,
                                             enb_properties_index,
                                             enb_properties.properties[enb_properties_index]->eutra_band,
                                             enb_properties.properties[enb_properties_index]->downlink_frequency,
                                             enb_properties.properties[enb_properties_index]->uplink_frequency_offset,
                                             enb_properties.properties[enb_properties_index]->frame_type);

		  setting_component_carriers = config_setting_get_member (setting_enb, ENB_CONFIG_STRING_COMPONENT_CARRIERS);
		  enb_properties.properties[enb_properties_index]->nb_cc = 0;
		  if(setting_component_carriers != NULL) { 

		    num_component_carriers     = config_setting_length(setting_component_carriers);  
		    //printf("num component carrier %d \n", num_component_carriers);
		    //enb_properties.properties[enb_properties_index]->nb_cc = num_component_carriers; 
		    for (j = 0; j < num_component_carriers /*&& j < MAX_NUM_CCs*/; j++) {
		      component_carrier = config_setting_get_elem(setting_component_carriers, j);
		      if(!(config_setting_lookup_int(component_carrier, ENB_CONFIG_STRING_CELL_ID, &cell_id[j]) && 
			   config_setting_lookup_int(component_carrier, ENB_CONFIG_STRING_N_RB_DL, &N_RB_DL[j])   )
			 ){
			AssertError (0, parse_errors ++,
				     "Failed to parse eNB configuration file %s, Component Carrier!\n",
				     lib_config_file_name_pP);
		      }
		      enb_properties.properties[enb_properties_index]->nb_cc++;
		      enb_properties.properties[enb_properties_index]->cell_id[j]= cell_id[j];
		      enb_properties.properties[enb_properties_index]->N_RB_DL[j]= N_RB_DL[j];
		      //printf("adding component carrier %d\n", j);
		    }
		    
		  } else {
		    for (j=0; j< MAX_NUM_CCs; j++) {
		      enb_properties.properties[enb_properties_index]->nb_cc +=1;
		      enb_properties.properties[enb_properties_index]->cell_id[j]=j;
		      enb_properties.properties[enb_properties_index]->N_RB_DL[j]=25;
		    }
		  }
		  
                  setting_mme_addresses = config_setting_get_member (setting_enb, ENB_CONFIG_STRING_MME_IP_ADDRESS);
                  num_mme_address     = config_setting_length(setting_mme_addresses);
                  enb_properties.properties[enb_properties_index]->nb_mme = 0;
                  for (j = 0; j < num_mme_address; j++) {
                      setting_mme_address = config_setting_get_elem(setting_mme_addresses, j);
                      if(  !(
                              config_setting_lookup_string(setting_mme_address, ENB_CONFIG_STRING_MME_IPV4_ADDRESS, (const char **)&ipv4)
                              && config_setting_lookup_string(setting_mme_address, ENB_CONFIG_STRING_MME_IPV6_ADDRESS, (const char **)&ipv6)
                              && config_setting_lookup_string(setting_mme_address, ENB_CONFIG_STRING_MME_IP_ADDRESS_ACTIVE, (const char **)&active)
                              && config_setting_lookup_string(setting_mme_address, ENB_CONFIG_STRING_MME_IP_ADDRESS_PREFERENCE, (const char **)&preference)
                            )
                        ) {
                          AssertError (0, parse_errors ++,
                                  "Failed to parse eNB configuration file %s, %u th enb %u th mme address !\n",
                                  lib_config_file_name_pP, i, j);
                      }
                      enb_properties.properties[enb_properties_index]->nb_mme += 1;

                      enb_properties.properties[enb_properties_index]->mme_ip_address[j].ipv4_address = strdup(ipv4);
                      enb_properties.properties[enb_properties_index]->mme_ip_address[j].ipv6_address = strdup(ipv6);
                      if (strcmp(active, "yes") == 0) {
                          enb_properties.properties[enb_properties_index]->mme_ip_address[j].active = 1;
#if defined(ENABLE_USE_MME)
                          EPC_MODE_ENABLED = 1;
#endif
                      } // else { (calloc)

                      if (strcmp(preference, "ipv4") == 0) {
                          enb_properties.properties[enb_properties_index]->mme_ip_address[j].ipv4 = 1;
                      } else if (strcmp(preference, "ipv6") == 0) {
                          enb_properties.properties[enb_properties_index]->mme_ip_address[j].ipv6 = 1;
                      } else if (strcmp(preference, "no") == 0) {
                          enb_properties.properties[enb_properties_index]->mme_ip_address[j].ipv4 = 1;
                          enb_properties.properties[enb_properties_index]->mme_ip_address[j].ipv6 = 1;
                      }
                  }
		  // NETWORK_INTERFACES
                  subsetting = config_setting_get_member (setting_enb, ENB_CONFIG_STRING_NETWORK_INTERFACES_CONFIG);
                  if(subsetting != NULL) {
                      if(  (
                              config_setting_lookup_string( subsetting, ENB_CONFIG_STRING_ENB_INTERFACE_NAME_FOR_S1_MME,
                                      (const char **)&enb_interface_name_for_S1_MME)
                           && config_setting_lookup_string( subsetting, ENB_CONFIG_STRING_ENB_IPV4_ADDRESS_FOR_S1_MME,
                                   (const char **)&enb_ipv4_address_for_S1_MME)
                           && config_setting_lookup_string( subsetting, ENB_CONFIG_STRING_ENB_INTERFACE_NAME_FOR_S1U,
                                   (const char **)&enb_interface_name_for_S1U)
                           && config_setting_lookup_string( subsetting, ENB_CONFIG_STRING_ENB_IPV4_ADDR_FOR_S1U,
                                   (const char **)&enb_ipv4_address_for_S1U)
                         )
                     ){
                          enb_properties.properties[enb_properties_index]->enb_interface_name_for_S1U = strdup(enb_interface_name_for_S1U);
                          cidr = enb_ipv4_address_for_S1U;
                          address = strtok(cidr, "/");
                          if (address) {
                              IPV4_STR_ADDR_TO_INT_NWBO ( address, enb_properties.properties[enb_properties_index]->enb_ipv4_address_for_S1U, "BAD IP ADDRESS FORMAT FOR eNB S1_U !\n" );
                          }

                          enb_properties.properties[enb_properties_index]->enb_interface_name_for_S1_MME = strdup(enb_interface_name_for_S1_MME);
                          cidr = enb_ipv4_address_for_S1_MME;
                          address = strtok(cidr, "/");
                          if (address) {
                              IPV4_STR_ADDR_TO_INT_NWBO ( address, enb_properties.properties[enb_properties_index]->enb_ipv4_address_for_S1_MME, "BAD IP ADDRESS FORMAT FOR eNB S1_MME !\n" );
                          }
                      }
                  }
		  // log_config 
		  subsetting = config_setting_get_member (setting_enb, ENB_CONFIG_STRING_LOG_CONFIG);
                  if(subsetting != NULL) {
		    // global 
		    if(config_setting_lookup_string(subsetting, ENB_CONFIG_STRING_GLOBAL_LOG_LEVEL, (const char **)  &glog_level)) {
                      if ((enb_properties.properties[enb_properties_index]->glog_level = map_str_to_int(log_level_names, glog_level)) == -1)
			enb_properties.properties[enb_properties_index]->glog_level = LOG_INFO; 
		      //printf( "\tGlobal log level :\t%s->%d\n",glog_level, enb_properties.properties[enb_properties_index]->glog_level);
		    } else {
                      enb_properties.properties[enb_properties_index]->glog_level = LOG_INFO; 
		    } 
		    if(config_setting_lookup_string(subsetting, ENB_CONFIG_STRING_GLOBAL_LOG_VERBOSITY,(const char **)  &glog_verbosity)) {
                      if ((enb_properties.properties[enb_properties_index]->glog_verbosity = map_str_to_int(log_verbosity_names, glog_verbosity)) == -1)
			enb_properties.properties[enb_properties_index]->glog_verbosity = LOG_MED;
		      //printf( "\tGlobal log verbosity:\t%s->%d\n",glog_verbosity, enb_properties.properties[enb_properties_index]->glog_verbosity);
		    } else {
                      enb_properties.properties[enb_properties_index]->glog_verbosity = LOG_MED; 
		    } 
		    // HW
		    if(config_setting_lookup_string(subsetting, ENB_CONFIG_STRING_HW_LOG_LEVEL, (const char **) &hw_log_level)) {
                      if ((enb_properties.properties[enb_properties_index]->hw_log_level = map_str_to_int(log_level_names,hw_log_level)) == -1)
			enb_properties.properties[enb_properties_index]->hw_log_level = LOG_INFO;
                      //printf( "\tHW log level :\t%s->%d\n",hw_log_level,enb_properties.properties[enb_properties_index]->hw_log_level);
		    } else {
                      enb_properties.properties[enb_properties_index]->hw_log_level = LOG_INFO;
		    } 
		    if(config_setting_lookup_string(subsetting, ENB_CONFIG_STRING_HW_LOG_VERBOSITY, (const char **) &hw_log_verbosity)) {
                      if ((enb_properties.properties[enb_properties_index]->hw_log_verbosity = map_str_to_int(log_verbosity_names,hw_log_verbosity)) == -1)
			enb_properties.properties[enb_properties_index]->hw_log_verbosity = LOG_MED;
                      //printf( "\tHW log verbosity:\t%s->%d\n",hw_log_verbosity, enb_properties.properties[enb_properties_index]->hw_log_verbosity);
		    } else {
                      enb_properties.properties[enb_properties_index]->hw_log_verbosity = LOG_MED; 
		    } 
		    // phy 
		    if(config_setting_lookup_string(subsetting, ENB_CONFIG_STRING_PHY_LOG_LEVEL,(const char **) &phy_log_level)) {
                      if ((enb_properties.properties[enb_properties_index]->phy_log_level = map_str_to_int(log_level_names,phy_log_level)) == -1)
			enb_properties.properties[enb_properties_index]->phy_log_level = LOG_INFO;
                      //printf( "\tPHY log level :\t%s->%d\n",phy_log_level,enb_properties.properties[enb_properties_index]->phy_log_level);
		    } else {
                      enb_properties.properties[enb_properties_index]->phy_log_level = LOG_INFO;
		    } 
		    if(config_setting_lookup_string(subsetting, ENB_CONFIG_STRING_PHY_LOG_VERBOSITY, (const char **)&phy_log_verbosity)) {
                      if ((enb_properties.properties[enb_properties_index]->phy_log_verbosity = map_str_to_int(log_verbosity_names,phy_log_verbosity)) == -1)
			enb_properties.properties[enb_properties_index]->phy_log_verbosity = LOG_MED; 
                      //printf( "\tPHY log verbosity:\t%s->%d\n",phy_log_level,enb_properties.properties[enb_properties_index]->phy_log_verbosity);
		    } else {
                      enb_properties.properties[enb_properties_index]->phy_log_verbosity = LOG_MED; 
		    } 
		    //mac 
		    if(config_setting_lookup_string(subsetting, ENB_CONFIG_STRING_MAC_LOG_LEVEL, (const char **)&mac_log_level)) {
                      if ((enb_properties.properties[enb_properties_index]->mac_log_level = map_str_to_int(log_level_names,mac_log_level)) == -1 )
			enb_properties.properties[enb_properties_index]->mac_log_level = LOG_INFO; 
                      //printf( "\tMAC log level :\t%s->%d\n",mac_log_level,enb_properties.properties[enb_properties_index]->mac_log_level);
		    } else {
                      enb_properties.properties[enb_properties_index]->mac_log_level = LOG_INFO; 
		    } 
		    if(config_setting_lookup_string(subsetting, ENB_CONFIG_STRING_MAC_LOG_VERBOSITY, (const char **)&mac_log_verbosity)) {
                      if ((enb_properties.properties[enb_properties_index]->mac_log_verbosity = map_str_to_int(log_verbosity_names,mac_log_verbosity)) == -1)
			enb_properties.properties[enb_properties_index]->mac_log_verbosity = LOG_MED; 
                      //printf( "\tMAC log verbosity:\t%s->%d\n",mac_log_verbosity,enb_properties.properties[enb_properties_index]->mac_log_verbosity);
		    } else {
                      enb_properties.properties[enb_properties_index]->mac_log_verbosity = LOG_MED; 
		    } 
		    //rlc
		    if(config_setting_lookup_string(subsetting, ENB_CONFIG_STRING_RLC_LOG_LEVEL, (const char **)&rlc_log_level)) {
                      if ((enb_properties.properties[enb_properties_index]->rlc_log_level = map_str_to_int(log_level_names,rlc_log_level)) == -1)
			enb_properties.properties[enb_properties_index]->rlc_log_level = LOG_INFO; 
                      //printf( "\tRLC log level :\t%s->%d\n",rlc_log_level, enb_properties.properties[enb_properties_index]->rlc_log_level);
		    } else {
                      enb_properties.properties[enb_properties_index]->rlc_log_level = LOG_INFO; 
		    } 
		    if(config_setting_lookup_string(subsetting, ENB_CONFIG_STRING_RLC_LOG_VERBOSITY, (const char **)&rlc_log_verbosity)) {
                      if ((enb_properties.properties[enb_properties_index]->rlc_log_verbosity = map_str_to_int(log_verbosity_names,rlc_log_verbosity)) == -1)
			enb_properties.properties[enb_properties_index]->rlc_log_verbosity = LOG_MED; 
                      //printf( "\tRLC log verbosity:\t%s->%d\n",rlc_log_verbosity, enb_properties.properties[enb_properties_index]->rlc_log_verbosity);
		    } else {
                      enb_properties.properties[enb_properties_index]->rlc_log_verbosity = LOG_MED; 
		    } 
		    //pdcp 
		    if(config_setting_lookup_string(subsetting, ENB_CONFIG_STRING_PDCP_LOG_LEVEL, (const char **)&pdcp_log_level)) {
                      if ((enb_properties.properties[enb_properties_index]->pdcp_log_level = map_str_to_int(log_level_names,pdcp_log_level)) == -1)
			enb_properties.properties[enb_properties_index]->pdcp_log_level = LOG_INFO; 
                      //printf( "\tPDCP log level :\t%s->%d\n",pdcp_log_level, enb_properties.properties[enb_properties_index]->pdcp_log_level);
		    } else {
                      enb_properties.properties[enb_properties_index]->pdcp_log_level = LOG_INFO; 
		    } 
		    if(config_setting_lookup_string(subsetting, ENB_CONFIG_STRING_PDCP_LOG_VERBOSITY, (const char **)&pdcp_log_verbosity)) {
                      enb_properties.properties[enb_properties_index]->pdcp_log_verbosity = map_str_to_int(log_verbosity_names,pdcp_log_verbosity);
                      //printf( "\tPDCP log verbosity:\t%s->%d\n",pdcp_log_verbosity, enb_properties.properties[enb_properties_index]->pdcp_log_verbosity);
		    } else {
                      enb_properties.properties[enb_properties_index]->pdcp_log_verbosity = LOG_MED; 
		    } 
		    //rrc
		    if(config_setting_lookup_string(subsetting, ENB_CONFIG_STRING_RRC_LOG_LEVEL, (const char **)&rrc_log_level)) {
                      if ((enb_properties.properties[enb_properties_index]->rrc_log_level = map_str_to_int(log_level_names,rrc_log_level)) == -1 )
			enb_properties.properties[enb_properties_index]->rrc_log_level = LOG_INFO; 
                      //printf( "\tRRC log level :\t%s->%d\n",rrc_log_level,enb_properties.properties[enb_properties_index]->rrc_log_level);
		    } else {
                      enb_properties.properties[enb_properties_index]->rrc_log_level = LOG_INFO; 
		    } 
		    if(config_setting_lookup_string(subsetting, ENB_CONFIG_STRING_RRC_LOG_VERBOSITY, (const char **)&rrc_log_verbosity)) {
                      if ((enb_properties.properties[enb_properties_index]->rrc_log_verbosity = map_str_to_int(log_verbosity_names,rrc_log_verbosity)) == -1)
			enb_properties.properties[enb_properties_index]->rrc_log_verbosity = LOG_MED; 
                      //printf( "\tRRC log verbosity:\t%s->%d\n",rrc_log_verbosity,enb_properties.properties[enb_properties_index]->rrc_log_verbosity);
		    } else {
                      enb_properties.properties[enb_properties_index]->rrc_log_verbosity = LOG_MED; 
		    } 
		    
                  } else { // not configuration is given 
		    enb_properties.properties[enb_properties_index]->glog_level = LOG_INFO; 
		    enb_properties.properties[enb_properties_index]->glog_verbosity = LOG_MED; 
		    enb_properties.properties[enb_properties_index]->hw_log_level = LOG_INFO;
		    enb_properties.properties[enb_properties_index]->hw_log_verbosity = LOG_MED; 
		    enb_properties.properties[enb_properties_index]->phy_log_level = LOG_INFO;
		    enb_properties.properties[enb_properties_index]->phy_log_verbosity = LOG_MED; 
		    enb_properties.properties[enb_properties_index]->mac_log_level = LOG_INFO; 
		    enb_properties.properties[enb_properties_index]->mac_log_verbosity = LOG_MED;
		    enb_properties.properties[enb_properties_index]->rlc_log_level = LOG_INFO; 
		    enb_properties.properties[enb_properties_index]->rlc_log_verbosity = LOG_MED;
		    enb_properties.properties[enb_properties_index]->pdcp_log_level = LOG_INFO; 
		    enb_properties.properties[enb_properties_index]->pdcp_log_verbosity = LOG_MED; 
		    enb_properties.properties[enb_properties_index]->rrc_log_level = LOG_INFO; 
		    enb_properties.properties[enb_properties_index]->rrc_log_verbosity = LOG_MED; 
		  }

                  enb_properties_index += 1;
                  break;
              }
          }
      }
  }
  enb_properties.number = num_enb_properties;

  AssertError (enb_properties_index == num_enb_properties, parse_errors ++,
          "Failed to parse eNB configuration file %s, mismatch between %u active eNBs and %u corresponding defined eNBs !\n",
          lib_config_file_name_pP, num_enb_properties, enb_properties_index);

  AssertFatal (parse_errors == 0,
               "Failed to parse eNB configuration file %s, found %d error%s !\n",
               lib_config_file_name_pP, parse_errors, parse_errors > 1 ? "s" : "");
  enb_config_display();
  return &enb_properties;

}

const Enb_properties_array_t *enb_config_get(void) {
    return &enb_properties;
}

