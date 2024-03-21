package toyLanguage.model.expressions;

import toyLanguage.model.exceptions.ADTException;
import toyLanguage.model.exceptions.ExpException;
import toyLanguage.model.exceptions.MyException;
import toyLanguage.model.programState.IDictionary;
import toyLanguage.model.programState.IHeap;
import toyLanguage.model.statements.IStmt;
import toyLanguage.model.types.Type;
import toyLanguage.model.values.Value;

public interface Exp {
    Value eval(IDictionary<String,Value> tbl, IHeap<Value> heap) throws ExpException, ADTException;
    public Exp deepcopy();
    Type typecheck(IDictionary<String, Type> typeEnv) throws ExpException, ADTException;
}
