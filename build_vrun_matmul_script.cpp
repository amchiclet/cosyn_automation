// basic file operations
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>

using namespace std;

string get_codelet_path(const string &path) {
  // if path includes a slash, use that path as is
  // otherwise, use compiler-evaluation-experiments/LoopGen as the base path
  string default_base_path = "compiler-evaluation-experiments/LoopGen/";
  bool use_default_base_path = (path.find('/') == std::string::npos);
  return use_default_base_path ? default_base_path + path : path;
}

vector<string> parse_codelet_names(const string &codelet_path) {
  vector<string> codelet_names;

  ifstream source_info_csv("../../" + codelet_path + "/src_info.csv");

  // skip header row
  string line;
  getline(source_info_csv, line);

  // read the rest of the rows, to gather the codelet names
  while(getline(source_info_csv,line)){
    // codelet name should be the first column
    string codelet_name = line.substr(0, line.find(','));
    codelet_names.push_back(codelet_name + "_de");
  }

  return codelet_names;
}

string parse_matmul_sizes(const string &matmul_sizes_file_name) {
  string sizes;
  ifstream matmul_sizes(matmul_sizes_file_name);

  matmul_sizes >> sizes;
  string size;
  while (matmul_sizes >> size) {
    sizes += " " + size;
  }
  return sizes;
}

void generate_vrun_script(const string &codelet_path,
			  const vector<string> &codelet_names,
			  const string &matmul_sizes,
			  const string vrun_file_name) {
  ifstream vrun_template;
  vrun_template.open("vrun_matmul_template.sh");

  ofstream vrun_file(vrun_file_name);

  string line;
  while (std::getline(vrun_template, line)) {
    if (line.find("amarin_lore_prefix=") != string::npos) {
      vrun_file << "        amarin_lore_prefix=\"${prefix}/" + codelet_path + "/\"\n";
    } else if (line.find("run_codelets=(") != string::npos){
      for (const string &codelet_name : codelet_names) {
	vrun_file << "        name2sizes[" << codelet_name << "]="
		  << '"' << matmul_sizes << '"' << "\n\n";
      }
      vrun_file << "        run_codelets=(\n";
      for (const string &codelet_name : codelet_names) {
	vrun_file << "            " << codelet_name << "\n";
      }
    } else{
      vrun_file << line << "\n";
    }
  }
}

void print_debug(const string &codelet_path,
		 const vector<string> &codelet_names,
		 const string &matmul_sizes,
		 const string &vrun_file_name) {
  cout << "\n"
       << "  Generated: " << vrun_file_name << "\n"
       << "  Codelet path: " << codelet_path << " (count = " << codelet_names.size() << ")\n"
       << "  Matmul sizes: " << matmul_sizes << "\n"
       << "\n";
}

int main (int argc, char *argv[]) {
  if(argc != 4){
    cout << "usage: ./a.out [base path/codelet path] [matmul_sizes_file_name] [vrun_file_name]\n"
	 << "or     ./a.out [codelet path] [matmul_sizes_file_name] [vrun_file_name]\n";
    return 0;
  }

  string codelet_path = get_codelet_path(argv[1]);
  vector<string> codelet_names = parse_codelet_names(codelet_path);

  string matmul_sizes_file_name(argv[2]);
  string matmul_sizes = parse_matmul_sizes(matmul_sizes_file_name);

  string vrun_file_name(argv[3]);
  generate_vrun_script(codelet_path, codelet_names, matmul_sizes, vrun_file_name);

  print_debug(codelet_path, codelet_names, matmul_sizes, vrun_file_name);
}
