package application;

import javafx.application.Platform;
import javafx.scene.control.*;
import javafx.stage.FileChooser;

import java.io.File;
import java.io.IOException;

/**
 * The class is responsible for the menu bar in main menu
 */
public class MainMenuBar extends MenuBar {
  Menu menuFile;
  Menu menuAbout;

  MainMenuBar() {
    this.setPrefWidth(800);
    menuFile = new Menu("File");
    MenuItem loadMenuBarItem = new MenuItem("Load from config file");
    MenuItem saveMenuBarItem = new MenuItem("Save to config file");
    MenuItem exitMenuBarItem = new MenuItem("Exit");

    exitMenuBarItem.setOnAction(actionEvent -> Platform.exit());

    loadMenuBarItem.setOnAction(actionEvent -> {
      FileChooser chooser = new FileChooser();
      File configFile;
      configFile = chooser.showOpenDialog(null);
      if (configFile != null && configFile.isFile()) {
        MainMenu.loadFromConfig(configFile.getPath());
      }
    });

    saveMenuBarItem.setOnAction(event -> {
      FileChooser chooser = new FileChooser();
      File file;
      file = chooser.showSaveDialog(null);
      if (file != null) {
        try {
          file.createNewFile();
        } catch (IOException e) {
          e.printStackTrace();
        }
        MainMenu.saveToConfig(file.getPath());
      }
    });

    menuFile.getItems()
        .addAll(loadMenuBarItem, saveMenuBarItem, new SeparatorMenuItem(), exitMenuBarItem);

    menuAbout = new Menu("About");
    MenuItem aboutMenuItem = new MenuItem("About");

    aboutMenuItem.setOnAction(event -> {
      Alert alert = new Alert(Alert.AlertType.INFORMATION);
      alert.setTitle("About");
      alert.getDialogPane().setPrefSize(580, 400);
      alert.setHeaderText("Information about the program\n\n\n");

      String info;
      info = "This program helps you to sort your files.\n" +
          "You can load settings from config file and save your settings to file.\n\n" +
          "If you want to move file with no extension, write \"empty\" in extensions field.";
      alert.setContentText(info);
      alert.showAndWait();
    });
    menuAbout.getItems().addAll(aboutMenuItem);
    this.getMenus().addAll(menuFile, menuAbout);
  }
}
