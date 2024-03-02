package toyLanguage.model.programState;

import toyLanguage.model.exceptions.ADTException;
import toyLanguage.model.exceptions.ExpException;
import toyLanguage.model.exceptions.MyException;
import toyLanguage.model.exceptions.StmtException;
import toyLanguage.model.statements.IStmt;
import toyLanguage.model.programState.IStack;
import toyLanguage.model.programState.IList;
import toyLanguage.model.programState.IDictionary;
import toyLanguage.model.programState.IHeap;
import toyLanguage.model.values.StringValue;
import toyLanguage.model.values.Value;

import java.io.BufferedReader;
import java.io.IOException;
import java.util.Set;
import java.util.concurrent.atomic.AtomicInteger;

public class PrgState {
    IStack<IStmt> exeStack;
    IDictionary<String, Value> symTable;
    IList<Value> out;
    IDictionary<StringValue, BufferedReader> fileTable;
    IHeap<Value> heap;
    private static final AtomicInteger threadIdCounter = new AtomicInteger(0);
    private int id;
    public IStack<IStmt> getExeStack() {
        return exeStack;
    }

    public IHeap<Value> getHeap() {
        return heap;
    }

    public void setHeap(IHeap<Value> heap) {
        this.heap = heap;
    }

    public void setExeStack(IStack<IStmt> exeStack) {
        this.exeStack = exeStack;
    }

    public void setSymTable(IDictionary<String, Value> symTable) {
        this.symTable = symTable;
    }

    public IList<Value> getOut() {
        return out;
    }

    public void setOut(IList<Value> out) {
        this.out = out;
    }

    public IStmt getOriginalProgram() {
        return originalProgram;
    }

    public void setOriginalProgram(IStmt originalProgram) {
        this.originalProgram = originalProgram;
    }

    IStmt originalProgram;

    public PrgState(){}
    public PrgState(IStack<IStmt> s, IDictionary<String, Value> tbl, IList<Value> o,
                    IDictionary<StringValue, BufferedReader> f, IHeap<Value> h, IStmt prg){
        exeStack = s;
        symTable = tbl;
        out = o;
        fileTable = f;
        heap = h;
        originalProgram = (IStmt) prg.deepcopy();
        this.id = threadIdCounter.incrementAndGet();
        s.push(prg);
    }

    public IStack<IStmt> getStack() {
        return exeStack;
    }

    public IDictionary<String, Value> getSymTable() {
        return symTable;
    }
    public IDictionary<StringValue, BufferedReader> getFileTable(){return fileTable;}

    public String fileTableToString(){
        Set<StringValue> keySet = fileTable.getKeys();
        StringBuilder keys = new StringBuilder();
        for(StringValue key : keySet){
            keys.append(key.toString());
        }
        return keys.toString();
    }

    public int getId() {
        return id;
    }

    public boolean isNotCompleted(){return !exeStack.isEmpty();}
    // return false if stack is empty, true otherwise

    public PrgState oneStep() throws MyException, IOException, StmtException, ExpException, ADTException {
        if(exeStack.isEmpty())
            throw new MyException("prgState stack is empty");
        IStmt crtStmt = exeStack.pop();
        return crtStmt.execute(this);
    }

    @Override
    public String toString() {
        return "PrgState{" +
                " \n ID = " + String.valueOf(id) +
                " \nexeStack=" + exeStack +
                ",\n symTable=" + symTable +
                ",\n out=" + out +
                ",\n fileTable=" + fileTableToString() +
                ",\n heap=" + heap +
                ",\n originalProgram=" + originalProgram +
                "}\n";
    }
}
