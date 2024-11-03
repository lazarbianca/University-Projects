package toyLanguage.model.values;

import toyLanguage.model.statements.IStmt;
import toyLanguage.model.types.Type;

public interface Value {
    Type getType();
    public Value deepcopy();
}
