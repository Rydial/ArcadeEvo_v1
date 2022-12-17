#ifndef SRC_DEBUG_H
#define SRC_DEBUG_H


#include <iostream>
#include <sstream>
#include <string>


////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////// MACROS ////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////


#ifndef NDEBUG  // Debug Mode

    #define DEBUG_PRINT(...)  debug::print(__VA_ARGS__)

#else           // Release Mode

    #define DEBUG_PRINT(...)

#endif


////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////// DEBUG /////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////


namespace debug
{
    /******************************** Concepts ********************************/

    template<typename T>
    concept Stringable = requires (std::ostringstream oss, T t)
    {
        oss << t;
    };

    /***************************** Main Functions *****************************/

    /* 
        Returns Formatted String
    */
    template <Stringable ...Args>
    std::string str(const std::string&& format, Args&&... args)
    {
        size_t numOfArgs {sizeof...(Args)}, argIndex {};
        std::stringstream sstream {};

        /************************ String Construction *************************/
        
        auto iter {format.begin()};

        ([&] ()
        {
            if (argIndex < numOfArgs)
            {
                for (; iter != format.end(); ++iter)
                {
                    if (*iter == '%')
                    {
                        sstream << args;
                        ++argIndex;
                        ++iter;
                        return;
                    }
                    else
                        sstream << *iter;
                }
            }
        }(), ...);

        for (; iter != format.end(); ++iter)
            sstream << *iter;

        /************************* String Validation **************************/
    
        if (argIndex != numOfArgs)
        {
            std::cout << "\n[ DEBUG ] str() Error: Number of variables in "
                "format string exceeded number of arguments\n";

            std::abort();
        }

        /**********************************************************************/   
    
        return sstream.str();
    }


    /*
        Logs formatted message
    */
    template <Stringable ...Args>
    void print(const std::string&& format, Args&&... args)
    {
        // Print Formatted Message
        std::cout << '\n' << str(std::move(format), args...) << '\n';
    }
}


#endif // SRC_DEBUG_H
