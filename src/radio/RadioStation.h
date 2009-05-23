/***************************************************************************
 *   Copyright 2005-2009 Last.fm Ltd.                                      *
 *                                                                         *
 *   This program is free software; you can redistribute it and/or modify  *
 *   it under the terms of the GNU General Public License as published by  *
 *   the Free Software Foundation; either version 2 of the License, or     *
 *   (at your option) any later version.                                   *
 *                                                                         *
 *    This program is distributed in the hope that it will be useful,      *
 *   but WITHOUT ANY WARRANTY; without even the implied warranty of        *
 *   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the         *
 *   GNU General Public License for more details.                          *
 *                                                                         *
 *   You should have received a copy of the GNU General Public License     *
 *   along with this program; if not, write to the                         *
 *   Free Software Foundation, Inc.,                                       *
 *   51 Franklin Steet, Fifth Floor, Boston, MA  02110-1301, USA.          *
 ***************************************************************************/

#ifndef LASTFM_RADIO_STATION_H
#define LASTFM_RADIO_STATION_H

#include <lastfm/User>
#include <lastfm/Tag>
#include <lastfm/Artist>


namespace lastfm
{
    /** @author <jono@last.fm> 
      */
    class LASTFM_DLLEXPORT RadioStation
    {
    public:
        RadioStation()
        {}
        RadioStation( const QString& s ) : m_url( s )
        {}
        explicit RadioStation( const QUrl& u ) : m_url( u.toString() )
        {}
    
        static RadioStation library( const lastfm::User& user )         { return "lastfm://user/" + user + "/personal"; }
        static RadioStation recommendations( const lastfm::User& user ) { return "lastfm://user/" + user + "/recommended"; }
        static RadioStation neighbourhood( const lastfm::User& user )   { return "lastfm://user/" + user + "/neighbours"; }
        static RadioStation lovedTracks( const lastfm::User& user )     { return "lastfm://user/" + user + "/loved"; }
        static RadioStation globalTag( const lastfm::Tag& tag )         { return "lastfm://globaltags/" + tag; }
        static RadioStation similar( const lastfm::Artist& artist )     { return "lastfm://artist/" + artist + "/similarartists"; }

        static RadioStation rql( const QString& rql )
        {
            RadioStation station;
            station.m_rql = rql;
            station.m_url = "lastfm://rql/" + QString(rql.toUtf8().toBase64());
            return station;
        }

        /** eg. "mxcl's Loved Tracks"
          * It is worth noting that the Radio doesn't set the title of RadioStation 
          * object until we have tuned to it, and then we only set the one we give 
          * you back.
          */    
        QString title() const { return m_title; }
        /** the Last.fm url, eg. lastfm://user/mxcl/loved */
        QString url() const { return m_url; }
        QString rql() const { return m_rql; }

        void setTitle( const QString& s ) { m_title = s; }

        bool isLegacyPlaylist() const
        {
            return m_url.startsWith( "lastfm://play/" ) ||
                   m_url.startsWith( "lastfm://preview/" ) ||
                   m_url.startsWith( "lastfm://track/" ) ||
                   m_url.startsWith( "lastfm://playlist/" );
        }
    
    private:
        QString m_rql;
        QString m_url;
        QString m_title;
    };
}


Q_DECLARE_METATYPE( lastfm::RadioStation )


inline QDebug operator<<( QDebug d, const lastfm::RadioStation& station )
{
    return d << station.url();
}

#endif
