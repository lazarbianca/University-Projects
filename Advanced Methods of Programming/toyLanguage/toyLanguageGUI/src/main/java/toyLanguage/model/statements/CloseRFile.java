package toyLanguage.model.statements;

import toyLanguage.model.exceptions.ADTException;
import toyLanguage.model.exceptions.ExpException;
import toyLanguage.model.exceptions.MyException;
import toyLanguage.model.exceptions.StmtException;
import toyLanguage.model.expressions.Exp;
import toyLanguage.model.programState.IDictionary;
import toyLanguage.model.programState.PrgState;
import toyLanguage.model.types.StringType;
import toyLanguage.model.types.Type;
import toyLanguage.model.values.StringValue;
import toyLanguage.model.values.Value;

import java.io.BufferedReader;
import java.io.IOException;

public class CloseRFile implements IStmt{
    Exp exp;

    public CloseRFile(Exp exp) {
        this.exp = exp;
    }

    @Override
    public PrgState execute(PrgState state) throws StmtException, IOException, ADTException, ExpException {
        IDictionary<String, Value> symTable = state.getSymTable();
        IDictionary<StringValue, BufferedReader> fileTable = state.getFileTable();
        Value v = exp.eval(symTable, state.getHeap());
        if(v.getType().equals(new StringType())){
            StringValue strValue = (StringValue) v;
            if(fileTable.isDefined(strValue))
            {
                BufferedReader fd = fileTable.lookup(strValue);
                //try
                fd.close();
                // catch(IOException e) throw new FileException("Failed to close the file " + stringValue);
                fileTable.remove(strValue);
            }
            else throw new StmtException("The file name: "+strValue+", is not defined in fileTable");
        }
        else throw new StmtException("The given expression: "+exp.toString()+", is not a String");
        return null;
    }

    @Override
    public String toString() {
        return "closeFile " + this.exp.toString();
    }

    @Override
    public IStmt deepcopy() {
        return new CloseRFile(exp.deepcopy());
    }

    @Override
    public IDictionary<String, Type> typeCheck(IDictionary<String, Type> typeEnv) throws StmtException, ExpException, ADTException {
        Type typeExp = exp.typecheck(typeEnv);
        if(typeExp.equals(new StringType())){
            return typeEnv;
        }
        else throw new StmtException("CLOSE R FILE Stmt: the expression is not a STRING");
    }
}
