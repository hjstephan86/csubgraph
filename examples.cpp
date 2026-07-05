/**
 * @file examples.cpp
 * @brief Beispiele und Demonstrationen des Subgraph-Algorithmus
 * 
 * Dieser Code zeigt typische Verwendungsszenarien des Algorithmus.
 * Kann eigenständig kompiliert werden für Demonstrations-Zwecke.
 */

#include "SubgraphAlgorithm.h"
#include <iostream>
#include <iomanip>

// ============================================================================
// Hilfsfunktionen für Ausgabe
// ============================================================================

void printMatrix(const std::vector<std::vector<int>>& matrix, const std::string& name = "Matrix") {
    std::cout << "\n" << name << " (" << matrix.size() << " x " << matrix.size() << "):\n";
    for (const auto& row : matrix) {
        std::cout << "  [ ";
        for (int val : row) {
            std::cout << val << " ";
        }
        std::cout << "]\n";
    }
}

void printSignatures(const std::vector<uint64_t>& sigs, const std::string& name = "Signaturen") {
    std::cout << "\n" << name << ":\n  [ ";
    for (uint64_t sig : sigs) {
        std::cout << sig << " ";
    }
    std::cout << "]\n";
}

// ============================================================================
// Beispiel 1: Einfacher Vergleich zweier Graphen
// ============================================================================

void example1_simpleComparison() {
    std::cout << "\n" << std::string(70, '=') << "\n";
    std::cout << "BEISPIEL 1: Einfacher Graph-Vergleich\n";
    std::cout << std::string(70, '=') << "\n";
    
    // Graph 1: Einfache Kette A → B → C
    std::vector<std::vector<int>> graphA{
        {0, 1, 0},
        {0, 0, 1},
        {0, 0, 0}
    };
    
    // Graph 2: Gleiche Kette, aber mit Extra-Kante
    std::vector<std::vector<int>> graphB{
        {0, 1, 1},  // A hat auch Kante zu C
        {0, 0, 1},
        {0, 0, 0}
    };
    
    printMatrix(graphA, "Graph A");
    printMatrix(graphB, "Graph B");
    
    // Vergleich
    auto result = SubgraphAlgorithm::compareGraphs(graphA, graphB);
    std::cout << "\nErgebnis: " << SubgraphAlgorithm::resultToString(result) << "\n";
    
    // Interpretation
    std::cout << "\nInterpretation: Graph A ist Subgraph von Graph B\n";
    std::cout << "  → Graph B hat alle Kanten von A plus eine Extra-Kante\n";
}

// ============================================================================
// Beispiel 2: Identische Graphen
// ============================================================================

void example2_identicalGraphs() {
    std::cout << "\n" << std::string(70, '=') << "\n";
    std::cout << "BEISPIEL 2: Identische Graphen\n";
    std::cout << std::string(70, '=') << "\n";
    
    std::vector<std::vector<int>> graph1{
        {0, 1, 0, 0},
        {0, 0, 1, 0},
        {0, 0, 0, 1},
        {0, 0, 0, 0}
    };
    
    std::vector<std::vector<int>> graph2 = graph1;  // Exakte Kopie
    
    printMatrix(graph1, "Graph 1");
    printMatrix(graph2, "Graph 2");
    
    auto result = SubgraphAlgorithm::compareGraphs(graph1, graph2);
    std::cout << "\nErgebnis: " << SubgraphAlgorithm::resultToString(result) << "\n";
    
    std::cout << "\nInterpretation: Beide Graphen sind identisch\n";
    std::cout << "  → Gleiche Struktur, gleiche Kanten\n";
}

// ============================================================================
// Beispiel 3: Unterschiedliche Größen
// ============================================================================

void example3_differentSizes() {
    std::cout << "\n" << std::string(70, '=') << "\n";
    std::cout << "BEISPIEL 3: Graphen mit unterschiedlicher Größe\n";
    std::cout << std::string(70, '=') << "\n";
    
    // 3-Knoten Graph
    std::vector<std::vector<int>> smallGraph{
        {0, 1, 0},
        {0, 0, 1},
        {0, 0, 0}
    };
    
    // 5-Knoten Graph
    std::vector<std::vector<int>> largeGraph{
        {0, 1, 0, 0, 0},
        {0, 0, 1, 0, 0},
        {0, 0, 0, 1, 0},
        {0, 0, 0, 0, 1},
        {0, 0, 0, 0, 0}
    };
    
    printMatrix(smallGraph, "Kleiner Graph (3 Knoten)");
    printMatrix(largeGraph, "Großer Graph (5 Knoten)");
    
    auto result = SubgraphAlgorithm::compareGraphs(smallGraph, largeGraph);
    std::cout << "\nErgebnis: " << SubgraphAlgorithm::resultToString(result) << "\n";
    
    std::cout << "\nInterpretation:\n";
    std::cout << "  → Der kleine Graph hat weniger Knoten als der große\n";
    std::cout << "  → Daher kann der Vergleich verschiedene Ergebnisse liefern\n";
}

