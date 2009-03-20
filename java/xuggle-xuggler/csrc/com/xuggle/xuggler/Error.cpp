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
/*
 * Error.cpp
 *
 *  Created on: Mar 20, 2009
 *      Author: aclarke
 */

#include <com/xuggle/ferry/Logger.h>
#include <com/xuggle/xuggler/Error.h>
#include <com/xuggle/xuggler/FfmpegIncludes.h>

#include <cstring>
#include <stdexcept>

VS_LOG_SETUP(VS_CPP_PACKAGE);

namespace com { namespace xuggle { namespace xuggler
{

struct ErrorMappingTable {
  int32_t mFfmpegError;
  IError::Type mXugglerError;
} ;

static struct ErrorMappingTable sErrorMappingTable[] = {
    { AVERROR_IO,           IError::ERROR_IO },
    { AVERROR_NUMEXPECTED,  IError::ERROR_NUMEXPECTED },
    { AVERROR_INVALIDDATA,  IError::ERROR_INVALIDDATA },
    { AVERROR_NOMEM,        IError::ERROR_NOMEM },
    { AVERROR_NOFMT,        IError::ERROR_NOFMT },
    { AVERROR_NOTSUPP,      IError::ERROR_NOTSUPPORTED },
    { AVERROR_NOENT,        IError::ERROR_NOENT },
    { AVERROR_EOF,          IError::ERROR_EOF },
    { AVERROR_PATCHWELCOME, IError::ERROR_PATCHWELCOME },
    { AVERROR(EAGAIN),       IError::ERROR_AGAIN },
    { AVERROR(ERANGE),      IError::ERROR_RANGE },
};
static int32_t sErrorMappingTableSize = sizeof(sErrorMappingTable)/sizeof(struct ErrorMappingTable);

Error :: Error()
{
  mType = IError::ERROR_UNKNOWN;
  mErrorNo = 0;
  *mErrorStr = 0;
}

Error :: ~Error()
{
  
}

const char*
Error :: getDescription()
{
  const char* retval = 0;
  if (!*mErrorStr && mErrorNo != 0)
  {
    retval = strerror_r(AVUNERROR(mErrorNo), mErrorStr, sizeof(mErrorStr));
    if (retval != (const char*) mErrorStr)
      strncpy(mErrorStr, retval, sizeof(mErrorStr));
  }
  return *mErrorStr ? mErrorStr : 0;
}

int32_t
Error :: getErrorNumber()
{
  return mErrorNo;
}
IError::Type
Error :: getType()
{
  return mType;
}

Error*
Error :: make(int32_t aErrorNo)
{
  if (aErrorNo >= 0)
    return 0;
  
  return make(aErrorNo, errorNumberToType(aErrorNo));
}

Error*
Error :: make(Type aType)
{
  return make(typeToErrorNumber(aType), aType);
}

Error*
Error :: make(int32_t aErrorNo, Type aType)
{
  Error* retval = 0;
  try
  {
    retval = make();
    if (!retval)
      throw std::bad_alloc();
    retval->mErrorNo = aErrorNo;
    retval->mType = aType;
    // null out and don't fill unless description is asked for
    *(retval->mErrorStr) = 0;
  }
  catch (std::exception & e)
  {
    VS_LOG_TRACE("Error: %s", e.what());
    VS_REF_RELEASE(retval);
  }
  return retval;
  
}

IError::Type
Error :: errorNumberToType(int32_t errNo)
{
  IError::Type retval = IError::ERROR_UNKNOWN;
  int i = 0;
  for(; i < sErrorMappingTableSize; i++)
  {
    if (sErrorMappingTable[i].mFfmpegError == errNo)
    {
      retval = sErrorMappingTable[i].mXugglerError;
      break;
    }
  }
  if (i >= sErrorMappingTableSize) {
    retval = IError::ERROR_UNKNOWN;
  }
  return retval;
}

int32_t
Error :: typeToErrorNumber(Type type)
{
  int32_t retval = AVERROR_UNKNOWN;
  int i = 0;
  for(; i < sErrorMappingTableSize; i++)
  {
    if (sErrorMappingTable[i].mXugglerError == type)
    {
      retval = sErrorMappingTable[i].mFfmpegError;
      break;
    }
  }
  if (i >= sErrorMappingTableSize) {
    retval = AVERROR_UNKNOWN;
  }
  return retval;
}

}}}
