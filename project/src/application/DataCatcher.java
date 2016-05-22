package application;

import javafx.scene.control.Alert;

import java.io.File;
import java.util.LinkedHashMap;
import java.util.Map;

/**
 * The class that gets data from forms
 */
public class DataCatcher {

  LinkedHashMap<File, String> map;
  Alert alert = new Alert(Alert.AlertType.INFORMATION);

  DataCatcher() {
    map = new LinkedHashMap<>();
  }

  /**
   * Gets destination paths and extensions
   *
   * @return LinkedHashMap containing entries of destination File and String of extensions
   */
  LinkedHashMap<File, String> readDestPathsAndExtensions(MenuItemBox[] menuItemBoxes) {
    map.clear();

    for (MenuItemBox box : menuItemBoxes) {
      if (box.getPath().compareTo("") != 0) {
        map.put(new File(box.getPath()), box.getExtensions());
        System.out.println(box.getPath() + " " + box.getExtensions() + "\n");
      }
    }

    for (Map.Entry<File, String> entry : map.entrySet()) {
      if (!entry.getKey().exists() && entry.getKey().getPath().compareTo("") != 0) {
        alert.setTitle("Warning");
        alert.setHeaderText(null);
        alert.setContentText(
            "Path " + entry.getKey().getPath() + " does not exists! Will be ignored.");
        alert.showAndWait();
      }
    }
    return map;
  }

  /**
   * Gets source paths
   *
   * @return File
   */
  public File readSourcePath(MenuItemBox sourceFolderBox) {
    return new File(sourceFolderBox.getPath());
  }

  /**
   * Gets default paths
   *
   * @return File
   */
  public File readDefaultDestPath(MenuItemBox defaultDestFolder) {
    return new File(defaultDestFolder.getPath());
  }
}
