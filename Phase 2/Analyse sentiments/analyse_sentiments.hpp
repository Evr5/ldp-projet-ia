#include <vector>
#include <string>

struct SentimentDictionary {
    std::vector<std::string> positiveWords;
    std::vector<std::string> negativeWords;
};

struct AnalysisResult {
    int positiveCount;
    int negativeCount;
    std::string overallSentiment;
};

void loadSentimentDictionary(SentimentDictionary& dictionary, const std::string& positivePath, const std::string& negativePath);

void loadSentimentDictionary(SentimentDictionary& dictionary, const std::string& positivePath, const std::string& negativePath);

AnalysisResult analyzeSentiment(const SentimentDictionary& dictionary, const std::string& filePath);