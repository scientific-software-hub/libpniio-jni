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
        System.out.println(String.format("Creating file %s from %s","target/test_create.h5", Paths.get("test.nxdl.xml").toAbsolutePath().toString()));
        NxFile file = NxFile.create("target/test_create.h5", Paths.get("test.nxdl.xml").toAbsolutePath().toString());
        file.close();
    }
}
