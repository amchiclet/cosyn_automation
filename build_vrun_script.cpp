// basic file operations
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>

using namespace std;

// for string delimiter
vector<string> split (string s, string delimiter) {
    size_t pos_start = 0, pos_end, delim_len = delimiter.length();
    string token;
    vector<string> res;

    while ((pos_end = s.find (delimiter, pos_start)) != string::npos) {
        token = s.substr (pos_start, pos_end - pos_start);
        pos_start = pos_end + delim_len;
        res.push_back (token);
    }
    res.push_back (s.substr (pos_start));
    return res;
}


int main (int argc, char *argv[]) {
    if(argc != 2){
        cout<<"usage: ./a.out [codelet name]\n";
        return 0;
    }
    ofstream new_file;
    ifstream myfile; 
    ifstream csvfile;
    string codelet_name(argv[1]);

    csvfile.open("../../compiler-evaluation-experiments/LoopGen/"+codelet_name+"/src_info.csv");
    myfile.open("vrun_clean_reduction.sh");
    new_file.open ("vrun_new.sh");
    string line;
    unsigned line_number = 0;
    vector<string> titles;
    vector<string> codelet_names;
    vector<int> array_numbers;
    bool no_array_idx = false;
    int default_array_no = 3;
    unsigned array_idx = 0;
    while(getline(csvfile,line)){
        line_number++;
        titles = split(line,",");
        if(line_number == 1){
            if(!no_array_idx){
                // it has "# arrays" in the 
                for(array_idx = 0; array_idx < titles.size();array_idx++){
                    if(titles[array_idx].compare("# arrays")==0) break;
                }
                if(array_idx == titles.size()) {
                    cerr<<"no arrays found in src_info.csv\n";
                    return 0;
                }
            }
        }else{
            // line_number >= 2
            codelet_names.push_back(titles[0]+"_de");
	        if(no_array_idx) {
		        array_numbers.push_back(default_array_no);
	        }else{
	    	    array_numbers.push_back(stoi(titles[array_idx]));	
	        }
	    }
    }
    line_number = 0;
    while (std::getline(myfile, line))
    {
        line_number++;
        if(line_number == 129){
            new_file << "   amarin_lore_prefix=\"${prefix}/compiler-evaluation-experiments/LoopGen/"+codelet_name+"/\""<<endl;
        }else if(line_number == 138){
            if(line=="	run_codelets=("){
                for(unsigned i = 0; i < codelet_names.size(); i++){
                    new_file <<"    name2sizes["<<codelet_names[i]<<"]=\"32000:"<<array_numbers[i]<<"\""<<endl;
                }
                new_file<<endl;
                new_file << line << endl;
                for(unsigned i = 0; i < codelet_names.size(); i++){
                    new_file <<"        "<<codelet_names[i]<<endl;
                }
            }else{
                cerr<<"no run_codelets=( found\n";
                return 0;
            }
        }else{
            new_file << line << endl;
        }
    }
    new_file.close();
    cout<<line_number;
    return 0;
}
