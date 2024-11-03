import java.util.List;
import java.util.concurrent.atomic.AtomicInteger;

public class Bank {
    private final AtomicInteger serialNumberGenerator;
    private final List<BankAccount> accounts;

    public Bank(AtomicInteger serialNumberGenerator, List<BankAccount> accounts) {
        this.serialNumberGenerator = serialNumberGenerator;
        this.accounts = accounts;
    }

    public List<BankAccount> getAccounts() {
        return accounts;
    }
protected void transferSum(int sourceAccountID, int destinationAccountID, int sumToTransfer){
    System.out.println("Transfer started...");
    BankAccount sourceAccount = accounts.get(sourceAccountID);
    BankAccount destinationAccount = accounts.get(destinationAccountID);

    BankAccount firstLock, secondLock;
    // Ensure a consistent locking order by comparing account IDs
    if (sourceAccountID < destinationAccountID) {
        firstLock = sourceAccount;
        secondLock = destinationAccount;
    } else {
        firstLock = destinationAccount;
        secondLock = sourceAccount;
    }

    firstLock.getLock().lock();
    secondLock.getLock().lock();
    try {
        // Perform transfer only if source has enough balance
        if (sourceAccount.getBalance() < sumToTransfer) {
            System.out.println("Not enough funds in account: " + sourceAccountID + " for transfer of: " + sumToTransfer);
            return;
        }
        System.out.println("from "+ sourceAccountID + " to " + destinationAccountID + " sum "+ sumToTransfer);
        // Deduct from source and add to destination
        sourceAccount.transfer(-sumToTransfer);
        destinationAccount.transfer(sumToTransfer);

        // Log the transfer in both accounts
        int serialNumber = serialNumberGenerator.getAndIncrement();
        LogRecord record = new LogRecord(serialNumber, sourceAccountID, destinationAccountID, sumToTransfer);
        addLogToAccount(sourceAccount, record);
        addLogToAccount(destinationAccount, record);
    } finally {
        secondLock.getLock().unlock();
        firstLock.getLock().unlock();
        System.out.println("Unlocked");
    }
}

    private void addLogToAccount(BankAccount account, LogRecord record){
        account.getLock().lock();
        try{
            account.addLog(record);
        }
        finally {
            account.getLock().unlock();
        }
    }
    protected boolean consistencyCheck(){
        // amount in each account corresponds to logged operations
        // all operations appear in both source and dest accounts
        for (BankAccount account : accounts){
            int computedBalance = account.getInitialBalance();
            for(LogRecord log: account.getLogs()){
                if(log.getSourceAccountID() == account.getId()){
                    computedBalance -= log.getSum();
                } else if (log.getDestinationAccountID() == account.getId()) {
                    computedBalance += log.getSum();
                }
            }

            if(computedBalance != account.getBalance()) {
                System.out.println("Consistency check failed for account: " + account.getId());
                return false;
            }
        }
        System.out.println("Consistency check passed.");
        return true;
    }
}