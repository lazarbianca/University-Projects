package toyLanguage.model.expressions;

import toyLanguage.model.exceptions.ADTException;
import toyLanguage.model.exceptions.ExpException;
import toyLanguage.model.exceptions.MyException;
import toyLanguage.model.programState.IDictionary;
import toyLanguage.model.programState.IHeap;
import toyLanguage.model.statements.IStmt;
import toyLanguage.model.types.BoolType;
import toyLanguage.model.types.Type;
import toyLanguage.model.values.BoolValue;
import toyLanguage.model.values.Value;

public class LogicExp implements Exp{
    Exp e1;
    Exp e2;
    String op;

    public LogicExp(Exp e1, Exp e2, String op) {
        this.e1 = e1;
        this.e2 = e2;
        this.op = op;
    }

    @Override
    public Value eval(IDictionary<String, Value> tbl, IHeap<Value> heap) throws ExpException, ADTException {
        Value v1,v2;
        v1=e1.eval(tbl, heap);
        if(v1.getType().equals(new BoolType())){
            v2=e2.eval(tbl, heap);
            if(v2.getType().equals(new BoolType())){
                BoolValue b1 = (BoolValue) v1;
                BoolValue b2=(BoolValue) v2;
                boolean b1Val, b2Val;
                b1Val = b1.getVal();
                b2Val = b2.getVal();
                if(op == "&&"){
                    return new BoolValue(b1Val && b2Val);
                }
                if(op=="||"){
                    return new BoolValue(b1Val || b2Val);
                }
                throw new ExpException("unidentified operand");
            }
            else{
                throw new ExpException("second operand is not a boolean");
            }
        }
        else throw new ExpException("first operand is not a boolean");
    }

    @Override
    public Exp deepcopy() {
        return new LogicExp(e1.deepcopy(),e2.deepcopy(), op);
    }

    @Override
    public Type typecheck(IDictionary<String, Type> typeEnv) throws ExpException, ADTException {
        Type type1, type2;
        type1 = e1.typecheck(typeEnv);
        type2 = e2.typecheck(typeEnv);
        if(type1.equals(new BoolType()))
        {
            if(type2.equals(new BoolType()))
                return new BoolType();
            else throw new ExpException("second operand is not a boolean");
        }
        else throw new ExpException("first operand is not a boolean");
    }

    @Override
    public String toString(){
        return e1.toString()+op+e2.toString();
    }
}
