/*
 * libretroshare/src/rsiface: rsnetwork.h
 *
 * RetroShare C++ Interface.
 *
 * Copyright 2004-2008 by Robert Fernie.
 *
 * This library is free software; you can redistribute it and/or
 * modify it under the terms of the GNU Library General Public
 * License Version 2 as published by the Free Software Foundation.
 *
 * This library is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * Library General Public License for more details.
 *
 * You should have received a copy of the GNU Library General Public
 * License along with this library; if not, write to the Free Software
 * Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA 02111-1307
 * USA.
 *
 * Please report all bugs and problems to "retroshare.project@gmail.com".
 *
 */

#pragma once

/* Net Mode */
const uint32_t RS_NETMODE_UDP		= 0x0001;
const uint32_t RS_NETMODE_UPNP		= 0x0002;
const uint32_t RS_NETMODE_EXT		= 0x0003;
const uint32_t RS_NETMODE_HIDDEN	= 0x0004;
const uint32_t RS_NETMODE_UNREACHABLE	= 0x0005;

/* Hidden Type */
const uint32_t RS_HIDDEN_TYPE_NONE	= 0x0000;
const uint32_t RS_HIDDEN_TYPE_UNKNOWN	= 0x0001;
const uint32_t RS_HIDDEN_TYPE_TOR	= 0x0002;
const uint32_t RS_HIDDEN_TYPE_I2P	= 0x0004;
/* mask to match all valid hidden types */
const uint32_t RS_HIDDEN_TYPE_MASK	= RS_HIDDEN_TYPE_I2P | RS_HIDDEN_TYPE_TOR;

/* Visibility */
const uint32_t RS_VS_DISC_OFF		= 0x0000;
const uint32_t RS_VS_DISC_MINIMAL	= 0x0001;
const uint32_t RS_VS_DISC_FULL		= 0x0002;

const uint32_t RS_VS_DHT_OFF		= 0x0000;
const uint32_t RS_VS_DHT_PASSIVE	= 0x0001;
const uint32_t RS_VS_DHT_FULL		= 0x0002;

/* LinkType Flags */

// CONNECTION
const uint32_t RS_NET_CONN_TRANS_MASK			= 0x0000ffff;
const uint32_t RS_NET_CONN_TRANS_TCP_MASK		= 0x0000000f;
const uint32_t RS_NET_CONN_TRANS_TCP_UNKNOWN		= 0x00000001;
const uint32_t RS_NET_CONN_TRANS_TCP_LOCAL		= 0x00000002;
const uint32_t RS_NET_CONN_TRANS_TCP_EXTERNAL		= 0x00000004;

const uint32_t RS_NET_CONN_TRANS_UDP_MASK		= 0x000000f0;
const uint32_t RS_NET_CONN_TRANS_UDP_UNKNOWN		= 0x00000010;
const uint32_t RS_NET_CONN_TRANS_UDP_DIRECT		= 0x00000020;
const uint32_t RS_NET_CONN_TRANS_UDP_PROXY		= 0x00000040;
const uint32_t RS_NET_CONN_TRANS_UDP_RELAY		= 0x00000080;

const uint32_t RS_NET_CONN_TRANS_OTHER_MASK		= 0x00000f00;

const uint32_t RS_NET_CONN_TRANS_UNKNOWN		= 0x00001000;


const uint32_t RS_NET_CONN_SPEED_MASK			= 0x000f0000;
const uint32_t RS_NET_CONN_SPEED_UNKNOWN		= 0x00000000;
const uint32_t RS_NET_CONN_SPEED_TRICKLE		= 0x00010000;
const uint32_t RS_NET_CONN_SPEED_LOW			= 0x00020000;
const uint32_t RS_NET_CONN_SPEED_NORMAL			= 0x00040000;
const uint32_t RS_NET_CONN_SPEED_HIGH			= 0x00080000;

const uint32_t RS_NET_CONN_QUALITY_MASK			= 0x00f00000;
const uint32_t RS_NET_CONN_QUALITY_UNKNOWN		= 0x00000000;

// THIS INFO MUST BE SUPPLIED BY PEERMGR....
const uint32_t RS_NET_CONN_TYPE_MASK			= 0x0f000000;
const uint32_t RS_NET_CONN_TYPE_UNKNOWN			= 0x00000000;
const uint32_t RS_NET_CONN_TYPE_ACQUAINTANCE		= 0x01000000;
const uint32_t RS_NET_CONN_TYPE_FRIEND			= 0x02000000;
const uint32_t RS_NET_CONN_TYPE_SERVER			= 0x04000000;
const uint32_t RS_NET_CONN_TYPE_CLIENT			= 0x08000000;

// working state of proxy

const uint32_t RS_NET_PROXY_STATUS_UNKNOWN  = 0x0000 ;
const uint32_t RS_NET_PROXY_STATUS_OK  	    = 0x0001 ;

class RsNetwork;
extern RsNetwork *rsNetwork;

class RsNetwork
{
public:
	virtual bool getProxyServer(const uint32_t type, std::string &addr, uint16_t &port,uint32_t& status_flags) = 0;
	virtual bool setProxyServer(const uint32_t type, const std::string &addr, const uint16_t port) = 0;

	virtual void getIPServersList(std::list<std::string>& ip_servers) = 0;
	virtual void allowServerIPDetermination(bool) = 0;
	virtual bool resetOwnExternalAddressList() = 0;
	virtual bool getAllowServerIPDetermination() = 0 ;

	//virtual	bool setLocalAddress(const std::string &addr, uint16_t port) = 0;	// these shouldn't be needed
	//virtual	bool setExtAddress(  const std::string &addr, uint16_t port) = 0;

	virtual	bool setDynDNS(const std::string &addr) = 0;
	virtual	bool setNetworkMode(uint32_t netMode) = 0;
	virtual bool setVisState(uint16_t vs_disc, uint16_t vs_dht)	= 0;

	/* Service permission flags */

	virtual ServicePermissionFlags servicePermissionFlags(const RsPgpId& gpg_id) = 0;
	virtual ServicePermissionFlags servicePermissionFlags(const RsPeerId& ssl_id) = 0;
	virtual void setServicePermissionFlags(const RsPgpId& gpg_id,const ServicePermissionFlags& flags) = 0;

	virtual bool setPeerMaximumRates(const RsPgpId& pid,uint32_t maxUploadRate,uint32_t maxDownloadRate) =0;
	virtual bool getPeerMaximumRates(const RsPeerId& pid,uint32_t& maxUploadRate,uint32_t& maxDownloadRate) =0;
	virtual bool getPeerMaximumRates(const RsPgpId& pid,uint32_t& maxUploadRate,uint32_t& maxDownloadRate) =0;

	virtual bool setHiddenNode(const std::string &address, uint16_t port) = 0;
};
