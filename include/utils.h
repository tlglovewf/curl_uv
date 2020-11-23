#ifndef _UTILS_H_
#define _UTILS_H_
#include <string>
#include <algorithm>
// #include <boost/optional.hpp>
#include <experimental/optional>
		
const static std::string tokenReservedChars = "{}";


template <typename T>
using optional = std::experimental::optional<T>;


class Utils
{
public:
    // Replaces {tokens} in a string by calling the lookup function.
    template <typename Lookup>
    static std::string replaceTokens(const std::string &source, const Lookup &lookup) 
    {
        std::string result;
        result.reserve(source.size());

        auto pos = source.begin();
        const auto end = source.end();

        while (pos != end) {
            auto brace = std::find(pos, end, '{');
            result.append(pos, brace);
            pos = brace;
            if (pos != end) {
                for (brace++; brace != end && tokenReservedChars.find(*brace) == std::string::npos; brace++);
                if (brace != end && *brace == '}') {
                    std::string key { pos + 1, brace };
                    if (optional<std::string> replacement = lookup(key)) {
                        result.append(*replacement);
                    } else {
                        result.append("{");
                        result.append(key);
                        result.append("}");
                    }
                    pos = brace + 1;
                } else {
                    result.append(pos, brace);
                    pos = brace;
                }
            }
        }

        return result;
    }
};

#endif