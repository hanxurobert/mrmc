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

#if (defined HAVE_CONFIG_H)
  #include "config.h"
#endif
#include "network/Network.h"
#include "system.h"
#include "FileFactory.h"
#ifdef TARGET_POSIX
#include "posix/PosixFile.h"
#endif
#include "CurlFile.h"
#include "HTTPFile.h"
#include "DAVFile.h"
#include "ShoutcastFile.h"
#include "FileReaderFile.h"
#ifdef HAS_FILESYSTEM_SMB
#include "SMBFile.h"
#endif
#ifdef HAS_FILESYSTEM_DSM
#include "DSMFile.h"
#endif
#ifdef HAS_FILESYSTEM_SAP
#include "SAPFile.h"
#endif
#ifdef HAS_PVRCLIENTS
#include "PVRFile.h"
#endif
#if defined(TARGET_ANDROID)
#include "APKFile.h"
#endif
#include "XbtFile.h"
#include "ZipFile.h"
#ifdef HAS_FILESYSTEM_SFTP
#include "SFTPFile.h"
#endif
#ifdef HAS_FILESYSTEM_NFS
#include "NFSFile.h"
#endif
#if defined(TARGET_ANDROID)
#include "AndroidAppFile.h"
#endif
#ifdef HAS_UPNP
#include "UPnPFile.h"
#endif
#include "PipeFile.h"
#include "MusicDatabaseFile.h"
#include "SpecialProtocolFile.h"
#include "MultiPathFile.h"
#include "UDFFile.h"
#include "ImageFile.h"
#include "ResourceFile.h"
#include "Application.h"
#include "URL.h"
#include "utils/log.h"
#include "network/WakeOnAccess.h"
#include "settings/Settings.h"

using namespace XFILE;

CFileFactory::CFileFactory()
{
}

CFileFactory::~CFileFactory()
{
}

IFile* CFileFactory::CreateLoader(const std::string& strFileName)
{
  CURL url(strFileName);
  return CreateLoader(url);
}

IFile* CFileFactory::CreateLoader(const CURL& url)
{
  if (!CWakeOnAccess::GetInstance().WakeUpHost(url))
    return NULL;

#if defined(TARGET_ANDROID)
  if (url.IsProtocol("apk")) return new CAPKFile();
#endif
  if (url.IsProtocol("zip")) return new CZipFile();
  else if (url.IsProtocol("xbt")) return new CXbtFile();
  else if (url.IsProtocol("musicdb")) return new CMusicDatabaseFile();
  else if (url.IsProtocol("videodb")) return NULL;
  else if (url.IsProtocol("special")) return new CSpecialProtocolFile();
  else if (url.IsProtocol("multipath")) return new CMultiPathFile();
  else if (url.IsProtocol("image")) return new CImageFile();
  else if (url.IsProtocol("file") || url.GetProtocol().empty()) return new CPosixFile();
  else if (url.IsProtocol("filereader")) return new CFileReaderFile();
  else if(url.IsProtocol("udf")) return new CUDFFile();
#if defined(TARGET_ANDROID)
  else if (url.IsProtocol("androidapp")) return new CFileAndroidApp();
#endif
  else if (url.IsProtocol("pipe")) return new CPipeFile();
  else if (url.IsProtocol("resource")) return new CResourceFile();

  bool networkAvailable = g_application.getNetwork().IsAvailable();
  if (networkAvailable)
  {
    if (url.IsProtocol("ftp")
    ||  url.IsProtocol("ftps")
    ||  url.IsProtocol("rss")) return new CCurlFile();
    else if (url.IsProtocol("http") ||  url.IsProtocol("https")) return new CHTTPFile();
    else if (url.IsProtocol("dav") || url.IsProtocol("davs")) return new CDAVFile();
#ifdef HAS_FILESYSTEM_SFTP
    else if (url.IsProtocol("sftp") || url.IsProtocol("ssh")) return new CSFTPFile();
#endif
    else if (url.IsProtocol("shout")) return new CShoutcastFile();
#ifdef HAS_FILESYSTEM_DSM
    else if (url.IsProtocol("smb") && CSettings::GetInstance().GetBool(CSettings::SETTING_SMB_ENABLEDSM))
      return new CDSMFile();
#endif
#ifdef HAS_FILESYSTEM_SMB
    else if (url.IsProtocol("smb")) return new CSMBFile();
#endif
#ifdef HAS_FILESYSTEM_SAP
    else if (url.IsProtocol("sap")) return new CSAPFile();
#endif
#ifdef HAS_PVRCLIENTS
    else if (url.IsProtocol("pvr")) return new CPVRFile();
#endif
#ifdef HAS_FILESYSTEM_NFS
    else if (url.IsProtocol("nfs")) return new CNFSFile();
#endif
#ifdef HAS_UPNP
    else if (url.IsProtocol("upnp")) return new CUPnPFile();
#endif
  }

  CLog::Log(LOGWARNING, "%s - %sunsupported protocol(%s) in %s", __FUNCTION__, networkAvailable ? "" : "Network down or ", url.GetProtocol().c_str(), url.GetRedacted().c_str());
  return NULL;
}
