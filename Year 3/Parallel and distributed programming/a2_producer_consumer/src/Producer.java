public class Producer implements Runnable {
    private final SynchronizedQueue queue;
    private final int[] a;
    private final int[] b;

    public Producer(SynchronizedQueue queue, int[] a, int[] b) {
        this.queue = queue;
        this.a = a;
        this.b = b;
    }

    @Override
    public void run() {
        try {
            for (int i = 0; i < a.length; i++) {
                queue.enqueue(a[i] * b[i]);
            }
        } catch (Exception e) {
            Thread.currentThread().interrupt();
            e.printStackTrace();
        }
    }
}