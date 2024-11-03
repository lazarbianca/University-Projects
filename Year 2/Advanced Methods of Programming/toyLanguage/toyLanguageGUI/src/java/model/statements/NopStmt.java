package toyLanguage.model.statements;

import toyLanguage.model.exceptions.MyException;
import toyLanguage.model.exceptions.StmtException;
import toyLanguage.model.programState.IDictionary;
import toyLanguage.model.programState.PrgState;
import toyLanguage.model.types.Type;

public class NopStmt implements IStmt{
    public NopStmt() {}

    @Override
    public PrgState execute(PrgState state) throws StmtException {
        return null;
    }

    @Override
    public IStmt deepcopy() {
        return new NopStmt();
    }

    @Override
    public IDictionary<String, Type> typeCheck(IDictionary<String, Type> typeEnv) throws StmtException {
        // nothing to check
        return typeEnv;
    }

    @Override
    public String toString(){
        return "nop";
   }
}
