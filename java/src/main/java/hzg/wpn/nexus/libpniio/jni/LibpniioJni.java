package hzg.wpn.nexus.libpniio.jni;

import sun.misc.Unsafe;

import java.lang.reflect.Field;

/**
 * @author ingvord
 * @since 3/31/15
 */
public class LibpniioJni {
    @SuppressWarnings("restriction")
    private static Unsafe getUnsafe() {
        try {

            Field singleoneInstanceField = Unsafe.class.getDeclaredField("theUnsafe");
            singleoneInstanceField.setAccessible(true);
            return (Unsafe) singleoneInstanceField.get(null);
        } catch (Exception e) {
            throw new RuntimeException(e);
        }
    }

    static {
        Unsafe unsafe = getUnsafe();
        int addressSize = unsafe.addressSize();
        if(addressSize != 8) throw new Error("Invalid address size [" +addressSize+ " Byte]! Address size must be equal to 8 Byte");

        System.loadLibrary("pniio_jni");
    }

    public static native long createFile(String fileName, String nx_template) throws LibpniioException;

    public static native long openFile  (String fileName) throws LibpniioException;

    public static native void closeFile(long ptr) throws LibpniioException;

    public static native void write(long ptr, String nx_path, int value) throws LibpniioException;

    public static native void write(long ptr, String nx_path, long value) throws LibpniioException;

    public static native void write(long ptr, String nx_path, float value) throws LibpniioException;

    public static native void write(long ptr, String nx_path, double value) throws LibpniioException;

    public static native void write(long ptr, String nx_path, String value) throws LibpniioException;

    public static native void write_and_grow(long ptr, String nx_path, int value) throws LibpniioException;

    public static native void write_and_grow(long ptr, String nx_path, long value) throws LibpniioException;

    public static native void write_and_grow(long ptr, String nx_path, float value) throws LibpniioException;

    public static native void write_and_grow(long ptr, String nx_path, double value) throws LibpniioException;

    public static native void write_and_grow(long ptr, String nx_path, String value) throws LibpniioException;
}
