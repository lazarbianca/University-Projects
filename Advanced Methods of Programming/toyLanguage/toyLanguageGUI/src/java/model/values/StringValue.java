package toyLanguage.model.values;

import toyLanguage.model.types.StringType;
import toyLanguage.model.types.Type;

import java.util.Objects;

public class StringValue implements Value{
    String val;
    @Override
    public boolean equals(Object o) {
        if (this == o) return true;
        if (o == null || getClass() != o.getClass()) return false;
        StringValue stringValue = (StringValue) o;
        return Objects.equals(val, stringValue.val);
    }
    public StringValue(String val) {
        this.val = val;
    }
    public String getVal(){
        return val;
    }
    @Override
    public Type getType() {
        return new StringType();
    }

    @Override
    public String toString() {
        return " " + val;
    }

    @Override
    public Value deepcopy() {
        return new StringValue(val);
    }
}
