package toyLanguage.model.types;

import toyLanguage.model.values.IntValue;
import toyLanguage.model.values.StringValue;
import toyLanguage.model.values.Value;

public class StringType implements Type{
    @Override
    public boolean equals(Object another){
        if(another instanceof StringType)
            return true;
        else
            return false;
    }
    @Override
    public String toString(){
        return "string ";
    }
    @Override
    public Type deepcopy() {
        return new StringType();
    }
    @Override
    public Value getDefault() {
        return new StringValue("");
    }
}
