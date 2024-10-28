// seed de la 0 cu mutex global
// th[i] random.seed(seed+1)
// or: ThreadLocalRandom
import java.util.concurrent.atomic.AtomicInteger;

public class Main {
    public static void main(String[] args) throws InterruptedException {
        int capacity = 5;
        SynchronizedQueue queue = new SynchronizedQueue(capacity);
        AtomicInteger sum = new AtomicInteger(0);

        int[] a = new int[100];
        int[] b = new int[100];
        for (int i = 1; i <= 100; i++) {
            a[i] = i;
            b[i] = i;
        }

        ProducerConsumer producerConsumer = new ProducerConsumer(queue, a, b, sum);
        producerConsumer.start();
        ProducerConsumer.displayResults(a, b, sum);
    }
}
