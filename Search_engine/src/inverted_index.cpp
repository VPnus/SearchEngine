#include "include/inverted_index.h"


// Обновить или заполнить базу документов, по которой будем совершать поиск

void InvertedIndex::UpdateDocumentBase(std::vector<std::string> documents)
{
      docs = documents;
      freq_dictionary.clear();
      for (size_t doc_id = 0; doc_id < docs.size(); doc_id++) {

          const std::string& document = docs[doc_id];
          std::map<std::string, size_t> word_count;
          size_t start_pos = 0;
          size_t end_pos = document.find(' ');

          while (end_pos != std::string::npos) {
            std::string word = document.substr(start_pos, end_pos - start_pos);
            word_count[word]++;
            start_pos = end_pos + 1;
            end_pos = document.find(' ', start_pos);
           }
           std::string last_word = document.substr(start_pos);
           word_count[last_word]++;

           for (const auto& pair : word_count) {
               const std::string& word = pair.first;
               size_t count = pair.second;
               freq_dictionary[word].push_back({doc_id, count});
           }
       }
}

//Метод определяет количество вхождений слова word в загруженной базе документов
std::vector<Entry> InvertedIndex::GetWordCount(const std::string& word)
{
        std::vector<Entry> wordCountList;
       for (size_t i = 0; i < docs.size(); i++) {
           size_t count = 0;
           size_t pos = 0;
           const std::string& document = docs[i];
           while ((pos = document.find(word, pos)) != std::string::npos) {
               pos += word.length();
               count++;
           }
           wordCountList.push_back({i, count});
       }
       return wordCountList;
}


