package libemojidex;

import java.io.InputStream;
import java.io.FileOutputStream;
import java.io.File;

/**
 *  Native library loader.
 */
public final class NativeLibLoader
{
  /**
   *  Load library.
   */
  static void load()
  {
    load("emojidex_swig");
  }

  /**
   *  Load library.
   */
  private static void load(String name)
  {
    try
    {
      System.loadLibrary(name);
    }
    catch(UnsatisfiedLinkError e)
    {
      loadFromJar(name);
    }
  }

  /**
   *  Load library from jar file.
   */
  private static void loadFromJar(String name)
  {
    try
    {
      final String path = "lib" + name + ".so";;
      final InputStream is = NativeLibLoader.class.getClassLoader().getResourceAsStream(path);

      final File tmp = File.createTempFile(name, ".tmp");
      tmp.deleteOnExit();

      final FileOutputStream os = new FileOutputStream(tmp);
      final byte[] buf = new byte[4096];
      int readBytes;

      while( (readBytes = is.read(buf)) != -1 )
        os.write(buf, 0, readBytes);

      os.close();
      is.close();

      System.load(tmp.getAbsolutePath());
    }
    catch(Exception e)
    {
      e.printStackTrace();
    }
  }
}
