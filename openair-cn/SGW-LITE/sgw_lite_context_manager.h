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

  Address      : Eurecom, Compus SophiaTech 450, route des chappes, 06451 Biot, France.

 *******************************************************************************/
/*! \file sgw_lite_context_manager.h
* \brief
* \author Lionel Gauthier
* \company Eurecom
* \email: lionel.gauthier@eurecom.fr
*/
#ifndef SGW_LITE_CONTEXT_MANAGER_H_
#define SGW_LITE_CONTEXT_MANAGER_H_

#include "commonDef.h"
#include "common_types.h"
#include "mme_app_ue_context.h" // for cgi_t
#include "hashtable.h"
#include "obj_hashtable.h"

/********************************
*     P-GW contexts             *
*********************************/
typedef struct pgw_eps_bearer_entry_gtp_based_S5_S8_only_s {
  ebi_t                eps_bearer_id;                         ///< An EPS bearer identity uniquely identifies an EPS bearer for one UE accessing via E-UTRAN
  // TO DO traffic_flow_template_t tft;                   ///< Traffic Flow Template

  ip_address_t         s_gw_address_in_use_up;            ///< The IP address of the S-GW currently used for sending user plane traffic.
  Teid_t               s_gw_teid_for_S5_S8_up;            ///< S-GW Tunnel Endpoint Identifier for the S5/S8 interface for the user plane.

  ip_address_t         p_gw_ip_address_for_S5_S8_up;      ///< P-GW IP address for user plane data received from PDN GW.
  Teid_t               p_gw_teid_for_S5_S8_up;            ///< P-GW Tunnel Endpoint Identifier for the GTP Based S5/S8 interface for user plane.

  // TO BE CHECKED
  BearerQOS_t          eps_bearer_qos;                    ///< ARP, GBR, MBR, QCI.
  // NOT NEEDED        charging_id                        ///< Charging identifier, identifies charging records generated by S-GW and PDN GW.

} pgw_eps_bearer_entry_t;

typedef struct pgw_pdn_connection_s {
  //ip_addresses;                                       ///< IPv4 address and/or IPv6 prefix
  pdn_type_t           pdn_type;                       ///< IPv4, IPv6, or IPv4v6
  ip_address_t         s_gw_address_in_use_cp;         ///< The IP address of the S-GW currently used for sending control plane signalling.
  Teid_t               s_gw_teid_for_S5_S8_cp;         ///< S-GW Tunnel Endpoint Identifier for the S5/S8 interface for the control plane. (For GTP-based S5/S8 only).
  ip_address_t         s_gw_address_in_use_up;         ///< The IP address of the S-GW currently used for sending user plane traffic. (For PMIP-based S5/S8 only).
  // NOT NEEDED s_gw_gre_key_for_dl_traffic_up         ///< Serving GW assigned GRE Key for the S5/S8 interface for the user plane for downlink traffic. (For PMIP-based S5/S8 only).
  ip_address_t         p_gw_ip_address_for_S5_S8_cp;   ///< P-GW IP address for the S5/S8 for the control plane signalling.
  Teid_t               p_gw_teid_for_S5_S8_cp;         ///< P-GW Tunnel Endpoint Identifier for the S5/S8 control plane interface. (For GTP-based S5/S8 only).
  ip_address_t         p_gw_address_in_use_up;         ///< The IP address of the P-GW currently used for sending user plane traffic. (For PMIP-based S5/S8 only).
  // NOT NEEDED p_gw_gre_key_for_uplink_traffic_up     ///< PDN GW assigned GRE Key for the S5/S8 interface for the user plane for uplink traffic. (For PMIP-based S5/S8 only).
  // NOT NEEDED MS Info Change Reporting Action        ///< Denotes whether the MME and/or the SGSN is/are requested to send changes in User Location Information change for this bearer.
  // NOT NEEDED CSG Information Reporting Action       ///< Denotes whether the MME and/or the SGSN is/are requested to send changes in User CSG Information change for this bearer.
  ///  This field denotes separately whether the MME/SGSN are requested to send changes in User CSG Information for (a) CSG cells,
  ///  (b) hybrid cells in which the subscriber is a CSG member, and (c) hybrid cells in which the subscriber is not a CSG member, or any combination of the above.
  ebi_t
  default_bearer;                 ///< Identifies the default bearer within the PDN connection by its EPS Bearer Id. The default bearer is the one which is established first within the PDN connection. (For GTP based
  ///  S5/S8 or for PMIP based S5/S8 if multiple PDN connections to the same APN are supported).

  hash_table_t         *pgw_eps_bearers;
} pgw_pdn_connection_t;


