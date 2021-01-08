public class Loop {
    public Loop(int x, int y) {
        System.out.println("In constructor Loop: " + x + ", " + y);
    }

    private void foo(int count, boolean b) {
        if (b)
            return;
        System.out.println(count);
    }

    private int add(int x, int y) {
        return x + y;
    }

    private int addTwo(int x) {
        return x + 2;
    }

    private static int subTwo(int x) {
        return x - 2;
    }

    private static void bar() {
        System.out.println("In bar");
    }

    public static void main(String[] args) {
        System.out.println("Hello Loop");
        Loop loop = new Loop(10, 20);
        Loop loop2 = new Loop(100, 200);
        for (int i = 0; i < 5; i++)
            loop.foo(loop2.add(i, i*i), i % 2 == 0);
        System.out.println("Add 2 returned: " + loop.addTwo(100));
        System.out.println("Static sub 2 returned: " + subTwo(100));
        bar();
    }
}
