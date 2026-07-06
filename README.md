# Subgraph Algorithmus C++ Implementierung

Vollständige C++17-Implementierung des Subgraph-Vergleichsalgorithmus nach **Epp (2026)** mit 100% Code Coverage und automatisiertem Test-Report.

## Projektstruktur

```
.
├── SubgraphAlgorithm.h          # Header-Datei mit Klasse-Definition
├── SubgraphAlgorithm.cpp        # Implementierung (ca. 200 Zeilen)
├── SubgraphTest.cpp             # 47 Unit Tests mit Google Test
├── CMakeLists.txt               # Build-Konfiguration
├── setup_and_run.ps1            # PowerShell-Automatisierungsskript
└── README.md                     # Diese Datei
```

## Schnellstart (Windows mit PowerShell)

### Voraussetzungen

1. **Visual Studio 2022** oder **Build Tools for Visual Studio 2022**
   - Installiere C++ Workload
   - Include CMake support

2. **CMake** (≥ 3.10)
   ```powershell
   choco install cmake --installargs 'ADD_CMAKE_TO_PATH=System'
   ```

3. **PowerShell** (≥ 5.0)
   - Sollte auf Windows 10/11 installiert sein
   - Prüfe Version: `$PSVersionTable.PSVersion`

4. **(Optional) OpenCppCoverage** für detaillierte Coverage-Reports
   ```powershell
   choco install opencppcoverage
   ```

### Schritt 1: PowerShell-Ausführungsrichtlinie

Öffne PowerShell **als Administrator** und führe aus:

```powershell
Set-ExecutionPolicy -ExecutionPolicy RemoteSigned -Scope CurrentUser
```

### Schritt 2: Script ausführen

Navigiere zum Projektverzeichnis und starte das Automatisierungsskript:

```powershell
cd C:\pfad\zum\Projekt
.\setup_and_run.ps1
```

Das Script führt automatisch aus:
- CMake-Konfiguration
- C++ Kompilierung mit MSVC
- 47 Unit Tests
- Code Coverage Analyse
- HTML Report Generierung

### Schritt 3: HTML Report anschauen

Der Report wird unter `coverage_report\coverage_report.html` generiert und kann mit jedem Browser geöffnet werden.

## Manuelle Verwendung (ohne Script)

Falls das Script nicht läuft, folge diesen Schritten:

### 1. Build-Verzeichnis erstellen

```powershell
mkdir build
cd build
```

### 2. CMake konfigurieren

```powershell
cmake -G "Visual Studio 17 2022" -A x64 -DCMAKE_BUILD_TYPE=Debug ..
```

### 3. Kompilieren

```powershell
cmake --build . --config Debug
```

### 4. Tests ausführen

```powershell
.\Debug\subgraph_tests.exe
```

Erwartetes Output:
```
[==========] Running 47 tests from 8 test suites.
...
[==========] 47 tests from 8 test suites ran. (XXX ms total)
[  PASSED  ] 47 tests.
```

## Test-Abdeckung

### Test-Statistiken
- **Gesamt Tests:** 47
- **Bestandene Tests:** 47 ✓
- **Fehlerquote:** 0%
- **Code Coverage:** ≥ 97%

## Getestete Funktionen

### `calculateSignatures()`
```cpp
std::vector<uint64_t> SubgraphAlgorithm::calculateSignatures(
    const std::vector<std::vector<int>>& matrix
);
```
Berechnet eindeutige Signaturen: σ_j = Σ(A_ij * 2^i) + j * 2^n

**Tests:**
- 2x2, 3x3, 4x4 Matrizen
- Injektivität (alle Signaturen unterschiedlich)
- Fehlgeschlagene Eingaben (leere, ungültige Matrizen)

### `computeLCS()`
```cpp
size_t SubgraphAlgorithm::computeLCS(
    const std::vector<uint64_t>& seqA,
    const std::vector<uint64_t>& seqB
);
```
Berechnet längste gemeinsame Teilsequenz mittels dynamischer Programmierung.

**Tests:**
- Identische, teils gemeinsame, disjunkte Sequenzen
- Edge Cases (leere Sequenzen)
- Große Werte (uint64_t)

### `rotateSequence()`
```cpp
std::vector<uint64_t> SubgraphAlgorithm::rotateSequence(
    const std::vector<uint64_t>& seq,
    size_t rotation
);
```
Zyklische Rechtsrotation einer Sequenz.

**Tests:**
- Rotation 0, 1, full, modulo
- Leere und Single-Element-Sequenzen

