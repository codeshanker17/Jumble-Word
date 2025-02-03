#include <iostream>
#include <string>
#include <vector>
#include <random>
#include <algorithm>
#include <chrono>
#include <fstream>

using namespace std;

class WordJumbleGame {
private:
    vector<string> wordList = {
         "programming", "computer", "algorithm", "developer",
        "software", "database", "network", "interface",
        "system", "virtual", "memory", "keyboard", "coding",
        "hardware", "monitor", "cloud", "machine", "cycle",
        "logic", "language", "input", "output", "process",
        "cache", "bandwidth", "float", "boolean", "structure",
        "loop", "class", "function", "variable", "browser", "compiler",
        "compile", "execute", "throughput", "version", "update", 
        "complex", "error", "fault", "debug", "testing", "storage",
        "disk", "list", "stack", "graph", "djikstra", "information", 
        "technology", "bloatware", "firmware", "cybersecurity", "kernel",
        "interface", "user", "antivirus", "virus", "processor", "streaming",
        "bitrate", "hacker", "hacking", "inject", "efficiency", "clock", 
        "binary", "technical", "encoding", "decoding", "compress", "compression",
        "datalink", "prompt", "directory", "linux", "pointer", "object", "method",
        "overloading", "overriding", "dictionary", "array", "simulation", "analysis",
        "testing", "debugging", "stock", "cyberpunk", "switch", "multimedia", 
        "optimization", "charge", "bluetooth", "torrent", "instance", "text", "file",
        "folder", "archive", "video", "picture", "wallpaper", "mouse", "github", 
        "application", "inheritance", "polymorphism", "encapsulation", "abstraction",
        "editor", "review", "desktop", "recycle", "cybercode", "synchronous",
        "thread", "read", "write", "notepad", "settings", "predefined", "learning",
        "cursor", "semantics", "service", "trojan", "cryptography", "digital", "analog",
        "frequency", "flowchart", "model", "modem", "router", "broadband", "optical", 
        "channel", "satellite", "numeric", "random", "tuple", "entity", "initialize",
        "iterate", "regex", "string", "vector", "privacy", "catalyst", "distribute",
        "constructor", "deconstructor", "shuffle", "gamma", "thermal", "laptop", "transmit",
        "scanner", "printer", "xerox", "quartz", "ultraviolet", "bottleneck", "transmission",
        "packet", "serial", "parallel", "motherboard", "syntax", "hosting", "project", 
        "development", "broadcast", "telecast", "blueprint", "compatible", "library", 
        "module", "package", "assembly", "command", "scripting", "multitask", "import",
        "include", "pseudocode", "liquid", "embedded", "javascript", "patch", "segmentation",
        "redundancy", "source", "diode", "protocol", "internet", "datagram", "headset", "quantum",
        "biotech", "component", "transaction", "bitcoin", "framework", "flutter", "dart", "omega",
        "alpha", "sigma", "scheduling", "lumbar", "color", "buffer", "normalization", "ethernet", 
        "pixel", "zoom", "layer", "agile", "cipher", "daemon", "mining", "document", "documentation",
        "domain", "emulator", "encryption", "decryption", "signature", "extension", "game", "gigabyte",
        "byte", "image", "interpret", "integration", "linear", "matrix", "peripheral", "python", "recursion",
        "spiral", "generation", "global", "local", "headerfile", "upload", "download", "tracker", "reflex",
        "reboot", "bios", "preprocessing", "hyperlink", "cookie", "hypertext", "element", "positive", 
        "tablet", "energy", "wired", "wireless", "connection", "cryptocurrency", "circuit", "blockchain",
        "devops", "portfolio", "shares", "yggdrasil", "kratos", "zeus", "odin", "epson", "coffee", "ping",
        "latency", "jitter", "drag", "pulse", "vintage", "jargon", "membrane", "mechanics", "mechanical",
        "optimal", "optimum", "keycap", "odyssey", "amplifier", "cartridge", "realm", "bridge", "portal",
        "lithium", "compose", "compound", "space", "zynegma", "messiah", "breaker", "catastrophe", 
    };
    int score = 0;
    int highScore = 0;
    const string HIGH_SCORE_FILE = "highscore.txt";
    
    string getRandomWord() {
        random_device rd;
        mt19937 gen(rd());
        uniform_int_distribution<> dis(0, wordList.size() - 1);
        return wordList[dis(gen)];
    }
    
    string jumbleWord(const string& word) {
        string jumbled = word;
        unsigned seed = chrono::system_clock::now().time_since_epoch().count();
        shuffle(jumbled.begin(), jumbled.end(), default_random_engine(seed));
        
        while (jumbled == word && word.length() > 1) {
            shuffle(jumbled.begin(), jumbled.end(), default_random_engine(seed));
        }
        return jumbled;
    }

    void loadHighScore() {
        ifstream file(HIGH_SCORE_FILE);
        if (file.is_open()) {
            file >> highScore;
            file.close();
        }
    }

    void saveHighScore() {
        ofstream file(HIGH_SCORE_FILE);
        if (file.is_open()) {
            file << highScore;
            file.close();
        }
    }

    void updateHighScore() {
        if (score > highScore) {
            highScore = score;
            saveHighScore();
            cout << "\nCongratulations! New high score achieved!\n";
        }
    }

public:
    WordJumbleGame() {
        loadHighScore();
    }

    void play() {
        cout << "\nWelcome to Word Jumble!\n";
        cout << "Unscramble the letters to make a word.\n";
        cout << "Type 'quit' to end the game.\n";
        cout << "Current High Score: " << highScore << "\n\n";
        
        while (true) {
            string currentWord = getRandomWord();
            string jumbled = jumbleWord(currentWord);
            
            cout << "\nJumbled word: " << jumbled << endl;
            cout << "Your guess (or 'quit' to end): ";
            
            string guess;
            getline(cin, guess);
            
            if (guess == "quit") {
                break;
            }
            
            if (guess == currentWord) {
                score += 10;
                cout << "Correct! You earned 10 points.\n";
            } else {
                cout << "Sorry, the word was: " << currentWord << "\n";
            }
            
            cout << "Current score: " << score << "\n";
            cout << "High score: " << highScore << "\n";
        }
        
        updateHighScore();
        
        cout << "\nGame Over!\n";
        cout << "Final score: " << score << "\n";
        cout << "High score: " << highScore << "\n";
    }
    
    void addWord(const string& word) {
        wordList.push_back(word);
    }
};

int main() {
    WordJumbleGame game;
    game.play();
    return 0;
}