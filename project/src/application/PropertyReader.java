package application;

import java.io.FileReader;
import java.io.IOException;
import java.util.Properties;

/**
 * The class that loads properties form config file
 */
public class PropertyReader {

  private String SOURCE_PATH;
  private String[] DESTINATION_PATHS;
  private String[] DESTINATION_EXTENSIONS;
  private String DEFAULT_DESTINATION_PATH;

  PropertyReader() {}

  /**
   * Loads properties form config file
   *
   * @param pathToConfig to load
   */
  public void loadProperties(String pathToConfig) {
    Properties properties = new Properties();
    DESTINATION_PATHS = new String[10];
    DESTINATION_EXTENSIONS = new String[10];
    try {
      FileReader reader = new FileReader(pathToConfig);
      properties.load(reader);
    } catch (IOException e) {
      e.printStackTrace();
    }
    SOURCE_PATH = properties.getProperty("SOURCE_PATH");
    DESTINATION_PATHS = properties.getProperty("DESTINATION_PATHS").split(";");
    DESTINATION_EXTENSIONS = properties.getProperty("DESTINATION_EXTENSIONS").split(";");
    DEFAULT_DESTINATION_PATH = properties.getProperty("DEFAULT_DESTINATION_PATH");
  }

  public String getSourcePath() {
    return SOURCE_PATH;
  }

  public String[] getDestinationPaths() {
    return DESTINATION_PATHS;
  }

  public String[] getDestinationExtensions() {
    return DESTINATION_EXTENSIONS;
  }

  public String getDefaultDestinationPath() {
    return DEFAULT_DESTINATION_PATH;
  }
}
