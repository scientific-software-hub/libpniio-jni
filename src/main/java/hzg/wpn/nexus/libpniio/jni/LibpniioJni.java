package hzg.wpn.nexus.libpniio.jni;

import sun.misc.Unsafe;

import java.io.IOException;
import java.io.InputStream;
import java.lang.reflect.Field;
import java.nio.file.Files;
import java.nio.file.Path;
import java.nio.file.Paths;
import java.nio.file.StandardCopyOption;

/**
 * @author ingvord
 * @since 3/31/15
 */
public class LibpniioJni {
    public static final String XENV_ROOT = System.getProperty("XENV_ROOT") != null ? System.getProperty("XENV_ROOT") : "";

    static {
        Unsafe unsafe = getUnsafe();
        int addressSize = unsafe.addressSize();
        if (addressSize != 8)
            throw new Error("Invalid address size [= " + addressSize + " Byte]! Address size must be equal to 8 Byte (64 bits). Probably using unsupported JVM... try x64 JVM");

        String os_name = System.getProperty("os.name");

        if (!"linux".equalsIgnoreCase(os_name)) throw new Error("Currently only linux is supported!");

        extractJniLibrary();

        System.setProperty("java.library.path", Paths.get(XENV_ROOT, "lib/native/x86_64-linux-gnu").toAbsolutePath().toString());

        hackClassLoader();

        System.loadLibrary("pniio_jni");
    }


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

    private static void extractJniLibrary() {
        InputStream pniio_jni = LibpniioJni.class.getResourceAsStream("/lib/native/x86_64-linux-gnu/libpniio_jni.so");

        Path cwd = Paths.get(XENV_ROOT);

        try {
            Files.copy(pniio_jni, Files.createDirectories(cwd.resolve("lib/native/x86_64-linux-gnu")).resolve("libpniio_jni.so"), StandardCopyOption.REPLACE_EXISTING);
        } catch (IOException e) {
            throw new Error("Unable to extract native library.", e);
        }
    }

    private static void hackClassLoader() {
        try {
            Field fieldSysPath = ClassLoader.class.getDeclaredField("sys_paths");
            fieldSysPath.setAccessible(true);
            fieldSysPath.set(null, null);
        } catch (NoSuchFieldException e) {
            throw new RuntimeException(e);
        } catch (IllegalAccessException e) {
            throw new RuntimeException(e);
        }
    }

    public static native long createFile(String fileName, String nx_template) throws LibpniioException;

    public static native long openFile  (String fileName) throws LibpniioException;

    public static native void closeFile(long ptr) throws LibpniioException;

    public static native void write(long ptr, String nx_path, int value, boolean append) throws LibpniioException;

    public static native void write(long ptr, String nx_path, long value, boolean append) throws LibpniioException;

    public static native void write(long ptr, String nx_path, float value, boolean append) throws LibpniioException;

    public static native void write(long ptr, String nx_path, double value, boolean append) throws LibpniioException;

    public static native void write(long ptr, String nx_path, String value, boolean append) throws LibpniioException;

    public static native void write(long ptr, String nx_path, long address, int size, short[] type, boolean append) throws LibpniioException;

    public static native void write(long ptr, String nx_path, long address, int size, int[] type, boolean append) throws LibpniioException;

    public static native void write(long ptr, String nx_path, long address, int size, float[] type, boolean append) throws LibpniioException;
}
