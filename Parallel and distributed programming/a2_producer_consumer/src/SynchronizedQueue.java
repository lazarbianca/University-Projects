import java.util.LinkedList;
import java.util.Queue;
import java.util.concurrent.locks.Condition;
import java.util.concurrent.locks.ReentrantLock;
public class SynchronizedQueue {
    private final LinkedList<Integer> queue;
    private final ReentrantLock lock;
    protected final Condition conditionalVariable;
    private final int capacity;

    public SynchronizedQueue(int capacity) {
        this.queue = new LinkedList<>();
        this.lock = new ReentrantLock();
        this.conditionalVariable = lock.newCondition();
        this.capacity = capacity;
    }

    public boolean empty() {
        lock.lock();
        try {
            return queue.isEmpty();
        } finally {
            lock.unlock();
        }
    }

    public boolean full() {
        lock.lock();
        try {
            return queue.size() == capacity;
        } finally {
            lock.unlock();
        }
    }

    public void enqueue(Integer value) throws InterruptedException {
        lock.lock();
        try {
            while (queue.size() == capacity) {
                conditionalVariable.await();
            }
            queue.add(value);
            conditionalVariable.signal();
        } finally {
            lock.unlock();
        }
    }

    public Integer dequeue() throws InterruptedException {
        lock.lock();
        try {
            while (queue.isEmpty()) {
                conditionalVariable.await();
            }
            Integer temp = queue.poll();
            conditionalVariable.signal();
            return temp;
        } finally {
            lock.unlock();
        }
    }
}