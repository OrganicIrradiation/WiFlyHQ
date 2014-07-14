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
 * @file WiFly RN-XV option parameters
 * Supports optional and infrequently used parameters.
 */
 
#include "WiFlyHQ.h"

boolean WiFly::setOptAverage(uint8_t value)
{
    // Sets the number of RSSI samples used to calculate the running RSSI average.
    // Default: 5
    return setopt(PSTR("set opt average"), value);
}

boolean WiFly::setOptDeviceID(const __FlashStringHelper *buf)
{
    // Sets the configurable device ID, where XXX is GSX for the RN131 and EZX for the RN171.
    // Default: WiFly-XXX
    return setopt(PSTR("set opt deviceid"), NULL, buf);
}
boolean WiFly::setOptDeviceID(const char *buf)
{
    return setopt(PSTR("set opt deviceid"), buf);
}
boolean WiFly::setDeviceID(const __FlashStringHelper *buf)
{
    return setOptDeviceID(buf);
}
boolean WiFly::setDeviceID(const char *buf)
{
    return setOptDeviceID(buf);
}

boolean WiFly::setOptFormat(uint8_t flag)
{
    // Sets the HTTP client/web server information.
    // Bit 0: Automatically send an HTML header-based broadcast interval.
    // Bit 1: Send users binary data (converted to ASCII hex).
    // Bit 2: Sample the GPIO and ADC pins and format to ASCII hex.
    // Bit 3: Appends &id=<value>, where <value> is the device ID string that was set
    //        using set opt device <string>.
    // Bit 4: Appends the following key/value pairs to the HTTP message: &rtc=<time>,
    //        &mac=<address>, &bss=<access point address>, &bat=<battery voltage>,
    //        &io=<GPIO in hex>, &wake=<wake reason>, &seq=<sequence value>, where <time>
    //        is the realtime clock value in the message as a 32-bit hex value in format
    //        aabbccddeeff and <sequence value> is a rolling counter of how many web posts
    //        have been sent.
    // Default: 0x00
    return setopt(PSTR("set opt format"), flag);
}

boolean WiFly::setOptJoinTmr(uint16_t value)
{
    // Sets the join timer, which is the length of time (in ms) the join function waits
    // for the access point to complete the association process.
    // Default: 1000
    return setopt(PSTR("set opt jointmr"), value);
}

boolean WiFly::setOptReplace(char ch)
{
    // Sets the replacement character you use to indicate spaces in the SSID and
    // passphrases, where <ch> is a single character.
    // Default: '$' (0x24)
    char buf[2] = { ch, 0 };

    replaceChar = ch;
    return setopt(PSTR("set opt replace"), buf);
}
boolean WiFly::setSpaceReplace(char ch)
{
    return setOptReplace(ch);
}

boolean WiFly::setOptPassword(const __FlashStringHelper *buf)
{
    // Sets the TCP connection password.
    // Default: ""
    return setopt(PSTR("set opt password"), NULL, buf);
}
boolean WiFly::setOptPassword(const char *buf)
{
    return setopt(PSTR("set opt password"), buf);
}

boolean WiFly::setOptSignal(uint8_t value)
{
    // Configures the threshold level for the RSSI value in infrastructure mode.
    // Default: 0
    return setopt(PSTR("set opt signal"), value);
}
