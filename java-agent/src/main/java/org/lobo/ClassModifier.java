package org.lobo;

import org.objectweb.asm.ClassVisitor;
import org.objectweb.asm.ClassWriter;
import org.objectweb.asm.MethodVisitor;
import org.objectweb.asm.Opcodes;

public class ClassModifier extends ClassVisitor {
    private String name;

    public ClassModifier(ClassWriter writer) {
        super(Opcodes.ASM7, writer);
    }

    @Override
    public void visit(int version, int access, String name, String signature, String superName, String[] interfaces) {
        this.name = name;
        System.out.println("Visit class: " + name);
        super.visit(version, access, name, signature, superName, interfaces);
    }

    @Override
    public MethodVisitor visitMethod(int access, String name, String desc, String signature, String[] exceptions) {
        MethodVisitor originalMethodVisitor = super.visitMethod(access, name, desc, signature, exceptions);
        return new MethodModifier(originalMethodVisitor, this.name, name);
    }
}
