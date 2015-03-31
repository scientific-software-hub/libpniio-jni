package hzg.wpn.nexus.libpniio.jni;

import org.junit.After;
import org.junit.Before;
import org.junit.BeforeClass;
import org.junit.Test;

import static org.junit.Assert.*;

/**
 * @author ingvord
 * @since 4/1/15
 */
public class NxFileTest {
    private NxFile file;

    @Before
    public void before() throws Exception{
        file = NxFile.open("test.h5");
    }

    @After
    public void after() throws Exception{
        file.close();
    }

    @Test
    public void testWrite_String() throws Exception {
        file.write("/entry/title","Hello World!!!",false);
    }
}