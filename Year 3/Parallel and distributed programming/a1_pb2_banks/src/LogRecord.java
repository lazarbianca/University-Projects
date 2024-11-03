public class LogRecord {
    private final int serialNumber;  // make all final?
    private final int sourceAccountID;

    private final int destinationAccountID;

    private final int sum;
    public LogRecord(int serialNumber, int sourceAccountID, int destinationAccountID, int sum) {
        this.serialNumber = serialNumber;
        this.sourceAccountID = sourceAccountID;
        this.destinationAccountID = destinationAccountID;
        this.sum = sum;
    }

    public int getSerialNumber() {
        return serialNumber;
    }

    public int getSourceAccountID() {
        return sourceAccountID;
    }

    public int getDestinationAccountID() {
        return destinationAccountID;
    }

    public int getSum() {
        return sum;
    }

    @Override
    public String toString() {
        return "LogRecord{" +
                "serialNumber=" + serialNumber +
                ", sourceAccountID=" + sourceAccountID +
                ", destinationAccountID=" + destinationAccountID +
                ", sum=" + sum +
                '}';
    }
}