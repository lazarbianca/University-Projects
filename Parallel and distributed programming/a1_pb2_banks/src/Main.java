import java.util.ArrayList;
import java.util.List;
import java.util.concurrent.atomic.AtomicInteger;

public class Main {
    private static void displayAccountLogs(List<LogRecord> logs){
        for(LogRecord record : logs){
            System.out.println("- from "+ record.getSourceAccountID() +
                    " to " + record.getDestinationAccountID() + " sum " + record.getSum());
        }
    }
    public static void main(String[] args) throws InterruptedException {
        List<BankAccount> accounts = new ArrayList<>();
        accounts.add(new BankAccount(0, 1000));
        accounts.add(new BankAccount(1, 2000));
        accounts.add(new BankAccount(2, 1500));
        accounts.add(new BankAccount(3, 3000));

        Bank bank = new Bank(new AtomicInteger(0), accounts);

        Thread t0 = new Thread(() -> bank.transferSum(0, 1, 500));
        Thread t1 = new Thread(() -> bank.transferSum(1, 2, 1000));
        // insufficient funds expected:
        Thread t2 = new Thread(() -> bank.transferSum(2, 0, 20000));
        Thread t3 = new Thread(() -> bank.transferSum(2, 3, 100));

        t0.start();
        t1.start();
        t2.start();
        t3.start();

        t0.join();
        t1.join();
        t2.join();
        t3.join();

        // Perform a consistency check after the operations
        boolean isConsistent = bank.consistencyCheck();
        if (isConsistent) {
            System.out.println("Final consistency check passed.");
        } else {
            System.out.println("Final consistency check failed.");
        }

        for (BankAccount account : accounts) {
            System.out.println("For account " + account.getId() + " the log records are: ");
            displayAccountLogs(account.getLogs());
            System.out.println("Initial sum: " + account.getInitialBalance()+ " Current sum: " + account.getBalance() + "\n");
        }
    }
}