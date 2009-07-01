package com.xuggle.xuggler;

import static org.junit.Assert.*;

import java.util.Collection;

import org.junit.Test;

public class MetaDataTest
{

  @Test
  public final void testGetKeys()
  {
    IMetaData meta = IMetaData.make();
    assertEquals(0, meta.getNumKeys());
    Collection<String> keys = meta.getKeys();
    assertNotNull(keys);
    assertEquals(0, keys.size());
    meta.setValue("foo", "bar");
    meta.setValue("bar", "goober");
    keys = meta.getKeys();
    assertEquals(2, keys.size());
    System.out.println("MetaData = " + meta);
  }

  @Test
  public final void testGetValue()
  {
    IMetaData meta = IMetaData.make();
    assertEquals(0, meta.getNumKeys());
    Collection<String> keys = meta.getKeys();
    assertNotNull(keys);
    assertEquals(0, keys.size());
    meta.setValue("foo", "bar");
    meta.setValue("bar", "goober");
    keys = meta.getKeys();
    assertEquals(2, keys.size());
    assertEquals("bar", meta.getValue("FoO", IMetaData.Flags.METADATA_NONE));
    assertNull(meta.getValue("FoO", IMetaData.Flags.METADATA_MATCH_CASE));
    assertNull(meta.getValue("notthere"));
  }
  
  @Test
  public void testGetFromContainer()
  {
    IContainer container = IContainer.make();
    container.open("fixtures/testfile.mp3", IContainer.Type.READ, null);
    IMetaData meta = container.getMetaData();
    assertEquals(5, meta.getNumKeys());
    Collection<String> keys = meta.getKeys();
    for(String key : keys)
    {
      System.out.println(key + " = " + meta.getValue(key));
    }
    assertNotNull(meta.getValue("author"));
    meta.setValue("author", "Your Mom");
    assertEquals("Your Mom", meta.getValue("author"));
  }

  @Test
  public void testSetInContainer()
  {
    String filename = getClass().getName()+".mp3";
    IContainer container = IContainer.make();
    container.open(filename, IContainer.Type.WRITE, null);
    IStream stream = container.addNewStream(0);
    IStreamCoder coder = stream.getStreamCoder();
    coder.setCodec(ICodec.ID.CODEC_ID_MP3);
    coder.setSampleRate(22050);
    coder.setChannels(1);
    coder.open();
    
    IMetaData meta = container.getMetaData();
    String author = "Your Mom";
    String genre = "Fat Mothers";
    String title = "Ode to Mothers";
    meta.setValue("title", title);
    meta.setValue("author", author);
    meta.setValue("genre", genre);
    container.writeHeader();
    container.writeTrailer();
    coder.close();
    coder.delete();
    stream.delete();
    container.close();
    container.delete();
    
    container = IContainer.make();
    meta = container.getMetaData();
    assertNull(meta);
    container.open(filename, IContainer.Type.READ, null);
    meta = container.getMetaData();
    assertEquals(author, meta.getValue("author"));
    assertEquals(genre, meta.getValue("genre"));
    assertEquals(title, meta.getValue("title"));
  }


}