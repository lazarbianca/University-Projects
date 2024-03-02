package toyLanguage.model.statements;

import toyLanguage.model.exceptions.ADTException;
import toyLanguage.model.exceptions.ExpException;
import toyLanguage.model.exceptions.MyException;
import toyLanguage.model.exceptions.StmtException;
import toyLanguage.model.expressions.Exp;
import toyLanguage.model.programState.IDictionary;
import toyLanguage.model.programState.PrgState;
import toyLanguage.model.types.RefType;
import toyLanguage.model.types.Type;
import toyLanguage.model.values.RefValue;
import toyLanguage.model.values.Value;

import java.io.IOException;

public class New implements IStmt{
    private String varName;
    private Exp expression;

    public New(String varName, Exp expression) {
        this.varName = varName;
        this.expression = expression;
    }

    // new(varName, expression)
    @Override
    public PrgState execute(PrgState state) throws StmtException, IOException, ADTException, ExpException {
        IDictionary<String, Value> symTable = state.getSymTable();
        if(symTable.isDefined(varName)){
            //check varName value in symTable is of refType
            Value varValue = symTable.lookup(varName);
            if(varValue.getType().equals(new RefType(null)))
            {
                Value expValue = expression.eval(symTable, state.getHeap());
                RefValue refValue = (RefValue) varValue;
                if(expValue.getType().equals(refValue.getLocationType())){
                    int address = state.getHeap().put(expValue);
                    symTable.put(varName, new RefValue(address, refValue.getLocationType()));
                    return null;
                }
                else{
                    throw new StmtException("the type of the given variable does not match" +
                            " with the type of the expression");
                }
            }
            else {
                throw new StmtException("the given variable: "+ varName+" is not a refType");
            }
        }
        else{
            throw new StmtException("the used variable "+varName+" was not declared before");
        }
    }

    @Override
    public IStmt deepcopy() {
        return new New(varName, expression.deepcopy());
    }

    @Override
    public IDictionary<String, Type> typeCheck(IDictionary<String, Type> typeEnv) throws StmtException, ADTException, ExpException {
        Type typeVar = typeEnv.lookup(varName);
        Type typeExp = expression.typecheck(typeEnv);
        if(typeVar.equals(new RefType(typeExp))){
            return typeEnv;
        }
        else throw new StmtException("NEW Stmt: right hand side and left hand side have different types");
    }

    @Override
    public String toString() {
        return "New(" + varName + "," + expression.toString() + ')';
    }
}
