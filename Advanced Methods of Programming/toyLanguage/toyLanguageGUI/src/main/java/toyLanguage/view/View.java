//package view;
//
//import cotroller.Controller;
//import model.exceptions.MyException;
//import model.expressions.ArithExp;
//import model.expressions.LogicExp;
//import model.expressions.ValueExp;
//import model.expressions.VarExp;
//import model.programState.*;
//import model.statements.*;
//import model.types.BoolType;
//import model.types.IntType;
//import model.values.BoolValue;
//import model.values.IntValue;
//import model.values.StringValue;
//import model.values.Value;
//import repository.IRepository;
//import repository.Repository;
//
//import java.io.BufferedReader;
//import java.util.Scanner;
//
//public class View {
//    IStmt example1 = new CompStmt(new VarDeclStmt("v", new IntType()),
//            new CompStmt(new AssignStmt("v",new ValueExp(new IntValue(2))),
//                    new VarDeclStmt("v", new IntType())));
//
//    IStmt example2 = new CompStmt(new VarDeclStmt("a", new IntType()),
//            new CompStmt(new VarDeclStmt("b",new IntType()),new CompStmt(new AssignStmt("a",
//            new ArithExp('+', new ValueExp(new IntValue(2)), new ArithExp('*',
//            new ValueExp(new IntValue(3)), new ValueExp(new IntValue(5))))), new CompStmt(
//            new AssignStmt("b",new ArithExp('+',new VarExp("a"), new ValueExp(new IntValue(1)))),
//            new PrintStmt(new VarExp("b"))))));
//
//    IStmt example3 = new CompStmt(new VarDeclStmt("a",new BoolType()),new CompStmt(new VarDeclStmt("v",
//            new IntType()), new CompStmt(new AssignStmt("a", new ValueExp(new BoolValue(true))),
//            new CompStmt(new IfStmt(new VarExp("a"), new AssignStmt("v",new ValueExp(new IntValue(2))),
//            new AssignStmt("v", new ValueExp(new IntValue(3)))), new PrintStmt(new VarExp("v"))))));
//
//    IStmt example4 = new CompStmt(
//            new VarDeclStmt("a",new BoolType()), //c1_1
//            new CompStmt( //c1_2
//                    new AssignStmt("a", new ValueExp(new BoolValue(true))),  //1
//                    new CompStmt(
//                            new VarDeclStmt("b",new BoolType()),  //2
//                            new CompStmt(
//                                    new AssignStmt("b", new ValueExp(new BoolValue(false))),
//                                    new CompStmt(
//                                            new PrintStmt(new LogicExp(new VarExp("a"), new VarExp("b"),"&&")),
//                                            new CompStmt(
//                                                    new PrintStmt(new LogicExp(new VarExp("a"),new VarExp("a"),"&&")),
//                                                    new PrintStmt(new LogicExp(new VarExp("a"), new VarExp("b"), "||"))))))));
//    //new AssignStmt("a",new ValueExp(
//    //new BoolValue(true))));
//    //boolean a=true;
//    //boolean b=false;
//    //print(a&&b);
//    //print(a&&a);
//    //print(a||b);
//    public View() {}
//
//
//    void menu(){
//        System.out.println("0. Exit execution");
//        System.out.println("1. "+example1);
//        System.out.println("2. "+example2);
//        System.out.println("3. "+example3);
//        System.out.println("4. "+example4);
//    }
//    String readLogFilePath(){
//        Scanner scanner = new Scanner(System.in);
//        System.out.println("Enter the log file path: ");
//        return scanner.nextLine();
//    }
//    public void start(){
//        // read menu
//        // handle user options
//        View view = new View();
//        while(true) {
//            view.menu();  // menu() is not static, making it statiic is a solution but a bad sol
//            Scanner scanner = new Scanner(System.in);
//            String input = scanner.nextLine();
//            switch (input) {
//                case "0":
//                    return;
//                case "1":
//                    System.out.println("Enter 1 for full display: ");
//                    String displayFlag1 = scanner.nextLine();
//                    this.runExample1(displayFlag1);
//                    break;
//                case "2":
//                    System.out.println("Enter 1 for full display: ");
//                    String displayFlag2 = scanner.nextLine();
//                    this.runExample2(displayFlag2);
//                    break;
//                case "3":
//                    System.out.println("Enter 1 for full display: ");
//                    String displayFlag3 = scanner.nextLine();
//                    this.runExample3(displayFlag3);
//                    break;
//                case "4":
//                    System.out.println("Enter 1 for full display: ");
//                    String displayFlag4 = scanner.nextLine();
//                    this.runExample4(displayFlag4);
//                    break;
//                default:
//                    break;
//            }
//        }
//    }
//
//    public void runExample1(String displayFlag) {
//        IStack<IStmt> stk = new MyStack<IStmt>();
//        IDictionary<String, Value> symTbl = new MyDictionary<String, Value>();
//        IList<Value> out = new MyList<Value>();
//        IDictionary<StringValue, BufferedReader> fileTable = new MyDictionary<StringValue, BufferedReader>();
//        try{
//            PrgState crtPrgState = new PrgState(stk,symTbl,out,fileTable,example1);
//            String logFilePath = readLogFilePath();
//            IRepository repo = new Repository(logFilePath);
//            repo.add(crtPrgState);
//            Controller controller = new Controller(repo, displayFlag);
//            //controller.setDisplayFlag(displayFlag);
//            controller.allStep();
//        }
//        catch(MyException | java.io.IOException e){
//            System.out.println(e.getMessage());
//        }
//    }
//
//    public void runExample2(String displayFlag){
//        IStack<IStmt> stk = new MyStack<IStmt>();
//        IDictionary<String,Value> symTbl = new MyDictionary<String,Value>();
//        IList<Value> out = new MyList<Value>();
//        IDictionary<StringValue, BufferedReader> fileTable = new MyDictionary<StringValue, BufferedReader>();
//        try{
//            PrgState crtPrgState = new PrgState(stk,symTbl,out,fileTable,example2);
//            String logFilePath = readLogFilePath();
//            IRepository repo = new Repository(logFilePath);
//            repo.add(crtPrgState);
//            Controller controller = new Controller(repo, displayFlag);
//            controller.allStep();
//        }
//        catch(MyException|java.io.IOException e){
//            System.out.println(e.getMessage());
//        }
//    }
//
//    public void runExample3(String displayFlag){
//        IStack<IStmt> stk = new MyStack<IStmt>();
//        IDictionary<String,Value> symTbl = new MyDictionary<String,Value>();
//        IList<Value> out = new MyList<Value>();
//        IDictionary<StringValue, BufferedReader> fileTable = new MyDictionary<StringValue, BufferedReader>();
//        try{
//            PrgState crtPrgState = new PrgState(stk,symTbl,out,fileTable,example3);
//            String logFilePath = readLogFilePath();
//            IRepository repo = new Repository(logFilePath);
//            repo.add(crtPrgState);
//            Controller controller = new Controller(repo, displayFlag);
//            controller.allStep();
//        }
//        catch(MyException|java.io.IOException e){
//            System.out.println(e.getMessage());
//        }
//    }
//
//    public void runExample4(String displayFlag){
//        IStack<IStmt> stk = new MyStack<IStmt>();
//        IDictionary<String,Value> symTbl = new MyDictionary<String,Value>();
//        IList<Value> out = new MyList<Value>();
//        IDictionary<StringValue, BufferedReader> fileTable = new MyDictionary<StringValue, BufferedReader>();
//        try{
//            PrgState crtPrgState = new PrgState(stk,symTbl,out,fileTable,example4);
//            String logFilePath = readLogFilePath();
//            IRepository repo = new Repository(logFilePath);
//            repo.add(crtPrgState);
//            Controller controller = new Controller(repo, displayFlag);
//            controller.allStep();
//        }
//        catch(MyException|java.io.IOException e){
//            System.out.println(e.getMessage());
//        }
//    }
//}
