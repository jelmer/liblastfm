/***************************************************************************
 *   Copyright 2005-2009 Last.fm Ltd.                                      *
 *                                                                         *
 *   This program is free software; you can redistribute it and/or modify  *
 *   it under the terms of the GNU General Public License as published by  *
 *   the Free Software Foundation; either version 2 of the License, or     *
 *   (at your option) any later version.                                   *
 *                                                                         *
 *   This program is distributed in the hope that it will be useful,       *
 *   but WITHOUT ANY WARRANTY; without even the implied warranty of        *
 *   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the         *
 *   GNU General Public License for more details.                          *
 *                                                                         *
 *   You should have received a copy of the GNU General Public License     *
 *   along with this program; if not, write to the                         *
 *   Free Software Foundation, Inc.,                                       *
 *   51 Franklin Steet, Fifth Floor, Boston, MA  02110-1301, USA.          *
 ***************************************************************************/

#ifndef LASTFM_MISC_H
#define LASTFM_MISC_H

#include <lastfm/global.h>
#include <QCryptographicHash>
#include <QDir>
#include <QString>

#ifdef Q_WS_MAC
typedef const struct __CFString* CFStringRef;
#endif

namespace lastfm
{
    namespace dir
    {
    #ifdef Q_WS_WIN
        LASTFM_DLLEXPORT QDir programFiles();
    #endif
    #ifdef Q_WS_MAC
        LASTFM_DLLEXPORT QDir bundle();
    #endif
        LASTFM_DLLEXPORT QDir runtimeData();
        LASTFM_DLLEXPORT QDir cache();
        LASTFM_DLLEXPORT QDir logs();
    }
   
#ifdef Q_WS_MAC 
    LASTFM_DLLEXPORT QByteArray CFStringToUtf8( CFStringRef );
    LASTFM_DLLEXPORT CFStringRef QStringToCFString( const QString& );
    inline QString CFStringToQString( CFStringRef s );
#endif

    inline const char* platform()
    {
        #ifdef Q_WS_WIN
        switch (QSysInfo::WindowsVersion)
        {
            case QSysInfo::WV_32s:        return "Windows 3.1 with Win32s";
            case QSysInfo::WV_95:         return "Windows 95";
            case QSysInfo::WV_98:         return "Windows 98";
            case QSysInfo::WV_Me:         return "Windows Me";
            case QSysInfo::WV_DOS_based:  return "MS-DOS-based Windows";

            case QSysInfo::WV_NT:         return "Windows NT";
            case QSysInfo::WV_2000:       return "Windows 2000";
            case QSysInfo::WV_XP:         return "Windows XP";
            case QSysInfo::WV_2003:       return "Windows Server 2003";
            case QSysInfo::WV_VISTA:      return "Windows Vista";
            case QSysInfo::WV_NT_based:   return "NT-based Windows";

            case QSysInfo::WV_CE:         return "Windows CE";
            case QSysInfo::WV_CENET:      return "Windows CE.NET";
            case QSysInfo::WV_CE_based:   return "CE-based Windows";

            default:                      return "Unknown";
        }
        #elif defined Q_WS_MAC
        switch (QSysInfo::MacintoshVersion)
        {
            case QSysInfo::MV_Unknown:    return "Unknown Mac";
            case QSysInfo::MV_9:          return "Mac OS 9";
            case QSysInfo::MV_10_0:       return "Mac OS X 10.0";
            case QSysInfo::MV_10_1:       return "Mac OS X 10.1";
            case QSysInfo::MV_10_2:       return "Mac OS X 10.2";
            case QSysInfo::MV_10_3:       return "Mac OS X 10.3";
            case QSysInfo::MV_10_4:       return "Mac OS X 10.4";
            case QSysInfo::MV_10_5:       return "Mac OS X 10.5";

            default:                      return "Unknown";
        }
        #elif defined Q_WS_X11
            return "UNIX X11";
        #else
            return "Unknown";
        #endif
    }
    
    inline QString md5( const QByteArray& src )
    {
        QByteArray const digest = QCryptographicHash::hash( src, QCryptographicHash::Md5 );
        return QString::fromLatin1( digest.toHex() ).rightJustified( 32, '0' ).toLower();
    }
}

#ifdef Q_WS_MAC
inline QString lastfm::CFStringToQString( CFStringRef s )
{
    return QString::fromUtf8( CFStringToUtf8( s ) );
}
#endif
#endif //LASTFM_MISC_H
