/*
 * Copyright (c) 2002 Apple Computer, Inc. All rights reserved.
 *
 * @APPLE_LICENSE_HEADER_START@
 * 
 * The contents of this file constitute Original Code as defined in and
 * are subject to the Apple Public Source License Version 1.2 (the
 * "License").  You may not use this file except in compliance with the
 * License.  Please obtain a copy of the License at
 * http://www.apple.com/publicsource and read it before using this file.
 * 
 * This Original Code and all software distributed under the License are
 * distributed on an "AS IS" basis, WITHOUT WARRANTY OF ANY KIND, EITHER
 * EXPRESS OR IMPLIED, AND APPLE HEREBY DISCLAIMS ALL SUCH WARRANTIES,
 * INCLUDING WITHOUT LIMITATION, ANY WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE OR NON-INFRINGEMENT.  Please see the
 * License for the specific language governing rights and limitations
 * under the License.
 * 
 * @APPLE_LICENSE_HEADER_END@
 */
/*
    File:       mDNSPlatformPosix.h

    Contains:   Interface to the Posix platform code.

    Written by: Quinn

    Copyright:  Copyright (c) 2002 by Apple Computer, Inc., All Rights Reserved.

    Disclaimer: IMPORTANT:  This Apple software is supplied to you by Apple Computer, Inc.
                ("Apple") in consideration of your agreement to the following terms, and your
                use, installation, modification or redistribution of this Apple software
                constitutes acceptance of these terms.  If you do not agree with these terms,
                please do not use, install, modify or redistribute this Apple software.

                In consideration of your agreement to abide by the following terms, and subject
                to these terms, Apple grants you a personal, non-exclusive license, under Apple's
                copyrights in this original Apple software (the "Apple Software"), to use,
                reproduce, modify and redistribute the Apple Software, with or without
                modifications, in source and/or binary forms; provided that if you redistribute
                the Apple Software in its entirety and without modifications, you must retain
                this notice and the following text and disclaimers in all such redistributions of
                the Apple Software.  Neither the name, trademarks, service marks or logos of
                Apple Computer, Inc. may be used to endorse or promote products derived from the
                Apple Software without specific prior written permission from Apple.  Except as
                expressly stated in this notice, no other rights or licenses, express or implied,
                are granted by Apple herein, including but not limited to any patent rights that
                may be infringed by your derivative works or by other works in which the Apple
                Software may be incorporated.

                The Apple Software is provided by Apple on an "AS IS" basis.  APPLE MAKES NO
                WARRANTIES, EXPRESS OR IMPLIED, INCLUDING WITHOUT LIMITATION THE IMPLIED
                WARRANTIES OF NON-INFRINGEMENT, MERCHANTABILITY AND FITNESS FOR A PARTICULAR
                PURPOSE, REGARDING THE APPLE SOFTWARE OR ITS USE AND OPERATION ALONE OR IN
                COMBINATION WITH YOUR PRODUCTS.

                IN NO EVENT SHALL APPLE BE LIABLE FOR ANY SPECIAL, INDIRECT, INCIDENTAL OR
                CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE
                GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION)
                ARISING IN ANY WAY OUT OF THE USE, REPRODUCTION, MODIFICATION AND/OR DISTRIBUTION
                OF THE APPLE SOFTWARE, HOWEVER CAUSED AND WHETHER UNDER THEORY OF CONTRACT, TORT
                (INCLUDING NEGLIGENCE), STRICT LIABILITY OR OTHERWISE, EVEN IF APPLE HAS BEEN
                ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.

    Change History (most recent first):

$Log: mDNSPosix.h,v $
Revision 1.1  2003/07/18 19:41:54  dean
Initial revision

Revision 1.1  2003/01/20 00:45:58  blackketter
Adding support for advertising the SLIMP3 via zeroconf/mDNS/Rendezvous.

Debugging via --d_mdns

Requires a binary executable installed to be fork/exec'ed off for each
instance advertised.  Need to add an option for disabling it.

It advertises the web interface, the HTTP automation interface (which are
the same now) and the CLI.  The latter two are _slimdevices_slimp3_http._tcp
and _slimdevices_slimp3_cli._tcp respectively.

This uses the Apple open source implementation of the mDNS
command-line application mDNSResponderPosix.

This source is included so folks can build the other posix implementations.
Windows, as always, will require more work.

Rumor has it that there will be a CPAN module for zeroconf, which would obsolete
this implementation if pulled in.  That's ok, we'll take it out in that case.

This introduces a new directory in slimp3/server which is bin.  bin contains
subdirectories for each supported platform and is where we'd put executables
we use (similar to the lib/CPAN arrangement.)

Also added the submitted patch for ogginfo support. This gives ogg files the
opportunity to be browsed by meta information.  This requires several ogg
executables to be installed in the default path, which is too hard for the
average user.  This should also be cleaned up.

The Ogg patch also included a fix to make ogg files work with spaces in the
filename.

Tweaked the comments for the fix that Rob Moser added when I broke hiding
. and .. on Win32 systems.

Revision 1.3  2002/09/21 20:44:53  zarzycki
Added APSL info

Revision 1.2  2002/09/19 04:20:44  cheshire
Remove high-ascii characters that confuse some systems

Revision 1.1  2002/09/17 06:24:34  cheshire
First checkin

*/

#ifndef __mDNSPlatformPosix_h
#define __mDNSPlatformPosix_h

#include <sys/time.h>

#ifdef  __cplusplus
    extern "C" {
#endif

// This is a global because debugf_() needs to be able to check its value
extern int gMDNSPlatformPosixVerboseLevel;

struct mDNS_PlatformSupport_struct
	{
    struct timeval NextEvent;
	};

extern mStatus mDNSPlatformPosixRefreshInterfaceList(mDNS *const m);
    // See comment in implementation.

// Call mDNSPosixGetFDSet before calling select(), to update the parameters
// as may be necessary to meet the needs of the mDNSCore code.
// The timeout pointer MUST NOT be NULL.
// Set timeout->tv_sec to 0x3FFFFFFF if you want to have effectively no timeout
// After calling mDNSPosixGetFDSet(), call select(nfds, &readfds, NULL, NULL, &timeout); as usual
// After select() returns, call mDNSPosixProcessFDSet() to let mDNSCore do its work
extern void mDNSPosixGetFDSet(const mDNS *const m, int *nfds, fd_set *readfds, struct timeval *timeout);
extern void mDNSPosixProcessFDSet(mDNS *const m, int selectresult, fd_set *readfds);

#ifdef  __cplusplus
    }
#endif

#endif