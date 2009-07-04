#include <boost/program_options.hpp>
#include <iostream>
#include <vector>
#include "ScriptManager.hpp"

int main(int argc, char **argv) {
  boost::program_options::options_description desc("Options");
  desc.add_options()
    ("help", "produce help message")
    ("script", boost::program_options::value<std::string>(), "script to load")
    ("args", boost::program_options::value< std::vector<std::string> >(), 
      "arguments to the script");

  boost::program_options::positional_options_description p;
  p.add("args", -1);

  boost::program_options::variables_map vm;
  try {
    boost::program_options::store(
      boost::program_options::command_line_parser(argc, argv).
          options(desc).positional(p).run(), vm);
  }
  catch (std::exception &e) {
    std::cout << "Error : " << e.what() << "\n";
    return 1;
  }
  boost::program_options::notify(vm);    

  if (vm.count("help")) {
      std::cout << desc << "\n";
      return 0;
  }

  if (!vm.count("script")) {
    std::cout << "Please give me a script !\n";
    return 0;
  }
  else {

    std::cout << "Calling " << vm["script"].as< std::string>() 
              << " with these args : ";

    if (vm.count("args")) {
      std::vector<std::string> V = vm["args"].as<std::vector<std::string> >(); 
      for (std::vector<std::string>::iterator I = V.begin(); I != V.end(); I++)
        std::cout << *I << " ";
    }
    std::cout << std::endl;
    
    ScriptManager::loadScript(vm["script"].as<std::string>().c_str());
    
  }
}

