package org.bitbucket.ingvord.pnijni;

/**
 * @author ingvord
 * @since 3/31/15
 */
public class LibpniioJni {

    static {
        System.loadLibrary("pniio_jni");
    }

    public native void createFile(String fileName);
}
