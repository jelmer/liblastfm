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
#ifndef LASTFM_SCROBBLER_SUBMISSION_H
#define LASTFM_SCROBBLER_SUBMISSION_H

#include "ScrobblerHttp.h"
#include "../types/Track.h"
#include <QList>

class ScrobblerSubmission : public ScrobblerPostHttp
{
    QList<lastfm::Track> m_tracks;
    QList<lastfm::Track> m_batch;

public:    
    /** tracks will be submitted in batches of 50 */
    void setTracks( const QList<lastfm::Track>& );
    /** submits a batch, if we are already submitting, does nothing */
    void submitNextBatch();
    /** the batch that is being submitted currently */
    QList<lastfm::Track> batch() const { return m_batch; }
    /** tracks that have not yet been removed due to an OK from Last.fm */
    QList<lastfm::Track> unsubmittedTracks() const { return m_tracks; }

    virtual void request()
    {
        if (!isActive()) ScrobblerPostHttp::request();
    }
};

#endif
