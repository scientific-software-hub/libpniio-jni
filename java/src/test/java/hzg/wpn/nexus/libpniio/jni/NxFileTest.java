package hzg.wpn.nexus.libpniio.jni;

import org.junit.After;
import org.junit.Before;
import org.junit.Test;
import sun.nio.ch.DirectBuffer;

import javax.imageio.ImageIO;
import java.awt.image.BufferedImage;
import java.awt.image.DataBufferByte;
import java.awt.image.DataBufferInt;
import java.io.File;
import java.nio.ByteBuffer;
import java.nio.ByteOrder;
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
        file = NxFile.open("test.h5");
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
    public void testWrite_intArr() throws Exception {
        BufferedImage image = ImageIO.read(Files.newInputStream(Paths.get("url.png")));

        byte[] pixels = ((DataBufferByte) image.getRaster().getDataBuffer()).getData();

        int[] data = new int[pixels.length / 4];

        ByteBuffer.wrap(pixels).asIntBuffer().get(data);

        file.write("/entry/scan/data/image/value",data);
    }
}