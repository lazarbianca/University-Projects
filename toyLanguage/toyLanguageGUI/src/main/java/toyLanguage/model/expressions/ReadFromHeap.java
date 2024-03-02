package toyLanguage.model.expressions;

import toyLanguage.model.exceptions.ADTException;
import toyLanguage.model.exceptions.ExpException;
import toyLanguage.model.exceptions.MyException;
import toyLanguage.model.programState.IDictionary;
import toyLanguage.model.programState.IHeap;
import toyLanguage.model.types.RefType;
import toyLanguage.model.types.Type;
import toyLanguage.model.values.RefValue;
import toyLanguage.model.values.Value;

//read from Heap
public class ReadFromHeap implements Exp{
    private Exp expression;

    public ReadFromHeap(Exp expression) {
        this.expression = expression;
    }

    @Override
    public Value eval(IDictionary<String, Value> tbl, IHeap<Value> heap) throws ExpException, ADTException {
        // must be eval to a refValue
        Value val = expression.eval(tbl, heap);
        if(val.getType().equals(new RefType(null))){
            RefValue refvalue = (RefValue) val;
            int address = refvalue.getAddress();
            if(heap.isDefined(address))
            {
                //get value in heap associated to that address
                return heap.lookup(address);
            }
            else throw new ExpException("the address of the given RefValue(" + this.expression.toString() + ")" +
                    " is not defined in the heap");
        }
        else throw new ExpException("expression" + expression.toString() + "is not of refType");
    }

    @Override
    public Exp deepcopy() {
        return new ReadFromHeap(expression.deepcopy());
    }

    @Override
    public Type typecheck(IDictionary<String, Type> typeEnv) throws ExpException, ADTException {
        Type type = expression.typecheck(typeEnv);
        if(type instanceof RefType){
            RefType refType = (RefType) type;
            return refType.getInner();
        }
        else throw new ExpException("the rH argument is not a Ref Type");
    }

    @Override
    public String toString() {
        return "readFromHeap(" + expression.toString() +
                ')';
    }
}
