#include <stdio.h>
#include <stdlib.h>
#include <string>
#include <sys/epoll.h>
#include <curl/curl.h>
#include <assert.h>
#include <stdexcept>
#include <iostream>

CURLM *multi  = NULL;
CURL  *handle = NULL;

size_t write_file_cb(char *ptr, size_t size, size_t nmemb, FILE *userdata)
{
    FILE *file = static_cast<FILE*>(userdata);
    size_t len = fwrite(ptr,size,nmemb,file);
    return len;
}

int main(int argc, char *argv[])
{
    const std::string str = "http://fs.navinfo.com/smapapi/parking/mapV/data/vector?dataSource=Parkingmore&z=18&x=215770&y=99258";

    curl_global_init(CURL_GLOBAL_ALL);
    
    multi = curl_multi_init();

    //do once request 
    handle = curl_easy_init();
    curl_easy_setopt(handle,CURLOPT_URL,str.c_str());
    curl_easy_setopt(handle,CURLOPT_VERBOSE,1L);
    curl_easy_setopt(handle,CURLOPT_NOSIGNAL,1L);
    curl_easy_setopt(handle,CURLOPT_FORBID_REUSE,1);
    curl_easy_setopt(handle,CURLOPT_TIMEOUT,15);
    curl_easy_setopt(handle,CURLOPT_NOPROGRESS,1);

    std::string pbfdata;
    curl_easy_setopt(handle,CURLOPT_WRITEFUNCTION,write_file_cb);
    curl_easy_setopt(handle,CURLOPT_WRITEDATA,&pbfdata);
    
    curl_multi_add_handle(multi,handle);
    int running_handle = 1;

    while(running_handle)
    {
        curl_multi_perform(multi, &running_handle);
    }

    curl_easy_cleanup(handle);
    curl_multi_cleanup(multi);
    curl_global_cleanup();
    std::cout << "pbf size " << pbfdata.size() << std::endl;
    return 0;
}