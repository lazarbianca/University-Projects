package toyLanguage.model.types;

import toyLanguage.model.statements.IStmt;
import toyLanguage.model.values.Value;

public interface Type {
    public Type deepcopy();
    Value getDefault();
}
