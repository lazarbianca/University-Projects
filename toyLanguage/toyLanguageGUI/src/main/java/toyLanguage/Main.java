package toyLanguage;

import javafx.application.Application;
import javafx.fxml.FXMLLoader;
import javafx.scene.Parent;
import javafx.scene.Scene;
import javafx.stage.Stage;
import toyLanguage.cotroller.StartWindowController;
import toyLanguage.model.expressions.*;
import toyLanguage.model.programState.IStack;
import toyLanguage.model.statements.*;
import toyLanguage.model.types.BoolType;
import toyLanguage.model.types.IntType;
import toyLanguage.model.types.RefType;
import toyLanguage.model.types.StringType;
import toyLanguage.model.values.BoolValue;
import toyLanguage.model.values.IntValue;
import toyLanguage.model.values.StringValue;
import toyLanguage.view.Interpreter;

import java.io.IOException;

public class Main extends Application {
    StartWindowController startWindowController; // this holds the list of programs

    @Override
    public void start(Stage stage) throws Exception {
        try {
            FXMLLoader fxmlLoader = new FXMLLoader(Main.class.getResource("/com/example/toylanguagegui/startWindow.fxml"));
            //FXMLLoader fxmlLoader = new FXMLLoader(Main.class.getResource("startWindow.fxml"));
            Parent root = fxmlLoader.load();
            Scene scene = new Scene(root);
            this.startWindowController = fxmlLoader.getController();
            this.addExamplesToController();
            this.startWindowController.setMainStage(stage);
            stage.setTitle("Hello World!");
            stage.setScene(scene);
            stage.show();
        } catch (IOException e) {
            e.printStackTrace();
        }
    }

    public static void main(String[] args) {
        launch();
    }

    private void addExamplesToController() {
        this.startWindowController.addStatement(getEx1());
        this.startWindowController.addStatement(getEx2());
        this.startWindowController.addStatement(getEx3());
        this.startWindowController.addStatement(getEx4());
        this.startWindowController.addStatement(getEx5());
        this.startWindowController.addStatement(getEx6());
        this.startWindowController.addStatement(getEx7());
        this.startWindowController.addStatement(getEx8());
        this.startWindowController.addStatement(getEx9());
        this.startWindowController.addStatement(getEx10());
        this.startWindowController.addStatement(getEx11());
        this.startWindowController.addStatement(getEx12());
        this.startWindowController.addStatement(getEx13());
    }

    private static IStmt getEx1() {
        return new CompStmt(new VarDeclStmt("v", new IntType()),
                new CompStmt(new AssignStmt("v", new ValueExp(new IntValue(2))),
                        new PrintStmt(new VarExp("v"))));
    }

    private static IStmt getEx2() {
        return new CompStmt(new VarDeclStmt("a", new IntType()),
                new CompStmt(new VarDeclStmt("b", new IntType()), new CompStmt(new AssignStmt("a",
                        new ArithExp('+', new ValueExp(new IntValue(2)), new ArithExp('*',
                                new ValueExp(new IntValue(3)), new ValueExp(new IntValue(5))))), new CompStmt(
                        new AssignStmt("b", new ArithExp('+', new VarExp("a"), new ValueExp(new IntValue(1)))),
                        new PrintStmt(new VarExp("b"))))));
    }

    private static IStmt getEx3() {
        return new CompStmt(new VarDeclStmt("a", new BoolType()), new CompStmt(new VarDeclStmt("v",
                new IntType()), new CompStmt(new AssignStmt("a", new ValueExp(new BoolValue(true))),
                new CompStmt(new IfStmt(new VarExp("a"), new AssignStmt("v", new ValueExp(new IntValue(2))),
                        new AssignStmt("v", new ValueExp(new IntValue(3)))), new PrintStmt(new VarExp("v"))))));
    }

