package toyLanguage.model.statements;

import toyLanguage.model.exceptions.ADTException;
import toyLanguage.model.exceptions.ExpException;
import toyLanguage.model.exceptions.MyException;
import toyLanguage.model.exceptions.StmtException;
import toyLanguage.model.expressions.Exp;
import toyLanguage.model.programState.IDictionary;
import toyLanguage.model.programState.IHeap;
import toyLanguage.model.programState.PrgState;
import toyLanguage.model.types.RefType;
import toyLanguage.model.types.Type;
import toyLanguage.model.values.RefValue;
import toyLanguage.model.values.Value;

import java.io.IOException;

public class WriteToHeap implements IStmt{
    private String varName;  //contains heap addr
    private Exp expression;  // new value to be stored in heap

    public WriteToHeap(String varName, Exp expression) {
        this.varName = varName;
        this.expression = expression;
    }

    @Override
    public PrgState execute(PrgState state) throws StmtException, IOException, ADTException, ExpException {
        IDictionary<String, Value> symTable = state.getSymTable();
        IHeap<Value> heap = state.getHeap();
        if(symTable.isDefined(varName))
        {
            Value varValue = symTable.lookup(varName);
            if(varValue.getType().equals(new RefType(null))){
                RefValue refValue = (RefValue) varValue;
                if(heap.isDefined(refValue.getAddress())){
                    Value expressionVal = expression.eval(symTable,heap);
                    if(expressionVal.getType().equals(refValue.getLocationType()))
                    {
                        heap.update(refValue.getAddress(), expressionVal);
                        return null;
                    }
                    else throw new StmtException("the type of the given expression(" + expression.toString() + ")" +
                            " does not match with the location type");
                }
                else throw new StmtException("the address associated with the given variable(" + varName + ")" +
                        " is no longer available in the heap");
            }
            else {
                throw new StmtException("the given variable: "+ varName+" is not a refType");
            }
        }
        else {
            throw new StmtException("the used variable "+varName+" was not declared before");
        }
    }

    @Override
    public IStmt deepcopy() {
        return new WriteToHeap(varName, expression.deepcopy());
    }

    @Override
    public IDictionary<String, Type> typeCheck(IDictionary<String, Type> typeEnv) throws StmtException, ADTException, ExpException {
        Type typeVar = typeEnv.lookup(varName);
        Type typeExp = expression.typecheck(typeEnv);
        if(typeVar.equals(new RefType(typeExp))){
            return typeEnv;
        }
        else throw new StmtException("WRITE TO HEAP Stmt: right hand side and left hand side have different types");
    }

    @Override
    public String toString() {
        return "writeToHeap(" + varName +
                ", " + expression.toString() +
                ')';
    }
}
