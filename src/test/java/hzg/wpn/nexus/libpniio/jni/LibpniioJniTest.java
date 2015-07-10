package hzg.wpn.nexus.libpniio.jni;

import org.junit.BeforeClass;
import sun.misc.Unsafe;

import java.lang.reflect.Field;
import java.nio.file.Files;
import java.nio.file.Paths;

public class LibpniioJniTest {

    @SuppressWarnings("restriction")
    private static Unsafe getUnsafe() {
        try {

            Field singleoneInstanceField = Unsafe.class.getDeclaredField("theUnsafe");
            singleoneInstanceField.setAccessible(true);
            return (Unsafe) singleoneInstanceField.get(null);

        } catch (IllegalArgumentException e) {
            throw new RuntimeException(e);
        } catch (SecurityException e) {
            throw new RuntimeException(e);
        } catch (NoSuchFieldException e) {
            throw new RuntimeException(e);
        } catch (IllegalAccessException e) {
            throw new RuntimeException(e);
        }
    }

    @BeforeClass
    public static void beforeClass(){
        System.out.println("Address size (B):" + getUnsafe().addressSize());
    }

    @org.junit.Test
    public void testCreateFile() throws Exception {
        Files.deleteIfExists(Paths.get("target/test.h5"));
        LibpniioJni.createFile("target/test.h5", "test.nxdl.xml");
    }
}