    private static IStmt getEx4() {
        return new CompStmt(
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
    }

    private static IStmt getEx5() {
        return new CompStmt(new VarDeclStmt("varf", new StringType()),
                new CompStmt(new AssignStmt("varf", new ValueExp(new StringValue("test.in"))),
                        new CompStmt(new OpenRFile(new VarExp("varf")),
                                new CompStmt(new VarDeclStmt("varc", new IntType()),
                                        new CompStmt(new ReadFile(new VarExp("varf"), "varc"),
                                                new CompStmt(new PrintStmt(new VarExp("varc")),
                                                        new CompStmt(new ReadFile(new VarExp("varf"), "varc"),
                                                                new CompStmt(new PrintStmt(new VarExp("varc")),
                                                                        new CloseRFile(new VarExp("varf"))))))))));
    }

    private static IStmt getEx6() {
        return new PrintStmt(new RelationalExp(
                new ArithExp('+', new ValueExp(new IntValue(5)), new ValueExp(new IntValue(2))),
                new ValueExp(new IntValue(1)), "<"));
    }

    private static IStmt getEx7() {
        return new CompStmt(new VarDeclStmt("v", new RefType(new IntType())),
                new CompStmt(new New("v", new ValueExp(new IntValue(20))),
                        new CompStmt(new VarDeclStmt("a", new RefType(new RefType(new IntType()))),
                                new CompStmt(new New("a", new VarExp("v")),
                                        new CompStmt(new PrintStmt(new ReadFromHeap(new VarExp("v"))),
                                                new PrintStmt(new ArithExp('+',
                                                        new ReadFromHeap(new ReadFromHeap(new VarExp("a"))),
                                                        new ValueExp(new IntValue(5)))))))));
    }

    private static IStmt getEx8() {
        return new CompStmt(new VarDeclStmt("v", new RefType(new IntType())),
                new CompStmt(new New("v", new ValueExp(new IntValue(20))),
                        new CompStmt(new PrintStmt(new ReadFromHeap(new VarExp("v"))),
                                new CompStmt(new WriteToHeap("v", new ValueExp(new IntValue(30))),
                                        new PrintStmt(new ArithExp('+',
                                                new ReadFromHeap(new VarExp("v")),
                                                new ValueExp(new IntValue(5))))))));
    }

    private static IStmt getEx9() {
        return new CompStmt(new VarDeclStmt("v", new RefType(new IntType())),
                new CompStmt(new New("v", new ValueExp(new IntValue(20))),
                        new CompStmt(new VarDeclStmt("a", new RefType(new RefType(new IntType()))),
                                new CompStmt(new New("a", new VarExp("v")),
                                        new CompStmt(new New("v", new ValueExp(new IntValue(30))),
                                                new PrintStmt(new ReadFromHeap(new ReadFromHeap(new VarExp("a")))))))));
    }

    private static IStmt getEx10() {
        return new CompStmt(new VarDeclStmt("v", new IntType()),
                new CompStmt(new AssignStmt("v", new ValueExp(new IntValue(4))),
                        new CompStmt(new WhileStmt(new RelationalExp(new VarExp("v"), new ValueExp(new IntValue(0)), ">"),
                                new CompStmt(new PrintStmt(new VarExp("v")),
                                        new AssignStmt("v", new ArithExp('-', new VarExp("v"), new ValueExp(new IntValue(1)))))),
                                new PrintStmt(new VarExp("v")))));
    }

    private static IStmt getEx11() {
        return new CompStmt(new VarDeclStmt("v", new IntType()),
                new CompStmt(new VarDeclStmt("a", new RefType(new IntType())),
                        new CompStmt(new AssignStmt("v", new ValueExp(new IntValue(10))),
                                new CompStmt(new New("a", new ValueExp(new IntValue(22))),
                                        new CompStmt(new ForkStmt(new CompStmt(new WriteToHeap("a", new ValueExp(new IntValue(30))),
                                                new CompStmt(new AssignStmt("v", new ValueExp(new IntValue(32))),
                                                        new CompStmt(new PrintStmt(new VarExp("v")), new PrintStmt
                                                                (new ReadFromHeap(new VarExp("a"))))))),
                                                new CompStmt(new PrintStmt(new VarExp("v")), new PrintStmt
                                                        (new ReadFromHeap(new VarExp("a")))))))));
    }

    private static IStmt getEx12() {
        return new CompStmt(new VarDeclStmt("v", new IntType()),
                new CompStmt(new ForkStmt(new CompStmt(new AssignStmt("v", new ValueExp(new IntValue(30))),
                        new PrintStmt(new VarExp("v")))),
                        new CompStmt(new ForkStmt(new CompStmt(new VarDeclStmt("a", new IntType()),
                                new CompStmt(new AssignStmt("a", new ValueExp(new IntValue(15))),
                                        new PrintStmt(new VarExp("a"))))),
                                new PrintStmt(new VarExp("v")))));
    }

    private static IStmt getEx13() {
        return new CompStmt(new VarDeclStmt("a", new RefType(new IntType())),
                new CompStmt(new VarDeclStmt("counter", new IntType()),
                        new WhileStmt(new RelationalExp(new VarExp("counter"), new ValueExp(new IntValue(10)), "<"),
                                new CompStmt(new ForkStmt(new ForkStmt(new CompStmt(new New("a", new VarExp("counter")),
                                        new PrintStmt(new ReadFromHeap(new VarExp("a")))))),
                                        new AssignStmt("counter", new ArithExp('+', new VarExp("counter"),
                                                new ValueExp(new IntValue(1))))))));
    }

}