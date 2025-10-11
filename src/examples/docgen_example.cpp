/*
 * docgen_example.cpp
 * Приклад використання генератора документації
 * Example of using the documentation generator
 * Пример использования генератора документации
 */

#include "../docgen/DocumentationGenerator.h"
#include <iostream>

using namespace NeuroSync;

int main() {
    std::cout << "Documentation Generator Example\n";
    std::cout << "==============================\n\n";
    
    // Configure documentation generator
    DocumentationConfig config;
    config.sourceDirectory = "./src";
    config.outputDirectory = "./docs/generated";
    config.outputFormat = "html";
    config.projectName = "NeuroSync OS Sparky";
    config.projectVersion = "1.0.0";
    
    if (!gDocGenerator->initialize(config)) {
        std::cerr << "Failed to initialize documentation generator\n";
        return 1;
    }
    
    // Analyze source files
    std::cout << "Analyzing source files...\n";
    if (!gDocGenerator->analyzeSourceFiles()) {
        std::cerr << "Failed to analyze source files\n";
        return 1;
    }
    
    // Generate documentation
    std::cout << "Generating documentation...\n";
    if (!gDocGenerator->generateDocumentation()) {
        std::cerr << "Failed to generate documentation\n";
        return 1;
    }
    
    // Export documentation in different formats
    std::cout << "Exporting documentation in different formats...\n";
    gDocGenerator->exportDocumentation("md", "./docs/generated/documentation.md");
    gDocGenerator->exportDocumentation("xml", "./docs/generated/documentation.xml");
    
    std::cout << "\nDocumentation generated successfully!\n";
    std::cout << "HTML documentation: ./docs/generated/index.html\n";
    std::cout << "Markdown documentation: ./docs/generated/documentation.md\n";
    std::cout << "XML documentation: ./docs/generated/documentation.xml\n";
    
    return 0;
}