#include <iostream>
#include <vector>
#include <fstream>
#include <stdexcept>
#include <sstream>
#include <list>
using namespace std;

#include "Visual.class.hpp"
#include "PRQSolver.class.hpp"
#include "PRQPuzzle.class.hpp"

int size = 0;



bool    clearTab(int **toClear) {
    if (toClear) {
        for (int i = 0; i < ::size; ++i)
            if (toClear[i])
                delete[] toClear[i];
        delete[] toClear;
    }
    return true;
}

int **parsing(string fileName) {
    ifstream file;
    string line;
    stringstream ss;
    int **ret = NULL;

    int y = -1;
    int x = 0;

    file.open(fileName);
    if (!file.is_open())
        throw runtime_error("Error opening file");
    while (getline(file, line)) {
        if (line[0] == '#')
            continue;
        ss.str("");
        ss.clear();
        ss << line;
        while (!ss.eof()) {
            unsigned int n;
            ss >> n;
            if (ss.fail()) {
                ss.clear();
                if (line[ss.tellg()] == '#')
                    break;
                else if (clearTab(ret))
                    throw runtime_error("Invalid file format");
            }
            if (::size == 0) {
                ::size = n;
                x = ::size;
                ret = new int*[n];
                for (int i = 0; i < (int)n; i++)
                    ret[i] = new int[n];
            }
            else if (ss.good() || ss.eof()) {
                if (x == ::size)
                    throw runtime_error("Invalid file format");
                if (n + 1 > static_cast<unsigned int>(::size * ::size) && clearTab(ret))
                    throw runtime_error("Invalid file format");
                ret[y][x++] = n;
            }
        }
        if ((x != ::size || ::size < 3) && clearTab(ret))
            throw runtime_error("Invalid file format");
        x = 0;
        y++;
    }
    file.close();
    return ret;
}

int     main(int ac, char **av)
{
    string searchType = "UCS";
    string heuristic = "AMD";
    string VisualMode = "";

    int **firstTab = NULL;

    try {
        if (ac == 1)
            throw runtime_error("usage");
        for (int n = 1; n < ac; n++) {
            if (av[n][0] == '-') {
                if (strcmp(av[n] + 1, "GS") == 0)
                    searchType = "GS";
                else if (strcmp(av[n] + 1, "UCS") == 0)
                    searchType = "UCS";
                else if (strcmp(av[n] + 1, "BFS") == 0)
                    heuristic = "BFS";
                else if (strcmp(av[n] + 1, "AHD") == 0)
                    heuristic = "AHD";
                else if (strcmp(av[n] + 1, "AMD") == 0)
                    heuristic = "AMD";
                else if (strcmp(av[n] + 1, "AED") == 0)
                    heuristic = "AED";
                else if (strcmp(av[n] + 1, "v") == 0)
                    VisualMode = "text";
                else if (strcmp(av[n] + 1, "w") == 0)
                    VisualMode = "web";
                else
                    throw runtime_error("invalid option: " + static_cast<string>(av[n]));
            }
            else if (!firstTab)
                firstTab = parsing(av[n]);
        }
        if (!firstTab)
            throw runtime_error("Missing file name.");
    }
    catch (exception& e) {
        if (firstTab)
            clearTab(firstTab);
        if (static_cast<string>(e.what()).compare("usage"))
            cout << e.what() << endl << endl;
        cout << "Usage: N-Puzzle FileName [-BFS -AHD -AMD -AED] [-UCS -GS] [-v] " << endl
        << "Heuristics:" << endl
        << "   -BFS     Breath First Search" << endl
        << "   -AHD     A* Hamming Distance" << endl
        << "   -AMD     A* Manhatan Distance" << endl
        << "   -AED     A* Euclidian Distance" << endl
        << "Search type:" << endl
        << "   -UCS     Uniform Cost Search" << endl
        << "   -GS      Greedy Search" << endl
        << "Additional:" << endl
        << "   -v       Use text visualisator mode" << endl
        << "   -w       Use web visualisator mode" << endl;
        return 0;
    }

    try {
        list<int**> soluce;

        PRQSolver solver(firstTab, ::size);
        PRQPuzzle *solution = solver.solve(heuristic, searchType);
        PRQPuzzle *tmp = solution;
        while(tmp != nullptr)
        {
            tmp->printPuzzle();
            soluce.push_front(tmp->getPuzzle());
            std::cout<< std::endl;
            tmp = tmp->prevInSolution;
        }
        std::cout << "heuristic = " << heuristic << std::endl;
        std::cout << "searchType = " << searchType << std::endl;
        std::cout << "complexity in time = " << solver.ComplexityInTime << std::endl;
        std::cout << "complexity in size = " << solver.ComplexityInSize << std::endl;
        std::cout << "number of moves for solution = " << solution->getDepth() << std::endl;
        if (VisualMode != "") {
            Visual visu(::size, VisualMode);
            if (VisualMode == "web")
                visu.GenerateWeb(soluce);
            else if (VisualMode == "text")
                visu.print(soluce);
        }
    }
    catch (exception& e) {
        cout << e.what() << endl;
    }


    return (0);
}
