package toyLanguage.model.values;

import toyLanguage.model.types.IntType;
import toyLanguage.model.types.Type;

public class IntValue implements Value{
    int val;
    @Override
    public boolean equals(Object o) {
        if (this == o) return true;
        if (o == null || getClass() != o.getClass()) return false;
        IntValue intValue = (IntValue) o;
        return val == intValue.val;
    }
    public IntValue(int v){
        val = v;
    }
    public int getVal(){
        return val;
    }
    @Override
    public String toString(){
        return " " + val;
    }
    @Override
    public Type getType() {
        return new IntType();
    }

    @Override
    public Value deepcopy() {
        return new IntValue(val);
    }
}