package toyLanguage.cotroller;

import javafx.collections.FXCollections;
import javafx.collections.ObservableList;
import javafx.event.ActionEvent;
import javafx.fxml.FXML;
import javafx.fxml.FXMLLoader;
import javafx.scene.Scene;
import javafx.scene.control.Alert;
import javafx.scene.control.Button;
import javafx.scene.control.ListView;
import javafx.stage.Modality;
import javafx.stage.Stage;
import toyLanguage.Main;
import toyLanguage.model.exceptions.ADTException;
import toyLanguage.model.exceptions.ExpException;
import toyLanguage.model.exceptions.StmtException;
import toyLanguage.model.statements.IStmt;
import toyLanguage.model.programState.*;

import java.io.IOException;
import java.util.ArrayList;

public class StartWindowController {
    Stage mainStage;
    ObservableList<IStmt> statements;

    @FXML
    private Button executeButton;

    @FXML
    private ListView<String> programsListView;

    @FXML
    void onClickExecuteButton(ActionEvent event) {
        int index = programsListView.getSelectionModel().getSelectedIndex();
        if (index == -1) {
            this.raiseAlert("You have to select a program.");
            return;
        }

        // Before opening a new window, perform a type check on the selected program
        IStmt statement = this.statements.get(index);
        try {
            statement.typeCheck(new MyDictionary<>());
        } catch (StmtException | ExpException | ADTException e) {
            this.raiseAlert(e.getMessage());
            return;
            //throw new RuntimeException(e);
            // TODO: CATCH THIS AND HANDLE IT IN INTERPRETER
        }

        try {
            // Load the scene needed to execute a program and set its controller's program state using the
            // selected statement (also pass the name of the folder where the repository should log the execution steps)
            FXMLLoader fxmlLoader = new FXMLLoader(Main.class.getResource("/com/example/toylanguagegui/executingProgram.fxml"));
            Scene scene = new Scene(fxmlLoader.load());
            PrgExecController programExecutionController = fxmlLoader.getController();
            programExecutionController.createProgramState(statement, "logFile.txt");

            // Create the new window and set its scene
            Stage newWindow = new Stage();
            newWindow.setTitle("Program Execution");
            newWindow.setScene(scene);

            // Set the new window to be modal, with the main window as the owner
            newWindow.initModality(Modality.WINDOW_MODAL);
            newWindow.initOwner(this.mainStage);

            newWindow.show();   // Show the new window on the screen
        } catch (IOException e) {
            e.printStackTrace();
        }
    }

    @FXML
    void initialize() {
        this.statements = FXCollections.observableArrayList();
    }

    public void addStatement(IStmt statement) {
        this.statements.add(statement);
        this.updateListViewItems();
    }

    private void updateListViewItems() {
        int index = 1;
        ArrayList<String> programsAsStrings = new ArrayList<>();
        for (IStmt statement: this.statements) {
            programsAsStrings.add(index + ") " + statement.toString());
            index = index + 1;
        }
        ObservableList<String> programsAsObservableStrings = FXCollections.observableList(programsAsStrings);
        this.programsListView.setItems(programsAsObservableStrings);
    }

    private void raiseAlert(String msg) {
        Alert alert = new Alert(Alert.AlertType.ERROR);
        alert.setContentText(msg);
        alert.show();
    }

    public void setMainStage(Stage stage) {
        this.mainStage = stage;
    }
}
