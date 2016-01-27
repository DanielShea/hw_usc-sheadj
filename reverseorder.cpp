#include <iostream>
#include <fstream>
#include <sstream>
#include <string>

using namespace std;

void helper(stringstream &words, int len){
   //terminate when all words have been read
   if(len <= 0){
      return;
   }
   
   //store the first word
   string s;
   if(words.good()){
      words >> s;
   }
   
   helper(words, len -1);
   
   cout << s << endl; //print the word that was stored after all before it
}

int main(int argc, char* argv[]){
   stringstream buffer;
   
   if(argc == 0){
      cout << "Enter a filename";
   }
   
   ifstream file(argv[1]); //open file

   if ( file )
   {
      //read into a buffer
      buffer << file.rdbuf();
      file.close();
      
      int i;
      buffer >> i; //get length
      
      helper(buffer, i); //call the recursive print
      
   } else {
      cout << argv[1] << " is not a valid file";
   }
}
