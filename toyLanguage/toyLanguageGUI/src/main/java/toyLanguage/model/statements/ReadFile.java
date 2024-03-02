package toyLanguage.model.statements;

import toyLanguage.model.exceptions.ADTException;
import toyLanguage.model.exceptions.ExpException;
import toyLanguage.model.exceptions.MyException;
import toyLanguage.model.exceptions.StmtException;
import toyLanguage.model.expressions.Exp;
import toyLanguage.model.programState.IDictionary;
import toyLanguage.model.programState.PrgState;
import toyLanguage.model.types.IntType;
import toyLanguage.model.types.RefType;
import toyLanguage.model.types.StringType;
import toyLanguage.model.types.Type;
import toyLanguage.model.values.IntValue;
import toyLanguage.model.values.StringValue;
import toyLanguage.model.values.Value;

import java.io.BufferedReader;
import java.io.IOException;

public class ReadFile implements IStmt{
    Exp exp;
    String varName;

    public ReadFile(Exp exp, String varName) {
        this.exp = exp;
        this.varName = varName;
    }

    @Override
    public PrgState execute(PrgState state) throws StmtException, IOException, ADTException, ExpException {
        IDictionary<String, Value> symTable = state.getSymTable();
        IDictionary<StringValue, BufferedReader> fileTable = state.getFileTable();
        if(symTable.isDefined(varName)){
            Value v = symTable.lookup(varName);
            if(v.getType().equals(new IntType())){
                Value fileName = exp.eval(symTable, state.getHeap());
                if(fileName.getType().equals(new StringType())){
                    StringValue fileString = (StringValue)fileName;
                    if(fileTable.isDefined(fileString))
                    {
                        BufferedReader fd = fileTable.lookup(fileString);
                        String line = fd.readLine();    // try catch IOException ("cannot read from file")
                        if(line!=null)
                            symTable.put(varName,new IntValue(Integer.parseInt(line)));
                        else symTable.put(varName, new IntType().getDefault());
                    }
                    else throw new StmtException("The file name: "+fileString+", is not defined in fileTable");
                }
                else throw new StmtException("The given value: " + fileName + ", is not of type String");
            }
            else throw new StmtException("The given variable: " + varName + ", is not of type int");
        }
        else throw new StmtException("The given variable :" + varName + ", is not defined in symTable");
        return null;
    }

    @Override
    public String toString(){
        return "read file: "+exp.toString()+" into variable "+varName;
    }

    @Override
    public IStmt deepcopy() {
        return new ReadFile(exp.deepcopy(), varName);
    }

    @Override
    public IDictionary<String, Type> typeCheck(IDictionary<String, Type> typeEnv) throws StmtException, ADTException, ExpException {
        Type typeVar = typeEnv.lookup(varName);
        Type typeExp = exp.typecheck(typeEnv);
        if(typeVar.equals(new IntType())){
            return typeEnv;
        }
        else throw new StmtException("READ FILE stmt: right hand side and left hand side have different types");
    }
}
