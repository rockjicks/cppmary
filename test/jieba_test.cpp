#include "cppjieba/Jieba.hpp"
#include "cppjieba/KeywordExtractor.hpp"

using namespace std;

const char *const DICT_PATH = "data/jieba/jieba.dict.utf8";
const char *const HMM_PATH = "data/jieba/hmm_model.utf8";
const char *const USER_DICT_PATH = "data/jieba/user.dict.utf8";
const char *const IDF_PATH = "data/jieba/idf.utf8";
const char *const STOP_WORD_PATH = "data/jieba/stop_words.utf8";

int main(int argc, char **argv) {
    cppjieba::Jieba jieba(DICT_PATH,
                          HMM_PATH,
                          USER_DICT_PATH);
    vector<string> words;
    vector<cppjieba::Word> jiebawords;
    string s;
    string result;

    s = "他来到了网易杭研大厦";
    cout << s << endl;
    cout << "[demo] Cut With HMM" << endl;
    jieba.Cut(s, words, true);
    cout << limonp::Join(words.begin(), words.end(), "/") << endl;

    cout << "[demo] Cut Without HMM " << endl;
    jieba.Cut(s, words, false);
    cout << limonp::Join(words.begin(), words.end(), "/") << endl;

    s = "我来到北京清华大学";
    cout << s << endl;
    cout << "[demo] CutAll" << endl;
    jieba.CutAll(s, words);
    cout << limonp::Join(words.begin(), words.end(), "/") << endl;

    s = "小明硕士毕业于中国科学院计算所，后在日本京都大学深造";
    cout << s << endl;
    cout << "[demo] CutForSearch" << endl;
    jieba.CutForSearch(s, words);
    cout << limonp::Join(words.begin(), words.end(), "/") << endl;

    cout << "[demo] Insert User Word" << endl;
    jieba.Cut("男默女泪", words);
    cout << limonp::Join(words.begin(), words.end(), "/") << endl;
    jieba.InsertUserWord("男默女泪");
    jieba.Cut("男默女泪", words);
    cout << limonp::Join(words.begin(), words.end(), "/") << endl;

    cout << "[demo] CutForSearch Word With Offset" << endl;
    jieba.CutForSearch(s, jiebawords, true);
    cout << jiebawords << endl;

    cout << "[demo] Tagging" << endl;
    vector<pair<string, string> > tagres;
    s = "我是拖拉机学院手扶拖拉机专业的。不用多久，我就会升职加薪，当上CEO，走上人生巅峰。";
    jieba.Tag(s, tagres);
    cout << s << endl;
    cout << tagres << endl;;


}