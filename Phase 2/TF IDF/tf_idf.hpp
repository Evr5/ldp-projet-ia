#include <vector>
#include <iostream>
#include <map>

std::vector<std::string> readDocument(const std::string& filePath);

std::map<std::string, double> computeTF(const std::vector<std::string>& words);

std::map<std::string, double> computeIDF(const std::vector<std::map<std::string, double>>& documentsTF, int totalDocuments);

std::map<std::string, double> calculateTFIDF(const std::map<std::string, double>& tf, const std::map<std::string, double>& idf);

void displayTFIDFScores(const std::map<std::string, double>& tfidfScores);