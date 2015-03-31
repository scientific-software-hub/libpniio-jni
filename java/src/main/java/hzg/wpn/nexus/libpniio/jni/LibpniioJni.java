package hzg.wpn.nexus.libpniio.jni;

/**
 * @author ingvord
 * @since 3/31/15
 */
public class LibpniioJni {

    static {
        System.loadLibrary("pniio_jni");
    }

    public native void createFile(String fileName) throws LibpniioException;
}
