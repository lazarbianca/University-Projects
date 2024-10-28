import org.junit.jupiter.api.BeforeEach;
import org.junit.jupiter.api.Test;

import java.util.concurrent.atomic.AtomicInteger;

import static org.junit.jupiter.api.Assertions.assertEquals;

public class ProducerConsumerTests {
    private static final int capacity = 5;
    private SynchronizedQueue queue;
    private AtomicInteger sum;

    @BeforeEach
    public void setUp() {
        queue = new SynchronizedQueue(capacity);
        sum = new AtomicInteger(0);
    }

    @Test
    public void testCaseBothArraysWith100ValuesOfOne() throws InterruptedException {
        int[] a = new int[100];
        int[] b = new int[100];
        for (int i = 0; i < 100; i++) {
            a[i] = 1;
            b[i] = 1;
        }

        runProducerConsumerTests(a, b);
        assertEquals(100, sum.get(), "Sum should be 100");
    }

    @Test
    public void testCaseAIsOneAndBIsConsecutiveFrom1To100() throws InterruptedException {
        int[] a = new int[100];
        int[] b = new int[100];
        for (int i = 0; i < 100; i++) {
            a[i] = 1;
            b[i] = i + 1;
        }

        runProducerConsumerTests(a, b);
        assertEquals(5050, sum.get(), "Sum should be the sum of numbers from 1 to 100 (100*101 /2)");
    }

    @Test
    public void testCaseBothArraysConsecutiveFrom1To100() throws InterruptedException {
        int[] a = new int[100];
        int[] b = new int[100];
        for (int i = 0; i < 100; i++) {
            a[i] = i + 1;
            b[i] = i + 1;
        }

        runProducerConsumerTests(a, b);
        int expectedSum = (100 * 101 * 201) / 6;
        assertEquals(expectedSum, sum.get(), "Sum should be the sum of squares of numbers from 1 to 100 " +
                "(n * (n+1) * (2n+1) /6");
    }

    private void runProducerConsumerTests(int[] a, int[] b) throws InterruptedException {
        ProducerConsumer producerConsumer = new ProducerConsumer(queue, a, b, sum);
        producerConsumer.start();
    }
}
