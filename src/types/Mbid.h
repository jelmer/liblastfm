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

#ifndef LASTFM_MBID_H
#define LASTFM_MBID_H

#include <lastfm/global.h>
#include <QString>


namespace lastfm
{
    class LASTFM_DLLEXPORT Mbid
    {
        QString id;
    
    public:
        explicit Mbid( const QString& p = "" ) : id( p )
        {}
    
        bool isNull() const { return id.isNull() || id.isEmpty(); }
        operator QString() const { return id; }

        /** if this is not an mp3 file you will be wasting time, as it won't work
          * but we will do what you say anyway because you are the boss */ 
        static Mbid fromLocalFile( const QString& path );
    };
}

#endif
