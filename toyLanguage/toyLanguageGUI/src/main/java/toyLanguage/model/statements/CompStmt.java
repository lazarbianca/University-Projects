package toyLanguage.model.statements;

import toyLanguage.model.exceptions.ADTException;
import toyLanguage.model.exceptions.ExpException;
import toyLanguage.model.exceptions.MyException;
import toyLanguage.model.exceptions.StmtException;
import toyLanguage.model.programState.IDictionary;
import toyLanguage.model.programState.IStack;
import toyLanguage.model.programState.PrgState;
import toyLanguage.model.types.Type;

public class CompStmt implements IStmt{
    private final IStmt first;
    private final IStmt second;

    public CompStmt(IStmt s1, IStmt s2) {
        first = s1;
        second = s2;
    }

    @Override
    public String toString(){
        return "("+first.toString()+";"+second.toString()+")";
    }
    @Override
    public PrgState execute(PrgState state) throws StmtException {
        IStack<IStmt> stack = state.getStack();
        stack.push(second);
        stack.push(first);
        return null;
    }

    @Override
    public IStmt deepcopy(){
        // IStmt deepFirst = first.deepcopy();
        // IStmt deepSecond = second.deepcopy();
        return new CompStmt(first.deepcopy(), second.deepcopy());
    }

    @Override
    public IDictionary<String, Type> typeCheck(IDictionary<String, Type> typeEnv) throws StmtException, ExpException, ADTException {
        // MyIDictionary<String,Type> typEnv1 = first.typecheck(typeEnv);
        // MyIDictionary<String,Type> typEnv2 = second.typecheck(typEnv1);
        // return typEnv2;
        return second.typeCheck(first.typeCheck(typeEnv));
    }
}
// You cannot override a method (like toString) which is public, and reduce its
// visibility (make it package-specific)