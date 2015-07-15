package hzg.wpn.nexus.libpniio.jni;

import org.junit.After;
import org.junit.Before;
import org.junit.Rule;
import org.junit.Test;
import org.junit.rules.TestRule;
import org.junit.rules.TestWatcher;
import org.junit.runner.Description;

import java.nio.file.Files;
import java.nio.file.Paths;

/**
 * @author ingvord
 * @since 4/1/15
 */
public class NxFileTest {
    public static final String TEST_NXDL_XML = "test.nxdl.xml";
    private NxFile file;
    private String testName;
    @Rule
    public TestRule watcher = new TestWatcher() {
        protected void starting(Description description) {
            testName = description.getMethodName();
        }
    };

    @Before
    public void before() throws Exception{
        Files.deleteIfExists(Paths.get("target/" + testName + ".h5"));
        file = NxFile.create("target/" + testName + ".h5", TEST_NXDL_XML);
    }

    @After
    public void after() throws Exception{
        file.close();
    }

    @Test
    public void testWrite_String() throws Exception {
        file.write("/entry/string/value", "Hello World!!!");
    }

    @Test
    public void testWrite_int() throws Exception {
        file.write("/entry/int/value", 12);
    }

    @Test
    public void testWrite_float() throws Exception {
        file.write("/entry/float/value", 3.14F);
    }

    @Test
    public void testWrite_double() throws Exception {
        file.write("/entry/double/value", Math.random());
        file.write("/entry/double/time", System.currentTimeMillis());
    }

    @Test
    public void testAppend_double_Once() throws Exception {
        file.write("/entry/double/value", Math.random(), true);
        file.write("/entry/double/time", System.currentTimeMillis(), true);
    }

    @Test
    public void testAppend_double() throws Exception {
        file.write("/entry/double/value", Math.random(), true);
        file.write("/entry/double/time", System.currentTimeMillis(), true);
        file.write("/entry/double/value", Math.random(), true);
        file.write("/entry/double/time", System.currentTimeMillis(), true);
        file.write("/entry/double/value", Math.random(), true);
        file.write("/entry/double/time", System.currentTimeMillis(), true);
        file.write("/entry/double/value", Math.random(), true);
        file.write("/entry/double/time", System.currentTimeMillis(), true);
        file.write("/entry/double/value", Math.random(), true);
        file.write("/entry/double/time", System.currentTimeMillis(), true);
    }

    //@Test
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
    public void testWriteString() throws Exception {
        file.write("/entry/string/value", "Hello World!!!");
    }

    //@Test
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

        file.write("/entry/scan/data/image/value", data, true);
    }

    @Test
    public void testWriteShortArray() throws Exception {
        file.write("/entry/data/data", new short[]{
                255, 0, 0, 0, 0, 0, 0, 255,
                0, 0, 255, 255, 255, 255, 0, 0,
                0, 0, 255, 255, 255, 255, 0, 0,
                255, 0, 0, 0, 0, 0, 0, 255
        }, true);
    }

    @Test(expected = NullPointerException.class)
    public void testWriteString_null() throws Exception {
        file.write("/entry/string/value", (String) null);
    }

    @Test(expected = NullPointerException.class)
    public void testWriteArray_null() throws Exception {
        file.write("/entry/data/data", (short[]) null);
    }

    @Test
    public void testWriteDouble_null() throws Exception {
        file.write("/entry/double/value", Double.NaN);
    }
}