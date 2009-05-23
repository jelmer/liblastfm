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

#ifndef LASTFM_TUNER_H
#define LASTFM_TUNER_H

#include <lastfm/RadioStation>
#include <lastfm/Track>
#include <lastfm/ws.h>
#include <QList>

namespace lastfm
{
    /** With regard to error handling. We handle Ws::TryAgain up to 5 times,
      * don't try again after that! Just tell the user to try again later. 
      */
    class LASTFM_DLLEXPORT RadioTuner : public QObject
    {
        Q_OBJECT
    
    public:
        /** You need to have assigned Ws::* for this to work, creating the tuner
          * automatically fetches the first 5 tracks for the station */
        explicit RadioTuner( const RadioStation& );

        Track takeNextTrack();

    signals:
        void title( const QString& );
        void trackAvailable();
        void error( lastfm::ws::Error );

    private slots:
        void onTuneReturn();
        void onGetPlaylistReturn();

    private:
        /** Tries again up to 5 times 
          * @returns true if we tried again, otherwise you should emit error */
        bool tryAgain();
        /** Will emit 5 tracks from tracks(), they have to played within an hour
          * or the streamer will refuse to stream them. Also the previous five are
          * invalidated apart from the one that is currently playing, so sorry, you
          * can't build up big lists of tracks.
          *
          * I feel I must point out that asking the user which one they want to play
          * is also not allowed according to our terms and conditions, which you
          * already agreed to in order to get your API key. Sorry about that dude. 
          */
        bool fetchFiveMoreTracks();

        QList<Track> m_queue;
        uint m_retry_counter;
    };
}

#endif
