package org.lobo;

import java.lang.instrument.Instrumentation;

public class JavaAgent {
    public static void premain(String args, Instrumentation inst) {
        agentStartup(args, inst, "premain");
    }

    private static void agentStartup(String args, Instrumentation inst, String invocation) {
        System.out.println("Starting the [" + invocation + "] agent");

        inst.addTransformer(new Transformer());
    }
}
