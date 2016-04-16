package application;

import javafx.application.Platform;
import javafx.scene.control.Menu;
import javafx.scene.control.MenuBar;
import javafx.scene.control.MenuItem;
import javafx.scene.control.SeparatorMenuItem;

public class MainMenuBar extends MenuBar {
  Menu menuFile;
  Menu menuAbout;

  MainMenuBar() {

    this.setPrefWidth(800);

    menuFile = new Menu("File");
    MenuItem loadMenuItem = new MenuItem("Load from config file");
    MenuItem saveMenuItem = new MenuItem("Save to config file");
    MenuItem exitMenuItem = new MenuItem("Exit");
    exitMenuItem.setOnAction(actionEvent -> Platform.exit());
    menuFile.getItems().addAll(loadMenuItem, saveMenuItem, new SeparatorMenuItem(), exitMenuItem);

    menuAbout = new Menu("About");
    MenuItem aboutMenuItem = new MenuItem("About");
    menuAbout.getItems().addAll(aboutMenuItem);

    this.getMenus().addAll(menuFile, menuAbout);
  }
}