typedef struct pgw_apn_s {
  APN_t                apn_in_use;                     ///< The APN currently used, as received from the S-GW.
  ambr_t               apn_ambr;                       ///<  The maximum aggregated uplink and downlink MBR values to be shared across all Non-GBR bearers,
  ///   which are established for this APN.
  obj_hash_table_t    *pdn_connections;                ///<  For each PDN Connection within the APN

} pgw_apn_t;


// The PDN GW maintains the following EPS bearer context information for UEs.
// For emergency attached UEs which are not authenticated, IMEI is stored in context.
typedef struct pgw_eps_bearer_context_information_s {
  Imsi_t               imsi;                           ///< IMSI (International Mobile Subscriber Identity) is the subscriber permanent identity.
  int8_t               imsi_unauthenticated_indicator; ///< This is an IMSI indicator to show the IMSI is unauthenticated.
  // TO BE CHECKED me_identity_t    me_identity;       ///< Mobile Equipment Identity (e.g. IMEI/IMEISV).
  char                 msisdn[MSISDN_LENGTH];          ///< The basic MSISDN of the UE. The presence is dictated by its storage in the HSS.
  // NOT NEEDED selected_cn_operator_id                ///< Selected core network operator identity (to support networksharing as defined in TS 23.251
  rat_type_t           rat_type;                       ///< Current RAT
  // NOT NEEDED Trace reference                        ///< Identifies a record or a collection of records for a particular trace.
  // NOT NEEDED Trace type                             ///< Indicates the type of trace
  // NOT NEEDED Trigger id                             ///< Identifies the entity that initiated the trace
  // NOT NEEDED OMC identity                           ///< Identifies the OMC that shall receive the trace record(s).

  // TO BE CONTINUED...
  obj_hash_table_t    *apns;
} pgw_eps_bearer_context_information_t;

/********************************
*     S-GW contexts             *
*********************************/
//--------------------------------
// EPS Bearer entry
//--------------------------------

// A primary key for a EPS Bearer entry  can be a tuple (eps bearer id, imsi)
typedef struct sgw_eps_bearer_entry_s {
#if defined (ENABLE_USE_GTPU_IN_KERNEL)
  PAA_t                paa;
#endif
  ebi_t                eps_bearer_id;                         ///< An EPS bearer identity uniquely identifies an EPS bearer for one UE accessing via E-UTRAN
  // TO DO traffic_flow_template_t tft;                   ///< Traffic Flow Template

  ip_address_t         p_gw_address_in_use_up;            ///< The IP address of the P-GW currently used for sending user plane traffic. (For GTP-based S5/S8 only).
  Teid_t               p_gw_teid_for_S5_S8_up;            ///< P-GW Tunnel Endpoint Identifier for the S5/S8 interface for the user plane. (For GTP-based S5/S8 only).

  ip_address_t         s_gw_ip_address_for_S5_S8_up;      ///< S-GW IP address for user plane data received from PDN GW. (For GTP-based S5/S8 only).
  Teid_t               s_gw_teid_for_S5_S8_up;            ///< S-GW Tunnel Endpoint Identifier for the S5/S8 interface for the user plane. (For GTP-based S5/S8 only).

  ip_address_t
  s_gw_ip_address_for_S1u_S12_S4_up; ///< S-GW IP address for the S1-u interface (Used by the eNodeB), for the S12 interface (used by the RNC) and for the S4 interface (used by the SGSN).
  Teid_t
  s_gw_teid_for_S1u_S12_S4_up;       ///< S-GW Tunnel Endpoint Identifier for the S1-u interface, for the S12 interface (used by the RNC) and for the S4 interface (used by the SGSN).

  ip_address_t         enb_ip_address_for_S1u;            ///< eNodeB IP address for the S1-u interface (Used by the S-GW).
  Teid_t               enb_teid_for_S1u;                  ///< eNodeB Tunnel Endpoint Identifier for the S1-u interface.

  // TO BE CHECKED
  BearerQOS_t          eps_bearer_qos;                    ///< ARP, GBR, MBR, QCI.
  // NOT NEEDED        charging_id                        ///< Charging identifier, identifies charging records generated by S-GW and PDN GW.

} sgw_eps_bearer_entry_t;


