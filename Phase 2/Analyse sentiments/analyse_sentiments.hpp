#include <vector>
#include <iostream>

class SentimentDictionary {
    public:
        void load(const std::string& positivePath, const std::string& negativePath);
        bool isPositive(const std::string& word) const;
        bool isNegative(const std::string& word) const;
        const std::vector<std::string>& getPositiveWords() const;
        const std::vector<std::string>& getNegativeWords() const;


    private:
        std::vector<std::string> positiveWords;
        std::vector<std::string> negativeWords;
};

const std::vector<std::string>& SentimentDictionary::getPositiveWords() const {
    return positiveWords;
}

const std::vector<std::string>& SentimentDictionary::getNegativeWords() const {
    return negativeWords;
}


class AnalysisResult {
    public:
        AnalysisResult();
        void incrementPositiveCount();
        void incrementNegativeCount();
        std::string getOverallSentiment() const;
        int getPositiveCount() const; 
        int getNegativeCount() const; 

    private:
        int positiveCount;
        int negativeCount;
};

int AnalysisResult::getPositiveCount() const {
    return positiveCount;
}

int AnalysisResult::getNegativeCount() const {
    return negativeCount;
}


class SentimentAnalyzer {
    public:
        AnalysisResult analyze(const SentimentDictionary& dictionary, const std::string& filePath) const;

    private:
        std::string cleanWord(const std::string& word) const;
};