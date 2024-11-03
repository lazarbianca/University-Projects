package toyLanguage.model.statements;

import toyLanguage.model.exceptions.ADTException;
import toyLanguage.model.exceptions.ExpException;
import toyLanguage.model.exceptions.MyException;
import toyLanguage.model.exceptions.StmtException;
import toyLanguage.model.expressions.Exp;
import toyLanguage.model.programState.IDictionary;
import toyLanguage.model.programState.IStack;
import toyLanguage.model.programState.MyDictionary;
import toyLanguage.model.programState.PrgState;
import toyLanguage.model.types.BoolType;
import toyLanguage.model.types.Type;
import toyLanguage.model.values.BoolValue;
import toyLanguage.model.values.Value;

import java.util.Map;
import java.util.stream.Collectors;

public class IfStmt implements IStmt{
    Exp exp;
    IStmt thenStmt;
    IStmt elseStmt;
    public IfStmt(Exp e, IStmt t, IStmt el) {
        exp = e;
        thenStmt = t;
        elseStmt = el;
    }
    @Override
    public PrgState execute(PrgState state) throws StmtException, ExpException, ADTException {
        IStack<IStmt> stack = state.getStack();
        IDictionary<String, Value> symTable = state.getSymTable();
        Value result = exp.eval(symTable, state.getHeap());
        if(result.getType().equals(new BoolType())){
            BoolValue b = (BoolValue) result; //result instanceof BoolValue
            boolean bVal = b.getVal();
            if(bVal == true)
                stack.push(thenStmt);
            else
                stack.push(elseStmt);
        }
        else throw new StmtException("the evaluation of the if condition is not a boolean! \n");
        return null;
    }

    @Override
    public String toString(){
        return "(IF ("+exp.toString()+") THEN ("+thenStmt.toString()+
                ") ELSE ("+elseStmt.toString()+") )";
    }

    /*@Override
    public Object clone() throws CloneNotSupportedException {
        return super.clone();
    }*/

    @Override
    public IStmt deepcopy() {
        return new IfStmt(exp.deepcopy(), thenStmt.deepcopy(), elseStmt.deepcopy());
    }

    @Override
    public IDictionary<String, Type> typeCheck(IDictionary<String, Type> typeEnv) throws StmtException, ExpException, ADTException {
        Type typeExp = exp.typecheck(typeEnv);
        if (typeExp.equals(new BoolType())) {
            //thenStmt.typeCheck(clone(typeEnv));
            // clone is protected; technically we shouldn't clone here (NOR IN FORK STMT)
            // as it needs to be independent of the Map data structure from IDictionary
            // TODO: ASK, should we create a clone in IDictionary/ MyDictionary?
            // TODO: make sure to check all stmts work with typechecker!
            Map<String, Type> typeEnvContent = typeEnv.getContent(); // clone typeEnv
            MyDictionary<String, Type> newTypeEnv = new MyDictionary<>();
            newTypeEnv.setMap(typeEnvContent.entrySet().stream()
                    .collect(Collectors.toMap(e -> e.getKey(), e -> e.getValue().deepcopy())));
            thenStmt.typeCheck(newTypeEnv);
            elseStmt.typeCheck(newTypeEnv);
            // TODO: do thenStmt and elseStmt need DIFFERENT CLONES? TEST. ASK!
            return typeEnv;
        }
        else throw new StmtException("The condition of IF is not of the type BOOL");
    }
}
