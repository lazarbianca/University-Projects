package toyLanguage.repository;

import toyLanguage.model.exceptions.FileException;
import toyLanguage.model.exceptions.MyException;
import toyLanguage.model.programState.PrgState;

import java.io.BufferedWriter;
import java.io.FileWriter;
import java.io.IOException;
import java.io.PrintWriter;
import java.util.LinkedList;
import java.util.List;

public class Repository implements IRepository {
    List<PrgState> repo;
    String logFilePath = "E:\\UNI\\AN2\\MAP\\toyLangGUI\\toyLanguageGUI\\src\\main\\java\\toyLanguage\\logFile.txt";
    // "C:\\Users\\ACASA\\IdeaProjects\\lab3_A2\\logFile.txt";  this is the actual file that
    // gets modified with the program states
    // it is not set for use here, but in the Interpreter: IRepository r10 = new Repository("logFile.txt");
    boolean firstWrite;

    public Repository(String logFilePath) {
        this.repo = new LinkedList<PrgState>();
        this.logFilePath = logFilePath;
        firstWrite = true;
    }

    @Override
    public void add(PrgState e) {
        repo.add(e);
    }

    @Override
    public void logPrgStateExec(PrgState programState) throws FileException {
        PrintWriter logFile;
        try {
            if (firstWrite) {
                logFile = new PrintWriter(new BufferedWriter(new FileWriter
                        (logFilePath, false))); // append: true
                this.firstWrite = false;
            } else {
                logFile = new PrintWriter(new BufferedWriter(new FileWriter
                        (logFilePath, true)));
            }
        } catch (IOException e) {
            throw new FileException("\" (FILE) IO exception: the file cannot be opened, created, or it doesn't exist\"");
        }
        logFile.write(programState.toString());
        logFile.flush();
        logFile.close();
    }

    @Override
    public List<PrgState> getPrgList() {
        return repo;
    }

    @Override
    public void setPrgState(List<PrgState> newList) {
        repo.clear();
        repo.addAll(newList);
    }

    // removed: we are no longer using it
//    @Override
//    public PrgState getCrtPrg() {
//        return repo.get(0);
//    }
    @Override
    public PrgState getProgramStateById(int id) throws MyException {
        for (PrgState programState: repo) {
            if (programState.getId() == id) {
                return programState;
            }
        }
        throw new MyException("Repository error: No prg state with ID " + id + " in the repository");
    }

    @Override
    public String toString() {
        return "Repository{" +
                "repo=" + repo +
                '}';
    }
}
