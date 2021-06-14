package hzg.wpn.nexus.libpniio.jni;

import org.junit.After;
import org.junit.Before;
import org.junit.Ignore;
import org.junit.Test;

import java.nio.file.Files;
import java.nio.file.Paths;

@Ignore
public class TestCreateNexus {

    @Before
    public void before() throws Exception{
        Files.deleteIfExists(Paths.get("target/test_create.h5"));
    }

    @Test
    public void create() throws Exception{
        NxFile file = NxFile.create("target/test_create.h5", "test.nxdl.xml");
        file.close();
    }
}
