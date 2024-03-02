package toyLanguage.model.expressions;

import toyLanguage.model.exceptions.ADTException;
import toyLanguage.model.exceptions.ExpException;
import toyLanguage.model.exceptions.MyException;
import toyLanguage.model.programState.IDictionary;
import toyLanguage.model.programState.IHeap;
import toyLanguage.model.types.Type;
import toyLanguage.model.values.Value;

public class VarExp implements Exp{
    String id;

    public VarExp(String v) {
        id=v;
    }

    @Override
    public Value eval(IDictionary<String, Value> tbl, IHeap<Value> heap) throws ExpException, ADTException {
        return tbl.lookup(id);
    }

    @Override
    public Exp deepcopy() {
        return new VarExp(new String(id));
    }

    @Override
    public Type typecheck(IDictionary<String, Type> typeEnv) throws ExpException, ADTException {
        return typeEnv.lookup(id);
    }

    @Override
    public String toString(){
        return id;
    }
}
