package application;

import javafx.application.Application;
import javafx.stage.Stage;
import javafx.scene.Scene;
import javafx.scene.layout.BorderPane;


/**
 * Main class
 */
public class Main extends Application {

  @Override public void start(Stage primaryStage) {
    try {
      BorderPane root = new BorderPane();

      root.setPrefSize(800, 600);
      primaryStage.setResizable(false);
      primaryStage.setTitle("mmm");
      System.setProperty("prism.lcdtext", "false"); //makes fonts look better

      MainMenu menu = new MainMenu();
      root.getChildren().addAll(menu);
      Scene scene = new Scene(root);

      primaryStage.setScene(scene);
      primaryStage.show();
    } catch (NullPointerException e) {
      e.printStackTrace();
    }
  }

  public static void main(String[] args) {
    launch(args);
  }
}
