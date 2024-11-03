package toyLanguage.model.values;

import toyLanguage.model.types.RefType;
import toyLanguage.model.types.Type;

import java.util.Objects;

public class RefValue implements Value{
    int address;
    Type locationType;

    @Override
    public boolean equals(Object o) {
        if (this == o) return true;
        if (o == null || getClass() != o.getClass()) return false;
        RefValue refValue = (RefValue) o;
        return address == refValue.address && Objects.equals(locationType, refValue.locationType);
    }

//    @Override
//    public int hashCode() {
//        return Objects.hash(address, locationType);
//    }

    public RefValue(int address, Type locationType) {
        this.address = address;
        this.locationType = locationType;
    }
    public int getAddress() {
        return address;
    }
    public Type getLocationType(){return locationType;}

    @Override
    public Type getType() {
        return new RefType(locationType);
    }

    @Override
    public Value deepcopy() {
        return new RefValue(address,locationType);
    }

    @Override
    public String toString() {
        return "(" + address +
                "," + locationType + ')';
    }
}
