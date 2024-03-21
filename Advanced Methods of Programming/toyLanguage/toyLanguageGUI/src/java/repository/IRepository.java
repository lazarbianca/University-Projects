package toyLanguage.repository;

import toyLanguage.model.exceptions.FileException;
import toyLanguage.model.exceptions.MyException;
import toyLanguage.model.programState.PrgState;

import java.io.File;
import java.io.IOException;
import java.util.List;

public interface IRepository {
    List<PrgState> getPrgList();
    void setPrgState(List<PrgState> newList);
    public void add(PrgState e);
    void logPrgStateExec(PrgState e) throws FileException;

    PrgState getProgramStateById(int t1) throws MyException;
}