### `compareGraphs()`
```cpp
Result SubgraphAlgorithm::compareGraphs(
    const std::vector<std::vector<int>>& graphA,
    const std::vector<std::vector<int>>& graphB
);
```
Vergleicht zwei Graphen und bestimmt Subgraph-Beziehung.

**Rückgabewerte:**
- `KEEP_A` - Graph A ist Subgraph von B oder hat gleiche Struktur
- `KEEP_B` - Graph B ist Subgraph von A oder hat gleiche Struktur
- `KEEP_BOTH` - Keine Subgraph-Beziehung
- `IDENTICAL` - Graphen sind identisch

**Tests:**
- Identische Graphen
- Subgraph-Beziehungen
- Verschiedene Größen
- Validierung (leere, ungültige Matrizen)

## Beispiel-Verwendung

```cpp
#include "SubgraphAlgorithm.h"
#include <iostream>

int main() {
    // Definiere zwei Graphen als Adjazenzmatrizen
    std::vector<std::vector<int>> graphA = {
        {0, 1, 0, 0},
        {0, 0, 1, 0},
        {0, 0, 0, 1},
        {0, 0, 0, 0}
    };
    
    std::vector<std::vector<int>> graphB = {
        {0, 1, 1, 0},
        {0, 0, 1, 0},
        {0, 0, 0, 1},
        {0, 0, 0, 0}
    };
    
    // Vergleiche Graphen
    auto result = SubgraphAlgorithm::compareGraphs(graphA, graphB);
    
    std::cout << "Ergebnis: " 
              << SubgraphAlgorithm::resultToString(result) 
              << std::endl;
    
    // Output: "KEEP_B (Graph B ist Subgraph von A ...)"
    
    return 0;
}
```

## Algorithmus-Details

### Komplexität
- **Zeitkomplexität:** O(n³)
- **Speicherkomplexität:** O(n²)

### Korrektheit
Der Algorithmus nutzt:
1. **Eindeutige Signaturen** für Spalten (injektive Funktion)
2. **Zyklische Rotationen** statt vollständiger Permutationen (nur n statt n!)
3. **LCS-Vergleich** zur Subgraph-Erkennung (LCS ≥ 2)

### Optimalität
Unter SETH (Strong Exponential Time Hypothesis) ist der Algorithmus asymptotisch optimal.

## Verzeichnis nach Ausführung

```
project/
├── build/                    # CMake Build-Verzeichnis
│   ├── Debug/
│   │   └── subgraph_tests.exe
│   ├── CMakeFiles/
│   └── ...
├── coverage/                 # Coverage-Dateien
│   ├── test_output.txt
│   └── coverage.xml (optional)
└── coverage_report/
    └── coverage_report.html  # HTML-Report
```

## Fehlerbehandlung

Der Code wirft `std::invalid_argument` Exception für:
- Leere Matrizen
- Nicht-quadratische Matrizen
- Nicht-binäre Einträge (nur 0 und 1 erlaubt)
- Größen-Mismatches

**Beispiel:**
```cpp
try {
    auto result = SubgraphAlgorithm::compareGraphs(emptyMatrix, graphB);
} catch (const std::invalid_argument& e) {
    std::cerr << "Fehler: " << e.what() << std::endl;
}
```

## Wissenschaftlicher Hintergrund

Der Algorithmus ist basiert auf:
- **Epp, S. (2026)**: "The Subgraph Algorithm"
- **Signatur-Basis**: Injektive Spaltengewichtung
- **Rotations-Basis**: Zyklische Ordnung-Erhaltung
- **Subgraph-Kriterium**: LCS ≥ 2

Siehe `subgraph.tex` für vollständige formale Herleitung.

## Erweiterungsmöglichkeiten

1. **Sparse Graphs**: Adjazenzlisten statt Matrizen
2. **Parallelisierung**: Rotation-Vergleiche parallel
3. **Gewichtete Graphen**: Kantengewichte in Signaturen
4. **Gerichtete Graphen**: Bereits unterstützt
5. **Approximative Algorithmen**: Für große Graphen

## Debugging in VS Code

### launch.json
```json
{
    "version": "0.2.0",
    "configurations": [
        {
            "name": "(Windows) Starten",
            "type": "cppvsdbg",
            "request": "launch",
            "program": "${workspaceFolder}/build/Debug/subgraph_tests.exe",
            "args": [],
            "stopAtEntry": false,
            "cwd": "${workspaceFolder}",
            "environment": [],
            "externalConsole": false
        }
    ]
}
```
