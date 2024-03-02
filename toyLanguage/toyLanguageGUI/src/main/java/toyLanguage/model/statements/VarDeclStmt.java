package toyLanguage.model.statements;

import toyLanguage.model.exceptions.MyException;
import toyLanguage.model.exceptions.StmtException;
import toyLanguage.model.programState.IDictionary;
import toyLanguage.model.programState.IStack;
import toyLanguage.model.programState.PrgState;
import toyLanguage.model.types.IntType;
import toyLanguage.model.types.Type;
import toyLanguage.model.values.Value;

public class VarDeclStmt implements IStmt{
    String name;
    Type typ;

    public VarDeclStmt(String v, Type intType) {
        name = v;
        typ = intType;
    }

    @Override
    public PrgState execute(PrgState state) throws StmtException {
        IStack<IStmt> stack = state.getStack();
        IDictionary<String, Value> symTable = state.getSymTable();
        if(!symTable.isDefined(name)){
            symTable.put(name,typ.getDefault());
        }
        else
            throw new StmtException("variable "+ name+ " is already declared as type "+ typ.toString());
        return null;
    }

    @Override
    public IStmt deepcopy() {
        return new VarDeclStmt(name, typ.deepcopy());
    }

    @Override
    public IDictionary<String, Type> typeCheck(IDictionary<String, Type> typeEnv) throws StmtException {
        typeEnv.put(name, typ);
        return typeEnv;
    }

    @Override
    public String toString(){
        return typ.toString() + ' ' + name;
    }
}