#ifndef GLOBAL_ARGS_VND_HPP
#define GLOBAL_ARGS_VND_HPP

/**
 * This class retrieves command line arguments used by the Variable
 * Neighbourhood Descent algorithm.
 */
struct GlobalArgsVND {
    std::string programName;
    std::string neighbourhood;
    std::string filePath;
    
    GlobalArgsVND(std::string programName);
    
    void retrieve(int argc, char *argv[]);
    
    void checkArgs() const;
    void checkEmpty() const;
    void checkNeighborhood() const;
    void checkFilePath() const;
    
    void printHelp() const;
};

#endif // GLOBAL_ARGS_VND_HPP
