package toyLanguage.model.statements;

import toyLanguage.model.exceptions.ADTException;
import toyLanguage.model.exceptions.ExpException;
import toyLanguage.model.exceptions.MyException;
import toyLanguage.model.exceptions.StmtException;
import toyLanguage.model.programState.IDictionary;
import toyLanguage.model.programState.PrgState;
import toyLanguage.model.types.Type;

import java.io.FileNotFoundException;
import java.io.IOException;

public interface IStmt {
    PrgState execute(PrgState state) throws StmtException, IOException, ExpException, ADTException;
    // execution method for a statement
    //public Object clone() throws CloneNotSupportedException;
    public IStmt deepcopy();
    IDictionary<String, Type> typeCheck(IDictionary<String, Type> typeEnv) throws StmtException, ADTException, ExpException;
}
