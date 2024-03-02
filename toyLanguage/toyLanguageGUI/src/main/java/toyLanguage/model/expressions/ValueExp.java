package toyLanguage.model.expressions;

import toyLanguage.model.exceptions.ExpException;
import toyLanguage.model.exceptions.MyException;
import toyLanguage.model.programState.IDictionary;
import toyLanguage.model.programState.IHeap;
import toyLanguage.model.statements.IStmt;
import toyLanguage.model.types.Type;
import toyLanguage.model.values.IntValue;
import toyLanguage.model.values.Value;

public class ValueExp implements Exp{
    Value e;

    public ValueExp(Value intValue) {
        e = intValue;
    }

    @Override
    public Value eval(IDictionary<String, Value> tbl, IHeap<Value> heap) throws ExpException {
        return e;
    }

    @Override
    public Exp deepcopy() {
        return new ValueExp(e.deepcopy());
    }

    @Override
    public Type typecheck(IDictionary<String, Type> typeEnv) throws ExpException {
        return e.getType();
    }

    @Override
    public String toString(){
        return e.toString();
    }
}
