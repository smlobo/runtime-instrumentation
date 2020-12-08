package org.lobo;

import org.objectweb.asm.ClassReader;
import org.objectweb.asm.ClassWriter;

import java.lang.instrument.ClassFileTransformer;
import java.lang.instrument.IllegalClassFormatException;
import java.security.ProtectionDomain;

public class Transformer implements ClassFileTransformer {
    private static final String[] DO_NOT_TRANSFORM = new String[] {
            "java/util",
            "java/lang",
            "java/io",
            "java/nio",
            "java/security",
            "java/net",
            "sun/",
            "com/sun",
            "jdk/",
            "jre/",
            "[",
            "org/objectweb/asm"
    };

    private static boolean doNotTransform(String className) {
        for (String s : DO_NOT_TRANSFORM) {
            if (className.startsWith(s))
                return true;
        }
        return false;
    }

    public byte[] transform(ClassLoader loader, String className, Class<?> classBeingRedefined,
                            ProtectionDomain protectionDomain, byte[] classfileBuffer) throws IllegalClassFormatException {
        if (doNotTransform(className))
            return null;

        ClassReader reader = new ClassReader(classfileBuffer);
        ClassWriter writer = new ClassWriter(reader, 0);
        ClassModifier modifier = new ClassModifier(writer);
        reader.accept(modifier, 0);
        return writer.toByteArray();
    }
}
