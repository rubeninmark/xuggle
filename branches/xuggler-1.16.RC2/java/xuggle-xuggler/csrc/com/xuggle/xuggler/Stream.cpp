/*
 * Copyright (c) 2008-2009 by Xuggle Inc. All rights reserved.
 *
 * It is REQUESTED BUT NOT REQUIRED if you use this library, that you let 
 * us know by sending e-mail to info@xuggle.com telling us briefly how you're
 * using the library and what you like or don't like about it.
 *
 * This library is free software; you can redistribute it and/or modify it under the
 * terms of the GNU Lesser General Public License as published by the Free Software
 * Foundation; either version 2.1 of the License, or (at your option) any later
 * version.
 *
 * This library is distributed in the hope that it will be useful, but WITHOUT ANY
 * WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS FOR A
 * PARTICULAR PURPOSE. See the GNU Lesser General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public License along
 * with this library; if not, write to the Free Software Foundation, Inc.,
 * 59 Temple Place, Suite 330, Boston, MA 02111-1307 USA
 */
#include <com/xuggle/ferry/Logger.h>

#include <com/xuggle/xuggler/Global.h>
#include <com/xuggle/xuggler/Stream.h>
#include <com/xuggle/xuggler/Rational.h>
#include <com/xuggle/xuggler/StreamCoder.h>

VS_LOG_SETUP(VS_CPP_PACKAGE);

namespace com { namespace xuggle { namespace xuggler
{

  Stream :: Stream()
  {
    mStream = 0;
    mDirection = INBOUND;
    mCoder = 0;
  }

  Stream :: ~Stream()
  {
    reset();
  }

  void
  Stream :: reset()
  {
    VS_ASSERT("should be a valid object", getCurrentRefCount() >= 1);
    if (mStream && mDirection == OUTBOUND)
    {
      // when outbound we manage our AVStream context;
      // when inbound, FFMPEG cleans up after itself.
      av_free(mStream);
    }
    mStream = 0;
    VS_REF_RELEASE(mCoder);    
  }
  Stream*
  Stream :: make(AVStream * aStream, Direction direction)
  {
    // note: make will acquire this for us.
    Stream *newStream = 0;
    if (aStream) {
      newStream = make();
      if (newStream)
      {
        newStream->mStream = aStream;
        newStream->mDirection = direction;

        newStream->mCoder = StreamCoder::make(
              direction == INBOUND?IStreamCoder::DECODING :
              IStreamCoder::ENCODING,
              aStream->codec,
              newStream);
        VS_ASSERT(newStream->mCoder, "Could not allocate a coder!");
      }
    }
    return newStream;
  }

  int
  Stream :: getIndex()
  {
    return (mStream ? mStream->index : -1);
  }

  int
  Stream :: getId()
  {
    return (mStream ? mStream->id : -1);
  }

  IStreamCoder *
  Stream :: getStreamCoder()
  {
    StreamCoder *retval = 0;
    
    // acquire a reference for the caller
    retval = mCoder;
    VS_REF_ACQUIRE(retval);

    return retval;
  }

  IRational *
  Stream :: getFrameRate()
  {
    IRational * result = 0;
    if (mStream)
    {
      result = Rational::make(&mStream->r_frame_rate);
    }
    return result;
  }

  IRational *
  Stream :: getTimeBase()
  {
    IRational * result = 0;
    if (mStream)
    {
      result = Rational::make(&mStream->time_base);
    }
    return result;
  }
  void
  Stream :: setTimeBase(IRational* src)
  {
    if (mStream && src)
    {
      mStream->time_base.den = src->getDenominator();
      mStream->time_base.num = src->getNumerator();
    }
  }
  void
  Stream :: setFrameRate(IRational* src)
  {
    if (mStream && src)
    {
      mStream->r_frame_rate.den = src->getDenominator();
      mStream->r_frame_rate.num = src->getNumerator();
    }
  }

  int64_t
  Stream :: getStartTime()
  {
    return (mStream ? mStream->start_time : Global::NO_PTS);
  }

  int64_t
  Stream :: getDuration()
  {
    return (mStream ? mStream->duration : Global::NO_PTS);
  }

  int64_t
  Stream :: getCurrentDts()
  {
    return (mStream ? mStream->cur_dts : Global::NO_PTS);
  }

  int64_t
  Stream :: getNumFrames()
  {
    return (mStream ? mStream->nb_frames : 0);
  }
  int
  Stream :: getNumIndexEntries()
  {
    return (mStream ? mStream->nb_index_entries : 0);
  }
  int
  Stream :: containerClosed(Container *)
  {
    // let the coder know we're closed.
    if (mCoder)
      mCoder->streamClosed(this);
    reset();
    return 0;
  }
  
  int32_t
  Stream :: acquire()
  {
    int retval = 0;
    retval = RefCounted::acquire();
    VS_LOG_TRACE("Acquired %p: %d", this, retval);
    return retval;
  }

  int32_t
  Stream :: release()
  {
    int retval = 0;
    retval = RefCounted::release();
    VS_LOG_TRACE("Released %p: %d", this, retval);
    return retval;
  }

}}}