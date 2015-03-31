package hzg.wpn.nexus.libpniio.jni;

public class LibpniioJniTest {

    @org.junit.Test
    public void testCreateFile() {
        LibpniioJni instance = new LibpniioJni();

        try {
            instance.createFile("test.h5");
        } catch (LibpniioException e) {
            e.printStackTrace();
        }


    }
}