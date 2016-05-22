package application;

import java.io.File;

import javafx.scene.control.Button;
import javafx.scene.control.Label;
import javafx.scene.control.TextField;
import javafx.scene.layout.HBox;
import javafx.stage.DirectoryChooser;

/**
 * This class creates group of elements that contains text field for path to destination, button
 * that opens file chooser and text field for file extension
 */
public class MenuItemBox extends HBox {

  private Button moveButton;
  private TextField pathTextField;
  private TextField extensionsTextField;

  /**
   * This constructor creates element with empty fields
   */
  public MenuItemBox() {
    super();
    initialize();
    getChildren().addAll(pathTextField, moveButton, extensionsTextField);
  }

  /**
   * This constructor creates element with one default field when we don't need field for extensions
   *
   * @param mode string that will added to label
   */
  public MenuItemBox(String mode) {
    super();
    initialize();
    Label modeLabel = new Label(mode);
    modeLabel.setPrefHeight(25);
    getChildren().addAll(pathTextField, moveButton, modeLabel);
  }

  /**
   * This function initializes the object
   */
  private void initialize() {
    this.setSpacing(10);

    pathTextField = new TextField();
    pathTextField.setPrefSize(360, 20);

    moveButton = new Button();
    moveButton.setPrefSize(25, 20);

    extensionsTextField = new TextField();
    extensionsTextField.setPrefSize(350, 20);

    moveButton.setOnAction(event -> {
      DirectoryChooser chooser = new DirectoryChooser();
      File file;
      file = chooser.showDialog(null);
      pathTextField.setText(file.getAbsoluteFile().toString());
    });
  }

  public String getPath() {
    return pathTextField.getText();
  }

  public String getExtensions() {
    return extensionsTextField.getText();
  }

  public void setPathTextField(String string) {
    this.pathTextField.setText(string);
  }

  public void setExtensionsTextField(String string) {
    this.extensionsTextField.setText(string);
  }
}
