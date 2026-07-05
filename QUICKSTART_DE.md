# ⚡ Schnellstart - 5 Minuten Setup (Windows)

## 📦 Was brauchst du?

1. **Visual Studio 2022** (kostenlos Community Edition)
   - Download: https://visualstudio.microsoft.com/vs/
   - Wähle: "Desktop development with C++"

2. **CMake** (oder wähle bei VS Install)
   - Download: https://cmake.org/download/

3. **VS Code** (optional, aber empfohlen)
   - Download: https://code.visualstudio.com/

## 🚀 Installation in 3 Schritten

### Schritt 1️⃣: Projekt-Dateien vorbereiten

Erstelle einen Ordner und kopiere folgende Dateien hinein:
```
C:\mein-projekt\
├── SubgraphAlgorithm.h
├── SubgraphAlgorithm.cpp
├── SubgraphTest.cpp
├── CMakeLists.txt
├── setup_and_run.ps1
└── README.md
```

### Schritt 2️⃣: PowerShell öffnen

1. Drücke `Win + X` → wähle "Windows PowerShell (Admin)"
   oder
2. Suche nach "PowerShell" → rechtsklick → "Als Administrator ausführen"

### Schritt 3️⃣: Berechtigungen & Script ausführen

Kopiere folgende Befehle in PowerShell:

```powershell
# Nur einmal: Ausführungsrichtlinie ändern
Set-ExecutionPolicy -ExecutionPolicy RemoteSigned -Scope CurrentUser

# Ins Projekt-Verzeichnis gehen
cd C:\pfad\zu\mein-projekt

# Script ausführen
.\setup_and_run.ps1
```

## ✅ Das wars!

Das Script macht alles automatisch:
- ✓ CMake konfiguriert
- ✓ C++ Code kompiliert
- ✓ 47 Tests ausgeführt
- ✓ HTML Report generiert

Am Ende siehst du eine Frage zum Öffnen des Reports:
```
HTML Report jetzt öffnen? (j/n): j
```

Dann öffnet sich automatisch der Report im Browser!

## 📊 Wo ist mein Report?

Nach dem Lauf findest du:
```
coverage_report/
└── coverage_report.html  ← Öffne diese Datei! 🎉
```

Einfach doppelklick und Browser öffnet automatisch.

## ❌ Fehler? Hier sind Lösungen:

### "PowerShell-Skript kann nicht ausgeführt werden"
→ Führe aus: `Set-ExecutionPolicy -ExecutionPolicy RemoteSigned -Scope CurrentUser`

### "CMake nicht gefunden"
→ Installiere Visual Studio 2022 mit C++ Workload erneut

### "MSVC-Compiler nicht gefunden"
→ Starte Visual Studio 2022 → Tools → Get Tools and Features → C++ Workload

### "OpenCppCoverage nicht installiert"
→ Das ist optional! Script läuft trotzdem, Report wird trotzdem generiert

### Tests schlagen fehl
→ Öffne `coverage\test_output.txt` für Details

## 🎯 Manuell ohne Script?

Falls das Script Probleme macht:

```powershell
# Build-Verzeichnis
mkdir build
cd build

# Konfigurieren
cmake -G "Visual Studio 17 2022" -A x64 ..

# Kompilieren
cmake --build . --config Debug

# Tests ausführen
.\Debug\subgraph_tests.exe
```

Sollte ausgeben:
```
[==========] 47 tests from 8 test suites ran.
[  PASSED  ] 47 tests.
```

## 🎓 Verständnis des Codes

### Was testet der Code?

Der **Subgraph-Algorithmus** vergleicht zwei Graphen:
- **Graph** = Netzwerk aus Knoten und Kanten
- **Adjazenzmatrix** = Tabelle von 0 und 1
- **Subgraph** = Ein Graph ist "in" einem anderen enthalten

### Beispiel:
```
Graph A:  1 → 2 → 3 → 4
          (Kette mit 4 Knoten)

Graph B:  1 → 2 → 3 → 4
          Plus eine Extra-Kante: 1 → 3
          (Kette + Extra)

Ergebnis: Graph A ist Subgraph von Graph B ✓
```

### Die 4 Funktionen

1. **calculateSignatures()** - Gibt jedem Knoten eine eindeutige Signatur
2. **computeLCS()** - Findet längste gemeinsame Sequenz
3. **rotateSequence()** - Dreht die Knoten-Anordnung
4. **compareGraphs()** - Vergleicht zwei Graphen (die Hauptfunktion!)

## 📖 Weitere Infos

Siehe `README.md` für:
- Detaillierte Algorithmus-Erklärung
- Komplexitätsanalyse
- Wissenschaftlichen Hintergrund
- Code-Beispiele

## 🆘 Noch Probleme?

1. **Fenster-Fehler**: VS 2022 nochmal installieren
2. **CMake-Fehler**: `cmake --version` in PowerShell testen
3. **Compilation-Fehler**: Header-Dateien (.h) und Implementation (.cpp) im gleichen Ordner?

## 🎉 Nächste Schritte

Nach erfolgreicher Ausführung:

1. **HTML Report anschauen** 📊
2. **Code modifizieren** und nochmal testen
3. **Neue Test-Cases schreiben** und Coverage verbessern
4. **Graphen selbst definieren** und vergleichen

Beispiel zum Ausprobieren:
```cpp
// In SubgraphTest.cpp:
TEST_F(GraphComparisonTest, MeinEigenerTest) {
    std::vector<std::vector<int>> g1{{0, 1}, {0, 0}};
    std::vector<std::vector<int>> g2{{0, 1}, {0, 0}};
    auto result = SubgraphAlgorithm::compareGraphs(g1, g2);
    EXPECT_EQ(result, SubgraphAlgorithm::Result::IDENTICAL);
}
```

Dann recompile mit:
```powershell
cd C:\pfad\zu\build
cmake --build . --config Debug
.\Debug\subgraph_tests.exe
```

---

**Du bist bereit! Viel Erfolg! 🚀**

Bei Fragen: Siehe README.md oder die Kommentare im Code.