typedef struct sgw_pdn_connection_s {
  APN_t                apn_in_use;                     ///< The APN currently used, as received from the MME or S4 SGSN.
  // NOT NEEDED NOW eps_pdn_charging                   ///< The charging characteristics of this PDN connection, e.g.normal, prepaid, flat-rate and/or hot billing.
  // NOT IMPLEMENTED NOW
  ip_address_t         p_gw_address_in_use_cp;         ///< The IP address of the P-GW currently used for sending control plane signalling.
  // NOT IMPLEMENTED NOW
  Teid_t               p_gw_teid_for_S5_S8_cp;         ///< P-GW Tunnel Endpoint Identifier for the S5/S8 interface for the control plane. (For GTP-based S5/S8 only).
  // NOT IMPLEMENTED NOW
  ip_address_t         p_gw_address_in_use_up;         ///< The IP address of the P-GW currently used for sending user plane traffic. (For PMIP-based S5/S8 only)
  // NOT NEEDED p_gw_gre_key_for_uplink_traffic_up     ///< PDN GW assigned GRE Key for the S5/S8 interface for the user plane for uplink traffic. (For PMIP-based S5/S8 only)
  ip_address_t         s_gw_ip_address_for_S5_S8_cp;   ///< S-GW IP address for the S5/S8 for the control plane signalling.
  Teid_t               s_gw_teid_for_S5_S8_cp;         ///< S-GW Tunnel Endpoint Identifier for the S5/S8 control plane interface. (For GTP-based S5/S8 only).
  ip_address_t         s_gw_address_in_use_up;         ///< The IP address of the S-GW currently used for sending user plane traffic. (For PMIP-based S5/S8 only)
  // NOT NEEDED s_gw_gre_key_for_dl_traffic_up         ///< user plane for downlink traffic. (For PMIP-based S5/S8 only)
  ebi_t                default_bearer;                 ///< Identifies the default bearer within the PDN connection by its EPS Bearer Id. (For PMIP based S5/S8.)

  // eps bearers
  hash_table_t         *sgw_eps_bearers;

} sgw_pdn_connection_t;

