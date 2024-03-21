package toyLanguage.model.statements;

import toyLanguage.model.exceptions.ADTException;
import toyLanguage.model.exceptions.ExpException;
import toyLanguage.model.exceptions.MyException;
import toyLanguage.model.exceptions.StmtException;
import toyLanguage.model.expressions.Exp;
import toyLanguage.model.programState.IDictionary;
import toyLanguage.model.programState.IStack;
import toyLanguage.model.programState.PrgState;
import toyLanguage.model.values.Value;
import toyLanguage.model.types.Type;

public class AssignStmt implements IStmt{
    private final String id;
    private final Exp exp;

    public AssignStmt(String v, Exp valueExp) {
        id = v;
        exp = valueExp;
    }

    @Override
    public PrgState execute(PrgState state) throws StmtException, ExpException, ADTException {
        // PrgState copy = state.deepcopy();
        IStack<IStmt> stack = state.getStack();
        IDictionary<String, Value> symTable = state.getSymTable();

        if(symTable.isDefined(id)){
            Value val = exp.eval(symTable,state.getHeap());
            Type typeId = (symTable.lookup(id)).getType();
            if(val.getType().equals(typeId)){
                symTable.update(id, val);
            }
            else{
                throw new StmtException("declared type of variable: "+ id+" and type" +
                        " of the assigned expression do not match");
            }
        }
        else{
            throw new StmtException("the used variable "+id+" was not declared before");
        }
        return null;
    }
    @Override
    public String toString(){
        return id+" ="+exp.toString();
    }

    /*@Override
    public Object clone() throws CloneNotSupportedException {
        return super.clone();
    }*/

    @Override
    public IStmt deepcopy(){
        return new AssignStmt(new String(id), exp.deepcopy());
    }

    @Override
    public IDictionary<String, Type> typeCheck(IDictionary<String, Type> typeEnv) throws StmtException, ADTException, ExpException {
        Type typeVar = typeEnv.lookup(id);
        Type typeExp = exp.typecheck(typeEnv);
        if(typeVar.equals(typeExp)){
            return typeEnv;
        }
        else throw new StmtException("ASSIGNMENT: right hand side and left hand side have different types");
    }

}
