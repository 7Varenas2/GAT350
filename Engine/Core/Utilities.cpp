#include "Utilities.h"
#include <algorithm>


namespace neu
{
    std::string ToLower(const std::string& str)
    {
        std::string lower = str;
        // Convert string characters to lower case
        std::transform(str.begin(), str.end(), lower.begin(), ::tolower);

        return lower;
        
    }

    std::string ToUpper(const std::string& str)
    {
        std::string upper = str;
        // Convert string character to upper case
        std::transform(str.begin(), str.end(), upper.begin(), ::toupper);

        return upper;
      
    }

    bool CompareIgnoreCase(const std::string& str1, const std::string& str2)
    {
        // If string lengths don't match return false
        // Way to fix error was adding const to the char since it was trying to convert (ERROR C2664)
        return ((str1.size() == str2.size()) && std::equal(str1.begin(), str1.end(), str2.begin(), [](const char & c1, const char & c2) {
            return (c1 == c2 || std::toupper(c1) == std::toupper(c2));
            }));

        // Returns false if string characters aren't equal

       return false;
    }
}