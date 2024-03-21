package toyLanguage.model.expressions;

import toyLanguage.model.exceptions.ADTException;
import toyLanguage.model.exceptions.ExpException;
import toyLanguage.model.exceptions.MyException;
import toyLanguage.model.programState.IDictionary;
import toyLanguage.model.programState.IHeap;
import toyLanguage.model.types.IntType;
import toyLanguage.model.types.Type;
import toyLanguage.model.values.BoolValue;
import toyLanguage.model.values.IntValue;
import toyLanguage.model.values.Value;

public class RelationalExp implements Exp{
    private Exp e1;
    private Exp e2;
    private String operation;

    public RelationalExp(Exp e1, Exp e2, String operation) {
        this.e1 = e1;
        this.e2 = e2;
        this.operation = operation;
    }

    @Override
    public Value eval(IDictionary<String, Value> tbl, IHeap<Value> heap) throws ExpException, ADTException {
        Value val1, val2;
        val1 = this.e1.eval(tbl, heap);
        if (val1.getType().equals(new IntType())) {
            val2 = this.e2.eval(tbl, heap);
            if (val2.getType().equals(new IntType())) {
                IntValue intVal1 = (IntValue) val1;
                IntValue intVal2 = (IntValue) val2;
                int num1, num2;
                num1 = intVal1.getVal();
                num2 = intVal2.getVal();
                switch (this.operation) {
                    case ">": {
                        return new BoolValue(num1 > num2);
                    }
                    case ">=": {
                        return new BoolValue(num1 >= num2);
                    }
                    case "==": {
                        return new BoolValue(num1 == num2);
                    }
                    case "<=": {
                        return new BoolValue(num1 <= num2);
                    }
                    case "<":
                    {
                        return new BoolValue(num1 < num2);
                    }
                    case "!=":{
                        return new BoolValue(num1 != num2);
                    }
                    default:{
                        throw new ExpException("The given operation is invalid (relational)");
                    }
                }
            }
            else
                throw new ExpException("Second operand is not an integer");
        }
        else
            throw new ExpException("First operand is not an integer");
    }

    @Override
    public Exp deepcopy() {
        return new RelationalExp(this.e1.deepcopy(), this.e2.deepcopy(), this.operation);
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
    public String toString() {
        return this.e1.toString() + " " + this.operation + " " + this.e2.toString();
    }
}
