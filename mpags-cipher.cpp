// Standard Library includes
#include <iostream>
#include <string>
#include <vector>
#include <fstream>

// For std::isalpha and std::isupper
#include <cctype>

std::string transformChar(const char in);

std::string readFromFile(const std::string& inputFile) {
      // This function reads in characters from inputFile, passes them to be transformed,
      // and returns the result in a string
      std::ifstream in_file {inputFile}; 
      bool ok_to_read = in_file.good(); // Checks if the infile exists
      std::string outputText{""};
      
      if (ok_to_read) {
	  char inputChar {'x'};
 	  while(in_file >> inputChar)  {
	         // Call the function to turn the input into alphabetic characters
  		 std::string outputStr {transformChar(inputChar)}; 
  		 outputText += outputStr;	
 	  }
      }
      //std::cout << inputText << std::endl;
      return outputText; 
}

void writeToFile(const std::string& outputText, const std::string& outputFile) {
	std::ofstream out_file {outputFile};
	bool ok_to_write = out_file.good(); // Checks if the outfile exists
	if (ok_to_write) {
		out_file << outputText;
		std::cout << "Written successfully to " << outputFile << std::endl;
	}
} 

// Function to process the command line arguments 
bool processCommandLine(
	const std::vector<std::string>& cmdLineArgs, 
	bool& helpRequested, 
	bool& versionRequested,
	std::string& inputFile,
	std::string& outputFile ) 
{
  /* This function references to the string of command line args, 
     and the other self-explanatory variables, and processes them
     by reference. Throws errors if the arguments you gave it   
     were incorrect. Gives a help & version statement if asked.
  */

  // Add a typedef that assigns another name for the given type for clarity
  typedef std::vector<std::string>::size_type size_type;
  const size_type nCmdLineArgs {cmdLineArgs.size()};

  // Process command line arguments - ignore zeroth element, as we know this to
  // be the program name and don't need to worry about it
  for (size_type i {1}; i < nCmdLineArgs; ++i) {

    if (cmdLineArgs[i] == "-h" || cmdLineArgs[i] == "--help") {
      helpRequested = true;
    }
    else if (cmdLineArgs[i] == "--version") {
      std::cout << "Testing!" << std::endl;
      versionRequested = true;
    }
    else if (cmdLineArgs[i] == "-i") {
      // Handle input file option
      // Next element is filename unless -i is the last argument
      if (i == nCmdLineArgs-1) {
	std::cerr << "[error] -i requires a filename argument" << std::endl;
	// exit main with non-zero return to indicate failure
	return false;
      }
      else {
	// Got filename, so assign value and advance past it
	inputFile = cmdLineArgs[i+1];
	++i;
      }
    }
    else if (cmdLineArgs[i] == "-o") {
      // Handle output file option
      // Next element is filename unless -o is the last argument
      if (i == nCmdLineArgs-1) {
	std::cerr << "[error] -o requires a filename argument" << std::endl;
	// exit main with non-zero return to indicate failure
	return false;
      }
      else {
	// Got filename, so assign value and advance past it
	outputFile = cmdLineArgs[i+1];
	++i;
      }
    }
    else {
      // Have an unknown flag to output error message and return non-zero
      // exit status to indicate failure
      std::cerr << "[error] unknown argument '" << cmdLineArgs[i] << "'\n";
      return false;
    }
  }

  // Handle help, if requested
  if (helpRequested) {
    // Line splitting for readability
    std::cout
      << "Usage: mpags-cipher [-i <file>] [-o <file>]\n\n"
      << "Encrypts/Decrypts input alphanumeric text using classical ciphers\n\n"
      << "Available options:\n\n"
      << "  -h|--help        Print this help message and exit\n\n"
      << "  --version        Print version information\n\n"
      << "  -i FILE          Read text to be processed from FILE\n"
      << "                   Stdin will be used if not supplied\n\n"
      << "  -o FILE          Write processed text to FILE\n"
      << "                   Stdout will be used if not supplied\n\n";
    // Help requires no further action, so return from main
    // with 0 used to indicate success
    return 0;
  }

  // Handle version, if requested
  // Like help, requires no further action,
  // so return from main with zero to indicate success
  if (versionRequested) {
    std::cout << "0.1.0" << std::endl;
    return 0;
  }
  return true;
}

// Main function of the mpags-cipher program
int main(int argc, char* argv[])
{
  // Convert the command-line arguments into a more easily usable form
  const std::vector<std::string> cmdLineArgs {argv, argv+argc};

  bool helpRequested {false};
  bool versionRequested {false};
  std::string inputFile {""};
  std::string outputFile {""};
  
  // Process the command line arguments and check if it went through OK. Kill if not. 
  bool status {processCommandLine(cmdLineArgs, helpRequested, versionRequested, inputFile, outputFile)};
  if (status==false) {
	return 1; 
  } 

  // Initialise variables for processing input text
  char inputChar {'x'};
  //std::string inputText {""};
  std::string outputText {""};
  // Read in user input from stdin/file
  // Warn that input file option not yet implemented
  if (!inputFile.empty()) {
      outputText = readFromFile(inputFile);
  }
  else {
     // Use the command line output 
     // Loop over each character from user input
     // (until Return then CTRL-D (EOF) pressed)
     while(std::cin >> inputChar)
     {
          // Call the function to turn the input into alphabetic characters
          std::string outputStr {transformChar(inputChar)}; 
          outputText += outputStr;	
     }
  }
  // Output the transliterated text
  if (!outputFile.empty()) {
      writeToFile(outputText, outputFile);
     // std::ofstream out_file {outputFile};
     // bool ok_to_write = out_file.good();
  }
  else {
     // Print to the console instead
     std::cout << outputText << std::endl;
  }
  // No requirement to return from main, but we do so for clarity
  // and for consistency with other functions
  return 0;
}

// Separate function to transform the input into just alphabetic, uppercase characters
std::string transformChar ( const char inputChar ) {
	
    std::string inputText{""};	

    // Uppercase alphabetic characters
    if (std::isalpha(inputChar)) {
      inputText += std::toupper(inputChar);
      //continue;
    }

    // Transliterate digits to English words
    switch (inputChar) {
      case '0':
	inputText += "ZERO";
	break;
      case '1':
	inputText += "ONE";
	break;
      case '2':
	inputText += "TWO";
	break;
      case '3':
	inputText += "THREE";
	break;
      case '4':
	inputText += "FOUR";
	break;
      case '5':
	inputText += "FIVE";
	break;
      case '6':
	inputText += "SIX";
	break;
      case '7':
	inputText += "SEVEN";
	break;
      case '8':
	inputText += "EIGHT";
	break;
      case '9':
	inputText += "NINE";
	break;
    }

    return inputText;
}


