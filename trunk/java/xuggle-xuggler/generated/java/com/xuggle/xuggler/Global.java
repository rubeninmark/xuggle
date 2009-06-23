/* ----------------------------------------------------------------------------
 * This file was automatically generated by SWIG (http://www.swig.org).
 * Version 1.3.37
 *
 * Do not make changes to this file unless you know what you are doing--modify
 * the SWIG interface file instead.
 * ----------------------------------------------------------------------------- */

package com.xuggle.xuggler;
import com.xuggle.ferry.*;
/**
 * A collection of static functions that refer to the entire package 
 * (like version getters).  
 */
public class Global extends RefCounted {
  // JNIHelper.swg: Start generated code
  // >>>>>>>>>>>>>>>>>>>>>>>>>>>
  /**
   * This method is only here to use some references and remove
   * a Eclipse compiler warning.
   */
  @SuppressWarnings("unused")
  private void noop()
  {
    IBuffer.make(null, 1);
  }
   
  private volatile long swigCPtr;

  /**
   * Internal Only.
   */
  protected Global(long cPtr, boolean cMemoryOwn) {
    super(XugglerJNI.SWIGGlobalUpcast(cPtr), cMemoryOwn);
    swigCPtr = cPtr;
  }
  
  /**
   * Internal Only.
   */
  protected Global(long cPtr, boolean cMemoryOwn,
      java.util.concurrent.atomic.AtomicLong ref)
  {
    super(XugglerJNI.SWIGGlobalUpcast(cPtr),
     cMemoryOwn, ref);
    swigCPtr = cPtr;
  }
    
  /**
   * Internal Only.  Not part of public API.
   *
   * Get the raw value of the native object that obj is proxying for.
   *   
   * @param obj The java proxy object for a native object.
   * @return The raw pointer obj is proxying for.
   */
  public static long getCPtr(Global obj) {
    if (obj == null) return 0;
    return obj.getMyCPtr();
  }

  /**
   * Internal Only.  Not part of public API.
   *
   * Get the raw value of the native object that we're proxying for.
   *   
   * @return The raw pointer we're proxying for.
   */  
  public long getMyCPtr() {
    if (swigCPtr == 0) throw new IllegalStateException("underlying native object already deleted");
    return swigCPtr;
  }
  
  /**
   * Create a new Global object that is actually referring to the
   * exact same underlying native object.
   *
   * @return the new Java object.
   */
  @Override
  public Global copyReference() {
    if (swigCPtr == 0)
      return null;
    else
      return new Global(swigCPtr, swigCMemOwn, getJavaRefCount());
  }

  /**
   * Releases ths instance of Global and frees any underlying
   * native memory.
   * <p>
   * {@inheritDoc}
   * </p> 
   */
  @Override
  public void delete()
  {
    do {} while(false); // remove a warning
    super.delete();
  }

  /**
   * Compares two values, returning true if the underlying objects in native code are the same object.
   *
   * That means you can have two different Java objects, but when you do a comparison, you'll find out
   * they are the EXACT same object.
   *
   * @return True if the underlying native object is the same.  False otherwise.
   */
  public boolean equals(Object obj) {
    boolean equal = false;
    if (obj instanceof Global)
      equal = (((Global)obj).swigCPtr == this.swigCPtr);
    return equal;
  }
  
  /**
   * Get a hashable value for this object.
   *
   * @return the hashable value.
   */
  public int hashCode() {
     return (int)swigCPtr;
  }
  
  // <<<<<<<<<<<<<<<<<<<<<<<<<<<
  // JNIHelper.swg: End generated code
  

  /**
   * The default unit of time that {@link IAudioSamples} and
   * {@link IVideoPicture} time stamps are represented in.
   */
  public static final java.util.concurrent.TimeUnit DEFAULT_TIME_UNIT =
    java.util.concurrent.TimeUnit.MICROSECONDS;

/**
 * Returns a 64 bit version number for this library.  
 * @return	a 64-bit integer version number for this library. The top 
 *		 16 bits is  
 * the {@link #getVersionMajor()} value. The next 16-bits are the {@link 
 * #getVersionMinor()}  
 * value, and the last 32-bits are the {@link #getVersionRevision()} 
 * value.  
 */
  public static long getVersion() {
    return XugglerJNI.Global_getVersion();
  }

/**
 * Get the major version number of this library.  
 * @return	the major version number of this library or 0 if unknown. 
 *		  
 */
  public static int getVersionMajor() {
    return XugglerJNI.Global_getVersionMajor();
  }

/**
 * Get the minor version number of this library.  
 * @return	the minor version number of this library or 0 if unknown. 
 *		  
 */
  public static int getVersionMinor() {
    return XugglerJNI.Global_getVersionMinor();
  }

/**
 * Get the revision number of this library.  
 * @return	the revision number of this library, or 0 if unknown.  
 */
  public static int getVersionRevision() {
    return XugglerJNI.Global_getVersionRevision();
  }

/**
 * Get a string representation of the version of this library.  
 * @return	the version of this library in string form.  
 */
  public static String getVersionStr() {
    return XugglerJNI.Global_getVersionStr();
  }

/**
 * Get the version of the FFMPEG libavformat library we are compiled 
 * against.  
 * @return	the version.  
 */
  public static int getAVFormatVersion() {
    return XugglerJNI.Global_getAVFormatVersion();
  }

/**
 * Get the version of the FFMPEG libavformat library we are compiled 
 * against.  
 * @return	the version.  
 */
  public static String getAVFormatVersionStr() {
    return XugglerJNI.Global_getAVFormatVersionStr();
  }

/**
 * Get the version of the FFMPEG libavcodec library we are compiled 
 * against.  
 * @return	the version.  
 */
  public static int getAVCodecVersion() {
    return XugglerJNI.Global_getAVCodecVersion();
  }

/**
 * Get the version of the FFMPEG libavcodec library we are compiled 
 * against.  
 * @return	the version.  
 */
  public static String getAVCodecVersionStr() {
    return XugglerJNI.Global_getAVCodecVersionStr();
  }

/**
 * A value that means no time stamp is set for a given object.  
 * if the {@link IMediaData#getTimeStamp()} method of an  
 * object returns this value it means the time stamp wasn't set.  
 */
  public final static long NO_PTS = XugglerJNI.Global_NO_PTS_get();
/**
 * The default time units per second that we use for decoded  
 * {@link IAudioSamples} and {@link IVideoPicture} objects.  
 * This means that 1 tick of a time stamp is 1 Microsecond.  
 */
  public final static long DEFAULT_PTS_PER_SECOND = XugglerJNI.Global_DEFAULT_PTS_PER_SECOND_get();
}
