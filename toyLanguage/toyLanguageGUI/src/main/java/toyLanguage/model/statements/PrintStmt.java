package toyLanguage.model.statements;

import toyLanguage.model.exceptions.ADTException;
import toyLanguage.model.exceptions.ExpException;
import toyLanguage.model.exceptions.MyException;
import toyLanguage.model.exceptions.StmtException;
import toyLanguage.model.expressions.Exp;
import toyLanguage.model.expressions.VarExp;
import toyLanguage.model.programState.IDictionary;
import toyLanguage.model.programState.PrgState;
import toyLanguage.model.types.Type;

public class PrintStmt implements IStmt{
    Exp exp;

    public PrintStmt(Exp v) {
        exp = v;
    }

    @Override
    public String toString(){
        return "print(" + exp.toString() + ")";
    }
    @Override
    public PrgState execute(PrgState state) throws StmtException, ExpException, ADTException {
        //System.out.println(exp.eval(state.getSymTable()).toString());

        state.getOut().add(exp.eval(state.getSymTable(), state.getHeap()));
        return null;
    }

    @Override
    public IStmt deepcopy() {
        return new PrintStmt(exp.deepcopy());
    }

    @Override
    public IDictionary<String, Type> typeCheck(IDictionary<String, Type> typeEnv) throws StmtException, ExpException, ADTException {
        exp.typecheck(typeEnv);
        return typeEnv;
    }

//    @Override
//    public Object clone() throws CloneNotSupportedException {
//        return super.clone();
//    }
}
