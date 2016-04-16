package application;

import java.io.File;
import javafx.event.ActionEvent;
import javafx.event.EventHandler;
import javafx.scene.control.Button;
import javafx.scene.control.TextField;
import javafx.scene.layout.HBox;
import javafx.stage.DirectoryChooser;

/**
 * This class creates group of elements that contains text field for path to destination, button
 * that opens file chooser and text field for file extension
 */
public class MenuItemBox extends HBox {

  private Button button;
  private TextField pathTextField;
  private TextField extensionsTextField;

  /**
   * This constructor creates with empty fields
   */
  MenuItemBox() {
    super();
    initialize();
  }

  /**
   * This constructor creates with default fields
   */
  MenuItemBox(String mode) {
    super();
    initialize();
    extensionsTextField.setText(mode);
  }

  /**
   * This functuin initializes the object
   */
  private void initialize() {
    this.setSpacing(10);

    pathTextField = new TextField();
    pathTextField.setPrefSize(360, 20);

    button = new Button();
    button.setPrefSize(25, 20);

    extensionsTextField = new TextField();
    extensionsTextField.setPrefSize(350, 20);

    button.setOnAction(new EventHandler<ActionEvent>() {
      @Override
      public void handle(ActionEvent e) {
        DirectoryChooser chooser = new DirectoryChooser();
        File file;
        file = chooser.showDialog(null);
        pathTextField.setText(file.getAbsoluteFile().toString());
      }
    });
    getChildren().addAll(pathTextField, button, extensionsTextField);
  }
}
