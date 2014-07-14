/*-
 * Copyright (c) 2012-2014 Darran Hunt (darran [at] hunt dot net dot nz)
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 * 1. Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 * 2. Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in the
 *    documentation and/or other materials provided with the distribution.
 *
 * THIS SOFTWARE IS PROVIDED ``AS IS'' AND ANY EXPRESS OR IMPLIED WARRANTIES,
 * INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY
 * AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED.  IN NO EVENT SHALL
 * THE CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL,
 * EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO,
 * PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS;
 * OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY,
 * WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR
 * OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF
 * ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */

/*
 * @file WiFly RN-XV soft AP methods 
 */
 
#include "WiFlyHQ.h"

/* Restore soft AP settings to a default state */
boolean WiFly::setAPModeDefaults(void)
{
    if (setAPModeBeacon(102) &
        setAPModeLinkMonitor(3600) &
        setAPModePassphrase("") &
        setAPModeProbe(5) &
        setAPModeReboot(0) &
        setAPModeSSID(""))
    {
        return true;
    } else {
        return false;
    }
}

 boolean WiFly::setAPModeBeacon(const uint16_t value)
{
    // Sets the apmode beacon interval in milliseconds
    // Default: 102
    return setopt(PSTR("set apmode beacon"), value);
}

boolean WiFly::setAPModeLinkMonitor(const uint16_t value)
{
    // This command is used in soft AP mode to detect if the individual client devices are
    // active and in range of the module.
    // Default: 3600
    return setopt(PSTR("set apmode link_monitor"), value);
}

boolean WiFly::setAPModePassphrase(const char *buf)
{
    // This command sets the soft AP mode passphrase to be used for WPA2-AES encryption.
    // Default: NULL
    return setopt(PSTR("set apmode passphrase"), buf);
}

boolean WiFly::setAPModeProbe(const uint16_t value)
{
    // Sets the apmode probe timeout in seconds (apmode mode only).
    // Default: 5
    return setopt(PSTR("set apmode probe"), value);
}

boolean WiFly::setAPModeReboot(const uint16_t value)
{
    // Sets the reboot timer.
    // Default: 0
    return setopt(PSTR("set apmode reboot"), value);
}

boolean WiFly::setAPModeSSID(const char *buf)
{
    // This command sets the soft AP mode network name (SSID) to be broadcast where
    // *buf is the SSID.
    // Default: NULL
    return setopt(PSTR("set apmode ssid"), buf);
}

/**
 * Create an Access Point.
 * The WiFly is assigned IP address 169.254.1.1.
 * @param ssid the SSID to use for the network
 * @param passphrase is the password
 * @param channel the WiFi channel to use; 1 to 13.
 * @retval true - successfully create Ad Hoc network
 * @retval false - failed
 * @note the WiFly is rebooted as the final step of this command.
 */
boolean WiFly::createAP(const char *ssid, const char *passphrase, uint8_t channel)
{
    startCommand();
    setJoin(WIFLY_WLAN_JOIN_AP);
    setChannel(channel);
    setAPModeSSID(ssid);
    setAPModePassphrase(passphrase);
    setDHCP(WIFLY_DHCP_MODE_SERVER);
    setIP(F("169.254.1.1"));
	setNetmask(F("255.255.255.0"));
	setGateway("169.254.1.1");
    
    save();
    finishCommand();
    reboot();
    return true;
}
/**
 * Soft Access Point
 * This does *not* survive a reboot
 * @param buff the SSID to use for the network
 * @retval true - successfully create Access Point
 * @retval false - failed
 */
boolean WiFly::setSoftAP(const char *ssid, const char *passphrase, uint8_t channel)
{
    char buf[4];
    if (!startCommand()) {
	    return false;
    }

    send_P(PSTR("apmode "));
    send(ssid);
    send_P(PSTR(" "));
    simple_utoa(channel, 10, buf, sizeof(buf));
    send(buf);
    send_P(PSTR(" "));
    send(passphrase);
    
    finishCommand();
	return true;
}
boolean WiFly::setSoftAP()
{
    return setopt(PSTR("apmode"));
}
