# Hebocontroller

Hebocontroller ist die OpenSource Library der IF-Hebocon-Roboter.

## Installation in der ArduinoIDE

1. Releases in GitHub aufrufen -> https://github.com/IF-Hebocon/Hebocontroller/releases
2. Die `hebocon.zip` Datei des gewünschten Releases herunterladen
3. In der ArduinoIDE unter "Sketch -> Include Library -> Add .ZIP Library" die heruntergeladene `hebocon.zip` Datei
   Importieren.

---

## Verwendung der Beispielscripts

Nach dem Importieren der `hebocon.zip` Datei können in der ArduinoIDE Beispielscripte geladen werden.
Hierzu kann in der ArduinoIDE unter "File -> Examples -> Hebocontroller -> ESP32" der Beispielscript für das standard
ESP32 Board aus unserem Kit geladen werden.

### Nummer Vergeben

In dem Beispielscript kann in Zeile 3 dann die Nummer des Roboters angepasst werden.

```cpp
Hebobot hebobot("hebobot #1", 115200);
```

Hierzu muss lediglich die nummer in den Anführungsstrichen geändert werden.

---

## Verwendung des Steuerungsscripts

__Zurzeit werden nur Windows Rechner unterstützt!__

Für die Verwendung des Steuerungsscripts wird eine Python Installation benötigt.
Python kann auf der offiziellen Python Website heruntergeladen und anschließend installiert
werden: https://www.python.org/downloads/

### Installation des Steuerungsscripts unter Windows

#### 1. Repository Klonen oder Herunterladen

Zuerst muss das Repository heruntergeladen oder geklont werden:

- __Herunterladen__
    - Zum Herunterladen des Repos kann dieser Link verwendet
      werden: https://github.com/IF-Hebocon/Hebocontroller/archive/refs/heads/main.zip
    - Anschließend muss die Zip datei entpackt werden. Hierzu kann unter Windows ein Rechtsklick auf die Datei und
      das Auswählen des Menüpunkts "Alle extrahieren..." verwendet werden.
- __Klonen__
    - Zum Klonen des Repos muss Git installiert sein: https://git-scm.com/downloads
    - Anschließend kann das Repository in der Konsole mit dem
      Befehl `git clone https://github.com/IF-Hebocon/Hebocontroller.git` geklont werden.

#### 2. In den richtigen Ordner Navigieren

Um in den richtigen Ordner zu navigieren, muss in einer Konsole welche in dem Geklonten oder dem heruntergeladenen
Ordner eine Konsole gestartet werden und folgender Befehl ausgeführt werden:

```bash
cd controller
```

#### 3. Erstellen eines Virtual Environment für das Installieren der Pakete

```bash
python -m venv .venv
```

#### 4. Aktivieren des Virtual Environments

```bash
./.venv/Scripts/activate
```

#### 5. Installieren der Pakete

```bash
pip install -r requirements.txt
```

### Starten des Scripts

Um das Projekt zu starten, kann folgender Befehl verwendet werden:

```bash
python load.py <nummer> (*optional name)
```

