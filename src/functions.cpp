#include "header.h"

//checks if specific file exists
/*
inline bool exists(const std::string& filename){
    struct stat buffer;
    return (stat (filename.c_str(), &buffer) == 0);
}
*/

//prints students in current vector
void out_students(std::vector<std::string> students){
    std::cout << "\n##################################################\n";
    for(int i = 0; i < students.size(); i++)
    {
        std::cout << i + 1 << "\t" << students[i] << "\n";
    }
    std::cout << "##################################################\n";
}

//prints options and takes option input
int out_opt(){
    std::string opt;
    int int_opt;
    
    std::cout
        << "\n"
        << "1\tAdd student\n"
        << "2\tRemove student\n"
        << "3\tSave students\n"
        << "4\tLoad students\n"
        << "5\tShow students\n"
        << "\n"
        << "6\tGroups by number of students per group\n"
        << "7\tGroups by number of groups\n"
        << "\n"
        << "8\tHelp\n"
        << "0\tExit\n"
        << "\n"
        << ">> ";
    
    std::cin >> opt;

    if(opt=="8"||opt=="h"||opt=="H"||opt=="help"||opt=="Help"||opt=="?"){ //alternative means of reaching the help page
        opt="8";
    }
    int_opt=std::stoi(opt); //string to int
    return int_opt;
}

//adds a student to vector ref_students and since it is a refference also to students
void add_student(std::vector<std::string>& ref_students){
    std::string new_student;
    //int spacePos=0;

    std::cout << "\n##################################################\n";
    std::cout << "Name (only one word!): ";
    std::cin >> new_student;

    /*
    for(int i=new_student.size();i>0;i--){
        spacePos=new_student.find(" ");
        if(new_student[0]!=' ')
    }
    */

    std::cout << "adding student...\n";
    ref_students.push_back(new_student);
    std::cout << "student added successfully\n##################################################\n";
}

//remove student from current vector
void remove_student(std::vector<std::string>& ref_students){
    int student_index; //student's index in vector
    std::string name_student; //student's name
    std::vector<std::string> tmp_students; //temporary vector for deleting student from ref_students

    std::cout << "\n##################################################\n";
    std::cout << "Number: ";
    std::cin >> student_index;
    student_index -= 1;
    name_student = ref_students.at(student_index);
    std::cout << "removing " << name_student << "...\n";

    for(int i=ref_students.size(); i>student_index; i--){ //moving all students up to wanted student to temporary vector
        tmp_students.push_back(ref_students[i-1]);
        ref_students.pop_back();
    }
    tmp_students.pop_back(); //delete wanted student from vector
    for(int i=tmp_students.size(); i>0; i--){ //move students from temporary vector back to normal vector
        ref_students.push_back(tmp_students[i-1]);
        tmp_students.pop_back();
    }

    std::cout << name_student << " removed successfully\n";
    std::cout << "##################################################\n";
}

//checks if you really want to continue saving the file
bool continue_save(std::string file){
    char overwrite;
    /*
    if(exists(file)==1){
        std::cout << "file\"" << file << "\" already exists\ndo you want to overwrite it? (y/n)\n";

        do{
            std::cin >> overwrite;

            if(overwrite=='y'){
                std::cout << "overwriting \"" << file << "\"...";
                return true;
            }
            else if(overwrite=='n'){
                return false;
            }
            else{
                std::cout << "ERROR: invalid input\n";
            }
        }
        while(true);
    }
    */
    do{
        std::cout << "Saving this file will overwrite any file of the same name. Do you want to continue? (y/n)\n";
        std::cin >> overwrite;

        if(overwrite=='y'){
            return true;
        }
        else if(overwrite=='n'){
            return false;
        }
        else{
            std::cout << "ERROR: invalid input\n";
        }
    }
    while(true);
}

//save current student vector to file
void save_students(std::vector<std::string> students,std::string studentFileName){
    std::string student, file;
    bool cont; //bool continue

    std::cout << "\n##################################################\n";

    std::cout << "File name (enter c to use current file name): ";
    std::cin >> file;

    if(file=="c"){
        file=studentFileName;
    }

    cont=continue_save(file);

    if(cont==true){
        /*if(exists(file)==0){
            std::cout << "creating file \"" << file << "\"...\n";
        }
        else{*/
            std::cout << "opening file \"" << file << "\"...\n";
        /*}*/

        std::ofstream writer(file);
        
        if(!writer){
            std::cout << "\nERROR: trouble opening file \"" << file << "\"\n";
        }
        else{
            std::cout << "file opened successfully\nwriting...\n";

            for(int i=0; i<students.size(); i++){ //write students from vector to file
                writer << students[i] << "\n";
            }
        
            std::cout << "saved successfully\n";
        }
        writer.close();
    }
    else{
        std::cout << "cancelling request...\n";
    }

    std::cout << "##################################################\n";
}

