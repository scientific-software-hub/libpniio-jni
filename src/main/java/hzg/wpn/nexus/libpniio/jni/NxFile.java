package hzg.wpn.nexus.libpniio.jni;

import sun.nio.ch.DirectBuffer;

import java.io.Closeable;
import java.io.IOException;
import java.nio.ByteBuffer;

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

    public static NxFile create(String fileName, String nxTemplate) throws LibpniioException {
        long ptr = LibpniioJni.createFile(fileName, nxTemplate);
        return new NxFile(fileName, ptr);
    }

    public static NxFile open(String fileName) throws LibpniioException {
        long ptr = LibpniioJni.openFile(fileName);
        return new NxFile(fileName, ptr);
    }

    public String getFileName() {
        return name;
    }

    public void write(String nxPath, int value) throws LibpniioException {
        LibpniioJni.write(ptr, nxPath, value, false);
    }

    public void write(String nxPath, long value) throws LibpniioException {
        LibpniioJni.write(ptr, nxPath, value, false);
    }

    public void write(String nxPath, float value) throws LibpniioException {
        LibpniioJni.write(ptr, nxPath, value, false);
    }

    public void write(String nxPath, double value) throws LibpniioException {
        LibpniioJni.write(ptr, nxPath, value, false);
    }

    public void write(String nxPath, String value) throws LibpniioException {
        LibpniioJni.write(ptr, nxPath, value, false);
    }

    public void write(String nx_path, int[] data) throws LibpniioException {
        write(nx_path, data, false);
    }

    public void write(String nx_path, float[] data) throws LibpniioException {
        write(nx_path, data, false);
    }

    public void append(String nxPath, int value) throws LibpniioException {
        LibpniioJni.write(ptr, nxPath, value, true);
    }

    public void append(String nxPath, long value) throws LibpniioException {
        LibpniioJni.write(ptr, nxPath, value, true);
    }

    public void append(String nxPath, float value) throws LibpniioException {
        LibpniioJni.write(ptr, nxPath, value, true);
    }

    public void append(String nxPath, double value) throws LibpniioException {
        LibpniioJni.write(ptr, nxPath, value, true);
    }

    public void append(String nxPath, String value) throws LibpniioException {
        LibpniioJni.write(ptr, nxPath, value, true);
    }

    public void append(String nx_path, int[] data) throws LibpniioException {
        write(nx_path, data, true);
    }

    public void append(String nx_path, float[] data) throws LibpniioException {
        write(nx_path, data, true);
    }

    public void write(String nxPath, int value, boolean append) throws LibpniioException {
        LibpniioJni.write(ptr, nxPath, value, append);
    }

    public void write(String nxPath, long value, boolean append) throws LibpniioException {
        LibpniioJni.write(ptr, nxPath, value, append);
    }

    public void write(String nxPath, float value, boolean append) throws LibpniioException {
        LibpniioJni.write(ptr, nxPath, value, append);
    }

    public void write(String nxPath, double value, boolean append) throws LibpniioException {
        LibpniioJni.write(ptr, nxPath, value, append);
    }

    public void write(String nxPath, String value, boolean append) throws LibpniioException {
        LibpniioJni.write(ptr, nxPath, value, append);
    }

    public void write(String nx_path, int[] data, boolean append) throws LibpniioException {
        ByteBuffer buffer = ByteBuffer.allocateDirect(data.length*4);

        buffer.asIntBuffer().put(data);

        LibpniioJni.write(ptr, nx_path, ((DirectBuffer) buffer).address(), data.length, data, append);
    }

    public void write(String nx_path, float[] data, boolean append) throws LibpniioException {
        ByteBuffer buffer = ByteBuffer.allocateDirect(data.length*4);

        buffer.asFloatBuffer().put(data);

        LibpniioJni.write(ptr, nx_path, ((DirectBuffer) buffer).address(), data.length, data, append);
    }

    @Override
    protected void finalize() throws Throwable {
        if(!isClosed) LibpniioJni.closeFile(ptr);
        super.finalize();
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
