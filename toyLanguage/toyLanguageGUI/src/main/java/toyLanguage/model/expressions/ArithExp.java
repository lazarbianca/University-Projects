package toyLanguage.model.expressions;

import toyLanguage.model.exceptions.ADTException;
import toyLanguage.model.exceptions.ExpException;
import toyLanguage.model.exceptions.MyException;
import toyLanguage.model.programState.IDictionary;
import toyLanguage.model.programState.IHeap;
import toyLanguage.model.statements.IStmt;
import toyLanguage.model.types.IntType;
import toyLanguage.model.types.Type;
import toyLanguage.model.values.IntValue;
import toyLanguage.model.values.Value;

import java.net.MalformedURLException;

public class ArithExp implements Exp{
    Exp e1;
    Exp e2;
    char operation; // "+", "-", "*", "/"

    public ArithExp(char operation, Exp e1, Exp e2) {
        this.e1 = e1;
        this.e2 = e2;
        this.operation = operation;
    }

    @Override
    public Value eval(IDictionary<String, Value> tbl, IHeap<Value> heap) throws ExpException, ADTException {
        Value v1, v2;
        v1=e1.eval(tbl, heap);
        if(v1.getType().equals(new IntType())){
            v2 = e2.eval(tbl, heap);
            if(v2.getType().equals(new IntType())){
                IntValue i1 = (IntValue) v1;
                IntValue i2 = (IntValue) v2;
                int n1,n2;
                n1 = i1.getVal();
                n2 = i2.getVal();
                if(operation == '+'){
                   return new IntValue(n1+n2);
                }
                if(operation == '-'){
                    return new IntValue(n1-n2);
                }
                if(operation=='*'){
                    return new IntValue(n1*n2);
                }
                if(operation == '/'){
                    if(n2==0) throw new ExpException("division by zero");
                    else return new IntValue(n1/n2);
                }
                throw new ExpException("unidentified operand");
            }
            else{
                throw new ExpException("second operand is not an integer");
            }
        }
        else throw new ExpException("first operand is not an integer");
    }

    @Override
    public Exp deepcopy() {
        return new ArithExp(operation, e1.deepcopy(), e2.deepcopy());
        //op - primitive types! Otherwise, if String or so on, new String(op)
    }

    @Override
    public Type typecheck(IDictionary<String, Type> typeEnv) throws ExpException, ADTException {
        Type type1, type2;
        type1 = e1.typecheck(typeEnv);
        type2 = e2.typecheck(typeEnv);
        if(type1.equals(new IntType())){
            if(type2.equals(new IntType())){
                return new IntType();
            }
            else throw new ExpException("second operand is not an integer");
        }
        else throw new ExpException("first operand is not an integer");
    }

    @Override
    public String toString(){
        return e1.toString()+operation+e2.toString();
    }
}
