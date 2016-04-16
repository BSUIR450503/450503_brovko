package application;

import javafx.scene.Parent;
import javafx.scene.control.Button;
import javafx.scene.control.CheckBox;
import javafx.scene.control.Label;
import javafx.scene.layout.HBox;
import javafx.scene.layout.VBox;

/**
 * @author tatiana
 * This class creates all the elements of the UI
 */
public class MainMenu extends Parent {
  private VBox mainMenuVBox;
  private int numberOfMenuItemBoxes; //number of folder-button-extensions groups
  private HBox labelBox; // contains folder-button-extensions groups
  private MenuItemBox[] menuItemBox; // folder-button-extensions group
  private MenuItemBox sourseFolderBox;
  private Button moveButton;
  private Label soursePathLabel;
  private Label pathLabel;
  private Label extentionLabel;
  private MainMenuBar menuBar;

  MainMenu() {
    super();
    numberOfMenuItemBoxes = 10;
    menuBar = new MainMenuBar();

    menuItemBox = new MenuItemBox[numberOfMenuItemBoxes];

    mainMenuVBox = new VBox();
    mainMenuVBox.setTranslateX(20);
    mainMenuVBox.setTranslateY(50);
    mainMenuVBox.setSpacing(10);
    
    soursePathLabel = new Label("Choose sourse directory");
    sourseFolderBox = new MenuItemBox("");

    pathLabel = new Label("Path to destinition folder:");
    extentionLabel = new Label("Extentions (for example: bmp, jpg, gif)");

    labelBox = new HBox();
    labelBox.setSpacing(250);
    labelBox.getChildren().addAll(pathLabel, extentionLabel);

    mainMenuVBox.getChildren().addAll(soursePathLabel, sourseFolderBox, labelBox);
    
    for (int i = 0; i < numberOfMenuItemBoxes - 1; i++) {
      menuItemBox[i] = new MenuItemBox();
      mainMenuVBox.getChildren().addAll(menuItemBox[i]);
    }
    //one element with default text
    menuItemBox[numberOfMenuItemBoxes - 1] = new MenuItemBox("Other");
    
    mainMenuVBox.getChildren().addAll(menuItemBox[numberOfMenuItemBoxes - 1]);

    moveButton = new Button("Move");
    moveButton.setPrefSize(100, 20);

    CheckBox checkBox = new CheckBox();
    checkBox.setText("leave all others in current folder");
    checkBox.setSelected(true);

    mainMenuVBox.getChildren().addAll(checkBox, moveButton);

    this.getChildren().addAll(menuBar, mainMenuVBox);
    this.setVisible(true);
  }
}