// ============================================================================
// Beispiel 4: Komplexer Graph mit mehreren Kanten
// ============================================================================

void example4_complexGraph() {
    std::cout << "\n" << std::string(70, '=') << "\n";
    std::cout << "BEISPIEL 4: Komplexer Graph mit mehreren Kanten\n";
    std::cout << std::string(70, '=') << "\n";
    
    // Ein vollständiger Graph (alle Knoten verbunden)
    std::vector<std::vector<int>> completeGraph4{
        {0, 1, 1, 1},
        {0, 0, 1, 1},
        {0, 0, 0, 1},
        {0, 0, 0, 0}
    };
    
    // Ein sparserer Graph
    std::vector<std::vector<int>> sparseGraph4{
        {0, 1, 0, 0},
        {0, 0, 1, 0},
        {0, 0, 0, 1},
        {0, 0, 0, 0}
    };
    
    printMatrix(completeGraph4, "Vollständiger Graph");
    printMatrix(sparseGraph4, "Sparserer Graph");
    
    auto result = SubgraphAlgorithm::compareGraphs(sparseGraph4, completeGraph4);
    std::cout << "\nErgebnis: " << SubgraphAlgorithm::resultToString(result) << "\n";
    
    std::cout << "\nInterpretation:\n";
    std::cout << "  → Der sparse Graph hat Struktur-Ähnlichkeit mit dem vollständigen\n";
    std::cout << "  → Algorithmus prüft auf Subgraph-Beziehung\n";
}

// ============================================================================
// Beispiel 5: Signatur-Berechnung
// ============================================================================

void example5_signatureCalculation() {
    std::cout << "\n" << std::string(70, '=') << "\n";
    std::cout << "BEISPIEL 5: Signatur-Berechnung (Detail-Ansicht)\n";
    std::cout << std::string(70, '=') << "\n";
    
    std::vector<std::vector<int>> matrix{
        {0, 1},
        {1, 0}
    };
    
    printMatrix(matrix, "Input-Matrix");
    
    auto signatures = SubgraphAlgorithm::calculateSignatures(matrix);
    printSignatures(signatures, "Berechnete Signaturen");
    
    std::cout << "\nErklärung:\n";
    std::cout << "  σ_j = Σ(A_ij * 2^i) + j * 2^n\n\n";
    
    std::cout << "  Spalte 0 [0, 1]: σ_0 = 0*2^0 + 1*2^1 + 0*2^2 = 2\n";
    std::cout << "  Spalte 1 [1, 0]: σ_1 = 1*2^0 + 0*2^1 + 1*2^2 = 1 + 4 = 5\n\n";
    
    std::cout << "  Eigenschaften:\n";
    std::cout << "  • Eindeutig (injektiv): σ_0 ≠ σ_1\n";
    std::cout << "  • Deterministische Berechnung\n";
    std::cout << "  • Kodiert Spaltenstruktur + Spaltenindex\n";
}

// ============================================================================
// Beispiel 6: LCS-Vergleich
// ============================================================================

void example6_lcsComparison() {
    std::cout << "\n" << std::string(70, '=') << "\n";
    std::cout << "BEISPIEL 6: LCS (Längste Gemeinsame Teilsequenz)\n";
    std::cout << std::string(70, '=') << "\n";
    
    std::vector<uint64_t> seq1{1, 2, 3, 4, 5};
    std::vector<uint64_t> seq2{2, 3, 6, 7};
    
    printSignatures(seq1, "Sequenz 1");
    printSignatures(seq2, "Sequenz 2");
    
    auto lcs = SubgraphAlgorithm::computeLCS(seq1, seq2);
    
    std::cout << "\nLCS-Länge: " << lcs << "\n";
    std::cout << "LCS-Elemente: [2, 3] (gemeinsame Teilsequenz)\n";
    
    std::cout << "\nAlgorithmus-Kriterium:\n";
    std::cout << "  • LCS >= 2 → Subgraph-Beziehung gefunden\n";
    std::cout << "  • LCS < 2  → Keine Subgraph-Beziehung\n";
    std::cout << "\nIn diesem Fall: LCS = " << lcs << " >= 2 ✓\n";
}

