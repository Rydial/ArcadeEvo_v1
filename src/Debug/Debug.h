#ifndef SRC_DEBUG_H
#define SRC_DEBUG_H


#include <iostream>
#include <sstream>
#include <string>


////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////// DEBUG /////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////


namespace debug
{
    /********************************* Macros *********************************/

    // #define stringify(x) (#x)       // Return identifier or literal value
    // #define xstringify(x) (stringify(x))

    /******************************* Constants ********************************/

#ifdef NDEBUG
    constexpr bool runtimeLogging {false};
#else
    constexpr bool runtimeLogging {true};

    constexpr unsigned int GREEN {0x00000000};
    constexpr unsigned int RED {0x00000001};

#endif

    /******************************** Concepts ********************************/

    template<typename T>
    concept Printable = requires(T t)
    {
        {std::cout << t} -> std::same_as<std::ostream&>;
    };

    template<typename T>
    concept Stringable = requires (std::ostringstream oss, T t)
    {
        oss << t;
    };

    /***************************** Main Functions *****************************/

    /*
        Logs message
    */
    template <Printable T>
    void print(const T& message)
    {
        std::cout << '\n' << message << '\n';
    }

    /*
        Logs formatted message
    */
    template <Stringable ...Args>
    void printf(const std::string&& format, Args&&... args)
    {
        /******************** Message String Construction *********************/
        
        size_t numOfArgs {sizeof...(Args)}, argIndex {};
        std::stringstream message {};
        auto iter {format.begin()};

        ([&] ()
        {
            if (argIndex < numOfArgs)
            {
                for (; iter != format.end(); ++iter)
                {
                    if (*iter == '%')
                    {
                        message << args;
                        ++argIndex;
                        ++iter;
                        return;
                    }
                    else
                        message << *iter;
                }
            }
        }(), ...);

        for (; iter != format.end(); ++iter)
            message << *iter;

        /**********************************************************************/

        // Error Check
        if (numOfArgs == 0)
            print("[ DEBUG ] printf() failed: No arguments provided");
        else if (argIndex != numOfArgs)
            print("[ DEBUG ] printf() failed: Number of format values does not "
                  "match number of arguments");

        // Print Constructed Message String
        else
            print(message.str());
    }
}


#endif // SRC_DEBUG_H
