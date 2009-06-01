/*
   Copyright 2009 Last.fm Ltd. 
      - Primarily authored by Max Howell, Jono Cole and Doug Mansell

   This file is part of liblastfm.

   liblastfm is free software: you can redistribute it and/or modify
   it under the terms of the GNU General Public License as published by
   the Free Software Foundation, either version 3 of the License, or
   (at your option) any later version.

   liblastfm is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.

   You should have received a copy of the GNU General Public License
   along with liblastfm.  If not, see <http://www.gnu.org/licenses/>.
*/
#ifndef SCROBBLE_CACHE_H
#define SCROBBLE_CACHE_H

#include "Scrobble.h"
#include <QList>
#include <QString>

// because we are not for public consumption
using lastfm::Scrobble;
using lastfm::Track;
 

/** absolutely not thread-safe */
class LASTFM_DLLEXPORT ScrobbleCache
{
    QString m_username;

    void write(); /// writes m_tracks to m_path

    friend class ScrobblerSubmission;

protected:
    ScrobbleCache()
    {}

    QString m_path;
    QList<Track> m_tracks;
    
    void read( QDomDocument& xml );  /// reads from m_path into m_tracks   
    
public:
    explicit ScrobbleCache( const QString& username );

    /** note this is unique for Track::sameAs() and equal timestamps 
      * obviously playcounts will not be increased for the same timestamp */
    void add( const Scrobble& );
    void add( const QList<Track>& );

    /** returns the number of tracks left in the queue */
    int remove( const QList<Track>& );

    QList<Track> tracks() const { return m_tracks; }
    QString path() const { return m_path; }
    QString username() const { return m_username; }

private:
    bool operator==( const ScrobbleCache& ); //undefined
};

#endif
