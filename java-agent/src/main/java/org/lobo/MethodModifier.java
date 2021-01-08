package org.lobo;

import org.objectweb.asm.Label;
import org.objectweb.asm.MethodVisitor;
import org.objectweb.asm.Opcodes;

public class MethodModifier extends MethodVisitor {
    private String className;
    private String methodName;
    private int numParams;
    private boolean firstInstruction;

    public MethodModifier(MethodVisitor methodVisitor, String className, String methodName) {
        super(Opcodes.ASM7, methodVisitor);
        this.className = className;
        this.methodName = methodName;
    }

    @Override
    public void visitParameter(String name, int access) {
        // TODO: Class needs to be compiled with -parameters
//        numParams++;
//        System.out.println("  Visit parameter: " + name + " {" + access + "}");
//        super.visitParameter(name, access);
    }

    @Override
    public void visitLocalVariable(String name, String descriptor, String signature, Label start, Label end, int index) {
        // TODO: Called after visitCode()
//        System.out.println("Visit local var: " + name);
//        if (!firstInstruction)
//            numParams++;
//        super.visitLocalVariable(name, descriptor, signature, start, end, index);
    }

    @Override
    public void visitCode() {
        System.out.println("Visit method: " + className + "." + methodName + "()");
        firstInstruction = true;

        // Add a print to stdout
        // TODO: Assume the method has a stack size of at least 2 (since we use 2 stack slots (out, "Executing ..."))
        mv.visitFieldInsn(Opcodes.GETSTATIC, "java/lang/System", "out", "Ljava/io/PrintStream;");
        if (methodName.startsWith("<") && methodName.endsWith(">"))
            mv.visitLdcInsn("Executing constructor: " + className + "." + methodName);
        else
            mv.visitLdcInsn("Executing method: " + className + "." + methodName);
        mv.visitMethodInsn(Opcodes.INVOKEVIRTUAL, "java/io/PrintStream", "println", "(Ljava/lang/String;)V",
                false);
        System.out.println("  Instrumented method: " + className + "." + methodName + " {" + numParams + "}");

        super.visitCode();
    }
}
