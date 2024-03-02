package toyLanguage.view.commands;

import toyLanguage.cotroller.Controller;
import toyLanguage.model.exceptions.MyException;
import java.io.IOException;
import java.util.Scanner;

public class RunExampleCommand extends Command {
    private Controller controller;

    public RunExampleCommand(String k, String desc, Controller c) {
        super(k, desc);
        this.controller = c;
    }

    @Override
    public void execute() {
        try {
            Scanner scanner = new Scanner(System.in);
            System.out.println("Enter 1 for full display: ");
            String displayFlag = scanner.nextLine();
            controller.setDisplayFlag(displayFlag);
            this.controller.allSteps();
        } catch (InterruptedException e) {
            System.out.println(e.getMessage());
        }
    }
}
