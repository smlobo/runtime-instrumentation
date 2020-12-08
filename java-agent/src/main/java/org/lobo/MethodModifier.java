package org.lobo;

import org.objectweb.asm.MethodVisitor;
import org.objectweb.asm.Opcodes;

public class MethodModifier extends MethodVisitor {
    private String className;
    private String methodName;
    private int numParams;

    public MethodModifier(MethodVisitor methodVisitor, String className, String methodName) {
        super(Opcodes.ASM7, methodVisitor);
        this.className = className;
        this.methodName = methodName;
    }

    @Override
    public void visitParameter(String name, int access) {
        numParams++;
        super.visitParameter(name, access);
    }

    @Override
    public void visitCode() {
        System.out.println("Visit method: " + className + "." + methodName + " {" + numParams + "}");

        // Add a print to stdout
        // TODO: Since we're putting 2 locals on the stack, the method needs to have at least 2 local variable slots
        if (!methodName.startsWith("<")) {
            mv.visitFieldInsn(Opcodes.GETSTATIC, "java/lang/System", "out", "Ljava/io/PrintStream;");
            mv.visitLdcInsn("Executing method: " + className + "." + methodName);
            mv.visitMethodInsn(Opcodes.INVOKEVIRTUAL, "java/io/PrintStream", "println", "(Ljava/lang/String;)V",
                    false);
        }

        super.visitCode();
    }
}
