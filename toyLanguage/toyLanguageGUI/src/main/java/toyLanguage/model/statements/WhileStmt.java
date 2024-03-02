package toyLanguage.model.statements;

import toyLanguage.model.exceptions.ADTException;
import toyLanguage.model.exceptions.ExpException;
import toyLanguage.model.exceptions.MyException;
import toyLanguage.model.exceptions.StmtException;
import toyLanguage.model.expressions.Exp;
import toyLanguage.model.programState.IDictionary;
import toyLanguage.model.programState.MyDictionary;
import toyLanguage.model.programState.PrgState;
import toyLanguage.model.types.BoolType;
import toyLanguage.model.types.IntType;
import toyLanguage.model.types.Type;
import toyLanguage.model.values.BoolValue;
import toyLanguage.model.values.Value;

import java.io.IOException;
import java.util.Map;
import java.util.stream.Collectors;

public class WhileStmt implements IStmt{
    private Exp expression;
    private IStmt stmt;

    public WhileStmt(Exp expression, IStmt stmt) {
        this.expression = expression;
        this.stmt = stmt;
    }

    @Override
    public PrgState execute(PrgState state) throws StmtException, IOException, ExpException, ADTException {
        Value condition = this.expression.eval(state.getSymTable(), state.getHeap());
        if (!condition.getType().equals(new BoolType())) {
            throw new StmtException("the given while conditional expression(" + this.expression.toString() + ") " +
                    "is not a boolean.");
        }
        BoolValue boolCondition = (BoolValue) condition;
        if (boolCondition.getVal()) {
            state.getExeStack().push(this);
            state.getExeStack().push(this.stmt);
        }
        return null;
    }

    @Override
    public IStmt deepcopy() {
        return new WhileStmt(expression.deepcopy(),stmt.deepcopy());
    }

    @Override
    public IDictionary<String, Type> typeCheck(IDictionary<String, Type> typeEnv) throws StmtException, ExpException, ADTException {
        Type typeExp = expression.typecheck(typeEnv);
        if(typeExp.equals(new IntType()))   // TODO: understand, why is this INT TYPE and not BOOL? what about IF STMT?
        {
            Map<String, Type> typeEnvContent = typeEnv.getContent(); // clone typeEnv
            MyDictionary<String, Type> newTypeEnv = new MyDictionary<>();
            newTypeEnv.setMap(typeEnvContent.entrySet().stream()
                    .collect(Collectors.toMap(e -> e.getKey(), e -> e.getValue().deepcopy())));
            stmt.typeCheck(newTypeEnv);
            return typeEnv;
        }
        else throw new StmtException("The condition of the WHILE is not of the type BOOL");
    }

    @Override
    public String toString() {
        return "While (" + this.expression.toString() + ") { " + this.stmt.toString() + " }";
    }
}
