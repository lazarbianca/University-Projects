package toyLanguage.view;

import toyLanguage.cotroller.Controller;
import toyLanguage.model.exceptions.ADTException;
import toyLanguage.model.exceptions.ExpException;
import toyLanguage.model.exceptions.MyException;
import toyLanguage.model.exceptions.StmtException;
import toyLanguage.model.expressions.*;
import toyLanguage.model.programState.*;
import toyLanguage.model.statements.*;
import toyLanguage.model.types.*;
import toyLanguage.model.values.*;
import toyLanguage.repository.IRepository;
import toyLanguage.repository.Repository;
import toyLanguage.view.commands.ExitCommand;
import toyLanguage.view.commands.RunExampleCommand;

import java.io.BufferedReader;

public class Interpreter {
    public static void main(String[] args) {

        TextMenu menu = new TextMenu();
        menu.addCommand(new ExitCommand("0", "Exit"));
        // for type checker; a sort of global symTable
        IDictionary<String, Type> typeEnv = new MyDictionary<>();

        try {
            IStmt example1 = new CompStmt(new VarDeclStmt("v", new IntType()),
                    new CompStmt(new AssignStmt("v", new ValueExp(new IntValue(2))),
                            new PrintStmt(new VarExp("v"))));
            // is the return value re-assigned?
            typeEnv = example1.typeCheck(typeEnv);
            PrgState p1 = new PrgState(new MyStack<IStmt>(), new MyDictionary<String, Value>(),
                    new MyList<Value>(), new MyDictionary<StringValue, BufferedReader>(),
                    new MyHeap<Value>(), example1);
            IRepository r1 = new Repository("logFile.txt");
            r1.add(p1);
            Controller c1 = new Controller(r1);
            menu.addCommand(new RunExampleCommand("1", example1.toString(), c1));
        }
        catch (ADTException | StmtException | ExpException e) {
            System.out.println("TypeCheck failed: " + e.getMessage());
        }

        try{
            IStmt example2 = new CompStmt(new VarDeclStmt("a", new IntType()),
                    new CompStmt(new VarDeclStmt("b", new IntType()), new CompStmt(new AssignStmt("a",
                            new ArithExp('+', new ValueExp(new IntValue(2)), new ArithExp('*',
                                    new ValueExp(new IntValue(3)), new ValueExp(new IntValue(5))))), new CompStmt(
                            new AssignStmt("b", new ArithExp('+', new VarExp("a"), new ValueExp(new IntValue(1)))),
                            new PrintStmt(new VarExp("b"))))));
            typeEnv = example2.typeCheck(typeEnv);
            PrgState p2 = new PrgState(new MyStack<IStmt>(), new MyDictionary<String, Value>(),
                    new MyList<Value>(), new MyDictionary<StringValue, BufferedReader>(), new MyHeap<Value>(), example2);
            IRepository r2 = new Repository("logFile.txt");
            r2.add(p2);
            Controller c2 = new Controller(r2);
            menu.addCommand(new RunExampleCommand("2", example2.toString(), c2));
        }
        catch (ADTException | StmtException | ExpException e) {
            System.out.println("TypeCheck failed: " + e.getMessage());
        }

        try {
            IStmt example3 = new CompStmt(new VarDeclStmt("a", new BoolType()), new CompStmt(new VarDeclStmt("v",
                    new IntType()), new CompStmt(new AssignStmt("a", new ValueExp(new BoolValue(true))),
                    new CompStmt(new IfStmt(new VarExp("a"), new AssignStmt("v", new ValueExp(new IntValue(2))),
                            new AssignStmt("v", new ValueExp(new IntValue(3)))), new PrintStmt(new VarExp("v"))))));
            typeEnv = example3.typeCheck(typeEnv);
            PrgState p3 = new PrgState(new MyStack<IStmt>(), new MyDictionary<String, Value>(),
                    new MyList<Value>(), new MyDictionary<StringValue, BufferedReader>(), new MyHeap<Value>(), example3);
            IRepository r3 = new Repository("logFile.txt");
            r3.add(p3);
            Controller c3 = new Controller(r3);
            menu.addCommand(new RunExampleCommand("3", example3.toString(), c3));
        }
        catch (ADTException | StmtException | ExpException e) {
            System.out.println("TypeCheck failed: " + e.getMessage());
        }

        try {
            IStmt example4 = new CompStmt(
                    new VarDeclStmt("a", new BoolType()), //c1_1
                    new CompStmt( //c1_2
                            new AssignStmt("a", new ValueExp(new BoolValue(true))),  //1
                            new CompStmt(
                                    new VarDeclStmt("b", new BoolType()),  //2
                                    new CompStmt(
                                            new AssignStmt("b", new ValueExp(new BoolValue(false))),
                                            new CompStmt(
                                                    new PrintStmt(new LogicExp(new VarExp("a"), new VarExp("b"), "&&")),
                                                    new CompStmt(
                                                            new PrintStmt(new LogicExp(new VarExp("a"), new VarExp("a"), "&&")),
                                                            new PrintStmt(new LogicExp(new VarExp("a"), new VarExp("b"), "||"))))))));
            typeEnv = example4.typeCheck(typeEnv);
            PrgState p4 = new PrgState(new MyStack<IStmt>(), new MyDictionary<String, Value>(),
                    new MyList<Value>(), new MyDictionary<StringValue, BufferedReader>(), new MyHeap<Value>(), example4);
            IRepository r4 = new Repository("logFile.txt");
            r4.add(p4);
            Controller c4 = new Controller(r4);
            menu.addCommand(new RunExampleCommand("4", example4.toString(), c4));
        }
        catch (ADTException | StmtException | ExpException e) {
            System.out.println("TypeCheck failed: " + e.getMessage());
        }


        try {
            // example 5: string varf; varf="test.in"; openRFile(varf); int varc; readFile(varf, varc); print(varc); readFile(varf, varc); print(varc); closeRFile(varf)
            IStmt example5 = new CompStmt(new VarDeclStmt("varf", new StringType()),
                    new CompStmt(new AssignStmt("varf", new ValueExp(new StringValue("test.in"))),
                            new CompStmt(new OpenRFile(new VarExp("varf")),
                                    new CompStmt(new VarDeclStmt("varc", new IntType()),
                                            new CompStmt(new ReadFile(new VarExp("varf"), "varc"),
                                                    new CompStmt(new PrintStmt(new VarExp("varc")),
                                                            new CompStmt(new ReadFile(new VarExp("varf"), "varc"),
                                                                    new CompStmt(new PrintStmt(new VarExp("varc")),
                                                                            new CloseRFile(new VarExp("varf"))))))))));
            typeEnv = example5.typeCheck(typeEnv);
            PrgState p5 = new PrgState(new MyStack<IStmt>(), new MyDictionary<String, Value>(),
                    new MyList<Value>(), new MyDictionary<StringValue, BufferedReader>(), new MyHeap<Value>(), example5);
            IRepository r5 = new Repository("logFile.txt");
            r5.add(p5);
            Controller c5 = new Controller(r5);
            menu.addCommand(new RunExampleCommand("5", example5.toString(), c5));
        }
        catch (ADTException | StmtException | ExpException e) {
            System.out.println("TypeCheck failed: " + e.getMessage());
        }

        try {
            // example 6: print(2 + 3 < 1); (false)
            IStmt example6 = new PrintStmt(new RelationalExp(
                    new ArithExp('+', new ValueExp(new IntValue(5)), new ValueExp(new IntValue(2))),
                    new ValueExp(new IntValue(1)), "<"));
            typeEnv = example6.typeCheck(typeEnv);
            PrgState p6 = new PrgState(new MyStack<IStmt>(), new MyDictionary<String, Value>(),
                    new MyList<Value>(), new MyDictionary<StringValue, BufferedReader>(), new MyHeap<Value>(), example6);
            IRepository r6 = new Repository("logFile.txt");
            r6.add(p6);
            Controller c6 = new Controller(r6);
            menu.addCommand(new RunExampleCommand("6", example6.toString(), c6));
        }
        catch (ADTException | StmtException | ExpException e) {
            System.out.println("TypeCheck failed: " + e.getMessage());
        }

        //
        // Ref int v;           Comp ( 1 VarDecl, 2
        // new(v,20);               Comp( 1 New, 2
        // Ref Ref int a;               Comp( 1 VarDecl (new reftype(new reftype(new intype))),
        // new(a,v);                            Comp( 1 New, 2
        // print(rH(v));                            Comp( 1 Print, 2
        // print( rH(rH(a)) + 5)                           Print( new Arith (new rH(new rH(a)), 5)))
        //
        // At the end of execution: Heap={1->20, 2->(1,int)}, SymTable={v->(1,int), a->(2,Ref int)} and
        //Out={20, 25}
        try {
            IStmt example7 = new CompStmt(new VarDeclStmt("v", new RefType(new IntType())),
                    new CompStmt(new New("v", new ValueExp(new IntValue(20))),
                            new CompStmt(new VarDeclStmt("a", new RefType(new RefType(new IntType()))),
                                    new CompStmt(new New("a", new VarExp("v")),
                                            new CompStmt(new PrintStmt(new ReadFromHeap(new VarExp("v"))),
                                                    new PrintStmt(new ArithExp('+',
                                                            new ReadFromHeap(new ReadFromHeap(new VarExp("a"))),
                                                            new ValueExp(new IntValue(5)))))))));
            typeEnv = example7.typeCheck(typeEnv);
            PrgState p7 = new PrgState(new MyStack<IStmt>(), new MyDictionary<String, Value>(),
                    new MyList<Value>(), new MyDictionary<StringValue, BufferedReader>(), new MyHeap<Value>(), example7);
            IRepository r7 = new Repository("logFile.txt");
            r7.add(p7);
            Controller c7 = new Controller(r7);
            menu.addCommand(new RunExampleCommand("7", example7.toString(), c7));
        }
        catch (ADTException | StmtException | ExpException e) {
            System.out.println("TypeCheck failed: " + e.getMessage());
        }

        //Ref int v;
        // new(v,20);
        // print(rH(v));
        // wH(v,30);
        // print(rH(v)+5); #4
        try {
            IStmt example8 = new CompStmt(new VarDeclStmt("v", new RefType(new IntType())),
                    new CompStmt(new New("v", new ValueExp(new IntValue(20))),
                            new CompStmt(new PrintStmt(new ReadFromHeap(new VarExp("v"))),
                                    new CompStmt(new WriteToHeap("v", new ValueExp(new IntValue(30))),
                                            new PrintStmt(new ArithExp('+',
                                                    new ReadFromHeap(new VarExp("v")),
                                                    new ValueExp(new IntValue(5))))))));
            typeEnv = example8.typeCheck(typeEnv);
            PrgState p8 = new PrgState(new MyStack<IStmt>(), new MyDictionary<String, Value>(),
                    new MyList<Value>(), new MyDictionary<StringValue, BufferedReader>(), new MyHeap<Value>(), example8);
            IRepository r8 = new Repository("logFile.txt");
            r8.add(p8);
            Controller c8 = new Controller(r8);
            menu.addCommand(new RunExampleCommand("8", example8.toString(), c8));
        }
        catch (ADTException | StmtException | ExpException e) {
            System.out.println("TypeCheck failed: " + e.getMessage());
        }

        //Ref int v;
        // new(v,20);
        // Ref Ref int a;
        // new(a,v);
        // new(v,30);
        // print(rH(rH(a))) #5
        try {
            IStmt example9 = new CompStmt(new VarDeclStmt("v", new RefType(new IntType())),
                    new CompStmt(new New("v", new ValueExp(new IntValue(20))),
                            new CompStmt(new VarDeclStmt("a", new RefType(new RefType(new IntType()))),
                                    new CompStmt(new New("a", new VarExp("v")),
                                            new CompStmt(new New("v", new ValueExp(new IntValue(30))),
                                                    new PrintStmt(new ReadFromHeap(new ReadFromHeap(new VarExp("a")))))))));
            // exmaple 9 without var a, to show how the garbage collector cleans up first value of v
//        IStmt example9= new CompStmt(new VarDeclStmt("v",new RefType(new IntType())),
//                new CompStmt(new New("v", new ValueExp(new IntValue(20))),
//                        new CompStmt(new New("v", new ValueExp(new IntValue(30))),
//                                new PrintStmt(new readFromHeap(new readFromHeap(new VarExp("v")))))));
            typeEnv = example9.typeCheck(typeEnv);
            PrgState p9 = new PrgState(new MyStack<IStmt>(), new MyDictionary<String, Value>(),
                    new MyList<Value>(), new MyDictionary<StringValue, BufferedReader>(), new MyHeap<Value>(), example9);
            IRepository r9 = new Repository("logFile.txt");
            r9.add(p9);
            Controller c9 = new Controller(r9);
            menu.addCommand(new RunExampleCommand("9", example9.toString(), c9));
        }
        catch (ADTException | StmtException | ExpException e) {
            System.out.println("TypeCheck failed: " + e.getMessage());
        }

        // int v;
        // v=4;
        // (while (v>0) print(v);v=v-1);
        // print(v)
        try {
            IStmt example10 = new CompStmt(new VarDeclStmt("v", new IntType()),
                    new CompStmt(new AssignStmt("v", new ValueExp(new IntValue(4))),
                            new CompStmt(new WhileStmt(new RelationalExp(new VarExp("v"), new ValueExp(new IntValue(0)), ">"),
                                    new CompStmt(new PrintStmt(new VarExp("v")),
                                            new AssignStmt("v", new ArithExp('-', new VarExp("v"), new ValueExp(new IntValue(1)))))),
                                    new PrintStmt(new VarExp("v")))));
            typeEnv = example10.typeCheck(typeEnv);
            PrgState prg10 = new PrgState(new MyStack<IStmt>(), new MyDictionary<String, Value>(),
                    new MyList<Value>(), new MyDictionary<StringValue, BufferedReader>(), new MyHeap<Value>(), example10);
            IRepository r10 = new Repository("logFile.txt");
            r10.add(prg10);
            Controller c10 = new Controller(r10);
            menu.addCommand(new RunExampleCommand("10", example10.toString(), c10));
        }
        catch (ADTException | StmtException | ExpException e) {
            System.out.println("TypeCheck failed: " + e.getMessage());
        }

        // example 11: int v; Ref int a; v = 10; new(a,22);
        //             fork(wH(a,30); v = 32; print(v); print(rH(a)));
        //             print(v); print(rH(a))
        try {
            IStmt example11 = new CompStmt(new VarDeclStmt("v", new IntType()),
                    new CompStmt(new VarDeclStmt("a", new RefType(new IntType())),
                            new CompStmt(new AssignStmt("v", new ValueExp(new IntValue(10))),
                                    new CompStmt(new New("a", new ValueExp(new IntValue(22))),
                                            new CompStmt(new ForkStmt(new CompStmt(new WriteToHeap("a", new ValueExp(new IntValue(30))),
                                                    new CompStmt(new AssignStmt("v", new ValueExp(new IntValue(32))),
                                                            new CompStmt(new PrintStmt(new VarExp("v")), new PrintStmt
                                                                    (new ReadFromHeap(new VarExp("a"))))))),
                                                    new CompStmt(new PrintStmt(new VarExp("v")), new PrintStmt
                                                            (new ReadFromHeap(new VarExp("a")))))))));
            typeEnv = example11.typeCheck(typeEnv);
            PrgState prg11 = new PrgState(new MyStack<IStmt>(), new MyDictionary<String, Value>(),
                    new MyList<Value>(), new MyDictionary<StringValue, BufferedReader>(), new MyHeap<Value>(), example11);
            IRepository r11 = new Repository("logFile.txt");
            r11.add(prg11);
            Controller c11 = new Controller(r11);
            menu.addCommand(new RunExampleCommand("11", example11.toString(), c11));
        }
        catch (ADTException | StmtException | ExpException e) {
            System.out.println("TypeCheck failed: " + e.getMessage());
        }

        // example 12: int v;
        //             fork(v=30; print(v));
        //             fork(int a = 15; print(a));
        //             print(v);
        try {
            IStmt example12 = new CompStmt(new VarDeclStmt("v", new IntType()),
                    new CompStmt(new ForkStmt(new CompStmt(new AssignStmt("v", new ValueExp(new IntValue(30))),
                            new PrintStmt(new VarExp("v")))),
                            new CompStmt(new ForkStmt(new CompStmt(new VarDeclStmt("a", new IntType()),
                                    new CompStmt(new AssignStmt("a", new ValueExp(new IntValue(15))),
                                            new PrintStmt(new VarExp("a"))))),
                                    new PrintStmt(new VarExp("v")))));
            typeEnv = example12.typeCheck(typeEnv);
            PrgState prg12 = new PrgState(new MyStack<IStmt>(), new MyDictionary<String, Value>(),
                    new MyList<Value>(), new MyDictionary<StringValue, BufferedReader>(), new MyHeap<Value>(), example12);
            IRepository r12 = new Repository("logFile.txt");
            r12.add(prg12);
            Controller c12 = new Controller(r12);
            menu.addCommand(new RunExampleCommand("12", example12.toString(), c12));
        }
        catch (ADTException | StmtException | ExpException e) {
            System.out.println("TypeCheck failed: " + e.getMessage());
        }

        // fork bomb example; here  we should have 20 threads only
        // ex 13:
        // Ref int a;
        // int counter;
        // while(counter<10){
        //      fork( fork( {new (a,counter); print (rH(a));} ))
        //      counter++; }
        try {
            IStmt example13 = new CompStmt(new VarDeclStmt("a", new RefType(new IntType())),
                    new CompStmt(new VarDeclStmt("counter", new IntType()),
                            new WhileStmt(new RelationalExp(new VarExp("counter"), new ValueExp(new IntValue(10)), "<"),
                                    new CompStmt(new ForkStmt(new ForkStmt(new CompStmt(new New("a", new VarExp("counter")),
                                            new PrintStmt(new ReadFromHeap(new VarExp("a")))))),
                                            new AssignStmt("counter", new ArithExp('+', new VarExp("counter"),
                                                    new ValueExp(new IntValue(1))))))));
            typeEnv = example13.typeCheck(typeEnv);
            PrgState prg13 = new PrgState(new MyStack<IStmt>(), new MyDictionary<String, Value>(),
                    new MyList<Value>(), new MyDictionary<StringValue, BufferedReader>(), new MyHeap<Value>(), example13);
            IRepository r13 = new Repository("logFile.txt");
            r13.add(prg13);
            Controller c13 = new Controller(r13);
            menu.addCommand(new RunExampleCommand("13", example13.toString(), c13));
        }
        catch (ADTException | StmtException | ExpException e) {
            System.out.println("TypeCheck failed: " + e.getMessage());
        }

        menu.show();
    }

    /*void addExample(IStmt example, TextMenu menu, IDictionary<String, Type> typeEnv) throws StmtException, ExpException, ADTException {
        typeEnv = example.typeCheck(typeEnv);
        PrgState prg = new PrgState(new MyStack<IStmt>(), new MyDictionary<String, Value>(),
                new MyList<Value>(), new MyDictionary<StringValue, BufferedReader>(), new MyHeap<Value>(), example);
        IRepository r = new Repository("logFile.txt");
        r.add(prg);
        Controller c = new Controller(r);
        menu.addCommand();
    }*/
}
