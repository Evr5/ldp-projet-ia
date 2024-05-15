#include <vector>
#include <iostream>

class SentimentDictionary {
public:
    void load(const std::string& positivePath, const std::string& negativePath);
    bool isPositive(const std::string& word) const;
    bool isNegative(const std::string& word) const;

private:
    std::vector<std::string> positiveWords;
    std::vector<std::string> negativeWords;
};

class AnalysisResult {
public:
    AnalysisResult();
    void incrementPositiveCount();
    void incrementNegativeCount();
    std::string getOverallSentiment() const;

private:
    int positiveCount;
    int negativeCount;
};

class SentimentAnalyzer {
public:
    AnalysisResult analyze(const SentimentDictionary& dictionary, const std::string& filePath) const;

private:
    std::string cleanWord(const std::string& word) const;
};