package hzg.wpn.nexus.libpniio.jni;

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
        String os_name = System.getProperty("os.name");

        if (!"linux".equalsIgnoreCase(os_name)) {
            System.err.println("Currently only linux is supported!");
            throw new RuntimeException("Currently only linux is supported!");
        }

        try {
            extractJniLibrary();
        } catch (IOException e) {
            System.err.println("Failed to extract jni library: " + e.getMessage());
            e.printStackTrace();
            throw new RuntimeException(e);
        }

        System.setProperty("java.library.path", Paths.get(XENV_ROOT, "lib/native/x86_64-linux-gnu").toAbsolutePath().toString());

        try {
            hackClassLoader();

            System.loadLibrary("pniio_jni");
        } catch (NoSuchFieldException | IllegalAccessException e) {
            System.err.println("Failed to hack class loader: " + e.getMessage());
            e.printStackTrace();
            throw new RuntimeException(e);
        } catch (Throwable throwable) {
            System.err.println("Failed to load library: " + throwable.getMessage());
            throwable.printStackTrace();
            throw throwable;
        }
    }


    @SuppressWarnings("restriction")
    private static void extractJniLibrary() throws IOException {
        InputStream pniio_jni = LibpniioJni.class.getResourceAsStream("/lib/native/x86_64-linux-gnu/libpniio_jni.so");

        Path cwd = Paths.get(XENV_ROOT);

        Files.copy(pniio_jni, Files.createDirectories(cwd.resolve("lib/native/x86_64-linux-gnu")).resolve("libpniio_jni.so"), StandardCopyOption.REPLACE_EXISTING);
    }

    private static void hackClassLoader() throws NoSuchFieldException, IllegalAccessException {
        Field fieldSysPath = ClassLoader.class.getDeclaredField("sys_paths");
        fieldSysPath.setAccessible(true);
        fieldSysPath.set(null, null);
    }

    public static native long createFile(String fileName, String nx_template) throws LibpniioException;

    public static native long openFile  (String fileName) throws LibpniioException;

    public static native void closeFile(long ptr) throws LibpniioException;

    public static native void write(long ptr, String nx_path, int value, boolean append) throws LibpniioException;

    public static native void write(long ptr, String nx_path, long value, boolean append) throws LibpniioException;

    public static native void write(long ptr, String nx_path, float value, boolean append) throws LibpniioException;

    public static native void write(long ptr, String nx_path, double value, boolean append) throws LibpniioException;

    public static native void write(long ptr, String nx_path, String value, boolean append) throws LibpniioException;
}
