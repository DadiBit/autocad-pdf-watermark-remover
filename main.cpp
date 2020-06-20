#include <iostream>
#include <fstream>

int main (int argc, char** argv) {

    if (argc>2) {

    //open file
    std::ifstream infile(argv[1], std::ios::in|std::ios::binary);

    std::ofstream outfile(argv[2], std::ios::out|std::ios::binary);
    
    //check if input file is open
    if (infile.is_open() && outfile.is_open()) {

        //set surrent position to end of file
        infile.seekg(-1, std::ios::end);

        //char holder
        char ch;

        //head (ET) - tail (BT)
        char head[] = {0x0A, 0x54, 0x45, 0x0A, 0x4A, 0x54, 0x20, 0x5D, 0x39, 0x36, 0x39, 0x37, 0x36, 0x31, 0x2E, 0x30, 0x2D, 0x3E, 0x31, 0x33, 0x30, 0x30, 0x3C, 0x30, 0x30, 0x30, 0x30, 0x30, 0x30, 0x2E, 0x37, 0x3E, 0x32, 0x33, 0x30, 0x30, 0x3C, 0x30, 0x30, 0x30, 0x30, 0x30, 0x30, 0x2E, 0x33, 0x2D, 0x3E, 0x43, 0x32, 0x30, 0x30, 0x3C, 0x30, 0x30, 0x30, 0x30, 0x30, 0x30, 0x2E, 0x36},
             tail[] = {0x46, 0x2F, 0x0A, 0x72, 0x54, 0x20, 0x30, 0x0A, 0x54, 0x42};

        int head_length = sizeof(head) / sizeof(head[0]),
            tail_length = sizeof(tail) / sizeof(tail[0]),
            max_matches = 4, //how many matches do we need?
            i = 0, //head
            j = 0, //tail
            k = 0, //matches
            b = infile.tellg(), //current byte
            size = b; //size

        int positions[max_matches][2];

        //go to previous char
        for (; infile.get(ch) && k<max_matches; infile.seekg(-2, std::ios::cur)) {

            if (i<head_length) {
                if (head[i]==(int)ch) {
                    i++;
                } else {
                    i = 0;
                }
                if (i==head_length) {
                    positions[max_matches-k-1][1] = b + head_length - 1;
                }
            } else {
                if (j<tail_length) {
                    if (tail[j]==(int)ch) {
                        j++;
                    } else {
                        j = 0;
                    }
                } else {
                    if (j==tail_length) {
                        positions[max_matches-k-1][0] = b + 1;
                        i = 0;
                        j = 0;
                        k++;
                    }
                }
            }

            b--;
        
        }

        //set surrent position to start
        b = 0;
        infile.seekg(b, std::ios::beg);

        //current position we're checking
        int a = 0;

        //loop over again
        for (; infile.get(ch); infile.seekg(0, std::ios::cur)) {

            if (b<positions[a][0]) {
                outfile << ch;
            } else {
                if (b>positions[a][1]) {
                    outfile << ch;
                    a++;
                }
            }

            b++;

        }

        outfile.close();

        infile.close();

        return 0;

    } else {
        std::cout << "Cannot open input/output file!";
        return 1;
    }

    } else {
        std::cout << "Not enough arguments!";
        return 1;
    }

}