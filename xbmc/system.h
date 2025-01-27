#pragma once

/*
 *      Copyright (C) 2005-2013 Team XBMC
 *      http://xbmc.org
 *
 *  This Program is free software; you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation; either version 2, or (at your option)
 *  any later version.
 *
 *  This Program is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
 *  GNU General Public License for more details.
 *
 *  You should have received a copy of the GNU General Public License
 *  along with XBMC; see the file COPYING.  If not, see
 *  <http://www.gnu.org/licenses/>.
 *
 */

#if defined(HAVE_CONFIG_H)
#include "config.h"
#define DECLARE_UNUSED(a,b) a __attribute__((unused)) b;
#endif

// USE_xxx  is for Makefiles (never use them in source code)
// HAVE_xxx comes from configure.ac
// HAS_xxx  is something we made up for app features

/*****************
 * All platforms
 *****************/
#define HAS_DVD_SWSCALE
#define HAS_EVENT_SERVER
#define HAS_SCREENSAVER
#define HAS_VIDEO_PLAYBACK
#define HAS_PVRCLIENTS

#ifdef HAVE_LIBMICROHTTPD
#define HAS_WEB_SERVER
#define HAS_WEB_INTERFACE
#endif

#define HAS_JSONRPC

#define HAS_FILESYSTEM
#define HAS_FILESYSTEM_SAP

#ifdef HAVE_LIBSMBCLIENT
  #define HAS_FILESYSTEM_SMB
#endif

#ifdef HAVE_BDSM_BDSM_H
  #define HAS_FILESYSTEM_DSM
#endif

#ifdef HAVE_LIBNFS
  #define HAS_FILESYSTEM_NFS
#endif

#ifdef HAVE_LIBPLIST
  #define HAS_AIRPLAY
#endif

#if defined(HAVE_LIBSHAIRPLAY)
  #define HAS_AIRTUNES
#endif

#ifdef HAVE_MYSQL
  #define HAS_MYSQL
#endif

#if defined(USE_UPNP)
  #define HAS_UPNP
#endif

#if defined(HAVE_LIBMDNSEMBEDDED)
  #define HAS_ZEROCONF
  #define HAS_MDNS
  #define HAS_MDNS_EMBEDDED
#endif

/*****************
 * Mac Specific
 *****************/

#if defined(TARGET_DARWIN)
  #if defined(TARGET_DARWIN_OSX)
    #define HAS_GL
  #endif
  #define HAS_ZEROCONF
  #define HAS_LINUX_NETWORK
#endif

/*****************
 * Linux Specific
 *****************/

#if defined(TARGET_LINUX) || defined(TARGET_FREEBSD)
#if defined(HAVE_LIBAVAHI_COMMON) && defined(HAVE_LIBAVAHI_CLIENT)
#define HAS_ZEROCONF
#define HAS_AVAHI
#endif
#ifdef HAVE_DBUS
#define HAS_DBUS
#endif
#define HAS_GL
#ifdef HAVE_X11
#define HAS_GLX
#define HAS_X11_WIN_EVENTS
#endif
#ifdef HAVE_SDL
#define HAS_SDL
#ifndef HAVE_X11
#define HAS_SDL_WIN_EVENTS
#endif
#else
#ifndef HAVE_X11
#define HAS_LINUX_EVENTS
#endif
#endif
#define HAS_LINUX_NETWORK
#ifdef HAVE_LIRC
#define HAS_LIRC
#endif
#ifdef HAVE_LIBPULSE
#define HAS_PULSEAUDIO
#endif
#ifdef HAVE_ALSA
#define HAS_ALSA
#endif
#endif

#ifdef HAVE_LIBSSH
#define HAS_FILESYSTEM_SFTP
#endif

/****************************************
 * Additional platform specific includes
 ****************************************/
#if defined(TARGET_POSIX)
#include <time.h>
#include <sys/time.h>
#include <sys/types.h>
#include <errno.h>
#include "linux/PlatformInclude.h"
#endif

#if defined(TARGET_ANDROID)
#undef HAS_LINUX_EVENTS
#undef HAS_LIRC
#endif

// EGL detected. Dont use GLX!
#ifdef HAVE_LIBEGL
#undef HAS_GLX
#define HAS_EGL
#endif

// GLES2.0 detected. Dont use GL!
#ifdef HAVE_LIBGLESV2
#undef HAS_GL
#define HAS_GLES 2
#endif

// GLES1.0 detected. Dont use GL!
#ifdef HAVE_LIBGLES
#undef HAS_GL
#define HAS_GLES 1
#endif

#define SAFE_DELETE(p)       do { delete (p);     (p)=NULL; } while (0)
#define SAFE_DELETE_ARRAY(p) do { delete[] (p);   (p)=NULL; } while (0)
#define SAFE_RELEASE(p)      do { if(p) { (p)->Release(); (p)=NULL; } } while (0)

// Useful pixel colour manipulation macros
#define GET_A(color)            ((color >> 24) & 0xFF)
#define GET_R(color)            ((color >> 16) & 0xFF)
#define GET_G(color)            ((color >>  8) & 0xFF)
#define GET_B(color)            ((color >>  0) & 0xFF)
