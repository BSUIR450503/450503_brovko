package application;

import javafx.scene.control.Alert;

import java.io.File;
import java.util.LinkedHashMap;
import java.util.Map;

/**
 * The class that moves files
 */
public class FileMover {
  DataCatcher dataCatcher;
  MenuItemBox[] menuItemBoxes;
  MenuItemBox sourceFolderBox;
  MenuItemBox defaultMenuItemBox;
  LinkedHashMap<File, String> destinationPathsMap;
  File sourcePath;
  File defaultFolder;
  File[] filesInSourceFolder;
  Alert alert;

  FileMover(MenuItemBox[] menuItemBoxes, MenuItemBox defaultMenuItemBox,
      MenuItemBox sourceFolderBox) {
    this.sourceFolderBox = sourceFolderBox;
    dataCatcher = new DataCatcher();
    destinationPathsMap = new LinkedHashMap<>();
    this.menuItemBoxes = menuItemBoxes;
    this.defaultMenuItemBox = defaultMenuItemBox;
    alert = new Alert(Alert.AlertType.INFORMATION);
  }

  /**
   * Gets data from forms
   */
  public void readFromForms() {
    destinationPathsMap = dataCatcher.readDestPathsAndExtensions(menuItemBoxes);
    sourcePath = dataCatcher.readSourcePath(sourceFolderBox);
    defaultFolder = dataCatcher.readDefaultDestPath(defaultMenuItemBox);
  }

  /**
   * Moves files
   *
   * @param mode = 0 if user want to move other files to default folder
   */
  public void move(int mode) {
    readFromForms();
    filesInSourceFolder = sourcePath.listFiles();
    if (filesInSourceFolder != null) {

      for (File fileToMove : filesInSourceFolder) {
        if (fileToMove.isFile() && fileToMove.exists()) {

          for (Map.Entry<File, String> entry : destinationPathsMap.entrySet()) {
            if (entry.getValue().contains(getFileExtension(fileToMove))
                && getFileExtension(fileToMove).compareTo("") != 0) {
              if (entry.getKey().exists()) {
                moveFileToPath(fileToMove, entry.getKey());
                break;
              }
            }
          }

        }
      }

      // if user want to move other files to default folder
      if (mode == 0) {
        filesInSourceFolder = sourcePath.listFiles();
        for (File fileToMove : filesInSourceFolder) {
          System.out.println(fileToMove.getPath() + "\n");
          if (fileToMove.isFile() && fileToMove.exists()) {
            moveFileToPath(fileToMove, defaultFolder);
          }
        }
      }
      alert.setTitle("");
      alert.setHeaderText(null);
      alert.setContentText("Done successful!");
    } else {
      alert.setTitle("Warning!");
      alert.setHeaderText(null);
      alert.setContentText("Empty source folder!");
    }
    alert.show();
  }

  /**
   * Moves one file to path
   *
   * @param file        to move
   * @param destination to move file
   */
  void moveFileToPath(File file, File destination) {
    if (destination.isDirectory()) {
      if (!file.renameTo(new File(destination, file.getName()))) {
        alert.setTitle("Warning");
        alert.setContentText("Cannot move " + file.getPath() + "\n");
        alert.show();
      }
    } else {
      alert.setTitle("Warning");
      alert.setContentText("Destination file is not a directory!");
      alert.show();
    }
  }

  /**
   * Gets file extension from file name
   *
   * @param file to get extension
   * @return String extension
   */
  private static String getFileExtension(File file) {
    String fileName = file.getName();
    // если есть точка и она не первый символ в названии
    if (fileName.lastIndexOf(".") != -1 && fileName.lastIndexOf(".") != 0)
      // то ХХХХХ.txt -> txt
      return fileName.substring(fileName.lastIndexOf(".") + 1);
      // в противном случае расширение не найдено
    else
      return "empty";
  }
}
