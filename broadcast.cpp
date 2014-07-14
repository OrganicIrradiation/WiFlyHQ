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
 * @file WiFly RN-XV broadcast parameters
 * Controls the broadcast hello/heartbeat UDP message.
 */
 
#include "WiFlyHQ.h"

/* Restore broadcast settings to a default state */
boolean WiFly::setBroadcastDefaults(void)
{
    if (setBroadcastAddress("255.255.255.255") &
        setBroadcastBackup("0.0.0.0") &
        setBroadcastInterval(7) &
        setBroadcastPort(55555) &
        setBroadcastRemote(0))
    {
        return true;
    } else {
        return false;
    }
}

boolean WiFly::setBroadcastAddress(const char *buf)
{
    // Sets the address to which the UDP hello/heartbeat message is sent.
    // Default: 255.255.255.255
    return setopt(PSTR("set broadcast address"), buf);
}
boolean WiFly::setBroadcastAddress(const __FlashStringHelper *buf)
{
    return setopt(PSTR("set broadcast address"), NULL, buf);
}

boolean WiFly::setBroadcastBackup(const char *buf)
{
    // Sets the secondary broadcast backup address.
    // Default: 0.0.0.0
    return setopt(PSTR("set broadcast backup"), buf);
}
boolean WiFly::setBroadcastBackup(const __FlashStringHelper *buf)
{
    return setopt(PSTR("set broadcast backup"), NULL, buf);
}

boolean WiFly::setBroadcastInterval(const uint16_t value)
{
    // Sets the interval (in seconds) at which the hello/heartbeat UDP message is sent.
    // Default: 7
    return setopt(PSTR("set broadcast interval"), value);
}

boolean WiFly::setBroadcastPort(const uint16_t port)
{
    // Sets the port to which the UDP hello/heartbeat message is sent.
    // Default: 55555
    return setopt(PSTR("set broadcast port"), port);
}

boolean WiFly::setBroadcastRemote(const uint16_t port)
{
    // Sets the secondary broadcast port.
    // Default: 0
    return setopt(PSTR("set broadcast remote"), port);
}
