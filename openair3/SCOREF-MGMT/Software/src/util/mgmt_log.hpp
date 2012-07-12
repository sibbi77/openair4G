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
 * \file mgmt_log.hpp
 * \brief A container for a basic logging utility
 * \company EURECOM
 * \date 2012
 * \author Baris Demiray
 * \email: baris.demiray@eurecom.fr
 * \note none
 * \bug none
 * \warning none
*/

#ifndef MGMT_LOG_HPP_
#define MGMT_LOG_HPP_

#include <string>
#include <map>
using namespace std;

/**
 * A container for a basic logging utility
 */
class Logger {
	public:
		enum LOG_LEVEL {
			DEBUG = 0,
			INFO = 1,
			WARNING = 2,
			ERROR = 3
		};

	public:
		/**
		 * Constructor for Logger class
		 *
		 * @param logLevel Initial log level (default is INFO)
		 */
		Logger(Logger::LOG_LEVEL logLevel = Logger::INFO);
		/**
		 * Destructor for Logger class
		 */
		~Logger();

	public:
		/**
		 * Prints given log message at DEBUG level
		 *
		 * @param message Log message
		 */
		void debug(const string& message);
		/**
		 * Prints given log message at INFO level
		 *
		 * @param message Log message
		 */
		void info(const string& message);
		/**
		 * Prints given log message at WARNING level
		 *
		 * @param message Log message
		 */
		void warning(const string& message);
		/**
		 * Prints given log message at ERROR level
		 *
		 * @param message Log message
		 */
		void error(const string& message);
		/**
		 * Prints given log message at given level
		 *
		 * @param message Log message
		 * @param level Log level
		 */
		void log(const string& message, Logger::LOG_LEVEL level);
		/**
		 * Updates configured log level with incoming information
		 *
		 * @param logLevel New log level of type Logger::LOG_LEVEL
		 */
		void setLogLevel(Logger::LOG_LEVEL logLevel);

	private:
		/**
		 * Configured log level
		 */
		Logger::LOG_LEVEL logLevel;
		/**
		 * Log level string map
		 */
		map<LOG_LEVEL, string> logLevelString;
};

#endif /* MGMT_LOG_HPP_ */
