package hzg.wpn.nexus.libpniio.jni;

import java.io.Closeable;
import java.io.IOException;

/**
 * @author ingvord
 * @since 4/1/15
 */
public class NxFile implements Closeable {
    private final String name;
    private final long ptr;
    private volatile boolean isClosed = false;

    private NxFile(String name, long ptr) {
        this.name = name;
        this.ptr = ptr;
    }

    public static NxFile create(String fileName) throws LibpniioException {
        long ptr = LibpniioJni.createFile(fileName);
        return new NxFile(fileName, ptr);
    }

    public static NxFile open(String fileName) throws LibpniioException {
        long ptr = LibpniioJni.openFile(fileName);
        return new NxFile(fileName, ptr);
    }

    public void write(String nxPath, int value, boolean append) throws LibpniioException {
        LibpniioJni.write(ptr, nxPath, value, append);
    }

    public void write(String nxPath, String value, boolean append) throws LibpniioException {
        LibpniioJni.write(ptr, nxPath, value, append);
    }

    @Override
    protected void finalize() throws Throwable {
        if(!isClosed) LibpniioJni.closeFile(ptr);
    }

    public void close() throws IOException {
        try {
            LibpniioJni.closeFile(ptr);
            isClosed = true;
        } catch (LibpniioException e) {
            throw new IOException(e);
        }
    }
}
