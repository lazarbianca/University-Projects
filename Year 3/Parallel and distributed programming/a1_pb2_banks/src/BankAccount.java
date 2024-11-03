import java.util.ArrayList;
import java.util.List;
import java.util.concurrent.locks.ReentrantLock;

public class BankAccount {
    private final int id;
    private int balance;
    private final int initialBalance; // for consistency check
    private List<LogRecord> log;
    private final ReentrantLock lock; // for fairness :D

    public BankAccount(int id, int initialBalance) {
        this.id = id;
        this.balance = initialBalance;
        this.initialBalance = initialBalance;
        log = new ArrayList<LogRecord>();
        lock = new ReentrantLock();
    }

    public BankAccount(int id, int initialBalance, List<LogRecord> log, ReentrantLock lock) {
        this.id = id;
        this.balance = initialBalance;
        this.initialBalance = initialBalance;
        this.log = log;
        this.lock = lock;
    }

    public int getId() {
        return id;
    }

    public int getBalance() {
        return balance;
    }

    public ReentrantLock getLock() {
        return lock;
    }

    public List<LogRecord> getLogs() {
        return log;
    }

    public int getInitialBalance() {
        return initialBalance;
    }

    public void transfer(int amount){
        balance += amount;
    }
    public void addLog(LogRecord record){
        log.add(record);
    }
}
