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
import java.io.FileNotFoundException;
import java.io.FileReader;

public class OpenRFile implements IStmt{
    Exp exp;

    public OpenRFile(Exp e) {
        exp = e;
    }

    @Override
    public PrgState execute(PrgState state) throws StmtException, FileNotFoundException, ExpException, ADTException {
        IDictionary<String, Value> symTable = state.getSymTable();
        IDictionary<StringValue, BufferedReader> fileTable = state.getFileTable();
        Value result = exp.eval(symTable, state.getHeap());
        if(result.getType().equals(new StringType())){     //StringType??? StringValue?
            StringValue v = (StringValue) result; //result instanceof StringValue
            String sVal = v.getVal();
            if(fileTable.isDefined(v))
                throw new StmtException("String already exists in file table");
            BufferedReader fd = new BufferedReader(new FileReader("E:\\UNI\\AN2\\MAP\\toyLangGUI\\toyLanguageGUI\\src\\main\\java\\toyLanguage\\test.in"));
            // here is the path of the openRFile
            fileTable.put(v,fd);
        }
        else throw new StmtException("the evaluation of the exp is not a StringType! \n");
        return null;
    }
    @Override
    public String toString() {
        return "openFile " + this.exp.toString();
    }

    @Override
    public IStmt deepcopy() {
        return new OpenRFile(this.exp.deepcopy());
    }

    @Override
    public IDictionary<String, Type> typeCheck(IDictionary<String, Type> typeEnv) throws StmtException, ExpException, ADTException {
        Type typeExp = exp.typecheck(typeEnv);
        if(typeExp.equals(new StringType())){
            return typeEnv;
        }
        else throw new StmtException("OPEN R FILE Stmt: the expression is not a STRING");
    }
}
