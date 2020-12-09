public class Loop {
    public Loop(int x, int y) {
        System.out.println("In constructor Loop: " + x + ", " + y);
    }

    private void foo(int count, boolean b) {
        if (b)
            return;
        System.out.println(count);
    }

    public static void main(String[] args) {
        System.out.println("Hello Loop");
        Loop loop = new Loop(10, 20);
        for (int i = 0; i < 5; i++)
            loop.foo(i, i % 2 == 0);
    }
}
