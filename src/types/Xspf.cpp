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

#include "Xspf.h"
#include "../core/XmlQuery.h"
#include <QUrl>


lastfm::Xspf::Xspf( const QDomElement& playlist_node )
{
    XmlQuery e( playlist_node );
    
    m_title = e["title"].text();
        
    //FIXME should we use UnicornUtils::urlDecode()?
    //The title is url encoded, has + instead of space characters 
    //and has a + at the begining. So it needs cleaning up:
    m_title.replace( '+', ' ' );
    m_title = QUrl::fromPercentEncoding( m_title.toAscii());
    m_title = m_title.trimmed();
    
    foreach (XmlQuery e, e["trackList"].children( "track" ))
    {
        MutableTrack t;
        t.setUrl( e["location"].text() );
        t.setExtra( "trackauth", e["extension"]["trackauth"].text() );
        t.setTitle( e["title"].text() );
        t.setArtist( e["creator"].text() );
        t.setAlbum( e["album"].text() );
        t.setDuration( e["duration"].text().toInt() / 1000 );        
        m_tracks += t; // outside try block since location is enough basically
    }
}
