#include <curl/curl.h>
#include <iostream>

using namespace std;


size_t write_file_cb(char *ptr, size_t size, size_t nmemb, FILE *userdata)
{
    FILE *file = static_cast<FILE*>(userdata);
    size_t len = fwrite(ptr,size,nmemb,file);
    return len;
}

size_t write_string_cb(char *ptr, size_t size, size_t nmemb, void *userdata)
{
    string &str = *(string*)userdata;
    if( NULL == ptr)
    {
        std::cout << "return ---------------- " << std::endl;
        return -1;
    }
    else
    {
        size_t totalSize = size * nmemb;
        str.append(ptr, totalSize);
        return totalSize;
    }
}

int main(int argc, char **argv)
{
    curl_global_init(CURL_GLOBAL_ALL);

    CURL *handle = curl_easy_init();
    const std::string str = "http://fs.navinfo.com/smapapi/parking/mapV/data/vector?dataSource=Parkingmore&z=18&x=215770&y=99258";
    std::cout << "current version" << curl_version() << std::endl;
    FILE *file = fopen("./text.pbf","w");
    std::string pbfdata;

    curl_easy_setopt(handle,CURLOPT_URL,str.c_str());
    curl_easy_setopt(handle,CURLOPT_VERBOSE,1L);
    curl_easy_setopt(handle,CURLOPT_NOSIGNAL,1L);
    curl_easy_setopt(handle,CURLOPT_TIMEOUT,15);
    curl_easy_setopt(handle,CURLOPT_NOPROGRESS,1);
    curl_easy_setopt(handle,CURLOPT_WRITEFUNCTION,write_file_cb);
    curl_easy_setopt(handle,CURLOPT_WRITEDATA,file);
    
    cout << "function run result : " << curl_easy_perform(handle) << endl;

    curl_easy_setopt(handle,CURLOPT_WRITEFUNCTION,write_string_cb);
    curl_easy_setopt(handle,CURLOPT_WRITEDATA,&pbfdata);

    curl_easy_perform(handle);
    std::cout << "pbf data size " << pbfdata.size() << std::endl;

    fclose(file);
    curl_easy_cleanup(handle);

    curl_global_cleanup();
    return 0;
}