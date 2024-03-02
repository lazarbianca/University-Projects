package toyLanguage.model.statements;

import toyLanguage.model.exceptions.MyException;
import toyLanguage.model.exceptions.StmtException;
import toyLanguage.model.programState.IDictionary;
import toyLanguage.model.programState.MyDictionary;
import toyLanguage.model.programState.MyStack;
import toyLanguage.model.programState.PrgState;
import toyLanguage.model.types.Type;
import toyLanguage.model.values.Value;

import java.io.IOException;
import java.util.Map;
import java.util.stream.Collectors;

public class ForkStmt implements IStmt{
    private IStmt stmt;

    public ForkStmt(IStmt stmt) {
        this.stmt = stmt;
    }

    @Override
    public PrgState execute(PrgState state) throws StmtException, IOException {
        // heap, fileTable, Output are shared between all prgStates
        MyStack<IStmt> newExeStack = new MyStack<>();

        Map<String, Value> symTableContent = state.getSymTable().getContent(); // deepcopy
        MyDictionary<String, Value> newSymTable = new MyDictionary<>();
        newSymTable.setMap(symTableContent.entrySet().stream()
                .collect(Collectors.toMap(e -> e.getKey(), e -> e.getValue().deepcopy())));
        return new PrgState(newExeStack, newSymTable, state.getOut(), state.getFileTable(), state.getHeap(), stmt);
    }

    @Override
    public IStmt deepcopy() {
        return new ForkStmt(stmt.deepcopy());
    }

    @Override
    public IDictionary<String, Type> typeCheck(IDictionary<String, Type> typeEnv) throws StmtException {
        // there is nothing to check?
        return typeEnv;
    }

    @Override
    public String toString() {
        return "fork(" + stmt + ')';
    }
}
