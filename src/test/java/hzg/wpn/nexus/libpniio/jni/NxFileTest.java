package hzg.wpn.nexus.libpniio.jni;

import org.junit.After;
import org.junit.Before;
import org.junit.Test;

import java.nio.file.Files;
import java.nio.file.Paths;

/**
 * @author ingvord
 * @since 4/1/15
 */
public class NxFileTest {
    private NxFile file;

    @Before
    public void before() throws Exception{
        file = NxFile.open("target/test.h5");
    }

    @After
    public void after() throws Exception{
        file.close();
    }

    @Test
    public void testWrite_String() throws Exception {
        file.write("/entry/title","Hello World!!!");
    }

    @Test
    public void testWrite_int() throws Exception {
        file.write("/entry/hardware/pco/camera/x0",12);
    }

    @Test
    public void testWrite_float() throws Exception {
        file.write("/entry/hardware/pco/camera/px_size", 3.14F);
    }

    @Test
    public void testWrite_double() throws Exception {
        file.write("/entry/hardware/beam_current/current/value", Math.random());
        file.write("/entry/hardware/beam_current/current/time", System.currentTimeMillis());
    }

    @Test
    public void testAppend_double() throws Exception {
        file.append("/entry/hardware/beam_current/current/value", Math.random());
        file.append("/entry/hardware/beam_current/current/time", System.currentTimeMillis());
    }

    @Test
    public void testWrite_intArr() throws Exception {
        byte[] bytes = Files.readAllBytes(Paths.get("url.bmp"));

        int[] data = new int[bytes.length / 3 - 18];

        for (int i = 0, j = 0; i < data.length; ++i) {
            int rgb;//0
            rgb = (bytes[j++] & 255) << 16;
            rgb |= (bytes[j++] & 255) << 8;
            rgb |= bytes[j++] & 255;
            data[i] = rgb;
        }

//        ByteBuffer.wrap(bytes).asIntBuffer().get(data);

//        BufferedImage test_out = new BufferedImage(512,512,BufferedImage.TYPE_INT_RGB);
//
//        test_out.setRGB(0,0,512,512,data,0,512);
//
//        ImageIO.write(test_out,"bmp", new File("test_out.bmp"));

        file.write("/entry/scan/data/image/value",data);
    }

    @Test
    public void testWrite_intArr_append() throws Exception {
        byte[] bytes = Files.readAllBytes(Paths.get("url.bmp"));

        int[] data = new int[bytes.length / 3 - 18];

        for (int i = 0, j = 0; i < data.length; ++i) {
            int rgb;//0
            rgb = (bytes[j++] & 255) << 16;
            rgb |= (bytes[j++] & 255) << 8;
            rgb |= bytes[j++] & 255;
            data[i] = rgb;
        }

//        ByteBuffer.wrap(bytes).asIntBuffer().get(data);

//        BufferedImage test_out = new BufferedImage(512,512,BufferedImage.TYPE_INT_RGB);
//
//        test_out.setRGB(0,0,512,512,data,0,512);
//
//        ImageIO.write(test_out,"bmp", new File("test_out.bmp"));

        file.append("/entry/scan/data/image/value", data);
    }
}