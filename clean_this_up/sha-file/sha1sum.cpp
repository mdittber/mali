#include <iostream>
#include <boost/filesystem.hpp>
#include <cryptopp/sha.h>
#include <cryptopp/hex.h>
#include <cryptopp/files.h>
using namespace std;
using namespace boost::filesystem;
 
string hashFile(const path &file);
 
int main( int argc, char** argv) {
	  string hash("");
		  path file("plaintext.txt");
			  hash = hashFile(file);
				  cout<<hash<<endl;
					  return 0;
}
 
string hashFile(const path &file)
{
	  string result;
		  CryptoPP::SHA1 hash;
			  CryptoPP::FileSource(file.string().c_str(),true, 
							new CryptoPP::HashFilter(hash, new CryptoPP::HexEncoder(
										new CryptoPP::StringSink(result), true)));
				  return result;
					 
}
