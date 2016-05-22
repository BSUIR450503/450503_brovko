package application;

import javafx.scene.Parent;
import javafx.scene.control.Alert;
import javafx.scene.control.Button;
import javafx.scene.control.CheckBox;
import javafx.scene.control.Label;
import javafx.scene.layout.HBox;
import javafx.scene.layout.VBox;
import javafx.scene.text.Font;

import java.io.FileNotFoundException;
import java.io.FileOutputStream;
import java.io.IOException;
import java.util.Properties;

/**
 * This class creates all the elements of the UI
 */
public class MainMenu extends Parent {
  private VBox mainMenuVBox;
  private static int numberOfMenuItemBoxes = 9; //number of folder-button-extensions groups
  private HBox labelBox; // contains folder-button-extensions groups
  private static MenuItemBox[] menuItemBox; // folder-button-extensions group
  private static MenuItemBox defaultMenuItemBox;
  private static MenuItemBox sourceFolderBox;

  private Button moveButton;

  private Label sourcePathLabel;
  private Label pathLabel;
  private Label extensionLabel;

  private MainMenuBar menuBar;

  MainMenu() {
    super();

    Font f = Font.loadFont("file:res/Sawasdee-Bold.ttf", 16);
    menuBar = new MainMenuBar();

    menuItemBox = new MenuItemBox[numberOfMenuItemBoxes];

    mainMenuVBox = new VBox();
    mainMenuVBox.setTranslateX(20);
    mainMenuVBox.setTranslateY(50);
    mainMenuVBox.setSpacing(10);

    sourcePathLabel = new Label("Choose source directory");
    sourcePathLabel.setFont(f);
    sourceFolderBox = new MenuItemBox("");

    pathLabel = new Label("Path to destination folder:");
    pathLabel.setFont(f);
    extensionLabel = new Label("Extensions (for example: bmp, jpg, gif)");
    extensionLabel.setFont(f);
    labelBox = new HBox();
    labelBox.setSpacing(220);
    labelBox.getChildren().addAll(pathLabel, extensionLabel);

    mainMenuVBox.getChildren().addAll(sourcePathLabel, sourceFolderBox, labelBox);

    for (int i = 0; i < numberOfMenuItemBoxes; i++) {
      menuItemBox[i] = new MenuItemBox();
      mainMenuVBox.getChildren().addAll(menuItemBox[i]);
    }
    //one element with default text
    defaultMenuItemBox = new MenuItemBox("Other");

    mainMenuVBox.getChildren().addAll(defaultMenuItemBox);

    CheckBox checkBox = new CheckBox();
    checkBox.setText("leave all others in current folder");
    checkBox.setSelected(true);

    moveButton = new Button("Move");
    moveButton.setPrefSize(100, 20);

    moveButton.setOnAction(event -> {
      FileMover fileMover = new FileMover(menuItemBox, defaultMenuItemBox, sourceFolderBox);
      if (checkBox.isSelected()) {
        fileMover.move(1);
      } else {
        fileMover.move(0);
      }
    });

    mainMenuVBox.getChildren().addAll(checkBox, moveButton);
    loadFromConfig("config/default.conf");

    this.getChildren().addAll(menuBar, mainMenuVBox);
    this.setVisible(true);
  }

  /**
   * Loads data from config file to forms
   *
   * @param path to config file to load
   */
  public static void loadFromConfig(String path) {
    PropertyReader p = new PropertyReader();
    p.loadProperties(path);
    String SOURCE_PATH = p.getSourcePath();
    String[] DESTINATION_PATHS = p.getDestinationPaths();
    String[] DESTINATION_EXTENSIONS = p.getDestinationExtensions();
    String DEFAULT_DESTINATION_PATH = p.getDefaultDestinationPath();

    sourceFolderBox.setPathTextField(SOURCE_PATH);
    if (DESTINATION_PATHS.length == DESTINATION_EXTENSIONS.length) {
      for (int i = 0; i < DESTINATION_PATHS.length && i < numberOfMenuItemBoxes; i++) {
        menuItemBox[i].setExtensionsTextField(DESTINATION_EXTENSIONS[i]);
        menuItemBox[i].setPathTextField(DESTINATION_PATHS[i]);
      }
    } else {
      Alert alert = new Alert(Alert.AlertType.INFORMATION);
      alert.setTitle("Warning");
      alert.setHeaderText(null);
      alert.setContentText("Config was corrupted!\n");
      alert.show();
    }
    defaultMenuItemBox.setPathTextField(DEFAULT_DESTINATION_PATH);
  }

  /**
   * Saves data from forms to config file
   *
   * @param path to config file to save
   */
  public static void saveToConfig(String path) {
    FileOutputStream fileOutputStream = null;
    try {
      fileOutputStream = new FileOutputStream(path);
    } catch (FileNotFoundException e) {
      e.printStackTrace();
      return;
    }
    Properties prop = new Properties();
    prop.put("SOURCE_PATH", sourceFolderBox.getPath());

    try {
      prop.store(fileOutputStream, "Path to source folder");
      fileOutputStream.flush();
    } catch (IOException e) {
      e.printStackTrace();
    }

    Properties prop2 = new Properties();
    prop2.put("DEFAULT_DESTINATION_PATH", defaultMenuItemBox.getPath());
    try {
      prop2.store(fileOutputStream,
          "\n\n This one is for directory in which the program will move all"
              + " remaining files that was not replaced yet."
              + "You can also choose if you want to leave them in current folder or move\n"
              + " in setting of the program.");
      fileOutputStream.flush();
    } catch (IOException e) {
      e.printStackTrace();
    }

    Properties prop3 = new Properties();
    String paths = "";
    String extensions = "";

    for (MenuItemBox box : menuItemBox) {
      if (box.getPath().compareTo("") != 0) {
        paths += box.getPath() + ";";
        extensions += box.getExtensions() + ";";
      }
    }

    prop3.put("DESTINATION_PATH", paths);
    try {
      prop3.store(fileOutputStream,
          "\n\n  Paths to destination folders. Paths must be separated by semicolons.\n"
              + " Pay attention that the last one is also separated by semicolons.");
      fileOutputStream.flush();
    } catch (IOException e) {
      e.printStackTrace();
    }

    Properties prop4 = new Properties();
    prop4.put("DESTINATION_EXTENSIONS", extensions);
    try {
      prop4.store(fileOutputStream, "\n\nGroups of strings containing extensions.\n"
          + "Example: jpg png;txt doc;gif,mov; It doesn't matter how to separate in one group,\n"
          + " but groups must be separated by semicolons.\n"
          + " Pay attention that the last one is aslo separated by semicolons. ");
      fileOutputStream.flush();
      fileOutputStream.close();
    } catch (IOException e) {
      e.printStackTrace();
    }
  }
}
