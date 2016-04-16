package application;

import javafx.application.Application;
import javafx.stage.Stage;
import javafx.scene.Scene;
import javafx.scene.layout.BorderPane;

// TODO: add elements to menu bar, load fonts, create scroll panel and possibility to add more
// folders

/**
 * @author tatiana Main class
 */
public class Main extends Application {
  private final int SCREEC_HEIGTH = 800;
  private final int SCREEC_WIDTH = 600;

  @Override
  public void start(Stage primaryStage) {
    try {
      BorderPane root = new BorderPane();

      root.setPrefSize(SCREEC_HEIGTH, SCREEC_WIDTH);
      primaryStage.setResizable(false);
      primaryStage.setTitle("mmm");

      MainMenu menu = new MainMenu();
      root.getChildren().addAll(menu);
      Scene scene = new Scene(root);

      primaryStage.setScene(scene);
      primaryStage.show();
    } catch (NullPointerException e) {
      e.printStackTrace();
    } catch (Exception e) {
      e.printStackTrace();
    }
  }

  public static void main(String[] args) {
    launch(args);
  }
}
