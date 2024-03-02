package toyLanguage.view;

import toyLanguage.view.commands.Command;

import java.util.HashMap;
import java.util.LinkedHashMap;
import java.util.Map;
import java.util.Scanner;

public class TextMenu {
    private Map<String, Command> commands;

    public TextMenu() {
        this.commands = new LinkedHashMap<>();
    }

    public void addCommand(Command c) {
        this.commands.put(c.getKey(), c);
    }

    private void printMenu() {
        System.out.println("Menu: ");
        for (Command c: this.commands.values()) {
            String line = String.format("%4s: %s", c.getKey(), c.getDescription());
            System.out.println(line);
        }
    }

    public void show() {
        Scanner scanner = new Scanner(System.in);
        while (true) {
            this.printMenu();
            System.out.print("Enter the option: ");
            String key = scanner.nextLine();
            Command currentCommand = this.commands.get(key);
            if (currentCommand == null) {
                System.out.println("Invalid option.");
                continue;
            }
            currentCommand.execute();
        }
    }
}
