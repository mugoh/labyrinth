# include "../include/main.h"

# include <iostream>
# include <fstream>
# include <iterator>

int main(int argc, char **argv) {
    if (show_usage(argv, argc))
        return EXIT_SUCCESS;
    std::vector<std::vector<Marker>> labyrinth;

    try {
        read_labyrinth(&labyrinth, *(argv + 1));
    } catch (std::exception& e) {
        std::cerr << e.what() << std::endl;
        return EXIT_SUCCESS;
    } 
    Maze mz = Maze(false);
    std::vector<Coordinate> path = mz.findLongestPath(labyrinth);
    displayTakenPath(labyrinth, path);
    return 0;
}
    
int show_usage(char **argv, int argc) {
    if (argc > 2) {
        std::cerr << "Unkown argument: " << *(argv + 2) << std::endl;
    } else if (argc < 2) {
        std::cerr << "Missing Path to file" << std::endl;
    } else {
        return 0;
    }
    std::cout << "Example Usage: " << std::endl;
    std::cout << "\t" << *argv << "  path_to_text_file" << std::endl;
    std::cout << "\t e.g: " << *argv << "  file.txt" <<std::endl;
    std::cout << "\nJust breath and try again, cool?" << std::endl;


    return 1;
}

void read_labyrinth(
        std::vector<std::vector<Marker>> *lh,
        char *input_file) {
    std::ifstream inFile(input_file);
    std::vector<std::string> labyrinth;

    if(!inFile) {
        throw std::runtime_error("Unable to find the labyrinth text file.\nCheck the name again");
    }

    std::copy(std::istream_iterator<std::string>(inFile),
            std::istream_iterator<std::string>(),
            std::back_inserter(labyrinth));

    size_t i =0;
    while(i < labyrinth.size()) {
        std::vector<Marker> v_row;
        for(auto l: labyrinth[i++]) {
            if(l !='#' and l!= '.') {
                const char msg[] = "Found invalid character in labyrinth text file. The maze should have either:\n '#' - WALL\n '.' - PATH ";
                throw std::invalid_argument(msg);
            }
            v_row.push_back((Marker)l);
        }
        lh->push_back(v_row);
    }
}


void displayTakenPath(std::vector<std::vector<Marker>> grid,
        std::vector<Coordinate> trace) {
    char order = '0';

    for(auto coord: trace) {
        grid.at(coord.row).at(coord.col) = (Marker)order++;
    }
    std::cout << "\n" << " " << trace.size() << std::endl;
    for (auto row: grid) {
        for (auto col: row)
            std::cout << " " << (char)col << std::flush;
        std::cout << "\n" << std::endl;
    }
}
