#include "header.h"

int main()
{
    std::vector<std::string> students; //vector holding all current students
    std::vector<std::string>& ref_students = students; //reference vector to students
    std::string studentFileName;
    std::string& ref_studentFileName=studentFileName;
    int opt; //what option was chosen

    std::cout << "\x1B[2J\x1B[H"; //clear screen (write screen empty)
    std::cout << "\e[8;50;125t"; //resize terminal to 50 x 125
    
    std::cout
        << "\nC++ group generator 0.2\n"
        << "(c) Lloyd Bush 2024\n"
        << "*************************\n"
        << "\n"
        << "recommended terminal size: 125 x 50\n";

    while(true) //until user exits or crash
    {
        opt=out_opt(); //outputs the options
        std::cout << "\x1B[2J\x1B[H"; //clear screen

        switch(opt){
            case 1: add_student(ref_students); break; //adds student to list
            case 2: remove_student(ref_students); break; //removes student from list
            case 3: save_students(students,studentFileName); break; //saves student list
            case 4: read_students(ref_students,ref_studentFileName); break; //reads students from file
            case 5: out_students(students); break; //outputs student list
            case 6: group_students(students); break; //generates groups by number of students per group
            case 7: group_num(students); break; //generates groups by number of groups
            case 8: help_me(); break; //opens help menu
            case 0: //exits program
                char save;

                std::cout << "Do you want to save this list of students to a file before exiting? (y/n)\n";

                do{
                    std::cin >> save;

                    if(save=='y'){
                        save_students(students,studentFileName);
                        break;
                    }
                    else if(save=='n'){
                        break;
                    }
                    else{
                        std::cout << "ERROR: invalid input\n\n";
                    }
                }
                while(true);
                return 0;
                break;
            default: std::cout << "\nERROR: invalid input\n"; break; //invalid input
        }
    }

    return 0;
}