// The Serving GW maintains the following EPS bearer context information for UEs.
// Struct sgw_eps_bearer_context_information_t contain the context fields for one UE.
typedef struct sgw_eps_bearer_context_information_s {
  Imsi_t               imsi;                           ///< IMSI (International Mobile Subscriber Identity) is the subscriber permanent identity.
  int8_t               imsi_unauthenticated_indicator; /// This is an IMSI indicator to show the IMSI is unauthenticated.
  // TO BE CHECKED me_identity_t    me_identity;       ///< Mobile Equipment Identity (e.g. IMEI/IMEISV).
  char                 msisdn[MSISDN_LENGTH];          ///< The basic MSISDN of the UE. The presence is dictated by its storage in the HSS.
  // NOT NEEDED selected_cn_operator_id                ///< Selected core network operator identity (to support networksharing as defined in TS 23.251
  Teid_t               mme_teid_for_S11;               ///< MME Tunnel Endpoint Identifier for the S11 interface
  ip_address_t         mme_ip_address_for_S11;         ///< MME IP address the S11 interface.
  Teid_t               s_gw_teid_for_S11_S4;           ///< S-GW Tunnel Endpoint Identifier for the S11 Interface and the S4 Interface (control plane)
  ip_address_t         s_gw_ip_address_for_S11_S4;     ///< S-GW IP address for the S11 interface and the S4 Interface (control plane).
  // NOT NEEDED Trace reference                        ///< Identifies a record or a collection of records for a particular trace.
  // NOT NEEDED Trace type                             ///< Indicates the type of trace
  // NOT NEEDED Trigger id                             ///< Identifies the entity that initiated the trace
  // NOT NEEDED OMC identity                           ///< Identifies the OMC that shall receive the trace record(s).
  cgi_t                last_known_cell_Id;             ///< This is the last location of the UE known by the network
  // NOT NEEDED NOW Last known Cell Id age             ///< This is the age of the above UE location information

  // ONLY ONE PDN CONNECTION
  // Do not know now what is the key for this hashtable
  //obj_hash_table_t      *pdn_connections;
  sgw_pdn_connection_t   pdn_connection;

  /* S11 specific parameter. Not used in standalone mode */
  void                  *trxn;
  uint32_t               peer_ip;

  SgwCreateSessionRequest saved_message;
} sgw_eps_bearer_context_information_t;

/********************************
*     Paired contexts           *
*********************************/
// data entry for s11_bearer_context_information_hashtable
// like this if needed in future, the split of S and P GW should be easier.
typedef struct s_plus_p_gw_eps_bearer_context_information_s {
  sgw_eps_bearer_context_information_t sgw_eps_bearer_context_information;
  pgw_eps_bearer_context_information_t pgw_eps_bearer_context_information;
} s_plus_p_gw_eps_bearer_context_information_t;


// data entry for s11teid2mme_hashtable
typedef struct mme_sgw_tunnel_s {
  uint32_t local_teid;   ///< Tunnel endpoint Identifier
  uint32_t remote_teid;  ///< Tunnel endpoint Identifier
} mme_sgw_tunnel_t;

// data entry for s1uteid2enb_hashtable
typedef struct enb_sgw_s1u_tunnel_s {
  uint32_t      local_teid;             ///< S-GW Tunnel endpoint Identifier
  uint32_t      remote_teid;            ///< eNB Tunnel endpoint Identifier
  ip_address_t  enb_ip_address_for_S11; ///< eNB IP address the S1U interface.
} enb_sgw_s1u_tunnel_t;


void                                   sgw_lite_display_s11teid2mme_mappings(void);
void                                   sgw_lite_display_s11_bearer_context_information_mapping(void);
void                                   pgw_lite_cm_free_apn(pgw_apn_t *apnP);


Teid_t                                 sgw_lite_get_new_S11_tunnel_id(void);
mme_sgw_tunnel_t *                     sgw_lite_cm_create_s11_tunnel(Teid_t remote_teid, Teid_t local_teid);
int                                    sgw_lite_cm_remove_s11_tunnel(Teid_t local_teid);
sgw_eps_bearer_entry_t *               sgw_lite_cm_create_eps_bearer_entry(void);
sgw_pdn_connection_t *                 sgw_lite_cm_create_pdn_connection(void);
void                                   sgw_lite_cm_free_pdn_connection(sgw_pdn_connection_t *pdn_connectionP);
s_plus_p_gw_eps_bearer_context_information_t * sgw_lite_cm_create_bearer_context_information_in_collection(Teid_t teid);
void                                   sgw_lite_cm_free_s_plus_p_gw_eps_bearer_context_information(s_plus_p_gw_eps_bearer_context_information_t *contextP);
int                                    sgw_lite_cm_remove_bearer_context_information(Teid_t teid);
sgw_eps_bearer_entry_t *               sgw_lite_cm_create_eps_bearer_entry_in_collection(hash_table_t *eps_bearersP, ebi_t eps_bearer_idP);
int                                    sgw_lite_cm_remove_eps_bearer_entry(hash_table_t *eps_bearersP, ebi_t eps_bearer_idP);

#endif /* SGW_LITE_CONTEXT_MANAGER_H_ */
