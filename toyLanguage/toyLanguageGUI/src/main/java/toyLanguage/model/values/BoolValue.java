package toyLanguage.model.values;

import toyLanguage.model.types.BoolType;
import toyLanguage.model.types.Type;

import java.util.Objects;

public class BoolValue implements Value{
    boolean val;

    @Override
    public boolean equals(Object o) {
        if (this == o) return true;
        if (o == null || getClass() != o.getClass()) return false;
        BoolValue boolValue = (BoolValue) o;
        return val == boolValue.val;
    }

    public BoolValue(boolean v){
        val = v;
    }
    public boolean getVal(){
        return val;
    }
    @Override
    public String toString(){
        return " " + val;
    }
    @Override
    public Type getType() {
        return new BoolType();
    }

    @Override
    public Value deepcopy() {
        return new BoolValue(val);
    }
}
