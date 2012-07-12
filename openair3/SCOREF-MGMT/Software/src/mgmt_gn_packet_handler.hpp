/*******************************************************************************

  Eurecom OpenAirInterface
  Copyright(c) 1999 - 2012 Eurecom

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

/*!
 * \file mgmt_gn_packet_handler.hpp
 * \brief A container with packet handling functionality, all the packets read on the socket is passed here
 * \company EURECOM
 * \date 2012
 * \author Baris Demiray
 * \email: baris.demiray@eurecom.fr
 * \note none
 * \bug none
 * \warning none
*/

#ifndef MGMT_GN_PACKET_HANDLER_HPP_
#define MGMT_GN_PACKET_HANDLER_HPP_

#include <boost/array.hpp>
using namespace boost;

#include "packets/mgmt_gn_packet_comm_profile_request.hpp"
#include "packets/mgmt_gn_packet_location_table_response.hpp"
#include "packets/mgmt_gn_packet_get_configuration.hpp"
#include "packets/mgmt_gn_packet_wireless_state_response.hpp"
#include "packets/mgmt_gn_packet_network_state.hpp"
#include "mgmt_gn_packet_factory.hpp"
#include "mgmt_information_base.hpp"
#include "util/mgmt_log.hpp"
#include "mgmt_client.hpp"

/**
 * A container with packet handling functionality, all the packets read on
 * the socket is passed here
 */
class GeonetMessageHandler {
	public:
		/**
		 * Constructor for GeonetMessageHandler class
		 *
		 * @param mib ManagementInformationBase reference
		 * @param logger Logger object reference
		 */
		GeonetMessageHandler(ManagementInformationBase& mib, Logger& logger);
		/**
		 * Destructor for GeonetMessageHandler class
		 */
		~GeonetMessageHandler();

	public:
		/**
		 * Takes buffers of Geonet messages and dispatches them to relevant private
		 * methods after building a GeonetPacket object out of them
		 *
		 * @param packetBuffer Buffer carrying Geonet message
		 * @param client Socket information of sender client
		 * @return pointer to the response of type GeonetMessage
		 */
		GeonetPacket* handleGeonetMessage(const vector<unsigned char>& packetBuffer, const udp::endpoint& client);

	private:
		/**
		 * Handles a Get Configuration message creating its reply utilizing relevant
		 * PacketFactory method
		 *
		 * @param packet Pointer to Get Configuration packet object
		 * @return Reply to Get Configuration message
		 */
		GeonetPacket* handleGetConfigurationEvent(GeonetGetConfigurationEventPacket* packet);
		/**
		 * Handles a Network State message and triggers an update at MIB
		 *
		 * @param packet Pointer to Network State packet
		 * @return true on success, false otherwise
		 */
		bool handleNetworkStateEvent(GeonetNetworkStateEventPacket* packet);
		/**
		 * Handles a Wireless State Response message and triggers an update at MIB
		 *
		 * @param packet Pointer to incoming Wireless State Response packet
		 * @return true on success, false otherwise
		 */
		bool handleWirelessStateResponseEvent(GeonetWirelessStateResponseEventPacket* packet);
		/**
		 * Handles a Location Table Response packet
		 *
		 * @param Pointer to a Location Table Response packet
		 * @return true on success, false otherwise
		 */
		bool handleLocationTableResponse(GeonetLocationTableResponseEventPacket* packet);
		/**
		 * Handles a Communication Profile Request event message and creates a
		 * Communication Profile Response packet
		 *
		 * @param Pointer to a Communication Profile Request packet
		 * @return Pointer to a Communication Profile Response packet
		 */
		GeonetPacket* handleCommunicationProfileRequestEvent(GeonetCommunicationProfileRequestPacket* packet);

	private:
		/**
		 * GeonetPacketFactory object to hide packet generation details from PacketHandler class
		 */
		GeonetPacketFactory* packetFactory;
		/**
		 * ManagementInformationBase object to fetch necessary information when needed
		 */
		ManagementInformationBase& mib;
		/**
		 * State map holding clients' states
		 */
		map<ManagementClient, ManagementClient::ManagementClientState> clientState;
		/**
		 * Logger object reference
		 */
		Logger& logger;
};

#endif /* MGMT_GN_PACKET_HANDLER_HPP_ */
