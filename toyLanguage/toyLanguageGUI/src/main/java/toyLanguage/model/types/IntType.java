package toyLanguage.model.types;

import toyLanguage.model.values.IntValue;
import toyLanguage.model.values.Value;

public class IntType implements Type{
    @Override
    public boolean equals(Object another){
        if(another instanceof IntType)
            return true;
        else
            return false;
    }
    @Override
    public String toString(){
        return "int";
    }

    @Override
    public Type deepcopy() {
        return new IntType();
    }

    @Override
    public Value getDefault() {
        return new IntValue(0);
    }
}
