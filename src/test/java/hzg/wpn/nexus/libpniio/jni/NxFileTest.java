package hzg.wpn.nexus.libpniio.jni;

import org.junit.*;
import org.junit.rules.TestRule;
import org.junit.rules.TestWatcher;
import org.junit.runner.Description;

import java.nio.file.Files;
import java.nio.file.Paths;

/**
 * @author ingvord
 * @since 4/1/15
 */
@Ignore
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
        file.write("/entry/string_scalar", "Hello World!!!");
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
        file.write("/entry/double_scalar", Math.random());
    }

    @Test
    public void testWrite_double_overwrite() throws Exception {
        file.write("/entry/double_scalar", 1);
        file.write("/entry/double_scalar", 2);
        file.write("/entry/double_scalar", 3);
        file.write("/entry/double_scalar", 4);
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



    @Test
    public void testAppend_String() throws Exception {
        file.write("/entry/string/value", "Hello World!!!", true);
    }

    @Test(expected = NullPointerException.class)
    public void testWriteString_null() throws Exception {
        file.write("/entry/string/value", (String) null);
    }

    @Test(expected = LibpniioException.class)
    public void test_getNonDataset() throws Exception {
        file.write("/entry/string", "Whatever");
    }

    @Test
    public void testWriteDouble_null() throws Exception {
        file.write("/entry/double/value", Double.NaN);
    }
}