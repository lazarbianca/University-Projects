package toyLanguage.cotroller;
import javafx.beans.property.SimpleIntegerProperty;
import javafx.beans.property.SimpleStringProperty;
import javafx.collections.FXCollections;
import javafx.fxml.FXML;
import javafx.scene.control.*;
import javafx.util.Pair;
import javafx.event.ActionEvent;
import toyLanguage.model.exceptions.MyException;
import toyLanguage.model.programState.*;
import toyLanguage.model.statements.IStmt;
import toyLanguage.model.values.StringValue;
import toyLanguage.model.values.Value;
import toyLanguage.repository.IRepository;
import toyLanguage.repository.Repository;
import java.util.ArrayList;

import java.io.BufferedReader;
import java.util.List;
import java.util.ListIterator;
import java.util.Stack;
import java.util.stream.Collectors;

public class PrgExecController {
    @FXML
    private ListView<String> executionStackList;

    @FXML
    private ListView<Pair<String, String>> fileTableList;

    @FXML
    private TableView<Pair<Integer, String>> heapTable;

    @FXML
    private ListView<String> outList;

    @FXML
    private TableColumn<Pair<Integer, String>, Integer> heapTableAddressColumn;

    @FXML
    private TableColumn<Pair<Integer, String>, String> heapTableValueColumn;

    @FXML
    private Label nrProgramStatesLabel;

    @FXML
    private ListView<Integer> prgStateIdentifiers;

    @FXML
    private Button runOneStepButton;

    @FXML
    private TableView<Pair<String, String>> symbolTable;

    @FXML
    private TableColumn<Pair<String, String>, String> symbolTableValueColumn;

    @FXML
    private TableColumn<Pair<String, String>, String> symbolTableVarNameColumn;

    @FXML
    void initialize() {
        this.heapTableAddressColumn.setCellValueFactory(p -> new SimpleIntegerProperty(p.getValue().getKey()).asObject());
        this.heapTableValueColumn.setCellValueFactory(p -> new SimpleStringProperty(p.getValue().getValue()));

        this.symbolTableVarNameColumn.setCellValueFactory(p -> new SimpleStringProperty(p.getValue().getKey()));
        this.symbolTableValueColumn.setCellValueFactory(p -> new SimpleStringProperty(p.getValue().getValue()));

        this.prgStateIdentifiers.getSelectionModel().selectedItemProperty().addListener((observableValue, integer, t1) -> {
            if (t1 == null) {
                return;
            }
            try {
                currentProgramState = this.repository.getProgramStateById(t1);
            } catch (MyException e) {
                raiseAlert(e.getMessage());  // TODO: aici?
            }
            // exe stack, sym table should get repopulated
            // heap table, file table, output list, prg state ids are shared between prg states; no re-population
            populateExecutionStack();
            populateSymbolTable();
        });
    }

    private PrgState currentProgramState;
    private IRepository repository;
    private Controller controller;
    public void createProgramState(IStmt program, String repositoryFilePath) {
        PrgState initialProgramState = new PrgState(new MyStack<IStmt>(), new MyDictionary<String, Value>(),
                new MyList<Value>(), new MyDictionary<StringValue, BufferedReader>(), new MyHeap<Value>(), program);
        this.currentProgramState = initialProgramState;
        this.repository = new Repository(repositoryFilePath);
        repository.add(initialProgramState);
        this.controller = new Controller(this.repository);
        this.controller.createExecutor();
        this.populateEverything();
    }

    private boolean checkForUnfinishedProgramStates() {
        return !this.repository.getPrgList().isEmpty();
    }

    @FXML
    void runOneStep(ActionEvent event) {
        if (!this.checkForUnfinishedProgramStates()) {
            this.raiseAlert("There are no unfinished prg states");
            return;
        }
        try {
            List<PrgState> programStateList = this.controller.removeCompletedPrg(this.repository.getPrgList());
            this.controller.conservativeGarbageCollector(programStateList);
            this.controller.oneStepForAllPrg(programStateList);
            programStateList = this.controller.removeCompletedPrg(this.repository.getPrgList());
            if (programStateList.size() == 0) {
                this.controller.destroyExecutor();
                this.repository.setPrgState(programStateList);
            }
        } catch (InterruptedException e) {
            this.raiseAlert(e.getMessage());
        }
        this.populateEverything();
    }

    private void populateEverything() {
        this.populateProgramStateIdentifiersList();
        this.populateHeapTable();
        this.populateSymbolTable();
        this.populateFileTable();
        this.populateExecutionStack();
        this.populateOutList();
    }

    private void populateProgramStateIdentifiersList() {
        List<Integer> programStatesIds = this.repository.getPrgList().stream().map(PrgState::getId).collect(Collectors.toList());
        this.prgStateIdentifiers.setItems(FXCollections.observableList(programStatesIds));
        this.updateNrPrgsStatesLabel();
    }

    private void updateNrPrgsStatesLabel() {
        this.nrProgramStatesLabel.setText(String.valueOf(this.repository.getPrgList().size()));
    }

    private void populateHeapTable() {
        ArrayList<Pair<Integer, String>> heapElems = new ArrayList<>();
        this.currentProgramState.getHeap().getContent().forEach((key, value) -> heapElems.add(new Pair<>(key, value.toString())));
        this.heapTable.setItems(FXCollections.observableList(heapElems));
    }

    private void populateSymbolTable() {
        ArrayList<Pair<String, String>> symbolTableElems = new ArrayList<>();
        this.currentProgramState.getSymTable().getContent().forEach((key, value) -> symbolTableElems.add(new Pair<>(key, value.toString())));
        this.symbolTable.setItems(FXCollections.observableList(symbolTableElems));
    }

    private void populateFileTable() {
        ArrayList<Pair<String, String>> files = new ArrayList<>();
        this.currentProgramState.getFileTable().getContent().forEach((key, value) -> files.add(new Pair<>(key.getVal(), value.toString())));
        this.fileTableList.setItems(FXCollections.observableList(files));
    }

    private void populateExecutionStack() {
        //this.repository.getProgramStateById(this.currentProgramState).getExeStack().getStack();
        Stack<IStmt> stack = this.currentProgramState.getExeStack().getStack();
        ArrayList<String> stackElems = new ArrayList<>();
        ListIterator<IStmt> stackIterator = stack.listIterator(stack.size());
        while (stackIterator.hasPrevious()) {
            stackElems.add(stackIterator.previous().toString());
        }

        this.executionStackList.setItems(FXCollections.observableList(stackElems));
    }

    private void populateOutList() {
        ArrayList<String> output = new ArrayList<>();
        this.currentProgramState.getOut().getOutput().forEach(e -> output.add(e.toString()));
        this.outList.setItems(FXCollections.observableList(output));
    }

    private void raiseAlert(String msg) {
        Alert alert = new Alert(Alert.AlertType.ERROR);
        alert.setContentText(msg);
        alert.show();
    }
}
