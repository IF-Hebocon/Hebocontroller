# Hebocontroller

## installation mit PowerShell
1. Projekt Klonen
2. ```powershell
    "src/", "examples/", "keywords.txt", "library.properties" | ForEach-Object { cp -r $($_) "build\$($_)" }
    ```
3. ```powershell
   Compress-Archive Hebocontroller -DestinationPath Hebocontroller.zip
   ```
4. Zip als Library in der ArduinoIDE hinzufügen. 
