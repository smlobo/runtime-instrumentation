import org.junit.jupiter.api.DynamicTest;
import org.junit.jupiter.api.TestFactory;
import org.junit.jupiter.api.function.Executable;

import java.io.*;
import java.util.ArrayList;
import java.util.List;

import static org.junit.jupiter.api.Assertions.assertEquals;
import static org.junit.jupiter.api.Assertions.assertFalse;

public class ITExamples {
    @TestFactory
    public List<DynamicTest> testEverything() throws Exception {
        List<DynamicTest> answer = new ArrayList<DynamicTest>();
        for(File f : new File("src/test/java/").listFiles()) {
            if (!f.getName().endsWith(".java") || f.getName().startsWith("IT")) {
                continue;
            }
            final String name = f.getName().substring(0, f.getName().indexOf("."));

            // Run the test vanilla
            DynamicTest test = DynamicTest.dynamicTest(name, new Executable() {
                public void execute() throws Throwable {
                    ITExamples.this.execute(name);
                }
            });
            answer.add(test);

        }
        assertFalse(answer.isEmpty());
        return answer;
    }

    protected void execute(String simpleFileNameWithoutJava) throws Exception {
        System.out.println("Running " + simpleFileNameWithoutJava + " as IntegrationTest");

        // Generate the arguments
        ArrayList<String> execArgs = new ArrayList<String>();
        execArgs.add("java");
        // Read the jarfile name from the pom.xml Maven property
        execArgs.add("-javaagent:target/java-agent-1.0-SNAPSHOT.jar");
        execArgs.add("-cp");
        execArgs.add("target/test-classes");
        execArgs.add(simpleFileNameWithoutJava);

        // Exec the new java process
        Process process = Runtime.getRuntime().exec(execArgs.toArray(new String[execArgs.size()]));

        // Print the output stream
        BufferedReader processOutput = new BufferedReader(new InputStreamReader(process.getInputStream()));
        String processLine = processOutput.readLine();
        while (processLine != null) {
            System.out.println(processLine);
            processLine = processOutput.readLine();
        }

        process.waitFor();
        processOutput.close();

        assertEquals(0, process.exitValue());
        System.out.println("  PASSED: " + simpleFileNameWithoutJava);
    }
}
