package toyLanguage.model.types;

import toyLanguage.model.values.BoolValue;
import toyLanguage.model.values.Value;

public class BoolType implements Type{
    @Override
    public boolean equals(Object another){
        if(another instanceof BoolType)
            return true;
        else
            return false;
    }
    @Override
    public String toString(){
        return "boolean";
    }

    @Override
    public Type deepcopy() {
        return new BoolType();
    }

    @Override
    public Value getDefault() {
        return new BoolValue(false);
    }
}