//read and load students from file to student vector
void read_students(std::vector<std::string>& ref_students,std::string& ref_studentFileName){
    std::string file; //file name

    char overwrite;

    std::cout << "\n##################################################\nFile name: ";
    std::cin >> file;

    std::cout << "Loading this file will clear your current student list. Do you want to continue? (y/n)\n";

    do{
        std::cin >> overwrite;

        if(overwrite=='y'){
            ref_studentFileName=file;
            //reads file
            std::ifstream reader(file);

            if(!reader){
                std::cout << "ERROR: trouble opening file \"" << file << "\"\n";
            }
            else{
                //clear student vector
                for(int i=ref_students.size()-1; i >= 0; i--){
                    ref_students.pop_back();
                }
                std::cout << "reading file...\n";
                while(!reader.eof()){ //add student from file to vector (one name per line)
                    getline(reader, file);
                    ref_students.push_back(file);

                    if(ref_students.at(ref_students.size()-1)==""){
                        ref_students.pop_back();
                    }
                }   
                std::cout << "file read successfully\n";
            }
            break;
        }

        else if(overwrite=='n'){
            std::cout << "cancelling...\n";
            break;
        }

        else{
            std::cout << "ERROR: invalid input\n\n";
        }
    }
    while(true);

    std::cout << "##################################################\n";
}

//calculates the number of grous based on the number of students per group
void group_students(std::vector<std::string> students){
    int int_num_students, int_num_groups;
    double num_groups;

    std::cout << "\n##################################################\nnumber of students per group: ";
    std::cin >> int_num_students;

    num_groups=double(students.size())/double(int_num_students); //ideal number of groups
    int_num_groups=int(num_groups); //int number of groups

    if(num_groups-int_num_groups>=0.5){ //refigned int number of groups
        int_num_groups+=1;
    }

    group(students, int_num_groups, int_num_students);
}

//calculates the number of students per group based on the number of groups
void group_num(std::vector<std::string> students){
    int int_num_groups, int_num_students;
    double num_students;

    std::cout << "\n##################################################\nnumber of groups: ";
    std::cin >> int_num_groups;

    num_students=double(students.size())/double(int_num_groups);
    int_num_students=int(num_students);

    if(num_students-int_num_students>=0.5){
        int_num_students+=1;
    }

    group(students, int_num_groups, int_num_students);
}

//generates groups based on the number of groups and the number of students per group
void group(std::vector<std::string> students, int int_num_groups, int int_num_students){
    int j;
    std::vector<std::string> rand_students;
    std::vector<int> used_index;
    bool isIndexUsed=false;

    srand(time(0)); //generates random seed based on time

    std::cout << "Generating random list...\n";

    for(int i=students.size(); i>0; i--){
        do{
            isIndexUsed=false;
            j=rand()%(students.size()); //generates random number from 0 to (number_of_students - 1)

            for(int k=used_index.size(); k>0; k--){
                if(j==used_index.at(k-1)){
                    isIndexUsed=true;
                }
            }
        }
        while(isIndexUsed==true);

        rand_students.push_back(students.at(j));
        used_index.push_back(j);
    }

    for(int i=1; i<=int_num_groups; i++){
        std::cout << "\n------------------------- Group " << i << "\n";
        
        if(i==int_num_groups){
            for(int l=rand_students.size(); l>0; l--){
                std::cout << rand_students[l-1] << "\n";
            }
        }
        else{
            for(int l=rand_students.size(), k=0; k<int_num_students; l--,k++){
                std::cout << rand_students[l-1] << "\n";
                rand_students.pop_back();
            }
        }
    }
    std::cout << "\ngroups generated successfully\n";

    std::cout << "##################################################\n";
}

void help_me(){
    std::cout
        << "\n##################################################\n"
        << "This is the manual page for the group generator 0.1.\n"
        << "For more information contact the author directly.\n"
        << "\n"
        << "\tC++ group generator 0.1\n"
        << "\t(c) Lloyd Bush 2024\n"
        << "\t*************************\n"
        << "\n"
        << "\t1\tAdd student\t\t\t<-- add a student to the list by name\n"
        << "\t2\tRemove student\t\t\t<-- remove a student from list by number\n"
        << "\t3\tSave students\t\t\t<-- save student list to a file\n"
        << "\t4\tLoad students from file\t\t<-- load student list from a file in the same directory as program\n"
        << "\t5\tShow students\t\t\t<-- show student list\n"
        << "\n"
        << "\t6\tGroups by number of students\t<-- generate groups by defining the number of students per group\n"
        << "\t7\tGroups by number of groups\t<-- generate groups by defining the number of groups\n"
        << "\n"
        << "\t8\tHelp\t\t\t\t<-- view this help menu\n"
        << "\t0\tExit\t\t\t\t<-- exit the program\n"
        << "\n"
        << "\t>> \t\t\t\t\t<-- select an option from the above given and enter it's number here\n"
        << "\n"
        << "Just follow further instruction\n"
        << "##################################################\n";
}

/*Kara
Tim
Jette
Leonard*/