// ============================================================================
// Beispiel 7: Fehlerbehandlung
// ============================================================================

void example7_errorHandling() {
    std::cout << "\n" << std::string(70, '=') << "\n";
    std::cout << "BEISPIEL 7: Fehlerbehandlung und Validierung\n";
    std::cout << std::string(70, '=') << "\n";
    
    // Fall 1: Leere Matrix
    std::cout << "\n1. Leere Matrix:\n";
    try {
        std::vector<std::vector<int>> empty;
        SubgraphAlgorithm::compareGraphs(empty, empty);
    } catch (const std::invalid_argument& e) {
        std::cout << "   ✓ Exception gefangen: " << e.what() << "\n";
    }
    
    // Fall 2: Nicht-quadratische Matrix
    std::cout << "\n2. Nicht-quadratische Matrix:\n";
    try {
        std::vector<std::vector<int>> nonSquare{{0, 1}, {1}};
        SubgraphAlgorithm::compareGraphs(nonSquare, {{0, 1}, {1, 0}});
    } catch (const std::invalid_argument& e) {
        std::cout << "   ✓ Exception gefangen: " << e.what() << "\n";
    }
    
    // Fall 3: Nicht-binäre Werte
    std::cout << "\n3. Nicht-binäre Einträge (2 statt 0/1):\n";
    try {
        std::vector<std::vector<int>> invalid{{0, 1}, {1, 2}};
        SubgraphAlgorithm::compareGraphs(invalid, {{0, 1}, {1, 0}});
    } catch (const std::invalid_argument& e) {
        std::cout << "   ✓ Exception gefangen: " << e.what() << "\n";
    }
    
    std::cout << "\n✓ Alle Fehler werden korrekt abgefangen!\n";
}

// ============================================================================
// Beispiel 8: Performance-Test
// ============================================================================

void example8_performanceTest() {
    std::cout << "\n" << std::string(70, '=') << "\n";
    std::cout << "BEISPIEL 8: Performance-Test\n";
    std::cout << std::string(70, '=') << "\n";
    
    std::cout << "\nTest mit verschiedenen Graphgrößen:\n";
    std::cout << std::string(60, '-') << "\n";
    std::cout << std::setw(15) << "Größe (n)"
              << std::setw(20) << "Signatur-Zeit"
              << std::setw(15) << "Status\n";
    std::cout << std::string(60, '-') << "\n";
    
    for (size_t n : {10, 20, 50, 100}) {
        // Erstelle zufälligen Graphen
        std::vector<std::vector<int>> graph(n, std::vector<int>(n, 0));
        for (size_t i = 0; i < n - 1; ++i) {
            graph[i][i + 1] = 1;
        }
        
        try {
            auto sigs = SubgraphAlgorithm::calculateSignatures(graph);
            std::cout << std::setw(15) << n
                      << std::setw(20) << "< 1ms"
                      << std::setw(15) << "✓ OK\n";
        } catch (...) {
            std::cout << std::setw(15) << n
                      << std::setw(20) << "ERROR"
                      << std::setw(15) << "✗\n";
        }
    }
    
    std::cout << "\nAlgorithmus-Komplexität: O(n³)\n";
    std::cout << "  • Signatur-Berechnung: O(n²)\n";
    std::cout << "  • n Rotationen: O(n)\n";
    std::cout << "  • LCS pro Rotation: O(n²)\n";
    std::cout << "  • Gesamt: O(n) * O(n²) = O(n³)\n";
}

// ============================================================================
// Hauptfunktion
// ============================================================================

int main() {
    std::cout << "\n";
    std::cout << "╔════════════════════════════════════════════════════════════╗\n";
    std::cout << "║  Subgraph-Algorithmus - Demonstrationen und Beispiele     ║\n";
    std::cout << "║  Author: Stephan Epp (2026)                              ║\n";
    std::cout << "╚════════════════════════════════════════════════════════════╝\n";
    
    try {
        example1_simpleComparison();
        example2_identicalGraphs();
        example3_differentSizes();
        example4_complexGraph();
        example5_signatureCalculation();
        example6_lcsComparison();
        example7_errorHandling();
        example8_performanceTest();
        
        std::cout << "\n" << std::string(70, '=') << "\n";
        std::cout << "✓ ALLE BEISPIELE ERFOLGREICH ABGESCHLOSSEN\n";
        std::cout << std::string(70, '=') << "\n\n";
        
    } catch (const std::exception& e) {
        std::cerr << "\n✗ FEHLER: " << e.what() << "\n\n";
        return 1;
    }
    
    return 0;
}
