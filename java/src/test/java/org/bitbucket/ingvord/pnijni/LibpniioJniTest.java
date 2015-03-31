package org.bitbucket.ingvord.pnijni;

import org.junit.BeforeClass;

import static org.junit.Assert.*;

public class LibpniioJniTest {

    @org.junit.Test
    public void testCreateFile() throws Exception {
        LibpniioJni instance = new LibpniioJni();

        instance.createFile("test.h5");


    }
}