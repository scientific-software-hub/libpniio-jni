package hzg.wpn.nexus.libpniio.jni;

/**
 * @author ingvord
 * @since 3/31/15
 */
public class LibpniioJni {
    static {
        System.loadLibrary("pniio_jni");
    }

    public static native long createFile(String fileName) throws LibpniioException;

    public static native long openFile  (String fileName) throws LibpniioException;

    public static native void closeFile(long ptr) throws LibpniioException;

    public static native void write(long ptr, String nx_path, int value, boolean append) throws LibpniioException;

    public static native void write(long ptr, String nx_path, long value, boolean append) throws LibpniioException;

    public static native void write(long ptr, String nx_path, float value, boolean append) throws LibpniioException;

    public static native void write(long ptr, String nx_path, double value, boolean append) throws LibpniioException;

    public static native void write(long ptr, String nx_path, String value, boolean append) throws LibpniioException;
}
