package toyLanguage.model.types;

import toyLanguage.model.values.RefValue;
import toyLanguage.model.values.Value;

import java.sql.Ref;

public class RefType implements Type{
    Type inner;

    public RefType(Type inner) {
        this.inner = inner;
    }

    public Type getInner() {
        return inner;
    }

    public boolean equals(Object another){
        if(another instanceof RefType) {
            RefType anotherRef = (RefType) another;
            if(anotherRef.getInner()==null)
                return true;
            else
                return inner.equals(anotherRef.getInner());
        }
        else return false;
    }

    @Override
    public String toString(){
        if(inner==null)
            return "null";
        return "Ref("+inner.toString()+")";
    }
    @Override
    public Type deepcopy() {
        return new RefType(inner.deepcopy());
    }

    @Override
    public Value getDefault() {
        return new RefValue(0,inner);
    }
}
