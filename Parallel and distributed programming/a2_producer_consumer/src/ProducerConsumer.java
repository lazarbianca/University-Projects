import java.util.concurrent.atomic.AtomicInteger;

public class ProducerConsumer {
    private final SynchronizedQueue queue;
    private final int[] a;
    private final int[] b;
    private final AtomicInteger sum;

    public ProducerConsumer(SynchronizedQueue queue, int[] a, int[] b, AtomicInteger sum) {
        this.queue = queue;
        this.a = a;
        this.b = b;
        this.sum = sum;
    }

    public void start() throws InterruptedException {
        Thread producerThread = new Thread(new Producer(queue, a, b));
        Thread consumerThread = new Thread(new Consumer(queue, sum));

        producerThread.start();
        consumerThread.start();

        producerThread.join();
        consumerThread.join();

        System.out.println("ALL THREADS JOINED");
    }

    public static void displayResults(int[] a, int[] b, AtomicInteger sum) {
        System.out.println("For a = ");
        for (int element : a) {
            System.out.print(element + " ");
        }
        System.out.println("\nand b = ");
        for (int element : b) {
            System.out.print(element + " ");
        }
        System.out.println("\nFinal sum is: " + sum);
    }
}