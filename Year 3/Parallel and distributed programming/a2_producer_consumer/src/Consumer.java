import java.util.concurrent.atomic.AtomicInteger;

public class Consumer implements Runnable {
    private final SynchronizedQueue queue;
    private final AtomicInteger sum;

    public Consumer(SynchronizedQueue queue, AtomicInteger sum) {
        this.queue = queue;
        this.sum = sum;
    }

    @Override
    public void run() {
        try {
            for (int i = 0; i < 100; i++) {
                sum.addAndGet(queue.dequeue());
            }
        } catch (Exception e) {
            Thread.currentThread().interrupt();
            e.printStackTrace();
        }
    }
}

